#include <cstdio>
#include <iostream>

int main ()
{
  int t, n, a_in;

  std::cin >> t;

  while (t > 0) {
  std::cin >> n;

int A[n], A2[n];

for (int i = 0; i < n; i++) {
        std::cin >> a_in;
        A[i] = a_in;
}

for (int i = 0; i < n; i++) {
        if (i < n - 1)
           A2[i] = A[i] | A[i + 1];
        else
           A2[i] = A[i];
}

for (int i = 0; i < n; i++)
std::cout << A2[i] << ' ';
std::cout << std::endl;

t--;
}

  return 0;
}
