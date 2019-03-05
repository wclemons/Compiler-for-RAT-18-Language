#include "Lexer.h"
int main() { 
     Lexer lex;
     if (lex.getSourceCode("test2.txt")){
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
          table.writeTable();
          //table.addEntry(t);
     }
     return 0;    
}
