#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef vector<vector<int>> matrix;

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

  int n, m, max = 0;
  string seq1, seq2, seq1Def, seq2Def;
  vector<string> subs1, subs2;
  matrix H;

  cin >> n >> m;
  cin >> seq1 >> seq2;

  cout << "seq1 size: " << n << endl;
  cout << "seq2 size: " << m << endl;
  cout << "seq1 is: " << seq1 << endl;
  cout << "seq2 is: " << seq2 << endl;

  H.resize(n + 1);
  for (int e = 0; e <= n; e++)
  {
    H[e].resize(m + 1);
  }

  subs1 = subGenerator(n, seq1);
  subs2 = subGenerator(m, seq2);

  for (int i = 0; i < int(subs1.size()); i++)
  {
    for (int j = 0; j < int(subs2.size()); j++)
    {

      string sub1 = subs1[i];
      string sub2 = subs2[j];

      sub1.insert(0, 1, '-');
      sub2.insert(0, 1, '-');

      cout << "sub1: " << sub1 << endl
           << "sub2: " << sub2 << endl;

      int size_sub1 = sub1.size();
      int size_sub2 = sub2.size();

      // calcula o sw
      H = high_score(sub1, sub2, size_sub1, size_sub2, H);

      // // descobrindo os maiores scores
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
    }
  }

  //     cout << "Score maximo: " << max << endl;
  //     cout << "Primeira sequencia utilizada: " << seqA_utilizada << endl;
  //     cout << "Segunda sequencia utilizada: " << seqB_utilizada << endl;

  //     return 0;
  // }

  return 0;
}