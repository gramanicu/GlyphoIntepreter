/**
 * @file Main.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Driver code for the Glypho Interpreter
 * @copyright Copyright (c) 2020
 */

#include <iostream>
#include <string>

#include "./Glypho/Helpers.hpp"
#include "./Glypho/Interpreter.hpp"

int main(int argc, char** argv) {
    // Check the program arguments
    if (argc != 2 && argc != 3) {
        Glypho::Helpers::MUST(false,
                              "ArgumentError: Invalid number of arguments\n");
    }

    // Store the path
    std::string path(argv[1]);
    Glypho::Interpreter g_interpreter;

    // Assign the parameters to the interpreter
    if (argc == 2) {
        // Base was not provided
        g_interpreter = Glypho::Interpreter(path);
    } else {
        // Try to parse the base
        int base;
        try {
            base = std::stoi(std::string(argv[2]));
        } catch (std::exception& e) {
            // Argument was not a number
            Glypho::Helpers::MUST(false, "ArgumentError: Base '" +
                                             std::string(argv[2]) +
                                             "' is not a number\n");
        }

        // Check if the base is a valid number
        Glypho::Helpers::MUST(base > 0, "ArgumentError: Base '" +
                                            std::to_string(base) +
                                            "' is not a valid number\n");

        // Base was a valid number
        g_interpreter = Glypho::Interpreter(path, base);
    }

    Glypho::Core::Integer a("-100");
    Glypho::Core::Integer b("-50");

    std::cout << (a < b) << " " << (a > b) << " " << (a <= b) << " " << (a >= b)
              << " " << (a == b) << " " << (a != b) << "\n";

    // Load the program
    g_interpreter.load_program();

    // Execute the code
    g_interpreter.run_program();

    return 0;
}
