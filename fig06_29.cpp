// recursive definition of function factorial
unsigned long factorial (unsigned long number)
{
  if (number <= 1) // test for base case
    return number; // base cases: 0! = 1  and 1! = 1
  else // recursion step
    return number * factorial(number - 1); 
} // end function factorial
