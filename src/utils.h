#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <napi.h>

#ifdef _WIN32
#include "utils_win.h"
#endif // _WIN32

Napi::Boolean MethodNotImplemented(const Napi::CallbackInfo& info);
Napi::Promise AsyncMethodNotImplemented(const Napi::CallbackInfo& info);

#ifdef _WIN32
#define METHOD_WIN(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, Method)); \
  }
#define METHOD_ASYNC_WIN(name, Method) \
  METHOD_WIN(name, Method);
#else
#define METHOD_WIN(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, MethodNotImplemented)); \
  }
#define METHOD_ASYNC_WIN(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, AsyncMethodNotImplemented)); \
  }
#endif

#if defined(__APPLE__)
#define METHOD_MAC(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, Method)); \
  }
#define METHOD_ASYNC_MAC(name, Method) \
  METHOD_MAC(name, Method);
#else
#define METHOD_MAC(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, MethodNotImplemented)); \
  }
#define METHOD_ASYNC_MAC(name, Method) \
  { \
      exports.Set(Napi::String::New(env, #name), \
                  Napi::Function::New(env, AsyncMethodNotImplemented)); \
  }
#endif

#endif // SRC_UTILS_H_