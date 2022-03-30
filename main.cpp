#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;
typedef vector<vector<int>> matrix;

void show_matrix(vector<vector<int>> H, int k)
{
  cout << "" << endl;
  for (int i = 0; i < k; i++)
  {
    cout << " " << endl;
    for (int j = 0; j < k; j++)
    {
      cout << H[i][j] << " ";
    }
  }
  cout << "" << endl;
  cout << "" << endl;
}

matrix high_score(string a, string b, int k, matrix H)
{
  int diagonal, deletion, insertion, w;
  // cout << a << endl;
  // cout << b << endl;

  for (int i = 1; i <= k; i++)
  {
    for (int j = 1; j <= k; j++)
    {

      if (a[i] == b[j])
      {
        w = 2;
      }
      else
      {
        w = -1;
      }

      diagonal = H[i - 1][j - 1] + w;
      deletion = H[i - 1][j] - 1;
      insertion = H[i][j - 1] - 1;

      H[i][j] = max({0, diagonal, deletion, insertion});
    }
  }

  return H;
}

int main()
{
  int n, m, k, j, i, p, max, score;
  max = 0;
  string seq1, seq2, sb1, sb2, best1;
  matrix H;

  sb2 += '-';

  std::default_random_engine generator;
  // generator.seed(10);

  cin >> n;
  cin >> m;

  cin >> seq1;
  cin >> seq2;

  for (int z = 0; z < 100; z++)
  {

    if (n > m)
    {
      std::uniform_int_distribution<int> distribution_k(3, m);
      k = distribution_k(generator);
    }
    else
    {
      std::uniform_int_distribution<int> distribution_k(3, n);
      k = distribution_k(generator);
    }

    std::uniform_int_distribution<int> distribution_j(0, m - k);
    j = distribution_j(generator);

    std::uniform_int_distribution<int> distribution_i(0, n - k);

    std::uniform_int_distribution<int> distribution_p(2, n + m);
    p = distribution_p(generator);

    sb2 += seq2.substr(j, k);

    // cout << "sb2: " << sb2 << endl;

    // cout << "j: " << j << endl;
    // cout << "n: " << n << endl;
    // cout << "m: " << m << endl;
    // cout << "k: " << k << endl;
    // cout << "p: " << p << endl;

    H.resize(k + 1);
    for (int e = 0; e <= k; e++)
    {
      H[e].resize(k + 1);
    }

    while (p > 0)
    {
      i = distribution_i(generator);
      sb1 = '-';
      sb1 += seq1.substr(i, k);
      // cout << sb1 << endl;
      // cout << "sb1: " << sb1 << endl;

      H = high_score(sb1, sb2, k, H);

      // show_matrix(H, k);

      score = 0;

      for (int i = 0; i <= k; i++)
      {
        for (int j = 0; j <= k; j++)
        {
          if (H[i][j] > score)
          {
            score = H[i][j];
            // cout << "score: " << score << endl;
          }
        }
      }

      if (score > max)
      {

        max = score;

        best1 = sb1.substr(1, k);

        // cout << "best1: " << best1 << endl;
      }

      p--;
    }

    cout << "BEST SCORE:" << max << endl;
    cout << "SA: " << best1 << endl;
    cout << "SB: " << sb2.substr(1, k) << endl;

    max = 0;

    cout << endl;
  }

  return 0;
}