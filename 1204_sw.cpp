#include <iostream>
#include <vector>
using namespace std;

int arr[101];   // 빈도 표기

int main(){
    int T;
    cin>>T;
    vector<int> ans;
    while(T>0){
        int num;
        cin>>num;
        for(int i=0;i<1000;i++){
            int n;
            cin>>n;
            arr[n]+=1;
        }
        int m=0;    // 숫자 저장
        int bin=0;  // 빈도 저장
        for(int i=0;i<=100;i++){
            if(arr[i]>=bin){
                m=i;
                bin=arr[i];
            }
        }
        ans.push_back(m);
        fill(arr,arr+101,0);
        T--;
    }
    for(int i=1;i<=ans.size();i++){
        cout<<"#"<<i<<" "<<ans[i-1]<<"\n";
    }
}