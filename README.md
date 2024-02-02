# balls

## Description

spawns balls on ur screen lmao idk

uses a modified [Kbuffardi's bitmap](https://github.com/kbuffardi/Bitmap) library

## Installation

To install this project, follow these steps:

1. Clone the repository
2. (Windows) Compile using `compile.bat` (no debugger flags) or `compileg.bat` (w/ debugging flags)
   1. (Alternative) compile `.o` objectfiles via `gcc`/`g++` and then link them together into binaries (refer to batchfiles)

## Usage

To use this project, after building, pass some cmdline args, w/ row-important order: `<filename> <width> <height> <num_objects>`, e.g. `balls 1920 1080 100`. You can play around with *BlendModes* too, maybe even create your own filters (TODO, currently) and idk this is v silly

## License

This project is licensed under the [MIT License](LICENSE).
