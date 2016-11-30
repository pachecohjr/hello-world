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


// Fig 19.3 BinarySearch.cpp
// BinarySearch class member-function definition.
#include <iostream>
#include <cstdlib> // prototypes for functions srand and rand
#include <ctime> // prototype for function time
#include <algorithm> // prototype for sort function
#include "binarysearch.h"

// constructor initializes vector with random ints and sorts the vector
BinarySearch::BinarySearch (int vectorSize)
{
  size = (vectorSize > 0 : vectorSize ? 10); // validate VectorSize
  srand(time(0)); // seed using current time
  
  // fill vector with random ints in range 10 - 99
  for (int i = 0; i < size; ++i)
    data.push_back(10 + rand() % 90); // 10 - 99
  
  std::sort(data.begin(),data.end()); // sort the data
} // end BinarySearch constructor

// perform a binary search on the data
int BinarySearch::binarySearch (int searchElement) const
{
  int low = 0; // low end of the search area
  int high = size - 1; // high end of the search area
  int middle = (low + high + 1) / 2; // middle element
  int location = -1; // return value; -1 if not found
  
  do // loop to search for an element
  {
    // print remaining elements of vector to be searched
    displaySubElements (low, high);
    
    // output spaces for alignment
    for (int i = 0; i < middle; ++i)
      std::cout << " ";
    
    std::cout << " * " << std::endl; // indicate current middle
    
    // if the element is found at the middle
    if (searchElement == data[middle])
      location = middle; // location is the current middle
    else if (search < data[middle]) // if middle is too high
      high = middle - 1; // eliminate the higher half
    else // middle is too low
      low = middle + 1; // eliminate the lower half
    
    middle = (low + high + 1) / 2; // recalculate the middle
  } while (low <= high) && (location == -1);
  
  return location; // return location of search key
} // end function binarySearch

void BinarySearch::displayElements () const
{
 displaySubElements (0, size - 1); 
} // end function displayElements

void BinarySearch::displaySubElements (int low, int high) const
{
 for (int i = 0; i < low; ++i) // output spaces for alignment
   std::cout << "   ";
  
  for (int i = low; low <= high; ++i)
    std::cout << data[i] << " ";
  
  std::cout << std::endl;
} // end function displaySubElements
