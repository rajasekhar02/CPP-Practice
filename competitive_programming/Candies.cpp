#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int cnt = t;
    while(t--){
        int output = 0;
        int input;
        int childs,N;
        cin>>N>>childs;
        for(int i=0;i<N;i++){
            cin>>input;
            output += input%childs;
        }
        cout<<"Case #"<<(cnt-t)<<": "<<(output%childs)<<endl;
    }
    return 0;
}