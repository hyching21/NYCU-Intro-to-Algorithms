#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
#define INF INT_MAX

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void INSERT(vector<vector<int>>&yt,int i,int j){
    if(i==0 && j==0){
        return;
    }
    if(i==0){      //first row
        if(yt[i][j]<yt[i][j-1]){
            swap(yt[i][j],yt[i][j-1]);
            INSERT(yt,i,j-1);
        }
        return;
    }
    if(j==0){       //first column
        if(yt[i][j]<yt[i-1][j]){
            swap(yt[i][j],yt[i-1][j]);
            INSERT(yt,i-1,j);
        }
        return;
    }
    if(yt[i][j]<yt[i-1][j]){       //up
        swap(yt[i][j],yt[i-1][j]);
        INSERT(yt,i-1,j);
    }
    if(yt[i][j]<yt[i][j-1]){     //left
        swap(yt[i][j],yt[i][j-1]);
        INSERT(yt,i,j-1);
    }
}
void initial(vector<vector<int>>&yt,vector<int>&insert_key,int m,int n){
    for(int key:insert_key){
        if(yt[m-1][n-1]!=INF){
            cout<<"Cannot insert!\n";
        }
        else{
            yt[m-1][n-1]=key;
            INSERT(yt,m-1,n-1);
        }
    }
}
void fix(vector<vector<int>>&yt,int i,int j){
    int m=yt.size();
    int n=yt[0].size();
    // get the bottom and right num of cur
    int bottom,right;
    if(i+1<m){bottom=yt[i+1][j];}
    else{bottom=INF;}
    if(j+1<n){right=yt[i][j+1];}
    else{right=INF;}
    if (bottom==INF && right==INF) {
        return;
    }
    if(bottom<right){ //down
        swap(yt[i][j],yt[i+1][j]);
        fix(yt,i+1,j);
    }
    else{ //right
        swap(yt[i][j],yt[i][j+1]);
        fix(yt,i,j+1);
    }

}
void EXTRACT_MIN(vector<vector<int>>&yt,ofstream& out){
    int min=yt[0][0];
    yt[0][0]=INF;
    fix(yt,0,0);
    out<<"Extract-min "<<min<<"\n";
}
void output(vector<vector<int>>&yt,int m,int n,ofstream& out){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(yt[i][j]==INF){out<<"x ";}
            else{out<<yt[i][j]<<" ";}
        }
        out<<"\n";
    }
    out<<"\n";
}
int main(){
    //read in txt
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    if(out.fail()){
        cout<<"Error opening output\n";
        exit(1);
    }
    if(in.fail()){
        cout<<"Error opening input\n";
        exit(1);
    }
    int yt_num;
    in>>yt_num;
    //cout<<"yt_num"<<yt_num<<"\n";
    while(yt_num!=0){
        int choice;
        in>>choice;
        //cout<<"choice"<<choice<<"\n";

        if(choice==1){
            vector<vector<int>> yt;
            vector<int> insert_key;
            int insert_num;
            string l;
            in.get();
            getline(in,l);
            istringstream i(l);
            while(i>>insert_num){
                insert_key.push_back(insert_num);
            }
            int insert_size=insert_key.size();
            out<<"Insert ";
            for(int i=0;i<insert_size;i++){
                out<<insert_key[i]<<" ";
            }
            out<<"\n";
            //store tableau data
            string line;
            while(getline(in,line)){
                stringstream iss(line);
                vector<int> row;
                string c;

                if(line.empty()){
                    break;
                }
                while(iss>>c){
                    if(c=="x"){row.push_back(INF);}
                    else if(isdigit(c[0])){
                        row.push_back(stoi(c));
                    }
                }
                yt.push_back(row);
            }
            int m=yt.size();
            int n=yt[0].size();
            initial(yt,insert_key,m,n);
            output(yt,m,n,out);
        }
        else if(choice==2){
            vector<vector<int>> yt;
            in.get();
            string line;
            while(getline(in,line)){
                stringstream iss(line);
                vector<int> row;
                string c;

                if(line.empty()){
                    break;
                }
                while(iss>>c){
                    if(c=="x"){row.push_back(INF);}
                    else if(isdigit(c[0])){
                        row.push_back(stoi(c));
                    }
                }
                yt.push_back(row);
            }
            int m=yt.size();
            int n=yt[0].size();
            EXTRACT_MIN(yt,out);
            output(yt,m,n,out);
        }
        yt_num--;
    }
    return 0;

}
