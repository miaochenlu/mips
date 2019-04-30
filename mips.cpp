#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <map>
#include <vector>
#include <ctype.h>
using namespace std;
string reg[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2",
                  "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", 
                  "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void tolower(char str[]) {
    int i = 0;
    while(str[i] != 0) {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
        i++;
    }
}

typedef map<string, int> Map;
Map jump_address;

int IsInteger(string s) {
    int res = 1;
    int j = 0;
    if(s[0] == '0' && s[1] == 'x') j = 2;
    for(int i = j; i < s.size(); i++) {
        if(s[i] < '0' || s[i] > '9')
            res = 0;
    }
    return res;
}

void FirstScan(ifstream &fin, ofstream &fout) {
    int i = 0, j = 0, k = 0, colon = 0;
    string address;
    string inst;
    char tmpbuffer[256];
    while(!fin.eof ()) {
        fin.getline(tmpbuffer, 256);
        tolower(tmpbuffer);
        j = 0, k = 0, colon = 0;
        char addr[50];
        while(tmpbuffer[j] == ' ') j++;
        if(tmpbuffer[j] == 0) continue;

        while(tmpbuffer[j] != 0) {
            if(tmpbuffer[j] == ':') {
                addr[k] = 0;
                colon = 1;
                address = addr;
                jump_address.insert(Map::value_type(address, i));
                k = 0;
                while((tmpbuffer[j] == ' ' || tmpbuffer[j] == ':') && tmpbuffer[j] != 0) j++;
                continue;
            }
            if(tmpbuffer[j] == '#') break;
            addr[k++] = tmpbuffer[j++];
        }
        if(colon == 1 && k == 0) continue;
        addr[k] = 0;
        fout << addr << endl;
        i++;
    }
}
string int25Binstring(int number) {
    bitset<5> tmp(number);
    return tmp.to_string();
}

string char226string(char imm_addr_tmp[]) {
    string tmp = imm_addr_tmp;

    int i = 0, result = 0;
    if(jump_address.count(tmp) > 0)
        result = jump_address[tmp];
    else {
        if(imm_addr_tmp[0] == '0' && imm_addr_tmp[1] == 'x') {
            i = 2;
            while(imm_addr_tmp[i] != 0) {
                result = (imm_addr_tmp[i] - '0') + result * 16; 
                i++;
            }
        }
        else if(imm_addr_tmp[0] == '0' && imm_addr_tmp[1] == 'b') {
            i = 2;
            while(imm_addr_tmp[i] != 0) {
                result = (imm_addr_tmp[i] - '0') + result * 2; 
                i++;
            }
        }
        else
            result = atoi(imm_addr_tmp);
    }
    bitset<26> addr(result);
    return addr.to_string();
}
string char216string(char imm_addr_tmp[], int line) {
    string tmp = imm_addr_tmp;

    int i = 0, result = 0;
    if(jump_address.count(tmp) > 0)
        result = jump_address[tmp];
    else {
        if(imm_addr_tmp[0] == '0' && imm_addr_tmp[1] == 'x') {
            i = 2;
            while(imm_addr_tmp[i] != 0) {
                result = (imm_addr_tmp[i] - '0') + result * 16; 
                i++;
            }
        }
        else if(imm_addr_tmp[0] == '0' && imm_addr_tmp[1] == 'b') {
            i = 2;
            while(imm_addr_tmp[i] != 0) {
                result = (imm_addr_tmp[i] - '0') + result * 2; 
                i++;
            }
        }
        else
            result = atoi(imm_addr_tmp);
    }
    result = result - line - 1;
    bitset<16> addr(result);
    return addr.to_string();
}
string j_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char imm_addr_tmp[30];

    string op, imm_addr;
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read imm_addr
    j = 0;
    while(buffer[i] == ' ') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#') 
        imm_addr_tmp[j++] = buffer[i++];
    imm_addr_tmp[j] = 0;
    if(op == "j") result += "000010";
    else if(op == "jal") result += "000011";
    result += char226string(imm_addr_tmp);
    return result;
}

string string216int(char imm[]) {
    int i = 0;
    int result = 0;
    //cout << "yers" << endl;
    if(imm[0] == '0' && imm[1] == 'x') {
        i = 2;
        while(imm[i] != 0) {
            if(imm[i] >= 'a' && imm[i] <= 'f')
                result = (imm[i] - 'a' + 10) + result * 16;
            else if(imm[i] >= '0' && imm[i] <= '9') 
                result = (imm[i] - '0') + result * 16; 
            i++;
        }
            
    }
    else if(imm[0] == '0' && imm[1] == 'b') {
        i = 2;
        while(imm[i] != 0) {
            result = (imm[i] - '0') + result * 2; 
            i++;
        }
    }
    else
        result = atoi(imm);
    bitset<16> tmp(result);
    cout << tmp.to_string() << endl;
    return tmp.to_string();
} 

