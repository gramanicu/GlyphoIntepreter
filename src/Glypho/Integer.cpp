/**
 * @file Integer.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief 
 * @copyright Copyright (c) 2020
 */


#include "Integer.hpp"

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
    } else if (!is_negative) {
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

Integer Integer::abs() const {
    Integer i(*this);
    i.is_negative = false;
    return i;
}

Integer Integer::neg() const {
    Integer i(*this);
    i.is_negative = true;
    return i;
}

void Integer::check_zero() {
    bool is_null = true;

    if (value.size() > 0) {
        for (auto& i : value) {
            if (i != 0) {
                is_null = false;
                break;
            }
        }
    }

    if (is_null) {
        value.clear();
        value.push_back(0);
    }
}

Integer Integer::sum(Integer l, Integer r) {
    bool carry = false;
    unsigned long int i = 0;
    Integer other(r);

    if (l < other) {
        Integer aux = l;
        l = other;
        other = aux;
    }

    do {
        if (i < other.value.size()) {
            l.value.at(i) += other.value.at(i) + carry;
            carry = l.value.at(i) > 9;
            l.value.at(i) %= 10;
        } else {
            if (i < l.value.size()) {
                l.value.at(i) += 1;
                carry = l.value.at(i) > 9;
                l.value.at(i) %= 10;
            } else {
                l.value.push_back(1);
                break;
            }
        }
        i++;
    } while (carry || i < other.value.size());

    return l;
}

Integer Integer::dif(Integer l, Integer r) {
    bool carry = false;
    unsigned long int i = 0;

    Integer other(r);
    bool negative = false;

    if (l < other) {
        Integer aux = l;
        l = other;
        other = aux;
        negative = true;
    }

    for (i = 0; i < other.value.size(); ++i) {
        l.value.at(i) += 10;
        l.value.at(i) -= other.value.at(i) - carry;
        carry = l.value.at(i) < 10;
        l.value.at(i) %= 10;
    }

    if (carry) {
        l.value.at(i)--;
        if (l.value.at(i) == 0) { l.value.pop_back(); }
    }

    l.check_zero();

    if (negative) return l.neg();
    return l;
}

namespace Glypho::Core {
    Integer operator+(Integer l, const Integer& r) {
        if (l.is_negative && !r.is_negative) {
            return Integer::dif(r.abs(), l.abs());
        } else if (!l.is_negative && r.is_negative) {
            return Integer::dif(l.abs(), r.abs());
        }

        if (l.is_negative) {
            return Integer::sum(l.abs(), r.abs()).neg();
        } else {
            return Integer::sum(l.abs(), r.abs());
        }
    }

    Integer operator-(Integer l, const Integer& r) {
        if (l.is_negative && !r.is_negative) {
            return (Integer::sum(l.abs(), r.abs()).neg());
        } else if (!l.is_negative && r.is_negative) {
            return (Integer::sum(l.abs(), r.abs()));
        }

        if (l.is_negative) {
            return Integer::dif(r.abs(), l.abs());
        } else {
            return Integer::dif(l.abs(), r.abs());
        }
    }

    Integer operator*(Integer l, const Integer& r) {
        // TODO - check signs and test
        bool switch_signs = false;
        if (l.is_negative != r.is_negative) { switch_signs = true; }

        Integer step = l.abs();
        Integer res("0");

        for (Integer i("0"); i < r.abs(); i++) { res = res + step; }

        if (switch_signs) return res.neg();

        return res;
    }

    Integer operator/(Integer l, const Integer& r) {
        Integer div = r.abs();
        Glypho::Helpers::MUST_NOT(
            (div == Integer("0")),
            Glypho::Throwable::message(
                Glypho::Throwable::RuntimeException::DIVISION_BY_0) +
                "\n");

        bool switch_signs = false;
        if (l.is_negative != r.is_negative) { switch_signs = true; }

        Integer res("0");
        l = l.abs();

        while (l - div >= Integer("0")) {
            l = l - div;
            res++;
        }

        if (switch_signs) return res.neg();
        return res;
    }

    Integer operator%(Integer l, const Integer& r) {
        Integer div = l / r;

        Integer remainder = l - (div * r);

        return remainder;
    }

    std::ostream& operator<<(std::ostream& os, const Integer& i) {
        if (i.value.size() > 1) {
            if (i.is_negative) { os << "-"; }

            for (unsigned long int id = i.value.size() - 1; id > 0; id--) {
                os << std::to_string(i.value.at(id));
            }
            os << std::to_string(i.value.at(0));
        } else {
            if (i.value.at(0) != 0) {
                if (i.is_negative) { os << "-"; }
                os << (int)i.value.at(0);
            } else {
                os << "0";
            }
        }

        return os;
    }
}    // namespace Glypho::Core