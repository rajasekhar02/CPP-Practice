#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int cnt = t;
    while(t--){
        int N,Q;
        int output = 0;
        cin>>N>>Q;
        string str;
        cin.ignore();
        cin>>str;
        vector<vector<int>> v(N+1,vector<int>(26,0));
        vector<int> alpha(26,0);
        for(int i=1;i<=N;i++){
            alpha[str[i-1]-'A']++;
            for(int j=0;j<26;j++){
                v[i][j] = alpha[j];
            }
        }
        int L,R;
        for(int i=0;i<Q;i++){
            cin>>L>>R;
            int div[2]= {0,0};
            for(int r=0;r<26;r++){
                div[abs(v[R][r]-v[L-1][r])%2]++;
            }
            if(div[1]<=1){
                output++;
            }
        }
        cout<<"Case #"<<(cnt-t)<<": "<<output<<endl;
    }
    return 0;
}