//##################################################
// File: Queue.h
// Description: A Queue class implemented using a doubly linked list.
// Date: Nov,10 2024
//##################################################



#ifndef QUEUE_H
#define QUEUE_H

#include "DoublyLinkedList.h"

template <typename T>
class Queue {
public:
    Queue();                     ///< Constructor initializes an empty queue.
    ~Queue();                    ///< Destructor to clean up queue.

    void enqueue(const T& data); ///< Adds an element to the end of the queue.
    bool dequeue();              ///< Removes the front element from the queue.
    T peek() const;              ///< Returns the front element without removing it.

    bool isEmpty() const;        ///< Checks if the queue is empty.

private:
    DoublyLinkedList<T> list;    ///< The underlying doubly linked list for queue storage.
};

/**
 * @brief Initializes an empty queue.
 * @note Constructor follows unit 11 with no modifications.
 */
template <typename T>
Queue<T>::Queue() {}

/**
 * @brief Destructor automatically cleans up the linked list.
 * @note follows lecture material.
 */
template <typename T>
Queue<T>::~Queue() {}

/**
 * @brief Adds an element to the end of the queue.
 * @param data The data to be added to the queue.
 * @note Uses addToEnd function from `DoublyLinkedList` to maintain queue order.
 */
template <typename T>
void Queue<T>::enqueue(const T& data) {
    list.addToEnd(data); // Adds to the end to represent the rear of the queue.
}

/**
 * @brief Removes the front element from the queue.
 * @return True if the dequeue was successful, false if queue was empty.
 * @note Uses deleteNode to remove the head element, simulating queue dequeue.
 */
template <typename T>
bool Queue<T>::dequeue() {
    if (!isEmpty()) {
        T frontData = list.head->data; // Get data at the front of the queue
        list.deleteNode(frontData);     // Delete the first node
        return true;
    }
    return false; // Queue was empty
}

/**
 * @brief Returns the front element without removing it.
 * @return The front element of the queue.
 * @note Accesses the first element in the list to simulate queue peek.
 */
template <typename T>
T Queue<T>::peek() const {
    if (!isEmpty()) {
        return list.head->data; // Access the first element as the front
    }
    return T(); // Return default value if queue is empty
}

/**
 * @brief Checks if the queue is empty.
 * @return True if empty, false otherwise.
 * @note Uses head pointer to determine if the list is empty.
 */
template <typename T>
bool Queue<T>::isEmpty() const {
    return list.head == nullptr;
}

#endif // QUEUE_H
