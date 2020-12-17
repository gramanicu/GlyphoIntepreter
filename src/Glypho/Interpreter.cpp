/**
 * @file Interpreter.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Interpreter.hpp"

using namespace Glypho;

Interpreter::Interpreter()
    : code_path(""),
      input_numbers_base(Constants::DEFAULT_INPUT_BASE),
      code_loaded(false) {}

Interpreter::Interpreter(const std::string& path, const unsigned int base)
    : code_path(path), input_numbers_base(base), code_loaded(false) {}

Interpreter::Interpreter(const Interpreter& other)
    : code_path(other.code_path),
      input_numbers_base(other.input_numbers_base),
      code_loaded(false) {}


Interpreter& Interpreter::operator=(const Interpreter& other) {
    this->code_path = other.code_path;
    this->input_numbers_base = other.input_numbers_base;
    this->code_loaded = false;
    return *this;
}

void Interpreter::load_program() {
    // Read encoded instructions from the file
    std::vector<std::string> e_instructions = Core::InputParser::read_data(code_path);

    // Decode the instructions

    code_loaded = true;
}


void Interpreter::run_program() {
    if(!code_loaded) exit(-1);

    // Start the program execution
}