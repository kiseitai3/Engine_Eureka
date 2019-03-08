#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstdlib>

template<typename T>
class Queue
{
 public:
  Queue(size_t capacity = 100);//Constructor
  typedef T ItemTy;
  void enqueue(const ItemTy& item);//Adds an item to the Queue
  void dequeue();//Removes the first item from the Queue
  void reserve(size_t n);//Reserve an array of this size!
  ItemTy front() const
  {
     /*Obtains the first item in the Queue, which is located at position Start*/
     assert(!empty());
     return Contents[Start];
  }//Returns the first item in the Queue
  bool empty() const;//Returns whether the Queue is empty
  bool full() const;//Returns whethe the Queue is full
  void print() const;//Prints the contents of the Queue
 private:
  //Instance vaiables
  ItemTy* Contents;//Circular array
  const size_t Capacity = 100;
  size_t Size, Start, End;//Counters
};

#include "Queue.cc"
#endif
