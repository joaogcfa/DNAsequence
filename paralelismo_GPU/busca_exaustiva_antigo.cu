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
  // essas marcações indicam que o código deve ser compilado para CPU (host)
  // e GPU (device)
  // IMPORTANTE: somente código com a marcação __device__ é compilado para GPU
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
}

matrix high_score(string a, string b, int n, int m, matrix H)
{
  int diagonal, deletion, insertion, w;

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
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

  int N, M, score, max = 0;
  string S, T, seq1, seq2, seq1Def, seq2Def;
  vector<string> subs1, subs2;
  matrix H;

  cin >> N >> M;
  cin >> S >> T;

  // cout << "seq1 size: " << n << endl;
  // cout << "seq2 size: " << m << endl;
  // cout << "seq1 is: " << seq1 << endl;
  // cout << "seq2 is: " << seq2 << endl;

  // subs1 = subGenerator(n, seq1);

  // thrust::device_vector<string> sub_device(subs1);
  // thrust::copy(subs1.begin(), subs1.end(), sub_vector1.begin());

  // subs2 = subGenerator(m, seq2);
  // thrust::copy(thrust::device, subs2.begin(), subs2.end(), sub_vector2.begin());

  // for (int i = 0; i < int(subs1.size()); i++)
  // {
  //   for (int j = 0; j < int(subs2.size()); j++)
  //   {

  //     string S = subs1[i];
  //     string T = subs2[j];

  // string S = "ACT";
  // string T = "GCT";

  // const char *L = S.c_str();

  // int L = strlen(S);
  // int M = strlen(T);

  // device_vector<int> calc[2];
  // calc[0].resize(N + 1);
  // calc[1].resize(N + 1);

  // sub1.insert(0, 1, '-');
  // sub2.insert(0, 1, '-');

  // int N = S.size();
  // int M = T.size();

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
    // cout << d_S[1] << endl;
    thrust::transform(c0, c1, temp.begin() + 1, calculo(d_S.data(), letradeT, calc.data()));
    thrust::inclusive_scan(temp.begin() + 1, temp.end(), calc.begin() + 1, inline_score());
    // cout << "calc: " << endl;
    for (int l = 0; l < calc.size(); l++)
    {
      cout << " " << calc[l];
    }
    score = thrust::reduce(calc.begin(), calc.end(), 0, thrust::maximum<int>());

    if (score > max)
    {
      max = score;
    }
    // cout << endl;
    // cout << "temp: " << endl;
    // for (int l = 0; l < temp.size(); l++)
    // {
    //   cout << " " << temp[l];
    // }
    cout << endl;
  }

  // thrust::copy(d_S.begin(), d_S.end(), std::ostream_iterator<char>(std::cout, " "));

  // calc.begin().resize(N + 1);
  // H.resize(size_sub1 + 1);
  // for (int e = 0; e <= size_sub1; e++)
  // {
  //   H[e].resize(size_sub2 + 1);
  // }

  // H = high_score(sub1, sub2, size_sub1, size_sub2, H);

  // for (int i = 1; i <= size_sub1; i++)
  // {
  //   for (int j = 1; j <= size_sub2; j++)
  //   {
  //     if (H[i][j] > max)
  //     {
  //       max = H[i][j];
  //       seq1Def = sub1;
  //       seq2Def = sub2;
  //     }
  //   }
  // }
  // }
  cout << "Score Maximo: " << max << endl;
  return 0;
}
// cout << endl;
// cout << "Sub Seq1 Best: " << seq1Def.substr(1, sizeof(seq1Def)) << endl;
// cout << "Sub Seq2 Best: " << seq2Def.substr(1, sizeof(seq2Def)) << endl;
// }