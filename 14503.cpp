#include <iostream>
#include <vector>
using namespace std;


int N,M;

int r,c;

int d;

// 벽 or 빈칸

// 좌표 (r,c)

// 0부터시작

// (N,M) 

// 처음 빈칸들은 청소가 안되어있음

// 청소 x -> 청소함

// 주변 4칸 청소가 모두 되거나 벽인경우  (바라보는 방향 후진 , 후진 안되면 종료)

// 청소 안된 빈칸 존재시 반시계 순으로 하나씩 탐색하며 안된쪽으로 전진

// 로봇 청소기 청소에는 결국 하나의 루트만 존재함

// 방문기록 하나만 있으면 됨 (청소했는가 안했는가)
int arr[51][51];    // 맵 바꿀필요 없음
bool visit[51][51]; // 방문기록 초기에 false 
int sum=0;

void rotate(){  // d의 값 변동하는
    if(d>0){        // 3 2 1 0 3 2 1 0 
        d-=1;
        return;
    }
    if(d==0){
        d=3;
        return;
    } 
}

void move(){        // 이동한 다음 행동양식 함수
    if(visit[r][c]==false){
        sum++;
        visit[r][c]=true;
    }
    int dx[4]={-1,0,1,0};
    int dy[4]={0,1,0,-1};
    for(int i=0;i<4;i++){
        rotate();
        int nx=r+dx[d]; 
        int ny=c+dy[d];
        if(nx<0||nx>=N||ny<0||ny>=M)
            continue;
        if(visit[nx][ny]==false&&arr[nx][ny]==0){
            r=nx;
            c=ny;
            move();
            return;
        }
    }
    // 4칸 모두 청소안된 빈칸이 없었다
    int nx=r-dx[d]; 
    int ny=c-dy[d];
    if(arr[nx][ny]==0){
        r=nx;
        c=ny;
        move();
        return;
    }
    else{
        return;
    }
}
int main(){
    cin>>N>>M; 
    cin>>r>>c;  // 로봇청소기 좌표
    cin>>d;     // 0 북   1 동   2 남   3 서
    // 바라보는 방향의 변동은  3 2 1 0 3 순으로 (반시계방향)
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>arr[i][j];
        }
    }
    move();
    cout<<sum;
}