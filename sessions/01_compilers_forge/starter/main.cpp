#include "display.h"

int main() {
    std::cout << "=== C++ Quest: Character Display System ===\n\n";

    // Display characters
    displayCharacter("Aragorn", "Warrior", 10, 70, 100);
    std::cout << "\n";
    displayCharacter("Gandalf", "Mage", 50, 45, 60);

    // Display character ID in different bases
    std::cout << "\nCharacter ID: ";
    displayInBases(42);
    std::cout << "\n";

    // Explore type sizes
    std::cout << "\n=== Type Information ===\n";
    displayTypeInfo<char>("char");
    std::cout << "\n";
    displayTypeInfo<int>("int");
    std::cout << "\n";
    displayTypeInfo<double>("double");

    return 0;
}
