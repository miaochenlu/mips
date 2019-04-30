#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream f1("codecompare.txt");
    ifstream f2("res.txt");
    
    int i = 1;
    // char buffer1[256] = {0};
    // char buffer2[256] = {0};
    while(!f2.eof()) {
        string s1, s2;
        s1.clear();
        s2.clear();
        f1 >> s1;
        f2 >> s2;
        
        if(s1 != s2) {
            cout << s1 << endl;
            cout << s2 << endl;
            cout << i << endl;
            break;
        }
        i++;
    }
    cout << "success" << endl;
}