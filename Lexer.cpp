#include "Lexer.h"
#include "DFSM.h"
#include <iomanip>

bool Lexer::getSourceCode(string fileName) {
     ifstream fileHandler(fileName);
     if (fileHandler.fail()) {
          return false;
     }
     string temp;
     while (!fileHandler.eof()) {
          getline(fileHandler, temp);
          sourceCode += temp;
     }
     fileHandler.close();
     return true;
}


//Get the next token in the string leaving off from current index
Token Lexer::nextToken() {
     if (indexCursor == sourceCode.length()) {
          return Token(TOKEN_ARRAY[EndString], "\0", indexCursor);
     }

     int tokenStartIndex = indexCursor;
     string buffer = "";
     char currentCharacter = sourceCode[indexCursor]; //For readability
     buffer += currentCharacter;

     if (isalpha(currentCharacter) || currentCharacter == '_') {
          //Process as potential identifier or keyword
          //While there is a next available character in the string that is a letter, digit, or underscore...
          while (indexCursor + 1 <= sourceCode.length() - 1 && ( isalpha(sourceCode[indexCursor + 1]) || isdigit(sourceCode[indexCursor + 1])
                                                                 || sourceCode[indexCursor + 1] == '_' ))
          {
               currentCharacter = sourceCode[indexCursor + 1];
               buffer += currentCharacter;
               indexCursor++;
          }
          //Now we should have a string. Let's figure out what it is...
          if (buffer[0] == '_' && isIdentifier(buffer)) //We know it can't be a keyword if it starts with an '_'. Short circuit evaluation
               return Token("keyword", buffer, tokenStartIndex);
          else if (isKeyword(buffer)) //Otherwise, check if it is a keyword first
               return Token("keyword", buffer, tokenStartIndex);
          else if (isIdentifier(buffer)) //If not a keyword, check if it is a valid identifier
               return Token("keyword", buffer, tokenStartIndex);
          else {
               cout << "\n\nInvalid identifier\n\n";
               system("PAUSE");
          } 
     }
     else if (isdigit(currentCharacter)) {
          //Process as potential real number
     }
     else if (currentCharacter == '\"') {
          //We may be encountering a string literal
     }
     else {
          cout << "\n\nInvalid input\n\n";
          system("PAUSE");
     }
}

bool Lexer::isKeyword(string input) {
     for (int i = 0; i < NUM_KEYWORDS; i++) {
          if (input == KEYWORDS[i])
               return true;
     }
     return false;
}

bool Lexer::isIdentifier(string input) {
     IdentifierDFSM fsm;
     return fsm.processInput(input);
}

bool Lexer::isReal(string input) {
     return true;
}

bool Lexer::isOperator(char input) {
     for (int i = 0; i < NUM_OPS; i++) {
          if (input == OPERATORS[i])
               return true;
     }
     return false;
}

bool Lexer::isSeparator(char input) {
     for (int i = 0; i < NUM_SEPS; i++) {
          if (input == SEPARATORS[i])
               return true;
     }
     return false;
}



//-----------------------------------------------------------------------------------------------------------------------------

void SymbolTable::addEntry(Token t) {
     entries.push_back(t);
}

void SymbolTable::printTable() {
     if (entries.empty()) {
          cout << "\nNo entries\n";
          return;
     }
     cout << "    Token     |     Lexeme     |   Starting Index\n";
     cout << "----------------------------------------------------\n";
     for (list<Token>::iterator p = entries.begin(); p != entries.end(); p++) {
          cout << left << "  " << setw(12) << p->tokenType << "|  " << setw(14) << p->lexeme << "|  " << p->startingIndex << endl;
     }
}
