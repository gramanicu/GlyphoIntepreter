/**
 * @file Helpers.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Helper functions, macros, consts etc.. used by the Glypho Interpreter
 * @copyright Copyright (c) 2020
 */

#pragma once

#include <iostream>

namespace Glypho {
    namespace Constants {
        const unsigned int DEFAULT_INPUT_BASE = 10;
    }

    namespace Helpers {
        /**
         * @brief Check if the condition is triggered. If it is not, print the
         * error message and exit the program
         * @param condition The condition that must happen
         * @param error The error message
         * @param code The exit code
         */
        inline void MUST(bool condition, std::string error, int code = -1) {
            if (!condition) {
                std::cerr << error;
                exit(code);
            }
        }

        /**
         * @brief Check if the condition is triggered. If it is, print the
         * error message and exit the program
         * @param condition The condition that must happen
         * @param error The error message
         * @param code The exit code
         */
        inline void MUST_NOT(bool condition, std::string error, int code = -1) {
            if (condition) {
                std::cerr << error;
                exit(code);
            }
        }
    }    // namespace Helpers

    namespace Throwable {
        /**
         * @brief Types of SyntaxErrors the Glypho interpreter can throw
         *
         */
        enum class SyntaxError {
            CODE_LENGTH_INVALID,    // The code length is not divisible by the
                                    // instruction length
            CLOSING_BRACE_EXPECTED,    // There is an open brace that was not
                                       // closed
            OPENING_BRACE_EXPECTED     // There is a closed brace without a
                                       // correspondent
        };

        /**
         * @brief Types of RuntimeExceptions the Glypho interpreter can throw
         *
         */
        enum class RuntimeException {
            EMPTY_STACK,    // The operation needs at least one element on the
                            // stack, but it is empty
            INSUFFICIENT_STACK_SIZE,    // The operation needs more elements
                                        // than are available on the stack
            INVALID_INPUT_BASE,    // The base of the input numbers is not the
                                   // one expected
            DIVISION_BY_0,         // A division by 0 was attempted
            INPUT_NOT_VALID_INT    // The value provided was not a integer
        };

        /**
         * @brief Returns the message associated to a specific SyntaxError
         *
         * @param error The SyntaxError
         * @return std::string The message
         */
        std::string message(SyntaxError error);

        /**
         * @brief Returns the message associated to a specific RuntimeException
         *
         * @param exception The RuntimeException
         * @return std::string The message
         */
        std::string message(RuntimeException exception);

    }    // namespace Throwable
}    // namespace Glypho