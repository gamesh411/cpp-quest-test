#pragma once

#include <string>

/**
 * Common game types used across all sessions
 * These will be expanded as the course progresses
 */

namespace quest {

// Character classes
enum class CharacterClass { Warrior, Mage, Rogue, Cleric };

// Convert enum to string
inline std::string toString(CharacterClass c) {
    switch (c) {
        case CharacterClass::Warrior:
            return "Warrior";
        case CharacterClass::Mage:
            return "Mage";
        case CharacterClass::Rogue:
            return "Rogue";
        case CharacterClass::Cleric:
            return "Cleric";
        default:
            return "Unknown";
    }
}

// Item rarity
enum class Rarity { Common, Uncommon, Rare, Epic, Legendary };

// Spell types (for later sessions)
enum class SpellType { Damage, Healing, Buff, Debuff };

}  // namespace quest
