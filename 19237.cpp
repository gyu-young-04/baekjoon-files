#include <iostream>
#include <vector>
using namespace std;


// 7시 15분

// 상어 번호 1~M
// 1이 제일 강력

// 상어가 자신의 위치에서 냄새를 뿌리고
// 1초마다 이동 후 냄새뿌리기 반복 (상하좌우)

// 냄새는 K번 이동하면 사라진다라고 하는데
// 배열에 냄새남은시간까지 저장하기엔..

// 이동 우선순위 - 냄새가 없는,자신의 냄새,

// 처음 보고있는 방향은 입력으로
// 이동하고나서는 방향변동 없음
// 다음 이동에서 변동일어남

// 모든 상어가 이동하고 같은곳 상어는 없어진다

// 우선순위의 경우 현재 어디를 바라보는가에 따라

// 저장해야할것 

// 상어별로 우선순위 설정
// 각 상어별 저장해야하는것 - 우선순위 , 현재방향
// 냄새가 없는게 존재 - 우선순위대로
// 냄새가 없는게 없음 - 본인의 냄새가 묻은

// 냄새를 어케 저장할것인가
// 시간이 지남에 따라 남은시간을 매번 없앨것인가

// 냄새 저장된 곳에 대한 정보 저장 unordered_set 
// set 순회해서 냄새가 0이 되면 퇴출
// 현재 상어의 방향 저장 

pair<int,int> smells[21][21];   // (시간,번호)
int arr[21][21];    // 배열 (상어 위치 저장)
int look_sharks[401];   // 상어가 어디를 보고있는가
int next_station[401];  // 다음에 어디로 이동할것인가
int tmp_arr[21][21];    // 다음상황 저장

// 번호 현재 보는곳 우선순위(4개)

int priority_sharks[401][5][5]; //(번호,현재보는,우선순위)

// 순차적으로 하나씩 이동시키면 오류발생가능성존재
// 이동시키지 말고 어디로 이동할지 결정만 하고
// 전부다 돌고 나서 이동
int N,M,k;

bool is_only_no1(){
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(arr[i][j]>1)
                return false;
        }
    }
    return true;
}
void next_move(int x,int y){
    int num=arr[x][y];      // 상어 번호
    int see_shark=look_sharks[num]; // 어딜 보고있는지
    int dx[5]={0,-1,1,0,0};
    int dy[5]={0,0,0,-1,1};
    // 냄새가 없는게 존재하는지 파악 - 우선순위대로
    bool blank=false;
    for(int i=1;i<5;i++){   // 상어의 우선순위 설정
        int k=priority_sharks[num][see_shark][i];  // 우선순위상 번호
        int nx=x+dx[k];
        int ny=y+dy[k];
        if(nx<=0||nx>N||ny<=0||ny>N)
            continue;
        if(smells[nx][ny].first==0&&smells[nx][ny].second==0){
            look_sharks[num]=k;
            next_station[num]=k;
            blank=true;
            break;
        }
    }
    if(blank==false){
        for(int i=1;i<5;i++){   // 상어의 우선순위 설정
            int k=priority_sharks[num][look_sharks[num]][i];  // 우선순위상 번호
            int nx=x+dx[k];
            int ny=y+dy[k];
            if(nx<=0||nx>N||ny<=0||ny>N)
                continue;
            if(smells[nx][ny].second==num){
                look_sharks[num]=k;
                next_station[num]=k;
                break;
            }
        }
    }

    return;
}

void real_move(int x,int y){
    int num=arr[x][y];
    int nxt=next_station[num];
    int dx[5]={0,-1,1,0,0};
    int dy[5]={0,0,0,-1,1};
    int nx=x+dx[nxt];
    int ny=y+dy[nxt];
    if(tmp_arr[nx][ny]==0||tmp_arr[nx][ny]>num){        // 이동할 위치의 값(상어) 보다 더 크다면
        tmp_arr[nx][ny]=num;
    }

    // 이동했으니 냄새 추가
}

int main(){
    cin>>N>>M>>k;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin>>arr[i][j];
            if(arr[i][j]!=0)
                smells[i][j]={k,arr[i][j]};
        }
    }
    // 냄새 저장 완료
    // 상어의 현재 위치 저장 완료
    for(int i=1;i<=M;i++){
        cin>>look_sharks[i];
    }
    for(int i=1;i<=M;i++){
        for(int j=1;j<5;j++){
            for(int k=1;k<5;k++){
                cin>>priority_sharks[i][j][k];
            }
        }
    }
    // 상어 우선순위 저장
    int time=1;
    while(time<=1000){
        // 다음으로 상어의 움직일 위치를 정하자
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(arr[i][j]!=0){
                    next_move(i,j);
                }
            }
        }
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(smells[i][j].first>1){
                    smells[i][j].first--;
                }
                else if(smells[i][j].first==1){
                    smells[i][j].first=0;
                    smells[i][j].second=0;
                }
            }
        }
        for(int i=1; i<=N; i++) {
            for(int j=1; j<=N; j++) {
                tmp_arr[i][j] = 0;
            }
        }
    // 이동할 위치를 다 정했으면 한번에 이동한다
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                    if(arr[i][j]!=0){
                        real_move(i,j);
                    }
            }
        }
        for(int i=1; i<=N; i++) {
            for(int j=1; j<=N; j++) {
                arr[i][j] = tmp_arr[i][j];
            }
        }
        if(is_only_no1()==true){
            break;
        }

        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                    if(arr[i][j]!=0)
                        smells[i][j]={k,arr[i][j]};
            }
        }
        // 냄새 추가하기

        time++;
    }
    if(time>1000)
        cout<<-1<<"\n";
    else    
        cout<<time<<"\n";
}

// 동시에 이동할때는 맵을 복사해야한다 아니면 오류가 덮어씌일수있다
// 우로 이동할때는 내가 짠 코드가 오류를 만들어낸다
// 새로 맵을 만들어서 하는게 좋다