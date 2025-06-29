#include <iostream>
/*
 *  Project 1
 *  Author: Michael Galloway
 *  Last update: 10/15/2023
 *  Program that simulates a simplified version of blackjack using a 14 sided
 *  die. A roll selects one of 2,3,4,5,6,7,8,9,10,10,10,10,11. Jack, Queen, and
 *  King are worth 10 while an Ace is 11 The player is given two rolls. The
 *  house, played by the computer, is given one roll. The player is shown the
 *  value of the house’s roll and given the option to stand or hit The house then
 *  hits till it is equel to 17 or higher. If either the player or the house hits
 *  over 21 they bust and lose the round If Player and House tie then the win
 *  goes to the House
 *
 */

using namespace std;

// returns a random number inclusively between (min,max)
int randRange(int min, int max) { return (rand() % ((max - min) + 1) + min); }

// randomly rolls a 2-10, Jack, Queen, King, or Ace and returns the value.
int rollDice() {
  int cards[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
  return cards[randRange(0, 12)];
}

// gets an acceptable wager from from the Player
int getWager(int money) {
  int wager;
  cout << "How much do you want to wager: ";

  // loop incase user puts bad input
  while (true) {
    cin >> wager;
    // ignore and reset if Player puts something other than a number
    cin.clear();
    cin.ignore(999, '\n');
    cout << endl;
    // check if Player put something other than a number
    if (!cin) {
      cout << "You didn't enter a valid number, please input a valid number: ";
      cin >> wager;
      // ignore and reset if Player puts something other than a number
      cin.clear();
      cin.ignore(999, '\n');
    }
    // if input was approriate return value
    if (wager <= money && wager >= 1) {
      cout << "You bet " << wager << " dollars." << endl << endl;
      return wager;
    } 
    else {
      // if input is greater than money or less than 0
      cout
          << "You can't wager that amount, please input an appropriate wager: ";
    }
  }
}

// function that returns the card name as a string
string roledCardName(int diceRoll) {
  string cardNames[] = {"10", "Jack", "Queen", "King"};
  if (diceRoll == 11){
    return "Ace";
  }
  // if value is 10 return a random choice of 10, Jack, King, or Queen
  if (diceRoll == 10){
    return cardNames[randRange(0, 3)];
  }
    // if 2-9 return int as a string
  else{
    return to_string(diceRoll);
  }
}

// funtion to return the outcome of Player's turn
void playerTurn(int money, int &wager, bool &bust, int &total, int &houseRoll) {
  // Players 1st two random draws and their total
  int drawCard1 = rollDice();
  int drawCard2 = rollDice();
  total = (drawCard1 + drawCard2);

  // tells the Player what cards they drew and their total
  cout << "You Draw a " << roledCardName(drawCard1) << " and "
       << roledCardName(drawCard2) << " and stand at " << total << endl;

  // tells the Player what card the house drew
  houseRoll = rollDice();
  cout << "The House rolled " << roledCardName(houseRoll) << " and stands at "
       << houseRoll << endl;

  // prompt the Player if they wish to hit or stand
  char hit;
  cout << endl << "Would you like to hit (y/n): ";
  cin >> hit;

  // line for clearity
  cout << endl;

  // handles if the Player puts a bunch of random input
  cin.ignore(999, '\n');
  // check if Player didnt say yes
  while (hit != 'y') {
    // if Player says no, break out of loop
    if (hit == 'n'){
      break;
    }
    // esle re-prompt the player
    cout << "You did not enter (y/n), please do so now: ";
    cin >> hit;
    cin.ignore(999, '\n');
  }
  // if yes draw add card to Player total and inform the Player
  if (hit == 'y') {
    int drawCard3 = rollDice();
    total += drawCard3;
    cout << "You drew a " << drawCard3 << " your total is " << total << endl
         << endl;
  }
  // if Player busts
  if (total > 21) {
    bust = true;
  }
}

// funtion to return the outcome of House's turn
void houseTurn(int &houseRoll, bool &bust, int &total) {
  // initial draw and add to Houses total
  int drawCard1 = rollDice();
  houseRoll += drawCard1;
  // give feed back to Player
  cout << "House draws a " << drawCard1 << " and stands at " << houseRoll
       << endl;
  // House hits till its total is 17 or higher
  while (houseRoll < 17) {
    drawCard1 = rollDice();
    houseRoll += drawCard1;
    cout << "House draws a " << drawCard1 << " and stands at " << houseRoll
         << endl;
  }
  // give Player feed back with a few extra lines for clerity
  cout << "You stand at " << total << " against the House's " << houseRoll
       << endl
       << endl;
  // eval if House has busted
  if (houseRoll > 21) {
    bust = true;
  }
}

// function to simulate the game to keep the main() clean
void game(int &wager, int &money, bool &bust, int &total, int &houseRoll) {
  cout << "Welcome to The BLACKJACK table!" << endl << endl;

  // Game loop contues indefantly untill Player quits for is out of money
  while (true) {
    wager = getWager(money);

    // call Players turn with current wager
    playerTurn(money, wager, bust, total, houseRoll);
    // use bust returned from playerTurn
    if (bust) {
      cout << "You busted sorry you lose the bet!" << endl;
      money -= wager;
      cout << "You now have " << money << " dollars" << endl;
    }

    // if Player busted skip this code block
    if (!bust) {
      // call House's turn
      houseTurn(houseRoll, bust, total);
      // check if House busted
      if (bust) {
        cout << "House busted you win the bet!" << endl;
        money += wager;
        cout << "You now have " << money << " dollars" << endl;
      }
      // see if Player has better score than Hosue
      else if (total > houseRoll) {
        cout << "You win the bet!" << endl;
        money += wager;
        cout << "You now have " << money << " dollars" << endl;
      }
      // if Player and House are equal House wins
      else {
        cout << "You lose the bet!" << endl;
        money -= wager;
        cout << "You now have " << money << " dollars" << endl;
      }
    }

    // reset bust after each round
    bust = false;

    // if Player is fully out of money break the loop
    if (money <= 0) {
      cout << "You are out of money, you lose the game." << endl;
      break;
    } 
    else {
      // else prompt Player for another round
      char playAnotherRound;
      cout << "Would you like to continue (y/n): ";
      cin >> playAnotherRound;
      cin.ignore(999, '\n');

      // check if Player said yes
      while (playAnotherRound != 'y') {
        // break the loop if Player is saying no
        if (playAnotherRound == 'n')
          break;
        // else prompt player to put in valid input
        cout << "You did not enter (y/n), please do so now: ";
        cin >> playAnotherRound;
        cin.ignore(999, '\n');
      }
      // line for clarity
      cout << endl;

      // if Player is done then break the loop and end the game
      if (playAnotherRound == 'n') {
        cout << "Thank you for playing! You have " << money << " dollars!"
             << endl;
        break;
      }
    }
  }
}

int main() {
  // seed random with current time
  srand(time(NULL));

  bool bust = false;
  int wager;
  int houseRoll;
  int money = 101;
  int total = 0;
  

  game(wager, money, bust, total, houseRoll);
}
