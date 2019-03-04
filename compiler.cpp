#include "Lexer.h"
int main() { 
     Lexer lex;
     if (lex.getSourceCode("test.txt")){
          SymbolTable table;
          Token t;
          while (true) {
               t = lex.nextToken();
               if (t.tokenType == "endOfCode")
                    break;
               table.addEntry(t);
               
          }
          table.printTable();
          system("PAUSE");
          //table.addEntry(t);
     }
     return 0;    
}
