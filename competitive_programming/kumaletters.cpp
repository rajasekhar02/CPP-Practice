#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cin.ignore();
    while(n--){
        string str;
        vector<int> a(26);
        getline(cin, str);
        for(int i=0;i<str.size();i++){
            a[tolower(str[i])-'a']++;
        }
        string outstr = "";
        for(int i=0;i<26;i++){
            if(a[i] == 0){
                outstr += (char) ((int)'a'+i);
            }
        }
        if(outstr.size()>0){
            cout<<"missing "<<outstr<<endl;
        }else{
            cout<<"pangram"<<endl;
        }

    }
    return 0;
}