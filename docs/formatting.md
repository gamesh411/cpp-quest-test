# Code Formatting Guide

## Automatic Formatting with clang-format

This repository includes a `.clang-format` configuration that automatically formats your code to match the course style guide.

---

## Quick Start

### Format Your Code Before Submitting

```bash
# Format a single file
clang-format -i sessions/01_compilers_forge/starter/main.cpp

# Format all your session files
clang-format -i sessions/*/starter/*.cpp sessions/*/starter/*.h
```

**Always format before committing!** This ensures consistent style and helps you earn the code quality bonus.

⚠️ **Important:** GitHub Actions will automatically check your formatting when you create a PR. If your code isn't properly formatted, the PR will be rejected with instructions on how to fix it.

---

## Installation

### Check if Already Installed

```bash
clang-format --version
```

If you see a version number, you're good to go!

### Install clang-format

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install clang-format
```

**macOS:**
```bash
brew install clang-format
```

**Windows:**
- Download from [LLVM releases](https://releases.llvm.org/)
- Or via Chocolatey: `choco install llvm`

---

## IDE Integration (Recommended)

### VS Code

1. **Install Extension:**
   - Install "C/C++" extension by Microsoft

2. **Enable Format on Save:**
   - Create `.vscode/settings.json` in your repository:
   ```json
   {
       "editor.formatOnSave": true,
       "C_Cpp.clang_format_style": "file",
       "C_Cpp.clang_format_fallbackStyle": "none"
   }
   ```

3. **Manual Format:**
   - Right-click in editor → "Format Document"
   - Or: `Shift+Alt+F` (Windows/Linux) / `Shift+Option+F` (Mac)

### CLion

1. **Settings → Editor → Code Style → C/C++**
2. **Scheme:** Select "Project"
3. CLion automatically detects `.clang-format`
4. **Format:** `Ctrl+Alt+L` (Windows/Linux) / `Cmd+Option+L` (Mac)

### Vim/Neovim

**Manual formatting:**
```vim
:!clang-format -i %
```

**Auto-format on save (add to .vimrc):**
```vim
autocmd BufWritePre *.cpp,*.h :silent! execute '!clang-format -i ' . shellescape(expand('%'))
```

### Emacs

```elisp
;; Add to .emacs or init.el
(require 'clang-format)
(global-set-key (kbd "C-c f") 'clang-format-buffer)

;; Auto-format on save
(add-hook 'c++-mode-hook
          (lambda () (add-hook 'before-save-hook 'clang-format-buffer nil 'local)))
```

---

## Command Line Usage

### Format Files

```bash
# Format single file (modifies in-place)
clang-format -i main.cpp

# Format multiple files
clang-format -i file1.cpp file2.cpp file3.h

# Format all C++ files in directory
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i
```

### Check Formatting (Without Modifying)

```bash
# Check if file needs formatting
clang-format --dry-run --Werror main.cpp

# Show what would change
clang-format main.cpp | diff main.cpp -
```

### Format Specific Lines Only

```bash
# Format lines 10-20
clang-format -i --lines=10:20 main.cpp
```

---

## What Gets Formatted

clang-format automatically fixes:

✅ **Indentation** - Consistent 4-space indentation  
✅ **Braces** - K&R style (opening brace on same line)  
✅ **Spacing** - Around operators, after keywords  
✅ **Line breaks** - Long lines split at 100 characters  
✅ **Pointer alignment** - `int* ptr` (not `int *ptr`)  
✅ **Include order** - Sorted and grouped correctly  

---

## Example: Before and After

**Before formatting:**
```cpp
#include <string>
#include <iostream>
int main(){
std::string name="Aldric";
    int health=100;
  if(health>0){
std::cout<<"Alive"<<std::endl;
}
return 0;}
```

**After `clang-format -i main.cpp`:**
```cpp
#include <iostream>
#include <string>

int main() {
    std::string name = "Aldric";
    int health = 100;
    if (health > 0) {
        std::cout << "Alive" << std::endl;
    }
    return 0;
}
```

---

## Pre-Commit Hook (Advanced)

Automatically format code before every commit:

**Create `.git/hooks/pre-commit`:**
```bash
#!/bin/bash
# Format all staged C++ files

# Get list of staged C++ files
FILES=$(git diff --cached --name-only --diff-filter=ACM | grep -E '\.(cpp|h)$')

if [ -n "$FILES" ]; then
    echo "Formatting staged files..."
    for FILE in $FILES; do
        clang-format -i "$FILE"
        git add "$FILE"
    done
    echo "✓ Files formatted"
fi
```

**Make executable:**
```bash
chmod +x .git/hooks/pre-commit
```

Now your code is automatically formatted on every commit!

---

## Troubleshooting

### "clang-format: command not found"
- Install clang-format (see Installation section above)
- Check PATH: `echo $PATH`

### "Configuration file not found"
- Make sure you're in the repository root or subdirectory
- `.clang-format` should be in repository root
- Check: `ls -la .clang-format`

### "Format doesn't match style guide"
- Make sure you're using the repository's `.clang-format` file
- Check clang-format version: `clang-format --version` (should be 10+)
- Don't use `--style=` flag (it overrides the config file)

### "IDE not using .clang-format"
- Restart IDE after creating config file
- Check IDE settings point to "file" or "project" style
- Verify `.clang-format` is in repository root

---

## Tips

### ✅ Do:
- Format before every commit
- Use IDE integration for automatic formatting
- Run `clang-format -i` on all files before submitting PR
- Check formatting in CI (GitHub Actions does this automatically)

### ❌ Don't:
- Manually format code (let clang-format do it!)
- Mix formatted and unformatted code
- Modify `.clang-format` without instructor approval
- Commit unformatted code

---

## Checking Your Formatting

Before submitting a PR:

```bash
# Format all your code
find sessions -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Check for any remaining issues
git diff

# If changes look good, commit
git add .
git commit -m "Format code with clang-format"
```

### Automated Check on PR

When you create a pull request, GitHub Actions will automatically:

1. ✅ **Check formatting** - Verifies all code is properly formatted
2. ✅ **Check warnings** - Ensures zero compiler warnings
3. ✅ **Run tests** - Validates correctness

If formatting check fails, you'll see:
```
❌ CODE FORMATTING CHECK FAILED

Your code is not properly formatted.

To fix this, run:
  clang-format -i sessions/*/starter/*.cpp sessions/*/starter/*.h

Then commit and push the changes.
```

Simply follow the instructions, format your code, and push again!

---

## Benefits

Using clang-format:

✨ **Saves time** - No manual formatting  
✨ **Consistent style** - Everyone's code looks the same  
✨ **Fewer review comments** - Focus on logic, not style  
✨ **Bonus XP** - Clean code earns +20 XP  
✨ **Professional skill** - Used in industry  

---

## Questions?

- **Style questions:** See [style_guide.md](style_guide.md)
- **Setup issues:** Ask in Discord/Slack
- **IDE integration:** Check IDE documentation

---

**Remember:** Formatted code is happy code! ✨

Use `clang-format -i` before every commit and earn that code quality bonus!
