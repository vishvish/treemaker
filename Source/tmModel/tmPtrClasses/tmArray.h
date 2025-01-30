#ifndef _TMARRAY_H_
#define _TMARRAY_H_

// Common TreeMaker header
#include "tmHeader.h"

// Standard libraries
#include <vector>
#include <algorithm>
#include <sstream>

/**********
class tmArray
A base class for arrays of objects. Derived from std::vector<T>.
**********/
template <class T>
class tmArray : public std::vector<T> {
public:
  // Constants
  enum {
    BAD_OFFSET = std::size_t(-1),
    BAD_INDEX = std::size_t(0)
  };

  // Constructors
  tmArray() : std::vector<T>() {};
  tmArray(const tmArray<T>& v) : std::vector<T>(v) {};
  tmArray(std::size_t n) : std::vector<T>(n) {};
  tmArray(std::size_t n, const T& t) : std::vector<T>(n, t) {};
  
  // Destructor
  virtual ~tmArray() {};
  
  // Assignment
  tmArray<T>& operator=(const tmArray<T>& v) {
    if (this != &v) std::vector<T>::operator=(v);
    return *this;
  };
  
// Indexing
  T& operator[](std::size_t n) {
    TMASSERT(n >= 0 && n < this->size());
    return std::vector<T>::operator[](n);
  };

  const T& operator[](std::size_t n) const {
    TMASSERT(n >= 0 && n < this->size());
    return std::vector<T>::operator[](n);
  };
  
  // Add an item to the end of the list if it isn't already in the list
  void union_with(const T& t) {
    if (std::find(this->begin(), this->end(), t) == this->end()) 
      this->std::vector<T>::push_back(t);
  }
  
  // Add all items from aList to the end of this list if they aren't already in the list
  void merge_with(const tmArray<T>& aList) {
    for (const auto& item : aList) {
      if (std::find(this->begin(), this->end(), item) == this->end()) {
        this->std::vector<T>::push_back(item);
      }
    }
  }
  
  // Add all items from another list that aren't already in this list
  void union_with(const tmArray<T>& aList) {
    for (const auto& item : aList) {
      if (std::find(this->begin(), this->end(), item) == this->end()) {
        this->std::vector<T>::push_back(item);
      }
    }
  }

  // Get offset (0-based index) of an item
  std::size_t GetOffset(const T& t) const {
    std::size_t i = std::size_t(std::find(this->begin(), this->end(), t) - this->begin());
    if (i < this->size()) return i;
    else return BAD_OFFSET;
  }

  // Test if array contains an item
  bool contains(const T& t) const {
    return std::find(this->begin(), this->end(), t) != this->end();
  }

  // Test if array is not empty
  bool not_empty() const {
    return !this->empty();
  }

  // Remove an item from a list given its value
  void erase_remove(const T& t) {
    this->erase(std::remove(this->begin(), this->end(), t), this->end());
  }

  // Rotate all items toward the front of the array by one position
  void rotate_left() {
    if (this->size() > 1) {
      T temp = this->front();
      this->erase(this->begin());
      this->push_back(temp);
    }
  }

  // Count occurrences of an item in the array
  std::size_t count(const T& t) const {
    return std::count(this->begin(), this->end(), t);
  }

  // Get 1-based index of an item
  std::size_t GetIndex(const T& t) const {
    auto it = std::find(this->begin(), this->end(), t);
    if (it != this->end()) return std::size_t(it - this->begin()) + 1;
    return BAD_INDEX;
  }

  // Test if this array has any elements in common with another array
  bool intersects(const tmArray<T>& other) const {
    for (const auto& item : other) {
      if (contains(item)) return true;
    }
    return false;
  }

  // Get string representation (for debugging)
  std::string GetStr() const {
    std::stringstream ss;
    ss << "[" << this->size() << "]: ";
    for (std::size_t i = 0; i < this->size(); ++i)
      ss << (*this)[i]->GetIndex() << " ";
    return ss.str();
  }
  
  // Remove an item from a list given its index
  tmArray<T>& RemoveItemAt(std::size_t n) {
    TMASSERT(n > 0);
    TMASSERT(n <= this->size());
    this->std::vector<T>::erase(this->begin() + ptrdiff_t(n) - 1);
    return *this;
  }
  
  // Insert an item at a specified index
  tmArray<T>& InsertItemAt(std::size_t n, const T& t) {
    TMASSERT(n > 0);
    TMASSERT(n <= this->size());
    this->std::vector<T>::insert(this->begin() + ptrdiff_t(n) - 1, t);
    return *this;
  }
  
  // Move an item from one position to another
  tmArray<T>& MoveItem(std::size_t inFromIndex, std::size_t inToIndex) {
    TMASSERT(inFromIndex > 0);
    TMASSERT(inToIndex > 0);
    TMASSERT(inFromIndex <= this->size());
    TMASSERT(inToIndex <= this->size());
    if (inFromIndex == inToIndex) return *this;
    T t = (*this)[inFromIndex];
    RemoveItemAt(inFromIndex);
    InsertItemAt(inToIndex, t);
    return *this;
  }

  // Get item at 1-based index
  T& NthItem(std::size_t n) {
    TMASSERT(n > 0);
    TMASSERT(n <= this->size());
    return (*this)[n];
  }
  
  const T& NthItem(std::size_t n) const {
    TMASSERT(n > 0);
    TMASSERT(n <= this->size());
    return (*this)[n];
  }
  
  // Add an item to the front of the list
  void push_front(const T& t) {
    this->insert(this->begin(), t);
  }
  
  // Replace an item at a given index
  void ReplaceItemAt(std::size_t n, const T& t) {
    TMASSERT(n > 0);
    TMASSERT(n <= this->size());
    (*this)[n] = t;
  }
  
  // Replace all occurrences of one item with another
  void replace_with(const T& oldItem, const T& newItem) {
    std::replace(this->begin(), this->end(), oldItem, newItem);
  }
  
  // Keep only items that are also in the other list
  void intersect_with(const tmArray<T>& other) {
    tmArray<T> temp;
    for (const auto& item : *this) {
      if (other.contains(item)) {
        temp.push_back(item);
      }
    }
    *this = temp;
  }
};

#endif // _TMARRAY_H_
