{
  # NOTE: 'module_name' and 'module_path' come from the 'binary' property in package.json
  # node-pre-gyp handles passing them down to node-gyp when you build from source
  "targets": [
    {
      "target_name": "<(module_name)",
      "sources": [
        "src/main.cc",
        "src/native_input.cc",
        "src/native_input_mac.mm",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "./src/WinrtLib/WinrtLib"
      ],
      "defines": [
        'NAPI_DISABLE_CPP_EXCEPTIONS',
        'NAPI_VERSION=<(napi_build_version)',
      ],
      # Platform-specific includes
      # https://gyp.gsrc.io/docs/InputFormatReference.md#pattern-lists
      'sources/': [
        ['exclude', '_win\\.cc$'],
      ],
      'conditions': [
        ['OS!="linux"', {'sources/': [['exclude', '_linux\\.cc$']]}],
        ['OS!="mac"', {'sources/': [['exclude', '_mac\\.cc|mm?$']]}],
        ['OS=="win"',
          {'sources/': [
            ['include', '_win\\.cc$'],
            ['exclude', '_posix\\.cc$'],
          ],
        }],
      ],
      "configurations": {
        "Release": {
          "msvs_settings": {
            "VCCLCompilerTool": {
              # /MD (2) - use multithreaded module
              "RuntimeLibrary": 2,
              "AdditionalOptions": [
                "/std:c++20", # C++20 required by Chromium in Electron v33
                "/await",     # allow C++ coroutines
                "/DUNICODE",  # prefer Unicode win32 APIs
              ],
              "AdditionalOptions!": [
                "-std:c++17" # fix warning D9025: overriding '/std:c++17' with '/std:c++20'
              ],
            },
          },
          "xcode_settings": {
            "OTHER_LDFLAGS": [
              "-framework", "ApplicationServices"
            ]
          }
        },
        "Debug": {
          "msvs_settings": {
            "VCCLCompilerTool": {
              # /MDd (3) - use multithreaded module with debug symbols
              "RuntimeLibrary": 3,
              "AdditionalOptions": [
                "/std:c++20", # C++20 required by Chromium in Electron v33
                "/await",     # allow C++ coroutines
                "/DUNICODE",  # prefer Unicode win32 APIs
              ],
              "AdditionalOptions!": [
                "-std:c++17" # fix warning D9025: overriding '/std:c++17' with '/std:c++20'
              ],
            },
          },
          "xcode_settings": {
            "OTHER_LDFLAGS": [
              "-framework", "ApplicationServices"
            ]
          }
        },
      },
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    },
  ]
}
