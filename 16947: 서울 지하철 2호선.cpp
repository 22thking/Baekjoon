#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N;
bool cycle[3003];
int pre[3003];
int isused[3003];
queue <int> BFS_cycle;
vector <int> Vertex[3003];
int dist[3003];
bool iscycle = false;

void Find_cycle(int x){ // 사이클 찾기!
    isused[x] = true;
    for (int i = 0; i < Vertex[x].size(); i++)
    {
        if(iscycle)
            return;
        int next = Vertex[x][i];
        if(isused[next]){ // 방문했었는데
            if(pre[x]!=next){ // 다음 그래프가 부모 그래프가 아닐 경우 사이클
                cycle[x] = true;
                iscycle = true;
                while (next!=x)
                {
                    cycle[pre[x]] = true;
                    x = pre[x];
                }
                return;
            }
            
        } else {
            pre[next] = x;
            Find_cycle(next);
        }
    }
}

void BFS(){ // 사이클에서 BFS 돌리기
    for (int i = 1; i <= N; i++)
    {
        if(cycle[i]){
            isused[i] = true;
            BFS_cycle.push(i);
            dist[i] = 0;
        }
    }

    while (!BFS_cycle.empty())
    {  
        int X = BFS_cycle.front();
        //cout << X;
        int d = dist[X];
        BFS_cycle.pop();
        isused[X] = true;

        for (int i = 0; i < Vertex[X].size(); i++)
        {
            int nx = Vertex[X][i];
            if(!isused[nx]){
                dist[nx] = d +1;
                BFS_cycle.push(nx);
            }
        }
        
    }
}

int main(){
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int to,end;
        cin >> to >> end;
        Vertex[to].push_back(end);
        Vertex[end].push_back(to);
    }
    Find_cycle(1);
    memset(isused,false,sizeof(isused));
    BFS();
    for (int i = 1; i <= N; i++)
    {
        cout << dist[i] << ' ';
    }
    

    return 0;
}
