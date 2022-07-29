#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N,M,K;
int maps[1003][1003];
bool isused[1003][1003][10];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

struct Vertex 
{
    int x,y,dis,count,day; //좌표 / 벽을 부순 수 / 몇개 부숨 / 낮 or 밤
};


bool Out(int x,int y){
    if(x<0||y<0||x>=N||y>=M)
        return true;
    else return false;
}

int BFS(){
    queue <Vertex> Q;
    Vertex tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.count = 1;
    tmp.day = 0; // 0 이면 낮 1이면 밤
    tmp.dis = 0; // 벽을 얼마나 부숨? 변수가 왜 이따구인지는 모르겠다. 내가 정해놓고도 어이가 없다
    Q.push(tmp);
    isused[0][0][0] = true;

    while (!Q.empty())
    {
        Vertex get = Q.front();
        Q.pop();
        int X = get.x;
        int Y = get.y;
        int count = get.count;
        int dis = get.dis;
        int day = get.day;
        //cout << day << ' ' << X << ' ' << Y << '\n';

        if(X==N-1&&Y==M-1) // 목적지 도착
            return count;  

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i]; 
            if(Out(nx,ny))
                continue;
            Vertex V;
            V.x = nx; // 약간 모지리 처럼 구현한 것 같다.
            V.y = ny;
            if(maps[nx][ny]==1&&!isused[nx][ny][dis + 1]&&day==1&&dis < K){ // 밤일 경우 낮으로 바꾸고 count 늘려서 다시 push
                V.x = X;
                V.y = Y;
                V.dis = dis;
                V.day = 0;
                V.count = count +1;
                Q.push(V);
            } else if(maps[nx][ny]==1&&!isused[nx][ny][dis + 1]&&day==0&&dis < K){ // 낮일 경우 난 벽을 뚫어
                isused[nx][ny][dis + 1] = true;
                V.dis = dis + 1;
                V.day = 1;
                V.count = count +1;
                Q.push(V);
            } else if(maps[nx][ny]==0&&!isused[nx][ny][dis]){ //그냥 BFS 조건
                isused[nx][ny][dis] = true;
                V.dis = dis;
                if(day==0)
                    V.day = 1;
                else V.day = 0;
                V.count = count + 1;
                Q.push(V);
            }
        } 
    }
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
            if(get[j]=='1')
                maps[i][j] = 1;
            else maps[i][j] = 0;
        }
    }
    
    int result = BFS();
    cout << result;

    return 0;
}
