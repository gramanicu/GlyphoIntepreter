/**
 * @file Helpers.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Definition for the helper functions
 * @copyright Copyright (c) 2020
 */

#include "Helpers.hpp"

using namespace Glypho;

std::string Throwable::message(Throwable::SyntaxError error, const int line) {
    std::string msg = "Error:";
    msg += std::to_string(line);

    // std::string msg = "SyntaxError: ";
    // switch (error) {
    //     case SyntaxError::CODE_LENGTH_INVALID: {
    //         msg +=
    //             "Invalid instruction (the number of chars in the source code
    //             " "should be divisible by 4)";
    //     } break;
    //     case SyntaxError::CLOSING_BRACE_EXPECTED: {
    //         msg += "Expected a closing brace (R-Brace)";
    //     } break;
    //     case SyntaxError::OPENING_BRACE_EXPECTED: {
    //         msg += "No corresponding opening brace (L-Brace)";
    //     } break;
    // }

    return msg;
}

std::string Throwable::message(Throwable::RuntimeException exception,
                               const int line) {
    std::string msg = "Exception:";
    msg += std::to_string(line);

    // std::string msg = "RuntimeException: ";
    // switch (exception) {
    //     case RuntimeException::EMPTY_STACK: {
    //         msg +=
    //             "Expected at least an element on the stack, but it was "
    //             "empty";
    //     } break;
    //     case RuntimeException::INSUFFICIENT_STACK_SIZE: {
    //         msg += "Not enough elements on the stack";
    //     } break;
    //     case RuntimeException::INVALID_INPUT_BASE: {
    //         msg +=
    //             "The base of the input number is not corresponding to "
    //             "the base that was selected initially";
    //     } break;
    //     case RuntimeException::DIVISION_BY_0: {
    //         msg += "Invalid arithmetic operation, division by 0";
    //     } break;
    //     case RuntimeException::INPUT_NOT_VALID_INT: {
    //         msg += "The provided input was not an integer";
    //     } break;
    // }

    return msg;
}

char Helpers::charValue(const int number) {
    if (number >= 0 && number <= 9)
        return (char)(number + '0');
    else
        return (char)(number - 10 + 'A');
}

std::string Helpers::switchBase(int base, long long int inputNumber) {
    std::string str = "";
    bool is_negative = false;

    // Convert input number is given base by repeatedly
    // dividing it by base and taking remainder
    if (inputNumber < 0) {
        is_negative = true;
        inputNumber = -inputNumber;
    }

    if (inputNumber == 0) { return "0"; };

    while (inputNumber > 0) {
        str += Helpers::charValue(inputNumber % base);
        inputNumber /= base;
    }

    // Reverse the result
    std::reverse(str.begin(), str.end());
    if (is_negative) { str = "-" + str; }

    return str;
}