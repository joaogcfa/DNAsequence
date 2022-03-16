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

    for(int i = 0; i<n; i++){
        for(int j = 0; i<m; j++){
            
        }
    }
    
    return H;
}


int main(){
    int n,m;
    // float w;
    string seq1,seq2;
    matrix H;

    cin >> n;
    cin >> m;

    cin >> seq1;
    cin >> seq2;
    
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }

    Smith(seq1,seq2,n,m,H);


    return 0;
}