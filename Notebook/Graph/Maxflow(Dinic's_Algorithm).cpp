const int SIZE = 1024;
const int INF = 1e9;

int N, M;
struct edge{
	int v, f, c, u;
};
vector<edge> E[SIZE];
int lvl[SIZE], st[SIZE];

void init(){
	for(int i=0;i<SIZE;i++){
		E[i].clear();
	}
}

void addedge(int a, int b, int ca, int cb){
	edge A={a,0,ca,(int)E[a].size()};
	edge B={b,0,cb,(int)E[b].size()};
	
	E[a].pb(B);
	E[b].pb(A);
}

bool BFS(int S, int T){
	
	memset(lvl,-1,sizeof(lvl));
	queue<int> q;
	q.push(S);
	lvl[S]=0;
	
	while(!q.empty()){
		int indx=q.fr;
		q.pop();
		for(int i=0;i<(int)E[indx].size();i++){
			edge &t=E[indx][i];
			int idx=t.v;
			if(lvl[idx]<0 && t.c>t.f){
				lvl[idx]=lvl[indx]+1;
				q.push(idx);
			}
		}
	}
	return lvl[T]>=0;
}

int DFS(int indx, int T, int flow){
	
	if(indx==T) return flow;
	
	for(int &i=st[indx];i<(int)E[indx].size();i++){
		edge &t=E[indx][i];
		int idx=t.v;
		if(lvl[idx]==lvl[indx]+1 && t.c>t.f){
			int curr=min(flow,t.c-t.f);
			int flow=DFS(idx,T,curr);
			if(flow>0){
				t.f+=flow;
				v[t.v][t.u].f-=flow;
				return flow;
			}
		}
	}
	
	return 0;
}
int Dinic(int S, int T){
	
	int ret=0;
	
	while(BFS(S,T)){
		memset(st,0,sizeof(st));
		while(int flow = DFS(S,T,INF)){
			ret+=flow;
		}
	}
	
	return ret;
}