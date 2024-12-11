#include "native_input.h"
#include "utils.h"

Napi::Object InitNativeInput(Napi::Env env) {
  Napi::Object exports = Napi::Object::New(env);
  METHOD_MAC(click, MouseClick);
  METHOD_MAC(setMousePosition, SetMousePosition);
  return exports;
}
