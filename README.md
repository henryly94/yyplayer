# yyplayer
A video player

## Usage

### Prequisites
- CMake (Version >= 3.1)
- Clang (Version >= 900.0.38)
- FFmpeg (Version >= 3.4.2)

### Install

```bash
mkdir -p build && cd build/
cmake ..
make
```

The binary file will be generated at bin/ , you can directly open the program by

```bash
cd ../bin
./player file_path
```

