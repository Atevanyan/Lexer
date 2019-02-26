
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>


using namespace std;

const string keywords[] = {"asm", "else", "new", "this", "auto", "enum", "operator", "throw", "bool", 
"explicit", "private", "true", "break", "export", "protected", "try", "case", "extern", "public", 
"typedef", "catch", "false", "register", "typeid", "char", "float", "reinterpret_cast", "typename", 
"class", "for", "return", "union", "const", "friend", "short", "unsigned", "const_cast", "goto", "signed", 
"using", "continue", "if", "sizeof",    "virtual", "default", "inline", "static", "void", "delete", "int", 
"static_cast", "volatile", "do", "long", "struct", "wchar_t", "double", "mutable", "switch", "while", 
"dynamic_cast", "namespace", "template",};

const string operators[] = {"=", "==", "+", "-", "*", "/", ">", "<", ">=", "<=", "|", "&&" };

string constants[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

string separators[] = { "[", "]", "(", ")", "{", "}", ",", ";", ":", ".", "#"};

string identifiers[] = { "_", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
    "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I",
    "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

bool isKeyword(string input)
{
	for (int i = 0; i < keywords->size(); i++)
	{
		if (input == keywords[i])
			return true;
	}
	return false;
}

bool isOperator(string input)
{
	for (int i = 0; i < operators->size(); i++)
	{
		if (input == operators[i])
			return true;
	}
	return false;
}

bool isConstant(string input)
{
	for (int i = 0; i < constants->size(); i++)
	{
		if (input == constants[i])
			return true;
	}
	return false;
}

bool isSeparator(string input)
{
	for (int i = 0; i < separators->size(); i++)
	{
		if (input == separators[i])
			return true;
	}
	return false;
}

bool isIdentifier(string input)
{
	for (int i = 0; i < identifiers->size(); i++)
	{
		if (input == identifiers[i])
			return true;
	}
	return false;
}

int main(int argc, const char * argv[]) {

	char read;
	string lex;
	list<char>mylist;

	ifstream infile("/Users/eugenelee/Documents/School Stuff/CPSC 323/sample input file for assignment 1.txt");

	if (infile.is_open()) {
		while (!infile.eof()) {
			infile >> read;
			mylist.push_back(read);
		}
	}

	//Remove comments
	for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it) {
		if (*it == '!') {
			do {
				mylist.erase(it);
				it++;
			} while (*it != '!');
		}
	}
	//Pops remaining exclamation point off of stack
	mylist.pop_front();

	//Output file without comments
	for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it) {
		cout << *it << " ";
	}

	cout << "\ndone" << "/t";
	return 0;
}
