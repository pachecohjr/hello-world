#include <iostream>
#include <cstdlib>

int power (int, int);

int main (void)
{
  int base, exp;
  
  std::cout << "Enter an integer followed by another integer for it's exponent: \n\n";
  std::cin >> base >> exp;
  
  std::cout << base << " in the power of " << exponent << " is " << power(base, exp) << std::endl;
  
  return 0;
}

int power (int a, int x);
{
 if (x == 1)
   return a;
 else 
   return (a * power(a, x-1);  
}
