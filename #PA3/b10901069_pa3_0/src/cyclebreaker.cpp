#include <cstring>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#define ll long long 

using namespace std;

struct Edge {
    int start, end, weight;
};

////////////////////////////////////////////////// QUICK SORT EDGES //////////////////////////////////////////////////
int Partition(vector<Edge>& data, int low, int high) {
    int x = data[low].weight;
    int i = low-1;
    int j = high+1;
    while(true){
        do{
            j = j-1;
        }while(data[j].weight>x);
        do{
            i = i+1;
        }while(data[i].weight<x);
        if(i<j){
            swap(data[i], data[j]);
        }
        else return j;
    }
}
void Sort(vector<Edge>& edges, int left, int right){
    if(left>=right) return;
    else{
        int q = Partition(edges, left, right);
        Sort(edges, left, q);
        Sort(edges, q+1, right);
    }
}
////////////////////////////////////////////////// KRUSKAL of UNDIRECTED //////////////////////////////////////////////////
void Union(vector<Edge>& edges, int a, int b, int** M, int vernum){
    for(int i=0;i<vernum;i++){
        if(M[i][a]==1 || M[a][i]==1 || M[i][b]==1 || M[b][i]==1){
            M[i][b] = 1;
            M[b][i] = 1;
            M[i][a] = 1;
            M[a][i] = 1;
            for(int j=0;j<vernum;j++){
                if(M[j][a]==1 || M[a][j]==1 || M[j][b]==1 || M[b][j]==1){
                    M[j][i] = 1;
                    M[i][j] = 1;
                }
            }
        }
    }
}
void Kruskal(vector<Edge>& edges, int vernum, int edgenum, int** M, vector<Edge>& ban){
    //Sort(edges, 0, edgenum-1);
    int count=0, stop=0;
    for(int i=edgenum-1;i>=0;i--){
        if((M[edges[i].start][edges[i].end]!=1) && (M[edges[i].end][edges[i].start]!=1)){
            count++;
            M[edges[i].start][edges[i].end]=1;
            M[edges[i].end][edges[i].start]=1;
            Union(edges, edges[i].start, edges[i].end, M, vernum);
           //cout << edges[i].start << " " << edges[i].end << " " << edges[i].weight << endl;
        }
        else{
            ban.push_back(edges[i]);
            //cout << "here";
        }
        if(count == (vernum-1)) {
            stop = i;
            break; 
        }
    }
    for(int i=stop-1;i>=0;i--){
        ban.push_back(edges[i]);
    }
}
////////////////////////////////////////////////// KRUSKAL of DIRECTED //////////////////////////////////////////////////
void UnionD(vector<Edge>& edges, int a, int b, int** M, int vernum){
    for(int i=0;i<vernum;i++){
        if(M[i][a]==1){
            M[i][b]=1;
            for(int j=0;j<vernum;j++){
                if(M[b][j]==1) M[i][j]=1;
            }
        }
        if(M[b][i]==1){
            M[a][i]=1;
            for(int j=0;j<vernum;j++){
                if(M[j][a]==1) M[j][i]=1;
            }
        }
    }
}
void KruskalD(vector<Edge>& edges, int vernum, int edgenum, int** M, vector<Edge>& ban){
    //Sort(edges, 0, edgenum-1);
    for(int i=edgenum-1;i>=0;i--){
        if(M[edges[i].end][edges[i].start] != 1){ //end & start
            if(M[edges[i].start][edges[i].end] != 1 || edges[i].weight>0){
                M[edges[i].start][edges[i].end]=1;
                UnionD(edges, edges[i].start, edges[i].end, M, vernum);
            }
            else ban.push_back(edges[i]);
        }
        else ban.push_back(edges[i]);
    }
}
////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////
int main(int argc, char* argv[]){
    if(argc !=3){
        cout << "Format Error" << endl;
        return 1;
    }
    ////////////////////////////////////////////////// READ INPUT //////////////////////////////////////////////////
    ifstream fin(argv[1]); //open input file
    ofstream fout(argv[2]); //open output file
    if(!fin || !fout){
        cout << "[ERROR] Failed to open input or output file!" << endl;
        return 1;
    }

    char type;
    int vernum, edgenum; // MST -> |V|-1 edges
    fin >> type >> vernum >> edgenum;

    vector<Edge> edges;
    for(int i=0;i<edgenum;i++){ //0 to edgenum-1
        Edge edge;
        fin >> edge.start >> edge.end >> edge.weight;
        edges.push_back(edge);
    }

    ////////////////////////////////////////////////// CB PART //////////////////////////////////////////////////
    int** M = new int*[vernum];
    for(int i=0;i<vernum;i++){
        M[i] = new int[vernum];
    }
    for(int i=0;i<vernum;i++){
        for(int j=0;j<vernum;j++) M[i][j]=0;
    }

    vector<Edge> ban;
    Sort(edges, 0, edgenum-1);
    if(type=='u')Kruskal(edges, vernum, edgenum, M, ban);
    else if(type=='d') KruskalD(edges, vernum, edgenum, M, ban);
    
    ////////////////////////////////////////////////// OUTPUT FILE //////////////////////////////////////////////////
    /*
    fout << "after sort\n";
    for(int i=edgenum-1;i>=0;i--){
        fout << edges[i].start << " " << edges[i].end << " " << edges[i].weight << endl;
    }
    fout << "after Kruskal\n";
    */
    int weight=0;
    if(ban.size()==0) fout << "0\n";
    else{
        for(int i=0;i<ban.size();i++){
            weight += ban[i].weight;
        }
        fout << weight << endl;
        for(int i=0;i<ban.size();i++){
            fout <<  ban[i].start << " " << ban[i].end << " " << ban[i].weight << endl;
        }
    }
    

    fin.close();
    fout.close();
    for (int i=0;i<vernum;i++){
        delete[] M[i];
    }
    delete[] M;
    return 0;
}
/*
Reference
PA1
https://www.geeksforgeeks.org/kruskals-algorithm-simple-implementation-for-adjacency-matrix/
*/