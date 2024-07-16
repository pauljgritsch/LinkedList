//
// Name : Paul Gritsch
// SSID : 1220449
// A04:  Submission Date: 11/19/23
//
#pragma once
#ifndef STACKLIST_H
#define STACKLIST_H
#include "LinkedList.hpp"
#include <iostream>
#include <string>

// add as a friend to LinkedList or add Node<NodeType>* Head() to LinkedList
template <class NodeType>
class StackList{
  public:
    StackList(): n(0) {}
    void push(NodeType data){
      list.insert_back(data);
      n++;
    }
    void pop(){
      list.remove_back();
      n--;
    }
    NodeType top(){
      return list.Tail()->data;
      // return list.tail->data;
    }
    bool empty(){
      return !n;
    }
    int size(){
      return n;
    }

    friend std::ostream& operator<<(std::ostream& os, const StackList<NodeType>& dll){
      dll.list.display(os);
      return os;
    }

    friend void post_fix_calculator();
  private:
    LinkedList<NodeType> list; 
    int n = 0; // stack counter
};

//helper function for post_fix_calculator
float operate(char op, float num1, float num2){
  if (op == '+'){
    return num1 + num2;
  }
  if (op == '-'){
    return num1 - num2;
  }
  if (op == '/'){
    return num1 / num2;
  }
  if (op == '*'){
    return num1 * num2;
  }
  return 0;
}

void post_fix_calculator(){
  float num2, num1;
  std::string input;
  StackList<float> stack;
  std::string current = "";
  // std::cout << "Please input an expression in postfix notation.\n";
  std::getline(std::cin, input);
  
  for (int i = 0; i < input.length(); i++){
    if (isdigit(input.at(i)) || input[i] == '.'){
      current.push_back(input[i]);
    }
    else if (input[i] == ' ' && current != ""){
      // std::cout << "\n"<< current << "pushed\n";
      stack.push(std::stof(current)); 
      // std::cout << "top is " << stack.top();
      // std::cout << "\ncurrent stack: "<< stack << "\n";
      current = "";
    }
    else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'){
      num2 = stack.top();
      stack.pop();
      num1 = stack.top();
      stack.pop();
      num1 = operate(input[i], num1, num2);
      stack.push(num1);
      // std::cout << "\ncurrent stack op: "<< stack << "\n";
    }
    else if (input[i] == '='){
      // std::cout << "Result of postfix = " << stack.top() << std::endl;
      std::cout << stack.top();
    }
  }
}


#endif