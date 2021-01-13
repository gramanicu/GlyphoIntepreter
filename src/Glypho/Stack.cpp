/**
 * @file Stack.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Stack.hpp"

namespace Glypho::Core {
    Stack::Stack() { data = std::list<long long int>(); }

    Stack::Stack(const Stack& other) { this->data = other.data; }

    Stack& Stack::operator=(const Stack& other) {
        this->data = other.data;
        return *this;
    }

    void Stack::Push() { data.push_back(1); }

    void Stack::Pop(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        data.pop_back();
    }

    long long int Stack::Peek(long int id) const {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        return data.back();
    }

    void Stack::Input(const long long int& value) { data.push_back(value); }

    long long int Stack::Output(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        long long int value = data.back();
        data.pop_back();
        return value;
    }

    void Stack::Dup(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        long long int value = data.back();
        data.push_back(value);
    }

    void Stack::Swap(long int id) {
        Helpers::MUST(
            data.size() >= 2,
            Throwable::message(
                Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE, id) +
                "\n",
            -2);

        long long int value1 = data.back();
        data.pop_back();
        long long int value2 = data.back();
        data.pop_back();

        data.push_back(value1);
        data.push_back(value2);
    }

    void Stack::Rotate(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        long long int value = data.back();
        data.pop_back();
        data.push_front(value);
    }

    void Stack::ReverseRotate(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        long long int value = data.front();
        data.pop_front();
        data.push_back(value);
    }

    void Stack::Add(long int id) {
        Helpers::MUST(
            data.size() >= 2,
            Throwable::message(
                Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE, id) +
                "\n",
            -2);

        long long int value1 = data.back();
        data.pop_back();
        long long int value2 = data.back();
        data.pop_back();

        data.push_back(value1 + value2);
    }

    void Stack::Multiply(long int id) {
        Helpers::MUST(
            data.size() >= 2,
            Throwable::message(
                Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE, id) +
                "\n",
            -2);

        long long int value1 = data.back();
        data.pop_back();
        long long int value2 = data.back();
        data.pop_back();

        data.push_back(value1 * value2);
    }

    void Stack::Negate(long int id) {
        Helpers::MUST_NOT(
            data.size() == 0,
            Throwable::message(Throwable::RuntimeException::EMPTY_STACK, id) +
                "\n",
            -2);

        long long int value = data.back();
        value = 0 - value;

        data.pop_back();
        data.push_back(value);
    }

    std::vector<long long int> Stack::Out_K_Elems(const uint64_t count,
                                                  long int id) {
        Helpers::MUST(
            data.size() >= count,
            Throwable::message(
                Throwable::RuntimeException::INSUFFICIENT_STACK_SIZE, id) +
                "\n",
            -2);

        std::vector<long long int> values;
        for (uint64_t i = 0; i < count; ++i) {
            values.push_back(data.back());
            data.pop_back();
        }

        return values;
    }
}    // namespace Glypho::Core