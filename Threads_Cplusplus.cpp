#include <iostream>
#include <thread>
#include <mutex>


using namespace std;

mutex myMutex;  // Mutex for protecting shared data

int sharedData = 0;

void incrementData(int id) {
  // Lock the mutex before accessing shared data
  // lock_guard<mutex> lock(myMutex); // unlocks the mutex after the scope ends
  myMutex.lock();// If tabbed out 2 might 
                                  // run before 1 or worse...
  for (int i = 0; i < 5; ++i) {
    // // Lock the mutex before accessing shared data
    // lock_guard<mutex> lock(myMutex);// If tabbed out 2 might 
    //                                 // run before 1 or worse...
    
    // Critical section: modify the shared data
    sharedData++;

    // Print the current state
     cout << "Thread " << id << ": Shared Data = " << sharedData << endl;

    // Unlock the mutex when done with shared data
    // The lock_guard will automatically unlock when it goes out of scope
  }
  cout << endl;
  myMutex.unlock();
}
class Node{
  public:
    int x;
    int y;
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* next = nullptr;
    Node(int x, int y){
      this->x=x;
      this->y=y;
    }

    void insert(int x,int y){
      Node* newNode = new Node(x,y);
      if(this->head == nullptr){
        this->head = newNode;
        this->tail = newNode;
      }else{
        newNode->next = this->head;
        this->head = newNode;
      }
    }

    void del(int value){
      Node* current = this->head;
      Node* prev = nullptr;
      // Traverse the list to find the node to be removed
      while (current && current->x != value) {
          prev = current;
          current = current->next;
      }
      // If the node is found, remove it
      if (current) {
        if (prev) {
          // Node to be removed is not the head
          prev->next = current->next;
        } else {
          // Node to be removed is the head
          head = current->next;
        }
        delete current;
      }
    }

    void insertAfter(int value){}
    void popHead(){}
    void popTail(){}
    void insertHead(){}
    void insertTail(){}

    void prints(){
      Node* current = this->head;
      int i = 0;
      while(current != nullptr){
        cout << "Node: " << i 
             << ", x = " << current->x 
             << ", y = " << current->y << endl;
        i++;
        current = current->next;
      }
    }
};

int main() {
  // // Create threads and pass the thread function
  thread t1(incrementData, 1);
  thread t2(incrementData, 2);
  thread t3(incrementData, 3);
  thread t4(incrementData, 4);

  // // Wait for threads to finish
  t1.join();
  t2.join();
  t3.join();
  t4.join();

  
  Node* node = new Node(7,8);
  node->insert(4, 5);
  node->insert(3, 2);
  node->insert(1, 0);
  node->insert(19, 9);
  node->insert(11, 20);
  node->prints();
  cout<<endl;
  node->del(3);
  node->prints();
  

  return 0;
}
