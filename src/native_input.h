#ifndef SRC_NATIVE_INPUT_H_
#define SRC_NATIVE_INPUT_H_

#include <napi.h>

Napi::Object InitNativeInput(Napi::Env env);
Napi::Value SetMousePosition(const Napi::CallbackInfo& info);
Napi::Value MouseClick(const Napi::CallbackInfo& info);

#endif // SRC_NATIVE_INPUT_H_
