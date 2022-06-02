#include <iostream>
#include <queue>

using namespace std;
int M,N;
int maps[1002][1002] ={0};
int dx[4] = {1,0,-1,0}; //우 하 좌 상
int dy[4] = {0,1,0,-1};

bool Out_of_Maps(int x,int y){ // 나갔나?
    if (x < 0 || x >= N || y < 0 || y >= M)
      return true;
    else return false;
}

int main(){
    queue <pair<int,int>> Q; //BFS를 위한 queue
    queue <int> Q2;
    
    cin >> M >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> maps[i][j];

            if(maps[i][j]==1){
                Q.push(make_pair(i,j)); // 좌표 넣어주기
                Q2.push(1);
            }
        }
    }

    int result = 0; // 나는 왜 이전에 풀었을 때 BFS를 main 문 안에다가 했는지 이해를 못하겠다.
    int now_front = Q2.front();
    while(!Q.empty()){
        
        if(now_front !=Q2.front()){ // 그냥 가장 큰 값을 찾으면 될 것을 왜 이렇게 했을까?
            now_front = Q2.front();
            result ++;
        }
        int X = Q.front().first;
        int Y = Q.front().second;
        Q.pop();
        Q2.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if (!Out_of_Maps(nx,ny)&&maps[nx][ny]==0)
            {
                maps[nx][ny] = maps[X][Y] + 1;
                Q.push(make_pair(nx,ny));
                Q2.push(maps[X][Y] + 1);
            } 
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {

            if(maps[i][j]==0){
                result = -1;
            }
        }
    }
    
    cout << result << ' ';
    

    return 0;
}
