# hl2sdk-starter

A starter template for hl2sdk server plugins.

## Requirements

Meson, Ninja, gcc/clang.

## Support

For more details check out the `build-matrix.sh` script and meson files.

### Linux

| Branch      | gcc     | clang |
| ----        | ----    | ----  |
| bgt         | x86     | x86   |
| blade       | -       | -     |
| bms         | -       | -     |
| contagion   | -       | -     |
| cs2         | -       | -     |
| csgo        | -       | -     |
| css         | x86     | x86   |
| darkm       | -       | -     |
| dods        | x86     | x86   |
| doi         | -       | -     |
| dota        | -       | -     |
| episode1    | -       | -     |
| eye         | x86     | x86   |
| gmod        | x86     | -     |
| hl2dm       | x86     | x86   |
| insurgency  | -       | -     |
| l4d         | x86     | x86   |
| l4d2        | x86     | x86   |
| mcv         | -       | -     |
| nucleardawn | x86     | x86   |
| orangebox   | x86     | x86   |
| portal2     | -       | -     |
| pvkii       | -       | -     |
| sdk2013     | -       | -     |
| swarm       | -       | -     |
| tf2         | x86/x64 | -     |

### Windows

Not at the moment.

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

