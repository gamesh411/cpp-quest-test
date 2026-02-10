# Git Workflow for C++ Quest

This guide explains how to work with the repository throughout the semester.

## One-Time Setup (Do This Once)

### 1. Create Your Repository from Template

1. Go to the course repository: `https://github.com/INSTRUCTOR_USERNAME/cpp-quest`
2. Click the **"Use this template"** button at the top right
3. Choose **"Create a new repository"**
4. Name it `cpp-quest` (or your preferred name)
5. Choose visibility:
   - **Private** (recommended for coursework)
   - Public (if you want to showcase your work)
6. Click **"Create repository"**

This creates your personal repository at `https://github.com/YOUR_USERNAME/cpp-quest`

### 2. Clone Your Repository

```bash
# Replace YOUR_USERNAME with your GitHub username
git clone https://github.com/YOUR_USERNAME/cpp-quest.git
cd cpp-quest
```

### 3. Test Your Setup

```bash
mkdir build
cd build
cmake ..
make
ctest
```

If everything works, you're ready to start!

---

## Weekly Workflow (Repeat for Each Session)

### Step 1: Start Fresh

Make sure you're on the main branch:

```bash
# Make sure you're on main branch
git checkout main

# Pull any updates you made from other machines
git pull origin main
```

### Step 2: Create Session Branch

Create a new branch for each session:

```bash
# For Session 1
git checkout -b session-01

# For Session 2
git checkout -b session-02

# etc.
```

**Why branches?** Keeps each session's work separate and makes code review easier.

### Step 3: Implement Your Quest

1. Navigate to the session folder:
   ```bash
   cd sessions/01_compilers_forge/
   ```

2. Read the quest requirements:
   ```bash
   cat README.md
   ```

3. Implement your solution in the `starter/` directory:
   ```bash
   # Edit the files
   vim starter/main.cpp
   # or use your preferred editor
   ```

4. Build and test frequently:
   ```bash
   cd ../../build  # Go to build directory
   cmake ..
   make
   ctest           # Run all tests
   
   # Or run specific test
   ./sessions/01_compilers_forge/tests/test_session01
   ```

### Step 4: Commit Your Work

Commit early and often:

```bash
# See what changed
git status

# Add your changes
git add sessions/01_compilers_forge/starter/

# Commit with descriptive message
git commit -m "Implement character stats display

- Add Character class with name, level, health, mana
- Implement formatted output with iostream
- All tests passing"

# Push to your fork
git push origin session-01
```

**Good commit messages:**
- Start with verb (Implement, Fix, Add, Refactor)
- Brief summary on first line
- Details in bullet points below

### Step 5: Create Pull Request

When you're ready for review:

1. Go to your fork on GitHub: `https://github.com/YOUR_USERNAME/cpp-quest`
2. You'll see a banner: "session-01 had recent pushes" with **"Compare & pull request"** button
3. Click it
4. Fill in the PR template:
   - **Title**: "Session 01 - Your Name"
   - **Description**: 
     - What you implemented
     - Any challenges you faced
     - Questions for reviewer
5. Click **"Create pull request"**

The instructor will review your code and provide feedback!

### Step 6: Address Feedback (if needed)

If the instructor requests changes:

```bash
# Make the changes in your session branch
git checkout session-01

# Edit files
vim sessions/01_compilers_forge/starter/main.cpp

# Commit changes
git add sessions/01_compilers_forge/starter/
git commit -m "Address review feedback: improve error handling"

# Push to same branch
git push origin session-01
```

The pull request automatically updates!

### Step 7: Move to Next Session

Once your PR is approved:

```bash
# Go back to main
git checkout main

# Merge your work
git merge session-01

# Ready for next session!
```

---

## Common Scenarios

### Scenario 1: I Made a Mistake in My Commit

**Before pushing:**
```bash
# Undo last commit, keep changes
git reset --soft HEAD~1

# Make corrections
# Then commit again
```

