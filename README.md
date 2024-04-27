# hl2sdk-starter

A starter template for hl2sdk server plugins.

## Requirements

Meson, Ninja, gcc.

## Support

### Compiler & targets

|          | Linux x86 | Linux x64 | Windows x86 | Windows x64 |
| ----     | ----      | ----      | ----        | ----        |
| gcc      | yes       | yes       | no          | no          |
| clang    | no        | no        | no          | no          |
| msvc     | no        | no        | no          | no          |

### SDK branches

| Branch      | Supported |
| ----        | ----      |
| bgt         | yes       |
| blade       | no        |
| bms         | no        |
| contagion   | no        |
| cs2         | no        |
| csgo        | no        |
| css         | yes       |
| darkm       | no        |
| dods        | yes       |
| doi         | no        |
| dota        | no        |
| episode1    | no        |
| eye         | yes       |
| gmod        | yes       |
| hl2dm       | yes       |
| insurgency  | no        |
| l4d         | yes       |
| l4d2        | yes       |
| mcv         | no        |
| nucleardawn | yes       |
| orangebox   | yes       |
| portal2     | no        |
| pvkii       | no        |
| sdk2013     | no        |
| swarm       | no        |
| tf2         | yes       |

For more details check out the `build-matrix.sh` script and meson files.

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

