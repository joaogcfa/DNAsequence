#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

int main()
{
  int n, m, k, j, i, p;
  // int j = 0;
  string seq1, seq2, sb1, sb2;

  std::default_random_engine generator;
  // generator.seed(10);

  cin >> n;
  cin >> m;

  cin >> seq1;
  cin >> seq2;

  if (n > m)
  {
    std::uniform_int_distribution<int> distribution_k(1, m);
    k = distribution_k(generator);
  }
  else
  {
    std::uniform_int_distribution<int> distribution_k(1, n);
    k = distribution_k(generator);
    while (k < 2)
    {
      k = distribution_k(generator);
    }
  }

  std::uniform_int_distribution<int> distribution_j(0, m - k);
  j = distribution_j(generator);

  // std::uniform_int_distribution<int> distribution_i(0, n - k);
  // i = distribution_i(generator);

  cout << "k: " << k << " j: " << j << endl;

  sb2 = seq2.substr(j, k);

  cout << "sb2: " << sb2;

  std::uniform_int_distribution<int> distribution_p(2, n + m);
  p = distribution_p(generator);

  while (p > 0 && i > n - k)
  {
    sb1 = seq1.substr(i, k);
    p--;
  }

  return 0;
}