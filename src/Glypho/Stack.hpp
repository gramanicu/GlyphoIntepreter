/**
 * @file Stack.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Header for that Stack class, the stack used by the glypho interpreter
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Helpers.hpp"
#include "Integer.hpp"

namespace Glypho::Core {
    class Stack {
        private:
        std::list<Integer> data;

        public:
        /**
         * @brief Construct a new Stack object
         * 
         */
        Stack();
        
        // Basic Stack Operations
        /**
         * @brief Add an element at the top of the stack with the value of 1
         * 
         */
        void Push();

        /**
         * @brief Take the element from the top of the stack
         * 
         * @return Integer 
         */
        void Pop();

        /**
         * @brief Get the element from the top of the stack, but don't remove it
         * 
         * @return Integer The value
         */
        Integer Peek() const;

        /**
         * @brief Add an element at the top of the stack with the specified value
         * 
         * @param value New value
         */
        void Input(const Integer& value);

        /**
         * @brief Get the element at the top of the stack and remove it
         * 
         * @return Integer The top value
         */
        Integer Output();

        // Complex Stack Operations
        /**
         * @brief Duplicate the element at the top of the stack
         * 
         */
        void Dup();

        /**
         * @brief Swaps the top 2 elements in the stack
         * 
         */
        void Swap();
        
        /**
         * @brief Put the top element at the back
         * 
         */
        void Rotate();

        /**
         * @brief Put the back element at the top
         * 
         */
        void ReverseRotate();

        /**
         * @brief Takes the top two elements, computes their sum, and pushes the new element
         * Will remove the two elements
         */
        void Add();

        /**
         * @brief Takes the top two elements, computes their product, and pushes the new element
         * Will remove the two elements
         */
        void Multiply();

        /**
         * @brief Removes the top element and inserts back the inverse of that value
         * 
         */
        void Negate();

        /**
         * @brief Removes and retuns the specified amount of elements from the stack
         * 
         * @param count The number of elements
         * @return std::vector<Integer> An array of elements
         */
        std::vector<Integer> Out_K_Elems(const uint64_t count);
    };
}    // namespace Glypho::Core