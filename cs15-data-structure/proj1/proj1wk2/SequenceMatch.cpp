
/*
 * SequenceMatch.cpp
 * Comp15
 * Spring 2019
 * proj1
 *
 * Author : Mengqi Irina Wang
 * Date: 3/12/2019
 */


#include "SequenceMatch.h"
#include <cmath>

using namespace std;

// Constructor
SequenceMatch::SequenceMatch(ifstream &infile, ofstream &Passfile) : 
    inFile(infile), passfile(Passfile)
{
    root = NULL;
}

// Destructor
SequenceMatch::~SequenceMatch()
{
    if(root != NULL)
        clear(root);
}

// clear - PUBLIC
//   clear the whole structure
// 
// Parameter : none
// Returns   : none
// Does      : clear the nodes of the entire structure
// Note      : called by destructor; only used for deleting the entire 
//             structure
void SequenceMatch::clear()
{
    clear(root);
    numOfnodes(); // print
}

// clear - PRIVATE
//   the recursive herlper function to clear the whole structure
// 
// Parameter : TrieNode pointer, curr that points to the structure
// Returns   : none
// Does      : clear the nodes of the entire structure
// Note      : only used to clear the whole structure
void SequenceMatch::clear(TrieNode *curr)
{
    if(curr == NULL){
            return;
    } else {
        for(int i = 0; i < 5; i++) {
            clear(curr->children[i]);
        }
        delete curr;
    }
    root = NULL; // set root to NULL
}

// command - PUBLIC
//   The general function that takes in all the commands and sequence 
//   from the file
//
// Parameter : none
// Return    : none
// Does      : Distinguishes the command by its first string and then calls the 
//             corresbonding functions to move the react to the command
// Note      : none
void SequenceMatch::command()
{ 
    string determine_command, sequence, filename;
    if (!inFile.is_open()) {
        cerr << "ERROR: File cannot be opened" << endl;
        exit(1);
    }
    while(inFile >> determine_command) {
        if(determine_command == "i" or determine_command == "I"){ // Insert
            inFile >> sequence;
            insert(sequence);
        } else if(determine_command == "Q" or determine_command == "q"){// Query
            inFile >> sequence;
            string similar_seq = query(sequence);
        } else if(determine_command == "pq" or determine_command == "PQ"
        or determine_command == "Pq" or determine_command == "pQ"){ //Prfx_Query
            inFile >> sequence;
            prefix_query(sequence);
        } else if(determine_command == "r" or determine_command == "R"){//Remove
            inFile >> sequence;
            remove(sequence);
        } else if(determine_command == "n" or determine_command == "N"){  
            numOfnodes();
        } else if(determine_command == "p" or determine_command == "P"){ //print
            print();
        } else if(determine_command == "d" or determine_command == "D"){//delete
            clear(); 
        } else if(determine_command == "f" or determine_command == "F"){ 
            inFile >> filename;
            switch_file(filename);
        } else
            passfile << "ERROR: invalid input" << endl;
    }
}

// switch_file - PRIVATE 
//   The function that changes the output file
//
// Parameter : filename
// Return    : none
// Does      : close the original file, and then open a new output file
// Note      : none
void SequenceMatch::switch_file(string filename)
{
    passfile.close();
    passfile.open(filename);
    passfile << "Output file has been changed to newfile.txt" << endl;
}

// insert - PUBLIC  
//   The function that inserts sequence into the structure
//
// Parameter : string, sequence to insert
// Return    : none
// Does      : inserting the sequence into the structure 
// Note      : call a helper function 
void SequenceMatch::insert(string sequence) 
{
     
    if(insert(root, sequence))
        passfile << sequence << " inserted" << endl;
    else
        passfile << sequence << " was previously inserted" << endl;
}

