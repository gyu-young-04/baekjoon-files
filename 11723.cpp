#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int M;
int aware[21];  // 존재성 파악


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>M;
    int num;
    for(int i=1;i<=M;i++){
        cin>>s;
        if(s=="all"){
            fill(aware,aware+21,1);
            continue;
        }
        if(s=="empty"){
            memset(aware,0,sizeof(aware));
            continue;
        }
        cin>>num;
        if(s=="add"){
            aware[num]=1;
            continue;
        }
        if(s=="remove"){
            aware[num]=0;
            continue;
        }
        if(s=="check"){
            cout<<aware[num]<<"\n";
            continue;
        }
        if(s=="toggle"){
            aware[num]=(aware[num]+1)&1;
            continue;
        }
    }
}