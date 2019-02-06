#include "Lexer.h"

const int NUM_KW = 88;
const int NUM_OPS = 13;
const string OPERATORS[13] = { "+", "-", "%", "/", "*", "<", ">", "=", "==", "<=", ">=", "!=", "." };
const string KEYWORDS[88] = { "while", "if", "else", "for", "do", "alignas", "alignof", "and", "and_eq", "asm", "auto", 
                              "bitand", "bitor", "bool","break", "case", "catch", "char", "char16_t", "char32_t", "class", 
                              "compl", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete",
                              "do","double", "dynamic_cast", "else", "enum", "explicit", "export","extern", "false", "float",
                              "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new",
                              "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
                              "public", "register", "reinterpret_cast", "return", "short", "sizeof", "static", "static_assert", 
                              "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", 
                              "typedef", "typeid", "typename", "union", "unsigned","using", "virtual", "void", "volatile", 
                              "wchar_t", "while", "xor", "xor_eq" };

//Get the next token in the string leaving off from current index
Token Lexer::nextToken() {
     
}

bool Lexer::getSourceCode(string fileName, string &sourceCode) {
     ifstream fileHandler(fileName);
     if (fileHandler.fail()) {
          return false;
     }
     string temp;
     while (!fileHandler.eof()) {
          getline(fileHandler, temp);
          sourceCode += temp;
     }
     return true;
}

bool Lexer::isOperator(string input) {
     for (int i = 0; i < NUM_OPS; i++) {
          if (input == OPERATORS[i])
               return true;
     }
     return false;
}
