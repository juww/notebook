const int SIZE = 50005;
const int INF = 1e9;

vector<int> v[SIZE];
int L[SIZE], R[SIZE], lvl[SIZE];

void init(){
	for(int i=0;i<SIZE;i++){
		L[i]=0; R[i]=0; lvl[i]=0; v[i].clear();
	}
}

bool BFS(int n){
	
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(L[i]==0) lvl[i]=0,q.push(i);
		else lvl[i]=INF;
	}
	lvl[0]=INF;
	while(!q.empty()){
		int indx=q.front();
		q.pop();
		if(lvl[indx]<lvl[0]){
			for(int i=0;i<(int)v[indx].size();i++){
				int idx=v[indx][i];
				if(lvl[R[idx]]==INF){
					lvl[R[idx]]=lvl[indx]+1;
					q.push(R[idx]);
				}
			}
		}
	}
	return lvl[0]!=INF;
}

bool DFS(int indx){
	
	if(indx!=0){
		for(int i=0;i<(int)v[indx].size();i++){
			int idx=v[indx][i];
			if(lvl[R[idx]]==lvl[indx]+1){
				if(DFS(R[idx])==true){
					R[idx]=indx;
					L[indx]=idx;
					return true;
				}
			}
		}
		lvl[indx]=INF;
		return false;
	}
	return true;
}

int Karp(int n){
	
	int ret=0;
	while(BFS(n)){
		for(int i=1;i<=n;i++){
			if(L[i]==0 && DFS(i)) ret++;
		}
	}
	
	return ret;
}
