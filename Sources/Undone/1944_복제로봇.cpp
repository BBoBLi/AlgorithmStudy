#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Pos{ int y; int x; };
struct Edge{ int cost; int y; int x; };
bool CompEdge(const Edge e1, const Edge e2) { return e1.cost < e2.cost; };
const int MAX_N = 51;
const int dy[4] = {1,-1,0,0};
const int dx[4] = {0,0,1,-1};

struct DisjointSet
{
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 1)
    {
        for(int i=0; i<n; i++)
            parent[i]=i;
    }

    int Find(int u)
    {
        if(u == parent[u]) return u;
        return parent[u] = Find(parent[u]);
    }

    void Merge(int u, int v)
    {
        u = Find(u); v = Find(v);
        if(u==v) return;

        if(rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if(rank[u] == rank[v]) rank[v]+=1;
    }
};

int n, m, vCnt=0;
bool ansFlag = false;
char board[MAX_N][MAX_N];
int vID[MAX_N][MAX_N];
vector<Edge> edges;
vector<Pos> stPos;

void BFS(Pos start)
{
	queue<Edge> q;
    bool visited[MAX_N][MAX_N]={false};
    int cnt=0;

	q.push({0, start.y, start.x});
	visited[start.y][start.x]=true;

	while(!q.empty())
	{
		Edge curr = q.front();
		q.pop();

		for(int i=0; i<4; i++)
		{
			Edge next = {curr.cost+1, curr.y+dy[i], curr.x+dx[i]};
            
			if(visited[next.y][next.x]) continue;
			if(board[next.y][next.x]=='1') continue;
			if(next.y<0 || next.x<0 || next.y>=n || next.x>=n) continue;

			if(board[next.y][next.x]=='K' || board[next.y][next.x]=='S')
			{
				edges.push_back({next.cost, vID[start.y][start.x], vID[next.y][next.x]});
				cnt++;// next.cost=0;
			}
			visited[next.y][next.x]=true;
           // cout<<"curr : ("<<curr.y<<","<<curr.x<<")=("<<board[curr.y][curr.x]<<")\n";
           // cout<<"next : ("<<next.y<<","<<next.x<<")=("<<board[next.y][next.x]<<")\n";
			q.push(next);
		}
	}
    
    if(cnt!=m) ansFlag = true;
}

int main()
{
	cin>>n>>m;

	for(int i=0; i<n; i++)
	for(int j=0; j<n; j++)
	{
		cin>>board[i][j];
		if(board[i][j]=='S' || board[i][j]=='K')
        {
			stPos.push_back({i, j});
            vID[i][j] = (++vCnt);
        }
	}

    cout<<"\n";
    for(int i=0; i<n; i++)
    {
    	for(int j=0; j<n; j++)
    	{
		    cout<<vID[i][j];
    	}
        cout<<"\n";
    }

	for(int i=0; i<stPos.size(); i++)
    {
        BFS(stPos[i]);
        if(ansFlag)
        {
            cout<<-1<<'\n';
            return 0;
        }
    }

    sort(edges.begin(), edges.end(), CompEdge);
    

    cout<<"vCnt : "<< vCnt<<", eCnt : "<<edges.size()<<"\n";
    for(int i=0; i<edges.size(); i++)
   
        cout<<">"<<i+1<<"-> cost :"<<edges[i].cost<<", ("<<edges[i].x<<", "<<edges[i].y<<")\n";
    

    int cnt=0, ans=0;
    
    DisjointSet djs(m+1);
    for(int i=0; i<edges.size(); i++)
    {
        if(djs.Find(edges[i].y) == djs.Find(edges[i].x)) continue;
        if(cnt==vCnt-1) break;

        djs.Merge(edges[i].y, edges[i].x);
        cnt++; ans+=edges[i].cost;
    }
    
    cout<<ans<<'\n';

	return 0;
}
