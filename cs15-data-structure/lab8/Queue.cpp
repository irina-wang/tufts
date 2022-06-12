/*
 * Filename: Queue.cpp
 * Author: Hayden Wolff
 * Contains: Queue as Template class implementation
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include <iostream>
#include "Queue.h"
#include "Patient.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor, sets front and rear to NULL
template<class E>
Queue<E>::Queue()
{
    front = NULL;
    rear = NULL;
}

// Function: destructor
// Parameters: none
// Returns: nothing
// Does: Frees memory
template<class E>
Queue<E>::~Queue()
{
    NodeType<E> *temp;

    while (front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
    rear = NULL;
}

// Function: Copy constructor
// Parameters: Queue
// Returns: nothing
// Does: Standard copy constructor
template<class E>
Queue<E>::Queue(const Queue<E> &q)
{
    if (q.front == NULL)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        try
        {
            front = new NodeType<E>;
        }
        catch (bad_alloc exception)
        {
            cerr << "Could not copy queue\n";
            return;
        }
        front->value = q.front->value;
        NodeType<E> *curr = front;
        NodeType<E> *orig = q.front;
        while (orig->next != NULL)
        {
            try
            {
                curr->next = new NodeType<E>;
                curr->next->value = orig->next->value;
                orig = orig->next;
                curr = curr->next;
                rear = curr;
            }
            catch (bad_alloc exception)
            {
                cerr << "Could not copy queue\n";
                return;
            }
        }
    }
}

// Function: Assignment operator
// Parameters: Queue
// Returns: nothing
// Does: makes a copy of the given queue into this;
//       returns a reference to itself
template<class E>
Queue<E> & Queue<E>::operator = (const Queue<E> &q)
{
    while (front != NULL)
    {
        NodeType<E> *temp = front;
        front = front->next;
        delete temp;
    }
    rear = NULL;
    if (q.front == NULL)
    {
        front = NULL;
    }
    else
    {
        try
        {
            front = new NodeType<E>;
            front->value = q.front->value;
            NodeType<E> *curr = front;
            NodeType<E> *orig = q.front;
            while (orig->next != NULL)
            {
                curr->next = new NodeType<E>;
                curr->next->value = orig->next->value;
                orig = orig->next;
                curr = curr->next;
                rear = curr;
            }
        }
        catch (bad_alloc exception)
        {
            cerr << "Could not copy queue\n";
        }
    }
    return *this;
}

// Function: make_empty
// Parameters: none
// Returns: nothing
// Does: empties out the queue and deallocates memory 
template<class E>
void Queue<E>::make_empty()
{
    NodeType<E> *temp;
    while (front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
    rear = NULL;
}

// Function: is_full
// Parameters: none
// Returns: bool, true if full
// Does: attempt to allocate space, return false 
//       if we could (queue not full), true otherwise
template<class E>
bool Queue<E>::is_full() const
{
    NodeType<E> *location;
    try 
    {
        location = new NodeType<E>;
        delete location;
        return false;
    }
    catch(std::bad_alloc exception)
    {
        return true;
    }
}

// Function: is_empty
// Parameters: none
// Returns: bool, true if empty
// Does: queue is empty if front pointer is NULL
template<class E>
bool Queue<E>::is_empty() const
{
    return (front == NULL);
}

// Function: enqueue
// Parameters: template item
// Returns: void
// Does: enqueue a new item onto the back of the queue
template<class E>
void Queue<E>::enqueue(E new_item)
{
    if (is_full())
        throw FullQueue();
    else
    {
        NodeType<E> *new_node;
        new_node = new NodeType<E>;
        new_node->value = new_item;
        new_node->next = NULL;
        if (rear == NULL)
            front = new_node;
        else
            rear->next = new_node;
        rear = new_node;
    }
}

// Function: get_length
// Parameters: none
// Returns: int length
// Does: count the number of nodes in the queue
template<class E>
int Queue<E>::get_length() const
{
    int count = 0;
    NodeType<E> *temp = front;
    while (temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

// Function: dequeue
// Parameters: none
// Returns: template item
// Does: dequeue one item from the front of the queue
template<class E>
E Queue<E>::dequeue()
{
    if (is_empty())
        throw EmptyQueue();
    else
    {
        E item;
        NodeType<E> *temp;
        temp = front;
        item = front->value;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        delete temp;
        return item;
    }
}

// Template class specifications
template class Queue<Patient>;
template class Queue<int>;
template class Queue<double>;
