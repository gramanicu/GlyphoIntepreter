/**
 * @file InputParser.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Definitions for the InputParser
 * @copyright Copyright (c) 2020
 */

#include "InputParser.hpp"

using namespace Glypho::Core;

std::vector<std::string> InputParser::read_data(std::istream& input) {
    std::vector<std::string> encoded_instructions;

    std::string instruction = "";
    char character;

    while (input >> character) {
        // Ignore empty spaces
        if (character == ' ') continue;

        instruction.push_back(character);

        // If we read 4 character, we have an instruction
        if (instruction.length() == 4) {
            encoded_instructions.push_back(instruction);
            instruction = "";
        }
    }

    // If we have finished to read the code, but we haven't finished to read
    // an instruction, we must throw the SyntaxError
    Helpers::MUST(
        instruction.length() == 0,
        Throwable::message(Throwable::SyntaxError::CODE_LENGTH_INVALID) + "\n");

    return encoded_instructions;
}

std::vector<std::string> InputParser::read_data(std::string path) {
    std::ifstream input(path);

    // Exit the program if the input file is unavailable
    Helpers::MUST_NOT(input.fail() || input.bad(),
                      "ArgumentError: Couldn't find or open the specified file\n");

    return InputParser::read_data(input);
}
