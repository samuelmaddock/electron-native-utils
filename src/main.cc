#include <napi.h>

#include "native_input.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "nativeInput"), InitNativeInput(env));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
