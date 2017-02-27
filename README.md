# dcraw-fltk

## Description
Raw image processor utilizing the portable C++ 'Fast Light ToolKit' and Dave Coffin's C 'dcraw' program, compiled under Visual Studio 14 for Windows.

## Dependancies

### Fast Light Tool Kit (FLTK)
You will need to compile and link third-party libraries for this implementaiton of dcraw-fltk to work.
Uses the open-source [FLTK](http://www.fltk.org/index.php) GUI libraries, compiled under Visual Studio and linked to this project.
Please [follow the instructions here](https://bewuethr.github.io/installing-fltk-133-under-visual-studio/#comment-2065708873) carefully. It is for an earlier version of Visual Studio, but is still accurate.

### dcraw
dcraw is an open source raw image processor [created and maintained by Dave Coffin](https://www.cybercom.net/~dcoffin/dcraw/).
You will need the binary executable of dcraw. Currently provided in the /dcraw-fltk folder is the latest 64-bit binary: dcraw-9.27-ms-64-bit.exe.
You are free to compile it [from the source yourself - https://www.cybercom.net/~dcoffin/dcraw/dcraw.c](https://www.cybercom.net/~dcoffin/dcraw/dcraw.c) if you need a binary for a different architecture.
Additionally, [Sergio Namias has built some Windows binaries (including a 32-bit version) for download](http://www.centrostudiprogressofotografico.it/en/dcraw/).

Note - you will need to find/replace "dcraw-9.27-ms-64-bit.exe" in the solution if you compile or download a new binary.

### dcraw manual
*nix [man page for dcraw](https://www.cybercom.net/~dcoffin/dcraw/dcraw.1.html)

## Bug Reporting

Please use the [Issues](https://github.com/aaronmboyd/dcraw-fltk/issues) page to report bugs or suggest new enhancements.

## License

dcraw-fltk has been published under a [GPL 3.0](https://github.com/aaronmboyd/dcraw-fltk/blob/master/LICENSE)

