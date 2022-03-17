#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>


using namespace std;
typedef vector<vector<int>> matrix;


matrix Smith(string a, string b, int n, int m, matrix H);

struct path
{
  int direction;
};

typedef vector<vector<path>> matrixpath;


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

void show_matrix_path(vector<vector<path>> H, int n, int m){
  cout << "" << endl;
  for(int i = 0; i < n; i++){
    cout << " " << endl;
    for(int j = 0; j < m; j++){
      cout << H[i][j].direction << " ";
    }
  }
  cout << "" << endl;
  cout << "" << endl;
}



matrix Smith(string a, string b, int n, int m, matrix H, matrixpath path){
  int diagonal, deletion, insertion, w;

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){

          if (a[i] == b[j]){
            w = 2;
          }
          else{
            w=-1;
          }


          diagonal = H[i-1][j-1] + w;
          deletion = H[i-1][j] -1;
          insertion = H[i][j-1] -1;

          H[i][j] = max({0,diagonal,deletion,insertion});  
        }
    }
    
    return H;
}

matrixpath Smithpath(string a, string b, int n, int m, matrix H, matrixpath path){
  int diagonal, deletion, insertion, w;

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){

          if (a[i] == b[j]){
            w = 2;
          }
          else{
            w=-1;
          }


          diagonal = H[i-1][j-1] + w;
          deletion = H[i-1][j] -1;
          insertion = H[i][j-1] -1;

          H[i][j] = max({0,diagonal,deletion,insertion});
          if(max({0,diagonal,deletion,insertion}) == diagonal){
            path[i][j].direction = 1;//"diagonal";
          }
          if(max({0,diagonal,deletion,insertion}) == deletion){
            path[i][j].direction = 2;//"deletion";
          }
          if(max({0,diagonal,deletion,insertion}) == insertion){
            path[i][j].direction = 3;//"insertion";
          }
            
        }
    }
    
    return path;
}




int main(){
    int n,m;
    char first_signal = '-';
    string seq1,seq2;
    matrix H, H2;
    matrixpath path;
    


    cin >> n;
    cin >> m;

    cin >> seq1;
    cin >> seq2;

    seq1 = first_signal + seq1;
    seq2 = first_signal + seq2;
    

    H.resize(n+1);
    H2.resize(n+1);
    path.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
        H2[e].resize(m+1);
        path[e].resize(m+1);
    }

    H = Smith(seq1,seq2,n,m,H,path);
    path = Smithpath(seq1,seq2,n,m,H,path);

    cout << "Matrix after algorithm: ";
    show_matrix(H,n,m);
    show_matrix_path(path,n,m);


    int top_H = 0;
    int top_j = 0;
    int top_i = 0;

    for (int i = 1; i<n; i++){
      for(int j = 1; j<m; j++){
        if(H[i][j] > top_H){
          top_H = H[i][j];
          top_i = i;
          top_j = j;
        }
      }
    }

    cout << "Highest value in H: " << top_H << endl;


    return 0;
}