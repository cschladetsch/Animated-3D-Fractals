# Changelog

All notable changes to the Animated 3D Fractals project are documented here.

## [2.0.0] - 2024-08-10

### Major Updates

#### Modern Build System
- **Migrated to modern CMake** (3.16+) with C++17 standard
- **Cross-platform build support** for Linux, macOS, and Windows
- **Dependency management** via git submodules
- **Parallel build support** with optimized compilation

#### SDL2 Integration
- **Upgraded to SDL2 2.32.8** (latest stable release)
- **Enhanced cross-platform support** with better graphics drivers compatibility
- **Improved input handling** for mouse and keyboard
- **Better window management** and display detection
- **WSL2 and Wayland support** for modern Linux environments

#### Testing Infrastructure
- **Comprehensive unit testing** with Google Test framework
- **27 unit tests** covering core mathematical functions
- **Automated testing** for interpolation, quaternion operations, and camera functions
- **Continuous integration ready** build system

### Project Structure Improvements

#### Code Organization
- **Separated source and headers** (.cpp files in `source/`, .h files in `include/`)
- **External dependencies** properly managed in `External/` directory
- **Test suite** organized in dedicated `tests/` directory
- **Modern C++ practices** with const correctness and RAII

#### Build Artifacts
- **Clean build separation** with dedicated `build/` directory  
- **Multiple executable targets**: main application, utilities, and tests
- **Static library architecture** for modular compilation
- **Debug and release configurations**

### Documentation Overhaul

#### User Documentation
- **Comprehensive README** with feature overview and quick start guide
- **Interactive controls reference** with detailed key mappings
- **Installation guide** with platform-specific instructions
- **Troubleshooting section** for common issues

#### Developer Documentation  
- **CMake configuration** with inline comments
- **Code structure** explanation and conventions
- **Testing procedures** and framework usage
- **Performance optimization** guidelines

### Enhanced Features

#### Interactive Controls
- **Full 6DOF camera movement** through fractal space
- **Real-time parameter adjustment** with immediate visual feedback
- **Advanced keyframe system** for smooth animation creation
- **Mouse-look camera control** similar to first-person games

#### Rendering Capabilities
- **Multiple fractal types**: Mandelbulb, Menger Sponge, Mandelbox, and more
- **Stereoscopic 3D output** with various viewing modes
- **High-quality rendering** with ambient occlusion and effects
- **Animation export** for creating video sequences

#### Quality Assurance
- **Memory safety improvements** with modern C++ practices
- **Error handling enhancements** for better user experience
- **Performance optimizations** for real-time exploration
- **Cross-platform compatibility** testing

### Technical Improvements

#### Dependencies
- **SDL2 2.32.8**: Latest stable version with bug fixes and performance improvements
- **Google Test**: Industry-standard testing framework
- **Modern OpenGL**: Enhanced shader pipeline support
- **Automated dependency management** via git submodules

#### Code Quality
- **C++17 standard**: Modern language features and performance
- **Const correctness**: Improved memory safety and optimization
- **RAII patterns**: Better resource management
- **Static analysis ready**: Compatible with modern code analysis tools

### Performance
- **Optimized compilation** with release builds
- **Parallel processing** support where applicable
- **GPU acceleration** with modern OpenGL pipeline
- **Memory usage optimization** for large fractal renders

### Bug Fixes
- **Shader compilation**: Improved error reporting and handling
- **Cross-platform issues**: Better compatibility across different systems
- **Memory leaks**: Fixed with modern C++ resource management
- **Build system**: Resolved dependency and linking issues

### User Experience
- **Streamlined installation**: One-command build process
- **Better error messages**: Clear feedback for common issues
- **Performance monitoring**: Built-in performance indicators
- **Intuitive controls**: Improved mouse and keyboard handling

---

## [1.02] - Historical Baseline

### Original Features (by Marius)
- Basic 3D fractal rendering with OpenGL
- Keyframe-based animation system
- Multiple fractal types and configurations
- SDL 1.2 integration for cross-platform support
- Command-line rendering options
- Stereoscopic output modes

### Legacy Components Preserved
- Core mathematical algorithms for fractal generation
- GLSL shader system for GPU acceleration  
- Configuration file format and fractal presets
- Animation and keyframe interpolation logic
- Rendering pipeline architecture

---

## Migration Notes

### Breaking Changes
- **CMake required**: Legacy Makefiles still available but CMake recommended
- **C++17 compiler**: Older compilers no longer supported
- **SDL2 dependency**: Upgraded from SDL 1.2 (automatic via submodule)

### Compatibility
- **Configuration files**: Fully backward compatible with existing .cfg files
- **Fractal presets**: All existing fractal configurations preserved
- **Rendering options**: All command-line options maintained
- **Controls**: Enhanced but backward compatible key bindings

### Upgrade Path
1. Clone repository with submodules
2. Use CMake build system (recommended)
3. All existing configurations and fractals work unchanged
4. Enhanced features available immediately

This modernization preserves all the original fractal generation capabilities while adding robust build infrastructure, comprehensive testing, and enhanced user experience for creating the stunning 3D fractal animations showcased in videos like the one you referenced!