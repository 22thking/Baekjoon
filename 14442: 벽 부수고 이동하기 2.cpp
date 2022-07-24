#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int maps[1003][1003];
int N,M,K;
bool isused[1003][1003][10]; // K번까지 벽을 뚫을 수 있음으로 방문 배열을 3차원 배열으로 정의 (K <= 10)
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

bool Out(int x,int y){ //못 나가지
    if(x<0||y<0||x>=N||y>=M)
        return true;
    else return false;
}

int BFS(){
    queue <pair<pair<int,int>,pair<int,int>>> Q; //X Y cnt block
    Q.push(make_pair(make_pair(0,0),make_pair(1,0)));
    isused[0][0][0] = true;

    while (!Q.empty())
    {
        int X = Q.front().first.first;
        int Y = Q.front().first.second;
        int cnt = Q.front().second.first; // 움직인 횟수
        int block = Q.front().second.second; // 벽을 뚫은 횟수
        Q.pop();

        if(X==N-1&&Y==M-1) // 목적지에 도착했을 때
            return cnt;

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];

            if(Out(nx,ny))
                continue;
            if(maps[nx][ny]==1&&block<K&&!isused[nx][ny][block + 1]){ // 벽을 뚫을 수 있을 때
                isused[nx][ny][block + 1] = true;
                Q.push(make_pair(make_pair(nx,ny),make_pair(cnt + 1,block + 1)));
            } else if(maps[nx][ny]==0&&!isused[nx][ny][block]){ // 벽이 아닌 곳
                isused[nx][ny][block] = true;
                Q.push(make_pair(make_pair(nx,ny),make_pair(cnt + 1,block)));
            }
        }
    }
    // while문을 그냥 빠져나왔다는 것은 목적지에 닿지 않았다는 것이다.
    return -1;
}

int main(){
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
    {
        string get;
        cin >> get;
        for (int j = 0; j < M; j++)
        {
            if(get[j]=='0')
                maps[i][j] = 0;
            else maps[i][j] = 1;
        }
    }
    int result = BFS();

    cout << result;
    
    return 0;
}
