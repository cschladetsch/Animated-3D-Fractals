# Installation Guide

This guide covers building and installing the Animated 3D Fractals project from source.

## System Requirements

### Minimum Requirements
- **OS**: Linux (Ubuntu 18.04+), macOS (10.14+), or Windows 10+
- **Compiler**: GCC 7+, Clang 7+, or MSVC 2017+
- **CMake**: Version 3.16 or later
- **Graphics**: OpenGL 3.0+ compatible GPU
- **Memory**: 4GB RAM minimum, 8GB+ recommended
- **Storage**: 500MB for source + build files

### Recommended Requirements
- **GPU**: Dedicated graphics card with 2GB+ VRAM
- **CPU**: Multi-core processor (4+ cores recommended)
- **Memory**: 16GB+ RAM for large fractal renderings

## Prerequisites

### Ubuntu/Debian
```bash
# Essential build tools
sudo apt update
sudo apt install build-essential cmake git

# Graphics and window system
sudo apt install libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev
sudo apt install libxcursor-dev libxi-dev libxext-dev

# Optional: Additional development tools
sudo apt install ninja-build ccache
```

### CentOS/RHEL/Fedora
```bash
# Essential build tools
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake git

# Graphics libraries
sudo dnf install mesa-libGL-devel libX11-devel libXrandr-devel
sudo dnf install libXinerama-devel libXcursor-devel libXi-devel
```

### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake git
```

### Windows
1. Install **Visual Studio 2019** or later with C++ development tools
2. Install **Git for Windows**  
3. Install **CMake** (3.16+)
4. Ensure OpenGL drivers are up to date

## Building from Source

### 1. Clone the Repository
```bash
git clone https://github.com/cschladetsch/Animated-3D-Fractals.git
cd Animated-3D-Fractals
```

### 2. Initialize Submodules
```bash
# Download SDL2 2.32.8 and Google Test
git submodule update --init --recursive
```

### 3. Configure Build
```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Optional: Configure with specific options
cmake .. -DCMAKE_BUILD_TYPE=Release -GNinja
```

### 4. Build the Project
```bash
# Using make (default)
make -j$(nproc)

# Or using ninja (if configured)
ninja

# Or using CMake (cross-platform)
cmake --build . --parallel
```

### 5. Verify Installation
```bash
# Run unit tests
./unit_tests

# Test SDL2 integration  
./sdl2-test

# Quick fractal test (may show shader errors - this is expected)
./boxplorer2 ../cfgs/mandelbulb/default.cfg
```

## Build Options

### CMake Configuration Options

```bash
# Release build (optimized)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Debug build (with debug symbols)
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Use Ninja generator (faster builds)
cmake .. -GNinja

# Specify compiler
cmake .. -DCMAKE_CXX_COMPILER=clang++

# Custom install prefix
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
```

### Advanced Build Options

```bash
# Enable additional warnings
cmake .. -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic"

# Use specific SDL2 version
cmake .. -DSDL2_ROOT=/path/to/sdl2

# Disable unit tests
cmake .. -DENABLE_TESTING=OFF
```

## Platform-Specific Notes

### Linux
- **Wayland**: Should work with XWayland compatibility layer
- **X11**: Native support included
- **Graphics Drivers**: Ensure proprietary NVIDIA/AMD drivers are installed for best performance

### macOS
- **M1/M2 Macs**: Build natively supports Apple Silicon
- **OpenGL**: Uses system OpenGL framework
- **Retina Displays**: Automatically handles high-DPI scaling

### Windows  
- **Visual Studio**: Supports VS 2019, 2022
- **MinGW**: Should work but not officially supported
- **Graphics**: Ensure latest GPU drivers are installed

### WSL2 (Windows Subsystem for Linux)
```bash
# Enable X11 forwarding
export DISPLAY=:0

# Or use WSLg (Windows 11)
# No additional configuration needed

# Test graphics
./sdl2-test
```

## Troubleshooting

### Common Build Issues

**CMake Version Too Old**
```bash
# Ubuntu: Install from CMake website or use snap
sudo snap install cmake --classic

# Or build from source
wget https://cmake.org/files/v3.28/cmake-3.28.0.tar.gz
```

**Missing OpenGL Headers**
```bash
# Ubuntu/Debian
sudo apt install mesa-common-dev

# CentOS/RHEL  
sudo dnf install mesa-libGL-devel
```

**Submodule Init Fails**
```bash
# Force update
git submodule update --init --recursive --force

# Or clone with submodules initially
git clone --recursive https://github.com/cschladetsch/Animated-3D-Fractals.git
```

### Runtime Issues

**SDL2 Initialization Fails**
```bash
# Check graphics drivers
glxinfo | grep "direct rendering"

# Test basic OpenGL
glxgears
```

**Shader Compilation Errors**
- This is expected for some fractal configurations
- Try different config files in `cfgs/` directory
- Verify GPU supports required OpenGL version

**Performance Issues**
- Start with lower iteration counts
- Reduce window resolution
- Check GPU utilization with `nvidia-smi` or similar
- Ensure using discrete GPU on laptops

### Getting Help

1. **Check logs**: Look for error messages in terminal output
2. **Verify graphics**: Run `./sdl2-test` to test SDL2/OpenGL
3. **Test configs**: Try different fractal configurations
4. **Update drivers**: Ensure latest graphics drivers are installed
5. **Create issue**: Report bugs with system info and error logs

## Performance Optimization

### Compile-Time Optimizations
```bash
# Maximum optimization
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -march=native"

# Link-time optimization
cmake .. -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON
```

### Runtime Performance Tips
- Use dedicated GPU on multi-GPU systems
- Close other graphics-intensive applications
- Increase iteration count gradually for quality vs performance balance
- Use fullscreen mode for better performance

## Development Setup

### Code Development
```bash
# Debug build with symbols
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Enable address sanitizer
cmake .. -DCMAKE_CXX_FLAGS="-fsanitize=address -g"

# Clang static analyzer
scan-build cmake ..
scan-build make
```

### Testing
```bash
# Run all tests
make test

# Run with verbose output
ctest --verbose

# Run specific test
./unit_tests --gtest_filter="InterpolateTest.*"
```

This completes the installation guide. The project should now be ready to create stunning 3D fractal animations!