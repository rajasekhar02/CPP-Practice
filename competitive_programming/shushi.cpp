#include<bits/stdc++.h>
using namespace std;
int main(){
 int t;
 cin>>t;
 while(t--){
     int innerPN;
     cin>>innerPN;
     vector<pair<double,double>> innerPolygonVertices(innerPN);
     for(int i=0;i<innerPN;i++){
         double x,y;
         cin>>x>>y;
         innerPolygonVertices.push_back(make_pair(x,y));
     }
     int outterPN;
     cin>>outterPN;
     vector<pair<double,double>> outterPolygonVertices(innerPN);
     for(int i=0;i<innerPN;i++){
         double x,y;
         cin>>x>>y;
         outterPolygonVertices.push_back(make_pair(x,y));
     }
    
 }
    return 0;
}