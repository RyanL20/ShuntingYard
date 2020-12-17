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

//node struct for the expression tree
struct treeNode{
  char* value;
  treeNode* left;
  treeNode* right;
  treeNode(char* newValue){
    value = newValue;
    right = NULL;
    left = NULL;
  }
};


//define function prototype for stack
void push(char* operation, Node* &head);
char* pop(Node* &sHead);
char * peek (Node* head);

//define function prototype for queue
void enqueue(char* num, Node* &front, Node* &rear);
void dequeue(Node* &front);

int chk_op (char op);
void postfix_Tree (treeNode* &root, Node* &queueFront);

void printInfix(treeNode* root);
void printPrefix(treeNode* root);
void printPostfix(treeNode* root);

using namespace std;

int main() {
  
  char input[80];
  char* value_in = new char[80];
  Node* stackHead = NULL;

  Node* queueRear = NULL;
  Node* queueFront = NULL;

  treeNode* root = NULL;
  
  cout << "Enter a mathematical expression:" << endl;
  cout << "Ex: 2+(3*(8-4))=" << endl;
  cin >> input;
  cout << input << " input" << endl;

  int i = 0;
  int j = 0;
  char num[80] = {'\0'};
  char op[2];

  while(input[i] != '\0') {
   
    // process expression input
    if (isdigit(input[i])) {    // store a digit for a complete nums; reset j after number is enqueue.
	num[j] = input[i];
	j++;
    }
    else { // for operator and ()
	// enqueue a complete number
        if (num[0] != '\0') {
          //enqueue number
          enqueue(num, queueFront, queueRear);
          //cout << num << "-Debug- enqueue num " << num << endl;

	  //reset num array
	  int a = 0; j = 0;
	  while (num[a] != '\0') {
             num[a] = {'\0'};
             a++;
	  }
	}


	if (input[i] == '(' ) {  // push ( on the stack
	  op[0] = input[i];
	  //cout << "push op" << endl;
	  push(op, stackHead);
	}
	else if ( input[i] == ')' ) {  // enque op until ) and then remove ( from stack
           while (strcmp(peek(stackHead), "(") !=0) {
	     enqueue(pop(stackHead), queueFront, queueRear);
           }
	   pop(stackHead);
	   
	}
	else if (input[i] != '=' ) {  // arithmatic operators.
	  //push and pop operator based on precedence
          op[0] = input[i];
          
	  // Need to pop operator that has higher precedent operation ^, *, /, + -
          while ((stackHead !=NULL) && ((chk_op(stackHead->value[0]) > chk_op(op[0])) || ((chk_op(stackHead->value[0]) == chk_op(op[0])) && op[0] != '^')) && (stackHead->value[0] != '(')) {
	    //cout << "enqueue op " << endl;
            enqueue(pop(stackHead), queueFront, queueRear);
          }
	  
	  //push operator in stack
	  push(op, stackHead);
	}

	
    } // end of else

    i++;

  } // end of while

    

  // pop operation then put on the queue
  while(stackHead != NULL) {
    enqueue(pop(stackHead), queueFront, queueRear);
  }
  
  // binary tree express based on postfix 
  postfix_Tree(root, queueFront);
  
  //ask which on to print
  cout << "Do you want to print out as 'Infix', 'Prefix', 'Postfix', or 'All' ?" << endl; 
  char printtype[80];
  cin >> printtype;
  if (strcmp(printtype, "Infix") == 0) {
    cout << "Infix " << endl;
    printInfix (root);
  }
  else if (strcmp(printtype, "Prefix") == 0) {
    cout << "Prefix " << endl;
    printPrefix (root);
  }
  else if (strcmp(printtype, "Postfix") == 0) {
    cout << "Postfix " << endl;
    printPostfix (root);
  }
  else if (strcmp(printtype, "All") == 0) {
  cout << "Infix " << endl;
  printInfix (root);
  
  cout << endl;
  cout << "Prefix " << endl;
  printPrefix (root);
  
  cout << endl;
  cout << "Postfix " <<endl;
  printPostfix(root);
  }
  return 0;
}


//push function
void push(char* operation, Node* &head){
  Node* newNode = new Node(strdup(operation));
  if(head == NULL){
    head = newNode;
  }
  else{
    Node* temp = head;
    newNode->next = temp;
    head = newNode;
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

//enqueue function
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

//dequeue function
void dequeue(Node* &front) {
  Node* temp = front->next;
  delete(front);
  front = temp;
}

// set operation precedence highest -> lowest (^, *, /, + -) for comparison
int chk_op (char op) {
  if (op == '^') { return 3; }
  else if (op == '*') { return 2; }
  else if (op == '/') { return 2; }
  else if (op == '+') { return 1; }
  else if (op == '-') { return 1; }
  else { return 0; }
}


//https://www.youtube.com/watch?v=WHs-wSo33MM
//converts from queue to tree
void postfix_Tree(treeNode* &root, Node* &qHead){
  vector<treeNode*> treeStack;
  Node* currentNode = qHead;
  
  while(currentNode != NULL){
    //cout << postfix_Tree << endl;
    if (isdigit(currentNode->value[0])){
      treeStack.push_back(new treeNode(currentNode->value));
    }
    else {
      treeNode* newTreeNode = new treeNode(currentNode->value);
      newTreeNode->right = treeStack.back();
      treeStack.pop_back();
      newTreeNode->left = treeStack.back();
      treeStack.pop_back();
      treeStack.push_back(newTreeNode);
    }
    currentNode = currentNode->next;
  }
  root = treeStack[0];

}

//https://en.wikipedia.org/wiki/Binary_expression_tree
void printInfix (treeNode* root){
  if (root != NULL){
    if (!isdigit(root->value[0])){
      cout << "(";
    }
    printInfix (root->left);
    cout << root->value;
    printInfix (root->right);
    if (!isdigit(root->value[0])){
      cout << ")";
    }
  }
}

void printPrefix(treeNode* root){
  if (root != NULL){
    cout << root->value << " ";
    printPrefix(root->left);
    printPrefix(root->right);
  }
}

//tree to postfix
void printPostfix(treeNode* root){
  if (root!= NULL){
    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->value << " ";
    
  }
}


