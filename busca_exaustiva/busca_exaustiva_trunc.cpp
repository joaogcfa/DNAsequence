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

int main()
{

    int n, m, w, max = 0;
    string seq1, seq2, seq1Def, seq2Def;
    vector<string> subs1, subs2;

    cin >> n >> m;
    cin >> seq1 >> seq2;

    cout << "seq1 size: " << n << endl;
    cout << "seq2 size: " << m << endl;
    cout << "seq1 is: " << seq1 << endl;
    cout << "seq2 is: " << seq2 << endl;

    subs1 = subGenerator(n, seq1);
    subs2 = subGenerator(m, seq2);

    for (int i = 0; i < int(subs1.size()); i++)
    {
        for (int j = 0; j < int(subs2.size()); j++)
        {

            w = 0;

            string sub1 = subs1[i];
            string sub2 = subs2[j];

            int size_sub1 = sub1.size();
            int size_sub2 = sub2.size();

            if (size_sub1 >= size_sub2)
            {
                sub1.resize(size_sub2);
            }
            else
            {
                sub2.resize(size_sub1);
            }

                        for (int i = 1; i <= size_sub1; i++)
            {
                for (int j = 1; j <= size_sub2; j++)
                {

                    if (sub1[i] == sub2[j])
                    {
                        w += 2;
                    }
                    else
                    {
                        w -= 1;
                    }
                }
            }
            if (w >= max)
            {
                max = w;
                seq1Def = sub1;
                seq2Def = sub2;
            }
        }
    }
    cout << endl;
    cout << "Score Maximo: " << max << endl;
    cout << "Sub Seq1 Best: " << seq1Def.substr(1, sizeof(seq1Def)) << endl;
    cout << "Sub Seq2 Best: " << seq2Def.substr(1, sizeof(seq2Def)) << endl;

    return 0;
}