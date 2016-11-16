// Multipurpose sorting program using function ptrs
#include <iostream>
#include <iomanip>

// prototypes
void selectionSort (int [], const int, bool (*)(int, int));
void swap (int * const, int * const);
bool ascending (int, int);
bool descending (int, int);

int main ()
{
  const int arraySize = 10;
  int order; // 1 = ascending, 2 = descending
  int counter; // array index
  int a [arraySize] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };
  
  std::cout << "Enter 1 to sort in ascending order,\n"
    << "Enter 2 to sort in descending order: ";
  std::cin >> order;
  std::cout << "Data items in original order\n";
  
  // output original array
  for (counter = 0; counter < arraySize; ++counter)
    std::cout << setw(4) << a[counter];
  
  // sort array in ascending order; pass function ascending
  // as an argument to specify ascending order
  if (order == 1)
  {
    selectionSort(a, arraySize, ascending);
    std::cout << "Data items in ascending order\n";
  } // end if
  else 
  {
    selectionSort(a, arraySize, descending);
    std::cout << "Data items in descending order\n";
  } // end part of if ... else
  
  
