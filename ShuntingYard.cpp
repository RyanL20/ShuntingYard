#include <iostream>
#include <cstring>
#include <vector>

/* Shuting Yard Algorithm
 * Author: Ryan Le
 * 
 */

//define node for stack and queue
struct Node{
  char* value;
  Node* next;
  Node(char* newValue){
    value = newValue;
    next = NULL;
  }
};

//define function prototype for stack
void push(char* operation, Node* &head);
char* pop(Node* &sHead);
char * peek (Node* head);

//define function prototype for queue
void enqueue(char* num, Node* &front, Node* &rear);
void dequeue(Node* &front);

using namespace std;

int main() {
  
  char* input = new char[80];
  char* value_in;
  Node* stackHead = NULL;

  Node* queueRear = NULL;
  Node* queueFront = NULL;
  
  cin >> input;
  strcpy(value_in, input);
  enqueue(value_in, queueFront, queueRear);
  push(value_in, stackHead);
  cout << "peek " << peek (stackHead) << endl;
  
  cin >> input;
  strcpy(value_in, input);
  enqueue(value_in, queueFront, queueRear);

  cin >> input;
  strcpy(value_in, input);
  enqueue(value_in, queueFront, queueRear);
  dequeue(queueFront);

  //for testing queue
  while (queueFront != NULL) {
    cout << "queueFront " << queueFront->value << endl;
    queueFront = queueFront->next;
  }
  //for testing stack  
  while (stackHead != NULL) {
    cout << "stackHead value" << stackHead->value << endl;
    stackHead = stackHead->next;
    }
  //return 0;
  
  //cout << "pop Apple " << pop(stackHead) << endl;
  //cout << "Stack Head is: " << stackHead << endl;
  //cout << "peeek after" << peek (stackHead) << endl;
  
  //cout << "pop Oragne " << pop(stackHead) << endl;
  //cout << "peek after orange " << peek (stackHead) << endl;
  //  cout << pop(stackHead) << endl;
}

//push function
void push(char* operation, Node* &head){
  Node* newNode = new Node(strdup(operation));
  if(head == NULL){
    head = newNode;
    
  }else{
    cout << "head " << head << endl;
    Node* temp = head;
    cout << "temp " << temp << endl;
    newNode->next = temp;
    head = newNode;
    cout << "head " << head << endl;
  }
}

//peek function
char* peek(Node* head){
  return head->value;
}

//pop function
char* pop(Node* &head) {
  char* datapop = head->value;
  Node* toDelete = head;
  head = head->next;
  delete toDelete;
  return datapop;
}

void enqueue(char* num, Node* &front, Node* &rear) {
    Node* newNode = new Node(strdup(num));

    // assign front and rear to the same node.
    if (front == NULL and rear == NULL) {
      front = newNode;
      rear = newNode;
    } else {
      rear->next = newNode;
      rear = newNode;
    }
    
}

void dequeue(Node* &front) {
  Node* temp = front->next;
  delete(front);
  front = temp;
}
