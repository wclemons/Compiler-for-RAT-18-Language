#pragma once
#include <string>
#include <list>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

const short NUM_OPS = 19;
const short NUM_SEPS = 11;
const short NUM_KEYWORDS = 88;

const char OPERATORS[NUM_OPS] = { '+', '-', '%', '&', '/', '*', '<', '>', '=', '==', '<=', '>=', '!=', '.', '&&', '||', '!', '!=', '|' };
const char SEPARATORS[NUM_SEPS] = { '(', ')', ';', '{', '}', '[', ']', ',', '\"', '\'' , ':'};
const string KEYWORDS[NUM_KEYWORDS] = { "while", "if", "else", "for", "do", "alignas", "alignof", "and", "and_eq", "asm", "auto",
                              "bitand", "bitor", "bool","break", "case", "catch", "char", "char16_t", "char32_t", "class",
                              "compl", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete",
                              "do","double", "dynamic_cast", "else", "enum", "explicit", "export","extern", "false", "float",
                              "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new",
                              "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
                              "public", "register", "reinterpret_cast", "return", "short", "sizeof", "static", "static_assert",
                              "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try",
                              "typedef", "typeid", "typename", "union", "unsigned","using", "virtual", "void", "volatile",
                              "wchar_t", "while", "xor", "xor_eq" };


const string TOKEN_ARRAY[] = { "keyword", "identifier", "separator", "operator", "literal", "real", "endString" };
enum TokenTypes {Keyword, Identifier, Separator, Operator, Literal, Real, EndString};

struct Token {
     string tokenType;
     string lexeme;
     int startingIndex;
     Token(string t, string l, int i) : tokenType(t), lexeme(l), startingIndex(i) {};
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
     Lexer() : sourceCode(""), indexCursor(0) {};
     Token nextToken(); //Parses string to find the next available token
     bool getSourceCode(string); //Opens and reads file contents into a string
     bool isKeyword(string);
     bool isSeparator(char);
     bool isIdentifier(string);
     bool isOperator(char);
     bool isReal(string);
};
