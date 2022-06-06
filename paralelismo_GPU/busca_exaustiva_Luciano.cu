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

struct calculo
{
    thrust::device_ptr<char> vA;
    thrust::device_ptr<char> vB;

    calculo(thrust::device_ptr<char> vA_, thrust::device_ptr<char> vB_)
        : vA(vA_),
          vB(vB_)
    {
    }
    __host__ __device__

        int
        operator()(const int &i, const int &j)
    {
        int w;
        if (vA[i] == vB[j])
        {

            w = 2;
        }
        else
        {
            w = -1;
        }

        return w;
    }
};

// struct inline_score
// {

//     __host__ __device__ int
//     operator()(const int &i, const int &j)
//     {
//         int actual = j;
//         int left = i - 1;
//         int max;

//         if (left >= actual)
//             max = left;
//         else
//             max = actual;

//         if (max < 0)
//             max = 0;

//         return max;
//     }
// };

int main()
{

    int n, m, max, endA, endB, sizeSubA, sizeSubB;
    string seq1, seq2;

    cin >> n >> m;
    cin >> seq1 >> seq2;

    thrust::device_vector<char> vA(seq1.begin(), seq1.end());
    thrust::device_vector<char> vB(seq2.begin(), seq2.end());

    thrust::device_vector<int> ponto(10);

    cout << "seq1 size: " << n << endl;
    cout << "seq2 size: " << m << endl;
    cout << "seq1 is: " << seq1 << endl;
    cout << "seq2 is: " << seq2 << endl;

    for (int beginA = 0; beginA < vA.size(); beginA++)
    {
        for (int beginB = 0; beginB < vB.size(); beginB++)
        {
            endA = beginA;
            while (endA < vA.size())
            {
                endB = beginB;
                sizeSubA = endA - beginA;
                while (endB < vB.size())
                {
                    sizeSubB = endB - beginB;
                    if (sizeSubA == sizeSubB && beginB + sizeSubA < vB.size())
                    {
                        cout << "beginA: " << beginA << endl;
                        cout << "endA: " << endA << endl
                             << endl;
                        cout << "beginB: " << beginB << endl;
                        cout << "endB: " << endB << endl
                             << endl;
                        thrust::transform(vA.begin() + beginA, vA.begin() + endA, vB.begin() + beginB, ponto.begin(), calculo(vA.data(), vB.data()));
                        for (int x = 0; x < ponto.size(); x++)
                        {
                            cout << "ponto: " << ponto[x] << endl;
                        }
                        endA++;
                    }
                    endB++;
                }
            }
        }
    }
    max = 0;

    cout
        << "Score Maximo: " << max << endl;
    return 0;
}