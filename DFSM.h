#pragma once
#include <string>
#include <set>

using namespace std;

enum IdentifierStates { InitialIState, InvalidIdentifier, ValidIdentifier };

enum RealStates { InitialRState, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart, InvalidReal };

enum IntegerStates { InitialIntState, InvalidInteger, ValidInteger};

class DFSM {
protected:
     int startingState;
     set<int> states;
     int currentState;
     set<int> finalStates;
public:
     virtual bool processInput(string, string&) = 0;
};



class IdentifierDFSM : public DFSM {
public:
     IdentifierDFSM() {
          startingState = InitialIState;
          for (int i = 0; i < 3; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(ValidIdentifier);
     }

     //Finite State Machine for validating identifier tokens
     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];

               //FSM implementation
               switch (currentState) {

               case InvalidIdentifier: //We have entered a dead state
                    buffer = "";
                    return false; //Don't bother processing any more input

               case InitialIState:
                    if (!isalpha(currentChar))
                         currentState = InvalidIdentifier;
                    else {
                         buffer += currentChar;
                         currentState = ValidIdentifier;
                    }
                    break;

               case ValidIdentifier:
                    if (isalpha(currentChar) || currentChar == '$' || isdigit(currentChar)) { //If character is a letter, $, or digit
                         buffer += currentChar;
                         currentState = ValidIdentifier;
                    }
                    else                 //Else were encountered a space or some other character
                         return true;   //Since we are in a valid state, return true
                    break;
               }
          }
          //We will only reach this point if the input size is 1 character
          //However, the state will have been correctly set by the fsm
          if (currentState == InvalidIdentifier)
               return false;
          else
               return true;
     }
};

class RealDFSM : public DFSM {
public:
     RealDFSM() {
          startingState = InitialRState;
          for (int i = 0; i < 5; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(NumberWithFractionalPart);
     }


     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];


               //FSM implementation
			   switch (currentState) {

			   case InvalidReal:
				   buffer = "";
				   return false;

			   case InitialRState:
				   if (isdigit(currentChar)) {
					   currentState = Integer;
					   buffer += currentChar;
				   }
				   else
					   currentState = InvalidReal;
				   break;

			   case Integer:
				   if (isdigit(currentChar)) {
					   //Same state as before
					   buffer += currentChar;
					   break;
				   }
				   else if (currentChar == '.') {
					   currentState = BeginNumberWithFractionalPart;
					   buffer += currentChar;
				   }
				   else
					   currentState = InvalidReal;
				   break;

			   case BeginNumberWithFractionalPart:
				   if (isdigit(currentChar)) {
					   currentState = NumberWithFractionalPart;
					   buffer += currentChar;
				   }
				   else
					   currentState = InvalidReal;
				   break;

			   case NumberWithFractionalPart:
                       if (isdigit(currentChar)) {
                            //Same state as before
                            buffer += currentChar;
                            break;
                       }
                       else
                            return true;
                       break;
                  }
          }
          //We will only reach this point if the input size is 1 character
          //However, the state will have been correctly set by the fsm
          if (currentState != NumberWithFractionalPart) {
               buffer = "";
               return false;
          }
          else
               return true;
     }
};
class IntegerDFSM : public DFSM {
public:
     IntegerDFSM() {
          startingState = InitialIntState;
          for (int i = 0; i < 3; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(ValidInteger);
     }

     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];


               //FSM implementation
               switch (currentState) {

               case InvalidInteger:
                    buffer = "";
                    return false;

               case InitialIntState:
                    if (isdigit(currentChar)) {
                         currentState = ValidInteger;
                         buffer += currentChar;
                    }
                    else
                         currentState = InvalidInteger;
                    break;

               case ValidInteger:
                    if (isdigit(currentChar)) {
                         //Same state as before
                         buffer += currentChar;
                         break;
                    }
                    else
                         return true;
                    break;
               }
          }
          //We will only reach this point if the input size is 1 character
          //However, the state will have been correctly set by the fsm
          if (currentState == InvalidInteger) {
               buffer = "";
               return false;
          }
          else
               return true;
     }
};
