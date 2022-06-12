#include<fstream>
#include<string>
#include<iostream>

using namespace std;

bool palindrome (string s){
	if (s.length()<2) {	//Base case
		//cout <<"Checking if palindrome. S is " << s <<". Because length <2 we return true." <<endl;
		return true;
	}
	else {
		string head, tail;
		head=s.substr(0,1);
		tail=s.substr(s.length()-1,s.length());
		if (head==tail) {
			//cout <<"Checking if palindrome. S is " << s <<". First and last letters match." <<endl;
			//cout << "New word to recurse is " << s.substr(1,s.length()-2) << endl;
			return palindrome(s.substr(1,s.length()-2));
		}
		else {
			//cout <<"Checking if palindrome. S is " << s <<". First and last letters did NOT match." <<endl;
			return false;
		}

	}
	return true;
}

void paliHelper(string s, string partialSol,ofstream &outfile){
	if (s.length()<2) {	//Base case
		cout << "Base case of recursion. s is " << s <<". PartialSol is:"<< partialSol <<endl;
		outfile << "Partition into palindromes found: " << partialSol << " " << s << endl;
	}
	else{				//Recursion
		string head, tail;
		cout << "Looking for a palindrome. S is " << s << endl;
			for(int i=1;i<=s.length();i++){
			head=s.substr(0,i);
			tail=s.substr(i,s.length());
			if (palindrome(head)){
				//partialSol=partialSol+ " "+ head;
				cout << "Found a palindrome: ";
				cout << head <<". Tail is:" <<tail <<endl;
 				cout << "About to recurse. New partialSol is " << partialSol <<" " <<head <<endl;
				paliHelper(tail,partialSol+ " "+ head,outfile);
			}
		}
	}
}


void allPalindromes(string s,ofstream &out){
	string aux="";
	cout << "AllPalindromes: top of recursion. S is equal to: " << s << endl;
	paliHelper(s,aux,out);	//Call a helper
}



int main(int argc, char* argv[]){
	if (argc != 3)
		cerr << "You have to call this program with 2 parameters: a string and a filename" << endl;
	else {
		string s=argv[1];
		ofstream outfile;
		outfile.open (argv[2]);
		allPalindromes(s,outfile);
		outfile.close();
	}
	return(0);
		
}
