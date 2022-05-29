#include <iostream>
#include <queue>
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int Top = 0; //물의 높이

int maps[103][103];
bool isused[103][103];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0}; //우 좌 하 상

bool Out(int x,int y){ // maps을 나갔나 안 나갔나 판단하는 함수
    if(x<0||y<0||x>=N||y>=N)
        return true;
    else return false;
}

void BFS(int x,int y){ //기본적인 BFS함수이다

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
            if(!Out(nx,ny)&&!isused[nx][ny]&&maps[nx][ny]>Top){ //그런데 여기에 조건을 첨가한...   조건은 물 높이보다 높을 때이다.
                isused[nx][ny] = true;
                Q.push(make_pair(nx,ny));
            }
        }
        
    }
    
    
}

int main(){
  
    int result = 0;
    int Top_max = 0;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> maps[i][j];
            Top_max = max(Top_max,maps[i][j]); // 물의 최대 높이
        }
    }

    for (int i = 0; i < Top_max; i++) // 물의 높이를 증가 시킨다.
    {
        int Number = 0; //안전영역의 수
        memset(isused,false,sizeof(isused)); // isused 초기화
        for (int j = 0; j < N; j++)
        {
            for (int z = 0; z < N; z++)
            {
                if(!isused[j][z]&&maps[j][z]>Top){ // maps를 돌면서 방문하지 않았으며 물의 잠기지 않은 안전영역에 BFS를 돌린다.
                    BFS(j,z);
                    Number++; // 안전영역 수 증가
                }
            }
        }
        result = max(result,Number); //안전영역의 최대값
        Top ++;
    }
    cout << result;
    

    return 0;
}
