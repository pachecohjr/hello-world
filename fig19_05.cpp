// Fig 19.5: mergesort.h
// Class that creates a vector filled w/ random integers
// Provides a function to sort the vector with merge sort
#include <vector>

// MergeSort class definition
class MergeSort
{
  public:
  MergeSort(int); // constructor intializes vector
  void sort(); // sort vector using merge sort
  void displayElements() const; // display vector elements
  private:
  int size_; // vector size
  vector<int> data_; // vector of ints
  void sortSubVector (int, int); // sort subvector
  void merge (int, int, int); // merge two subvectors
  void displaySubVector (int, int) const; // display subvector
}; // end class MergeSort
