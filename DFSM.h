#pragma once
#include <string>
#include <set>

using namespace std;

enum IdentifierStates {InitialIState, InvalidIdentifier, ValidIdentifier};
enum RealStates {InitialRState, BeginSignedNumber, SignedInteger, Integer, BeginNumberWithFractionalPart, NumberWithFractionalPart,
                  BeginNumberWithExponent, BeginNumberWithSignedExponent, NumberWithExponent, InvalidState};

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

               case InitialIState:
                    if (isdigit(currentChar))
                         currentState = InvalidIdentifier;
                    else
                         currentState = ValidIdentifier;
                    break;

               case InvalidIdentifier:
                    if (i == input.size() - 1) // If invalid identifier and the whole string has been processed...
                         return false;
                    break;

               case ValidIdentifier:
                    if (i == input.size() - 1) //If valid identifier and the whole string has been processed...
                         return true;
                    break;
               }
          }
     }

};



class RealDFSM : public DFSM {
public:
     RealDFSM() {
          startingState = InitialIState;
          for (int i = 0; i < 7; i++)
               states.insert(i);
          currentState = startingState;
          finalStates.insert(Integer);
          finalStates.insert(NumberWithExponent);
          finalStates.insert(NumberWithFractionalPart);
     }

     virtual bool processInput(string input) {
          char currentChar;
          for (int i = 0; i < input.size(); i++) {
               currentChar = input[i];

               
               //FSM implementation
               switch (currentState) {

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
                         currentState = SignedInteger;
                    else if (currentChar == '.')
                         currentState = BeginNumberWithFractionalPart;
                    else
                         currentState = InvalidState;
                    break;

               case Integer:

               case BeginNumberWithFractionalPart:
               case NumberWithFractionalPart:
               case BeginNumberWithExponent:
               case BeginNumberWithSignedExponent:
               case NumberWithExponent:
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
