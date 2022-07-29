#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int N,M;
int maps[101][101];
bool check_maps[101][101]; //불이 켜졌는지
bool isused[101][101]; // 방문했
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int result = 1;

vector <pair<int,int>> V[101][101];
vector <pair<int,int>> check;

bool Out(int x,int y){
    if(x<1||y<1||x>N||y>N)
        return true;
    else return false;
}

void BFS(){

    queue <pair<int,int>> Q;
    isused[1][1] = true;
    check_maps[1][1] = true;
    Q.push(make_pair(1,1));

    while (true)
    {
        if(Q.empty()){ //만약 Q가 비었을 경우 
            for (int i = 0; i < check.size(); i++) // 불을 킨 Vector를 탐색한다.
            {
                int x = check[i].first;
                int y = check[i].second;
                if(isused[x][y]) // 방문했던 방일 경우 패스
                    continue;
                else {           // 방문하지 않은 방인 경우
                    for (int i = 0; i < 4; i++) 
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if(isused[nx][ny]){ // 상하좌우 안에 방문했던 경우 즉 불이 켜져 있는 경우
                            Q.push(make_pair(x,y)); // 불이 켜져있음으로 방문이 가능해진다. q.push
                            isused[x][y] = true;
                        }
                    }
                }
            }
            if(Q.empty()) // 켜진 방을 모두 방문한 경우 또는 방문할 수 없는 경우 BFS를 탈출한다.
                break;
        }
        
        int X = Q.front().first;
        int Y = Q.front().second;
        for (int i = 0; i < V[X][Y].size(); i++) // 불켜기
        {
            int x = V[X][Y][i].first;
            int y = V[X][Y][i].second;
            if(check_maps[x][y]) // 이미 켜져있는 방일 경우 
                continue;
            check_maps[x][y] = true; // 불을 킨다.
            //cout << x << ' ' << y << '\n';
            check.push_back(make_pair(x,y));
            result++;
        }

        Q.pop();
        for (int i = 0; i < 4; i++) // 기본적인 BFS
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];

            if(!Out(nx,ny)&&!isused[nx][ny]&&check_maps[nx][ny]){ // 불이 켜져있는지 확인하는 조건을 추가한다.
                isused[nx][ny] = true;
                Q.push(make_pair(nx,ny));
            }
        }
    }
}

int main(){
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int x,y,turn_x,turn_y;
        cin >> x >> y >> turn_x >> turn_y;
        V[x][y].push_back(make_pair(turn_x,turn_y));
    }
    BFS();
    cout << result;

    return 0;
}
