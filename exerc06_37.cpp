#include <iostream>

// Could also override these functions by changing them to the same name, since they are of different types
unsigned long fibonacci1 (unsigned long n);
size_t        fibonacci2 (size_t n);

int main (void)
{
  int j = 10;
  std::cout << "Recursion: \n:";
  for (int i = 0; i <= j; ++i)
    std::cout << "fibonacci(" << i << ") = " << fibonacci1(i) << std::endl;
  
  std::cout << "\nIteration: \n:";
  for (int i = 2; i <= j; ++i)
    std::cout << "fibonacci(" << i << ") = " << fibonacci2(i) << std::endl;
  
  return 0;
}

unsigned long fibonacci1 (unsigned long n)
{
 if ((n == 0) || (n == 1))
   return n;
  else
    return fibonacci1(n - 1) + fibonacci1(n - 2);
}

size_t fibonacci2 (size_t n)
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
