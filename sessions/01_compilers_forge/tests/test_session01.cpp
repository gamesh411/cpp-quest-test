#include <sstream>
#include <string>

#include <catch2/catch_all.hpp>

// Include student's implementation
#include "../starter/display.h"

#include "../starter/display.cpp"

/*
 * Session 1 Test Coverage
 *
 * Tests student's implementation of:
 * ✅ displayBar() - Progress bar rendering
 * ✅ displayCharacter() - Character info display
 * ✅ displayInBases() - Number base conversion
 * ✅ displayTypeInfo() - Type size and limits
 *
 * Coverage: 8 test cases, 20+ assertions
 */

// Helper to capture cout
class CoutCapture {
    std::stringstream buffer;
    std::streambuf* old;

   public:
    CoutCapture() : old(std::cout.rdbuf(buffer.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(old); }
    std::string str() { return buffer.str(); }
};

TEST_CASE("displayBar renders progress correctly", "[session01][bar]") {
    SECTION("Full bar") {
        CoutCapture capture;
        displayBar(10, 10, 10);
        REQUIRE(capture.str() == "[██████████]");
    }

    SECTION("Half bar") {
        CoutCapture capture;
        displayBar(5, 10, 10);
        REQUIRE(capture.str() == "[█████░░░░░]");
    }

    SECTION("Empty bar") {
        CoutCapture capture;
        displayBar(0, 10, 10);
        REQUIRE(capture.str() == "[░░░░░░░░░░]");
    }

    SECTION("80% bar") {
        CoutCapture capture;
        displayBar(80, 100, 10);
        REQUIRE(capture.str() == "[████████░░]");
    }

    SECTION("Custom width") {
        CoutCapture capture;
        displayBar(3, 10, 5);
        std::string output = capture.str();
        REQUIRE(output.find('[') != std::string::npos);
        REQUIRE(output.find(']') != std::string::npos);
    }
}

TEST_CASE("displayBar handles edge cases", "[session01][bar][edge]") {
    SECTION("Zero max (avoid division by zero)") {
        CoutCapture capture;
        displayBar(0, 0, 10);
        // Should not crash, output should contain brackets
        std::string output = capture.str();
        REQUIRE(output.find('[') != std::string::npos);
        REQUIRE(output.find(']') != std::string::npos);
    }

    SECTION("Current exceeds max") {
        CoutCapture capture;
        displayBar(15, 10, 10);
        std::string output = capture.str();
        // Should handle gracefully (either clamp or show full)
        REQUIRE(output.find('[') != std::string::npos);
        REQUIRE(output.find(']') != std::string::npos);
    }
}

TEST_CASE("displayCharacter shows all information", "[session01][character]") {
    CoutCapture capture;
    displayCharacter("Aragorn", "Warrior", 10, 70, 100);
    std::string output = capture.str();

    REQUIRE(output.find("Aragorn") != std::string::npos);
    REQUIRE(output.find("Warrior") != std::string::npos);
    REQUIRE(output.find("10") != std::string::npos);

    // Should contain a progress bar
    bool hasBar = (output.find("█") != std::string::npos || output.find("░") != std::string::npos);
    REQUIRE(hasBar);
}

TEST_CASE("displayInBases shows decimal, hex, and octal", "[session01][bases]") {
    CoutCapture capture;
    displayInBases(42);
    std::string output = capture.str();

    // Should contain decimal 42
    REQUIRE(output.find("42") != std::string::npos);

    // Should contain hex 2a or 2A
    bool hasHex =
        (output.find("2a") != std::string::npos || output.find("2A") != std::string::npos);
    REQUIRE(hasHex);

    // Should contain octal 52
    REQUIRE(output.find("52") != std::string::npos);
}

TEST_CASE("displayInBases handles different values", "[session01][bases]") {
    SECTION("Zero") {
        CoutCapture capture;
        displayInBases(0);
        std::string output = capture.str();
        REQUIRE(output.find("0") != std::string::npos);
    }

    SECTION("Negative number") {
        CoutCapture capture;
        displayInBases(-10);
        std::string output = capture.str();
        // Should handle negative numbers
        REQUIRE(output.length() > 0);
    }

    SECTION("Large number") {
        CoutCapture capture;
        displayInBases(255);
        std::string output = capture.str();
        REQUIRE(output.find("255") != std::string::npos);  // decimal
        bool hasHex =
            (output.find("ff") != std::string::npos || output.find("FF") != std::string::npos);
        REQUIRE(hasHex);  // hex
    }
}

TEST_CASE("displayTypeInfo shows type information", "[session01][types]") {
    CoutCapture capture;
    displayTypeInfo<int>("int");
    std::string output = capture.str();

    REQUIRE(output.find("int") != std::string::npos);
    REQUIRE(output.find("4") != std::string::npos);  // size (typically 4 bytes)

    // Should show min and max values
    REQUIRE(output.length() > 20);  // Should have substantial output
}

TEST_CASE("displayTypeInfo works for different types", "[session01][types]") {
    SECTION("char") {
        CoutCapture capture;
        displayTypeInfo<char>("char");
        std::string output = capture.str();
        REQUIRE(output.find("char") != std::string::npos);
        REQUIRE(output.find("1") != std::string::npos);  // 1 byte
    }

    SECTION("double") {
        CoutCapture capture;
        displayTypeInfo<double>("double");
        std::string output = capture.str();
        REQUIRE(output.find("double") != std::string::npos);
        REQUIRE(output.find("8") != std::string::npos);  // 8 bytes
    }
}

TEST_CASE("Functions compile and link correctly", "[session01][compile]") {
    // This test just verifies that all required functions exist
    // and can be called without linker errors

    REQUIRE(true);  // If we got here, everything compiled
}
