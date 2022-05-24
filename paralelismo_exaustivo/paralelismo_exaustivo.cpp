#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>

using namespace std;
typedef vector<vector<int>> matrix;

struct comb
{
    string subs1;
    string subs2;
    int score;
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

int high_score(string a, string b, int n, int m, matrix H)
{

    int diagonal, deletion, insertion, w;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
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


    int max = -1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (H[i][j] > max)
            {
                max = H[i][j];
            }
        }
    }

    return max;
}

int main()
{

    int n, m, max = 0;
    string seq1, seq2, seq1Def, seq2Def, sub1, sub2, ompsub1, ompsub2;
    vector<string> subs1, subs2;
    

    vector<comb> combinations;

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

            sub1 = subs1[i];
            sub2 = subs2[j];

            comb comb;
            comb.subs1 = sub1;
            comb.subs2 = sub2;
            comb.score = 0;

            combinations.push_back(comb);


            sub1.clear();
            sub2.clear();

        }
    }

    // for (int i = 0; i < int(combinations.size()); i++)
    // {
    //     cout << "sub1: " << combinations[i].subs1 << endl;
    //     cout << "sub2: " << combinations[i].subs2 << endl;
    //     cout << "score: " << combinations[i].score << endl;
    // }

    #pragma omp parallel for private(ompsub1,ompsub2)
    for (int i = 0; i < int(combinations.size()); i++)
    {
        ompsub1 = combinations[i].subs1;
        ompsub2 = combinations[i].subs2;
        int score;
        matrix H;

        // cout << "sub1: " << combinations[i].subs1 << endl;
        // cout << "sub2: " << combinations[i].subs2 << endl << endl;

        ompsub1.insert(0, 1, '-');
        ompsub2.insert(0, 1, '-');

        H.resize(int(ompsub1.size()));
        for (int e = 0; e < int(ompsub1.size()); e++)
        {
            H[e].resize(int(ompsub2.size()));
        }

        score = high_score(ompsub1, ompsub2, int(ompsub1.size()), int(ompsub2.size()), H);


        combinations[i].score = score;
    }

    for (int i = 1; i < int(combinations.size()); i++)
    {
        int score = combinations[i].score;
        if (score > max)
        {
            max = score;
            seq1Def = combinations[i].subs1;
            seq2Def = combinations[i].subs2;
        }
    }

    cout << endl;
    cout << "Score Maximo: " << max << endl;
    cout << "Sub Seq1 Best: " << seq1Def.substr(1, sizeof(seq1Def)) << endl;
    cout << "Sub Seq2 Best: " << seq2Def.substr(1, sizeof(seq2Def)) << endl;

    return 0;
}