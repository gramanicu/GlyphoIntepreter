/**
 * @file Stack.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace Glypho::Core {
    class Integer {
       private:
        std::vector<uint8_t> value;
        bool is_negative;

       public:
        // Constructors
        Integer();
        Integer(const std::string& string);
        Integer(const Integer& other);
        Integer& operator=(const Integer& other);

        // Arithmetic operators
        friend Integer operator+(Integer l, const Integer& r);
        friend Integer operator-(Integer l, const Integer& r);
        friend Integer operator*(Integer l, const Integer& r);
        friend Integer operator/(Integer l, const Integer& r);
        friend Integer operator%(Integer l, const Integer& r);

        // Increment/Decrement
        Integer operator++();
        Integer operator++(int);
        Integer operator--();
        Integer operator--(int);

        // Relational operators
        inline bool operator<(const Integer& other) {
            if (value.size() < other.value.size()) { return true; }

            if (value.size() > other.value.size()) { return false; }

            for (long unsigned int i = value.size() - 1; i > 0; i--) {
                if (value[i] < other.value[i]) { return true; }

                if (value[i] > other.value[i]) { return false; }
            }
            
            return false;
        }

        inline bool operator>(const Integer& other) {
            if (value.size() > other.value.size()) { return true; }

            if (value.size() < other.value.size()) { return false; }

            for (long unsigned int i = value.size() - 1; i > 0; i--) {
                if (value[i] > other.value[i]) { return true; }

                if (value[i] < other.value[i]) { return false; }
            }

            return false;
        }

        inline bool operator<=(const Integer& other) {
            return (*this < other) || (*this == other);
        }

        inline bool operator>=(const Integer& other) {
            return (*this > other) || (*this == other);
        }

        inline bool operator==(const Integer& other) {
            if (value.size() == other.value.size()) {
                for (long unsigned int i = 0; i < value.size(); ++i) {
                    if (value[i] != other.value[i]) { return false; }
                }
                return true;
            }
            return false;
        }

        inline bool operator!=(const Integer& other) {
            return !(*this == other);
        }

        // Value print
        friend std::ostream& operator<<(std::ostream& os, const Integer& val);
    };

    class Stack {
        std::stack<Integer> data;
    };
}    // namespace Glypho::Core