#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int K,W,H;
int hx[8] = {1,2,2,1,-1,-2,-2,-1}; // 말이 되어버린 원숭이 움직임 
int hy[8] = {-2,-1,1,2,2,1,-1,-2}; 
int dx[4] = {0,0,1,-1}; // 고냥 원숭이
int dy[4] = {1,-1,0,0};
int maps[203][203];
bool isused[203][203][40]; // 3차원 배열이 된 이유는 원숭이가 가는 길이 반복될 수 있기 때문이다.

bool Out(int x,int y){ // maps 밖으로 나갔나 안 나갔나?
    if(x<0||y<0||x>=H||y>=W)
        return true;
    else return false;
}

int BFS(){
    queue <pair<pair<int,int>,pair<int,int>>> Q; // queue는 4개의 값을 담는다.
    isused[0][0][0] = true;
    Q.push(make_pair(make_pair(0,0),make_pair(0,0))); // 말이 된 횟수  현재 움직인 수  x좌표 y좌표

    while (!Q.empty())
    {
        int horse = Q.front().first.first;
        int now_number = Q.front().first.second;
        int X = Q.front().second.first;
        int Y = Q.front().second.second;
        //cout << X << ' ' << Y << '\n';
        Q.pop();

        if(X==H-1&&Y==W-1){ // 정답 위치에 왔음 -> 현재 움직인 수를 출력한다.
            cout << now_number;
            return 1;
        }
        
        if(horse < K){ // 입력 값으로 주어진 수보다 말이 된 횟수가 낮을 경우
            for (int i = 0; i < 8; i++) //말이 된다.
            {
                int nx = X + hx[i];
                int ny = Y + hy[i];
                if(!Out(nx,ny)&&maps[nx][ny]!=1&&!isused[nx][ny][horse +1]){ // 말이 된 경우 움직인 곳을 또 다시 방문할 수 있어야 한다.
                    isused[nx][ny][horse+1] = true;
                    Q.push(make_pair(make_pair(horse + 1,now_number + 1),make_pair(nx,ny)));
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(!Out(nx,ny)&&maps[nx][ny]!=1&&!isused[nx][ny][horse]){ // 말이 되지 않았기 때문에 horse 값을 증가시키지 않는다.
                isused[nx][ny][horse] = true;
                Q.push(make_pair(make_pair(horse,now_number + 1),make_pair(nx,ny)));
            }
        }
    }
    return 0;
}

int main(){
    cin >> K;
    cin >> W >> H;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> maps[i][j];
        }
    }
    int x = BFS();
    if(x==0)
        cout << -1;

    return 0;
}
