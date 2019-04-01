const int SIZE = 1e5 + 5;
const int LOG_SIZE = log2(SIZE);
const int INF = 1e9;

int N, Q;
int par[LOG_SIZE+1][SIZE];
int lvl[SIZE];
vector<int> v[SIZE];

void init(){
	for(int j=0;j<LOG_SIZE;j++){
		for(int i=0;i<SIZE;i++){
			par[j][i]=-1;
		}
	}
}

void DFS(int indx, int prev){
	
	lvl[indx]=lvl[indx]+1;
	par[0][indx]=prev;
	for(int i=0;i<v[indx].size();i++){
		int idx=v[indx][i];
		if(idx!=prev){
			DFS(idx,indx);
		}
	}
}

void filltable(){
	
	for(int i=1;i<LOG_SIZE;i++){
		for(int j=1;j<=N;j++){
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}
}

int LCA(int a, int b){
	
	if(lvl[a]>lvl[b]) swap(a,b);
	int dif=lvl[b]-lvl[a];
	
	for(int i=0;i<LOG_SIZE;i++){
		if((dif>>i)%2==1){
			b=par[i][b];
		}
	}
	if(a==b) return a;
	for(int i=LOG_SIZE-1;i>=0;i--){
		if(par[i][a]!=par[i][b]){
			a=par[i][a];
			b=par[i][b];
		}
	}
	return par[0][b];
}

int main (){
	
	int a, b;
	
	scanf("%d", &N);
	for(int i=0;i<N-1;i++){
		scanf("%d %d", &a, &b);
		v[a].pb(b);
		v[b].pb(a);
	}
	lvl[0]=0;
	DFS(1,0);
	filltable();
	scanf("%d", &Q);
	while(Q--){
		scanf("%d %d", &a, &b);
		int lca=LCA(a,b);
		printf("%d\n", lca);
	}
	
	return 0;
}