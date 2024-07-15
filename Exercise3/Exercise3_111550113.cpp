#include <iostream>
#include <vector>
using namespace std;
//r=1~4, c=assign to how many, d= r sum

int maxprofit(int r,int c,vector<vector<int>>&table, int d){
    int a=min(r,d-c+1);
    vector<vector<int>> dp(c+1,vector<int>(d-c+2,0));
    //dp: row=c, column=d-c+1
    for(int i=1;i<=c;i++){
        for(int j=1;j<=d-c+1;j++){
            dp[i][j]=dp[i-1][j];
            for(int k=1;k<=min(j,a);k++){
                dp[i][j]=max(dp[i][j],dp[i-1][j-k+1]+table[k-1][i-1]);
            }
        }
    }
    return dp[c][d-c+1];
}

int main(){
    int t; //testcase
    cin>>t;
    while(t--){
        int r,c;
        cin>>r>>c; //row(day), column(course)
        vector<vector<int>> table(r, vector<int>(c));
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                cin>>table[i][j];
            }
        }
        int q; //query
        cin>>q;
        while(q--){
            int d;
            cin>>d;
            int ans=maxprofit(r,c,table,d);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
