#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <set>
#include <algorithm>

using namespace std;

vector <int> size_maps; // 빈 구역의 공간 크기를 저장하는 vector

bool isused[1003][1003];
int N,M;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int maps[1003][1003];
int result_maps[1003][1003] = {0};
int copy_maps[1003][1003] = {0};

bool Out(int x,int y){
    if(x<0||y<0||x>=N||y>=M)
        return true;
    else return false;
}
  
int BFS(int number,int x,int y){ // 벽이 아닌 곳을 찾아서 BFS를 돌린다.
    int result = 1;
    queue <pair<int,int>> Q;
    Q.push(make_pair(x,y));
    isused[x][y] = true;
    copy_maps[x][y] = number;

    while (!Q.empty())
    {
        int X = Q.front().first;
        int Y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(!Out(nx,ny)&&!isused[nx][ny]&&maps[nx][ny]!=1){
                result ++;
                isused[nx][ny] = true;
                copy_maps[nx][ny] = number;
                Q.push(make_pair(nx,ny));
            }
        } 
    }
    return result; // 공간 크기를 리턴한다.
}

int main(){

    vector <pair<int,int>> V;
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        string get;
        cin >> get;
        for (int j = 0; j < M; j++)
        {
            if(get[j]=='0')
                maps[i][j] = 0;
            else {
                V.push_back(make_pair(i,j)); // 벽 좌표를 저장한다
                maps[i][j] = 1;
            }
        }
    }
    size_maps.push_back(0);
    for (int i = 0; i < N; i++) // 빈 공간 구역을 지정하고 크기를 저장할 수 있게 한다.
    {
        for (int j = 0; j < M; j++)
        {
            if(!isused[i][j]&&maps[i][j]==0){
                int get = BFS(size_maps.size(),i,j);
                size_maps.push_back(get);
            }
        }
    }

    vector <int> V3;
    for (int i = 0; i < V.size(); i++)
    {
        int result = 1;
        set<int>s;
        int X = V[i].first;
        int Y = V[i].second;

        for (int i = 0; i < 4; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            if(Out(nx,ny)||maps[nx][ny]==1)
                continue;
            if(s.find(copy_maps[nx][ny])==s.end()){ // 아 여기 때문에 정신 나갈 뻔했다. set 안 쓰고 똥고집 부리지 말자
                result +=size_maps[copy_maps[nx][ny]];
                s.insert(copy_maps[nx][ny]);
            }
        }
        result_maps[X][Y] = result % 10;
    }
    
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << result_maps[i][j];
        }
        cout << '\n';
    }
    
    return 0;
}
