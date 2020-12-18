/**
 * @file Helpers.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Definition for the helper functions
 * @copyright Copyright (c) 2020
 */

#include "Helpers.hpp"

using namespace Glypho;

std::string Throwable::message(Throwable::SyntaxError error) {
    std::string msg = "SyntaxError: ";
    switch (error) {
        case SyntaxError::CODE_LENGTH_INVALID: {
            msg +=
                "Invalid instruction (the number of chars in the source code "
                "should be divisible by 4)";
        } break;
        case SyntaxError::CLOSING_BRACE_EXPECTED: {
            msg += "Expected a closing brace (R-Brace)";
        } break;
        case SyntaxError::OPENING_BRACE_EXPECTED: {
            msg += "No corresponding opening brace (L-Brace)";
        } break;
    }

    return msg;
}

std::string Throwable::message(Throwable::RuntimeException exception) {
    std::string msg = "RuntimeException: ";
    switch (exception) {
        case RuntimeException::EMPTY_STACK: {
            msg +=
                "Expected at least an element on the stack, but it was "
                "empty";
        } break;
        case RuntimeException::INSUFFICIENT_STACK_SIZE: {
            msg += "Not enough elements on the stack";
        } break;
        case RuntimeException::INVALID_INPUT_BASE: {
            msg +=
                "The base of the input number is not corresponding to "
                "the base that was selected initially";
        } break;
        case RuntimeException::DIVISION_BY_0: {
            msg += "Invalid arithmetic operation, division by 0";
        }
    }

    return msg;
}