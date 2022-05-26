#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int isused[20003];
int V,E;
vector <int> Vertex[20003];

void DFS(int x){ //DFS
    if(isused[x]==0) // 방문하지 않았을 시 2로 방문 표시한다.
        isused[x] = 2;
    
    for (int i = 0; i < Vertex[x].size(); i++) //연결되어 잇는 노드를 찾아 방문
    {
        int index = Vertex[x][i];
        if(isused[index]==0){
            if(isused[x]==2) // 현재 노드가 2일 경우
                isused[index] = 3; // 다음 노드를 3으로 체크
            else if(isused[x]==3){ // 3인 경우
                isused[index] = 2; // 2로 체크
            }
            DFS(index); // 다음 노드로 DFS
        }
    }
}

bool check_same(){ // 모든 노드를 방문하며 현재 노드와 다음 노드가 같을 경우 true 값을 반환하는 함수이다.
    for (int i = 1; i <= V; i++)
    {
        for (int j = 0; j < Vertex[i].size(); j++)
        {
            int index = Vertex[i][j];
            if(isused[i]==isused[index]){ //현재 노드와 다음 노드의 값이 같을 경우 이분 그래프의 조건을 위반함
                return true; // true 값 반환
            }
        }
    }
    return false; // 이분 그래프 조건 성립
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int K;
    cin >> K;
    while (K-->0)
    {   
        cin >> V >> E;
        memset(isused,0,sizeof(isused));
        memset(Vertex, 0, sizeof(Vertex));
        for (int i = 0; i < E; i++)
        {
            int u,v;
            cin >> u >> v;
            Vertex[u].push_back(v);
            Vertex[v].push_back(u);
        }
        for (int i = 1; i <= V; i++)
        {
            if(!isused[i])
                DFS(i); // 모든 노드의 대해서 DFS() 실행
        }
        if(check_same()) // 함수 실행해서 이분 그래프 여부 파악
            cout << "NO" << '\n';
        else cout << "YES" << '\n';
        
    }
    

    return 0;
}
