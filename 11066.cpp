#include <iostream>
#include <vector>
using namespace std;

// 20분



// 파일의 크기가 크면 합치는 비용 증가

// 40 30 30 50  
// 30 30            60 90 150

// 마지막 원소와 앞의 N-1개의 최솟값을 구해서 합하는 방식

// 모든 경우를 다 구해야함

// 이어진것만 더할수있음

// 일단 1 21 일때 무조건 1가지경우

// 1 21 3 이라고 하면 MIN(1 21 더한 최솟값+이후 최솟값 , 21 , 3 더한 최솟값 + 앞의 값)

// 1 21 3 4 라고 하면 (1 21 3 더한 최솟값 + 이후 값(4) , 1 21 더한 최솟값 +)

// start = 1 , end = 4

// k = 1,2,3..end-1

int arr[501];   //  숫자 배열 저장
int N;
int dp[501][501];   // 중간 최솟값들 계산하기

int S[501]; // 누적합 더하기

// 인덱스들의 총합 계산해주는 함수

void calculate(int start,int end){
    // 중간에 어디를 break 할것인가 정하기 
    if(end-start==1){
        dp[start][end]=arr[start]+arr[end];
        return;
    }
    int minn=2e9;
    for(int k=start;k<end;k++){ // break 지점
        int plus1=dp[start][k];
        int plus2=dp[k+1][end];
        int ans=plus1+plus2;
        minn=min(minn,ans+S[end]-S[start-1]);    // 비용추가
    }
    dp[start][end]=minn;
}
int main(){
    int T;
    cin>>T;
    vector<long long> answer;
    while(T--){
        cin>>N;
        for(int i=1;i<=N;i++){
            cin>>arr[i];    // 각각의 숫자의 비용은 자기자신이라고 두기
            dp[i][i]=0;     // 자기자신을 합칠순없으니
            S[i]=S[i-1]+arr[i];
        }
        // 숫자를 다 받았다면 계산해야지
        for(int j=1;j<N;j++){
            for(int i=1;i<=N-j;i++){
                calculate(i,i+j);
            }
        }
        answer.push_back(dp[1][N]);
    }
    for(int i=0;i<answer.size();i++){
        cout<<answer[i]<<"\n";
    }
}