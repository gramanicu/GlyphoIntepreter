/**
 * @file Stack.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Header for that Stack class, the stack used by the glypho interpreter
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Helpers.hpp"
#include "Integer.hpp"

namespace Glypho::Core {
    class Stack {
        std::stack<Integer> data;
    };
}    // namespace Glypho::Core