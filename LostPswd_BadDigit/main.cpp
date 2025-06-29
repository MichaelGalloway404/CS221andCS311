#include <iostream>
#include <iomanip>

using namespace std;
/*
 *  Lab 2
 *  Author: Michael Galloway
 *  Last update: 10/8/2023
 *  Problem: I need my password. The key pad numbers 1, 4, and 7 are broken.
 *  The following program checks the users input for bad digits and return the sum
 *  of the two next acceptable passwords followed by 147# else if input is without
 *  bad digits the new password is returned.
 *
 */

// checks is a nmber contains a specific digit
bool containsBadDigit(int number, int digit){
  // loop through numbers 0-999
  for(int i=0;i<3;i++){
    // check ones place for bad digit
    if(number%10 == digit){
      return true;
    }
    // divide number so we can check ones place next loop
    number /= 10;
  }
  // if we are here there is no bad digit
  return false;
}

// calculates the next higher available number
int nextHigherNum(int number){
  // increment number until its acceptable
  while(containsBadDigit(number, 1) || containsBadDigit(number, 4) || containsBadDigit(number,7)){
    number += 1;
  }
  return number;
}

// calculates the next lower available number
int nextLowerNum(int number){
  // decrement number until its acceptable
  while(containsBadDigit(number, 1) || containsBadDigit(number, 4) || containsBadDigit(number, 7)){
    number -= 1;
  }
  return number;
}

// calculates the sum of a bad number and outputs it 
// or output the input of it is an acceptable number
void calcNewNumber(int input){
  if(containsBadDigit(input, 1) || containsBadDigit(input, 4) || containsBadDigit(input,7)){
    cout << "Error bad digits the sum of you next two available codes are: "
         << (nextHigherNum(input) + nextLowerNum(input)) << " 147#" << endl;
  }
  else{
    // fill in a single or two digit password with leading zeros
    cout << "You inputed: " << input << " good choice! Your pass code is now "
         << setw(3) << setfill('0') << input << endl;
  }
}

int main() {
  int input;

  cout << "Please inputs a desired secret code. "
       << "Your code must be between 0 and 999: ";
  
  cin >> input;
  
  // check if input is a number
  if(!cin){
    cout << "Sorry you did not input a number" << endl;
  }
  else{
    // check for accepted range
    if(input <= 999 && input >= 0){
      calcNewNumber(input);
    }
    else
      cout << "Sorry passward must be btween 0-999" << endl;
  }
}