
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>


using namespace std;

const string keywords[] = { "asm", "else", "new", "this", "auto", "enum", "operator", "throw", "bool",
"explicit", "private", "true", "break", "export", "protected", "try", "case", "extern", "public",
"typedef", "catch", "false", "register", "typeid", "char", "float", "reinterpret_cast", "typename",
"class", "for", "return", "union", "const", "friend", "short", "unsigned", "const_cast", "goto", "signed",
"using", "continue", "if", "sizeof",    "virtual", "default", "inline", "static", "void", "delete", "int",
"static_cast", "volatile", "do", "long", "struct", "wchar_t", "double", "mutable", "switch", "while",
"dynamic_cast", "namespace", "template", };

const string operators[] = { "=", "==", "+", "-", "*", "/", ">", "<", ">=", "<=", "|", "&&" };

string separators[] = { "[", "]", "(", ")", "{", "}", ",", ";", ":", ".", "#" };

bool isKeyword(string input)
{
	for (int i = 0; i < (sizeof(keywords) / sizeof(*keywords)); i++)
	{
		if (input == keywords[i])
			return true;
	}
	return false;
}

bool isOperator(string input)
{
	for (int i = 0; i < (sizeof(operators) / sizeof(*operators)); i++)
	{
		if (input == operators[i])
			return true;
	}
	return false;
}


bool isSeparator(string input)
{
	for (int i = 0; i < (sizeof(separators) / sizeof(*separators)); i++)
	{
		if (input == separators[i])
			return true;
	}
	return false;
}


int main() {

	char read;
	string lex;
	list<char>mylist;

	ifstream infile("input.txt");
	infile >> noskipws;
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile >> read;
			mylist.push_back(read);
		}
	}

	//Remove comments
	for (list<char>::const_iterator it = mylist.begin(); it != mylist.end(); ++it)
	{
		if (*it == '!') {
			do
			{
				list<char>::const_iterator temp = it;
				*it++;
				mylist.erase(temp);
			} while (*it != '!');
			it = mylist.erase(it);
		}
	}
	//Pops remaining exclamation point off of stack
	mylist.pop_front();

	//Output file without comments
	ofstream somefile;

	somefile.open("NoComments.txt");
	for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it)
	{
		cout << *it;
		somefile << *it;
	}
	
	somefile.close();

	string temp;
	//read in from new txt file with no comments
	ifstream newFile("NoComments.txt");

	if (newFile.is_open())
	{
		cout << "Keyword                       Lexemes" << endl << endl;
		//until we reach the end of the txt doc get one line at a time
		while (newFile >> temp)
		{

			if (isKeyword(temp))
			{
				cout << "Keyword              =            " << temp << endl;
			}
			else if (isSeparator(temp))
			{
				cout << "Seperator            =            " << temp << endl;
			}
			else if(isOperator(temp))
			{
				cout << "Operator             =            " << temp << endl;
			}
			//if not any of the above then assume it is identifier
			else
			{
				cout << "Identifier           =            " << temp << endl;
			}
		}
	}

	system("PAUSE");
	return 0;
}
