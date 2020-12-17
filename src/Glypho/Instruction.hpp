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

    class Instruction {
       private:
        InstructionType type;
        long int instruction_id;
        long int next_instruction_id;

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
         * @brief Set the id of the next instruction
         *
         * @param next_id The id
         */
        void set_next_id(const long int next_id);

        /**
         * @brief Get the type of the instruction
         *
         * @return InstructionType The type
         */
        InstructionType get_type() const;
    };
}    // namespace Glypho::Core