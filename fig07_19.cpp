// Fig 07.19: fig07_19.cpp
// This program sorts an array's values into ascending order
#include <iostream>
#include <iomanip>

int main (void)
{
  const int arraySize = 10; // size of array a
  int data[arraySize] = {34, 56, 4, 10, 77, 51, 93, 30, 5, 52};
  int insert; // temporary variable to hold element to insert
  
  std::cout << "Unsorted array:\n";
  
  // output original array
  for (int i = 0; i < arraySize; ++i)
    std::cout << std::setw(4) << data[i];
  
  // insertion sort
  // loop over the elements of the array
  for (int next = 1; next < arraySize; ++next)
  {
    insert = data[next]; // store the value in the current element
    
    int moveItem = next; // initialize location to place element
    
    while ( (moveItem > 0) && (data[moveItem - 1] > insert) )
    {
     data[moveItem] = data[moveItem - 1];
     moveItem--;
    } // end while
    
    data[moveItem] = insert; // placed inserted element into the array
  } // end for
  
  std::cout << "\nSorted array:\n";
  
  // output sorted array
  for (int i = 0; i < arraySize; ++i)
    std::cout << std::setw(4) << data[i];
  
  std::cout << std::endl;
} // end main
