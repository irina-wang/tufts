/*
 * Filename: main.cpp
 * Contains: Driver for lab session about using STL's unordered map COMP15
 * Part of: Lab 12 for Comp15 
 *
 */

#include "Index.h"

int main(int argc, char *argv[]) {
        std::string input;

        if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " filename\n";
                return 1;
        }

        Index index(argv[1]);

        while (std::cout << "Query: ", std::cin >> input) {
                if (input == "@q" or input == "@quit")
                        break;
                index.query(input, std::cout);
        }

        std::cout << "Goodbye! Thank you and have a nice day.\n";
        return 0;
}