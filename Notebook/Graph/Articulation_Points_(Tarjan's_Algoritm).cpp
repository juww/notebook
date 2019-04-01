const int SIZE = 1e5 + 5;
const int INF = 1e9;

vector<int> v[SIZE]; // adjacent list
int disc[SIZE]; // time of node or the visit
bool vis[SIZE]; // visit notde
int low[SIZE]; // update of the node time
int par[SIZE]; // par -> parent of node
int t=1; // time dfs

bool ap[SIZE]; // articulation point

void init(){
	for(int i=0;i<SIZE;i++){
		v[i].clear();
		disc[i]=0;
		low[i]=0;
		par[i]=-1;
		vis[i]=false;
	}
	t=1;
}

void DFS(int indx){
	
	int child=0; // how many child at its node
	
	vis[indx]=true;
	disc[indx]=low[indx]=t++;
	
	for(int i=0;i<v[indx].size();i++){
		int idx=v[indx][i];
		
		if(vis[idx]==false){
			par[idx]=indx;
			child++;
			DFS(idx);
			//update lowtime node
			low[indx]=min(low[indx],low[idx]);
			
			//the condition its node is articulation point
			if(par[indx]==-1 && child>1){
				ap[indx]=true;
			}
			if(par[indx]!=-1 && low[idx]>=disc[indx]){
				ap[indx]=true;
			}
						
			// the condition its edge is bridge
			if(low[idx]>disc[indx]){
				printf("%d %d\n", indx, idx);
			}
			
		} else if(idx!=par[indx]){
			low[indx]=min(low[indx],disc[idx]);
		}
	}
}