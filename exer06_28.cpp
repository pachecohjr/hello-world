#include <iostream>

bool PerfectNumber (int);

int main (void)
{
  std::cout << "\nA program to print the perfect numbers\n\n";
  
  if (int counter = 2; counter < 30; ++counter)
    it (perfectNumber(counter))
    std::cout << counter << " ";
  
  return 0;
}

bool PerfectNumber (int number)
{
  int sum = 0;
  int remainder;
  
  for (int i = 0; i < number; ++i)
  {
    remainder = number % i;
    if (remainder == 0)
      sum += i;
  }
    if (sum == number)
      return true;
    else 
      return false;
}