**After pushing:**
```bash
# Make corrections
git add .
git commit -m "Fix: correct mistake in previous commit"
git push origin session-01
```

### Scenario 2: I Want to Start Over

```bash
# Discard all local changes
git checkout main
git branch -D session-01  # Delete branch
git checkout -b session-01  # Start fresh
```

### Scenario 3: Merge Conflicts

If you get conflicts when merging upstream:

```bash
git fetch upstream
git merge upstream/main

# If conflicts occur:
# 1. Open conflicted files (Git will mark them)
# 2. Resolve conflicts manually
# 3. Remove conflict markers (<<<<, ====, >>>>)
# 4. Add resolved files
git add .
git commit -m "Merge upstream changes"
```

### Scenario 4: I Forgot to Create a Branch

```bash
# You're on main with uncommitted changes
# Create branch and move changes to it
git checkout -b session-01

# Your changes come with you!
```

### Scenario 5: Check My Progress

```bash
# See all branches
git branch -a

# See commit history
git log --oneline

# See what changed in a file
git diff sessions/01_compilers_forge/starter/main.cpp
```

---

## Testing Your Code

### Run All Tests
```bash
cd build
ctest
```

### Run Specific Session Tests
```bash
cd build
ctest -R session01  # Only Session 1 tests
```

### Run Tests with Verbose Output
```bash
cd build
ctest --output-on-failure
```

### Run Tests with Valgrind (Memory Check)
```bash
cd build
ctest -T memcheck
```

---

## Best Practices

### ✅ Do:
- Commit frequently with clear messages
- Test before committing
- Push to your fork regularly (backup!)
- Ask questions in PR description
- Help classmates (without giving answers)

### ❌ Don't:
- Commit compiled files (*.o, executables)
- Push directly to main (use branches)
- Copy code without understanding
- Wait until deadline to start
- Forget to pull upstream updates

---

## Quick Reference

```bash
# Get new materials
git fetch upstream && git merge upstream/main

# Start new session
git checkout -b session-XX

# Check status
git status

# Add and commit
git add sessions/XX_*/starter/
git commit -m "Descriptive message"

# Push to your fork
git push origin session-XX

# Run tests
cd build && ctest

# Switch branches
git checkout main
git checkout session-XX
```

---

## Getting Help

### Git Issues
- [Git Documentation](https://git-scm.com/doc)
- [GitHub Guides](https://guides.github.com/)
- Ask in Discord/Slack
- Office hours

### Build/Test Issues
- Check CMake output for errors
- Ensure you're in `build/` directory
- Try `rm -rf build && mkdir build` (clean rebuild)
- Check compiler version: `g++ --version`

### Code Issues
- Read test output carefully
- Use debugger: `gdb ./test_session01`
- Add print statements
- Ask in office hours

---

## Troubleshooting

### "Permission denied" when pushing
- Check you're pushing to your fork, not upstream
- Verify GitHub authentication (SSH keys or token)

### "Merge conflict" when pulling upstream
- See "Scenario 3: Merge Conflicts" above
- Or ask for help!

### Tests fail after pulling upstream
- Rebuild: `cd build && cmake .. && make`
- Check if you modified test files (don't!)

### "Branch already exists"
- Delete old branch: `git branch -D session-XX`
- Or use different name: `git checkout -b session-XX-v2`

---

## Advanced: Working on Multiple Machines

If you work on both laptop and lab computer:

**On Machine 1:**
```bash
git push origin session-01
```

**On Machine 2:**
```bash
git fetch origin
git checkout session-01
# Continue working
```

Always push before switching machines!

---

## Summary

1. **Fork** → Your personal copy
2. **Clone** → Local copy on your computer
3. **Upstream** → Get new quests from instructor
4. **Branch** → Separate workspace for each session
5. **Commit** → Save your progress
6. **Push** → Backup to GitHub
7. **Pull Request** → Submit for review

**Remember:** Git is a valuable skill! You're learning professional development workflow while mastering C++.

---

Need help? Don't hesitate to ask! Everyone struggles with Git at first. 🚀
