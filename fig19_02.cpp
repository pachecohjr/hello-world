// Fig 19.2: binarysearch.h
// Class that contains a vector of random integers and a function 
// that uses binary search to find an integer.
#include <vector>

class BinarySearch
{
  public:
  BinarySearch (int ); // constructor initializes vector
  int binarySearch (int ) const; // perform a binary search on vector
  void displayElements() const; // display vector elements
  private:
  int size_; // vector size
  vector<int> data; // vector of ints
  void displaySubElements (int, int) const; // display range of values
}; // end class BinarySearch
  
