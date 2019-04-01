#include<bits/stdc++.h>

using namespace std;

const int SIZE = 128;
const int INF = 1e9;

int mat[SIZE][SIZE];
int N, S, T, M;
int ans=0;

bool BFS(){
	
	queue<int> q;
	bool vis[N+2]={false};
	int par[N+2]={-1};
	q.push(S);
	vis[S]=true;
	while(!q.empty()){
		int indx=q.front();
		q.pop();
		
		if(indx==T){
			int Mn=INF;
			int temp=T;
			while(temp!=S){
				Mn=min(Mn,mat[par[temp]][temp]);
				temp=par[temp];
			}
			temp=T;
			while(temp!=S){
				mat[par[temp]][temp]-=Mn;
				mat[temp][par[temp]]+=Mn;
				temp=par[temp];
			}
			ans+=Mn;
		}
		
		for(int i=1;i<=N;i++){
			if(mat[indx][i]>0 && vis[i]==false){
				vis[i]=true;
				par[i]=indx;
				q.push(i);
			}
		}
	}
	if(vis[T]==false) return true;
	else return false;
}

int main (){
	
	int a, b, c;
	
	scanf("%d", &N);
	memset(mat,0,sizeof(mat));
	scanf("%d %d %d", &S, &T, &M);
	for(int i=0;i<M;i++){
		scanf("%d %d %d", &a, &b, &c);
		mat[a][b]+=c;
		// mat[b][a]+=c;
	}
	ans=0;
	while(1){
		if(BFS()==true) break;
	}
	printf("%d\n", ans);
	
	return 0;
}