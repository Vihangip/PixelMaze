/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T const& newItem)
{

    inStack.push(newItem);
//    if(!inStack.isEmpty()) {
//        while(!inStack.isEmpty()){
//            T elem = inStack.pop();
//            outStack.push(elem);
//        }
//    }
//
//
//    inStack.push(newItem);
//
//    while(!outStack.isEmpty()){
//        T elem = outStack.pop();
//        inStack.push(elem);
//    }
}

/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue()
{
    if(outStack.isEmpty()){
        while(!inStack.isEmpty()){
            outStack.push(inStack.pop());
        }

        return outStack.pop();
    } else {
        return outStack.pop();
    }

//    if(outStack.isEmpty()){
//        while(!inStack.isEmpty()) {
//            T elem = inStack.pop();
//            outStack.push(elem);
//        }
//    }
//
//    T temp = NULL;
//    if(!outStack.isEmpty()){
//        temp = outStack.pop();
//    }
//
//    return temp;
   // return inStack.pop();

}

/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add(const T& theItem)
{
    enqueue(theItem);

}

/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove()
{
    return dequeue();
}

/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template <class T>
T Queue<T>::peek()
{
    return outStack.peek();
}

/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template <class T>
bool Queue<T>::isEmpty() const
{
    return inStack.isEmpty() && outStack.isEmpty();

}
