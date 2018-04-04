#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void Scanner(vector<string> *tokens, vector<string> *types)
{
	ifstream in("tiny_sample_code.txt"); ofstream cout("scanner_output.txt");
	cin.rdbuf(in.rdbuf());
	string RW[8] = { "if", "then", "else", "end", "repeat", "until", "read", "write" };
	char x; string y, z, s; int f = 0; 
	while (!cin.eof())
	{
		cin >> x;
	loop:   if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122) && !cin.eof())
	{
		while (((x >= 65 && x <= 90) || (x >= 97 && x <= 122)) && !cin.eof())
		{
			y.push_back(x);
			cin >> x;
		}
		for (int i = 0; i < y.length(); i++)
		{
			if (f)i = 0;  f = 0; z = y[i];
			for (int j = i + 1; j < y.length(); j++)
			{
				z.push_back(y[j]);
				for (int k = 0; k < 8; k++)
				{
					if (z == RW[k])
					{
						s = y.substr(0, i);
						y = y.substr(j + 1, y.length() - (j + 1));
						if (s != ""){
							cout << s << " : identifier" << endl; tokens->push_back(s); types->push_back("identifier");
						}
						cout << z << " : reserved word" << endl;
						tokens->push_back(z); types->push_back("reserved word");
						f = 1;  s = ""; break;
					}
				}if (f)break;
			}z = "";
		}
		if (y != ""){
			cout << y << " : identifier" << endl; tokens->push_back(y); types->push_back("identifier");
		}
	}
			y = "";

			if (!cin.eof()){
				switch (x)
				{
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				{
					while (x >= 48 && x <= 57 && !cin.eof())
					{
						y.push_back(x);
						cin >> x;
					}
					cout << y << " : number" << endl;
					tokens->push_back(y); types->push_back("number");
					y = "";
					goto loop;
				}
				case '+': {cout << "+" << " : special symbol" << endl; tokens->push_back("+"); types->push_back("special symbol"); break; }
				case '-':{ cout << "-" << " : special symbol" << endl; tokens->push_back("-"); types->push_back("special symbol"); break; }
				case '*':{ cout << "*" << " : special symbol" << endl; tokens->push_back("*"); types->push_back("special symbol"); break; }
				case '/':{ cout << "/" << " : special symbol" << endl; tokens->push_back("/"); types->push_back("special symbol"); break; }
				case ';': {cout << ";" << " : special symbol" << endl; tokens->push_back(";"); types->push_back("special symbol"); break; }
				case '<': {cout << "<" << " : special symbol" << endl; tokens->push_back("<"); types->push_back("special symbol"); break; }
				case '(':{ cout << "(" << " : special symbol" << endl; tokens->push_back("("); types->push_back("special symbol"); break; }
				case ')': {cout << ")" << " : special symbol" << endl; tokens->push_back(")"); types->push_back("special symbol"); break; }
				case '=': {cout << "=" << " : special symbol" << endl; tokens->push_back("="); types->push_back("special symbol"); break; }
				case ':':{ y.push_back(x); cin >> x; if (x == '='){ cout << ":=" << " : assignment" << endl; tokens->push_back(":="); types->push_back("assignment"); y = ""; break; }
						 else { cout << ":" << " : special symbol" << endl; tokens->push_back(":"); types->push_back("special symbol"); goto loop; } }
				case '{':
				{
					cin >> x;
					while (x != '}' && !cin.eof())
						cin >> x;

					break;
				}
				default:{cout << "ERROR" << endl; }
				}
			}
	}
	
}