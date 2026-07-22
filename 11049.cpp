#include <iostream>
#include <vector>
using namespace std;


// 

// 

// 기존에 방식에서 찾았다고 해보자 

// 3개일때 1번

// 5 3 2 6 8 이라고 해보자

// 5 3 2 입력시 도출되는 방법 1개 (3이 사라지는)

// 5 3 2  에 6 들어오면 (3이 사라지는 기존 방법 + 마지막 숫자인 2가 사라지는 방법)

// 명심할 사실 추가된 숫자는 그 배열에서 사라지지않는다 결국 마지막에는 양옆이 처음과 끝이다

//  5 1 4 7 9 4 3 5     7 라고 하자 모든 숫자들 순서대로 저장했다고 치자

// 총 저장해야하는 개수? (N-2)! 개

// 한개가 추가되기 이전의 최적의 값이 도움이 되는가

// 결국 마지막에 남는건 첫 숫자와 중간 하나 그리고 추가된 숫자

// 추가된 숫자가 중간에 영향을 끼친다면?

// 뭐가 최적인지 모르기에 모든방식으로 수행한걸 저장해둘필요가있다

// 5 3 2 6 의 경우   532+526 // 326 + 536 과정 계산해둬야함

// 5 3 2 6 8 의 경우 532+526+568 // 532+

long long dp[501][501]; // 인덱스 순대로 계산할거임

// 일단 숫자를 받아서 3개의 인덱스 차이를 기본정보로서 미리 저장해두기

int arr[502];   // 숫자 배열 저장

int N;
int r,c;
long long answer=0;

// ABCDE 라고 할때   AB (CDE) ABC (DE)  인 총 2개 구하기

void calculate(int start,int end){  
    long long minn = 1e18;
    for(int k=start;k<end;k++){ //1 2
        minn=min(minn,dp[start][k]+dp[k+1][end]+arr[start]*arr[k+1]*arr[end+1]);
    }
    dp[start][end]=minn;
    return;
}

// 5 3 2 6  (1,3)

int main(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>r>>c;
        if(i==N){
            arr[i]=r;
            arr[i+1]=c;
        }
        else{
            arr[i]=r;
        }
        dp[i][i]=0;
    }

    // dp는 숫자기준이 아니라 행렬기준으로

    // 일단 숫자 3개일때의 값들을 저장해두기
    for(int j=1;j<=N;j++){
        for(int i=1;i<N-j+1;i++){
            calculate(i,i+j);   // 행렬기준으로 계산
        }
    }
    cout<<dp[1][N];
}
