#include<bits/stdc++.h>
using namespace std;
int main(){
    /*
    let l = 100;
    let offset = 15;
    let number = Number.parseInt('10101',2);
    let numbers = new Array(l).fill(1).map((_,index)=>index+1).map(y=>[y-offset>0?y-offset:1, y+offset < l ? y+offset:l]).map((arrValues)=>{
        return Number(((1<<(arrValues[1]-arrValues[0]+1))-1)<<(arrValues[0]-1))
    }).reverse()

    let queue = [[number,0]];

    while(queue.length != 0){
        let val = queue.shift();
        if(val[0] == 0){
            console.log(val[1]);
            break;
        }
        for(let i=0;i<numbers.length;i++){
            queue.push([val[0]^numbers[i], val[1]+1]);
        }
    }
    */
    // int t;
    // cin>>t;
    // while(t--){
    //     int len, winSize;
    //     cin>>len>>winSize;
    //     vector<int> switches(len,0);
    //     if(winSize>=len){
    //         cout<<"impossible"<<endl;
    //         continue;
    //     }
    //     for(int i=0;i<len;i++){
    //         cin>>switches[i];
    //     }
        
    // }
    vector<int>  offsetValues = {120, 124, 126, 127, 63, 31, 15};
    int x = 112;
    int flag = 0;
    deque< pair<int,int> > qu;
    qu.push_front(make_pair(x,0));
    int min_rounds = 1e9+7;
    while(!qu.empty()){
        pair<int,int> val = qu.back();
        qu.pop_back();
        if(val.first == 0){
            cout<<val.second<<endl;
            flag = 1;
           break;
        }
        for(int i=0;i<offsetValues.size();i++){
            qu.push_front(make_pair(val.first^offsetValues[i],val.second+1));
        }
    }
    if(flag == 0){
        cout<<"impossible"<<endl;
    }
    return 0;
}