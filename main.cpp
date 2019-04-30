//
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

vector<string> lexemes;
int LEXNUM = 0;

void reverseStr(string& str)
{
	int n = str.length();

	// Swap character starting from two 
	// corners 
	for (int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
}

string keywords[] = { "int ", "float ", "bool ", "if ", "else ", "then ", "while ", "whileend ", "do ", "doend ", "for ", "and ", "or ", "function " };

char separators[] = { '(',')','{','}','[',']',',','.',':',';','!','\n' };
string separators2[] = { "(",")","{","}","[","]",",",".",":",";","!","\n" };

char operators[] = { '+','*','-','<','>','=','/','%'};
string operators2[] = { "+","*","-","<",">","=","/","%" };

bool isOperator(char input)
{
	for (int i = 0; i < (sizeof(operators) / sizeof(*operators)); i++)
	{
		if (input == operators[i])
			return true;
	}
	return false;
}
bool isOperator(string input)
{
	for (int i = 0; i < (sizeof(operators) / sizeof(*operators)); i++)
	{
		if (input == operators2[i])
			return true;
	}
	return false;
}

bool isKeyword(string input)
{
	for (int i = 0; i < (sizeof(keywords) / sizeof(*keywords)); i++)
	{
		if (input == keywords[i])
			return true;
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
bool isSeparator(string input)
{
	for (int i = 0; i < (sizeof(separators) / sizeof(*separators)); i++)
	{
		if (input == separators2[i])
			return true;
	}
	return false;
}

list<char>mylist;
int state = 0;
int counter = 0;

int char_to_col(char c) {

	if (isdigit(c)) {
		return 2;
	}
	else if (isSeparator(c)) {
		return 4;
	}
	else if (isalpha(c) || c == '$') {
		return 1;
	}
	else {
		return 3;
	}

}

void finalState(int state, string filename) {
	ofstream outfile;
	outfile.open(filename,std::ofstream::app);

	if (state == 6) {
		outfile << "Real:	   = ";
		//state = 0;
	}
	/*else if (state == 7) {
		outfile << "Operator:	  = ";
		//state = 0;
	}
	else if (state == 😎 {
		outfile << "Seperator:		  = ";
		//state = 0;
	}
	else {
		cout << "Error: Invalid final state\n";
	}*/
	outfile.close();
}

//Returns true if keyword, returns false if identifier
bool checkKeyword(string lexeme) {

	if (isKeyword(lexeme)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void DFSM(string filename) {
	const int STATES = 9;
	const int INPUTS = 6;

	int table[STATES][INPUTS] = {
		{ 0,1,2,3,4,4 },    //0 1->char 2->digit 3->operator 4->Separator 5->period
		{ 0,1,1,5,5,4 },    //1 Maps to end of string when it hits an operator or seperator. goes to seperator if you get a period
		{ 0,6,2,6,6,2 },    //2 Maps to digit until you reach a seperator, operator or character
		{ 0,7,7,7,7,4 },    //3 Maps to final state of operator unless you get a period which maps to a seperator
		{ 0,8,8,8,8,8 },    //4 Maps to final state of seperator
		{ 0,0,0,0,0,0 },    //5 Reached the end of the string
		{ 0,0,0,0,0,0 },    //6 Final state for Digits
		{ 0,0,0,0,0,0 },    //7 Final state for Operators
		{ 0,0,0,0,0,0 }     //8 Final state for seperators
	};
	//if digit after period then go back to float. 

	ofstream myfile;
	myfile.open("analyzed.txt");

	for (list<char>::iterator it = mylist.begin(); it != mylist.end(); ++it) {
		int col = char_to_col(*it);

		state = table[state][col];
		counter++;

		if (state == 4)
		{
			state = 8;
		}
		if (state == 3)
		{
			state = 7;
		}
		if (state == 6 || state == 7 || state == 😎 {
			//finalState(state, "analyzed.txt");
			ofstream myfile;
			if (state == 6) 
			{
				myfile << "Real:		  = " << *it << endl;
				//state = 0;
			}
			counter = 0;
			state = 0;
		}
		else if (state == 5) {
		//	char* lexeme = new char[counter];
			string lexeme;
			list<char>::iterator temp = it;
			if (isSeparator(*it))
			{
				myfile << "Seperator:		  = " << *it << endl;
			}
			else if (isOperator(*it))
			{
				myfile << "Operator:     		= " << *it << endl;
			}
			
			--temp;
			counter--;
			for (int i = 0; i < counter; i++) 
			{
				if (isSeparator(*temp))
				{
					--temp;
				}
				else if (isOperator(*temp))
				{
					--temp;
				}
				lexeme += *temp;
				--temp;
			}
			reverseStr(lexeme);
			lexemes.push_back(lexeme);
			if (checkKeyword(lexeme)) 
			{
				myfile <<"Keyword:		= "<< lexeme << endl;

				state = 0;
			}
			else 
			{
				myfile <<"Identifier:		= "<< lexeme << endl;
				state = 0;
			}
			lexeme.clear();
			counter = 0;
		}
	}
	myfile.close();
}

//returns 1 if current lexeme is an operator
//returns 2 if current lexeme is a keyword
//returns 3 if current lexeme is a seperator
//returns 4 if current lexeme is a identifier
int tokenVal(int position)
{
	if (isOperator(lexemes[position]))
	{
		LEXNUM++;
		return 1;
	}
	else if (isKeyword(lexemes[position]))
	{
		LEXNUM++;
		return 2;
	}
	else if (isSeparator(lexemes[position]))
	{
		LEXNUM++;
		return 3;
	}
	else
		return 4;
}

int main() {

	char read;

	ifstream infile("Input.txt");
	infile >> noskipws;
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			infile >> read;
			mylist.push_back(read);
		}
	}
	infile.close();

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

	DFSM("NoComments.txt");

	cout << endl << endl;
	return 0;
}
