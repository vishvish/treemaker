/*******************************************************************************
File:         tmDpptrTester.cpp
Project:      TreeMaker 5.x
Purpose:      Test application for the tmDpptr and tmDpptrArray container classes
Author:       Robert J. Lang
Modified by:  
Created:      2005-09-27
Copyright:    2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

#include <iostream>
#include <format>

#include "tmDpptr.h"
#include "tmDpptrArray.h"

using namespace std;

/*
This program illustrates usage of the two reference classes tmDpptr<T> and
tmDpptrArray<T>.

A tmDpptr<T> is essentially a dangle-proof pointer-to-T; it behaves like a T*
and can be used anywhere you would normally use a T*, with one enhancement;
when the object of a tmDpptr<T> is deleted, the tmDpptr<T> sets itself to NULL.
Any subsequent attempt to dereference the pointer generates an exception.

A tmDpptrArray<T> acts like a tmArray<T*> (which is basically a vector<T*>),
but when any of the pointed-to objects are deleted, the pointer is completely
removed from the list.

You can give your own container classes the capability to interact with RefObjs
by descending them from the tmDpptrSrc class and overriding the appropriate
access member functions. See the implementation of tmDpptr and tmDpptrArray for
examples of how to do this.
*/

/* Main program */

class A;
class B;

// Classes A and B hold references to each other.

class A : public tmDpptrTarget {  // Remove virtual
public:
    A() { cout << "member of class A created" << endl; }
    ~A() override { cout << "member of class A deleted" << endl; }
    tmDpptr<B> ab;
};


class B : public tmDpptrTarget {  // Remove virtual
public:
    B() { cout << "member of class B created" << endl; }
    ~B() override { cout << "member of class B deleted" << endl; }
    tmDpptr<A> ba;
    
    void Test() { cout << "test B!" << endl; }
};


class D : public tmDpptrTarget {
public:
    D(char* aName) : tmDpptrTarget() {
        std::format_to_n(mName, 20, "{}", aName);
        cout << mName << " created" << endl;
    }
    ~D() override {
        cout << mName << " deleted" << endl;
    }
private:
    char mName[20];
};


int main(void)
{
  cout << "Hello World\n";
  
  // Create two objects and assign their references to each other.

  A* a = new A();   // a->ab is initialized to NULL.
  B* b = new B();   // b->ba is initialized to NULL.
  
  b->ba = a;
  a->ab = b;
  
  tmDpptr<B> c = b; // create another reference to b
  
  cout << "a has " << a->GetNumSrcs() << " references to it" << endl;
  cout << "b has " << b->GetNumSrcs() << " references to it" << endl;
  
  delete a; // Lots of stuff happens right here:
    // If ab and ba had been ordinary pointers, b->ba would dangle. But since
    // we're using references, b->ba has been automatically set to null. Also,
    // the number of references to b has been decreased (since a->ab no longer
    // exists).
        
  cout << "a is deleted; now b has " << b->GetNumSrcs() << 
    " references to it" << endl;
  
  // Test out the various ways of using a reference like a pointer.
  
  cout << "Test of pointer usage:" << endl;
  
  ((B*) c)->Test(); // cast to a pointer
  (*c).Test();      // dereference
  c->Test();        // arrow operator
  
  // Remove unused variable rd1 declaration
  // Create test objects and use them
  D* d1 = new D(const_cast<char*>("d1"));
  tmDpptr<D> rd2(new D(const_cast<char*>("d2")));
  
  delete d1;
  
  // Now try out a tmDpptrArray that automatically removes objects as they are
  // are deleted.
  
  // Create test objects and populate array
  tmDpptrArray<D> rld;    // create a list of references

  // Create objects with clear ownership
  std::unique_ptr<D> d1(new D(const_cast<char*>("d1")));
  std::unique_ptr<D> d2(new D(const_cast<char*>("d2")));
  std::unique_ptr<D> d3(new D(const_cast<char*>("d3")));

  // Add to array without transferring ownership
  rld.push_back(d1.get());
  rld.push_back(d2.get());
  rld.push_back(d3.get());
  rld.push_back(d1.get());    // test multiple references

  cout << "Initially rld has " << rld.size() << " elements." << endl;

  // Let smart pointers handle cleanup
  d1.reset();
  d2.reset();
  d3.reset();
  
  // Try it again but this time test the clear() command
  
  D* d4 = new D(const_cast<char*>("d4"));  // create a bunch of objects to put into the list
  D* d5 = new D(const_cast<char*>("d5"));
  D* d6 = new D(const_cast<char*>("d6"));
  
  rld.push_back(d4);    // put them into the list.
  rld.push_back(d5);
  rld.push_back(d6);
  rld.push_back(d4);    // also check out effect of multiple references.
  cout << "Initially rld has " << rld.size() << " elements." << endl;
  
  rld.clear();
  cout << "After clear() rld has " << rld.size() << " elements." << endl;

  // done

  cout << "Bye...\n";
}
