//
// Name : Paul Gritsch
// SSID : 1220449
// A04:  Submission Date: 11/19/23
//
#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <set>


template <class NodeType>
struct Node {
  Node(NodeType item): data(item) {}
  NodeType data ;
  Node<NodeType>* next = nullptr;
  Node<NodeType>* prev = nullptr;
 };

 template <class NodeType>
 class LinkedList{
  public: 					//or using a getter : Node<NodeType>* Head();

    //default constructor
    LinkedList(): head(nullptr), tail(nullptr), n(0) {}
    // copy constructor and assignment
    LinkedList<NodeType>(const LinkedList <NodeType>& that){
      Node<NodeType>* iter = that.head;
      for (int i = 0; i < that.size(); i++){
        this->insert_back(iter->data);
        iter = iter->next;
      }
    }
    LinkedList<NodeType>& operator=(const LinkedList<NodeType>& that){
      clear();
      Node<NodeType>* iter = that.head;
      for (int i = 0; i < that.size(); i++){
        this->insert_back(iter->data);
        iter = iter->next;
      }
      return *this;
    }
    virtual ~LinkedList(){ //destructor deletes all nodes
      Node<NodeType>* temp = nullptr;
      while (head != nullptr){
          temp = head;
          head = head->next;
          delete temp;
          n--;
      }
      head = nullptr;
      tail = nullptr;
    }

    Node<NodeType>* Head(){
      return head;
    }
    Node<NodeType>* Tail(){
      return tail;
    }

    int size(){ // return node count
      return n;
    }
    const int size() const{ // return node count
      return n;
    }
    bool empty(){ // check if empty
      return head == nullptr;
    }
    void insert_front(const NodeType& item){
      n++;
      Node<NodeType>* newNode = new Node<NodeType>(item);
      //if list empty becomes head and tail
      if (empty()){
        head = newNode;
        tail = newNode;
      }
      // set newNode as first node, update next and prev pointers
      else{
        newNode->next = head;
        head = newNode;
        //set 2nd node prev to newNode
        newNode->next->prev = newNode;
      }
    }
    NodeType remove_front(){ // working?
      Node<NodeType>* temp = head;
      NodeType returndata = temp->data;
      if (tail == head){
        // std::cout << "\nremoving last item " << this->head->data << "\n";
        head = nullptr;
        tail = nullptr;
        delete temp;
        n = 0;
        return returndata;
      }
      head = head->next;
      head->prev = nullptr;
      // if (head != tail && head->next != tail){
      // head->next->prev = head;
      // }
      n--;
      delete temp;
      return returndata;
    }
    void insert_back(const NodeType& item){ //done
      //increase node counter
      n++;
      // Create the new Node
      Node<NodeType>* newNode = new Node<NodeType>(item);
      //assign to head and tail if empty list
      if (head == nullptr){
        head = newNode;
        tail = newNode;
        return;
      }
      // set temp to last node
      Node<NodeType>* temp = tail;
      //insert at end
      temp->next = newNode;
      newNode->prev = temp;
      tail = newNode;    
      return;
    }
    NodeType remove_back(){
      Node<NodeType>* temp = tail;
      NodeType returndata = temp->data;
      if (tail == head){
        // std::cout << "\nremoving last item " << this->tail->data << "\n";
        head = nullptr;
        tail = nullptr;
        delete temp;
        n = 0;
        return returndata;
      }      
      tail = tail->prev;
      // if (head != tail && head->next != tail){
      //   tail->prev->next = tail;
      // }
      tail->next = nullptr;
      n--;
      delete temp;
      return returndata;
    }
    void clear(){ // remove all nodes
      Node<NodeType>* temp = nullptr;
      while (head != nullptr){
          temp = head;
          head = head->next;
          delete temp;
          n--;
      }
      head = nullptr;
      tail = nullptr;
    }

    template <class T>
    friend LinkedList<T> list_union(const LinkedList<T>& u, const LinkedList<T>& v);

    template <class T>
    friend LinkedList<T> list_intersection(const LinkedList<T>& u, const LinkedList<T>& v);



    void display(std::ostream& out = std::cout) const{
        Node<NodeType>* node = head;
        while(node != nullptr){
              out << node->data << " ";
              node = node->next;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<NodeType>& dll){
      dll.display(os);
      return os;
    }


   private:
     Node<NodeType>* head = nullptr;
     // optional tail , useful for back operations
     Node<NodeType>* tail = nullptr;
     int n = 0; // node counter
 };

template <class NodeType>
LinkedList<NodeType> list_union(const LinkedList<NodeType>& u, const LinkedList<NodeType>& v){
  std::set<NodeType> st;
  LinkedList<NodeType> out;
  Node<NodeType>* iter = u.head;
  while (iter != nullptr){
    // out.insert_back(iter->data);
    st.insert(iter->data);
    iter = iter->next;
  }
  iter = v.head;
  while (iter != nullptr){
    // out.insert_back(iter->data);
    st.insert(iter->data);
    iter = iter->next;
  }
  for (auto item: st){
    out.insert_front(item);
  }
  return out;
}

template <class NodeType>
LinkedList<NodeType> list_intersection(const LinkedList<NodeType>& u, const LinkedList<NodeType>& v){
  LinkedList<NodeType> out;
  Node<NodeType>* iteru = u.head;
  Node<NodeType>* iterv;
  while (iteru != nullptr){
    iterv = v.head;
    while (iterv != nullptr){
      if (iteru->data == iterv->data){
        out.insert_back(iteru->data);
      }
      iterv = iterv->next;
    }
    iteru = iteru->next;
  }

  return out;      
}



#endif