#pragma once
#include <string>
#include <set>

using namespace std;

enum IdentifierStates { InitialIState, ValidIdentifier, InvalidIdentifier, TerminateIdentifier };
enum IdentifierInputs  { letter, $, id_digit, id_other };

enum RealStates { InitialRState, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart, InvalidReal, TerminateReal };
enum RealInputs { r_digit, period, r_other };

enum IntegerStates { InitialIntState, ValidInteger, InvalidInteger, TerminateInteger };
enum IntegerInputs { i_digit, i_other };

class DFSM {
protected:
     int startingState;
     int currentState;
     set<int> states;
     set<int> inputs;
     set<int> finalStates;
public:
     virtual bool processInput(string, string&) = 0;
     virtual int inputType(char) = 0;
};



class IdentifierDFSM : public DFSM {
private:
     int transitionTable[4][4];
public:
     IdentifierDFSM() {
          startingState = InitialIState;
          currentState = startingState;
          for (int i = 0; i < 4; i++)
               states.insert(i);
          for (int i = 0; i < 4; i++)
               inputs.insert(i);
          finalStates.insert(ValidIdentifier);
          finalStates.insert(TerminateIdentifier);

         //State transition table for an identifier
         //                      |  0       1      2         3
         //                      |letter    $    digit     other
         //   -------------------|------------------------------ 
         //  0 Starting State    |  1       2      2         2
         //  1 Valid Identifier  |  1       1      1         3
         //  2 Invalid Identifier|  2       2      2         2
         //  3 Terminate Iden.   |  0       0      0         0

          transitionTable[InitialIState][letter] = ValidIdentifier;
          transitionTable[InitialIState][$] = InvalidIdentifier;
          transitionTable[InitialIState][id_digit] = InvalidIdentifier;
          transitionTable[InitialIState][id_other] = InvalidIdentifier;
          transitionTable[ValidIdentifier][letter] = ValidIdentifier;
          transitionTable[ValidIdentifier][$] = ValidIdentifier;
          transitionTable[ValidIdentifier][id_digit] = ValidIdentifier;
          transitionTable[ValidIdentifier][id_other] = TerminateIdentifier;
          transitionTable[InvalidIdentifier][letter] = InvalidIdentifier;
          transitionTable[InvalidIdentifier][$] = InvalidIdentifier;
          transitionTable[InvalidIdentifier][id_digit] = InvalidIdentifier;
          transitionTable[InvalidIdentifier][id_other] = InvalidIdentifier;
          transitionTable[TerminateIdentifier][letter] = InitialIState;
          transitionTable[TerminateIdentifier][$] = InitialIState;
          transitionTable[TerminateIdentifier][id_digit] = InitialIState;
          transitionTable[TerminateIdentifier][id_other] = InitialIState;
     }

     //Finite State Machine for validating identifier tokens
     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               if (currentState == TerminateIdentifier || currentState == InvalidIdentifier)
                    break;
               currentChar = input[i];
               currentState = transitionTable[currentState][inputType(currentChar)];
               if (currentState == ValidIdentifier)
                    buffer += currentChar;
          }
          //The state should be correctly set by the FSM
          if (currentState == InvalidIdentifier)
               return false;
          else
               return true;
     }

     virtual int inputType(char currentChar) {
          if (isalpha(currentChar))
               return letter;
          else if (currentChar == '$')
               return $;
          else if (isdigit(currentChar))
               return id_digit;
          else
               return id_other;
     }
};





