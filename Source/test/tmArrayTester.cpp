/*******************************************************************************
File:         tmArrayTester.cpp
Project:      TreeMaker 5.x
Purpose:      Test application for the tmArray container classes
Author:       Robert J. Lang
Modified by:  
Created:      2005-09-27
Copyright:    2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

// Standard libraries

#include <iostream>
// My libraries
#include "tmArray.h"          // my general-purposes container class
#include "tmArrayIterator.h"  // my redefinition of PowerPlant tmArrayIterator

// tmArrayIterator test
void test1(tmArray<const char*>& aList);
void test1(tmArray<const char*>& aList)
{
  tmArrayIterator<const char*> i(aList);
  const char* c;
  while (i.Next(&c)) *c; // Keep dereferencing to prevent unused variable warning for c
}



// for loop test
void test2(tmArray<const char*>& aList);
void test2(tmArray<const char*>& aList)
{
  size_t nmax = aList.size();
  for (size_t i = 1; i <= nmax; ++i) *(aList.NthItem(i));
}



// for loop with repeated size()
void test2a(tmArray<const char*>& aList);
void test2a(tmArray<const char*>& aList)
{
  for (size_t i = 1; i <= aList.size(); ++i) *(aList.NthItem(i));
}



// class for test of stored pointers
class Foo {
  public:
    void DoSomething() const {std::cout << "foo!" << std::endl;}
};


// stream output for a list (helps in testing)
template <class T>
std::ostream& operator<<(std::ostream& os, tmArray<T>& aList);
template <class T>
std::ostream& operator<<(std::ostream& os, tmArray<T>& aList)
{
  os << "<";
  for (size_t i = 0; i < aList.size(); ++i) {
    os << aList[i];
    if (i != aList.size() - 1) os << ", ";
  }
  os << ">";
  return os;
}


// Main test program
int main(void)
{
  std::cout << "Hello World.\n";
  
  const char* a = "A";
  const char* b = "B";
  const char* c = "C";
  const char* d = "D";
  const char* e = "E";
  const char* f = "F";
  const char* g = "G";
  const char* h = "H";
  
  tmArray<const char*> alist;
  
  alist.push_back(b);
  alist.push_back(c);
  alist.push_front(a);
  
  std::cout << "alist is " << alist << std::endl;
  std::cout << "size() is " << alist.size() << std::endl;
  std::cout << "front = " << *(alist.front()) << std::endl;
  std::cout << "NthItem(2) = " << *(alist.NthItem(2)) << std::endl;
  std::cout << "back = " << *(alist.back()) << std::endl;
  std::cout << std::endl;
  
  alist.union_with(a);
  alist.union_with(d);
  std::cout << "After union_with(a, d) the list is " << alist << std::endl;
  
  alist.erase_remove(d);
  std::cout << "After erase_remove(d) the list is " << alist << std::endl;
  
  
  alist.erase_remove(b);
  std::cout << "After erase_remove(b) the list is " << alist << std::endl;
  if (alist.size() >= 2) {
    std::cout << "2nd item is now " << *(alist.NthItem(2)) << std::endl;
  }
  std::cout << "size() is now " << alist.size() << std::endl;
  std::cout << std::endl;
  
  std::cout << "list contains a? " << (alist.contains(a) ? 1 : 0) << std::endl;
  std::cout << "list contains b? " << (alist.contains(b) ? 1 : 0) << std::endl;
  std::cout << "list contains c? " << (alist.contains(c) ? 1 : 0) << std::endl;
  std::cout << std::endl;
  
  if (alist.size() > 1) {
    alist.ReplaceItemAt(1, d);
    std::cout << "After ReplaceItemAt(1, d) the list is " << alist << std::endl;
    std::cout << "1st item is now " << *(alist.NthItem(1)) << std::endl;
    std::cout << "Index of 'd' is " << alist.GetIndex(d) << std::endl;
    std::cout << "Offset of 'd' is " << alist.GetOffset(d) << std::endl;
  }
  
  if (!alist.empty()) {
    std::cout << "alist[0] = " << *(alist[0]) << std::endl;
  }
  std::cout << std::endl;
  
  alist.push_back(e);
  std::cout << "After push_back(e) the list is " << alist << std::endl;
  
  alist.replace_with(d, a);
  std::cout << "After replace_with(d, a) the list is " << alist << std::endl;
  
  // tmArrayIterator/tmArrayIterator test
  tmArrayIterator<const char*> i(alist);
  const char* dp;
  std::cout << "Forward iterator test." << std::endl;
  while (i.Next(&dp)) std::cout << "an element is " << dp << std::endl;
  std::cout << "Backward iterator test." << std::endl;
  i.ResetTo(tmArray_END);
  while (i.Previous(&dp)) std::cout << "an element is " << dp << std::endl;
  std::cout << std::endl;
  
  // operator[] returns an lvalue 
  std::cout << std::endl;
  alist[0] = f;
  std::cout << "Set alist[0] = f; alist = " << alist << std::endl;
  std::cout << std::endl;
  
  // combinational routines 
  tmArray<const char*> blist;
  blist.push_back(f);
  blist.push_back(g);
  blist.push_back(h);
  std::cout << "alist = " << alist << std::endl;
  std::cout << "blist = " << blist << std::endl;
  blist.intersect_with(alist);
  std::cout << "blist.intersect_with(alist) = " << blist << std::endl;
  blist.union_with(alist);
  std::cout << "blist.union_with(alist) = " << blist << std::endl;
  
  // intersection routines
  tmArray<int> clist;
  clist.push_back(1);
  clist.push_back(2);
  clist.push_back(3);
  clist.push_back(4);
  tmArray<int> dlist;
  dlist.push_back(5);
  dlist.push_back(4);
  std::cout << "clist = " << clist << std::endl;
  std::cout << "dlist = " << dlist << std::endl;
  std::cout << "clist.intersects(dlist) = " << (clist.intersects(dlist)) << std::endl;
  std::cout << "dlist.intersects(clist) = " << (dlist.intersects(clist)) << std::endl;
}
