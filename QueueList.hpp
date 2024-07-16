//
// Name : Paul Gritsch
// SSID : 1220449
// A04:  Submission Date: 11/19/23
//
#pragma once
#ifndef QUEUELIST_H
#define QUEUELIST_H
#include "LinkedList.hpp"
#include <iostream>
#include <string>

template <class NodeType>
class QueueList {
  public:
    QueueList(): n(0) {}
    void enqueue(NodeType data){
      list.insert_back(data);
      n++;
    }
    void dequeue(){
      list.remove_front();
      n--;
    }
    NodeType front(){
      return list.Head()->data;
    }
    bool empty(){
      return !n;
    }

    friend std::ostream& operator<<(std::ostream& os, const QueueList<NodeType>& dll){
      dll.list.display(os);
      return os;
    }

  private:
    LinkedList<NodeType> list ;
    int n ; // element counter
};

bool palindrome_checker(std::string input){ //why use queue for this? stack seems better
  QueueList<char> queue;
  char current;
  // put input into queuelist backwards since first in is first out
  for (int i = input.length() - 1; i >= 0; i--){
    queue.enqueue(input[i]);
  }

  //test each letter of queue against letter of input
  int index = 0;
  while (!queue.empty()){
    current = queue.front();
    // std::cout << "\ncurrent = " << current << " input[index] = " << input[index];
    if (current != input[index]){
      return false;
    }
    queue.dequeue();
    index++;
  }
  return true;
}



#endif