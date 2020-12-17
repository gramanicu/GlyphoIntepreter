/**
 * @file Instruction.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Instruction.hpp"

using namespace Glypho::Core;

std::string Glypho::Core::instruction_name(InstructionType type) {
    switch (type) {
        case InstructionType::NOP: return "NOP";
        case InstructionType::Input: return "Input";
        case InstructionType::Rot: return "Rot";
        case InstructionType::Swap: return "Swap";
        case InstructionType::Push: return "Push";
        case InstructionType::RRot: return "RRot";
        case InstructionType::Dup: return "Dup";
        case InstructionType::Add: return "Add";
        case InstructionType::LBrace: return "L-brace";
        case InstructionType::Output: return "Output";
        case InstructionType::Multiply: return "Multiply";
        case InstructionType::Execute: return "Execute";
        case InstructionType::Negate: return "Negate";
        case InstructionType::Pop: return "Pop";
        case InstructionType::RBrace: return "R-brace";
    }
    return "";
}

Instruction::Instruction() : type(InstructionType::NOP), instruction_id(-1) {}

Instruction::Instruction(const std::string& encoded_instruction,
                         const long int id)
    : instruction_id(id) {
    std::unordered_map<char, int> associated_code;
    std::unordered_map<char, bool> appeared;

    // Associated a number to each instruction character
    int current_code = 0;
    for (char c : encoded_instruction) {
        if (!appeared[c]) {
            associated_code[c] = current_code++;
            appeared[c] = true;
        }
    }

    // Decode the instruction
    int decoded_instruction = 0;
    int power = 3;
    for (char c : encoded_instruction) {
        decoded_instruction += pow(3, power--) * associated_code[c];
    }

    // Set the instruction type
    switch (decoded_instruction) {
        case 0: type = InstructionType::NOP; break;
        case 1: type = InstructionType::Input; break;
        case 3: type = InstructionType::Rot; break;
        case 4: type = InstructionType::Swap; break;
        case 5: type = InstructionType::Push; break;
        case 9: type = InstructionType::RRot; break;
        case 10: type = InstructionType::Dup; break;
        case 11: type = InstructionType::Add; break;
        case 12: type = InstructionType::LBrace; break;
        case 13: type = InstructionType::Output; break;
        case 14: type = InstructionType::Multiply; break;
        case 15: type = InstructionType::Execute; break;
        case 16: type = InstructionType::Negate; break;
        case 17: type = InstructionType::Pop; break;
        case 18: type = InstructionType::RBrace; break;
    }
}

Instruction::Instruction(const Instruction& other) {
    this->type = other.type;
    this->instruction_id = other.instruction_id;
}

Instruction& Instruction::operator=(const Instruction& other) {
    this->type = other.type;
    this->instruction_id = other.instruction_id;
    return *this;
}

long int Instruction::get_id() const { return instruction_id; }

long int Instruction::get_next_id() const { return next_instruction_id; }

void Instruction::set_next_id(const long int next_id) {
    next_instruction_id = next_id;
}

InstructionType Instruction::get_type() const { return type; }

namespace Glypho::Core {
    std::ostream& operator<<(std::ostream& os, const Instruction& i) {
        os << instruction_name(i.type);
        return os;
    }
}    // namespace Glypho::Core