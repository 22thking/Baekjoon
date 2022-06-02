#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

int N,K;
int maps[203][203];
int isused[203][203];
int S,X,Y;

int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};

bool Out(int x,int y){ // 나감?
    if(x<0||y<0||x>=N||y>=N)
        return true;
    else return false;
}

vector <pair<int,int>> V[1003]; // 순서대로 queue의 추가하기 위

void BFS(){ // 기본적인 BFS 구조를 가지고 있지만 조금 다르다
    memset(isused,-1,sizeof(isused));
    queue <pair<int,pair<int,int>>> Q;
    for (int i = 1; i <= K; i++) // 1번 바이러스부터 추가를 해준다.
    {
        for (int j = 0; j < V[i].size(); j++) // 처음 입력 받는 바이러스가 하나가 아닐 수도 있기 때문에 이렇게 했다.
        {
            int X = V[i][j].first;
            int Y = V[i][j].second;
            isused[X][Y] = 0;
            Q.push(make_pair(i,make_pair(X,Y)));
        }
    }

    while (!Q.empty())
    {
        int X = Q.front().second.first;
        int Y = Q.front().second.second;
        int number = Q.front().first;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(maps[nx][ny]==0&&!Out(nx,ny)&&isused[nx][ny]==-1){ // BFS가 돌아가는 방법은 기본과 같다.
                isused[nx][ny] = isused[X][Y] + 1;
                maps[nx][ny] = number; // 그런데 map 에다가 바이러스를 추가시킨다.
                Q.push(make_pair(number,make_pair(nx,ny)));
            }
        }
    }
}

int main(){
  
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> maps[i][j];
            if(maps[i][j]!=0){
                V[maps[i][j]].push_back(make_pair(i,j)); // 바이러스 추가
            }
        }
    }
    cin >> S >> X >> Y;

    BFS();

    if(isused[X-1][Y-1]<=S){ // 이부분이 포인트이다. 원하는 시간보다 많으면 0을 출력하고 아니면 바이러스 값을 출력한다.
        cout << maps[X-1][Y-1]; // 방문을 하지 않았어도 0을 출력한다.
    }else cout << 0;
    
    return 0;
}
