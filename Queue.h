#ifndef UNTITLED23_QUEUE_H
#define UNTITLED23_QUEUE_H

#include <new>
#include "Node.h"
#include <iostream>
using namespace std;

// class queue,Iterator,constIterator implementation //

/**
 * class queue
 */
template<class T>
class Queue {
public:

    class Iterator;
    class ConstIterator;
    Queue()=default;
    ~Queue();
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    void pushBack(T value);
    T& front() const;
    void popFront();
    int size() const;
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
    bool operator()(T& value) const;
    class EmptyQueue {};


private:
   //the queue's size
    int m_size = 0;
   //pointer to the head of the queue
    Node<T>* m_head = nullptr;
    //pointer to the end of the queue
    Node<T>* m_tail = nullptr;

};

template<class T>
Queue<T>::Queue(const Queue<T>& queue)
{
    if (!queue.m_head)
        throw Queue<T>::EmptyQueue();

    Node<T>* node = queue.m_head;
    try {
        for (int i = 0; i < queue.m_size; i++)
        {

            this->pushBack(node->getValue());

            node = node->getNext();
        }
    }
    catch (Queue<T>::EmptyQueue& e) {
        throw e;
    }

}

template <class T>
Queue<T>::~Queue()
{
    Node<T>* node = this->m_head;
    for (int i = 0; i < this->m_size; i++)
    {
        if(node== nullptr)
            break;
         delete node;
        this->m_head = this->m_head->getNext();
        node = this->m_head;
    }
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue1)
{
    if (this == &queue1)
        return *this;
    Node<T>* node = queue1.m_head;
    Queue<T> queue2;

    if (this->m_head!= nullptr) {
        for (int i = 0; i < this->m_size; i++) {
            this->popFront();
        }
    }

    for (int i = 0; i < queue1.m_size; i++)
    {
        queue2.pushBack(node->getValue());
        node = node->getNext();
    }

    try {
        for (int i = 0; i < queue1.m_size; i++)
        {
            this->pushBack(queue2.m_head->getValue());
            queue2.popFront();
        }
    }
    catch (const Queue<T>::EmptyQueue& e) {
        throw e;
    }
    return *this;
}

template<class T>
void Queue<T>::pushBack(T value)
{
    this->m_size += 1;

    if (this->m_tail)
    {
        this->m_tail=this->m_tail->insert(value);

    }
    else {
        Node<T>* node = new Node<T>(value);
        this->m_head = node;
        this->m_tail=node;
    }
}

template<class T>
T& Queue<T>::front() const
{
    if (!this->m_head || this->m_size==0)
        throw Queue<T>::EmptyQueue();
    return this->m_head->getValue();
}

template<class T>
void Queue<T>::popFront()
{
    if (!this->m_head)
        throw Queue<T>::EmptyQueue();
    this->m_size -= 1;
    Node<T>* temp = this->m_head;
    this->m_head = this->m_head->getNext();
    delete(temp);
}

template<class T>
int Queue<T>::size() const
{
    return m_size;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this->m_head);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(nullptr);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this->m_head);
}
template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(nullptr);
}


template<class T>
bool Queue<T>::operator()(T& value) const
{
    return Condition(value);
}


/**
 * class Iterator implementation
 */


template<class T>
class Queue<T>::Iterator
{
private:
    Node<T>* m_currentNode;

    friend class Queue<T>;
public:
    Iterator()=default;
    Iterator(Node<T>* node);
    Iterator(const Queue<T>::Iterator& iterator) = default;
    Iterator& operator=(const Queue<T>::Iterator& iterator) = default;
    ~Iterator() = default;
    T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Queue<T>::Iterator& it) const;
    bool operator==(const Queue<T>::Iterator& it) const;

    class InvalidOperation {};
};

template<class T>
Queue<T>::Iterator::Iterator(Node<T>* node) : m_currentNode(node)
{}

template<class T>
T& Queue<T>::Iterator::operator*() const
{
    if (m_currentNode != nullptr)
    {
        return this->m_currentNode->getValue();
    }
    else
    {
        throw InvalidOperation();
    }
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (this->m_currentNode != nullptr)
        this->m_currentNode = this->m_currentNode->getNext();
    else { throw Queue<T>::Iterator::InvalidOperation(); }
    return *this;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const
{
    return !(m_currentNode == it.m_currentNode);
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& it) const
{
    return m_currentNode == it.m_currentNode;
}

/**
 * class ConstIterator implementation
 */

template<class T>
class Queue<T>::ConstIterator
{
    Node<T>* m_currentNode;
    ConstIterator(Node<T>* node);
    friend class Queue;
public:
    ConstIterator()=default;
    ConstIterator(const Queue<T>::ConstIterator& constIterator) = default;
    ConstIterator& operator=(const Queue<T>::ConstIterator& constIterator) = default;
    ~ConstIterator() = default;
    T operator*() const;
    ConstIterator& operator++();
    bool operator!=(const Queue<T>::ConstIterator& it) const;
    bool operator==(const Queue<T>::ConstIterator& it) const;
    class InvalidOperation {};
};

template<class T>
Queue<T>::ConstIterator::ConstIterator(Node<T>* node) : m_currentNode(node)
{}

template<class T>
T Queue<T>::ConstIterator::operator*() const
{
    if (m_currentNode != nullptr)
    {
        return this->m_currentNode->getValue();
    }
    else
    {
        throw InvalidOperation();
    }
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (this->m_currentNode != nullptr)
        this->m_currentNode = this->m_currentNode->getNext();
    else { throw Queue<T>::ConstIterator::InvalidOperation(); }
    return *this;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const
{
    return !(m_currentNode == it.m_currentNode);
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& it) const
{
    return m_currentNode == it.m_currentNode;
}

template<class T,class Condition>
Queue<T> filter(Queue<T> queue, Condition c)
{

    Queue<T> result;
    typename Queue<T>::Iterator it;

    for( it=queue.begin();it!= queue.end();++it)
    {
        if(c(*it))
        {
            result.pushBack(*it);
        }
    }
    return result;
}

template<class T,class Effect>
void transform(Queue<T>& queue, Effect c)
{
    typename Queue<T>::Iterator it;

    for( it=queue.begin();it!= queue.end();++it)
    {
        c(*it);

    }
}

#endif //UNTITLED23_QUEUE_H
