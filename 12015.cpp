#include <iostream>
#include <vector>
using namespace std;

// 백만개의 숫자가 주어진다
int N;

// 10 입력 시 

// 

// 10 20 10 30 11 12 13 14

// 숫자가 들어올때마다 배열을 만들어내자

// 만약 현재 최대길이의 배열의 최댓값인 
// 마지막 숫자보다 작은게 들어오면
// lower_bound 이용해서 구하기
int main(){
    vector<int> v;  // 배열 저장
    v.push_back(0); // 일단 기본값 저장
    cin>>N;
    int num;
    for(int i=1;i<=N;i++){
        cin>>num;
        if(*v.rbegin()<num){
            v.push_back(num);
        }
        else{
            auto a=lower_bound(v.begin(),v.end(),num);
            *a=num;
        }
    }
    cout<<v.size()-1;
}