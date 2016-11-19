#include <iostream>

int gcd (int, int);

int main (void)
{
  int a, b;
  
  std::cout << "Enter first number: ";
  std::cin  >> a;
  std::cout << "Enter second number: ";
  std::cin  >> b;
  
  std::cout << "The G.C.D. of " << a << " and " << b << " is " << gcd(a,b) << std::endl;
  
  return 0;
}

int gcd (int a, int b) // local a and and local b
{
  std::cout << "a: " << a << "b: " << b << std::endl;
  // if b divides 
 if (b % a == 0) 
   return a;
  if (a > b)
    return gcd (b, a);
  else
    return gcd (b % a, a);
}
