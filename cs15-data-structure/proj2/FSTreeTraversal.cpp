/*
 * FSTreeTraversal.cpp
 * Comp15
 * Spring 2019
 * proj2
 *
 * Author : Mengqi Irina Wang
 * Date: 04/10/2019
 */


#include "DirNode.h"
#include "FSTree.h"

#include<iostream>

using namespace std;

void FSTreeTraversal_helper(DirNode *dir,string curr, bool first_time);

// FSTreeTraversal
//   call the recursive function FSTreeTraversal_helper
// 
// Parameter : a DirNode pointer dir
// Returns   : none
// Does      : call the recursive function FSTreeTraversal_helper
// Note      : pass in empty string curr and true as first_time boolean
void FSTreeTraversal(DirNode *dir){
    FSTreeTraversal_helper(dir,"",true);
}   

// FSTreeTraversal_helper
//   Recursively print out all the files and subdirs in the given path
// 
// Parameter : a DirNode pointer dir, indicating where to start
//             a string curr, collect the string that's already passed
//             bool first_time, mark the special case when it's the first time
// Returns   : none
// Does      : Recursively print out all the files and subdirs in the given path
// Note      : first_time boolean is given to avoid printing the given path 
//              twice or print two "/" at the beginning
void FSTreeTraversal_helper(DirNode *dir, string curr, bool first_time){
    string currname;
    if ( dir->isEmpty())
        return;
    else{
        currname = curr + "/" + dir->getName();
        if(first_time) // first time to recurse
            currname = dir->getName();
        if(dir->hasSubDir()){
            for(int i=0; i< dir->numSubDirs(); i++){
                FSTreeTraversal_helper(dir->getSubDir(i),currname,false);
            }   
        }
        if(dir->hasFiles()){
            for(int i=0; i< dir->numFiles(); i++){
                cout << currname << "/" << dir->getFile(i) << endl; // note "/"
            }
        }
        cout << currname << endl; 
    }   
}


int main(int argc, char** argv) {
    if (argc == 2) {
        FSTree Tree(argv[1]);
        FSTreeTraversal(Tree.getRoot());
        return 0;
    } else {
        cerr << "Usage: " << argv[0] <<" [foldername]" << endl;
        return 1;
    }
}