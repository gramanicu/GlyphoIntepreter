/**
 * @file Interpreter.cpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */

#include "Interpreter.hpp"

using namespace Glypho;

Interpreter::Interpreter()
    : code_path(""),
      input_numbers_base(Constants::DEFAULT_INPUT_BASE),
      code_loaded(false) {
    glypho_stack = Core::Stack();
}

Interpreter::Interpreter(const std::string& path, const unsigned int base)
    : code_path(path), input_numbers_base(base), code_loaded(false) {
    glypho_stack = Core::Stack();
}

Interpreter::Interpreter(const Interpreter& other)
    : code_path(other.code_path),
      input_numbers_base(other.input_numbers_base),
      code_loaded(false),
      glypho_stack(other.glypho_stack) {}

Interpreter& Interpreter::operator=(const Interpreter& other) {
    this->code_path = other.code_path;
    this->input_numbers_base = other.input_numbers_base;
    this->code_loaded = false;
    this->glypho_stack = other.glypho_stack;

    return *this;
}

void Interpreter::load_program() {
    // Read encoded instructions from the file
    std::vector<std::string> e_instructions =
        Core::InputParser::read_data(code_path);

    // Initialise the space to store the instructions
    int instruction_count = e_instructions.size();
    program = std::vector<Core::Instruction>(instruction_count);

    // Multithreaded instruction decoding
    std::vector<std::thread> decoding_threads;

    // Get the number of available threads (at least 1)
    int thread_count =
        std::max((unsigned int)1, std::thread::hardware_concurrency());

    for (int thread_id = 0; thread_id < thread_count; ++thread_id) {
        // Split the program into segments, once to each thread
        int start = thread_id * (double)instruction_count / thread_count;
        int end = std::min(
            (int)(((long int)thread_id + 1) * (double)instruction_count / thread_count),
            instruction_count);

        // The thread function that decodes the instructions
        auto decoder = [start, end, &e_instructions, &program = program]() {
            for (int id = start; id < end; ++id) {
                program.at(id) = Core::Instruction(e_instructions[id], id);
            }
        };

        decoding_threads.push_back(std::thread(decoder));
    }

    // Wait for the decoding to finish
    for (auto& thread : decoding_threads) { thread.join(); }

    // Analyse the code for SyntaxErrors (braces matching)
    // and "link" the instructions (set the id of the next instruction)
    using namespace Throwable;
    std::stack<long int> braces_stack;

    for (auto& instruction : program) {
        using namespace Core;

        InstructionType type = instruction.get_type();

        if (type == InstructionType::LBrace) {
            long int next_id = instruction.get_id() + 1;
            instruction.set_next_id(next_id);

            braces_stack.push(instruction.get_id());
        } else if (type == InstructionType::RBrace) {
            long int next_id = instruction.get_id() + 1;
            instruction.set_next_id(next_id);

            // Check if there are any opened braces
            Helpers::MUST_NOT(
                braces_stack.empty(),
                message(SyntaxError::OPENING_BRACE_EXPECTED) + "\n");

            int block_start = braces_stack.top();
            int block_end = instruction.get_id();
            braces_stack.pop();

            // Process code block (link the two braces)
            instruction.set_jump_id(block_start);
            program.at(block_start).set_jump_id(block_end);

            if (next_id >= instruction_count) {
                instruction.set_next_id(-1);
            }
        } else {
            long int next_id = instruction.get_id() + 1;

            // If we have not reached the end of the program
            if (next_id < instruction_count) {
                instruction.set_next_id(next_id);
                instruction.set_jump_id(next_id);
            } else {
                instruction.set_next_id(-1);
                instruction.set_jump_id(-1);
            }
        }
    }

    // Check that all braces are closed
    Helpers::MUST(braces_stack.empty(),
                  message(SyntaxError::CLOSING_BRACE_EXPECTED) + "\n");

    // The code is loaded, sa we can run it
    code_loaded = true;
}

void Interpreter::run_program() {
    if (!code_loaded) exit(-1);

    // Start the program execution
    long int instruction_id = 0;
    uint64_t instructions_exec = 0;

    // -1 instruction id means there is no other instruction
    while (instruction_id != -1) {
        instructions_exec++;
        program.at(instruction_id).execute(&glypho_stack, &instruction_id, &program);

        // To stop infinite looping
        // if(instructions_exec > 1000) {
        //     return;
        // }
    }
}