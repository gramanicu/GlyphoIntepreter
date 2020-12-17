/**
 * @file InputParser.hpp
 * @author Grama Nicolae (gramanicu@gmail.com)
 * @brief Declares the InputParser, used by the interpreter to get the (encoded)
 * instructions from the code file (or a stream).
 * @copyright Copyright (c) 2020
 */
#pragma once

#include <fstream>
#include <vector>

#include "Helpers.hpp"

namespace Glypho::Core {
    class InputParser {
       private:
        /**
         * @brief Private constructor to disallow instantiation of this class
         */
        InputParser(){};

        /**
         * @brief Read Glypho code from an input stream
         *
         * @param input The stream
         * @return std::vector<std::string> An array of encoded instructions
         * (chars grouped 4 by 4)
         */
        static std::vector<std::string> read_data(std::istream& input);

       public:
        /**
         * @brief Read Glypho code from a file
         *
         * @param filename The path to the source code file
         * @return std::vector<std::string> An array of encoded instructions
         * (chars grouped 4 by 4)
         */
        static std::vector<std::string> read_data(std::string path);
    };
}    // namespace Glypho::Core