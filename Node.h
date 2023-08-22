#ifndef UNTITLED23_NODE_H
#define UNTITLED23_NODE_H

//class node implementation
template<class T>
class Node
{
private:
    T m_value;
    Node *m_next;

public:
    Node()=default;
    Node(const T &item);
    ~Node()=default;
    /**
     * insert a new node at the end of the linked list
     * @param value the new node value
     * @return the new node
     */
    Node* insert(T &value);
    /// \return a pointer to the next node
    Node* getNext()const;
    /// \return reference to the current node value
    T& getValue();

};
template<class T>
Node<T> :: Node(const T &item): m_value(item)
{
    this->m_next= nullptr;
}

template<class T>
Node<T>* Node<T>::insert(T &value)
{
    Node<T>* node= new Node<T>();
    node->m_value=value;
    node->m_next= nullptr;
    this->m_next=node;
    return node;
}

template<class T>
Node<T>* Node<T>::getNext()const
{
    return m_next;
}

template<class T>
T& Node<T>::getValue()
{
    return m_value;
}



#endif //UNTITLED23_NODE_H
