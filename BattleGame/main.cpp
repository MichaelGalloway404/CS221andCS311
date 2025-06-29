#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// returns a random number on inclusive interval (min,max)
int randRange(int min, int max) { 
  return (rand() % ((max - min) + 1) + min); 
  }
// prints menu options
void menu(string abilityName){
  cout << "a: Attack\n" << "b: Use " << abilityName << endl
       << "c: Use a Potion\n" << "Enter action: ";
}
// returns a stream of whos turn it is for output to file/terminal
string turn(string name, int health){
  stringstream streamToFile;
  streamToFile << "It's " << name << "'s turn. Current HP = " << health << endl;
  return streamToFile.str();
}

/*
  Function optionA() makes use of randRange() as its first arg
  to do random damage to victim and then prints output to file and terminal
  victims health and is passed by reference so changes are permanent
  outFile is also passed by reference so it is not auto-closed
*/
void optionA(int atkDamge, string attackerName, string victimName, int &victemHealth, ofstream &outFile){
  stringstream streamToFile;
  int AtkDMG = atkDamge;
  victemHealth -= AtkDMG;
  streamToFile << attackerName << " attacks " << victimName << " who takes " << AtkDMG
               << " of attack damage. New HP = " << victemHealth << endl; 
  cout << streamToFile.str();
  outFile << streamToFile.str();
}
/*
  Function optionB() makes use of randRange() as its first arg
  to do random Ability damage to victem and then prints output to file and terminal
  victims health and is passed by reference so changes are permanent
  outFile is also passed by reference so it is not auto-closed
*/
void optionB(int atkDamge, string attackerName, string attackerAbility, string victimName, int &victemHealth, ofstream &outFile){
  int AtkDMG = atkDamge;
  victemHealth -= AtkDMG;
  stringstream streamToFile;
  streamToFile << attackerName << " uses their " << attackerAbility << " on " << victimName
               << " who takes " << AtkDMG << " of ability damage. New HP = " << victemHealth << endl;
  cout << streamToFile.str();
  outFile << streamToFile.str();
}
/*
  Function optionC() makes use of randRange() as its first arg
  to heal target random amount and then prints output to file and terminal
  decrements potion count and checks potion quantity and uses appropriate outputs
  targest health and is passed by reference so changes are permanent along with potion count
  outFile is also passed by reference so it is not auto-closed
*/
void optionC(int amountToHeal, int &PotionCount, int &targetHealth, int starHP, string targetName, ofstream &outFile){
  stringstream streamToFile;
  if (PotionCount > 0) {
    PotionCount--;
    targetHealth += amountToHeal;
    if (targetHealth > starHP){ targetHealth -= (targetHealth - starHP); }
    streamToFile << targetName << " Drinks a potion healing for " << amountToHeal<< " HP points and has "
                 << PotionCount << "/3 potions left, HP = " << targetHealth << endl;
    cout << streamToFile.str();
    outFile << streamToFile.str();
  }
  else{
    streamToFile << targetName << " is out of potions!\n";
    cout << streamToFile.str();
    outFile << streamToFile.str();
  }
}

