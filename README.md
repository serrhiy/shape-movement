### How to build

1. Install dependecies for glfw3. In Debian or Ubuntu:

`sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config`

2. Add `CMakeUserPresets.json` to source directory:

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "release",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "/home/serhii/vcpkg"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "debug",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "/home/serhii/vcpkg"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    }
  ]
}
```

3. Run CMake in source directory:

```shell
cmake --preset=release # or debug
cmake --build build
```
