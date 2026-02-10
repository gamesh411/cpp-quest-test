# C++ Quest: The Codex of Modern Magic 🧙‍♂️

Welcome, apprentice mage! You are about to embark on a 13-session journey to master the ancient art of C++ programming. Each session will teach you new magical techniques (C++ concepts) that unlock powerful abilities in your quest to build a complete RPG game engine.

## 🎮 What You'll Build

By the end of this quest, you will have created a fully functional text-based RPG game engine featuring:
- Character creation and management
- Inventory and item systems
- Spell casting mechanics
- Combat system with polymorphic enemies
- Quest and achievement tracking
- Save/load functionality
- And much more!

## 📚 Course Structure

| Session | Quest Name | C++ Magic Learned | What You'll Build |
|---------|------------|-------------------|-------------------|
| 1 | The Compiler's Forge | Compilation, environment | Character stats display |
| 2 | Memory Realms | Pointers, references | Dynamic inventory |
| 3 | Stream of Knowledge | I/O, argument passing | Save/load system |
| 4 | Guardian Spirits | RAII, smart pointers | Resource management |
| 5 | Crafting Classes | Classes, encapsulation | Spell system |
| 6 | Hidden Implementation | Pimpl idiom | Game engine core |
| 7 | Bloodlines | Inheritance | Entity hierarchy |
| 8 | Shapeshifting | Polymorphism | Combat system |
| 9 | Ancient Powers | Advanced inheritance | Complex NPCs |
| 10 | Template Codex | Templates | Generic systems |
| 11 | Standard Library | STL, algorithms | Quest system |
| 12 | Forging Artifacts | Custom containers | Priority queues |
| 13 | The Final Quest | Integration | Complete game! |

## 🎯 Progression System

### Experience Points (XP)
- **Core Quest**: 100 XP (required)
- **Side Quests**: 50 XP each (optional, for extra challenge)
- **Code Quality Bonus**: +20 XP (clean code, no warnings)
- **Achievements**: 10-30 XP each
- **Helping Peers**: 15 XP (verified by instructor)

### Levels
- **Level 1-3**: Apprentice (Sessions 1-4)
- **Level 4-6**: Adept (Sessions 5-8)
- **Level 7-9**: Expert (Sessions 9-11)
- **Level 10-12**: Master (Sessions 12-13)
- **Level 13**: Archmage (Course completion)

### Achievements 🏆
Unlock badges for mastery:
- 🎯 **Pointer Sage** - Master pointers and references
- 🛡️ **RAII Guardian** - Perfect resource management
- 🦎 **Shapeshifter Supreme** - Polymorphism mastery
- 📜 **Template Wizard** - Advanced generic programming
- ⚗️ **STL Alchemist** - Masterful library usage
- ✨ **Clean Coder** - Zero compiler warnings
- 🤝 **Helpful Mentor** - Help 5 classmates

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++ 10+ or clang++ 12+)
- Git
- CMake 3.14+
- Text editor or IDE (VS Code, CLion, etc.)

### Setup Instructions

1. **Create your repository from template**
   - Click the "Use this template" button at the top right
   - Choose "Create a new repository"
   - Name it `cpp-quest` (or your preferred name)
   - Choose visibility (Private recommended for coursework)
   - Click "Create repository"

2. **Clone your repository**
   ```bash
   git clone https://github.com/YOUR_USERNAME/cpp-quest.git
   cd cpp-quest
   ```

3. **Build and test**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ctest
   ```

5. **Read the detailed workflow**
   - See [docs/git_workflow.md](docs/git_workflow.md) for complete instructions

## 📖 How to Complete Each Quest

### 0. Format Your Code (Important!)
```bash
# Before committing, format your code
clang-format -i sessions/01_compilers_forge/starter/main.cpp
```
See [Formatting Guide](docs/formatting.md) for IDE integration.

### 1. Get New Quest Materials
```bash
git fetch upstream
git merge upstream/main
```

### 2. Create Session Branch
```bash
git checkout -b session-01
```

### 3. Implement Your Solution
- Navigate to `sessions/01_compilers_forge/starter/`
- Read the `README.md` for quest requirements
- Implement your solution
- Run tests frequently: `cd build && ctest`

### 4. Submit for Review
```bash
git add sessions/01_compilers_forge/starter/
git commit -m "Complete Session 1 core quest"
git push origin session-01
```

### 5. Create Pull Request
- Go to your repository on GitHub
- Click "Pull Request"
- Base: instructor repo, Compare: your session branch
- Title: "Session 01 - Your Name"
- Submit!

**Note:** GitHub Actions will automatically check your code for:
- ✅ Proper formatting (clang-format)
- ✅ Zero compiler warnings
- ✅ All tests passing

See [CI Checks Guide](docs/ci_checks.md) for details.

## 📊 Assessment

Each quest is graded on:
- **Correctness (40%)**: All tests pass
- **Code Quality (30%)**: Style, warnings, documentation
- **Design (20%)**: Proper use of C++ concepts
- **Creativity (10%)**: Side quests, extra features

## 🆘 Getting Help

- **Office Hours**: [Schedule TBD]
- **Discord/Slack**: [Link TBD]
- **GitHub Issues**: For technical problems with starter code
- **Pair Programming**: In-class sessions every week

## 📜 Code of Honor

- Your repository is your personal workspace - experiment freely!
- Collaboration is encouraged, but write your own code
- Help others learn, don't just give answers
- Cite any external resources you use

## 🎓 Learning Resources

- [C++ Reference](https://en.cppreference.com/)
- [Course Notes](docs/course_notes.md)
- [Style Guide](docs/style_guide.md)
- [Formatting Guide](docs/formatting.md) - **Use clang-format for automatic formatting!**
- [Common Pitfalls](docs/common_pitfalls.md)

## 🏆 Leaderboard (Optional)

Want to see how you rank? Opt-in to the public leaderboard:
- [Leaderboard Link TBD]
- Tracks XP, level, and achievements
- Completely optional - focus on your own growth!

## 📝 License

This course material is for educational use. Your implementations are your own work.

---

**Ready to begin your journey?** Start with [Session 1: The Compiler's Forge](sessions/01_compilers_forge/README.md)!

May your code compile without warnings and your pointers never dangle! ✨
