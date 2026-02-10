#pragma once

#include "session_config.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

// Session integrations
#ifdef SESSION_02_AVAILABLE
#    include "../sessions/02_memory_realms/starter/inventory.h"
#endif

#ifdef SESSION_03_AVAILABLE
#    include "../sessions/03_stream_of_knowledge/starter/game_state.h"
#endif

#ifdef SESSION_04_AVAILABLE
#    include "../sessions/04_guardian_spirits/starter/weapon.h"
#endif

#ifdef SESSION_05_AVAILABLE
#    include "../sessions/05_crafting_classes/starter/spell.h"
#endif

#ifdef SESSION_08_AVAILABLE
#    include "../sessions/08_shapeshifting/starter/combat.h"
#endif

#ifdef SESSION_11_AVAILABLE
#    include "../sessions/11_standard_library/starter/stl_game.h"
#endif

// Fallback implementations for sessions not completed
#ifndef SESSION_02_AVAILABLE
struct Item {
    std::string name;
    int value;
    Item(const std::string& n, int v) : name(n), value(v) {}
};
#endif

#ifndef SESSION_08_AVAILABLE
// Fallback Enemy system
struct Enemy {
    std::string name;
    int health;
    int maxHealth;
    int attack;
    bool isBoss;

    Enemy(const std::string& n, int hp, int atk, bool boss = false)
        : name(n), health(hp), maxHealth(hp), attack(atk), isBoss(boss) {}

    bool isAlive() const { return health > 0; }
    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    std::string getType() const { return isBoss ? "Boss" : "Enemy"; }
    void takeDamage(int amount) { health = std::max(0, health - amount); }
};
#endif

// Location system
struct Location {
    std::string name;
    std::string description;
#ifdef SESSION_08_AVAILABLE
    std::unique_ptr<Entity> enemy;
#else
    std::unique_ptr<Enemy> enemy;
#endif
    std::vector<std::string> treasureNames;
    std::vector<int> treasureValues;
    bool visited;
    std::map<char, int> exits;

    Location(const std::string& n, const std::string& desc)
        : name(n), description(desc), visited(false) {}
};

class GameEngine {
   private:
    bool running_;

    // Player stats
    std::string playerName_;
    int playerHealth_;
    int playerMaxHealth_;
    int playerAttack_;
    int playerGold_;
    int playerLevel_;
    std::string currentLocationName_;

#ifdef SESSION_02_AVAILABLE
    std::unique_ptr<Inventory> inventory_;
#else
    std::vector<Item> inventory_;
#endif

#ifdef SESSION_04_AVAILABLE
    std::unique_ptr<Weapon> equippedWeapon_;
#endif

#ifdef SESSION_11_AVAILABLE
    std::unique_ptr<QuestManager> questManager_;
#endif

    // Dungeon
    std::vector<std::unique_ptr<Location>> dungeon_;
    int currentLocation_;
    bool bossDefeated_;

    // RNG
    std::mt19937 rng_;

   public:
    GameEngine()
        : running_(false), playerName_("Hero"), playerHealth_(100), playerMaxHealth_(100),
          playerAttack_(15), playerGold_(0), playerLevel_(1),
          currentLocationName_("Dungeon Entrance"), currentLocation_(0), bossDefeated_(false),
          rng_(std::random_device{}()) {
#ifdef SESSION_02_AVAILABLE
        inventory_ = std::make_unique<Inventory>(20);
#endif
#ifdef SESSION_11_AVAILABLE
        questManager_ = std::make_unique<QuestManager>();
        initializeQuests();
#endif
        createDungeon();
    }

