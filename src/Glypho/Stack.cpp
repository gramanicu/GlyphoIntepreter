/**
 * @file Stack.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Stack.hpp"

using namespace Glypho::Core;

Integer::Integer() { value.push_back(0); }

Integer::Integer(const std::string& value) {
    is_negative = false;
    if (value.at(0) == '-') { is_negative = true; }

    this->value.clear();
    for (unsigned long int id = value.size() - 1; id > 0; id--) {
        char c = value.at(id);
        if (c >= '0' && c <= '9') {
            this->value.push_back(c - '0');
        } else {
            this->value.clear();
        }
    }

    char c = value.at(0);
    if (c >= '0' && c <= '9') {
        this->value.push_back(c - '0');
    } else if(!is_negative) {
        this->value.clear();
    }
}

Integer::Integer(const Integer& other) {
    this->value.clear();
    this->is_negative = other.is_negative;

    if (other.value.size() != 0) {
        for (auto& val : other.value) { this->value.push_back(val); }
    }
}

Integer& Integer::operator=(const Integer& other) {
    this->value.clear();
    this->is_negative = other.is_negative;

    if (other.value.size() != 0) {
        for (auto& val : other.value) { this->value.push_back(val); }
    }

    return *this;
}

Integer Integer::operator++() {
    bool carry = true;
    unsigned long int id = 0;

    if (value.size() == 0) {
        value.push_back(1);
        return Integer(*this);
    }

    if (is_negative == true) {
        while (carry && id < value.size()) {
            if (value.at(id) == 0) {
                value.at(id) = 9;
                carry = true;
            } else {
                value.at(id) -= 1;
                carry = false;
            }

            id++;
        }

        if (value.at(value.size() - 1) == 0) { value.pop_back(); }
        if (value.size() == 0) { is_negative = false; }
    } else {
        while (carry && id < value.size()) {
            carry = false;
            value.at(id) += 1;

            if (value.at(id) == 10) {
                value.at(id) = 0;
                carry = true;
            }

            id++;
        }

        if (carry) { value.push_back(1); }
    }

    return Integer(*this);
}

Integer Integer::operator++(int) {
    bool carry = true;
    unsigned long int id = 0;
    Integer res(*this);

    if (value.size() == 0) {
        value.push_back(1);
        return res;
    }

    if (is_negative) {
        while (carry && id < value.size()) {
            if (value.at(id) == 0) {
                value.at(id) = 9;
                carry = true;
            } else {
                value.at(id) -= 1;
                carry = false;
            }

            id++;
        }

        if (value.at(value.size() - 1) == 0) { value.pop_back(); }
        if (value.size() == 0) { is_negative = false; }
    } else {
        while (carry && id < value.size()) {
            carry = false;
            value.at(id) += 1;

            if (value.at(id) == 10) {
                value.at(id) = 0;
                carry = true;
            }

            id++;
        }

        if (carry) { value.push_back(1); }
    }

    return res;
}

Integer Integer::operator--() {
    bool carry = true;
    unsigned long int id = 0;

    if (value.size() == 0) {
        value.push_back(1);
        is_negative = true;
        return Integer(*this);
    }

    if (is_negative) {
        while (carry && id < value.size()) {
            carry = false;
            value.at(id) += 1;

            if (value.at(id) == 10) {
                value.at(id) = 0;
                carry = true;
            }

            id++;
        }

        if (carry) { value.push_back(1); }
        if (value.size() == 0) { is_negative = true; }
    } else {
        while (carry && id < value.size()) {
            if (value.at(id) == 0) {
                value.at(id) = 9;
                carry = true;
            } else {
                value.at(id) -= 1;
                carry = false;
            }

            id++;
        }

        if (value.at(value.size() - 1) == 0) { value.pop_back(); }
    }

    return Integer(*this);
}

Integer Integer::operator--(int) {
    bool carry = true;
    unsigned long int id = 0;
    Integer res(*this);

    if (value.size() == 0) {
        value.push_back(1);
        is_negative = true;
        return res;
    }

    if (is_negative) {
        while (carry && id < value.size()) {
            carry = false;
            value.at(id) += 1;

            if (value.at(id) == 10) {
                value.at(id) = 0;
                carry = true;
            }

            id++;
        }

        if (carry) { value.push_back(1); }
        if (value.size() == 0) { is_negative = true; }
    } else {
        while (carry && id < value.size()) {
            if (value.at(id) == 0) {
                value.at(id) = 9;
                carry = true;
            } else {
                value.at(id) -= 1;
                carry = false;
            }

            id++;
        }

        if (value.at(value.size() - 1) == 0) { value.pop_back(); }
    }

    return res;
}

namespace Glypho::Core {
    Integer operator+(Integer l, const Integer& r) {
        // TODO - check signs and test
        uint8_t carry = 0;
        unsigned long int i;
        Integer other(r);

        if (l.value.size() < other.value.size()) {
            Integer aux = l;
            l = other;
            other = aux;
        }

        for (i = 0; i < other.value.size(); ++i) {
            l.value.at(i) += other.value.at(i) + carry;
            carry = l.value.at(i) / 10;
            l.value.at(i) %= 10;
        }

        while (carry != 0) {
            if (i != l.value.size()) {
                l.value.at(i) += carry;
                carry = l.value.at(i) / 10;
                l.value.at(i) %= 10;
            } else {
                l.value.push_back(carry);
                carry = 0;
            }

            i++;
        }

        return l;
    }

    Integer operator-(Integer l, const Integer& r) {
        uint8_t carry = 0;
        unsigned long int i;

        if(l.is_negative && r.is_negative) {
            // TODO - difference
        } else if (l.is_negative && !r.is_negative) {
            // TODO - remins negative, add values
        } else if (!l.is_negative && r.is_negative) {
            // TODO - remains positive, add values
        } else if (!l.is_negative && !r.is_negative) {
            // TODO - difference
        }

        return l;
    }

    Integer operator*(Integer l, const Integer& r) {
        // TODO - check signs and test
        for(Integer i("0"); i < r; i++) {
            l = l + l;
        }

        return l;
    }

    Integer operator/(Integer l, const Integer& r) {
        // TODO - check signs and test
        Integer div = l;
        Integer res("0");
        while(l > Integer("0")) {
            l = l - div;
            res = ++res;
        }

        return res;
    }

    Integer operator%(Integer l, const Integer& r) {
        // TODO - check signs and test
        Integer div = l;
        while(l - div > Integer("0")) {
            l = l - div;
        }

        return l;
    }

    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        if (i.value.size() > 0) {
            if (i.is_negative) { os << "-"; }

            for (unsigned long int id = i.value.size() - 1; id > 0; id--) {
                os << std::to_string(i.value.at(id));
            }
            os << std::to_string(i.value.at(0));
        } else {
            os << "0";
        }

        return os;
    }
}    // namespace Glypho::Core