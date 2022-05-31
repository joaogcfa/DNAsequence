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

void show_matrix(vector<vector<int>> H, int n, int m)
{
  cout << "" << endl;
  for (int i = 0; i < n; i++)
  {
    cout << " " << endl;
    for (int j = 0; j < m; j++)
    {
      cout << H[i][j] << " ";
    }
  }
  cout << "" << endl;
  cout << "" << endl;
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

  // for (int i = 0; i < int(subs1.size()); i++)
  // {
  //   for (int j = 0; j < int(subs2.size()); j++)
  //   {

  string sub1 = seq1;
  string sub2 = seq2;

  sub1.insert(0, 1, '-');
  sub2.insert(0, 1, '-');

  int size_sub1 = sub1.size();
  int size_sub2 = sub2.size();

  H.resize(size_sub1 + 1);
  for (int e = 0; e <= size_sub1; e++)
  {
    H[e].resize(size_sub2 + 1);
  }

  H = high_score(sub1, sub2, size_sub1, size_sub2, H);

  show_matrix(H, size_sub1, size_sub2);

  for (int i = 1; i <= size_sub1; i++)
  {
    for (int j = 1; j <= size_sub2; j++)
    {
      if (H[i][j] > max)
      {
        max = H[i][j];
        seq1Def = sub1;
        seq2Def = sub2;
      }
    }
  }
  // }
  // }
  cout << endl;
  cout << "Score Maximo: " << max << endl;
  cout << "Sub Seq1 Best: " << seq1Def.substr(1, sizeof(seq1Def)) << endl;
  cout << "Sub Seq2 Best: " << seq2Def.substr(1, sizeof(seq2Def)) << endl;

  return 0;
}