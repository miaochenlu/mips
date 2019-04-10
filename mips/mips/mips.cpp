#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
int Op2Binary(string op) {
	int result = 0;
	transform(op.begin(), op.end(), op.begin(), ::tolower);
	if (op == "j" || op == "jal") {

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
int main() {
	ifstream fin("mips.txt");
	if (!fin) {
		cout << "Can't open the file" << endl;
		exit(0);
	}
	string op;
	char buffer[256];
	char **tmp = 0;
	char *oper;
	while (!fin.eof()) {
		fin.getline(buffer, 256);
		if (buffer[0]) {
			oper = strtok_s(buffer, " ", tmp);
			op = oper;
			cout << op << endl;
		}
		
	}

}