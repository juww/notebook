const int INF = 1e9;
const int SIZE = 2222;

int N, M;
int match[SIZE], par[SIZE], flower[SIZE], getlca[SIZE];
bool vis[SIZE];
vector<int> v[SIZE];
int tt=0;

void init(){
	for(int i=0;i<SIZE;i++){
		match[i]=0;
		getlca[i]=0;
		v[i].clear();
	}
	tt=0;
}

void addedge(int a, int b){
	v[a].pb(b);
	v[b].pb(a);
}

int LCA(int a, int b){
	
	tt++;
	while(true){
		a=flower[a];
		getlca[a]=tt;
		if(match[a]==0) break;
		a=par[match[a]];
	}
	while(true){
		b=flower[b];
		if(getlca[b]==tt) break;
		b=par[match[b]];
	}
	return b;
}

void blossom(int indx, int idx, int lca, queue<int> &q){
	
	while(flower[indx]!=lca){
		if(vis[indx]==false){
			vis[indx]=true;
			q.push(indx);
		}
		if(vis[match[indx]]==false){
			vis[match[indx]]=true;
			q.push(match[indx]);
		}
		flower[indx]=lca;
		flower[match[indx]]=lca;
		par[indx]=idx;
		idx=match[indx];
		indx=par[match[indx]];
	}
	
}

void augment(int indx){
	
	while(indx>0){
		int idx=par[indx], matchidx=match[idx];
		match[indx]=idx;
		match[idx]=indx;
		indx=matchidx;
	}
}

bool BFS(int root, int n){
	
	for(int i=0;i<=n;i++){
		vis[i]=false;
		par[i]=0;
		flower[i]=i;
	}
	queue<int> q;
	q.push(root);
	vis[root]=true;
	while(!q.empty()){
		int indx=q.fr;
		unmatch[indx]=true;
		q.pop();
		for(int i=0;i<(int)v[indx].size();i++){
			int idx=v[indx][i];
			if(flower[indx]!=flower[idx] && idx!=match[indx]){
				if(idx==root || (match[idx]>0 && par[match[idx]]>0)){
					int lca=LCA(indx,idx);
					blossom(indx,idx,lca,q);
					blossom(idx,indx,lca,q);
				} else if(par[idx]==0){
					par[idx]=indx;
					if(match[idx]>0){
						vis[match[idx]]=true;
						q.push(match[idx]);
					} else {
						augment(idx);
						return true;
					}
				}
			}
		}
	}
	return false;
}

int edmonds(int n){
	
	int ret=0;
	for(int i=1;i<=n;i++){
		int indx=i;
		if(match[indx]==0){
			for(int j=0;j<(int)v[indx].size();j++){
				int idx=v[indx][j];
				if(match[idx]==0){
					match[indx]=idx;
					match[idx]=indx;
					ret++;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(match[i]==0){
			if(BFS(i,n)) ret++;
		}
	}
	
	return ret;
}