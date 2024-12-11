#ifndef SRC_UTILS_WIN_H_
#define SRC_UTILS_WIN_H_

#include <string>
#include <comdef.h>
#include <windows.h>
#include <winrt/Windows.Foundation.h>

// NOTE: This header file is included in multiple objects. inline is used to
// prevent multiple colliding symbols during linking. If we wish to remove this
// in the future, move the function definitions into a .cc file.

// Function to convert const wchar_t* to std::string using UTF-8 encoding
inline std::string wchar_to_string(const wchar_t* wchar_str) {
  if (!wchar_str) {
    return std::string();
  }

  // Determine the size of the resulting multi-byte string
  int size_needed = WideCharToMultiByte(CP_UTF8, 0, wchar_str, -1, nullptr, 0, nullptr, nullptr);
  if (size_needed <= 0) {
    return std::string();
  }

  // Allocate a string to hold the converted result
  std::string str(size_needed, 0);

  // Perform the conversion
  WideCharToMultiByte(CP_UTF8, 0, wchar_str, -1, &str[0], size_needed, nullptr, nullptr);

  // Remove the null terminator added by WideCharToMultiByte
  str.pop_back();

  return str;
}

// <message> (<code>)
inline std::string format_hresult_error(winrt::hresult_error const& ex) {
  std::string errorText = winrt::to_string(ex.message()).c_str();
  std::string errorCode = std::to_string(static_cast<int>(ex.code()));
  std::string error = errorText + " (" + errorCode + ")";
  return error;
}

inline std::string format_com_hresult_error(HRESULT hr) {
  _com_error err(hr);
  const TCHAR* errorMsg = err.ErrorMessage();
  std::string errorText = wchar_to_string(errorMsg);
  std::string errorCode = std::to_string(hr);
  std::string error = errorText + " (" + errorCode + ")";
  return error;
}

#define THROW_TYPE_ERROR_AND_RETURN_UNDEFINED_PROMISE(env, message) \
  Napi::TypeError::New(env, message).ThrowAsJavaScriptException(); \
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env); \
  deferred.Resolve(env.Undefined()); \
  return deferred.Promise();

#define IF_FAILED_HR_RETURN_ERROR_MESSAGE(hr, error, message) \
  if (FAILED(hr)) { \
    std::string messageStr(message); \
    std::string formattedError = format_com_hresult_error(hr); \
    error = messageStr + ": " + formattedError; \
    return; \
  }

#endif // SRC_UTILS_WIN_H_