#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
string Op2Binary(string op) {
	string result;
	transform(op.begin(), op.end(), op.begin(), ::tolower);
	if (op == "j" || op == "jal") {
        result = 
	}
	else if (op == "jr") {

	}
	else if (op == "addi" || op == "ori" || op == "beq") {

	}
	else if (op == "add" || op == "sub" || op == "and" || op == "or" || op == "slt" || op == "sll") {

	}
	else if (op == "sw" || op == "lw") {

	}
	return result;
}
string j_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    string op;

    while(buffer[i] != ' ') {
        oper[i] = buffer[i];
        i++;
    }
    op = oper;
    if(op == "j") result += "000010";
    else if(op == "jal") result += "000011";
    while(buffer[i] != '\n') {
        
    }
}
int main() {
	ifstream fin("mips.txt");
	if (!fin) {
		cout << "Can't open the file" << endl;
		exit(0);
	}
	string op;
	char buffer[256];
	char oper[20];
	while (!fin.eof()) {
		fin.getline(buffer, 256);
        string instruction;
		if (buffer[0]) {
            int i = 0;
			while(buffer[i] != ' ') {
                oper[i] = buffer[i];
                i++;
            }
            oper[i] = '\0';
			op = oper;
            if (op == "j" || op == "jal") {
                j_instruction(buffer);
            }
            else if (op == "jr") {

            }
            else if (op == "addi" || op == "ori" || op == "beq") {

            }
            else if (op == "add" || op == "sub" || op == "and" || op == "or" || op == "slt" || op == "sll") {

            }
            else if (op == "sw" || op == "lw") {

            }
			cout << op << endl;
		}
		
	}

}