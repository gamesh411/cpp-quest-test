# C++ Quest: Dungeon Crawler

A text-based dungeon crawler game built with C++ to showcase what you'll learn in the C++ Quest course!

## Game Features

### 🗺️ Dungeon Exploration
- Navigate through 7 interconnected locations
- Each location has unique descriptions
- Discover hidden treasures and face dangerous enemies

### ⚔️ Combat System
- Fight enemies or flee from battle
- Strategic combat with attack and defense
- Boss battle against the Ancient Dragon!

### 💎 Loot & Items
- Find treasure chests in various locations
- Enemies drop loot when defeated
- Items provide stat bonuses:
  - **Health Bonus**: Increases max HP
  - **Attack Bonus**: Increases damage
  - **Gold**: Currency for your adventure

### 📊 Character Progression
- Start with basic stats
- Improve through equipment
- Track your gold and inventory

### 💾 Save/Load System
- Save your progress anytime
- Load and continue your adventure

## Building the Game

### Prerequisites

Complete the sessions to unlock features:
- **Session 2** for inventory system
- **Session 3** for save/load
- **Session 4** for weapon system

### Build Steps

```bash
# From cpp-quest directory
# First, copy your solutions to starter files
./copy_solutions_to_starter.sh

# Build the game
cmake -B build -S .
cmake --build build --target game_world

# Run the game
./build/game_world/game_world

# After playing, restore starter files
./restore_starter_files.sh
```

### Testing Your Code

The game automatically detects which sessions you've completed:
- Session files in `starter/` directories are used
- If not completed, fallback implementations are used
- Check the startup message to see which sessions are integrated

### Commands

**Movement:**
- `n` or `north` - Move north
- `s` or `south` - Move south
- `e` or `east` - Move east
- `w` or `west` - Move west

**Actions:**
- `look` - Examine current location
- `fight` - Fight enemy in current location
- `flee` - Run from combat (takes damage)
- `loot` - Take treasure from current location

**Character:**
- `stats` - View your character stats
- `inv` - View inventory

**Game:**
- `save` - Save game
- `load` - Load game
- `quit` - Exit game

## Dungeon Map

```
                    [Dragon's Lair]
                           |
                    [Treasure Chamber]
                           |
                     [Guard Room]
                           |
    [Storage] --- [Grand Hall] --- [Armory]
                       |
                  [Entrance]
```

## Locations

1. **Dungeon Entrance** - Starting point, safe zone
2. **Grand Hall** - Central hub with a Goblin Scout
3. **Old Armory** - Find weapons and armor
4. **Storage Room** - Potions and gold
5. **Guard Room** - Skeleton Warrior guards the way
6. **Treasure Chamber** - Valuable magical items
7. **Dragon's Lair** - Face the Ancient Dragon (BOSS)

## Enemies

### Goblin Scout
- HP: 30
- Attack: 8
- Drops: Rusty Dagger (+2 ATK)

### Skeleton Warrior
- HP: 50
- Attack: 12
- Drops: Steel Sword (+8 ATK)

### Ancient Dragon (BOSS)
- HP: 150
- Attack: 25
- Drops: Dragon Scale Armor (+50 HP, +10 ATK), Dragon Hoard (5000 gold)

## Items

### Weapons
- **Rusty Dagger**: +2 ATK
- **Iron Sword**: +5 ATK
- **Steel Sword**: +8 ATK

### Armor
- **Leather Armor**: +20 HP
- **Dragon Scale Armor**: +50 HP, +10 ATK

### Consumables
- **Health Potion**: +30 HP
- **Magic Amulet**: +30 HP, +5 ATK

### Treasure
- **Gold Coins**: 100 gold
- **Gold Pile**: 500 gold
- **Dragon Hoard**: 5000 gold

## Strategy Tips

1. **Explore thoroughly** - Collect items before fighting
2. **Gear up first** - Visit Armory and Storage before combat
3. **Know when to flee** - Fleeing is better than dying
4. **Save often** - Don't lose your progress
5. **Prepare for the boss** - Collect all items before facing the Dragon

## Session Integration

This game uses **your actual code** from completed sessions! Features unlock as you progress:

### ✅ Integrated Sessions

**Session 2: Memory Realms**
- `Item` class with name and value
- `Inventory` class with dynamic array management
- See your memory management in action!

**Session 3: Stream of Knowledge**
- `GameState` class for character data
- `saveToFile()` / `loadFromFile()` with streams
- See your file I/O working in a real game!

**Session 4: Guardian Spirits**
- `Weapon` class with RAII and move semantics
- `WeaponManager` with smart pointers
- See your weapons equipped and used in combat!

**Session 5: Crafting Classes** (Future)
- `Spell` and `SpellBook` classes
- Magic system for combat

### 🔄 Progressive Enhancement

The game uses conditional compilation:
- If you haven't completed a session, fallback code is used
- As you complete sessions, features unlock automatically
- Your actual student code runs in the game!

### 📚 What You'll Learn

By completing sessions, you'll see:
- **Session 2**: Dynamic memory management with raw pointers
- **Session 3**: File I/O with streams and error handling
- **Session 4**: RAII, smart pointers, and move semantics
- **Session 5**: Class design and encapsulation
- **Session 8**: Polymorphism and virtual functions (coming soon)
- **Session 11**: STL containers and algorithms (coming soon)

## Winning the Game

Defeat the Ancient Dragon in the Dragon's Lair to win!

Your final stats will be displayed, showing:
- Total gold collected
- Final health and attack
- Items acquired

## Game Over

If your health reaches 0, the game ends. You can:
- Load your last save
- Start a new game

## Future Enhancements

As you progress through C++ Quest, you could add:
- More complex combat (Session 8: Polymorphism)
- NPC merchants (Session 9: Multiple inheritance)
- Spell system (Session 5: Classes)
- Quest system (Session 11: STL)
- Custom inventory container (Session 12: Custom containers)

## Have Fun!

This game is a preview of what you can build with C++. As you complete more sessions, you'll understand how every part works and be able to create even more complex games!

Good luck, adventurer! 🗡️🐉
