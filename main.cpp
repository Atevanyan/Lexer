
#include <iostream>
#include <fstream>
#include <list>
#include <string>


using namespace std;
void fileread(string filename);

int main(int argc, const char * argv[]) {
    
    fileread("/Users/eugenelee/Documents/School Stuff/CPSC 323/sample input file for assignment 1.txt");
    return 0;
}

//Input file stream that will read file
void fileread(string filename){
//Characters that I will insert into list
char read;
//List of the characters
list<char>mylist;

ifstream infile(filename);

if(infile.is_open()){
    while(!infile.eof()){
        infile>>read;
        mylist.push_back(read);
    }
}

//Remove comments
for(list<char>::iterator it=mylist.begin();it!=mylist.end();++it){
    if(*it=='!'){
        do{
            mylist.erase(it);
            it++;
        } while(*it!='!');
    }
}
    
//Pops remaining exclamation point off of stack
mylist.pop_front();

//Output file without comments
for(list<char>::iterator it=mylist.begin();it!=mylist.end();++it){
    cout<<*it<<" ";
    }
    
    cout<<"\ndone"<<"/t";
}
