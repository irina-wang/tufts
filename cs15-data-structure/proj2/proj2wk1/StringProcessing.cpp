
/*
 * StringProcessing.cpp
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

// check_in_bound
//   check if the character is alphanumeric
// 
// Parameter : char n, the character ready to be checked
// Returns   : boolean, true - is alphanumeric
//                      false - is not alphanumeric
// Does      : check if the character is alphanumeric
// Note      : none
bool check_in_bound(char n){
    if( n >= 'a' and n <= 'z')
        return true;
    else if( n >= 'A' and n<= 'Z')
        return true;
    else if( n >= '0' and n <= '9')
        return true;
    else 
        return false;
}

// StringProcessing
//   strips all leading and trailing non-alphanumeric characters from the word
// 
// Parameter : string filename, the word to be processed
// Returns   : string, the word after being processed
// Does      : strips all leading and trailing non-alphanumeric characters from
//             the word
// Note      : none
string StringProcessing(string filename){
    int front = -1;
    bool smallest = true; // boolean to decide whether to renew front
    for(int i=0; i<filename.length(); i++){
        bool front_check = check_in_bound(filename[i]); 
        if(smallest){ 
            if(front_check){
                front = i;
                smallest = false; // change the value so that the loop won't be
                                  // accessed again
            }
        }  
    }
    int back = filename.length();
    bool biggest = true; // boolean to decide whether to renew back
    for(int i=filename.length(); i > -1; i--){ // iterating backwards
        bool back_check = check_in_bound(filename[i]);
        if(biggest){
            if(back_check){
                back = i;
                biggest = false;  // change the value so that the loop won't be
                                  // accessed again
            }
        }
    }
    if(front == -1)
        return "";
    if(front == back) 
        return filename.substr(front,back+1);
    if(front > back) // all non-alphanumeric characters
        return "";
    return filename.substr(front,back-front+1);
}


int main(){
    string input;

    while(cin >> input){
        input = StringProcessing(input); 
        cout << input << endl << endl;
    }
    return 0;
}
