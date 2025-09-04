### How to build

1. Install dependecies for glfw3. In Debian or Ubuntu:

`sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config`

2. Add `CMakeUserPresets.json` in source directory:

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<path to vcpkg>"
      }
    }
  ]
}
```

3. Run CMake in source directory:

`cmake --preset=default`
