# hl2sdk-starter

A starter template for hl2sdk server plugins.

## Requirements

Meson, Ninja, gcc.

## Support

| Compiler | Linux x86 | Linux x64 | Windows x86 | Windows x64 |
| ----     | ----      | ----      | ----        | ----        |
| gcc      | yes       | yes       | ?           | ?           |
| clang    | ?         | ?         | ?           | ?           |
| msvc     | ?         | ?         | ?           | ?           |

## Building

1. Check out the correct SDK branch, e.g. `tf2`:
```
git submodule update --init
cd include/hl2sdk
git checkout tf2
cd ../..
```

2. Setup Meson build folder
```
meson setup -D arch=x86 -D buildtype=debug build
```

3. Build with Meson
```
cd build
meson compile
```

