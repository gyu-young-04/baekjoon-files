#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

// int = 2의 31승까지
// long long  =  2의 63승까지
int n;
int A[4001];
int B[4001];
int C[4001];
int D[4001];
//4000 4000
long long first[16000001];
long long second[16000001];
long long sum;

// 16000000
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    for(int i=1;i<=n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        A[i]=a;
        B[i]=b;
        C[i]=c;
        D[i]=d;
    }
    int t=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int k=A[i]+B[j];
            first[t]=k;
            t++;
        }
    }
    t=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int k=C[i]+D[j];
            second[t]=k;
            t++;
        }
    }
    // 둘 중 하나를 정렬한다 (탐색을 쉽게 하기 위해서)
    sort(first+1,first+n*n+1);  // 정렬
    // -100 -43 -4 0 1 46 47 79 
    for(int i=1;i<=n*n;i++){
        auto k=lower_bound(first+1,first+n*n+1,-second[i]);    // first 배열에서 저거보다 크거나 같은 첫 배열
        auto k2=upper_bound(first+1,first+n*n+1,-second[i]);
        sum+=(k2-k);    
        // k= 저 숫자보다 이상인 인덱스
        // k2= 저 숫자보다 초과인 인덱스

        // bound 함수의 경우 이분탐색이 구현된 STL 이다
    }
    cout<<sum;
}