// insert - PRIVATE  
//   The helper function that inserts sequence into the structure
//
// Parameter : TrieNode pointer lead, which 
//             string sequence, seq2Bsearched
// Return    : boolean, true if it's successfully inserted
//                      false if it's not inserted
// Does      : inserting the sequence into the structure
// Note      : none
bool SequenceMatch::insert(TrieNode *lead, string seq2Bsearched)
{
    if (root == NULL){
        root = newTrieNode();
        lead = root; // update the lead pointer
    }
    if (seq2Bsearched == ""){
        if (lead->children[char2int(END)] == NULL) {
            lead->children[char2int(END)] = newTrieNode();
            return true;
        } else {
            return false;
        }
    } else {
        char head;
	    head = seq2Bsearched[0]; // head to search
	    seq2Bsearched = seq2Bsearched.substr(1,seq2Bsearched.length());

        if(lead->children[char2int(head)] == NULL) {
            lead->children[char2int(head)] = newTrieNode();
        }
        return insert(lead->children[char2int(head)], seq2Bsearched);
    }
    return false;
}

// query - PUBLIC  
//   The function that finds the most similar sequence
//
// Parameter : string sequence, sequence to be searched
// Return    : string sequence, sequence that is the most similar sequence 
//             to the given sequence
// Does      : inserting the sequence into the structure 
// Note      : call a helper function 
string SequenceMatch::query(string sequence) const
{
    string result = query(NULL, root, "", sequence);
    string prefix = return_prefix(result, sequence);
    if (matchnessExam(prefix,result,sequence) == 0) {
        passfile << sequence << ": No match found" << endl;
    } else {
        passfile << "Match found: " << result << " "
            << matchnessExam(prefix,result,sequence) <<  "%" << endl;
    }
    return result;
}

// query - PRIVATE 
//   The function that finds the most similar sequence
//
// Parameter : TrieNode pointer, prev, pointer to the previous pointer
//             TrieNode pointer, curr, pointer to the current pointer
//             string sequence, sequence we've get so far
//             string remain, sequence that's remain to be add to "sequence" to
//                            search for 
// Return    : string sequence, sequence that is the most similar sequence 
//             to the given sequence
// Does      : search for the maximum matched letters, and then find the 
//             most similar sequence to the given sequence
// Note      : call helper function query_return
string SequenceMatch::query(TrieNode *prev, TrieNode *curr, 
                            string sequence, string remain) const
{
    if(remain == ""){
        return query_return(curr, sequence);
    } else if (curr == NULL){
        return query_return(prev, sequence.substr(0,sequence.size() - 1));
    } else {
        char head = remain[0];
        remain = remain.substr(1,remain.length());
        sequence += head; // add head to the sequence

        string result = query(curr, curr->children[char2int(head)], sequence, 
                                                                        remain);
        return result;
    }   
}

// query_return - PRIVATE 
//   The helper function that finds the suffix that makes the sequence most 
//   similar to the given one
//
// Parameter : TrieNode pointer, curr, pointer to the current pointer
//             string sequence, sequence to add to
// Return    : string sequence, sequence 
// Does      : compare different suffix and return the one that matches 
//             the original list the most
// Note      : none
string SequenceMatch::query_return(TrieNode *curr, string sequence) const
{
    if (curr == NULL) {
        return "#"; 
    } else if(curr->children[0] != NULL) {
        return sequence; 
    } else {
        string result = "#";
        for (int i = 1; i < 5; i++) {
            if(curr->children[i] != NULL) {
                string curr_str = query_return(curr->children[i],
                                               sequence + int2char(i));
                result = query_compare(result, curr_str); // compare the result
            }
        }
        return result;
    }
}

// query_compare - PRIVATE 
//   The helper function that compare two strings and find the one that is most 
//   similar to the original list
//
// Parameter : string sequence, s1
//             string sequence, s2
// Return    : string sequence, sequence that matches the original one the most
// Does      : compare different suffix and return the one that is most 
//             similar to the original list
// Note      : none
string SequenceMatch::query_compare(string s1, string s2)
{
    if (s1 == "#") { // when string is empty
        return s2; 
    } else if (s2 == "#") {
        return s1;
    } else if (s1.size() < s2.size()) { // compare size first
        return s1;
    } else if (s1.size() > s2.size()) {
        return s2;
    } else if (s1 < s2) { // compare letter's order
        return s1;
    } else {
        return s2;
    }
}

