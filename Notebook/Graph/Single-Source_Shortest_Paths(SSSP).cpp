//Dijkstra's Algorithm
//single source shortest path
int Dijkstra(int st, int ed){
	
	for(int i=0;i<SIZE;i++) cost[i]=INF;
	priority_queue<pair<int,int> > pq;
	cost[st]=0;
	pq.push(mp(0,st));
	while(!pq.empty()){
		int indx=pq.top().second;
		int step=-pq.tp.fi;
		pq.pop();
		if(indx==ed) return step;
		for(int i=0;i<vp[indx].size();i++){
			int idx=vp[indx][i].first;
			int move=vp[indx][i].second;
			if(visit[idx]>move+step){
				visit[idx]=min(visit[idx],move+step);
				pq.push(mp(-visit[idx],idx));
			}
		}
	}
	return -1;
}

//Floyd–Warshall's Algorithm
//all pair shortest path
void Floyd(int n){
	
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
			}
		}
	}	
}