string string25int(char imm[]) {
    int i = 0;
    int result = 0;
    //cout << "yers" << endl;
    if(imm[0] == '0' && imm[1] == 'x') {
        i = 2;
        while(imm[i] != 0) {
            if(imm[i] >= 'a' && imm[i] <= 'f')
                result = (imm[i] = 'a' + 10) + result * 16;
            else if(imm[i] >= '0' && imm[i] <= '9') 
                result = (imm[i] - '0') + result * 16; 
            i++;
        }
    }
    else if(imm[0] == '0' && imm[1] == 'b') {
        i = 2;
        while(imm[i] != 0) {
            result = (imm[i] - '0') + result * 2; 
            i++;
        }
    }
    else
        result = atoi(imm);
    bitset<5> tmp(result);
    return tmp.to_string();
} 
string i_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];
    char rt_tmp[20];
    char imm_tmp[30];
    string op;
    string rs , rt, imm;
    int rs_num = 0, rt_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read rt
    j = 0;
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',')
        rt_tmp[j++] = buffer[i++];
    rt_tmp[j] = 0;
    rt = rt_tmp;

    //read rs
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',') 
        rs_tmp[j++] = buffer[i++];
    rs_tmp[j] = 0;
    rs = rs_tmp;

    //read imm
    j = 0; 
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#') 
        imm_tmp[j++] = buffer[i++];
    imm_tmp[j] = 0;
    
    for(int k = 0; k < 32; k++) {
        if(rt == reg[k])
            rt_num = k;
        if(rs == reg[k])
            rs_num = k;
    }
    imm = string216int(imm_tmp);
    if(op == "addi") result += "001000";
    else if(op == "ori") result += "001101";
    result += int25Binstring(rs_num) + int25Binstring(rt_num) + imm;
    return result;
}

string bounce_instruction(char buffer[], int line) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];
    char rt_tmp[20];
    char imm_tmp[30];
    string op;
    string rs , rt, imm;
    int rs_num = 0, rt_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read rt
    j = 0;
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',')
        rs_tmp[j++] = buffer[i++];
    rs_tmp[j] = 0;
    rs = rs_tmp;

    //read rs
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',') 
        rt_tmp[j++] = buffer[i++];
    rt_tmp[j] = 0;
    rt = rt_tmp;
    //read imm
    j = 0; 
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#') 
        imm_tmp[j++] = buffer[i++];
    imm_tmp[j] = 0;
    
    for(int k = 0; k < 32; k++) {
        if(rt == reg[k])
            rt_num = k;
        if(rs == reg[k])
            rs_num = k;
    }
    imm = char216string(imm_tmp, line);
    if(op == "beq")      result += "000100";
    else if(op == "bne") result += "000101";
    result += int25Binstring(rs_num) + int25Binstring(rt_num) + imm;
    return result;
}
string lw_sw(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];
    char rt_tmp[20];
    char imm_tmp[30];
    string op;
    string rs , rt, imm;
    int rs_num = 0, rt_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read rt
    j = 0;
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',')
        rt_tmp[j++] = buffer[i++];
    rt_tmp[j] = 0;
    rt = rt_tmp;
    
    //read imm
    j = 0; 
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '(' && buffer[i] != ' ') 
        imm_tmp[j++] = buffer[i++];
    imm_tmp[j] = 0;

    //read rs
    j = 0; while(buffer[i] == ' ' || buffer[i] == '(') i++;
    while(buffer[i] != ')' && buffer[i] != ' ') 
        rs_tmp[j++] = buffer[i++];
    rs_tmp[j] = 0;
    rs = rs_tmp;
    
    for(int k = 0; k < 32; k++) {
        if(rt == reg[k])
            rt_num = k;
        if(rs == reg[k])
            rs_num = k;
    }
    // cout << "rs " << rs << " rt " << rt << endl;
    // cout << "rs_num " << rs_num << endl;
    imm = string216int(imm_tmp);
    if(op == "sw") result += "101011";
    else if(op == "lw") result += "100011";
    result += int25Binstring(rs_num) + int25Binstring(rt_num) + imm;
   //cout << result << endl;
    return result;
}

