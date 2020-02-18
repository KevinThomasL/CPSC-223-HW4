//----------------------------------------------------------------------
// Author: Kevin Lunden
// Course: CPSC 223, Spring 2020
// Assign: 4
// File:   linked_list_collection.h
//
// TODO: implements key-value pairs using a linked list
//----------------------------------------------------------------------

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>            
#include "collection.h"

using namespace std;

template<typename K, typename V>
class LinkedListCollection : public Collection<K,V>
{
public:

  // constructor to initialize empty linked list
  LinkedListCollection();

  // copy constructor
  LinkedListCollection(const LinkedListCollection<K,V>& rhs);

  // assignment operator
  LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);
  
  // destructor to delete a linked list
  ~LinkedListCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

private:
  struct Node {
    K key;
    V value;
    Node* next;
  };
  Node* head;
  Node* tail;
  int length;

  // Optional: declare a void make_empty() helper function
  
  void make_empty()
  {
   while (head != nullptr)
   {	   
    Node* tmp = head;
    head = head->next;
    delete tmp;
    tmp = nullptr;
   }
  }

};


// TODO: Implement member functions here
// 
// NOTE: Within the sort function, you can use the keys() function to
//       build up the all_keys_sorted vector, then call std::sort over
//       the all_keys_sorted list as in HW3


// constructor to initialize empty linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
{
 head = nullptr;
 tail = nullptr;
 length = 0;
}

// copy constructor
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
{
 *this = rhs;
}

// assignment operator
template <typename K, typename V>
LinkedListCollection<K,V>&LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
 if (head == rhs.head)
  return *this;
 else
 {
  make_empty();
  Node* tmp = rhs.head;
  head = nullptr;
  tail = nullptr;
  length = 0;
  while (tmp != nullptr)
  {
   add(tmp->key, tmp->value);
   tmp = tmp->next;
  }
  return *this;
 } 
}

// destructor to delete a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
 make_empty();
}

template <typename K, typename V>
// add a new key-value pair into the collection 
void LinkedListCollection<K,V>::add(const K& a_key, const V& a_val)
{
 Node* tmp = new Node;
 tmp->key = a_key;
 tmp->value = a_val;
 tmp->next = nullptr;

 if (head == nullptr)
 {
  head = tmp;
  tail = tmp;
 }
 else
 {
  tail->next = tmp;
  tail = tmp;
 }

 length++;
}

template <typename K, typename V>
// remove a key-value pair from the collectiona
void LinkedListCollection<K,V>::remove(const K& a_key)
{
 //if no nodes
 if (length == 0)
  return;

 Node* tmp = head;

 //if only one node
 if (length == 1)
 {
  if (tmp->key == a_key)
  {
   delete tmp;
   tmp = nullptr;
   head = nullptr;
   tail = nullptr;
   length--;
   return;
  }
  return;
 }

 //if removing first node
 if (tmp->key == a_key)
 {
  head = tmp->next;
  delete tmp;
  tmp = nullptr;
  length--;
  return;
 }
 
 //if removing between first and last
 while (tmp->next->key != a_key)
 {
  if (tmp->next->next == nullptr)
   return;
  tmp = tmp->next;
 }
 Node* tmp2 = tmp->next;
 if (tmp2->next != nullptr)
  tmp->next = tmp2->next;

 //if removing last
 if (tmp2->next == nullptr)
 {
  tail = tmp;
  tmp->next = nullptr;
 }

 delete tmp2;
 length--;
 tmp2 = nullptr;
}

template <typename K, typename V>
// find and return the value associated with the key
bool LinkedListCollection<K,V>::find(const K& search_key, V& the_val) const
{
 if (length == 0)
  return false;
 Node* tmp = head;
 while (tmp->key != search_key)
 {
  if (tmp->next == nullptr)
   return false;
  tmp = tmp->next;
 }
 the_val = tmp->value;
 return true;
}

template <typename K, typename V>
// find and return the values with keys >= to k1 and <= to k2 
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
 Node* tmp = head;
 while (tmp != nullptr)
 {
  if (tmp->key >= k1 && tmp->key <= k2) 
   vals.push_back(tmp->value);
  tmp = tmp->next;
 }
}

template <typename K, typename V>
// return all of the keys in the collection 
void LinkedListCollection<K,V>::keys(std::vector<K>& all_keys) const
{
 Node* tmp = head;
 while (tmp != nullptr)
 {
  all_keys.push_back(tmp->key);
  tmp = tmp->next;
 }
}

template <typename K, typename V>
// return all of the keys in ascending (sorted) order
void LinkedListCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
 keys(all_keys_sorted);
 std::sort(all_keys_sorted.begin(), all_keys_sorted.end());
}

template <typename K, typename V>
// return the number of key-value pairs in the collection
int LinkedListCollection<K,V>::size() const
{
 return length;
}


#endif
