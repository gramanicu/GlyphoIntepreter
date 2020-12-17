/**
 * @file Interpreter.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief A Glypho language interpreter
 * @copyright Copyright (c) 2020
 */

#pragma once

#include "Helpers.hpp"
#include "InputParser.hpp"
#include "Instruction.hpp"
#include "Stack.hpp"

namespace Glypho {
    /**
     * @brief Declaration for the Interpreter class
     * This interpretor can only run code from files (can not do it in realtime)
     */
    class Interpreter {
       private:
        std::string code_path;    // The path to the file containing the program's code
        unsigned int input_numbers_base;    // The base of the numbers that can be read from stdin
        bool code_loaded;          // If a program was loaded

       public:
        /**
         * @brief Construct a new Interpreter object
         * Empty constructor
         */
        Interpreter();

        /**
         * @brief Construct a new Interpreter object
         *
         * @param path The path to the source code used by this object
         * @param base The base of the numbers that will be taken as input
         */
        Interpreter(const std::string& path,
                    const unsigned int base = Constants::DEFAULT_INPUT_BASE);

        /**
         * @brief Copy-Constructs a new Interpreter object
         *
         * @param other The other Interpretor object
         */
        Interpreter(const Interpreter& other);

        /**
         * @brief Assignment operator
         * 
         * @param other The other object
         * @return Interpreter& The new object
         */
        Interpreter& operator=(const Interpreter& other);

        /**
         * @brief Loads the program code, decodes it and checks syntax.
         *
         */
        void load_program();

        /**
         * @brief Run the loaded program code
         *
         */
        void run_program();
    };
}    // namespace Glypho