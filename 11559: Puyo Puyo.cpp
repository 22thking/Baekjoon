#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

char maps[12][6];
bool isused[12][6];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

bool Out(int x,int y){ // 나갔나?
    if(x<0||y<0||x>=12||y>=6)
        return true;
    else return false;
}

void Gravity(){
    for (int i = 10; i >= 0; i--) // 아래부터 탐색을 해야지 위에 있는 것이 내려온다.
    {
        for (int j = 0 ; j < 6; j++)
        {
            if(maps[i][j]!='.'){
                int X = i + 1;
                int Y = j;
                while (true)
                {
                    if(Out(X,Y)||maps[X][Y]!='.') // 아니면 내려가기
                        break;
                    X = X + 1;
                }
                X--; // 더했던거 빼버리기
                if(i==X){ // 제자리에 있는 것들은 가만둔다.
                    continue;
                }
                maps[X][Y] = maps[i][j];
                maps[i][j] = '.';
            }
        }
    }
    
}

bool BFS(char get,int x,int y){ // 색도 매개변수로 받는다.
    bool check = false;
    vector <pair<int,int>> V; // 좌표를 저장하는 벡터
    queue <pair<int,int>> Q; // BFS를 위한 큐
    isused[x][y] = true;
    V.push_back(make_pair(x,y));
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

            if(!Out(nx,ny)&&get==maps[nx][ny]&&!isused[nx][ny]){ //기본적인 BFS 구조를 가지고 있지만 좌표를 추가하는 것을 곁드린...
                isused[nx][ny] = true;
                V.push_back(make_pair(nx,ny));
                Q.push(make_pair(nx,ny));
            }
        }
    }
    if(V.size()>=4){ // 추가한 좌표가 4개 이상 즉 같은 색거품이 4개 이상 뭉쳐있을 경우
        for (int i = 0; i < V.size(); i++)
        {
            int X = V[i].first;
            int Y = V[i].second;
            maps[X][Y] = '.';
        }
        check = true; // 터진 경우에만 좌표 변동이 있으니 계속 BFS를 돌아야하기 때문에 true 값을 리턴
    }
    return check;
}

int main(){
    int result = 0;
    for (int i = 0; i < 12; i++)
    {
        string get;
        cin >> get;
        for (int j = 0; j < 6; j++)
        {
            maps[i][j] = get[j];
        }
    }
    while (true) // 조건에 맞는 경우 거품이 터트리고 중력을 작용시킨다.
    {
        memset(isused,false,sizeof(isused)); // isused 초기화는 기본이다.
        bool check = false;
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                if(maps[i][j]!='.'&&!isused[i][j]){ // 색 거품일 경우
                    bool dsa = BFS(maps[i][j],i,j); // 거품이 터질 경우 계속 진행한다.
                    if(dsa)
                        check = true;
                }
            } 
        }

        if(!check)
            break;
        Gravity();
        result ++;
    }
    
    cout << result;

    return 0;
}
