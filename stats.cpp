#include <iostream>

float Mean   (const int* array, size_t size); // calculates mean of data in array
float Median (int* array, size_t size);       // calculates median of data in array
void  Swap   (int& x, int& y);                // interchanges values of x and y
void  Sort   (int* array, size_t size);       // sorts the data in array

float Mean   (const int* array, size_t size)
{
  int sum = 0;
  
  for (size_t i = 0; i < size; ++i)
      sum += array[i];
  
  return sum / size;  
}

float Median (int* array, size_t size)
{
  Sort (array, size);
  
  for (size_t i = 0; i < size; ++i)
  {
    if (size % 2 != 0)
      return array[(size - 1) / 2];
    else
      return array[size / 2 - 1] + array[size / 2];
  }
}

void  Sort   (int* array, size_t size)
{
  for (int i = 0; i < size - 1; ++i)
  {
    int smallest = array[0];
  
  for (size_t j = 1; i < size - 1; ++i)
  {
    if (array[i] > array[i + 1])
      Swap(a[i], a[i + 1]);
  }
  }
  
}
