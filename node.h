//
//  node.h
//
//  Created by Elaina Teramoto
//  Copyright © 2017 Elaina Teramoto. All rights reserved.
//

#ifndef NODE_H
#define NODE_H

using namespace std;
template <typename T>
class Node {
    
public:
    Node ( int, int, Node<T>* = 0);
    T &getObject();
    void setNextPtr( Node<T> * );
    Node<T> *getNextPtr() const;
    int coef;
    int exponent;
    Node<T> *nextPtr;
}; // Node<T> class

template <typename T>
Node<T>::Node(int coefficient, int exponent, Node<T>* temp)
{
    
    this->coef = coefficient;
    this->exponent = exponent;
    this-> nextPtr = temp;
    
} // Node<T>::Node

template <typename T>
void Node<T>::setNextPtr( Node<T> *nextPtr )
{
    this->nextPtr = nextPtr;
} // Node<T>::setNextPtr

template <typename T>
Node<T> *Node<T>::getNextPtr() const
{
    return nextPtr;
} // Node<T>::getNextPtr

#endif // NODE_H

