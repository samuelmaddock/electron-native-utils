# electron-native-utils

Additional native utilities for Electron.

## Building

### Requirements

- Windows: Visual Studio 2022

### Commands

- `yarn build` - Incremental builds.
- `yarn build:ci` - Clean and fully rebuild.
- `yarn build:debug` - Debug builds for easier debugging.

## Architecture

electron-native-utils uses [node-gyp](https://github.com/nodejs/node-gyp) to configure and build .node binaries.

It uses [Node-API](https://github.com/nodejs/node-addon-api) to provide JavaScript bindings to native code.
- [Node addon docs](https://nodejs.org/docs/latest/api/addons.html)
- [Node-API examples](https://github.com/nodejs/node-addon-examples)

### Files
- `src/` - contains C++ source and header files
- `lib/index.js` - main entry point of the node module
- `lib/index.d.ts` - TypeScript type definitions
- `binding.gyp` - build config for node-gyp
- `test.js` - simple test script to require and invoke the module's API to ensure no crashes occur

### API Design

- Group functionality by namespaces
- Prefer promises over callbacks for async
- Reject promises with an `Error` instead of a string
- Exported bindings should be available on each platform (Windows, Mac, Linux)
  - When a function returns a promise, it should reject on unsupported platforms. \
    Otherwise, it should throw an exception.

### Writing cross-platform code

- Source files can be compiled for specific patterns using a filename postfix.
  - `_win` - Windows
  - `_mac` - macOS
  - `_linux` - Linux
- Platform-specific macros can be used to export methods which throw on
  unsupported platforms.
  ```cpp
  Napi::Object InitApi(Napi::Env env) {
    Napi::Object exports = Napi::Object::New(env);
    // Method throws on non-Windows platforms.
    METHOD_WIN(winMethodName, WinMethod);

    // Method throws on non-MacOS platforms.
    METHOD_MAC(macMethodName, MacMethod);

    // Async variants which reject returned promise on unsupported platforms.
    METHOD_ASYNC_WIN(asyncMethod, AsyncMethod);
    METHOD_ASYNC_MAC(asyncMethod, AsyncMethod);
    return exports;
  }
  ```
- Platform defines can be used to conditionally include code.
  ```cpp
  #ifdef _WIN32
    // Windows code
  #endif // _WIN32

  // OR

  #if defined(_WIN32)
    // Windows code
  #elif defined(__APPLE__)
    // Mac code
  #elif defined(__linux__)
    // Linux code
  #endif
  ```
