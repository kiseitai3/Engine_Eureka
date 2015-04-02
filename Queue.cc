#include <iostream>
#include <cstdlib>
#include <cassert>

template<typename T>
Queue<T>::Queue(size_t capacity)
{
  //Set the Queue to its initial state
  Size = 0;
  Start = 0;
  End = 0;

  //Create queue array
  Contents = new ItemTy[Capacity];
}

template<typename T>
void Queue<T>::reserve(size_t n)
{
    //Let's see if our array was initialized (which should because of the default constructor)!
    assert(Contents);

    //Let's deallocate it
    delete[] Contents;

    //Let's reallocate it
    Contents = new ItemTy[n];
}

template<typename T>
bool Queue<T>::empty() const
{
  //Returns whether the stack is empty by checking the value of Size.
  return Size == 0;
}

template<typename T>
bool Queue<T>::full() const
{
  //Returns whether the stack is full by checking the value of Size.
  return Size == Capacity;
}

template<typename T>
void Queue<T>::enqueue(const ItemTy& item)
{
  /*This method checks whether the Queue is full and proceeds to add item
    to the intenal array. Since I'm implementing a circular array, this method
    returns to the first position in the array when it has to add an item
    beyond Capacity - 1.
  */
  assert(!full());
  if(End < Capacity)
    //Checks to see if we are still within the array.
    Contents[End] = item;
  else
    {
      //Wrap around
      End = 0;
      Contents[End] = item;
    }
  End++;//move up end
  Size++;//increment size
}

template<typename T>
void Queue<T>::dequeue()
{
  /*This method checks whether the Queue is empty and then removes the first
    item. It doesn't really remove anything, but rather decrease the size
    counter and move the start counter.
  */
  assert(!empty());
  Start++;//move up start
  if(Start == Capacity)
    Start = 0;
  Size--;//decrement size
}

template<typename T>
void Queue<T>::print() const
{
  /*This method prints the contents of the Queue to standard output!*/
  size_t i = Start;//Keeps track of position in the array
  size_t count = 0;//Keeps track of how far in the Queue we have looked
  std::cout << "Contents: ";
  while(count < Size)//Output until the condition is met.
    {
      if(i == Capacity)
	i = 0;
      std::cout << Contents[i] << " ";
      count++;
      i++;
    }
  std::cout << std::endl;//Place an endline character
}
