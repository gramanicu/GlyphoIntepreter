/**
 * @file Instruction.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <math.h>

#include <ostream>
#include <string>
#include <unordered_map>

#include "Helpers.hpp"
#include "Stack.hpp"

namespace Glypho::Core {
    enum class InstructionType {
        NOP,
        Input,
        Rot,
        Swap,
        Push,
        RRot,
        Dup,
        Add,
        LBrace,
        Output,
        Multiply,
        Execute,
        Negate,
        Pop,
        RBrace
    };

    /**
     * @brief Returns the name of the specified instruction
     *
     * @param type The type of instruction
     * @return std::string The name
     */
    std::string instruction_name(InstructionType type);

    /**
     * @brief Converts the number array to a string, by assigning a char to each
     * unique element in the array This is used for the instructions extracted
     * from the glypho stack
     * @param arr The array of numbers
     * @return std::string The encoded instuction
     */
    std::string encode_number_array(std::vector<long long int>& arr);

    class Instruction {
       private:
        InstructionType type;
        long int instruction_id;
        long int next_instruction_id;
        long int jump_id;    // Used by braces to jump
        long int
            parent_exec;    // Used by nested executes, to know the parent id

       public:
        /**
         * @brief Construct a new Instruction object
         * Empty constructor
         */
        Instruction();

        /**
         * @brief Construct a new Instruction object
         *
         * @param encoded_instruction The 4-char instruction code
         * @param id The id of the instruction
         */
        Instruction(const std::string& encoded_instruction, const long int id);

        /**
         * @brief Copy-Constructs a new Instruction object
         *
         * @param other
         */
        Instruction(const Instruction& other);

        /**
         * @brief Assignment operator
         *
         * @param other The other object
         * @return Instruction& The new object
         */
        Instruction& operator=(const Instruction& other);

        /**
         * @brief Operator overload for output streams
         *
         */
        friend std::ostream& operator<<(std::ostream& os, const Instruction& i);

        /**
         * @brief Get the id of the instruction
         *
         * @return long int The id
         */
        long int get_id() const;

        /**
         * @brief Get the id of the next instruction
         *
         * @return long int The id
         */
        long int get_next_id() const;

        /**
         * @brief Get the id of the next instruction (if takes a jump)
         *
         * @return long int The id
         */
        long int get_jump_id() const;

        /**
         * @brief Set the id of the next instruction
         *
         * @param next_id The id
         */
        void set_next_id(const long int next_id);

        /**
         * @brief Set the id of the next instruction (if takes a jump)
         *
         * @param next_id The id
         */
        void set_jump_id(const long int next_id);

        /**
         * @brief Set the parent exec instruction id
         *
         * @param parent_exec_id The id of the parent
         */
        void set_parent_exec(const long int parent_exec_id);

        /**
         * @brief Get the type of the instruction
         *
         * @return InstructionType The type
         */
        InstructionType get_type() const;

        /**
         * @brief Get the parent exec instruction id
         *
         * @return long int The id
         */
        long int get_parent_exec_id() const;

        /**
         * @brief Executes the instructions
         *
         * @param glypho_stack The glypho stack the program uses
         * @param instruction_id The current instruction id in the program
         * @param program The program (instruction vector)
         * @param base The base of the numbers that can be read from stdin
         */
        void execute(Stack* glypho_stack, long int* instruction_id,
                     std::vector<Core::Instruction>* program,
                     const int base) const;
    };
}    // namespace Glypho::Core