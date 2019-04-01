struct node{
	int v; // from
	int u; // to
	int c; // cost
};
vector<node> vpp;
//DISJOINT SET
int Pn[SIZE];
int root(int indx){ while(Pn[indx]!=indx) indx=Pn[indx]; return indx; }
int disjoint(int a,int b){Pn[root(a)]=root(b); return root(b); }
bool find(int a,int b){ return (root(a)==root(b)); }

// Kruskal's Algorithm
int Kruskal(){
	int sum=0;
	//sort by cost increase order
	sort(vpp.begin(),vpp.end());
	int edge=N-1;
	for(int i=0;i<vpp.size();i++){
		if(edge==0) {
			return sum;
		}
		if(!find(vpp[i].v,vpp[i].u)){
			sum+=vpp[i].c;
			Pn[a]=disjoint(vpp[i].v,vpp[i].u);
			edge--;
		}
	}
	return sum;
}


//Prims's Algorithm
struct edge{
	int to;
	int cost;
}
vector<edge> v[SIZE];
bool vis[SIZE];
int Prims(int st, int ed){ 
	
	// from start to end find a cheapest cost
	// or find a maximum/minimum the cost/size/etc...
	int Mn=INF;
	
	priority_queue<pii> pq;
	pq.push(mp(INF,st));
	while(!pq.empty()){
		int indx=pq.top().to;
		int step=pq.top().cost;
		pq.pop();
		if(vis[indx]==true) continue;
		vis[indx]=true;
		Mn=min(Mn,step);
		if(indx==ed) return Mn; 
		for(ui i=0;i<v[indx].size();i++){
			int idx=v[indx][i].to;
			int move=v[indx][i].cost;
			pq.push(mp(move,idx));
		}
	}
	
	return Mn;
}