// query_compare - PRIVATE 
//   The helper function that compute the matchness
//
// Parameter : string prefix,  
//             string matched_string
//             string original_seq
// Return    : int, the percentage that two sequence matched
// Does      : compare the size of the original and string size, store the 
//             larger one in len_seq, and use the size of prefix to divide 
//             len_seq to return the matchness
// Note      : none
int SequenceMatch::matchnessExam(string prefix, string matched_string, 
                                            string original_seq)
{
    int len_seq = max(original_seq.size(), matched_string.size());
    return round( (double) prefix.size() / len_seq * 100);
}

// return_prefix - PRIVATE 
//   The helper function that return the prefix 
//
// Parameter : string matched_string
//             string original_seq
// Return    : string, the matched letters in original list and the sequence 
//             that we found
// Does      : compare letters one by one and then return the sequence of all
//             matched letters
// Note      : none
string SequenceMatch::return_prefix(string matched_string,string original_seq)
{
    string prefix;
    int minimum_len = min(matched_string.size(), original_seq.size());
    for (int i = 0; i < minimum_len; i++) {
        if (matched_string[i] == original_seq[i]) {
            prefix += original_seq[i];
        } else {
            break;
        }
    }
    return prefix;
}

// prefix_query - PUBLIC  
//   The function that finds all the sequences that contain the same prefix
//
// Parameter : string prefix, prefix to be searched
// Return    : string sequence, sequence that is the most similar sequence 
//             to the given sequence
// Does      : inserting the sequence into the structure 
// Note      : call a helper function 
bool SequenceMatch::prefix_query(string prefix) const
{
    if(search(root, prefix) == NULL) {
        passfile << prefix << ": No match found" << endl;
        return false;
    } else {
        print(search(root, prefix), prefix);
        return true;
    }
}

// search - PRIVATE  
//   The function that searches the sequences from current pointer
//
// Parameter : TrieNode pointer, curr, place to start searching
//             string sequence, string to be searches
// Return    : TrieNode pointer, pointer to the last letter in the sequence
// Does      : tranverse through the structure from curr to look for the 
//             sequence, and return the pointer to the last letter if found
// Note      : none
SequenceMatch::TrieNode *SequenceMatch::search(TrieNode *curr, string sequence) 
const
{
    if (curr == NULL){
        return NULL;
    }
    if (sequence == ""){
        if (curr->children[char2int(END)] == NULL) { // search for $ sign
            return NULL;
        } else {
            return curr;
        }
    } else {
        char head;
	    head = sequence[0]; // search that
	    sequence = sequence.substr(1,sequence.length());

        return search(curr->children[char2int(head)], sequence);
    }
}

// remove - PUBLIC 
//   The function that removes a sequence 
//
// Parameter : string sequence, sequence to be removed
// Return    : none
// Does      : call a helper function to recursively remove a sequence
// Note      : none
void SequenceMatch::remove(string sequence)
{
    if(remove(root, sequence)) {
        passfile << sequence << " removed" << endl;
    } else
        passfile << sequence << ": No match found" << endl;
         
}

// remove - PRIVATE
//   The function that removes a sequence 
//
// Parameter : TrieNode lead, the pointer to the node that we should start 
//             removing from;  sequence, sequence to be removed
// Return    : boolean, true if successfully removed, and false if fail to 
//             remove
// Does      : call a helper function to recursively remove a sequence
// Note      : none
bool SequenceMatch::remove(TrieNode *lead, std::string seq)
{
    if (root == NULL){
        return false; 
    }
    if(lead == NULL) {
            return false;
    }
    if (seq == ""){
        if (lead->children[char2int(END)] == NULL) { // $ sign
            return false; 
        } else {
            delete_node(lead->children[char2int(END)]);
            return true;
        }
       
    } else {
	    char head = seq[0]; // search that
	    seq = seq.substr(1,seq.length());
        
        bool tmp = remove(lead->children[char2int(head)], seq);
       
        if (tmp) { // find the seq to remove
            delete_node(lead->children[char2int(head)]);
        }
        return tmp;
    }
}

