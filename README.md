# Stable Project Template

A comprehensive multi-library project template focussed on compatibility with older CMake versions.

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/CMake-Blueprints/stable-project-template/build-and-test.yml)

- Compatible with CMake 3.4+
- Includes compiled and header-only library examples
- Supports installing Debug and Release configuration to the same directory
- Provides versioning info to `find_package()` calls
- Able to handle `find_package()` calls for transitive dependencies
- Safe to use in a superbuild as all targets are namespaced
- Includes hacks to allow unit testing of non-exported library symbols

> [!IMPORTANT]
> Many of the patterns in this example have been superceded by superior solutions. If you are starting a new project, it is highly recommended to use the [State-of-the-Art Project Template](https://github.com/CMake-Blueprints/state-of-the-art-project-template) instead.

## Caveats

This project is designed for compatibility with older versions of CMake. As such, there are some caveats to be aware of:

- Tests must recompile any source files for non-exported symbols they want to test. Using `OBJECT` libraries would save on compile time, but they are very verbose to use in older CMake versions.
- `CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT` is only set in CMake 3.7.1+. When using older versions, the install prefix must be specified manually.

## Building and Testing

This project uses CTest to run tests regardless of the test framework used.

<details>
<summary>Linux (Ninja build system)</summary>

The following commands will build the project with the default compiler in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```bash
# Optional: Install ninja-build (Debian/Ubuntu shown)
sudo apt install ninja-build

# Configure and build (Release)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --target install
rm -rf build/

# Configure amnd build (Debug)
cmake -S . -B build/ -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/ --target install

# Test
cd build/
ctest --output-on-failure
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(MyProject)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

<details>
<summary>Windows (Visual Studio 2022)</summary>

The following commands will build the project with MSVC v143 in both Debug and Release configurations, run the tests in Debug configuration, and install the library to the `install` directory.

```powershell
# Configure
cmake -S . -B .\build\ -G "Visual Studio 17 2022" -A x64

# Build
cmake --build .\build\ --target install --config Debug
cmake --build .\build\ --target install --config Release

# Test
cd .\build\
ctest --output-on-failure -C Debug
cd ..
```

The `install` directory will contain CMake configuration files for both Debug and Release configurations and can be used by other CMake projects. Add a `find_package(MyProject)` statement to the consuming project and make sure that the install path is added to the `CMAKE_PREFIX_PATH` variable.

</details>

## Adapting This Template

This template is designed to be easily adapted to your needs. The following steps will help you get started:

1. Click on "Use this template" at the top of the repository page to create a copy of this repository with a clean history.
2. Replace the placeholder library names with your own library name. The following files and paths will need to be adjusted:

    - Top-level `CMakeLists.txt` file
       - Project name specified for the `project()` call
    - Rename `MyProjectConfig.cmake.in` to match `${PROJECT_NAME}Config.cmake.in`
    - File paths in the `lib1/include/` directory
    - `lib1/CMakeLists.txt` file
       - `Lib1` target name
       - `lib1_export.h` filename in `set(EXPORT_HEADER ...)`
       - `LIB1_EXPORT` macro name in the `generate_export_header()` call
       - `EXPORT_NAME` in the `set_target_properties()` call
       - The `/lib1` include directory suffix in the `install(TARGETS ...)` call
    - `lib1/tests/CMakeLists.txt` file
       - `Lib1` and `Lib1Test` target names
       - `MyProject_Lib1_EXPORTS` compile definition
       - Any private source files you want to reuse from the library itself
    - File paths in the `lib2/include/` directory
    - `lib2/CMakeLists.txt` file
       - `Lib2` target name
       - `EXPORT_NAME` in the `set_target_properties()` call
       - The `/lib2` include directory suffix in the `install(TARGETS ...)` call
    - `lib2/tests/CMakeLists.txt` file
       - `Lib2` and `Lib2Test` target names
    - `tests/CMakeLists.txt` file
       - `Lib1` and `Lib2` target names

3. Update the `PUBLIC_HEADERS` lists and `target_sources()` calls in the respective libraries as you replace the dummy sources with your own files.
4. If you want to add additional linked libaries, use the `lib1/` template, use `lib2/` for header-only libraries.

## Additional Notes

- When adding dependencies via `find_package()` calls (not counting test dependencies), be sure to also add them to a `find_dependency()` call in `cmake/MyProjectConfig.cmake.in`. This ensures that client code can simply call `find_package(MyProject)` without having to worry about hidden dependencies.
- The version config file written by this project uses the `SameMajorVersion` setting. Depending on your needs, you may want to change this to `SameMinorVersion`, `AnyNewerVersion`, or `ExactVersion`.
- The compile definition and source file reuse in the `lib1/tests/` test is a hack to allow testing of non-exported symbols. The compile definition avoids warnings about importing local symbols on Windows. If you do not need to test internals, you can just link the library itself, as is done for the top-level `tests/` directory.
- Targets are named `${PROJECT_NAME}_<tgt>` to avoid name collisions with other libraries. This would lead to names like `MyProject::MyProject_Lib1`, so the `EXPORT_NAME` property is used to ensure the desired `MyProject::Lib1` name. Similarly, `OUTPUT_NAME` is used for `lib1` to control the name of the generated library file.
- Since the dummy library `lib1` already starts with "lib", the default library name would be `liblib1` on Unix systems. To avoid this, the `PREFIX` property is set to an empty string.

## Contributing

If you have any suggestions or improvements, please open an issue or pull request.

## License

This is free and unencumbered software released into the public domain.

For more information, please refer to the LICENSE file or <https://unlicense.org>.
