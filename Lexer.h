#pragma once

#include <string>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

const short NUM_OPS = 8;
const short NUM_SEPS = 13;
const short NUM_KEYWORDS = 15;

const char OPERATORS[NUM_OPS] = { '*', '+', '-', '=', '/', '>', '<', '%'};

const char SEPARATORS[NUM_SEPS] = {'/', '(', ')', '{', '}', '[', ']', ',', '.', ':', ';', '!',' ' };

const string KEYWORDS[NUM_KEYWORDS] = { "int", "float", "bool", "if", "else", "then", "do", "while", 
                                        "whileend", "do", "doend", "for", "and", "or" , "function" };


/*		C++ Operators
{ '+', '-', '%', '&', '/', '*', '<', '>', '=', '==', '<=', '>=', '!=', '.', '&&', '||', '!', '!=', '|', '+=',
  '-=', '/=', '*=', '%=', ':', '::' };*/

/*        C++ Separators
{ ' ', '(', ')', ';', '{', '}', '[', ']', ',', '\"', '\'' };*/

/*		C++ keywords
"while", "if", "else", "for", "do", "alignas", "alignof", "and", "and_eq", "asm", "auto",
"bitand", "bitor", "bool","break", "case", "catch", "char", "char16_t", "char32_t", "class",
"compl", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete",
"do","double", "dynamic_cast", "else", "enum", "explicit", "export","extern", "false", "float",
"for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new",
"noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
"public", "register", "reinterpret_cast", "return", "short", "sizeof", "static", "static_assert",
"static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try",
"typedef", "typeid", "typename", "union", "unsigned","using", "virtual", "void", "volatile",
"wchar_t", "while", "xor", "xor_eq" };*/


struct Token {
     string tokenType;
     string lexeme;
     Token() : tokenType(""), lexeme("") {};
     Token(string t, string l) : tokenType(t), lexeme(l) {};
     Token(const Token& token) {
          tokenType = token.tokenType;
          lexeme = token.lexeme;
     }

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
     vector<string> sourceCode;
public:
     Lexer() : sourceCode() {};
     Token nextToken(); //Parses string to find the next available token
     bool getSourceCode(string); //Opens and reads file contents into a vector of strings
     bool isKeyword(string);
     bool isSeparator(char);
     bool isIdentifier(string, string&);
     bool isOperator(char);
     bool isReal(string, string&);
	bool isInteger(string, string&);
};
