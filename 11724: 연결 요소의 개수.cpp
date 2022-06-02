#include <iostream>
#include <vector>

using namespace std;

bool isused[1003];
int N,M;
vector <int> Vertex[1003]; // 그래프를 위한 vector

void DFS(int x){ // DFS를 이용하여 그래프 탐색

    isused[x] = true;
    for (int i = 0; i < Vertex[x].size(); i++) // 연결된 노드 탐색
    {
        int next = Vertex[x][i];
        if(!isused[next]){ // 방문하지 않았다면
            DFS(next);
        }
    }
    
}

int main(){
    int result =0;
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int to,end;
        cin >> to >> end;
        Vertex[to].push_back(end); // 방향없는 그래프이기 때문에 서로 연결
        Vertex[end].push_back(to);
    }
    for (int i = 1; i <= N; i++) // 탐색
    {
        if(!isused[i]){
            result ++;
            DFS(i);
        }
    }
    cout << result;

    return 0;
}
