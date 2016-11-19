#include <iostream>

int reverse (int);

int main (void)
{
  int n;
  
  std::cout << "Enter an integer, it will show in reverse: ";
  std::cin  >> n;
  
  std::cout << "You entered " << n << "\n";
  std::cout << "In reverse: " << reverse(n) << std::endl;
}

int reverse (int number)
{
 int rem = number;
  while (rem > 0) {
  std::cout << rem %= 10; <<
  rem /= 10; }
}
