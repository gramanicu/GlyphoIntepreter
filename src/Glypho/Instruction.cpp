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

std::string Glypho::Core::encode_number_array(std::vector<Integer>& arr) {
    std::vector<char> encodes;
    std::string res = "";

    // Associated a number to each instruction integer
    char current_code = '0';
    for (int i = 0; i < 4; ++i) {
        int code = current_code++;
        
        for(int j = 0; j < i; ++j) {
            if(arr[i] == arr[j]) {
                code = encodes[j];
                break;
            }
        }

        encodes.push_back(code);
    }
    
    for(auto& c : encodes) {
        res += c;
    }

    return res;
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
    this->next_instruction_id = other.next_instruction_id;
    this->jump_id = other.jump_id;
}

Instruction& Instruction::operator=(const Instruction& other) {
    this->type = other.type;
    this->instruction_id = other.instruction_id;
    this->next_instruction_id = other.next_instruction_id;
    this->jump_id = other.jump_id;
    return *this;
}

long int Instruction::get_id() const { return instruction_id; }

long int Instruction::get_next_id() const { return next_instruction_id; }

void Instruction::set_next_id(const long int next_id) {
    next_instruction_id = next_id;
}

void Instruction::set_jump_id(const long int next_id) { jump_id = next_id; }

long int Instruction::get_jump_id() const { return jump_id; }

InstructionType Instruction::get_type() const { return type; }

void Instruction::execute(Stack* glypho_stack,
                          long int* program_instruction_id, std::vector<Core::Instruction>* program) {
    bool is_jumping = false;

    switch (type) {
        case InstructionType::Input: {
            // Read a number from stdin and add it to the stack
            std::string number;
            std::cin >> number;

            // Check if the input is a number
            Helpers::MUST(
                number.find_first_not_of("-0123456789") == std::string::npos,
                Throwable::message(
                    Throwable::RuntimeException::INPUT_NOT_VALID_INT) +
                    "\n",
                -2);

            glypho_stack->Input(Integer(number));
        } break;
        case InstructionType::Rot: {
            glypho_stack->Rotate();
        } break;
        case InstructionType::Swap: {
            glypho_stack->Swap();
        } break;
        case InstructionType::Push: {
            glypho_stack->Push();
        } break;
        case InstructionType::RRot: {
            glypho_stack->ReverseRotate();
        } break;
        case InstructionType::Dup: {
            glypho_stack->Dup();
        } break;
        case InstructionType::Add: {
            glypho_stack->Add();
        } break;
        case InstructionType::LBrace: {
            // Jump to associated RBrace if the top element is 0
            if (glypho_stack->Peek() == Integer("0")) { is_jumping = true; }
        } break;
        case InstructionType::Output: {
            std::cout << glypho_stack->Output() << "\n";
        } break;
        case InstructionType::Multiply: {
            glypho_stack->Multiply();
        } break;
        case InstructionType::Execute: {
            // Get the instruction from the stack
            std::vector<Integer> instr_code_arr = glypho_stack->Out_K_Elems(4);
            std::string instr_code = encode_number_array(instr_code_arr);
            long int new_code = program->size();

            // Add the new instruction to the program
            Instruction new_instruction(instr_code, new_code);

            // Link the new instruction to the others
            long int next_id;
            if(next_instruction_id != -1) {
                next_id = program->at(next_instruction_id).get_id();
            } else {
                next_id = -1;
            }

            next_instruction_id = new_code;
            new_instruction.set_next_id(next_id);
            new_instruction.set_jump_id(next_id);

            program->push_back(new_instruction);
        } break;
        case InstructionType::Negate: {
            glypho_stack->Negate();
        } break;
        case InstructionType::Pop: {
            glypho_stack->Pop();
        } break;
        case InstructionType::RBrace: {
            // Jump to associated LBrace if the top element is 0
            // If the code jumped to this brace, the stack should not have
            // changed, so don't have to jump back to the opened brace
            if (glypho_stack->Peek() != Integer("0")) {
                is_jumping = true;
            }
        } break;
        default: { /* NOP */
        } break;
    }

    if (is_jumping) {
        *program_instruction_id = jump_id;
    } else {
        *program_instruction_id = next_instruction_id;
    }
}

namespace Glypho::Core {
    std::ostream& operator<<(std::ostream& os, const Instruction& i) {
        os << instruction_name(i.type);
        return os;
    }
}    // namespace Glypho::Core