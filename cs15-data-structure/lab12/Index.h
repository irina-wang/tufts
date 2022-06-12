/*
 * Filename: Index.h
 * Contains: Interface of the Index class
 *           Each Index object contains a vector of filenames it has parsed
 *           and an unordered map that uses words as keys and a vector of 
             Entry objects as values.
 * Part of: Lab 12 for Comp15 
 *
 */

#ifndef INDEX_H
#define INDEX_H

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "DirNode.h"
#include "FSTree.h"
class Index {
private:
        /**
         * an Entry object: Stores the word verbatim, the lineno, the
         * file number (index into files array), and the position of its
         * sentence in the file.
         *
         */
        struct Entry {
                std::string    word;
                unsigned       lineno;
                size_t         fileno;
                std::streampos sentence;

                Entry(std::string newWord, unsigned newLineno,
                      std::streampos position, size_t new_fileno)
                    : word(newWord),
                      lineno(newLineno),
                      fileno(new_fileno),
                      sentence(position) {}
        };

        // A unordered_map (hash table) that uses strings as keys that "map" to
        // vectors of Entries
        std::unordered_map<std::string, std::vector<Entry>> entries;
        std::vector<std::string>                            files;

        /**
        * Function: lower
        * Parameters: string
        * Returns: modified version of same string
        * Does: takes in a string and returns the same string where all alpha 
        * characters have been made lowercase.
        * 
        */
        std::string lower(std::string s) const;

        /**
        * Function: cleanString
        * Parameters: string
        * Returns: modified version of same string
        * Does: removes leading and trailing non-alphanumeric characters from
        *       string.
        * 
        */
        std::string cleanString(std::string s) const;

        /**
        * Function: buildIndex
        * Parameters: root of FSTree to search, string representation of path 
                      prefix
        * Returns: void
        * Does: iterates through directory tree, and parses any files found
        * 
        */
        void buildIndex(DirNode *node, std::string dir);

        /*
        * Function: reportMatch
        * Parameters: Entry to print, ostream to print to
        * Returns: void
        * Does: prints out entry according to specification.
        * 
        */
        void reportMatch(const Entry &e, std::ostream &out) const;

        /*
        * Function: shouldAdd
        * Parameters: vector of Entrys for a given key, potential Entry to be 
                      added
        * Returns: bool
        * Does: checks whether another identical word on the same line was
         *        already added to the Index.
        * 
        */
        bool shouldAdd(const std::vector<Entry> &e, const Entry &toAdd) const;

        /*
        * Function: getPosition
        * Parameters: istream object
        * Returns: streampos
        * Does: gets the current position of the stream.
        * 
        */
        static std::streampos getPosition(std::istream &stream);

        /*
        * Function: parseFile
        * Parameters: name of file (a string) to be parsed
        * Returns: void
        * Does: parses every word of every line of a particular file and 
        * accounts for every instance of a word by creating a unique Entry 
        * object and storing said object in the Index (note: a word which 
        * appears several times in a line is only included once in the Index 
        * object).
        * 
        */
        void parseFile(const std::string &filename);

public:

        /*
        * Function: query
        * Parameters: string to query, ostream object to be written to
        * Returns: void
        * Does: searches the Index object to see if it contains any instances of the 
        * word to be queried... prints out all the Entry objects which describe unique 
        * locations of particular instances of the word.
        * 
        */
        void query(const std::string &toQuery, std::ostream &out) const;

        /*
        * Function: Index constructor
        * Parameters: name of rootDirectory(a string)
        * Returns: void
        * Does: creates a tree of DirNodes to represent the files and
        * subdirectories (and its contents) of a root directory.
        * 
        */
        Index(std::string rootDir);
};

#endif