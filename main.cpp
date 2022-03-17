#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>


using namespace std;
typedef vector<vector<int>> matrix;

matrix Smith(string a, string b, int n, int m, matrix H);

void show_matrix(vector<vector<int>> H, int n, int m){
  cout << "" << endl;
  for(int i = 0; i < n; i++){
    cout << " " << endl;
    for(int j = 0; j < m; j++){
      cout << H[i][j] << " ";
    }
  }
  cout << "" << endl;
  cout << "" << endl;
}



matrix Smith(string a, string b, int n, int m, matrix H){
  int diagonal, deletion, insertion, w;

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){

          if (a[i] == b[j]){
            w = 2;
          }
          else{
            w=-1;
          }

          // cout << w << endl;
          // cout << H[i-1][j-1]<< endl;

          diagonal = H[i-1][j-1] + w;
          // cout << diagonal;
          deletion = H[i-1][j] -1;
          insertion = H[i][j-1] -1;

          H[i][j] = max({0,diagonal,deletion,insertion});
            
        }
    }
    
    return H;
}


int main(){
    int n,m;
    // float w;
    string seq1,seq2;
    matrix H;
    char first_signal = '-';


    cin >> n;
    cin >> m;

    cin >> seq1;
    cin >> seq2;

    seq1 = first_signal + seq1;
    seq2 = first_signal + seq2;
    

    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    H = Smith(seq1,seq2,n,m,H);

    show_matrix(H,n,m);


    return 0;
}