    void createDungeon() {
        // Entrance
        auto loc0 = std::make_unique<Location>(
            "Dungeon Entrance",
            "You stand at the entrance of a dark dungeon. Torches flicker on the walls.");
        loc0->exits['n'] = 1;
        dungeon_.push_back(std::move(loc0));

        // Hall
        auto loc1 = std::make_unique<Location>(
            "Grand Hall", "A vast hall with crumbling pillars. You hear echoes in the distance.");
        loc1->exits['s'] = 0;
        loc1->exits['e'] = 2;
        loc1->exits['w'] = 3;
        loc1->exits['n'] = 4;
#ifdef SESSION_08_AVAILABLE
        loc1->enemy = std::make_unique<Warrior>("Goblin Scout", 30, 8, 5);
#else
        loc1->enemy = std::make_unique<Enemy>("Goblin Scout", 30, 8);
#endif
        loc1->treasureNames.push_back("Rusty Dagger");
        loc1->treasureValues.push_back(10);
        dungeon_.push_back(std::move(loc1));

        // Armory
        auto loc2 =
            std::make_unique<Location>("Old Armory", "Broken weapons and armor litter the floor.");
        loc2->exits['w'] = 1;
        loc2->treasureNames.push_back("Iron Sword");
        loc2->treasureValues.push_back(50);
        loc2->treasureNames.push_back("Leather Armor");
        loc2->treasureValues.push_back(40);
        dungeon_.push_back(std::move(loc2));

        // Storage
        auto loc3 =
            std::make_unique<Location>("Storage Room", "Dusty crates and barrels fill this room.");
        loc3->exits['e'] = 1;
        loc3->treasureNames.push_back("Health Potion");
        loc3->treasureValues.push_back(25);
        loc3->treasureNames.push_back("Gold Coins");
        loc3->treasureValues.push_back(100);
        dungeon_.push_back(std::move(loc3));

        // Guard Room
        auto loc4 = std::make_unique<Location>(
            "Guard Room", "This room once housed the dungeon guards. Bones scatter the floor.");
        loc4->exits['s'] = 1;
        loc4->exits['n'] = 5;
#ifdef SESSION_08_AVAILABLE
        loc4->enemy = std::make_unique<Warrior>("Skeleton Warrior", 50, 12, 8);
#else
        loc4->enemy = std::make_unique<Enemy>("Skeleton Warrior", 50, 12);
#endif
        loc4->treasureNames.push_back("Steel Sword");
        loc4->treasureValues.push_back(100);
        dungeon_.push_back(std::move(loc4));

        // Treasure Room
        auto loc5 = std::make_unique<Location>("Treasure Chamber",
                                               "Gold and jewels glitter in the torchlight!");
        loc5->exits['s'] = 4;
        loc5->exits['n'] = 6;
        loc5->treasureNames.push_back("Magic Amulet");
        loc5->treasureValues.push_back(200);
        loc5->treasureNames.push_back("Gold Pile");
        loc5->treasureValues.push_back(500);
        dungeon_.push_back(std::move(loc5));

        // Boss Room
        auto loc6 = std::make_unique<Location>(
            "Dragon's Lair",
            "A massive chamber. The air is thick with smoke and the smell of sulfur.");
        loc6->exits['s'] = 5;
#ifdef SESSION_08_AVAILABLE
        loc6->enemy = std::make_unique<Mage>("Ancient Dragon", 150, 25, 100);
#else
        loc6->enemy = std::make_unique<Enemy>("Ancient Dragon", 150, 25, true);
#endif
        loc6->treasureNames.push_back("Dragon Hoard");
        loc6->treasureValues.push_back(5000);
        dungeon_.push_back(std::move(loc6));
    }

    void initialize() {
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════╗\n";
        std::cout << "║     C++ QUEST: DUNGEON CRAWLER         ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << "\n";

        displayAvailableSessions();

        std::cout << "You are " << playerName_ << ", a brave adventurer.\n";
        std::cout << "A dark dungeon awaits. Treasure and danger lie within!\n\n";

        std::cout << "Commands:\n";
        std::cout << "  n/s/e/w - Move north/south/east/west\n";
        std::cout << "  look    - Examine current location\n";
        std::cout << "  fight   - Fight enemy in current location\n";
        std::cout << "  flee    - Run from combat\n";
        std::cout << "  loot    - Take treasure from current location\n";
        std::cout << "  stats   - View your character\n";
        std::cout << "  inv     - View inventory\n";
#ifdef SESSION_11_AVAILABLE
        std::cout << "  quests  - View quests\n";
#endif
        std::cout << "  save    - Save game\n";
        std::cout << "  load    - Load game\n";
        std::cout << "  quit    - Exit game\n\n";

        running_ = true;
        describeLocation();
    }

