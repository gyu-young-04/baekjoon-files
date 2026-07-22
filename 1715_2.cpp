#include <iostream>
#include <queue>
using namespace std;


int main(){
    int N;
    cin>>N;
    int sum=0;
    priority_queue<int,vector<int>,greater<int>> pq;     //pq는 숫자높은게 기본적으로 우선순위가 높다
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        pq.push(a);
    }
    while(pq.size()>1){
        int num1=pq.top();
        pq.pop();
        int num2=pq.top();
        pq.pop();
        sum+=num1+num2;
        pq.push(num1+num2);
    }
    cout<<sum;
    return 0;
}