#pragma once
#include <string>
#include <set>

using namespace std;

enum IdentifierStates { InitialIState, InvalidIdentifier, ValidIdentifier };
enum RealStates {
     InitialRState, BeginSignedNumber, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart,
     BeginNumberWithExponent, BeginNumberWithSignedExponent, NumberWithExponent, InvalidState
};

class DFSM {
protected:
     int startingState;
     set<int> states;
     int currentState;
     set<int> finalStates;
public:
     virtual bool processInput(string) = 0;
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
     virtual bool processInput(string input) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];

               //FSM implementation
               switch (currentState) {

               case InvalidIdentifier: //We have entered a dead state
                    return false; //Don't bother processing any more input

               case InitialIState:
                    if (isdigit(currentChar))
                         currentState = InvalidIdentifier;
                    else if (!isalpha(currentChar) && currentChar != '_')
                         currentState = InvalidIdentifier;
                    else
                         currentState = ValidIdentifier;
                    break;

               case ValidIdentifier:
                    if (!isalpha(currentChar) && currentChar != '_' && !isdigit(currentChar)) //If character is not a letter, digit or underscore
                         currentState = InvalidIdentifier;
                    else { //Else it is a valid character
                         if (i == input.size() - 1) //If valid identifier and the whole string has been processed...
                              return true;
                         else
                              break;
                    }
                    break;
               }
          }
     }

};



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

     virtual bool processInput(string input) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];


               //FSM implementation
               switch (currentState) {

               case InvalidState:
                    break;

               case InitialRState:
                    if (currentChar == '+' || currentChar == '-')
                         currentState = BeginSignedNumber;
                    else if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidState;
                    break;

               case BeginSignedNumber:
                    if (isdigit(currentChar))
                         currentState = Integer;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidState;
                    break;

               case Integer:
                    if (isdigit(currentChar))
                         break;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidState;
                    break;

               case BeginNumberWithFractionalPart:
                    if (isdigit(currentChar))
                         currentState = NumberWithFractionalPart;
                    else
                         currentState = InvalidState;
                    break;

               case NumberWithFractionalPart:
                    if (isdigit(currentChar))
                         break;
                    else if (tolower(currentChar) == 'e')
                         currentState = BeginNumberWithExponent;
                    else
                         currentState = InvalidState;
                    break;

               case BeginNumberWithExponent:
                    if (isdigit(currentChar))
                         currentState = NumberWithExponent;
                    else if (currentChar == '+' || currentChar == '-')
                         currentState = BeginNumberWithSignedExponent;
                    else
                         currentState = InvalidState;
                    break;

               case BeginNumberWithSignedExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidState;
                    break;

               case NumberWithExponent:
                    if (isdigit(currentChar))
                         break;
                    else
                         currentState = InvalidState;
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

/*
For now, the real FSM can determine if it is an interger or a real.
class IntegerDFSM : public DFSM {
public:
     IntegerDFSM() {

     }
};
*/
