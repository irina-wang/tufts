/*
 * SequenceMatch.h
 * Comp15
 * Spring 2019
 * proj1
 *
 * Author : Mengqi Irina Wang
 * Date: 3/12/2019
 */


#ifndef SEQUENCEMATCH_H_
#define  SEQUENCEMATCH_H_

#include <iostream>
#include <fstream>

class SequenceMatch
{
public:
    
    struct TrieNode
    {  
        TrieNode *children[5];
    };
    
    SequenceMatch(std::ifstream &infile, std::ofstream &Passfile); 
    ~SequenceMatch(); // destructor

    void command(); 
    void insert(std::string sequence);
    std::string query(std::string sequence) const; 
    bool prefix_query(std::string prefix) const;
    void remove(std::string sequence);
    void print() const; 
    void clear();
    int numOfnodes() const;
       

private:
    TrieNode *root;

    static char int2char(int index);
    static int char2int(char acid);

    bool insert(TrieNode *lead, std::string seq2Bsearched);
    int numOfnodes(TrieNode *cur) const;
    void print(TrieNode *start, std::string sequence) const;
    bool remove(TrieNode *lead, std::string seq);
    void clear(TrieNode *curr);
    void delete_node(TrieNode *&node);
    std::string query(TrieNode *prev, TrieNode *curr, std::string sequence, 
    std::string remain) const;
    void switch_file(std::string filename);

    // Helper Functions
    std::string query_return(TrieNode *curr, std::string sequence) const;
    TrieNode *newTrieNode();
    TrieNode *search(TrieNode *curr, std::string sequence) const;
    static std::string query_compare(std::string s1, std::string s2);

    
    static int matchnessExam(std::string prefix, std::string matched_string, 
                                std::string original_seq);
    static std::string return_prefix(std::string matched_string, 
                                    std::string original_seq);

    // Deciphering tool 
    static const char END = '$';
    static const char ADENINE = 'A';
    static const char CYTOSINE = 'C';
    static const char GUANINE = 'G';
    static const char THYMINE = 'T';
    
    static const int END_IDX = 0;
    static const int ADENINE_IDX = 1;
    static const int CYTOSINE_IDX = 2;
    static const int GUANINE_IDX = 3;
    static const int THYMINE_IDX = 4;

    // Files
    std::ifstream &inFile;
    std::ofstream &passfile;
};

#endif