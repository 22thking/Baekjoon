#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

int T;
int I;
int X,Y;
int XX,YY;
int isused[302][302];
int dx[8] = {-1,-2,-2,-1,1,2,2,1};
int dy[8] = {-2,-1,1,2,2,1,-1,-2};

bool Out(int x,int y){
    if(x<0||y<0||x>=I||y>=I)
        return true;
    else return false;
}

int BFS(){

    memset(isused,-1,sizeof(isused));
    queue <pair<int,int>> Q;
    Q.push(make_pair(X,Y));
    isused[X][Y] = 0;

    while (!Q.empty())
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        if(isused[XX][YY]!=-1)
            return isused[XX][YY];

        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(isused[nx][ny]==-1&&!Out(nx,ny)){
                isused[nx][ny] = isused[x][y] + 1;
                Q.push(make_pair(nx,ny));
            }
        }
        
    }
    
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T>0)
    {
        T--;
        cin >> I;
        cin >> X >> Y;
        cin >> XX >> YY;
        cout << BFS() << '\n';
    }   
    

    return 0;
}
