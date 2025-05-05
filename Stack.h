//##################################################
// File: Stack.h
// Description: A Stack class implemented using a doubly linked list.
// Date: Nov,10 2024
//##################################################



#ifndef STACK_H
#define STACK_H

#include "DoublyLinkedList.h"

template <typename T>
class Stack {
public:
    Stack();                    ///< Constructor initializes an empty stack.
    ~Stack();                   ///< Destructor cleans up stack.

    void push(const T& data);   ///< Pushes an element onto the stack.
    bool pop();                 ///< Removes the top element from the stack.
    T peek() const;             ///< Returns the top element without removing it.

    bool isEmpty() const;       ///< Checks if the stack is empty.

private:
    DoublyLinkedList<T> list;   ///< The underlying doubly linked list for stack storage.
};

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::~Stack() {}

/**
 * @brief Pushes an element onto the stack.
 * @param data The data to push.
 * @note Uses `addToEnd` function from `DoublyLinkedList` as per lecture material.
 */
template <typename T>
void Stack<T>::push(const T& data) {
    list.addToEnd(data);
}

/**
 * @brief Removes the top element from the stack.
 * @return True if the pop was successful, false if stack was empty.
 * @note Uses `deleteNode` to remove the last element, as outlined in lecture material.
 */
template <typename T>
bool Stack<T>::pop() {
    if (!isEmpty()) {
        T topData = list.getTail()->data;
        list.deleteNode(topData);
        return true;
    }
    return false;
}

/**
 * @brief Returns the top element without removing it.
 * @return The top element of the stack.
 * @note Uses `getTail` to access the top element, adhering to lecture material.
 */
template <typename T>
T Stack<T>::peek() const {
    if (!isEmpty()) {
        return list.getTail()->data;
    }
    return T(); // Default return if stack is empty
}

/**
 * @brief Checks if the stack is empty.
 * @return True if empty, false otherwise.
 * @note Determines if stack is empty by checking if `getHead()` is nullptr, following lecture material.
 */
template <typename T>
bool Stack<T>::isEmpty() const {
    return list.getHead() == nullptr;
}

#endif // STACK_H
