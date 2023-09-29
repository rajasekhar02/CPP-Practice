#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int cnt = t;
    while(t--){
        int L,R;
        cin>>L>>R;
        long long int minBal = (long long int) min(L,R);
        long long int maxBal = (minBal*(minBal+1))>>1;
        cout<<"Case #"<<(cnt-t)<<":"<<maxBal<<endl;
    }
    return 0;
}