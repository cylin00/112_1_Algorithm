#include <cstring>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include "../utilities/tm_usage.h" 
#define ll long long 

using namespace std;

int MPS(int n, int i, int j, int* chord, vector<pair<int, int> >& data, int** M, bool** select){
    if(i>=j || i<0 ||  j>n-1){
        return 0;
    }
    else if(M[i][j]!=0) return M[i][j];
    else{
        int k =  chord[j];
        //case1
        if(k>j || k<i) M[i][j] = MPS(n, i, j-1, chord, data, M, select);
        //case2
        else if(k<j && k>i){
            int case2_1 = MPS(n, i, k-1, chord, data, M, select) + 1 + MPS(n, k+1, j-1, chord, data, M, select);
            int case2_2 = MPS(n, i, j-1, chord, data, M, select);
            if(case2_1 > case2_2){ //select jk
                M[i][j] = case2_1;
                select[i][j] = true;
            }
            else M[i][j] = case2_2;
        }
        //case3
        
        else if(k==i){
            M[i][j] = 1 + MPS(n, i+1, j-1, chord, data, M, select);
            select[i][j] = true;
        }
        
    }
    return M[i][j];
}

void chordK(int i, int j, vector<int> &selectK, int n, int* chord, bool** select){
    if(i>=j || i<0 ||  j>n-1) return;
    int k = chord[j];
    if(k>j || k<i) chordK(i, j-1, selectK, n, chord, select);
    else if(k<j && k>i){
        if(select[i][j]){
            selectK.push_back(k);
            chordK(i, k-1, selectK, n, chord, select);
            chordK(k+1, j-1, selectK, n, chord, select);
        }
        else chordK(i, j-1, selectK, n, chord, select);
    }
    else if(k==i){
        selectK.push_back(k);
        chordK(i+1, j-1, selectK, n, chord, select);
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Format Error" << endl;
        return 1;
    }
    //////////// read the input file /////////////
    ifstream fin(argv[1]); //open input file
    ofstream fout(argv[2]); //open output file
    if(!fin || !fout){
        cout << "Failed to open inout or ouput file" << endl;
        return 1;
    }
    int original_data;
    fin >> original_data; //read all of input
    vector<pair<int, int> > data;
    int num1, num2;
    while(fin >> num1 >> num2){
        if(num1==0 && num2==0) break;
        if(num1<num2) data.push_back(make_pair(num1, num2));
        else data.push_back(make_pair(num2, num1));
    }
    //////////// the DP part /////////////
    int N = data.size();
    int n = 2*N;
    int chord[n];

    for(const auto& pair: data){
        chord[pair.first] = pair.second;
        chord[pair.second] = pair.first;
    }

    int** M = new int*[n];
    for(int i=0;i<n;i++){
        M[i] = new int[n];
    }
    
    bool** select = new bool*[n];
    for(int i=0;i<n;i++){
        select[i] = new bool[n];
    }

    vector<int> selectK;
    M[0][n-1] = MPS(n, 0, n-1, chord, data, M, select);
    chordK(0, n-1, selectK, n, chord, select);
    cout << "out" << endl;

    //////////// write the output file /////////////
    fout << M[0][n-1] << endl;
    //fout << "size of selected K = " << selectK.size() << endl;
    bool finK[n];
    for(int i=0;i<n;i++){
        finK[i] = 0;
    }
    for(int i=0;i<selectK.size();i++){
        finK[selectK[i]] = true;
        //fout << selectK[i] <<endl;
    }
    /*
    for(int i=0;i<n;i++){
        fout << finK[i] << endl;
    }
    */
    for(int i=0;i<n;i++){
        for(const auto& pair:data){
            if(pair.first == i && finK[i]){
                fout << pair.first << " " << pair.second << endl;
                break;
            }
            else if(pair.second == i && finK[i]){
                fout << pair.second << " " << pair.first << endl;
                break;
            }
        }
    }
}
/*
bool nonIntersect(int i1, int j1, int i2, int j2){
    if(i1==i2) return 0;
    if((j1>i2 && i2>i1) && !(j1>j2 && j2>i1)) return 0;
    else if(!(j1>i2 && i2>i1) && (j1>j2 && j2>i1)) return 0;
    return 1;
}

int sumIntersect(int** table, int N, int k){
    int sum=0;
    for(int i=k+1;i<N;i++){
        if(table[k][i]==1) sum+=1;
    }
    for(int i=0;i<k;i++){
        if(table[i][k]==1) sum+=1;
    }
    return sum;
}
*/
/*
    int** table = new int*[N];
    for(int i=0;i<N;i++){
        table[i] = new int[N];
    }
    int i=-1;
    for(const auto& pair_i: data){ //construct a table
        i++;
        int j=-1;
        for(const auto& pair_j: data){
            j++;
            //if(i>=j) table[i][j] = 0;
            //else if(i<j) table[i][j] = nonIntersect(pair_i.first, pair_i.second, pair_j.first, pair_j.second);
            table[i][j] = nonIntersect(pair_i.first, pair_i.second, pair_j.first, pair_j.second);
        }
    }
    for(int x=0;x<N;x++){
        table[x][x] = sumIntersect(table, N, x);
    }
    */