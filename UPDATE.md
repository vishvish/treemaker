# TreeMaker Modernization Plan

## Current State

- Version: TreeMaker 5.0.1 (Build 20060413)
- wxWidgets Version: 3.2.6
- Minimum OS: macOS 10.4.2
- Build System: CMake
- Language: Pre-modern C++

## Modernization Phases

### Phase 1: Build System and Basic Compilation

#### Build System Modernization

- [x] Initial CMake setup
- [x] Complete CMake configuration
- [ ] Remove CVS-based scripts
- [ ] Add package management (Conan/vcpkg)
- [ ] Update XCode project format
- [x] Support both Intel and ARM architectures

#### Basic Compilation

- [x] Update compiler flags
- [ ] Fix template dependency issues
- [x] Update wxWidgets to 3.2.6
- [x] Fix dangling else warnings in tmTree.cpp and tmVertex.cpp
- [x] Fix tmOnAssert ambiguity in tmHeader.cpp
- [x] Fix event handling in tmwxApp.cpp for wxWidgets 3.2
- [ ] Fix remaining compilation errors
- [ ] Update minimum macOS version to 10.13

### Phase 2: Core Modernization

#### C++ Modernization

- [ ] Update to C++17 standard
- [ ] Replace C-style headers
- [ ] Update template code patterns
- [ ] Add proper namespacing

#### Memory Management

- [ ] Replace raw pointers with smart pointers
- [ ] Update custom array classes to use std containers
- [ ] Fix memory leaks
- [ ] Update resource management

#### Data Structures

- [ ] Modernize tmDpptrArray implementation
- [ ] Update container usage
- [ ] Add RAII patterns
- [ ] Update error handling

### Phase 3: GUI Modernization

#### wxWidgets Updates

- [ ] Update to wxWidgets 3.2 API
- [ ] Replace deprecated calls
- [ ] Update event handling
- [ ] Modernize document/view framework

#### GUI Components

- [ ] Update tmwxCommon utilities
- [ ] Modernize tmwxDocView
- [ ] Update tmwxInspector
- [ ] Refresh tmwxPalette
- [ ] Update tmwxViewSettings
- [ ] Modernize tmwxHtmlHelp

#### Modern GUI Features

- [ ] Add high DPI support
- [ ] Update window styles
- [ ] Modernize dialogs
- [ ] Add accessibility support

### Phase 4: Platform Integration

#### macOS Integration

- [ ] Update Info.plist
- [ ] Add code signing
- [ ] Update icon resources
- [ ] Add entitlements
- [ ] Implement sandboxing

#### Modern Features

- [ ] Add dark mode support
- [ ] Update to modern UI guidelines
- [ ] Update file associations
- [ ] Add modern macOS integration

#### Deployment

- [ ] Update deployment process
- [ ] Add notarization
- [ ] Update installation process
- [ ] Add auto-update capability

### Phase 5: Quality and Polish

#### Testing

- [ ] Add unit testing framework
- [ ] Add integration tests
- [ ] Add GUI tests
- [ ] Add test automation

#### CI/CD

- [ ] Set up CI pipeline
- [ ] Add automated builds
- [ ] Add code quality checks
- [ ] Add automated deployment

#### Documentation

- [ ] Update build instructions
- [ ] Update API documentation
- [ ] Add modern README.md
- [ ] Add contribution guidelines

## Component-Specific Updates

### Core Components

- tmModel/
  - [ ] Update solver implementations
  - [ ] Modernize optimization code
  - [ ] Update tree classes
  - [ ] Fix template issues

### GUI Components

- tmwxGUI/
  - [ ] Update all GUI components
  - [ ] Fix deprecation issues
  - [ ] Add modern features
  - [ ] Update help system

## Progress Tracking

- ✅ Phase 1 In Progress
- ⬜ Phase 2 Not Started
- ⬜ Phase 3 Not Started
- ⬜ Phase 4 Not Started
- ⬜ Phase 5 Not Started

## Notes

### Breaking Changes

1. Minimum OS version increase
2. wxWidgets API changes
3. Template implementation updates
4. Memory management changes

### Dependencies

1. wxWidgets 3.2.6+
2. Modern C++ compiler
3. CMake 3.15+
4. Modern XCode

### Build Requirements

- macOS 10.13 or later
- XCode 14+
- CMake 3.15+
- wxWidgets 3.2.6+

## Timeline Estimates

- Phase 1: 1-2 weeks
- Phase 2: 2-3 weeks
- Phase 3: 2-3 weeks
- Phase 4: 1-2 weeks
- Phase 5: 1-2 weeks

Total estimated time: 7-12 weeks

## Contributors

- Original Author: Robert J. Lang
- Current Maintainers: TBD
