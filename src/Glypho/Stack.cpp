/**
 * @file Stack.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Stack.hpp"

namespace Glypho::Core { 
        Stack::Stack() {
            data = std::list<Integer>();
        }

        void Stack::Push() {
            data.push_front(Integer("1"));
        }

        void Stack::Pop() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            data.pop_front();
        }

        Integer Stack::Peek() const {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            return data.front();
        }

        void Stack::Input(const Integer& value) {
            data.push_front(value);
        }

        Integer Stack::Output() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            Integer value = data.front();
            data.pop_front();
            return value;
        }

        void Stack::Dup() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            Integer value = data.front();
            data.push_front(value);
        }

        void Stack::Swap() {
            Helpers::MUST(data.size() >= 2, Throwable::message(Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE) + "\n");

            Integer value1 = data.front();
            data.pop_front();
            Integer value2 = data.front();
            data.pop_front();

            data.push_front(value1);
            data.push_front(value2);
        }

        void Stack::Rotate() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            Integer value = data.front();
            data.pop_front();
            data.push_back(value);
        }

        void Stack::ReverseRotate() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            Integer value = data.back();
            data.pop_back();
            data.push_front(value);
        }

        void Stack::Add() {
            Helpers::MUST(data.size() >= 2, Throwable::message(Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE) + "\n");

            Integer value1 = data.front();
            data.pop_front();
            Integer value2 = data.front();
            data.pop_front();

            data.push_back(value1 + value2);
        }

        void Stack::Multiply() {
            Helpers::MUST(data.size() >= 2, Throwable::message(Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE) + "\n");

            Integer value1 = data.front();
            data.pop_front();
            Integer value2 = data.front();
            data.pop_front();

            data.push_back(value1 * value2);
        }

        void Stack::Negate() {
            Helpers::MUST_NOT(data.size() == 0, Throwable::message(Throwable::RuntimeException::EMPTY_STACK) + "\n");

            Integer value = data.front();
            value = Integer("0") - value;

            data.pop_front();
            data.push_front(value);
        }

        std::vector<Integer> Stack::Out_K_Elems(const uint64_t count) {
            Helpers::MUST(data.size() >= count, Throwable::message(Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE) + "\n");

            std::vector<Integer> values;
            for(uint64_t i = 0; i < count; ++i) {
                values.push_back(data.front());
                data.pop_front();
            }

            return values;
        }
}