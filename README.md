TreeMaker 5.1.2
================

A program for origami design.

*Originally written by Robert J. Lang, et al.*

2026 update for macOS by Vish Vishvanath, et al.

TreeMaker is a program for the design of origami bases and a sophisticated tool
that helps you create complex origami figures using the tree theory of origami
design. You draw a stick figure on a square, assign lengths to each stick, and
TreeMaker computes a crease pattern that folds into the corresponding base.

Download
--------

Signed and notarized macOS builds are available from the
[Releases](https://github.com/vishvish/treemaker/releases) page.

- **macOS**: Apple Silicon (arm64), requires macOS 13.3 Ventura or later

What's New in 5.1.2
--------------------

- Built for Apple Silicon (arm64) with wxWidgets 3.2.7
- Signed with Developer ID and notarized by Apple
- Fixed crash in condition path inspector panels (issue #9)
- C++20 codebase, compiled with Clang 17
- Self-contained build system with no system-wide dependencies

Building from Source
--------------------

### Prerequisites

- macOS 13.3 or later
- Xcode Command Line Tools (`xcode-select --install`)
- CMake 3.15 or later (`brew install cmake`)

### Build

The included `build.sh` script downloads wxWidgets 3.2.7, compiles it locally
under `deps/`, then builds TreeMaker. No system-wide installation of wxWidgets
is required.

```sh
# Debug build (default)
./build.sh

# Release build
./build.sh Release
```

The built application will be at `build/bin/TreeMaker.app`.

To remove build artifacts:

```sh
# Remove TreeMaker build only (keeps wxWidgets)
./build.sh clean

# Remove everything including wxWidgets
./build.sh clean-all
```

### Debugging

```sh
lldb build/bin/TreeMaker.app/Contents/MacOS/TreeMaker
```

Credits
-------

- Robert J. Lang (lead author)
- Carlos Furuti (Linux port)
- Wlodzimierz 'ABX' Skiba (Windows port)
- Vish Vishvanath (2025-6 macOS refresh)

Special thanks to Erik D. Demaine, Martin L. Demaine, Toshiyuki Meguro, Alex
Bateman, Marshall Bern, Barry Hayes, Tom Hull, and Fumiaki Kawahata for
algorithmic insight. Thanks to Stefan Csomor and the wxWidgets team, and to
Will Naylor and Bill Chapman (authors of wnlib).

License
-------

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version. See [LICENSE.txt](LICENSE.txt) for details.

---

Information for Programmers
---------------------------

TreeMaker consists of several projects that can be built individually or
together. Source code and headers for all projects is contained within the
Source directory. TreeMaker can be built as a model-only library or as the
full application with GUI. All the code to build the model is in the included
files. However, you will need to download and build the wxWidgets libraries
(<www.wxwidgets.org>) in order to build the TreeMaker application with GUI.

On macOS, `build.sh` handles the wxWidgets download, build, and configuration
automatically.

### Source layout

- `Source/tmModel` -- the complete TreeMaker mathematical model (no GUI, no
  wxWidgets dependency)
- `Source/tmwxGUI` -- the TreeMaker GUI, built on wxWidgets
- `Source/test` -- command-line test programs for parts of the model
- `Source/images` -- images such as the splash screen
- `Source/about` -- the about page shown in the application
- `Source/help` -- the built-in help documentation

`tmHeader.h` is the required prefix header for all code (precompiled via
`tmPrec.cpp`). `tmHeader.cpp` contains assertion and log code common to all
files.

### Preprocessor symbols

The relevant compiler symbols are:

- `__WXDEBUG__` -- wxWidgets debug symbol
- `TMDEBUG` -- TreeMaker debug assertions
- `TMPROFILE` -- profiling / timing output
- `TMWX` -- building with wxWidgets GUI

For a release build of the full app, define only `TMWX`.

### Build configurations

- **Debug** -- `__WXDEBUG__` + `TMWX`, no optimizations, full symbols. Links
  against wxWidgets debug libraries. Assertions break into the debugger.
- **Development** -- `TMDEBUG` + `TMWX`, no optimizations, symbols. Links
  against wxWidgets release libraries. Assertions show a dialog then terminate.
- **Profile** -- `TMPROFILE` + `TMWX`, full optimizations, symbols. Writes
  timing info to log. Assertions compiled out.
- **Release** -- `TMWX` only, full optimizations. Assertions compiled out,
  no timing or log output.

### Test code

The test files are command-line tools for debugging parts of the model (no GUI).
Do not define `TMWX` for test code. Header search paths should include all
folders in `Source/` recursively.

| Test file | Purpose | Dependencies |
|-----------|---------|-------------|
| `tmArrayTester.cpp` | General-purpose container class | `tmHeader.cpp`, `tmModel/tmPtrClasses` |
| `tmDpptrTester.cpp` | Dangle-proof pointer/array classes | `tmHeader.cpp`, `tmModel/tmPtrClasses` |
| `tmNewtonRaphsonTester.cpp` | Newton-Raphson root-finding | `tmHeader.cpp`, `tmModel/tmPtrClasses` |
| `tmNLCOTester.cpp` | Nonlinear constrained optimization | `tmHeader.cpp`, `tmModel/tmPtrClasses`, `tmModel/tmNLCO`, `tmModel/wnlib` |
| `tmModelTester.cpp` | Full model including optimizers | `tmHeader.cpp`, `tmModel` (all subdirectories) |

---

### Code conventions

The codebase is split into three groups, identifiable by prefix:

- **`tm`** -- model classes (`tmNode`, `tmTree`, `tmEdge`, etc.)
- **`wx`** -- wxWidgets library classes
- **`tmwx`** -- TreeMaker GUI classes built on wxWidgets (`tmwxApp`,
  `tmwxDesignCanvas`, etc.)

Naming rules:

- Classes use `PascalCase` with the appropriate prefix
- Functions use `PascalCase`
- Variables use `camelCase`
- Member variables start with `m` (`mLoc`, `mPath`)
- Static members start with `s` (`sTag`)
- Macros, constants, and enum values use `ALL_CAPS`

Implementation files may be split with a `_Usage` suffix (e.g.
`MyClass_IO.cpp`). The model (`tmModel`) uses exceptions, RTTI, and template
specialization. It does not depend on wxWidgets.
