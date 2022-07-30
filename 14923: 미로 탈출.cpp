#include <iostream>
#include <queue>

using namespace std;

int N,M;
int Hx,Hy,Ex,Ey;

int maps[1003][1003];
bool isused[1003][1003][3];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

bool Out(int x,int y){
    if(x<0||y<0||x>=N||y>=M)
        return true;
    else return false;
}

int BFS(){
    queue <pair<pair<int,int>,pair<int,int>>> Q;
    isused[Hx-1][Hy-1][0] = true;
    Q.push(make_pair(make_pair(Hx-1,Hy-1),make_pair(0,0)));

    while (!Q.empty())
    {
        int X = Q.front().first.first;
        int Y = Q.front().first.second;
        int count = Q.front().second.first;
        int block = Q.front().second.second;
        Q.pop();

        if(X == Ex-1&&Y == Ey-1)
            return count;

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];

            if(Out(nx,ny))
                continue;

            if(maps[nx][ny]==1&&!isused[nx][ny][block+1]&&block <1){
                isused[nx][ny][block +1] = true;
                Q.push(make_pair(make_pair(nx,ny),make_pair(count + 1,block + 1)));
            } else if(maps[nx][ny]==0&&!isused[nx][ny][block]){
                isused[nx][ny][block] = true;
                Q.push(make_pair(make_pair(nx,ny),make_pair(count + 1,block)));
            }
        }
    }
    return -1;
}

int main(){
    cin >> N >> M;
    cin >> Hx >> Hy;
    cin >> Ex >> Ey;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> maps[i][j];
        }
    }
    
    int result = BFS();
    cout << result;

    return 0;
}