// delete_node - PRIVATE
//   The helper function that helps remove a node
//
// Parameter : TrieNode node, the reference pointer to the node that
//             we should remove
// Return    : none
// Does      : remove a node
// Note      : none
void SequenceMatch::delete_node(TrieNode *&node)
{
    if (node == NULL)
     return;
    bool empty_node = true;
    for(int i = 0; i < 5; i++){
        if(node->children[i] != NULL)
            empty_node = false;
    }
    if(empty_node) {
        delete node;
        node = NULL;
    }
}

// print - PUBLIC
//   The function that print the entire structure
//
// Parameter : none
// Return    : none
// Does      : calls the helper function print
// Note      : none
void SequenceMatch::print() const
{
    print(root, "");
}

// print - PRIVATE
//   The helper function that recursively print the entire structure
//
// Parameter : TrieNode pointer curr, the pointer to start printing from 
//             string sequence, 
// Return    : none
// Does      : print the sequence in the list in order
// Note      : none
void SequenceMatch::print(TrieNode *curr, string sequence) const
{
    if(curr == NULL){
        return;
    } 
    else {
        if( curr->children[END_IDX] != NULL) // $
            passfile << sequence << endl;

        for(int i = 1; i < 5; i++) {
            print(curr->children[i],sequence + int2char(i)); //translate back 
        }  
    }
}

// numOfnodes - PUBLIC
//   The function that counts the nodes in the structure
//
// Parameter : none
// Return    : int, num of nodes in the structure
// Does      : counts the nodes in the structure
// Note      : none
int SequenceMatch::numOfnodes() const
{
    if(root == NULL){
        passfile << "There are " << 0 << " nodes in the database" << endl;
        return 0;
    } else {
        passfile << "There are " << numOfnodes(root)-1 
            << " nodes in the database" << endl;        
        return numOfnodes(root)-1;
    }
}

// numOfnodes - PRIVATE
//   The function that counts the nodes in the structure
//
// Parameter : TrieNode pointer cur, the place to start counting from 
// Return    : int, num of nodes in the structure
// Does      : counts the nodes in the structure
// Note      : none
int SequenceMatch::numOfnodes(TrieNode *cur) const
{
    if(cur == NULL){
        return 0;
    } else {
        int num = 1;
        for(int i = 0; i < 5; i++) {
            num += numOfnodes(cur->children[i]);
        }
        return num;
    }
}

// char2int - PRIVATE
//   The function that transfer char to int
//
// Parameter : char acid
// Return    : int, the corresbonding index
// Does      : transfer char to int
// Note      : none
int SequenceMatch::char2int(char acid)
{
    if(acid == END)
        return END_IDX;
    if(acid == ADENINE)
        return ADENINE_IDX;
    if(acid == CYTOSINE)
        return CYTOSINE_IDX;
    if(acid == GUANINE)
        return GUANINE_IDX;
    if(acid == THYMINE)
        return THYMINE_IDX;
    else 
        throw out_of_range("SEQUENCE OUT OF RANGE");
}

// int2char - PRIVATE
//   The function that transfer int to char
//
// Parameter : int index
// Return    : char, corresbonding letter
// Does      : transfer int to char
// Note      : none
char SequenceMatch::int2char(int index)
{
    if( index == END_IDX)
        return END;
    if( index == ADENINE_IDX)
        return ADENINE;
    if( index == CYTOSINE_IDX)
        return CYTOSINE;
    if( index == GUANINE_IDX)
        return GUANINE;
    if( index == THYMINE_IDX)
        return THYMINE;
    else 
        throw out_of_range("SEQUENCE OUT OF RANGE");
}

// newTrieNode - PRIVATE
//   The function that build a new Node
//
// Parameter : none
// Return    : TrieNode pointer, the pointer to the node that they just newed
// Does      : build a new Node
// Note      : none
SequenceMatch::TrieNode *SequenceMatch::newTrieNode()
{
    TrieNode *newNode = new TrieNode;

    for(int i = 0; i < 5; i++){
        newNode->children[i] = NULL;
    }
    return newNode;
}