    void run() {
        if (!running_)
            return;

        while (running_) {
            std::cout << "\n> ";
            std::string command;
            std::cin >> command;

            if (command == "n" || command == "north")
                move('n');
            else if (command == "s" || command == "south")
                move('s');
            else if (command == "e" || command == "east")
                move('e');
            else if (command == "w" || command == "west")
                move('w');
            else if (command == "look")
                describeLocation();
            else if (command == "fight")
                fight();
            else if (command == "flee")
                flee();
            else if (command == "loot")
                loot();
            else if (command == "stats")
                showStats();
            else if (command == "inv")
                showInventory();
#ifdef SESSION_11_AVAILABLE
            else if (command == "quests")
                showQuests();
#endif
            else if (command == "save")
                saveGame();
            else if (command == "load")
                loadGame();
            else if (command == "quit")
                running_ = false;
            else
                std::cout << "Unknown command. Type 'look' for help.\n";

            if (bossDefeated_) {
                std::cout << "\n";
                std::cout << "╔════════════════════════════════════════╗\n";
                std::cout << "║          VICTORY!                      ║\n";
                std::cout << "╚════════════════════════════════════════╝\n";
                std::cout << "You have defeated the Ancient Dragon!\n";
                std::cout << "The dungeon is cleared. You are a true hero!\n\n";
                std::cout << "Final Stats:\n";
                showStats();
                running_ = false;
            }

            if (playerHealth_ <= 0) {
                std::cout << "\n";
                std::cout << "╔════════════════════════════════════════╗\n";
                std::cout << "║          GAME OVER                     ║\n";
                std::cout << "╚════════════════════════════════════════╝\n";
                std::cout << "You have fallen in the dungeon...\n";
                std::cout << "Better luck next time!\n\n";
                running_ = false;
            }
        }
    }

    void shutdown() {
        std::cout << "\nThanks for playing C++ Quest!\n";
        std::cout << "Keep learning and building! 🚀\n\n";
    }

   private:
#ifdef SESSION_11_AVAILABLE
    void initializeQuests() {
        questManager_->addQuest({"goblin", "Defeat the Goblin Scout", false});
        questManager_->addQuest({"skeleton", "Defeat the Skeleton Warrior", false});
        questManager_->addQuest({"treasure", "Find the Magic Amulet", false});
        questManager_->addQuest({"dragon", "Slay the Ancient Dragon", false});
    }

    void checkQuestCompletion(const std::string& questId) {
        if (!questManager_->isCompleted(questId)) {
            questManager_->completeQuest(questId);
            std::cout << "\n🎯 Quest Completed: ";
            auto quests = questManager_->getCompletedQuests();
            for (const auto& q : quests) {
                if (q.id == questId) {
                    std::cout << q.name << "\n";
                    break;
                }
            }
        }
    }
#endif

