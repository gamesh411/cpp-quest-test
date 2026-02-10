# GitHub Actions CI/CD - What Gets Checked

When you create a pull request, GitHub Actions automatically runs three checks:

---

## ✅ Check 1: Code Formatting

**What it does:**
- Verifies all `.cpp` and `.h` files are formatted with clang-format
- Compares your code against the `.clang-format` configuration
- Shows exactly which files need formatting

**If it passes:**
```
✅ sessions/01_compilers_forge/starter/main.cpp
✅ sessions/02_memory_realms/starter/inventory.cpp

✅ All files are properly formatted!
```

**If it fails:**
```
❌ sessions/01_compilers_forge/starter/main.cpp needs formatting

Diff for sessions/01_compilers_forge/starter/main.cpp:
5c5
< int main(){
---
> int main() {

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
❌ CODE FORMATTING CHECK FAILED
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Your code is not properly formatted.

To fix this, run:
  clang-format -i sessions/*/starter/*.cpp sessions/*/starter/*.h

Then commit and push the changes.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**How to fix:**
```bash
# Format your code
clang-format -i sessions/01_compilers_forge/starter/main.cpp

# Commit and push
git add sessions/01_compilers_forge/starter/main.cpp
git commit -m "Fix code formatting"
git push
```

The PR will automatically re-run the checks!

---

## ✅ Check 2: Compiler Warnings

**What it does:**
- Compiles your code with `-Wall -Wextra -Werror`
- Checks for any compiler warnings
- Treats warnings as errors (forces clean code)

**If it passes:**
```
✅ No warnings - clean build!
```

**If it fails:**
```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
⚠️  COMPILER WARNINGS DETECTED
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Fix all warnings to earn the code quality bonus (+20 XP)

main.cpp:15:9: warning: unused variable 'x' [-Wunused-variable]
    int x = 42;
        ^
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**How to fix:**
- Read the warning message carefully
- Fix the issue in your code
- Common warnings:
  - Unused variables
  - Missing return statements
  - Type conversions
  - Uninitialized variables

---

## ✅ Check 3: Tests

**What it does:**
- Runs all automated tests with `ctest`
- Verifies your implementation is correct
- Shows detailed output if tests fail

**If it passes:**
```
Test project /path/to/build
    Start 1: Session01_Tests
1/1 Test #1: Session01_Tests ..................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

**If it fails:**
```
Test project /path/to/build
    Start 1: Session01_Tests
1/1 Test #1: Session01_Tests ..................***Failed    0.01 sec

The following tests FAILED:
	  1 - Session01_Tests (Failed)

Test output:
===============================================================================
test cases: 2 | 1 passed | 1 failed
assertions: 3 | 2 passed | 1 failed
```

**How to fix:**
- Run tests locally: `cd build && ctest --output-on-failure`
- Read the test output to understand what failed
- Fix your implementation
- Re-run tests until they pass

---

## Workflow

### 1. Create Pull Request

```bash
git push origin session-01
# Create PR on GitHub
```

### 2. GitHub Actions Runs Automatically

You'll see three checks:
- ⏳ Check Code Formatting (running...)
- ⏳ Build and Test (waiting...)
- ⏳ All checks (waiting...)

### 3. View Results

**All checks pass:**
```
✅ Check Code Formatting
✅ Build and Test
✅ All checks have passed
```

Your PR is ready for review! 🎉

**Some checks fail:**
```
❌ Check Code Formatting
⏳ Build and Test (skipped - formatting must pass first)
❌ Some checks were not successful
```

Click on "Details" to see what failed and how to fix it.

### 4. Fix Issues and Push Again

```bash
# Fix the issues
clang-format -i sessions/01_compilers_forge/starter/main.cpp

# Commit and push
git add .
git commit -m "Fix formatting"
git push origin session-01
```

GitHub Actions automatically re-runs all checks!

---

## Benefits

### For Students:
✅ **Immediate feedback** - Know if your code is correct before review  
✅ **Learn from errors** - Clear messages explain what's wrong  
✅ **No surprises** - Same checks run locally and on GitHub  
✅ **Professional workflow** - Experience real CI/CD  

### For Instructor:
✅ **Automated grading** - Correctness checked automatically  
✅ **Consistent standards** - Everyone's code meets same criteria  
✅ **Less review time** - Focus on design, not formatting/warnings  
✅ **Quality assurance** - No unformatted or buggy code merged  

---

## Running Checks Locally

Before pushing, run the same checks locally:

```bash
# 1. Check formatting
clang-format --dry-run --Werror sessions/01_compilers_forge/starter/main.cpp

# 2. Build and check warnings
cd build
cmake ..
make 2>&1 | grep -i warning

# 3. Run tests
ctest --output-on-failure
```

If all pass locally, they'll pass on GitHub!

---

## Troubleshooting

### "Check Code Formatting failed but I ran clang-format"

Make sure you:
- Formatted ALL files: `clang-format -i sessions/*/starter/*.cpp sessions/*/starter/*.h`
- Committed the formatted files: `git add . && git commit`
- Pushed to your repository: `git push`

### "Build and Test is skipped"

The build step only runs if formatting passes. Fix formatting first!

### "Tests pass locally but fail on GitHub"

- Make sure you pushed all files
- Check you're testing the same code
- Look at GitHub Actions logs for details

### "Can't see the error details"

On GitHub PR page:
1. Scroll to bottom where checks are listed
2. Click "Details" next to failed check
3. Expand the failed step to see full output

---

## Summary

Every PR automatically checks:

1. **Formatting** → Must use clang-format
2. **Warnings** → Must compile cleanly
3. **Tests** → Must pass all tests

Fix any failures, push again, and checks re-run automatically!

This ensures all submitted code meets quality standards. 🎯
