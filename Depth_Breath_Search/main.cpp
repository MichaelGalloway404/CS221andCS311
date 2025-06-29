#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

bool canmove(int spot) {
  if (spot == 0 || spot == 88)
    return true;
  else
    return false;
}


int main() {

  int arr[10][10] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  
  {1, 99, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1},  
  {1, 0, 0, 1, 0, 1, 1, 1, 1, 1}, 
  {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},  
  {1, 0, 0, 0, 1, 0, 1, 1, 0, 1}, 
  {1, 1, 0, 1, 1, 0, 0, 0, 0, 1},  
  {1, 0, 0, 0, 1, 0, 1, 1, 1, 1}, 
  {1, 88, 1, 1, 1, 0, 0, 0, 0, 1}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };
  int arr2[10][10] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  
  {1, 99, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1},  
  {1, 0, 0, 1, 0, 1, 1, 1, 1, 1}, 
  {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},  
  {1, 0, 0, 0, 1, 0, 1, 1, 0, 1}, 
  {1, 1, 0, 1, 1, 0, 0, 0, 0, 1},  
  {1, 0, 0, 0, 1, 0, 1, 1, 1, 1}, 
  {1, 88, 1, 1, 1, 0, 0, 0, 0, 1}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  int row = 1;
  int col = 1;

  stack<int> stack;
  queue<int> q;

  int count = 1;
  int numMoves = 1;

  // stack depth 1st
  while (arr[row+1][col] != 88
       &&arr[row-1][col] != 88
       &&arr[row][col+1] != 88
       &&arr[row][col-1] != 88) {
    
    // over write current square
    // cout << "row=" << row << " col=" << col << " count=" << count << endl;
    arr[row][col] = count;
    
    // up
    if (canmove(arr[row - 1][col])) {
      // if can move add row then col to stack
      stack.push(row - 1);
      stack.push(col);
    }
    // down
    if (canmove(arr[row + 1][col])) {
      // if can move add row then col to stack
      stack.push(row + 1);
      stack.push(col);
    }
    // left
    if (canmove(arr[row][col - 1])) {
      // if can move add row then col to stack
      stack.push(row);
      stack.push(col - 1);
    }
    // right
    if (canmove(arr[row][col + 1])) {
      // if can move add row then col to stack
      stack.push(row);
      stack.push(col + 1);
    }
    
    col = stack.top();
    stack.pop();
    row = stack.top();
    stack.pop();
    
    numMoves++;
    count++;
    arr[row][col] = count;
  }

  // // //queqe breath 1st
  // // while (arr[row+1][col] != 88
  // //      &&arr[row-1][col] != 88
  // //      &&arr[row][col+1] != 88
  // //      &&arr[row][col-1] != 88) {

  // //   // over write current square
  // //   // cout << "row=" << row << " col=" << col << " count=" << count << endl;
  // //   arr[row][col] = count;

  // //   // up
  // //   if (canmove(arr[row - 1][col])) {
  // //     // if can move add row then col to stack
  // //     q.push(row - 1);
  // //     q.push(col);
  // //   }
  // //   // down
  // //   if (canmove(arr[row + 1][col])) {
  // //     // if can move add row then col to stack
  // //     q.push(row + 1);
  // //     q.push(col);
  // //   }
  // //   // left
  // //   if (canmove(arr[row][col - 1])) {
  // //     // if can move add row then col to stack
  // //     q.push(row);
  // //     q.push(col - 1);
  // //   }
  // //   // right
  // //   if (canmove(arr[row][col + 1])) {
  // //     // if can move add row then col to stack
  // //     q.push(row);
  // //     q.push(col + 1);
  // //   }

  // //   row = q.front();
  // //   q.pop();
  // //   col = q.front();
  // //   q.pop();

  // //   numMoves++;
  // //   count++;
  // //   arr[row][col] = count;
  // // }

  cout << "MAZE!\n";
  cout << "-------------------------------------------------------------\n";
  for (int i = 0; i < 10; i++) {
    cout << "| ";
    for (int j = 0; j < 10; j++) {

      if (arr2[i][j] > 9)
        cout << arr2[i][j] << "  | ";
      else
        cout << arr2[i][j] << "   | ";
    }
    cout << "\n-------------------------------------------------------------\n";
  }
  
  cout << endl;
  
  cout << "-------------------------------------------------------------\n";
  for (int i = 0; i < 10; i++) {
    cout << "| ";
    for (int j = 0; j < 10; j++) {

      if (arr[i][j] > 9)
        cout << arr[i][j] << "  | ";
      else
        cout << arr[i][j] << "   | ";
    }
    cout << "\n-------------------------------------------------------------\n";
  }

  cout << "number of moves: " << numMoves << endl;

}