    void displayAvailableSessions() {
        auto sessions = SessionConfig::getAvailableSessions();
        std::cout << "📚 Sessions integrated: ";

        if (sessions.empty()) {
            std::cout << "None (using fallback code)\n";
        } else {
            for (size_t i = 0; i < sessions.size(); ++i) {
                std::cout << sessions[i];
                if (i < sessions.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "\n";
        }

#ifdef SESSION_02_AVAILABLE
        std::cout << "   ✅ Session 2: Inventory system (dynamic memory)\n";
#endif
#ifdef SESSION_03_AVAILABLE
        std::cout << "   ✅ Session 3: Save/Load system (file I/O)\n";
#endif
#ifdef SESSION_04_AVAILABLE
        std::cout << "   ✅ Session 4: Weapon system (smart pointers)\n";
#endif
#ifdef SESSION_05_AVAILABLE
        std::cout << "   ✅ Session 5: Spell system (classes)\n";
#endif
#ifdef SESSION_08_AVAILABLE
        std::cout << "   ✅ Session 8: Combat system (polymorphism)\n";
#endif
#ifdef SESSION_11_AVAILABLE
        std::cout << "   ✅ Session 11: Quest system (STL containers)\n";
#endif
        std::cout << "\n";
    }

    void describeLocation() {
        Location& loc = *dungeon_[currentLocation_];
        currentLocationName_ = loc.name;

        std::cout << "\n═══════════════════════════════════\n";
        std::cout << loc.name << "\n";
        std::cout << "═══════════════════════════════════\n";
        std::cout << loc.description << "\n";

        if (loc.enemy && loc.enemy->isAlive()) {
            std::cout << "\n⚠️  " << loc.enemy->getName() << " blocks your path!\n";
#ifdef SESSION_08_AVAILABLE
            std::cout << "   Type: " << loc.enemy->getType() << "\n";
#endif
            std::cout << "   HP: " << loc.enemy->getHealth() << "\n";
        }

        if (!loc.treasureNames.empty()) {
            std::cout << "\n✨ You see treasure here:\n";
            for (size_t i = 0; i < loc.treasureNames.size(); ++i) {
                std::cout << "   - " << loc.treasureNames[i];
                std::cout << " (" << loc.treasureValues[i] << " gold)\n";
            }
        }

        std::cout << "\nExits: ";
        for (const auto& exit : loc.exits) {
            switch (exit.first) {
                case 'n':
                    std::cout << "north ";
                    break;
                case 's':
                    std::cout << "south ";
                    break;
                case 'e':
                    std::cout << "east ";
                    break;
                case 'w':
                    std::cout << "west ";
                    break;
            }
        }
        std::cout << "\n";

        loc.visited = true;
    }

    void move(char direction) {
        Location& loc = *dungeon_[currentLocation_];

        if (loc.enemy && loc.enemy->isAlive()) {
            std::cout << "You cannot leave while " << loc.enemy->getName()
                      << " blocks your path!\n";
            std::cout << "Fight or flee!\n";
            return;
        }

        auto it = loc.exits.find(direction);
        if (it == loc.exits.end()) {
            std::cout << "You cannot go that way.\n";
            return;
        }

        currentLocation_ = it->second;
        std::cout << "You move ";
        switch (direction) {
            case 'n':
                std::cout << "north";
                break;
            case 's':
                std::cout << "south";
                break;
            case 'e':
                std::cout << "east";
                break;
            case 'w':
                std::cout << "west";
                break;
        }
        std::cout << "...\n";

        describeLocation();
    }

    void fight() {
        Location& loc = *dungeon_[currentLocation_];

        if (!loc.enemy || !loc.enemy->isAlive()) {
            std::cout << "There is nothing to fight here.\n";
            return;
        }

#ifdef SESSION_08_AVAILABLE
        Entity* enemy = loc.enemy.get();

        std::cout << "\n⚔️  COMBAT!\n";
        std::cout << "You vs " << enemy->getName() << " (" << enemy->getType() << ")\n\n";

        while (enemy->isAlive() && playerHealth_ > 0) {
            // Player attacks
            int totalAttack = playerAttack_;
#    ifdef SESSION_04_AVAILABLE
            if (equippedWeapon_) {
                totalAttack += equippedWeapon_->getDamage();
            }
#    endif
            int damage = totalAttack + (rand() % 5);
            enemy->takeDamage(damage);

            std::cout << "You attack for " << damage << " damage!\n";
            std::cout << enemy->getName() << " HP: " << enemy->getHealth() << "\n";

            if (!enemy->isAlive()) {
                std::cout << "\n🎉 Victory! " << enemy->getName() << " defeated!\n";

#    ifdef SESSION_11_AVAILABLE
                // Check quest completion
                if (enemy->getName() == "Goblin Scout") {
                    checkQuestCompletion("goblin");
                } else if (enemy->getName() == "Skeleton Warrior") {
                    checkQuestCompletion("skeleton");
                } else if (enemy->getName() == "Ancient Dragon") {
                    checkQuestCompletion("dragon");
                }
#    endif

                if (enemy->getType() == "Mage" && enemy->getName() == "Ancient Dragon") {
                    bossDefeated_ = true;
                }

                if (!loc.treasureNames.empty()) {
                    std::cout << "\n💎 " << enemy->getName() << " dropped treasure!\n";
                }
                break;
            }

            // Enemy attacks using polymorphism - just for visual effect
            std::cout << "\n";
            // Create a dummy player entity for the attack visual
            // The actual damage is calculated below
            std::cout << enemy->getName() << " attacks!\n";

            // Calculate actual damage
            int enemyDamage = 10 + (rand() % 5);
            playerHealth_ -= enemyDamage;
            if (playerHealth_ < 0)
                playerHealth_ = 0;

            std::cout << "You take " << enemyDamage << " damage!\n";
            std::cout << "Your HP: " << playerHealth_ << "/" << playerMaxHealth_ << "\n\n";

            if (playerHealth_ <= 0) {
                return;
            }
        }
#else
        // Fallback combat
        Enemy& enemy = *loc.enemy;

        std::cout << "\n⚔️  COMBAT!\n";
        std::cout << "You vs " << enemy.name << "\n\n";

        while (enemy.isAlive() && playerHealth_ > 0) {
            int totalAttack = playerAttack_;
#    ifdef SESSION_04_AVAILABLE
            if (equippedWeapon_) {
                totalAttack += equippedWeapon_->getDamage();
            }
#    endif
            int damage = totalAttack + (rand() % 5);
            enemy.health -= damage;
            if (enemy.health < 0)
                enemy.health = 0;

            std::cout << "You attack for " << damage << " damage!\n";
            std::cout << enemy.name << " HP: " << enemy.health << "/" << enemy.maxHealth << "\n";

            if (!enemy.isAlive()) {
                std::cout << "\n🎉 Victory! " << enemy.name << " defeated!\n";

                if (enemy.isBoss) {
                    bossDefeated_ = true;
                }

                if (!loc.treasureNames.empty()) {
                    std::cout << "\n💎 " << enemy.name << " dropped treasure!\n";
                }
                break;
            }

            int enemyDamage = enemy.attack + (rand() % 3);
            playerHealth_ -= enemyDamage;
            if (playerHealth_ < 0)
                playerHealth_ = 0;

            std::cout << enemy.name << " attacks for " << enemyDamage << " damage!\n";
            std::cout << "Your HP: " << playerHealth_ << "/" << playerMaxHealth_ << "\n\n";

            if (playerHealth_ <= 0) {
                return;
            }
        }
#endif
    }

    void flee() {
        Location& loc = *dungeon_[currentLocation_];

        if (!loc.enemy || !loc.enemy->isAlive()) {
            std::cout << "There is nothing to flee from.\n";
            return;
        }

        std::cout << "You flee from " << loc.enemy->getName() << "!\n";

        int damage = 5;
        playerHealth_ -= damage;
        if (playerHealth_ < 0)
            playerHealth_ = 0;

        std::cout << loc.enemy->getName() << " strikes you as you run! (-" << damage << " HP)\n";
        std::cout << "Your HP: " << playerHealth_ << "/" << playerMaxHealth_ << "\n";

        currentLocation_ = 0;
        std::cout << "You retreat to the entrance.\n";
        describeLocation();
    }

    void loot() {
        Location& loc = *dungeon_[currentLocation_];

        if (loc.treasureNames.empty()) {
            std::cout << "There is no treasure here.\n";
            return;
        }

        std::cout << "\n💰 You collect:\n";
        for (size_t i = 0; i < loc.treasureNames.size(); ++i) {
            const std::string& name = loc.treasureNames[i];
            int value = loc.treasureValues[i];

#ifdef SESSION_02_AVAILABLE
            inventory_->addItem(name, value);
#else
            inventory_.push_back(Item(name, value));
            std::cout << "   - " << name << " (" << value << " gold)\n";
#endif

            playerGold_ += value;

#ifdef SESSION_11_AVAILABLE
            // Check quest completion for Magic Amulet
            if (name == "Magic Amulet") {
                checkQuestCompletion("treasure");
            }
#endif

            // Check for weapons
#ifdef SESSION_04_AVAILABLE
            if (name.find("Sword") != std::string::npos ||
                name.find("Dagger") != std::string::npos) {
                int weaponDamage = value / 10;
                equippedWeapon_ = std::make_unique<Weapon>(name, weaponDamage);
                std::cout << "   ⚔️  Equipped " << name << " (+" << weaponDamage << " damage)\n";
            }
#endif
        }

        loc.treasureNames.clear();
        loc.treasureValues.clear();
    }

    void showStats() {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║          CHARACTER STATS               ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        std::cout << "Name:     " << playerName_ << "\n";
        std::cout << "Level:    " << playerLevel_ << "\n";
        std::cout << "Health:   " << playerHealth_ << "/" << playerMaxHealth_ << "\n";
        std::cout << "Attack:   " << playerAttack_;

#ifdef SESSION_04_AVAILABLE
        if (equippedWeapon_) {
            std::cout << " + " << equippedWeapon_->getDamage() << " (weapon)";
        }
#endif
        std::cout << "\n";
        std::cout << "Gold:     " << playerGold_ << "\n";
        std::cout << "Location: " << currentLocationName_ << "\n";

        int barWidth = 20;
        int filled = playerMaxHealth_ > 0 ? (playerHealth_ * barWidth) / playerMaxHealth_ : 0;
        std::cout << "HP:       [";
        for (int i = 0; i < barWidth; ++i) {
            std::cout << (i < filled ? "█" : "░");
        }
        std::cout << "]\n";
    }

    void showInventory() {
#ifdef SESSION_02_AVAILABLE
        inventory_->display();
#else
        std::cout << "\n🎒 Inventory (" << inventory_.size() << " items):\n";
        if (inventory_.empty()) {
            std::cout << "   (empty)\n";
        } else {
            for (size_t i = 0; i < inventory_.size(); ++i) {
                std::cout << "   " << (i + 1) << ". " << inventory_[i].name << " ("
                          << inventory_[i].value << " gold)\n";
            }
        }
#endif
    }

#ifdef SESSION_11_AVAILABLE
    void showQuests() {
        std::cout << "\n📜 Quest Log:\n";
        std::cout << "═══════════════════════════════════\n";

        auto active = questManager_->getActiveQuests();
        auto completed = questManager_->getCompletedQuests();

        if (!active.empty()) {
            std::cout << "\n🔸 Active Quests:\n";
            for (const auto& quest : active) {
                std::cout << "   [ ] " << quest.name << "\n";
            }
        }

        if (!completed.empty()) {
            std::cout << "\n✅ Completed Quests:\n";
            for (const auto& quest : completed) {
                std::cout << "   [✓] " << quest.name << "\n";
            }
        }

        std::cout << "\nProgress: " << questManager_->getCompletedCount() << "/"
                  << questManager_->getQuestCount() << " quests completed\n";
    }
#endif

    void saveGame() {
        std::cout << "💾 Saving game...\n";

#ifdef SESSION_03_AVAILABLE
        GameState state(playerName_, "Adventurer", playerLevel_, playerGold_, currentLocationName_);

        // Add inventory items
#    ifdef SESSION_02_AVAILABLE
        for (int i = 0; i < inventory_->getCount(); ++i) {
            // Note: Can't access items directly, so we save count only
            state.addItem("Item");
        }
#    else
        for (const auto& item : inventory_) {
            state.addItem(item.name);
        }
#    endif

        if (state.saveToFile("dungeon_save.txt")) {
            std::cout << "   ✅ Game saved successfully! (Session 3 file I/O)\n";
        } else {
            std::cout << "   ❌ Error: Could not save game!\n";
        }
#else
        // Fallback save
        std::ofstream file("dungeon_save.txt");
        if (!file.is_open()) {
            std::cout << "   ❌ Error: Could not save game!\n";
            return;
        }

        file << playerName_ << "\n";
        file << playerHealth_ << "\n";
        file << playerMaxHealth_ << "\n";
        file << playerAttack_ << "\n";
        file << playerGold_ << "\n";
        file << playerLevel_ << "\n";
        file << currentLocation_ << "\n";
        file << bossDefeated_ << "\n";

        file.close();
        std::cout << "   ✅ Game saved successfully!\n";
#endif
    }

    void loadGame() {
        std::cout << "📂 Loading game...\n";

#ifdef SESSION_03_AVAILABLE
        GameState state;
        if (state.loadFromFile("dungeon_save.txt")) {
            playerName_ = state.getName();
            playerLevel_ = state.getLevel();
            playerGold_ = state.getGold();
            currentLocationName_ = state.getLocation();

            std::cout << "   ✅ Game loaded successfully! (Session 3 file I/O)\n";
            std::cout << "   Loaded: " << playerName_ << ", Level " << playerLevel_ << ", "
                      << playerGold_ << " gold\n";
        } else {
            std::cout << "   ❌ No save file found!\n";
        }
#else
        // Fallback load
        std::ifstream file("dungeon_save.txt");
        if (!file.is_open()) {
            std::cout << "   ❌ No save file found!\n";
            return;
        }

        std::getline(file, playerName_);
        file >> playerHealth_ >> playerMaxHealth_ >> playerAttack_ >> playerGold_;
        file >> playerLevel_ >> currentLocation_ >> bossDefeated_;

        file.close();
        std::cout << "   ✅ Game loaded successfully!\n";
        describeLocation();
#endif
    }
};
