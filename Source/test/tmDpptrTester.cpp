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
    // Default constructor
    A() { cout << "member of class A created" << endl; }
    
    // Copy constructor - deep copy the tmDpptr
    A(const A& other) : tmDpptrTarget(other) {
        ab = other.ab;  // tmDpptr has its own copy semantics
        cout << "member of class A copied" << endl;
    }
    
    // Copy assignment - deep copy the tmDpptr
    A& operator=(const A& other) {
        if (this != &other) {
            tmDpptrTarget::operator=(other);
            ab = other.ab;  // tmDpptr has its own copy semantics
            cout << "member of class A copy assigned" << endl;
        }
        return *this;
    }
    
    // Move constructor - transfer ownership
    A(A&& other) noexcept : tmDpptrTarget(std::move(other)), ab(std::move(other.ab)) {
        cout << "member of class A moved" << endl;
    }
    
    // Move assignment - transfer ownership
    A& operator=(A&& other) noexcept {
        if (this != &other) {
            tmDpptrTarget::operator=(std::move(other));
            ab = std::move(other.ab);
            cout << "member of class A move assigned" << endl;
        }
        return *this;
    }
    
    ~A() override { cout << "member of class A deleted" << endl; }
    tmDpptr<B> ab;
};


class B : public tmDpptrTarget {  // Remove virtual
public:
    // Default constructor
    B() { cout << "member of class B created" << endl; }
    
    // Copy constructor - deep copy the tmDpptr
    B(const B& other) : tmDpptrTarget(other) {
        ba = other.ba;  // tmDpptr has its own copy semantics
        cout << "member of class B copied" << endl;
    }
    
    // Copy assignment - deep copy the tmDpptr
    B& operator=(const B& other) {
        if (this != &other) {
            tmDpptrTarget::operator=(other);
            ba = other.ba;  // tmDpptr has its own copy semantics
            cout << "member of class B copy assigned" << endl;
        }
        return *this;
    }
    
    // Move constructor - transfer ownership
    B(B&& other) noexcept : tmDpptrTarget(std::move(other)), ba(std::move(other.ba)) {
        cout << "member of class B moved" << endl;
    }
    
    // Move assignment - transfer ownership
    B& operator=(B&& other) noexcept {
        if (this != &other) {
            tmDpptrTarget::operator=(std::move(other));
            ba = std::move(other.ba);
            cout << "member of class B move assigned" << endl;
        }
        return *this;
    }
    
    ~B() override { cout << "member of class B deleted" << endl; }
    tmDpptr<A> ba;
    
    void Test() { cout << "test B!" << endl; }
};


class D : public tmDpptrTarget {
public:
    // Constructor
    D(char* aName) : tmDpptrTarget() {
        std::format_to_n(mName, 20, "{}", aName);
        cout << mName << " created" << endl;
    }
    
    // Copy constructor
    D(const D& other) : tmDpptrTarget(other) {
        std::copy_n(other.mName, 20, mName);
        cout << mName << " copied" << endl;
    }
    
    // Copy assignment operator
    D& operator=(const D& other) {
        if (this != &other) {
            tmDpptrTarget::operator=(other);
            std::copy_n(other.mName, 20, mName);
            cout << mName << " copy assigned" << endl;
        }
        return *this;
    }
    
    // Move constructor
    D(D&& other) noexcept : tmDpptrTarget(std::move(other)) {
        std::copy_n(other.mName, 20, mName);
        other.mName[0] = '\0';  // Clear the source name
        cout << mName << " moved" << endl;
    }
    
    // Move assignment operator
    D& operator=(D&& other) noexcept {
        if (this != &other) {
            tmDpptrTarget::operator=(std::move(other));
            std::copy_n(other.mName, 20, mName);
            other.mName[0] = '\0';  // Clear the source name
            cout << mName << " move assigned" << endl;
        }
        return *this;
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
  std::unique_ptr<D> up1(new D(const_cast<char*>("d1")));
  std::unique_ptr<D> up2(new D(const_cast<char*>("d2")));
  std::unique_ptr<D> up3(new D(const_cast<char*>("d3")));

  // Add to array without transferring ownership
  rld.push_back(up1.get());
  rld.push_back(up2.get());
  rld.push_back(up3.get());
  rld.push_back(up1.get());    // test multiple references

  cout << "Initially rld has " << rld.size() << " elements." << endl;

  // Let smart pointers handle cleanup
  up1.reset();
  up2.reset();
  up3.reset();
  
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
