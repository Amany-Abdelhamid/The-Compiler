#include <iostream>
#include <fstream>
#include <vector>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main(){

	vector<string> tokens,types;

	//fisrt you must call Scanner function to get tokens and their types then give them to the parser
	//scanner function makes scan for tiny code sample input file and create output called scanner_output 
	//then return tokens,types vectors to give them to the parser

	Scanner(&tokens,&types);
	
	
	//note the parser function must take tokens and types vectors came from scanner to work

	Parser(tokens, types);

	return 0;

}













