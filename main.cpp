
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>


using namespace std;

const string keywords[] = {
	"if", "ifend", "put", "get", "else",
	"while", "whileend", "return", "true", "false",
	"function", "int", "boolean", "real", "string", "do", "char"};

const string operators[] = {
	"=", "==", "+", "-", "*", "/", ">", "<", ">=", "<=", "|", "&&" };

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
