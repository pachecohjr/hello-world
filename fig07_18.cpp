// Fig 7.18: fig07_18.cpp
// Linear search of an array
#include <iostream>

int linearSearch (const int [], int, int); // prototype

int main (void)
{
  const int arraySize = 100; // size of array a
  int a[arraySize]; // create array a
  int searchKey; // value to locate in array a
  
  for (int i = 0; i < arraySize; ++i)
    a[i] = 2 * i; // create some data
  
  std::cout << "Enter search integer key: ";
  std::cin  >> searchKey;
  
  // attempt to locate searchKey in array a
  int element = linearSearch (a, searchKey, arraySize);
  
  // display results
  if (element != -1)
    std::cout << "Found value in element " << element << std::endl;
  else
    std::cout << "Value not found." << std::endl;  
} // end main


  // compare key to every element of array until location is
  // found or until end of array is reached; return subscript of
  // element if key is found or -1 if key is not found
  linearSearch (const int array, int key, int sizeOfArray)
  {
    for (int j = 0; j < sizeOfArray; ++j)
      if (array[j] == key) // if found,
        return j; // return location of key
    
    return -1; // key not found
  } // end function linearSearch