string lui_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];
    char rt_tmp[20];
    char imm_tmp[30];
    string op;
    string rs , rt, imm;
    int rs_num = 0, rt_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read rt
    j = 0;
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',')
        rt_tmp[j++] = buffer[i++];
    rt_tmp[j] = 0;
    rt = rt_tmp;
    
    //read imm
    j = 0; 
    while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#' && buffer[i] != ';') 
        imm_tmp[j++] = buffer[i++];
    imm_tmp[j] = 0;
    j = 0; 

    //read rs
    rs = "00000";
    
    for(int k = 0; k < 32; k++) {
        if(rt == reg[k]) {
            rt_num = k;
            cout << reg[k] << endl;
        }
    }
    cout << "rt " << rt_num << endl;
    // cout << "rs " << rs << " rt " << rt << endl;
    // cout << "rs_num " << rs_num << endl;
    imm = string216int(imm_tmp);
    if(op == "lui") result += "001111";
    result += rs + int25Binstring(rt_num) + imm;
   //cout << result << endl;
    return result;
}
string r_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];
    char rt_tmp[20];
    char rd_tmp[20];
    string op;
    string rs , rt, rd;
    string shamt = "00000";
    string func;
    int rs_num = 0, rt_num = 0, rd_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ')
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;
    
    //read rd
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',')
        rd_tmp[j++] = buffer[i++];
    rd_tmp[j] = 0;
    rd = rd_tmp;

    //read rs
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != ',') 
        rs_tmp[j++] = buffer[i++];
    rs_tmp[j] = 0;
    rs = rs_tmp;
    //read rt
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#') 
        rt_tmp[j++] = buffer[i++];
    rt_tmp[j] = 0;
    rt = rt_tmp;

    for(int k = 0; k < 32; k++) {
        int flag[3] = {0};
        if(rd == reg[k]) {
            rd_num = k;
            flag[0] = 1;
        }
        if(rs == reg[k]) {
            rs_num = k;
            flag[1] = 1;
        }
        if(rt == reg[k]) {
            rt_num = k;
            flag[2] = 1;
        }
        else if(IsInteger(rt)) {
            shamt = string25int(rt_tmp);
            flag[2] = 1;
        }
    }
    //cout << rs << rd << rt << endl;
    result += "000000";
    result += int25Binstring(rs_num) + int25Binstring(rt_num) + int25Binstring(rd_num);
    if(op == "add")      { func = "100000";}
    else if(op == "sub") { func = "100010";}
    else if(op == "nor") { func = "100111";}
    else if(op == "slt") { func = "101010";}
    else if(op == "and") { func = "100100";}
    else if(op == "or")  { func = "100101";}
    else if(op == "xor") { func = "100110";}
    else if(op == "srl") { func = "000010";}
    result += shamt + func;
    return result;
}
string jr_instruction(char buffer[]) {
    string result;
    int i = 0;
    char oper[20];
    char rs_tmp[20];

    string op;
    string rs;
    string shamt;
    string func;
    int rs_num = 0;
    //read op
    int j = 0;
    while(buffer[i] != ' ') 
        oper[j++] = buffer[i++];
    oper[j] = 0;
    op = oper;

    //read rs
    j = 0; while(buffer[i] == ' ' || buffer[i] == ',') i++;
    while(buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '#' && buffer[i] != ';')
        rs_tmp[j++] = buffer[i++];
    rs_tmp[j] = 0;
    rs = rs_tmp;

    for(int k = 0; k < 32; k++)
        if(rs == reg[k])
            rs_num = k;
    
    result += "000000";
    result += int25Binstring(rs_num) + "00000" + "00000";
    shamt   = "00000";
    func    = "001000";
    result += shamt + func;

    return result;
}
int main() {
	ifstream fin("mips.txt");
    ofstream ftmp("tmp.txt");
	if (!fin) {
		cout << "Can't open the file" << endl;
		exit(0);
	}
	string op;
    vector<string>res;
	char buffer[256];
	char oper[20];
    FirstScan(fin, ftmp);
    ifstream filein("tmp.txt");
    int line = 0;
	while (!filein.eof()) {
		filein.getline(buffer, 256);
        string result;
        string instruction;
		if (buffer[0]) {
            int i = 0;
			while(buffer[i] != ' ') {
                oper[i] = buffer[i];
                i++;
            }
            oper[i] = 0;
			op = oper;
            cout << op << endl;
            if (op == "j" || op == "jal")
                res.push_back(j_instruction(buffer));
            else if (op == "jr") {
                res.push_back(jr_instruction(buffer));
            }
            else if (op == "addi" || op == "andi" || op == "ori" || op == "xori" 
                         || op == "slti") 
                res.push_back(i_instruction(buffer));
            else if (op == "lui") 
                res.push_back(lui_instruction(buffer));
            else if(op == "beq" || op == "bne") 
                res.push_back(bounce_instruction(buffer, line));
            else if (op == "add" || op == "sub" || op == "and" || op == "or" || op == "sltu" 
                        || op == "xor" || op == "slt" || op == "nor" || op == "srl")
                res.push_back(r_instruction(buffer));
            else if (op == "sw" || op == "lw") 
                res.push_back(lw_sw(buffer));
		}
        line++;
	}
    ofstream foutput("res.txt");
    vector<string>::iterator iter;
    for(iter = res.begin(); iter != res.end(); iter++)
        foutput << *iter << endl;
}