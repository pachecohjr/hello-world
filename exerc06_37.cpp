#include <iostream>

// Could also overload these functions by changing them to the same name, since they are of different types
unsigned long fibonacci (unsigned long n);
size_t        fibonacci (size_t n);

int main (void)
{
  int j = 10;
  std::cout << "Recursion: \n:";
  for (int i = 0; i <= j; ++i)
    std::cout << "fibonacci(" << i << ") = " << fibonacci(i) << std::endl;
  
  std::cout << "\nIteration: \n:";
  for (size_t i = 2; i <= 10; ++i)
    std::cout << "fibonacci(" << i << ") = " << fibonacci(i) << std::endl;
  
  return 0;
}

unsigned long fibonacci (unsigned long n)
{
 if ((n == 0) || (n == 1))
   return n;
  else
    return fibonacci1(n - 1) + fibonacci1(n - 2);
}

size_t fibonacci (size_t n)
{
  size_t fib0 = 0;
  size_t fib1 = 1;
  size_t fib2;
 while (n > 1)
 {
   fib2 = fib0 + fib1;
   fib0 = fib1;
   fib1 = fib2;
 }
 
   if ((n == 0) || (n == 1))
   return n;
  else
    return fib2;  
}
