//imports
#include <iostream>
#include <cstring>
#include "node.h"

Node::Node() {
    //initialize
    data = '\0';
    next = nullptr;
    left = nullptr;
    right = nullptr;
}

Node::Node(char newData) {
    //initialize
    data = newData;
    next = nullptr;
    left = nullptr;
    right = nullptr;
}

//methods used in code, all just "getters and setters"

Node* Node::getLeft() {
    return left;
}

Node* Node::getRight() {
    return right;
}
char Node::getData() {
    return data;
}

Node* Node::getNext() {
    return next;
}

void Node::setLeft(Node* newLeft) {
    left = newLeft;
}

void Node::setRight(Node* newRight) {
    right = newRight;
}

void Node::setData(char newData) {
    data = newData;
}

void Node::setNext(Node* newNext) {
    next = newNext;
}
