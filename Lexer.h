#pragma once
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

/*

**********************************************************
		Tokens			Lexemes
		keyword			while, if, else, for, do, alignas, alignof, and, and_eq, asm, auto, bitand, bitor, bool,
						break, case, catch, char, char16_t, char32_t, class, compl, const, constexpr, const_cast,
						continue, decltype, default, delete, do, double, dynamic_cast, else, enum, explicit, export, 
						extern, false, float, for, friend, goto, if, inline, int, long, mutable, namespace, new,
						noexcept, not, not_eq, nullptr, operator, or, or_eq, private, protected, public, register, 
						reinterpret_cast, return, short, sizeof, static, static_assert, static_cast, struct, switch,
						template, this, thread_local, throw, true, try, typedef, typeid, typename, union, unsigned, 
						using, virtual, void, volatile, wchar_t, while, xor, xor_eq

		separator		(, ), [, ], {, }, ;, :, \n, \t, space

		identifier		any variable name

		operator		+, -, %, /, *, <, >, =, ==, <=, >=, !=, .

		real			any number (int, float, double, real)

*************************************************************
*/

/*
take in a file, read the file in different ways depending on the format, either in a while(!eof) and process 1-2 chars at a time,
or process 1 line of the file at a time
*/


/*						PROCESSING THE FILE IN A LOOP
infile
open file
vector<string> lexemeHolder
vector<string> tokenHolder
while(!eof)
	process a char/ char[] in the case of a keyword or real
	switch (fin)
		case(keyword lexeme)	
			call keyword_fsm function	//returns if/what valid keyword or not a valid keyword
		case(seperator lexeme)
			call seperator_fsm function		//returns if/what valid seperator or not a valid seperator
		case(identifier lexeme)
			call identifier_fsm function		//returns if/what valid identifier or not a valid identifier
		case(operator lexeme)
			call operator_fsm function		//returns if/what valid operator or not a valid operator
		case(real lexeme)
			call real_fsm function		//returns if/what valid real or not a valid real
		case(default)
			no lexeme					//throw an error

close file
*/
#pragma once
#include <string>
#include <list>
#include <cassert>
#include <iostream>
using namespace std;

enum TokenTypes { Keyword, Identifier, Separator, Operator, Literal, Real };


struct Token {
     string tokenType;
     string lexeme;
     int startingIndex;
     Token(string, string, int);
};

class SymbolTable {
private:
     list<Token> entries;
public:
     void addEntry(Token);
     void printTable();
};

class Lexer {
private:
     string sourceCode;
     int indexCursor;
public:
     SymbolTable nextToken(); //Parses string to find the next available token
     bool getSourceCode(string, string&); //Opens and reads file contents into a string
     bool isKeyword(string);
     bool isSeparator(string);
     bool isIdentifier(string);
     bool isOperator(string);
     bool isReal(string);

};
