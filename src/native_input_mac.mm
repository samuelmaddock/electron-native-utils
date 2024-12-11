#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>

#include <napi.h>

Napi::Value SetMousePosition(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // Validate arguments
  if (info.Length() < 1 || !info[0].IsObject()) {
    Napi::TypeError::New(env, "Expected an object").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Object options = info[0].As<Napi::Object>();

  if (!options.Has("x") || !options.Get("x").IsNumber()) {
    Napi::TypeError::New(env, "Expected x as a number").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!options.Has("y") || !options.Get("y").IsNumber()) {
    Napi::TypeError::New(env, "Expected y as a number").ThrowAsJavaScriptException();
    return env.Null();
  }

  double x = options.Get("x").As<Napi::Number>().DoubleValue();
  double y = options.Get("y").As<Napi::Number>().DoubleValue();

  CGPoint movePoint = CGPointMake(x, y);

  // Create a mouse move event
  CGEventRef moveEvent = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, movePoint, kCGMouseButtonLeft);
  if (moveEvent == NULL) {
    Napi::Error::New(env, "Failed to create mouse move event").ThrowAsJavaScriptException();
    return env.Null();
  }

  CGEventPost(kCGSessionEventTap, moveEvent);
  CFRelease(moveEvent);

  return env.Undefined();
}

Napi::Value MouseClick(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // Validate arguments
  if (info.Length() < 1 || !info[0].IsObject()) {
    Napi::TypeError::New(env, "Expected an object").ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Object options = info[0].As<Napi::Object>();

  if (!options.Has("button") || !options.Get("button").IsString()) {
    Napi::TypeError::New(env, "Expected button as 'left' or 'right'").ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string button = options.Get("button").As<Napi::String>();

  CGEventType downEventType;
  CGEventType upEventType;
  CGMouseButton mouseButton;

  if (button == "left") {
    downEventType = kCGEventLeftMouseDown;
    upEventType = kCGEventLeftMouseUp;
    mouseButton = kCGMouseButtonLeft;
  } else if (button == "right") {
    downEventType = kCGEventRightMouseDown;
    upEventType = kCGEventRightMouseUp;
    mouseButton = kCGMouseButtonRight;
  } else {
    Napi::TypeError::New(env, "Button must be 'left' or 'right'").ThrowAsJavaScriptException();
    return env.Null();
  }

  // Get current mouse position
  CGEventRef currentEvent = CGEventCreate(NULL);
  CGPoint clickPoint = CGEventGetLocation(currentEvent);
  CFRelease(currentEvent);

  // Create and post the mouse down event
  CGEventRef downEvent = CGEventCreateMouseEvent(NULL, downEventType, clickPoint, mouseButton);
  if (downEvent == NULL) {
    Napi::Error::New(env, "Failed to create mouse down event").ThrowAsJavaScriptException();
    return env.Null();
  }
  CGEventPost(kCGSessionEventTap, downEvent);
  CFRelease(downEvent);

  // Create and post the mouse up event
  CGEventRef upEvent = CGEventCreateMouseEvent(NULL, upEventType, clickPoint, mouseButton);
  if (upEvent == NULL) {
    CFRelease(downEvent);
    Napi::Error::New(env, "Failed to create mouse up event").ThrowAsJavaScriptException();
    return env.Null();
  }
  CGEventPost(kCGSessionEventTap, upEvent);
  CFRelease(upEvent);

  return env.Undefined();
}
