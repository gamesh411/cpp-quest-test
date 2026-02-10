# Setup Guide for C++ Quest

This guide will help you set up your development environment for the course.

---

## Required Software

### 1. C++ Compiler

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential g++

# Verify installation
g++ --version  # Should be 10.0 or higher
```

**macOS:**
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Or install via Homebrew
brew install gcc

# Verify
g++ --version
```

**Windows:**
- Install [MinGW-w64](https://www.mingw-w64.org/) or
- Install [Visual Studio 2022](https://visualstudio.microsoft.com/) with C++ workload
- Or use [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install) (recommended)

### 2. CMake

**Linux:**
```bash
sudo apt-get install cmake

# Verify
cmake --version  # Should be 3.14 or higher
```

**macOS:**
```bash
brew install cmake
```

**Windows:**
- Download from [cmake.org](https://cmake.org/download/)
- Or via Chocolatey: `choco install cmake`

### 3. Git

**Linux:**
```bash
sudo apt-get install git
```

**macOS:**
```bash
brew install git
# Or comes with Xcode Command Line Tools
```

**Windows:**
- Download from [git-scm.com](https://git-scm.com/)
- Or via Chocolatey: `choco install git`

**Configure Git:**
```bash
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

### 4. Catch2 (Testing Framework)

**Linux:**
```bash
sudo apt-get install catch2
```

**macOS:**
```bash
brew install catch2
```

**Windows/Manual Installation:**
```bash
# Clone Catch2
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -B build -S . -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install
```

---

## Recommended Tools

### Text Editors / IDEs

**VS Code (Recommended for beginners)**
- Download: [code.visualstudio.com](https://code.visualstudio.com/)
- Install extensions:
  - C/C++ (Microsoft)
  - CMake Tools
  - GitLens

**CLion (Professional IDE)**
- Download: [jetbrains.com/clion](https://www.jetbrains.com/clion/)
- Free for students with .edu email

**Vim/Neovim (For the brave)**
- Install plugins: coc.nvim, vim-cmake, etc.

**Other Options:**
- Visual Studio (Windows)
- Qt Creator
- Code::Blocks

---

## Project Setup

### 1. Create Repository from Template

```bash
# On GitHub: Click "Use this template" → "Create a new repository"
# Name it cpp-quest, choose Private visibility
# Then clone:
git clone https://github.com/YOUR_USERNAME/cpp-quest.git
cd cpp-quest
```

### 2. Add Upstream Remote

```bash
git remote add upstream https://github.com/INSTRUCTOR_USERNAME/cpp-quest.git
git remote -v  # Verify
```

### 3. Build the Project

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build
make

# Run tests
ctest
```

**Expected output:**
```
Test project /path/to/cpp-quest/build
    Start 1: Session01_Tests
1/1 Test #1: Session01_Tests ..................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

---

## IDE Configuration

### VS Code

1. **Open project:**
   ```bash
   cd cpp-quest
   code .
   ```

2. **Configure CMake:**
   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Type "CMake: Configure"
   - Select your compiler

3. **Build:**
   - Press `F7` or use CMake Tools panel

4. **Run tests:**
   - Press `Ctrl+Shift+P`
   - Type "CMake: Run Tests"

5. **Recommended settings** (`.vscode/settings.json`):
   ```json
   {
       "C_Cpp.default.cppStandard": "c++20",
       "C_Cpp.default.compilerPath": "/usr/bin/g++",
       "cmake.configureOnOpen": true,
       "files.associations": {
           "*.h": "cpp",
           "*.cpp": "cpp"
       }
   }
   ```

### CLion

1. **Open project:**
   - File → Open → Select `cpp-quest` directory

2. **CMake auto-configures**
   - CLion detects CMakeLists.txt automatically

3. **Build:**
   - Click hammer icon or `Ctrl+F9`

4. **Run tests:**
   - Right-click on test file → Run

### Command Line (Any Editor)

```bash
# Build
cd build
cmake ..
make

# Run specific executable
./sessions/01_compilers_forge/starter/character_display

# Run tests
ctest

# Run tests with verbose output
ctest --output-on-failure

# Clean build
cd ..
rm -rf build
mkdir build
cd build
cmake ..
make
```

---

## Troubleshooting

### "CMake not found"
```bash
# Check if installed
which cmake

# If not, install (see above)
```

### "Compiler not found"
```bash
# Check if installed
which g++

# If not, install build-essential (Linux) or Xcode (Mac)
```

### "Catch2 not found"
```bash
# Install Catch2 (see above)
# Or tests will be skipped (you can still build executables)
```

### "Permission denied" errors
```bash
# On Linux/Mac, you might need sudo for installation
sudo apt-get install ...

# For project files, check ownership
ls -la
```

### Build errors after pulling updates
```bash
# Clean rebuild
rm -rf build
mkdir build
cd build
cmake ..
make
```

### Git authentication issues
```bash
# Use SSH keys (recommended)
ssh-keygen -t ed25519 -C "your.email@example.com"
# Add to GitHub: Settings → SSH Keys

# Or use HTTPS with token
# GitHub → Settings → Developer settings → Personal access tokens
```

---

## Verification

Run this checklist to verify your setup:

```bash
# 1. Check compiler
g++ --version
# Should show version 10.0 or higher

# 2. Check CMake
cmake --version
# Should show version 3.14 or higher

# 3. Check Git
git --version

# 4. Clone and build
git clone https://github.com/YOUR_USERNAME/cpp-quest.git
cd cpp-quest
mkdir build && cd build
cmake ..
make
ctest

# If all tests pass, you're ready! ✅
```

---

## Optional Tools

### Debugger (GDB)
```bash
# Install
sudo apt-get install gdb

# Use
gdb ./program
(gdb) break main
(gdb) run
(gdb) next
(gdb) print variable
```

### Memory Checker (Valgrind)
```bash
# Install
sudo apt-get install valgrind

# Use
valgrind --leak-check=full ./program
```

### Code Formatter (clang-format)
```bash
# Install
sudo apt-get install clang-format

# Use
clang-format -i main.cpp
```

### Static Analyzer (cppcheck)
```bash
# Install
sudo apt-get install cppcheck

# Use
cppcheck --enable=all main.cpp
```

---

## Getting Help

### Common Issues

**"fatal: not a git repository"**
- You're not in the project directory
- Run `cd cpp-quest` first

**"No such file or directory"**
- Check you're in the right directory
- Use `pwd` to see current directory
- Use `ls` to list files

**"undefined reference to..."**
- Linking error - check CMakeLists.txt
- Make sure all source files are included

**Compiler warnings**
- Read them carefully - they often point to real bugs
- Fix all warnings before submitting

### Where to Ask

1. **Course Discord/Slack** - Quick questions
2. **Office Hours** - Detailed help
3. **GitHub Issues** - Problems with starter code
4. **Stack Overflow** - General C++ questions

---

## Next Steps

Once your environment is set up:

1. Read [Git Workflow Guide](git_workflow.md)
2. Review [Style Guide](style_guide.md)
3. Start [Session 1: The Compiler's Forge](../sessions/01_compilers_forge/README.md)

---

**Setup complete?** Time to begin your quest! 🚀
