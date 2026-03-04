#include <iostream>
using namespace std;

int NUM=1000000007;

// int는 10억 7의 수를 처리가능

// 이항계수를 여러개의 합으로 쪼개자 

// 그리고 여러개의 합들이 만약 10억 7을 넘긴다면

// 그 수를 빼자

// 30=10+20 이때 7로 나눈 나머지는 

// 10과 20을 7로나눈 나머지의 합들로 간단히 표현가능

//30%7 = 3+6 =9%7

// 30 = 10+20

// 결론적으로 이항계수를 여러개의 합으로 거슬러 올라가며 합할껀데 

// 만약 10억 7을 넘는 결과가 나오면 나머지의 값을 도출시키자

// 재귀를 활용하게 되면 중복된 계산이 끝도없이 이어진다

//dp의 경우도 숫자가 5000보다 작을때 사용한다 왜냐하면 O(N제곱)의 시간복잡도를 가지기에 

// 여기서 사용불가 (컴퓨터는 1초에 1억번 연산한다고 생각 1억은 10의 8승)

// 이처럼 N이 400만이 넘어가면 O(N)의 시간복잡도를 가지게 하는게 더 좋다

// 메모리 계산 시에 int는 4바이트

// 1KB = 1024 BYTES =256개의 int
// 1MB = 256*1024개 int
// 256MB = 256*256*1024개 int 의 메모리 공간 차지

// 대략 6700만개의 int 저장가능

// 2차원의 경우 arr[8000][8000] 정도가 최대라고 보면된다

// 페르마의 소정리로 문제 해결해야한다네 (뭐지..)

// 팩토리얼 n!=(n-1)!*n 

// nCr 의 경우 n!/((n-r)!*r!) 로 이루어 지는데 나눗셈에서는 나머지의 값이

// 분배법칙이 적용되지 않는다

// 5*13 라고 할때 3으로 나눈 나머지 = (2+3)(1+12) 이니 2*1 을 3으로 나눈 나머지와 같다

// 따라서 나눗셈으로 정의 된 조합을 곱셈으로 바꿔줄 필요가 있다

// 소수로 나누었을때 특별한 이유는 결국 나머지가 0이 되지 않는다는것에 있다

// (n-r)!을 나누는 대신 (n-r)!에 해당하는 값을 p-2번 거듭제곱 한 값을 곱해주자

// 거듭제곱을 NUM으로 나누었을때의 나머지를 구하는 함수

long long power1(long long base,int exp){
    if(exp==1){
        return base%NUM;
    }
    if(exp%2==1){
        long long a=(base*base)%NUM;
        return (base*power1(a,(exp-1)/2))%NUM;
    }
    else {
        long long b=(base*base)%NUM;
        return power1(b,exp/2);
    } 
}

void my_code(){
    int N,K;
    cin>>N>>K;
    // 실제로 팩토리얼값을 배열에 저장하면 메모리 초과가 걸리기에
    // 나누는 값인 10억+7로 나눈 나머지를 저장하자
    long long factorial[4000001];
    for(int i=0;i<=N;i++){
        if(i<=1)
            factorial[i]=1;
        else{
            factorial[i]=(i*factorial[i-1])%NUM;
        }
    }

    // 여기서 n!과 (n-r)! , r! 의 값이 필요함

    // 3!을 나누는 대신 3!의 값을 p-2번 거듭제곱한 값을 곱하자

    int num1=factorial[N-K];
    int num2=factorial[K];

    long long num3=(num1*num2)%NUM;

    // num1과 num2를 각각 10억번정도 거듭제곱을 해야하기에 
    // 이걸 나눠서 곱해줘야한다
    long long answer=factorial[N]*((power1(num3,NUM-2)%NUM))%NUM;
    cout<<answer;
}

// 내가 필요한 값은 N!과 (N-K)! ,K! 이다 배열을 사용해서 팩토리얼들을 모두 저장할 필요 없다

long long power2(long long base,int exp){
    long long answer=1;

    // 비트연산으로 거듭제곱 계산하기?

    // 10의 31제곱이라고 하자 그러면..31은 11111로 표시된다
    while(exp>0){
        int a=exp&1;    // 만약 1이라면 10의 2의 0승을 처리
        if(a==1)
            answer=(answer*base)%NUM;
        exp=exp>>1;
        base=(base*base)%NUM;
    }
    return answer; 
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N,K;
    cin>>N>>K;
    // 실제로 팩토리얼값을 배열에 저장하면 메모리 초과가 걸리기에
    // 나누는 값인 10억+7로 나눈 나머지를 저장하자

    // 여기서 n!과 (n-r)! , r! 의 값이 필요함

    // 3!을 나누는 대신 3!의 값을 p-2번 거듭제곱한 값을 곱하자
    long long num1=1,num2=1,num3=1;
    long long factorial = 1;
    for (int i = 1; i <= N; i++) {
        factorial = (factorial * i) % NUM;
        if (i == K) num3 = factorial;
        if (i == N - K) num2 = factorial;
        if (i == N) num1 = factorial;
    }

    long long sum=(num2*num3)%NUM;
    // num1과 num2를 각각 10억번정도 거듭제곱을 해야하기에 
    // 이걸 나눠서 곱해줘야한다
    long long answer=num1*((power2(sum,NUM-2)%NUM))%NUM;
    cout<<answer;
}

