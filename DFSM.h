#pragma once
#include <string>
#include <set>

using namespace std;

enum IdentifierStates { InitialIState, InvalidIdentifier, ValidIdentifier };
enum RealStates {
     InitialRState, BeginSignedNumber, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart,
     BeginNumberWithExponent, BeginNumberWithSignedExponent, NumberWithExponent, InvalidReal
};
//enum RealStates { InitialRState, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart, InvalidReal };
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

/*
class RealDFSM : public DFSM {
public:
     RealDFSM() {
          startingState = InitialRState;
          for (int i = 0; i < 7; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(Integer);
          finalStates.insert(NumberWithFractionalPart);
          finalStates.insert(NumberWithExponent);
     }
	 

     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];


               //FSM implementation
               switch (currentState) {

               case InvalidReal:
                    break;

               case InitialRState:
                    if (currentChar == '+' || currentChar == '-')
                         currentState = BeginSignedNumber;
                    else if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginSignedNumber:
                    if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case Integer:
                    if (isdigit(currentChar))
                         break;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithFractionalPart:
                    if (isdigit(currentChar))
                         currentState = NumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case NumberWithFractionalPart:
                    if (isdigit(currentChar))
                         break;
                    else if (tolower(currentChar) == 'e')
                         currentState = BeginNumberWithExponent;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithExponent:
                    if (isdigit(currentChar))
                         currentState = NumberWithExponent;
                    else if (currentChar == '+' || currentChar == '-')
                         currentState = BeginNumberWithSignedExponent;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithSignedExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidReal;
                    break;

               case NumberWithExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidReal;
                    break;
               }


               if (i == input.size() - 1) {
                    set<int>::iterator p = finalStates.find(currentState);
                    if (p == finalStates.end())//The current state is not in the set of final states
                         return false;
                    else                       //Otherwise the current state is a final state
                         return true;
               }
          }
     }
};
*/
class RealDFSM : public DFSM {
public:
     RealDFSM() {
          startingState = InitialRState;
          for (int i = 0; i < 7; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(Integer);
          finalStates.insert(NumberWithFractionalPart);
          finalStates.insert(NumberWithExponent);
     }


     virtual bool processInput(string input, string &buffer) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];


               //FSM implementation
               switch (currentState) {

               case InvalidReal:
                    break;

               case InitialRState:
                    if (currentChar == '+' || currentChar == '-')
                         currentState = BeginSignedNumber;
                    else if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginSignedNumber:
                    if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case Integer:
                    if (isdigit(currentChar))
                         break;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithFractionalPart:
                    if (isdigit(currentChar))
                         currentState = NumberWithFractionalPart;
                    else
                         currentState = InvalidReal;
                    break;

               case NumberWithFractionalPart:
                    if (isdigit(currentChar))
                         break;
                    else if (tolower(currentChar) == 'e')
                         currentState = BeginNumberWithExponent;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithExponent:
                    if (isdigit(currentChar))
                         currentState = NumberWithExponent;
                    else if (currentChar == '+' || currentChar == '-')
                         currentState = BeginNumberWithSignedExponent;
                    else
                         currentState = InvalidReal;
                    break;

               case BeginNumberWithSignedExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidReal;
                    break;

               case NumberWithExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidReal;
                    break;
               }


               if (i == input.size() - 1) {
                    set<int>::iterator p = finalStates.find(currentState);
                    if (p == finalStates.end())//The current state is not in the set of final states
                         return false;
                    else                       //Otherwise the current state is a final state
                         return true;
               }
          }
     }
};
class IntegerDFSM : public DFSM {
public:
     IntegerDFSM() {

     }
};
