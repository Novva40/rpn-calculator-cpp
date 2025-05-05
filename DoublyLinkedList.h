//##################################################
// File: DoublyLinkedList.h
// Description: Implements a generic doubly linked list with basic functionalities: adding to front, adding to end, inserting after a node, deleting a node,and traversing forwards and backwards.
// Date: Nov,10 2024
//##################################################



#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    /**
     * @brief Initializes a node with given data.
     * @param data The data to store in the node.
     * @note No modifications were made for this structure.
     */
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();    ///< Constructor initializes an empty list.
    ~DoublyLinkedList();   ///< Destructor clears all nodes from the list.

    void addToFront(const T& data);   ///< Adds a node with data to the front.
    void addToEnd(const T& data);     ///< Adds a node with data to the end.
    void insert(const T& search, const T& data); ///< Inserts a node after the specified value.
    void deleteNode(const T& search); ///< Deletes a node with the specified value.
    bool find(const T& search) const; ///< Checks if a node with the specified value exists.

    void traverseForward() const; ///< Traverses and prints the list from head to tail.
    void traverseBackward() const; ///< Traverses and prints the list from tail to head.

    Node<T>* getHead() const { return head; }  ///< Returns the head node.
    Node<T>* getTail() const { return tail; }  ///< Returns the tail node.

private:
    Node<T>* head;
    Node<T>* tail;
};

// Function definitions follow the lecture unit 11, with modifications noted where applicable.

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

/**
 * @brief Adds a node to the front of the list.
 * @param data The data to add to the front.
 * @note This function follows the lecture material, adding a node to the front of the list without modifications.
 */
template <typename T>
void DoublyLinkedList<T>::addToFront(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = head;
    if (head) head->prev = newNode;
    else tail = newNode;
    head = newNode;
}

/**
 * @brief Adds a node to the end of the list.
 * @param data The data to add to the end.
 * @note Follows the lecture material with a slight modification to update the tail pointer.
 */
template <typename T>
void DoublyLinkedList<T>::addToEnd(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

/**
 * @brief Inserts a node with specified data after the node containing `search`.
 * @param search The value after which to insert.
 * @param data The data to insert.
 * @note Based on lecture material; modified to work with generic types.
 */
template <typename T>
void DoublyLinkedList<T>::insert(const T& search, const T& data) {
    Node<T>* current = head;
    while (current && current->data != search) {
        current = current->next;
    }
    if (current) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
        if (current == tail) tail = newNode;
    }
}

/**
 * @brief Deletes a node with the specified value.
 * @param search The value to delete.
 * @note This function is based on the lecture material and includes logic to handle head and tail adjustments.
 */
template <typename T>
void DoublyLinkedList<T>::deleteNode(const T& search) {
    Node<T>* current = head;
    while (current && current->data != search) {
        current = current->next;
    }
    if (!current) return;

    if (current->prev) current->prev->next = current->next;
    else head = current->next;

    if (current->next) current->next->prev = current->prev;
    else tail = current->prev;

    delete current;
}

/**
 * @brief Checks if a node with the specified value exists.
 * @param search The value to search for.
 * @return True if the value is found, false otherwise.
 * @note This function follows the lecture material directly.
 */
template <typename T>
bool DoublyLinkedList<T>::find(const T& search) const {
    Node<T>* current = head;
    while (current) {
        if (current->data == search) return true;
        current = current->next;
    }
    return false;
}

/**
 * @brief Traverses and prints the list from head to tail.
 * @note Follows lecture material for traversal.
 */
template <typename T>
void DoublyLinkedList<T>::traverseForward() const {
    Node<T>* current = head;
    while (current) {
        // Replace with a custom print function
        current = current->next;
    }
}

/**
 * @brief Traverses and prints the list from tail to head.
 * @note Follows lecture material for reverse traversal.
 */
template <typename T>
void DoublyLinkedList<T>::traverseBackward() const {
    Node<T>* current = tail;
    while (current) {
        // Replace with a custom print function
        current = current->prev;
    }
}

#endif // DOUBLYLINKEDLIST_H
