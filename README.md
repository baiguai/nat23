# Nat23

A command-line dice roller for tabletop RPGs. Input dice notation, get results. No frills.

## Usage

Run the executable.
Type a roll at the prompt.
Type `?` for help.
Type `q` to quit.

### Roll notation

- Basic: `<number>d<sides>` -- e.g. `2d6` rolls two six-sided dice.
- Multiple rolls: `<count>*<roll>` -- e.g. `2*3d6` does two separate 3d6 rolls.
- Best of: `(<keep>)<roll>` -- e.g. `(2)4d6` rolls 4d6 and keeps the highest 2.
- Advantage: `<roll>+<mod>` -- e.g. `3d6+2` adds 2 to the total.
- Penalty: `<roll>-<mod>` -- e.g. `3d20-2` subtracts 2.
- All of these can be combined: `2*(3)4d6+1`

### Presets

Rolls can be saved and recalled from a `presets.conf` file in the current directory.

- `save` -- save your last roll as a preset.
- `presets` -- list saved presets.
- `preset <n>` -- run a saved preset by number.
- `delete <n>` -- delete a preset by number.

## Build

Requires CMake 3.16+ and a C++17 compiler.

```
mkdir build && cd build
cmake ..
make
```

The binary goes in `build/bin/`. Or just run `./build.sh`.

On Linux with mingw-w64, use `windows_build.sh` to cross-compile for Windows.
On Windows, run `windows_build.bat` from a Visual Studio or MinGW command prompt, or `windows_run.bat` to build and run in one step.
