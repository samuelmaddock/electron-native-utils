#include "utils.h"

Napi::Boolean MethodNotImplemented(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::TypeError::New(env, "Method not implemented")
      .ThrowAsJavaScriptException();
  return Napi::Boolean::New(env, false);
}

Napi::Promise AsyncMethodNotImplemented(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);
  deferred.Reject(Napi::String::New(env, "Method not implemented"));
  return deferred.Promise();
}
