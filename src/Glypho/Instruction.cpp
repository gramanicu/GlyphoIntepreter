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

std::string Glypho::Core::encode_number_array(std::vector<long long int>& arr) {
    std::vector<char> encodes;
    std::string res = "";

    // Associated a number to each instruction integer
    char current_code = '0';
    for (int i = 0; i < 4; ++i) {
        int code = current_code++;

        for (int j = 0; j < i; ++j) {
            if (arr[i] == arr[j]) {
                code = encodes[j];
                break;
            }
        }

        encodes.push_back(code);
    }

    for (auto& c : encodes) { res += c; }

    return res;
}

Instruction::Instruction()
    : type(InstructionType::NOP),
      instruction_id(-1),
      next_instruction_id(-1),
      jump_id(-1),
      parent_exec(-1) {}

Instruction::Instruction(const std::string& encoded_instruction,
                         const long int id)
    : type(InstructionType::NOP),
      instruction_id(id),
      next_instruction_id(-1),
      jump_id(-1),
      parent_exec(id) {
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
    this->parent_exec = other.parent_exec;
}

Instruction& Instruction::operator=(const Instruction& other) {
    this->type = other.type;
    this->instruction_id = other.instruction_id;
    this->next_instruction_id = other.next_instruction_id;
    this->jump_id = other.jump_id;
    this->parent_exec = other.parent_exec;
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

void Instruction::set_parent_exec(const long int parent_exec_id) {
    parent_exec = parent_exec_id;
}

long int Instruction::get_parent_exec_id() const { return parent_exec; }

void Instruction::execute(Stack* glypho_stack, long int* program_instruction_id,
                          std::vector<Core::Instruction>* program,
                          const int base) const {
    bool is_jumping = false;
    int next_instr_id = this->get_next_id();

    switch (type) {
        case InstructionType::Input: {
            // Read a number from stdin and add it to the stack
            std::string number;
            std::cin >> number;

            // Parse the input (change from original base to base 10)
            try {
                stoll(number, nullptr, base);
            } catch (const std::invalid_argument&) {
                Helpers::MUST(
                    false,
                    Throwable::message(
                        Throwable::RuntimeException::INPUT_NOT_VALID_INT,
                        this->get_id()) +
                        "\n",
                    -2);
            } catch (const std::out_of_range&) {
                // Helpers::MUST(false, "OUT OF RANGE", -2);
            }

            glypho_stack->Input(Helpers::switchFromBase(base, number));
        } break;
        case InstructionType::Rot: {
            glypho_stack->Rotate(get_id());
        } break;
        case InstructionType::Swap: {
            glypho_stack->Swap(get_id());
        } break;
        case InstructionType::Push: {
            glypho_stack->Push();
        } break;
        case InstructionType::RRot: {
            glypho_stack->ReverseRotate(get_id());
        } break;
        case InstructionType::Dup: {
            glypho_stack->Dup(get_id());
        } break;
        case InstructionType::Add: {
            glypho_stack->Add(get_id());
        } break;
        case InstructionType::LBrace: {
            // Jump to associated RBrace if the top element is 0
            if (glypho_stack->Peek(get_id()) == 0) { is_jumping = true; }
        } break;
        case InstructionType::Output: {
            std::cout << Helpers::switchToBase(base,
                                               glypho_stack->Output(get_id()))
                      << "\n";
        } break;
        case InstructionType::Multiply: {
            glypho_stack->Multiply(get_id());
        } break;
        case InstructionType::Execute: {
            // Get the instruction from the stack
            std::vector<long long int> instr_code_arr =
                glypho_stack->Out_K_Elems(4, get_parent_exec_id());
            std::string instr_code = encode_number_array(instr_code_arr);
            long int new_code = program->size();

            // Add the new instruction to the program
            Instruction new_instruction(instr_code, new_code);
            new_instruction.set_parent_exec(get_parent_exec_id());

            // Check if we can get this instruction from an execute
            Helpers::MUST_NOT(
                (new_instruction.get_type() == InstructionType::RBrace ||
                 new_instruction.get_type() == InstructionType::LBrace),
                Throwable::message(Throwable::RuntimeException::INVALID_EXECUTE,
                                   get_id()) +
                    "\n",
                -2);

            // Link the new instruction to the others
            long int next_id;
            if (next_instruction_id != -1) {
                next_id = program->at(next_instruction_id).get_id();
            } else {
                next_id = -1;
            }

            next_instr_id = new_code;
            new_instruction.set_next_id(next_id);
            new_instruction.set_jump_id(next_id);

            program->push_back(new_instruction);
        } break;
        case InstructionType::Negate: {
            glypho_stack->Negate(get_id());
        } break;
        case InstructionType::Pop: {
            glypho_stack->Pop(get_id());
        } break;
        case InstructionType::RBrace: {
            // Jump to associated LBrace if the top element is 0
            // If the code jumped to this brace, the stack should not have
            // changed, so don't have to jump back to the opened brace
            if (glypho_stack->Peek(get_jump_id()) != 0) { is_jumping = true; }
        } break;
        default: { /* NOP */
        } break;
    }

    if (is_jumping) {
        *program_instruction_id = jump_id;
    } else {
        *program_instruction_id = next_instr_id;
    }
}

namespace Glypho::Core {
    std::ostream& operator<<(std::ostream& os, const Instruction& i) {
        os << instruction_name(i.type);
        return os;
    }
}    // namespace Glypho::Core