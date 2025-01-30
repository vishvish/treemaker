# wxEvtHandler Segfault - January 30, 2025

## Crash Location
The application crashes in `wxEvtHandler::TryHereOnly` with an EXC_BAD_ACCESS error.

## Backtrace
```
Process 14531 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=2, address=0x16f603fe0)
    frame #0: 0x0000000100bfe2f0 libwx_baseu-3.2.0.3.0.dylib`wxEvtHandler::TryHereOnly(wxEvent&)
```

## Context
- This crash occurs immediately after application launch
- The application is built with wxWidgets 3.2.0
- The crash happens during event handling initialization
- Last log message before crash: "Unable to open mach-O at path: default.metallib Error:2"

## Build Information
- Built using build-tm-modern.sh
- Platform: macOS (arm64)
- Compiler warnings during build:
  1. Format warning in wnrnd.c
  2. Int-to-void-pointer cast warning in wnmemg.c
  3. Deprecated function declaration warnings in wnmem.c

## Root Cause Analysis
The crash is caused by infinite recursion in the event handling system. Specifically:

1. The backtrace shows over 149,000 recursive calls between:
   ```
   tmwxApp::ProcessEvent -> wxEvtHandler::TryAfter -> tmwxApp::ProcessEvent -> wxEvtHandler::TryAfter
   ```

2. The issue is in `tmwxApp::ProcessEvent`:
   - It has an event stack to prevent recursion
   - But it never adds events to the stack before processing them
   - This allows infinite recursion when processing events through other handlers

3. The recursion eventually causes a stack overflow, leading to the segmentation fault

## Steps to Reproduce
1. Build application using mac/build-tm-modern.sh
2. Launch the built application
3. Segfault occurs immediately on startup

## Fix Required
1. In `tmwxApp::ProcessEvent`, add the current event to the stack before processing it
2. Remove it from the stack after processing is complete
3. Consider using RAII (e.g., a scoped guard) to ensure the event is always removed from the stack

## Additional Notes
- The crash appears to be related to wxWidgets event handling initialization
- May be related to the Metal graphics framework initialization (given the metallib error)
- Need to investigate if this is related to arm64 architecture support in wxWidgets 3.2.0
