const int SIZE = 1024;
const int INF = 1e9;

int N, M;
struct edge{
	int v, f, c, u;
	int cost;
};
vector<edge> v[SIZE];
int lvl[SIZE], st[SIZE];
int cost[SIZE];

void init(){
	for(int i=0;i<SIZE;i++){
		E[i].clear();
	}
}

void addedge(int a, int b, int ca, int cb, int val){
	
	edge A={a,0,ca,(int)E[a].size(),-val};
	edge B={b,0,cb,(int)E[b].size(),val};
	
	E[a].pb(B);	
	E[b].pb(A);
}

// Dijkstra -- O(VE * log V).
bool Dijkstra(int S, int T){
	
	for(int i=0;i<SIZE;i++){
		cost[i]=INF;
		lvl[i]=-1;
	}
	priority_queue<pii> pq;
	pq.push(mp(0,S));
	cost[S]=0;
	lvl[S]=0;
	while(!pq.empty()){
		int indx=pq.top().seccond;
		int val=-pq.top().first;
		pq.pop();
		if(val>cost[indx]) continue;
		for(int i=0;i<(int)E[indx].size();i++){
			edge &t=E[indx][i];
			int idx=t.v;
			if(cost[idx]>cost[indx]+t.cost && t.c>t.f){
				cost[idx]=cost[indx]+t.cost;
				lvl[idx]=lvl[indx]+1;
				pq.push(mp(-cost[idx],idx));
			}
		}
	}
	return cost[T]!=INF;
}

// SPFA -- O(V^3).
bool vis[SIZE]; 
bool spfa(int S, int T){
	
	for(int i=0;i<SIZE;i++){
		cost[i]=LLINF;
		lvl[i]=-1;
		vis[i]=false;
	}
	queue<int> q;
	q.push(S);
	vis[S]=true;
	cost[S]=0;
	lvl[S]=0;
	while(!q.empty()){
		int indx=q.fr;
		q.pop();
		vis[indx]=false;
		for(int i=0;i<(int)E[indx].size();i++){
			edge &t=E[indx][i];
			int idx=t.v;
			if(cost[idx]>cost[indx]+t.cost && t.c>t.f){
				cost[idx]=cost[indx]+t.cost;
				lvl[idx]=lvl[indx]+1;
				if(vis[idx]==false){
					vis[idx]=true;
					q.push(idx);
				}
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
		if(lvl[idx]==lvl[indx]+1 && cost[idx]==cost[indx]+t.cost && t.c>t.f){
			int ret=DFS(idx,T,min(flow,t.c-t.f));
			if(ret>0){
				t.f+=ret;
				E[t.v][t.u].f-=ret;
				return ret;
			}
		}
	}
	return 0;
}

pii MCMF(int S, int T){
	
	pii ret=mp(0,0);
	//Dijkstra 	-- O(VE * log V).
	//SPFA		-- O(V^3).
	while(Dijkstra(S,T)){
		memset(st,0,sizeof(st));
		while(int flow=DFS(S,T,INF)){
			ret.fi+=cost[T];
			ret.se+=flow;
		}
	}
	
	return ret;
}
