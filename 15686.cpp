#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>
using namespace std;

// 집과 가장 가까운 치킨집 사이의 거리 - 치킨거리

// 도시의 치킨거리 = 모든 집의 치킨거리 합

// 일부 치킨집 없애려고함

// 치킨집 개수 최대 M개에서 수익을 많이 냄

// 어떻게 하면 치킨거리가 가장 작을까 

// M개가 아닌 작은 수로 최대가 되냐

// 결국 M개일때가 가장 작을것

int N,M;
int arr[51][51];

// M개를 선택 할때 마다 게산하기?

// 일단 처음에 가장 가까운 치킨집 구하는 계산을 하고 

// 치킨집 별로 가장 가까운 치킨집으로 선정한 집들을 모아두기

// M개를 선택하고 그 M개의 치킨집이 제일 가까운 집들은 방문표시를 해서 이미 게산해뒀음을 적용

// 가장 가까운 치킨집이 사라진 집의 경우 새로이 BFS로 새로운 치킨집까지의 거리 측정하기

// 선택하는 함수 DFS (매개변수로 남은 치킨집 수를 받는)

vector<int> near_chic[14];  // 인덱스는 치킨집 번호 ,치킨집이랑 가까운 집들 
pair<int,int> num_chic[14]; // 인덱스는 치킨집 번호 , 치킨집 정보 저장
pair<int,int> num_house[101]; // 인덱스는 집 번호, 집정보
int leng_near_chic[101];        // 인덱스는 집 번호
bool visit[51][51];
int num_ch=0;   // 치킨집 개수
int num_hou=0;  // 집 개수
int tmp_arr[51][51];
int min_leng=2e9;
bool visit_house[101]; // 집 계산이 됐는지

// 가장 가까운 치킨집까지 거리 구하는 함수
int bfs1(int x,int y,int num_h){
    queue<tuple<int,int,int>> q;    // (x좌표 y좌표 거리)
    memset(visit,false,sizeof(visit));
    int answer=0;
    q.push({x,y,0});
    int dx[4]={0,0,-1,1};
    int dy[4]={1,-1,0,0};
    while(!q.empty()){
        int nowx,nowy,leng;
        tie(nowx,nowy,leng)=q.front();
        q.pop();
        if(arr[nowx][nowy]==2){
            for(int i=1;i<=num_ch;i++){
                if(num_chic[i].first==nowx&&num_chic[i].second==nowy){
                    near_chic[i].push_back(num_h);
                }
            }
            answer=leng;
            break;
        }
        for(int i=0;i<4;i++){
            int nx=nowx+dx[i];
            int ny=nowy+dy[i];
            if(nx<=0||nx>N||ny<=0||ny>N)
                continue;
            if(visit[nx][ny]==true)
                continue;
            q.push({nx,ny,leng+1});
            visit[nx][ny]=true;
        }
    }
    return answer;
}
int bfs2(int x,int y,int num_h){
    queue<tuple<int,int,int>> q;    // (x좌표 y좌표 거리)
    memset(visit,false,sizeof(visit));
    int answer=0;
    q.push({x,y,0});
    int dx[4]={0,0,-1,1};
    int dy[4]={1,-1,0,0};
    visit[x][y]=true;
    while(!q.empty()){
        int nowx,nowy,leng;
        tie(nowx,nowy,leng)=q.front();
        q.pop();
        if(tmp_arr[nowx][nowy]!=0){
            answer=leng;
            break;
        }

        for(int i=0;i<4;i++){
            int nx=nowx+dx[i];
            int ny=nowy+dy[i];
            if(nx<=0||nx>N||ny<=0||ny>N)
                continue;
            if(visit[nx][ny]==true)
                continue;
            q.push({nx,ny,leng+1});
            visit[nx][ny]=true;
        }
    }
    return answer;
}

void sums_leng(){ // tmp_arr 에 있는 상태로 거리계산하기 (치킨집 번호로 저장됨)
    int sum=0;
    memset(visit_house,false,sizeof(visit_house));  // 방문기록 초기화
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            if(tmp_arr[i][j]!=0){
                int n=tmp_arr[i][j]; // 치킨집 번호
                for(int j=0;j<near_chic[n].size();j++){
                    int house_num=near_chic[n][j];
                    visit_house[house_num]=true;
                    sum+=leng_near_chic[house_num];
                }
            }
        }
    }
    // 살아있는 치킨집에서 가장 가까운거 계산됨
    for(int i=1;i<=num_hou;i++){    // 새로 계산해야하는것들
        if(visit_house[i]==false){
            int n=bfs2(num_house[i].first,num_house[i].second,i);
            sum+=n;
        }
    }
    min_leng=min(min_leng,sum);
}


void select(int num_c,int aware){ 
    if(num_c>num_ch)
        return; 
    int x=num_chic[num_c].first;
    int y=num_chic[num_c].second;
    tmp_arr[x][y]=num_c;
    if(aware<=0){
        sums_leng();
        tmp_arr[x][y]=0;    // 정하고 백트래킹
        return;
    }
    for(int i=num_c+1;i<=num_ch;i++){
        select(i,aware-1);
        tmp_arr[num_chic[i].first][num_chic[i].second]=0; //정할때 마다 백트래킹
    }
}


int main(){
    cin>>N>>M;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin>>arr[i][j];
            if(arr[i][j]==2){
                num_ch++;
                num_chic[num_ch]={i,j};
            }
            if(arr[i][j]==1){
                num_hou++;
                num_house[num_hou]={i,j};
            }
        }
    }
    // 가장 가까운 치킨집 처음 도출해두기
    for(int i=1;i<=num_hou;i++){
        int x=num_house[i].first;
        int y=num_house[i].second;
        leng_near_chic[i]=bfs1(x,y,i);     // i는 집 번호
    }
    // 치킨집이랑 가까운 집들 저장됨
    // 이제 치킨집 M개 골라야함
    for(int k=1;k<=num_ch-M+1;k++){
        memset(tmp_arr,0,sizeof(tmp_arr));
        // 다 했으면 tmp_arr로 진행한다
        select(k,M-1);
        tmp_arr[num_chic[k].first][num_chic[k].second]=0;  // 정하고 백트래킹
    }
    cout<<min_leng;
}