const int SIZE = 1e5 + 5;
const int INF = 1e9;

vector<int> v[SIZE], u[SIZE];
// v -> the original directed
// u -> the reversed directed
int vis[SIZE], scc[SIZE];
stack<int> st;
int tt=1;

void init(){
	for(int i=0;i<SIZE;i++){
		v[i].clear();
		u[i].clear();
		scc[i]=0;
		vis[i]=0;
	}
	tt=1;
}

void DFS1(int indx){
	
	// the first dfs for insert the node to the stack
	vis[indx]=0;
	for(int i=0;i<(int)v[indx].size();i++){
		int idx=v[indx][i];
		if(vis[idx]==0){
			DFS1(idx);
		}
	}
	st.push(indx);
}

void DFS2(int indx){
	
	// the second dfs for find the SSC
	// use node form the stack
	vis[indx]=2;
	for(int i=0;i<(int)u[indx].size();i++){
		int idx=u[indx][i];
		if(vis[idx]==1){
			DFS2(idx);
		}
	}
	scc[indx]=tt;
}

void SCC(int n){
	
	for(int i=0;i<n;i++){
		if(vis[i]==0){
			DFS1(i);
		}
	}
	while(!ck.empty()){
		int i=ck.top();
		ck.pop();
		if(vis[i]==1){
			DFS2(i);
		}
	}
}
