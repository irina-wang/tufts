#include "FSTree.h"
#include "DirNode.h"
#include <iostream>

using namespace std;

void recurse(string parent_folder, DirNode *currdir, bool is_root) {
    string currname;
    if (is_root)
        currname = currdir->getName();
    else
        currname = parent_folder + "/" + currdir->getName();
    for (int i = 0; i < currdir->numSubDirs(); i++) {
        recurse(currname, currdir->getSubDir(i), false);
    }
    for (int i = 0; i < currdir->numFiles(); i++) {
        cout << currname << "/" << currdir->getFile(i) << endl;
    }
    cout << currname << endl;
}

int main(int argc, char** argv) 
{
    if (argc == 2) {
        FSTree filesystem(argv[1]);
        recurse("", filesystem.getRoot(), true);
        return 0;
    } else {
        cerr << "Usage: " << argv[0] <<" [foldername]" << endl;
        return 1;
    }
}