class IntegerDFSM : public DFSM {
private:
     int transitionTable[5][2];
public:
     IntegerDFSM() {
          startingState = InitialIntState;
          for (int i = 0; i < 3; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(ValidInteger);
          finalStates.insert(TerminateInteger);

          //State transition table for an integer
          //                      |  0        1  
          //                      |digit    other 
          //   -------------------|---------------
          //  0 Starting State    |  1       2    
          //  1 Valid Integer     |  1       3      
          //  2 Invalid Integer   |  2       2      
          //  3 Terminate Integer |  0       0

          transitionTable[InitialIntState][i_digit] = ValidInteger;
          transitionTable[InitialIntState][i_other] = InvalidInteger;
          transitionTable[ValidInteger][i_digit] = ValidInteger;
          transitionTable[ValidInteger][i_other] = TerminateInteger;
          transitionTable[InvalidInteger][i_digit] = InvalidInteger;
          transitionTable[InvalidInteger][i_other] = InvalidInteger;
          transitionTable[TerminateInteger][i_digit] = InitialIntState;
          transitionTable[TerminateInteger][i_other] = InitialIntState;
     }

     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               if (currentState == TerminateInteger || currentState == InvalidInteger)
                    break;
               currentChar = input[i];
               currentState = transitionTable[currentState][inputType(currentChar)];
               if (currentState == ValidInteger)
                    buffer += currentChar;
          }
          //The state should be correctly set by the FSM
          if (currentState == InvalidInteger)
               return false;
          else
               return true;
     }

     virtual int inputType(char currentChar) {
          if (isdigit(currentChar))
               return i_digit;
          else
               return i_other;
     }
};





class RealDFSM : public DFSM {
private:
     int transitionTable[6][3];
public:
     RealDFSM() {
          startingState = InitialRState;
          for (int i = 0; i < 5; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(NumberWithFractionalPart);
          finalStates.insert(TerminateReal);
          
          //State transition table for an identifier
          //                      |  0       1         2
          //                      |digit   period    other
          //   -------------------|-------------------------
          //  0 Starting State    |  1       4        4
          //  1 Integer           |  1       2        4
          //  2 Begin # with frac.|  3       4        4
          //  3 # with frac. part |  3       5        5
          //  4 Invalid Real      |  4       4        4
          //  5 Terminate Real    |  0       0        0 

          transitionTable[InitialRState][r_digit] = Integer;
          transitionTable[InitialRState][period] = InvalidReal;
          transitionTable[InitialRState][r_other] = InvalidReal;
          transitionTable[Integer][r_digit] = Integer;
          transitionTable[Integer][period] = BeginNumberWithFractionalPart;
          transitionTable[Integer][r_other] = InvalidReal;
          transitionTable[BeginNumberWithFractionalPart][r_digit] = NumberWithFractionalPart;
          transitionTable[BeginNumberWithFractionalPart][period] = InvalidReal;
          transitionTable[BeginNumberWithFractionalPart][r_other] = InvalidReal;
          transitionTable[NumberWithFractionalPart][r_digit] = NumberWithFractionalPart;
          transitionTable[NumberWithFractionalPart][period] = TerminateReal;
          transitionTable[NumberWithFractionalPart][r_other] = TerminateReal;
          transitionTable[InvalidReal][r_digit] = InvalidReal;
          transitionTable[InvalidReal][period] = InvalidReal;
          transitionTable[InvalidReal][r_other] = InvalidReal;
          transitionTable[TerminateReal][r_digit] = InitialRState;
          transitionTable[TerminateReal][period] = InitialRState;
          transitionTable[TerminateReal][r_other] = InitialRState;
     }


     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               if (currentState == TerminateReal || currentState == InvalidReal)
                    break;
               currentChar = input[i];
               currentState = transitionTable[currentState][inputType(currentChar)];
               if (currentState != InvalidReal && currentState != TerminateReal)
                    buffer += currentChar;
          }
          //The state should be correctly set by the FSM
          if (currentState != NumberWithFractionalPart && currentState != TerminateReal) {
               buffer = "";
               return false;
          }
          else
               return true;
     }

     virtual int inputType(char currentChar) {
          if (isdigit(currentChar))
               return r_digit;
          else if (currentChar == '.')
               return period;
          else
               return r_other;
     }
};
