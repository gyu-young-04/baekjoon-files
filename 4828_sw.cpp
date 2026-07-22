#include <iostream>
#include <vector>
using namespace std;

// set - 중복이 허용이 안되는 숫자들의 집합(정렬됨)
// multiset - 중복이 허용된 set
// unordered_set - 정렬이 안되는 것

// map 내용을 통째로 vector<pair<>>로 뽑아서 sort()로 정렬하는 방식을 자주씀
// vector<pair<int,int>> v; 처럼 사용하여서 정렬하기도 함

/*

만약 .first는 오름차순인데 .second는 내림차순처럼 
방향을 다르게 하고 싶으면 기본 비교로는 안 되고, 
아까처럼 람다로 직접 비교 기준을 짜야 합니다

sort(v.begin(), v.end(), [](auto&a, auto&b){
    if(a.first != b.first) return a.first < b.first;   // first 오름차순
    return a.second > b.second;                          // second 내림차순
});

*/


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin>>T;
    vector<int> ans;
    while(T--){
        int N;
        cin>>N;
        int maxx=0;
        int minn=2e8;
        for(int i=0;i<N;i++){
            int a;
            cin>>a;
            if(maxx<a)
                maxx=a;
            if(minn>a)
                minn=a;
        }
        ans.push_back(maxx-minn);
    }

    for(int i=1;i<=ans.size();i++){
        cout<<"#"<<i<<" "<<ans[i-1]<<"\n";
    }
    return 0;

}