//Author: Tejas Pandit
//Last Edited: Pi Day - 3/14/24
//This code creates a Shunting yard Algorithm
//Worked mainly with Jazveer Kaler, also got help from Taaha Khan
//GeeksForGeeks and YouTube were helpful with this project

//imports
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//prototypes, WOW SO MANY!!!
void push(Node* &top, Node* newNode);
Node* pop(Node* &top);
Node* peek(Node* top);
void enqueue(Node* &front, Node* &rear, Node* newNode);
Node* dequeue(Node* &front);
bool isOperator(char c);
int precedence(char c);
void shuntingYard(const char* input, char* postfixExpression);
Node* expressionTree(const char* postfixExpression);
void infix(Node* root);
void prefix(Node* root);
void postfix(Node* root);

int main() {
    //initialize variables 
    Node* root = nullptr;
    Node* stackTop = nullptr;
    Node* queueFront = nullptr;
    Node* queueRear = nullptr;
    bool stillRunning = true;
    char command[10];
    char input[100];

    cout << endl << "Shunting Yard..." << endl;

    //runs until 'Quit' is entered
    while (stillRunning == true) {
        //get user input
        cout << endl << "Enter a command: " << endl;
        cout << "Calculate" << endl;
        cout << "Quit" << endl << endl;
        
        //get user input
        cin.get(command, 10);
        cin.clear();
        cin.ignore(100, '\n');

	//end while loop
        if (strcmp(command, "Quit") == 0) {
	  cout << "Goodbye..." << endl;
	  stillRunning = false;
        }
        
        else if (strcmp(command, "Calculate") == 0) {
            
	    cout << "Enter an equation in infix notation: "; //get an equation from the user
            cin.getline(input, 100);
            
            char postfixExpression[100];
            shuntingYard(input, postfixExpression); //shunting yard function call

            root = expressionTree(postfixExpression); //expression tree build call
            
            //print out different forms of notation by calling print functions
            cout << "Postfix Expression: " << postfixExpression << endl;
            cout << "Infix Notation: ";
            infix(root);
            cout << endl;
            cout << "Prefix Notation: ";
            prefix(root);
            cout << endl;
            cout << "Postfix Notation: ";
            postfix(root);
            cout << endl;
        }
    }
    return 0;
}

//functions used for the stack
//push adds a new node to the top
void push(Node* &top, Node* newNode) {
    newNode->setNext(top);
    top = newNode;
}

//return the top node
Node* peek(Node* top) {
    if (top == nullptr) {
        //cout << "Stack is empty";
        return nullptr;
    }
    return top;
}

//remove and return the top node
Node* pop(Node* &top) {
    if (top == nullptr) {
        //cout << "Hello there!";
        return nullptr;
    }
    Node* data = top;
    top = top->getNext();
    return data;
}


//queue
void enqueue(Node* &front, Node* &rear, Node* newNode) {
    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->setNext(newNode);
        rear = newNode;
    }
}

Node* dequeue(Node* &front) {
    if (front == nullptr) {
        //cout << "Queue is empty";
        return nullptr;
    }
    Node* data = front;
    front = front->getNext();
    return data;
    
}

//all of the valid operators
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

//precedence - matters when pushing operators to stack
int precedence(char c) {
    //+ and - have lowest precedence
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    //carats added, have highest precedence
    else if (c == '^')
        return 3;
    else if (c == '(' || c == ')')
        return 0;
    return 0;
}


//shunting yard algorithm, get some help from Taaha here
void shuntingYard(const char* input, char* postfixExpression) {
    Node* operatorStack = nullptr;
    Node* outputQueueFront = nullptr;
    Node* outputQueueRear = nullptr;
    int i = 0;

    while (input[i] != '\0') {
        char token = input[i];
        if (token == '(')
            push(operatorStack, new Node(token));
        else if (isdigit(token))
            enqueue(outputQueueFront, outputQueueRear, new Node(token));
        
        else if (token == ')') {
            while (operatorStack != nullptr && peek(operatorStack)->getData() != '(')
                enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));
            pop(operatorStack);
        } 
        
        else if (isOperator(token)) {
            while (operatorStack != nullptr && precedence(peek(operatorStack)->getData()) >= precedence(token) && peek(operatorStack)->getData() != '(')
                enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));
            push(operatorStack, new Node(token));
        }
        i++;
    }

    while (operatorStack != nullptr)
        enqueue(outputQueueFront, outputQueueRear, pop(operatorStack));
    Node* current = outputQueueFront;
    int j = 0;
    while (current != nullptr) {
        postfixExpression[j++] = current->getData();
        current = current->getNext();
    }
    postfixExpression[j] = '\0';
}

//expression tree function, got some help here too
Node* expressionTree(const char* postfixExpression) {
    Node* nodeStack = nullptr;
    int i = 0;
    //some error here I don't know :(
    //fixed :)
    while (postfixExpression[i] != '\0') {
        char token = postfixExpression[i];
        Node* newNode = new Node(token);
        if (!isOperator(token)) {
            newNode->setLeft(nullptr);
            newNode->setRight(nullptr);
        } 
        
        else {
            Node* right = pop(nodeStack);
            Node* left = pop(nodeStack);
            newNode->setLeft(left);
            newNode->setRight(right);
        }
        push(nodeStack, newNode);
        i++;
    }
    return pop(nodeStack);
}

//print functions
void infix(Node* root) {
    if (root) {
        if (isOperator(root->getData()) && root->getData() != '(')
            cout << "(";
        infix(root->getLeft());
        cout << root->getData();
        infix(root->getRight());
        if (isOperator(root->getData()) && root->getData() != ')')
            cout << ")";
    }
}

void prefix(Node* root) {
    if (root) {
        cout << root->getData();
        prefix(root->getLeft());
        prefix(root->getRight());
    }
}

void postfix(Node* root) {
    if (root) {
        postfix(root->getLeft());
        postfix(root->getRight());
        cout << root->getData();
    }
}
//some random code I played around with that didn't work
//WHY DOESN'T THIS WORK TIME TO RESTART AHHHHHHHHHHHH
/*
 for (char ch : infix) {
        if (isdigit(ch) || isalpha(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove the '('
        } else { // Operator
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
*/
