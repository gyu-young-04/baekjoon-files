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
    sort(second+1,second+n*n+1,greater<long long>());   // 내림차순
    // 99 43 4 0 -1 -48 49 -91
    int index_f=1,index_s=1;
    while(true){
        if(index_f>n*n||index_s>n*n)
            break;
        if(-first[index_f]>second[index_s]){    //  숫자가 더 크니 없다
            index_f++;
            continue;
        }
        if(-first[index_f]<second[index_s]){    //  숫자가 더 크니 없다
            index_s++;
            continue;
        }
        int num=first[index_f];
        long long n1=0,n2=0;
        while(index_f<=n*n&&first[index_f]==num){
            index_f++;
            n1++;
        }
        while(index_s<=n*n&&second[index_s]==-num){
            index_s++;
            n2++;
        }
        sum+=n1*n2;
    }
    cout<<sum;
}