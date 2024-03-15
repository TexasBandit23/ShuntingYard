#ifndef NODE_H
#define NODE_H

class Node {
//private variables 
private:
    Node* next;
    Node* left;
    Node* right;
    char data;

//public variables
public:

    //methods all in node.cpp file
    Node();
    Node(char newData);
    //setters
    void setData(char newData);
    void setNext(Node* newNext);
    void setLeft(Node* newLeft);
    void setRight(Node* newRight);

    //getters
    char getData();
    Node* getNext();
    Node* getLeft();
    Node* getRight();
};

#endif