/*
Michael Galloway
CS 221 Winter 2023

A simple text-based game's battle system
Input to the program is a file named characterInfo.txt file contains five lines
line 1. Hero_Name Hero_Health Spell/Ability_Name
line 2. Monster_Name Monster_Health Spell/Ability_Name
line 3. Min_Attack_Damage Max_Attack_Damage
line 4. Min_Spell/Ability_Damage Max_Spell/Ability_Damage
line 5. Min_Potion Max_Potion
all output is sent to terminal and a file called battleResults.txt
the game consists of a series of turns with one decision of three choices each game (attack, use ability, use potion)
game loops until one character is out of HP.
*/
int main() {
  srand(time(NULL));
  
  int heroPotionCount = 3;
  int enemyPotionCount = 3;

  string heroName; string enemyName;
  string heroAbility; string enemyAbility;
  int heroHealth; int enemyHealth;

  // random range values
  int atkMin; int atkMax;
  int abilityMin; int abilityMax;
  int potionMin; int potionMax;

  stringstream streamToFile;
  ofstream outFile;
  outFile.open("battleResults.txt");
  
  ifstream inFile;
  inFile.open("characterInfo.txt");

  if (inFile.is_open()) {
    inFile >> heroName >> heroHealth >> heroAbility;
    inFile >> enemyName >> enemyHealth >> enemyAbility;
    inFile >> atkMin >> atkMax;
    inFile >> abilityMin >> abilityMax;
    inFile >> potionMin >> potionMax;
    // no further need of input file
    inFile.close();

    // using a string rather than a char allows user to input 'aaaa' but only 'a' is read
    // other wise if 'aaa' was put the loop would skip 3 switch statements
    string choice;

    int heroStartHealth = heroHealth;
    int enemyStartHealth = enemyHealth;


    streamToFile << heroName << " (" << heroHealth << " HP) will battle " 
                 << enemyName  << " (" << enemyHealth << " HP)" << endl;
    cout << streamToFile.str() << endl;
    outFile << streamToFile.str();

    // game loop ends if eather player has 0 or less HP
    while (heroHealth > 0 && enemyHealth > 0) {
      cout << turn(heroName, heroHealth);
      outFile << turn(heroName, heroHealth);
      
      menu(heroAbility);

      // allows input with spaces but wont use them
      cin.ignore(0,'\n');
      getline(cin,choice);
      // if input is more than one char is int or is not 'a','b', or 'c' promt user
      while(isdigit(choice[0]) || choice[0] < 'a' || choice[0] > 'c' || choice.length() > 1){
        cout << "Invalid Input, Enter action: ";
        cin.ignore(0,'\n');
        getline(cin,choice);
      }
      cout << endl;

      switch (choice[0]) {
        case 'a':
          optionA(randRange(atkMin, atkMax), heroName, enemyName, enemyHealth, outFile);
          break;
        case 'b':
          optionB(randRange(abilityMin, abilityMax), heroName, heroAbility, enemyName, enemyHealth, outFile);
          break;
        case 'c':
          optionC(randRange(potionMin, potionMax), heroPotionCount, heroHealth, heroStartHealth, heroName, outFile);
          break;
      }

      cout << endl;
      // end game early if enemy died last turn(other wise zombie enemy gets a free turn)
      if(enemyHealth <= 0){break;}
      
      cout << turn(enemyName, enemyHealth);
      outFile << turn(enemyName, enemyHealth);

      menu(enemyAbility);

      cin.ignore(0,'\n');
      getline(cin,choice);
      while(isdigit(choice[0]) || choice[0] < 'a'  || choice[0] > 'c' || choice.length() > 1){
        cout << "Invalid Input, Enter action: ";
        cin.ignore(0,'\n');
        getline(cin,choice);
      }
      cout << endl;

      switch (choice[0]) {
        case 'a':
          optionA(randRange(atkMin, atkMax), enemyName, heroName, heroHealth, outFile);
          break;
        case 'b':
          optionB(randRange(abilityMin, abilityMax), enemyName, enemyAbility, heroName, heroHealth, outFile);
          break;
        case 'c':
          optionC(randRange(potionMin, potionMax), enemyPotionCount, enemyHealth, enemyStartHealth, enemyName, outFile);
          break;
        }
      cout << endl;
    }
    // end game output
    if (heroHealth <= 0){
      // clear stream
      streamToFile.str("");
      streamToFile << "The " << heroName
           << " has been vanquished his mind ceases to wander..."; 
      cout << streamToFile.str();
      outFile << streamToFile.str();
      outFile.close();
      }
    else{
      // clear stream
      streamToFile.str("");
      streamToFile << "The " << enemyName << " has been destroyed and the " << heroName
           << "'s journey continues!"; 
      cout << streamToFile.str();
      outFile << streamToFile.str();
      outFile.close();
    }
  } 
  else {
    cout << "=INVALID FILE=\n";
  }
  outFile.close();
}