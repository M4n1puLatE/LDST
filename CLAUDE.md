# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

This is a CMake-based C++20 project using Ninja generator. The project uses CMake presets for configuration.

### Configure and Build
```bash
# Configure with a preset (e.g., x64-debug)
cmake --preset x64-debug

# Build the configured project
cmake --build out/build/x64-debug

# Alternatively, use the preset for both configure and build
cmake --build --preset x64-debug
```

### Available Presets
- `x64-debug` – Windows x64 Debug (default)
- `x64-release` – Windows x64 Release
- `x86-debug` – Windows x86 Debug
- `x86-release` – Windows x86 Release
- `linux-debug` – Linux Debug
- `macos-debug` – macOS Debug

The output directory follows the pattern `out/build/<preset-name>`.

### Running the Main Executable
After building, the main application `LDST.exe` (Windows) or `LDST` (Unix) is located at:
```
out/build/<preset>/LDST/LDST
```

### Running Tests
The test executable `Tester` is built and can be run directly:
```
out/build/<preset>/Tester/Tester
```
It runs all registered unit tests (currently LinkList tests) and reports success/failure with colored output.

## Project Architecture

### Subdirectories
- **LDST/** – Main executable placeholder (currently just prints "Hello CMake.")
- **Linear/** – Core data structures library
- **Util/** – Utility library (string splitting, timers)
- **Tester/** – Unit testing framework and test implementations
- **MemoryPool/** – Placeholder (not yet integrated into build)
- **docs/** – Documentation site (likely personal blog)

### Linear Library (`Linear/include/`)
- **Collection.h** – Defines the `is_collection` concept and `CollectionOperation` base class with generic algorithms (`assign`, `compare`).
- **Node.h** – Generic `Node<T>` class for linked structures. Requires `Container` concept (default constructible, copyable, comparable).
- **LinkList.h** – Doubly linked list implementation inheriting from `CollectionOperation`. Provides full CRUD operations, range views, and exception handling (`OutOfRangeException`).
- **Views.h** – `ListView<Node>` for read-only iteration over a segment of nodes.

Key design patterns:
- CRTP (Curiously Recurring Template Pattern) used in `CollectionOperation` where derived classes pass themselves as template parameter.
- Concepts (`is_collection`, `Container`) constrain template parameters.
- Exception-safe operations with `OutOfRangeException` for bounds checking.

### Utility Library (`Util/include/`)
- **Util.h** – String splitting functions (`SplitString`, `IndexSplitString`).
- **Timer.h** – Generic timer class templated on `std::chrono` duration types.

### Testing Framework (`Tester/include/`)
- **Tester.h** – Generic test runner using the CRTP. Derived test classes register functions via `add(name, lambda)`. Supports timed tests and colored console output.
- **LinkListTester.h** – Example test suite for `LinkList`. New test suites should follow the same pattern: inherit from `Tester<Derived>`, declare `A_TEST;`, implement `init()` to register test methods.

### Adding New Tests
1. Create a new test class in `Tester/include/` (e.g., `MyClassTester.h`) that inherits from `Tester<MyClassTester>`.
2. Add `A_TEST;` macro inside the class.
3. Declare an `init()` method that calls `add("testName", TEST_FUNCTION(method))` for each test case.
4. Implement test methods returning `bool` (`true` for pass).
5. Add the new header to `Tester/include/Tests.h`.
6. The test will be automatically run when the `Tester` executable is executed.

### Memory Pool
The `MemoryPool` directory contains a stub header but is not currently referenced in the CMake build. It may be a future component.

## Development Notes
- The project uses C++20 features (concepts, ranges, `std::format`).
- Build artifacts are placed under `out/` (ignored by `.gitignore`).
- The `Tester` framework is not thread-safe; tests run sequentially.
- The `LinkList` implementation is a doubly linked list with head/tail pointers; `Node` objects are allocated with `new`/`delete`.
- The `CONTAINER` macro defines a template constraint for types that satisfy the `Container` concept (default constructible, copyable, comparable).