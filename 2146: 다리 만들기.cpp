#include <iostream>
#include <queue>
#include <vector> 
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int maps[103][103];
int iceberg[103][103]; // 그 대륙이 빙산인 줄 알았던 나는 그냥 빙산이라고 변수명을 지었따!
int now_number = 1; // 빙산을 구별하기 위한 수
bool isused[103][103]; // 빙산을 구별하기 위한 배열
int visited[103][103]; // 이건 다리 길이 구하기 위한 배열
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

vector <pair<int,int>> V; // 빙산(대륙)을 추가하기 위한 벡터이다.

bool Out(int x,int y){ // 나갔나?
    if(x<0||y<0||x>=N||y>=N)
        return true;
    else return false;
}

void BFS(int x,int y){ // 빙산을 구별하기 위한 첫번째 BFS이다.
    queue <pair<int,int>> Q;
    isused[x][y] = true;
    Q.push(make_pair(x,y));
    V.push_back(make_pair(x,y));
    iceberg[x][y] = now_number; // 구별하기 위해 빙산 숫자 추가

    while (!Q.empty())
    {
        int X = Q.front().first;
        int Y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(!Out(nx,ny)&&!isused[nx][ny]&&maps[nx][ny]==1){
                isused[nx][ny] = true;
                iceberg[nx][ny] = now_number; //이것도
                Q.push(make_pair(nx,ny));
                V.push_back(make_pair(nx,ny)); // 빙산을 좌표를 추가해서 다리를 채우기 위함이다.
            }
        }
    } 
}

int Short_BFS(int x,int y){ // 가장 짧을 다리를 구하기 위한 두번째 BFS
    memset(visited,-1,sizeof(visited)); // visited는 새로 갱신해준다. 
    visited[x][y] = 0;
    int now_ice = iceberg[x][y]; // 현재 어느 빙산을 탐색하는지 알아야 함
    queue <pair<int,int>> Q;
    Q.push(make_pair(x,y));

    while (!Q.empty())
    {
        int X = Q.front().first;
        int Y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(!Out(nx,ny)&&visited[nx][ny]== -1&&iceberg[nx][ny]!=now_ice){ // 밖으로 나가지 않고 방문하지 않았으며 같은 빙산이 아닐 때
                if(iceberg[nx][ny]!=0&&iceberg[nx][ny]!=now_ice){ // 바다가 아니면서 같은 빙산이 아닌 경우
                    return visited[X][Y]; // 이 방문한 곳이 다른 대륙임으로 현재 다리 값을 리턴해준다.
                }
                visited[nx][ny] = visited[X][Y] +1; // 거리 더하기
                Q.push(make_pair(nx,ny));
            }
        }
    }
    return 987654321; // 그냥 빠져나갔을 경우 서로 다른 빙산을 마주친 경우가 아님으로 max 값을 리턴해준다.
}

int main(){
    int result = 987654321;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> maps[i][j];
        }
    }
    for (int i = 0; i < N; i++) // 탐색하면서 대륙의 빙산을 구분해준다.
    {
        for (int j = 0; j < N; j++)
        {
            if(!isused[i][j]&&maps[i][j]==1){ 
                BFS(i,j);
                now_number++;
            }
        }
    }
    for (int i = 0; i < V.size(); i++) // 모든 빙산을 탐색하면서 최소 다리 길이를 찾는다.
    {
        int X = V[i].first;
        int Y = V[i].second;
        result = min(result,Short_BFS(X,Y)); //가장 낮은 값이 답
    }
    
    // 주석을 풀면 구분된 빙산 값이 나온다.
    // cout << '\n';
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         cout << iceberg[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    cout << result;

    return 0;
}
