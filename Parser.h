#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

ofstream out;                       //to write outputs in file 
string token,type;                  //token and type inside tokens and types came from scanner
vector<string> Atokens, Atypes;    //take tokens and types vectors as global vectors to use them in match function
int pointer;                       //pointer loops on all tokens and types inside tokens and types vectors

void factor();                       //to make function global to all functions that call it
void stmt_sequence();                //to make function global to all functions that call it

void match(string t)
{
	if (token == t)
	{
		pointer++;           //accumulate to loop on tokens and types 
		if (pointer != Atokens.size())          //to ensure that pointer does not exceed size of vectors
		{
			token = Atokens[pointer]; type = Atypes[pointer];              //get next token and type
		}
	}
	else
	{
		out << "Error match terminal\n";
		exit(EXIT_FAILURE);
	}
}

void mulop(){
	if (token == "*")
	{
		match("*"); out << "Mul_Operator Found" << endl;
	}
	else if (token == "/")
	{
		match("/"); out << "Mul_Operator Found" << endl;
	}
}

void addop(){
	if (token == "+")
	{
		match("+"); out << "Add_Operator Found" << endl;
	}
	else if (token == "-")
	{
		match("-"); out << "Add_Operator Found" << endl;
	}
}

void comparison_op(){
	if (token == "<")
	{
		match("<"); out << "Comparison_Operator Found" << endl;
	}
	else if (token == "=")
	{
		match("="); out << "Comparison_Operator Found" << endl;
	}
}

void term(){
	factor();
	mulloop:if (token == "*" || token == "/")
	{
		mulop();
		factor();
		goto mulloop;
	}
	out << "Term Found" << endl;
}
void simple_exp(){
	term();
	addloop:if (token == "+" || token == "-")
	{
		addop();
		term();
		goto addloop;
	}
	out << "Simple_Expression Found" << endl;
}
void exp(){
	simple_exp();
	if (token == "<" || token == "=")
	{
		comparison_op();
		simple_exp();
	}
	out << "Expression Found" << endl;
}
void factor(){
	if (type == "number")
	{
		match(token);
		out << "Factor Found" << endl;
	}
	else if (type == "identifier")
	{
		match(token);
		out << "Factor Found" << endl;
	}
	else if (token == "(")
	{
		match("(");
		exp();
		match(")");
		out << "Factor Found" << endl;
	}
	else
	{
		out << "Error match factor" << endl;
		exit(EXIT_FAILURE);
	}
}

void assign_stmt(){
	match(token);
	match(":=");
	exp();
	out << "Assignment_Statement Found" << endl;
}
void read_stmt(){
	match("read");
	if (type == "identifier")
		match(token);
	else {
		out << "Error match read statement" << endl; exit(EXIT_FAILURE);
	}
	out << "Read_Statement Found" << endl;
}
void write_stmt(){
	match("write");
	exp();
	out << "Write_Statement Found" << endl;
}
void repeat_stmt(){
	match("repeat");
	stmt_sequence();
	match("until");
	exp();
	out << "Repeat_Statement Found" << endl;
}
void if_stmt(){
	match("if");
	exp();
	match("then");
	stmt_sequence();
	if (token == "else")
	{
		match("else");
		stmt_sequence();
	}
	match("end");
	out << "IF_Statement Found" << endl;
}
void statement(){
	if (token == "if")
	{
		if_stmt(); out << "Statement Found" << endl; 
	}
	else if (token == "repeat")
	{
		repeat_stmt(); out << "Statement Found" << endl; 
	}
	else if (type == "identifier")
	{
		assign_stmt(); out << "Statement Found" << endl; 
	}
	else if (token == "read")
	{
		read_stmt(); out << "Statement Found" << endl; 
	}
	else if (token == "write")
	{
		write_stmt(); out << "Statement Found" << endl;
	}
	else
	{
		out << "Error match statement" << endl;
		exit(EXIT_FAILURE);
	}
}

void stmt_sequence(){
	statement(); 
  stmtloop:	if (token == ";")
	{
		match(";"); 
		statement();
		goto stmtloop;
	}
	out << "Statement_Sequence Found" << endl;
}

void program(){
	stmt_sequence();
	out << "Program Found" << endl;
}

void Parser(vector<string> tokens,vector<string> types)
{
	out.open("parser_output.txt");    //create file for output 
	pointer = 0;                       //initialize pointer
	token = tokens[pointer];           //first token
	type = types[pointer];             //first type
	Atokens = tokens;                  //give tokens to global vector Atokens
	Atypes = types;                    //give types to global vector Atypes

	program();                         //start parsing
	
}