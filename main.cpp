
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

char separators[] = { '[', ']' , '(', ')', '{', '}', ',', ';', ':', '#' };

string reals[] = { "1", "2", "3", "4", "5","6","7","8","9","0" };

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

bool isReal(string input)
{
	for (int i = 0; i < (sizeof(reals) / sizeof(*reals)); i++)
	{
		if (input == reals[i])
			return true;
	//	else if(isdigit(input) )
	}
	return false;
}


bool isSeparator(char input)
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
		//cout << *it;
		somefile << *it;
	}
	somefile.close();

	string temp;
	//read in from new txt file with no comments
	ifstream newFile("NoComments.txt");

	ofstream anotherFile;
	anotherFile.open("Analyze.txt");

	if (newFile.is_open())
	{
		anotherFile << "Keyword                       Lexemes" << endl << endl;
		//until we reach the end of the txt doc get one line at a time
		while (newFile >> temp)
		{

			if (isKeyword(temp))
			{
				anotherFile << "Keyword              =            " << temp << endl;
			}
			else if (isSeparator(temp[0]))
			{
				anotherFile << "Seperator            =            " << temp << endl;
			}
			else if (isOperator(temp))
			{
				anotherFile << "Operator             =            " << temp << endl;
			}
			else if (isReal(temp))
			{
				anotherFile << "Real                 =            " << temp << endl;
			}
			//if not any of the above then assume it is identifier
			else
			{

				//outer loop with check each char in the current string against the separators
				for (int i = 0; i < (sizeof(separators) / sizeof(*separators)); i++)
				{
					//check each char of current string against separator of i
					for (int j = 0; j < temp.size(); j++)
					{
						if (temp[j] == separators[i])
						{
							//if a separator is found, split the current string into sub string
							//output the separator then output each new string
							anotherFile << "Seperator            =            " << temp[j] << endl;

							//first half of string before separator
							string string1 = temp.substr(0, j);
							//second half of string after separator
							string string2 = temp.substr(j + 1, temp.size());

							//check if any of the new strings are keywords
							if (isKeyword(string1))
							{
								anotherFile << "Keyword              =            " << string1 << endl;
							}
							//if not assume it is an identifier
							else
							{
								anotherFile << "Identifier           =             " << string1 << endl;
							}

							//do same with second half of new string
							if (isKeyword(string2))
							{
								anotherFile << "Keyword              =            " << string2 << endl;
							}
							//double check to make sure we arent printing an empty space if the separator came at the end
							else if (string2 == "")
							{
								continue;
							}
							else
							{
								anotherFile << "Identifier           =             " << string2 << endl;
							}
							temp.empty();
						}
					}
				}
			}
		}
	}

	system("PAUSE");
	return 0;
}
