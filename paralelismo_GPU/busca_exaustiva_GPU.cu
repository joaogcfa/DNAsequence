#include <vector>
#include <cmath>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/device_ptr.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/copy.h>
#include <thrust/execution_policy.h>
#include <thrust/iterator/counting_iterator.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
typedef vector<vector<int>> matrix;

struct calculo
{
  thrust::device_ptr<char> d_S;
  char letradeT;
  thrust::device_ptr<int> calc;

  calculo(thrust::device_ptr<char> d_S_, char letradeT_, thrust::device_ptr<int> calc_)
      : d_S(d_S_),
        letradeT(letradeT_),
        calc(calc_)
  {
  }
  __host__ __device__

      int
      operator()(const int &i)
  {
    int w;
    int diagonal;
    int insertion;
    int max = 0;
    if (d_S[i - 1] == letradeT)
    {
      w = 2;
    }
    else
    {
      w = -1;
    }

    diagonal = calc[i - 1] + w;
    insertion = calc[i] - 1;

    if (diagonal > max)
    {
      max = diagonal;
    }
    if (insertion > max)
    {
      max = insertion;
    }

    return max;
  }
};
struct inline_score
{

  __host__ __device__ int
  operator()(const int &i, const int &j)
  {
    int actual = j;
    int left = i - 1;
    int max;

    if (left >= actual)
      max = left;
    else
      max = actual;

    if (max < 0)
      max = 0;

    return max;
  }
};
vector<string> subGenerator(int size, string seq)
{
  vector<string> sub_seqs;
  for (int i = 0; i < size; i++)
  {
    string cand = "";
    for (int j = i; j < size; j++)
    {
      cand += seq[j];
      sub_seqs.push_back(cand);
    }
  }

  return sub_seqs;
};

int main()
{

  int N, M,n,m, score,maxlc, max = 0;
  string S, T, seq1, seq2;
  vector<string> subs1, subs2;
  matrix H;

  cin >> n >> m;
  cin >> seq1 >> seq2;

  // cout << "seq1 size: " << n << endl;
  // cout << "seq2 size: " << m << endl;
  // cout << "seq1 is: " << seq1 << endl;
  // cout << "seq2 is: " << seq2 << endl;

  subs1 = subGenerator(n, seq1);

  // thrust::device_vector<string> sub_device(subs1);
  // thrust::copy(subs1.begin(), subs1.end(), sub_vector1.begin());

  subs2 = subGenerator(m, seq2);
  // thrust::copy(thrust::device, subs2.begin(), subs2.end(), sub_vector2.begin());

  for (int i = 0; i < int(subs1.size()); i++)
  {
    for (int j = 0; j < int(subs2.size()); j++)
    {

      string S = subs1[i];
      string T = subs2[j];


      N = S.size();
      M = T.size();

      thrust::device_vector<int> calc(N + 1);
      thrust::device_vector<int> temp(N + 1);

      thrust::fill(calc.begin(), calc.end(), 0);
      thrust::fill(temp.begin(), temp.end(), 0);

      thrust::device_vector<char> d_S(S.begin(), S.end());

      thrust::counting_iterator<int> c0(1);
      thrust::counting_iterator<int> c1(N + 1);

      for (int j = 0; j < M; j++)
      {
        char letradeT = T[j];
        thrust::transform(c0, c1, temp.begin() + 1, calculo(d_S.data(), letradeT, calc.data()));
        thrust::inclusive_scan(temp.begin() + 1, temp.end(), calc.begin() + 1, inline_score());
        // for (int l = 0; l < calc.size(); l++)
        // {
        //   cout << " " << calc[l];
        // }
        score = thrust::reduce(calc.begin(), calc.end(), 0, thrust::maximum<int>());

        if (score > maxlc)
        {
          maxlc = score;
          if (maxlc > max)
          max = maxlc;
        }
        cout << endl;
      }
    }
    cout << "*" << endl;
  }
  cout << "Score Maximo: " << max << endl;
  return 0;
}
// cout << endl;
// cout << "Sub Seq1 Best: " << seq1Def.substr(1, sizeof(seq1Def)) << endl;
// cout << "Sub Seq2 Best: " << seq2Def.substr(1, sizeof(seq2Def)) << endl;
// }