#include <iostream>
#include <queue>

using namespace std;

int M,N,H;

int dx[6] = {0,1,0,-1,0,0};
int dy[6] = {1,0,-1,0,0,0};
int dz[6] = {0,0,0,0,1,-1}; //하 우 상 좌 아래 위

int maps[102][102][102] = {0};

bool Out_Of_Maps(int x,int y,int z){ // 나갔냐?
    if(x<0||x>=M||y<0||y>=N||z<0||z>=H){
        return true;
    }else return false;
}

int main(){
    int result =0;
    queue<pair<int, pair<int, int>>> Q;  
    queue <int> Q2;
    cin >> M >> N >> H;
    
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int z = 0; z < M; z++)
            {
                cin >> maps[z][j][i];
                if(maps[z][j][i]==1){
                    Q.push(make_pair(z,make_pair(j,i))); //x,y,z
                    Q2.push(1);
                }
            }      
        }
    }
    int now_queue = Q2.front();
    while (!Q.empty())
    {
        int X = Q.front().first;
        int Y = Q.front().second.first;
        int Z = Q.front().second.second;
        Q.pop();
        if(now_queue != Q2.front()){
            result ++;
            now_queue = Q2.front();
        }
        Q2.pop();
        for (int i = 0; i < 6; i++)
        {
            int nx = X + dx[i];
            int ny = Y + dy[i];
            int nz = Z + dz[i];
            if(!Out_Of_Maps(nx,ny,nz)&&maps[nx][ny][nz]==0){
                maps[nx][ny][nz] = maps[X][Y][Z] +1;
                Q2.push(maps[X][Y][Z] +1);
                Q.push(make_pair(nx,make_pair(ny,nz)));
            }
        }
    }
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int z = 0; z < M; z++)
            {
                if(maps[z][j][i]==0)
                result = -1;
            } 
        }   
    }

    cout << result << '\n';
    

    return 0;
}
