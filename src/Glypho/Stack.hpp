/**
 * @file Stack.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Header for that Stack class, the stack used by the glypho interpreter
 * Internally, the top of the stack is the end of the vector and vice-versa
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Helpers.hpp"
//#include "Integer.hpp"

namespace Glypho::Core {
    class Stack {
       private:
        std::list<long long int> data;

       public:
        // The id that some functions receive is the id of the current
        // instruction (for error handling)
        /**
         * @brief Construct a new Stack object
         *
         */
        Stack();

        /**
         * @brief Copy-Constructs a new Stack object
         *
         * @param other
         */
        Stack(const Stack& other);

        /**
         * @brief Assignment operator
         *
         * @param other The other object
         * @return Stack& The new object
         */
        Stack& operator=(const Stack& other);

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
        void Pop(long int id);

        /**
         * @brief Get the element from the top of the stack, but don't remove it
         *
         * @return Integer The value
         */
        long long int Peek(long int id) const;

        /**
         * @brief Add an element at the top of the stack with the specified
         * value
         *
         * @param value New value
         */
        void Input(const long long int& value);

        /**
         * @brief Get the element at the top of the stack and remove it
         *
         * @return Integer The top value
         */
        long long int Output(long int id);

        // Complex Stack Operations
        /**
         * @brief Duplicate the element at the top of the stack
         *
         */
        void Dup(long int id);

        /**
         * @brief Swaps the top 2 elements in the stack
         *
         */
        void Swap(long int id);

        /**
         * @brief Put the top element at the back
         *
         */
        void Rotate(long int id);

        /**
         * @brief Put the back element at the top
         *
         */
        void ReverseRotate(long int id);

        /**
         * @brief Takes the top two elements, computes their sum, and pushes the
         * new element Will remove the two elements
         */
        void Add(long int id);

        /**
         * @brief Takes the top two elements, computes their product, and pushes
         * the new element Will remove the two elements
         */
        void Multiply(long int id);

        /**
         * @brief Removes the top element and inserts back the inverse of that
         * value
         *
         */
        void Negate(long int id);

        /**
         * @brief Removes and retuns the specified amount of elements from the
         * stack
         *
         * @param count The number of elements
         * @return std::vector<long long int> An array of elements
         */
        std::vector<long long int> Out_K_Elems(const uint64_t count,
                                               long int id);
    };
}    // namespace Glypho::Core