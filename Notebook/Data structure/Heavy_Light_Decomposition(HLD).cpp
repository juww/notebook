#include<bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int SIZE = 1e5 + 5;

int N; // node on tree
int col; // color of chain
int ptr; // used for indexing segment tree
vector<pii> v[SIZE]; // the tree
vector<int> Index[SIZE]; //Indexing the node to segment tree
int otherend[SIZE];
int par[20][SIZE], lvl[SIZE], nchild[SIZE]; //use for LCA
int headchain[SIZE], colorchain[SIZE], poschain[SIZE], costchain[SIZE]; // make a chain of HLD
int tr[SIZE*4]; // segment tree.

void init(){
	for(int i=0;i<SIZE;i++){
		for(int k=0;k<20;k++){
			par[k][i]=-1;
		}
		v[i].clear();
		Index[i].clear();
		otherend[i]=-1;
		nchild[i]=0;
		headchain[i]=-1;
		colorchain[i]=-1;
		poschain[i]=-1;
		costchain[i]=-1;
	}
	col=1, ptr=1;
}

////////////////////////// LCA //////////////////////////////
void DFS(int indx, int prev){
	
	lvl[indx]=lvl[prev]+1;
	par[0][indx]=prev;
	for(ui i=0;i<v[indx].size();i++){
		int idx=v[indx][i].fi;
		if(idx!=prev){
			otherend[Index[indx][i]]=idx;
			DFS(idx,indx);
			nchild[indx]+=nchild[idx];
		}
	}
	nchild[indx]++;
}

void memo(){
	
	for(int i=1;i<15;i++){
		for(int j=1;j<=N;j++){
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}
}

int LCA(int a, int b){
	
	if(lvl[a]>lvl[b]) swap(a,b);
	int dif=lvl[b]-lvl[a];
	
	for(int i=0;i<20;i++){
		if(((dif)>>i)%2==1){
			b=par[i][b];
		}
	}
	if(a==b) return a;
	for(int i=19;i>=0;i--){
		if(par[i][a]!=par[i][b]){
			a=par[i][a];
			b=par[i][b];
		}
	}
	return par[0][b];
}
////////////////////////// LCA //////////////////////////////

////////////////////////// HLD //////////////////////////////
void build_HLD(int indx, int prev, int cost){
	
	if(headchain[col]==-1) headchain[col]=indx;
	colorchain[indx]=col;
	poschain[indx]=ptr;
	costchain[ptr++]=cost;
	
	int idx=-1, child=0, C=0;
	for(int i=0;i<v[indx].size();i++){
		int &dx=v[indx][i].fi;
		int &c=v[indx][i].se;
		if((idx==-1 || child<nchild[dx]) && dx!=prev){
			idx=dx;
			child=nchild[dx];
			C=c;
		}
	}
	if(idx!=-1) build_HLD(idx,indx,C);
	for(int i=0;i<v[indx].size();i++){
		int &dx=v[indx][i].fi;
		int &c=v[indx][i].se;
		if(dx!=prev && dx!=idx){
			col++;
			build_HLD(dx,indx,c);
		}
	}
}
////////////////////////// HLD //////////////////////////////

///////////////////// segment tree //////////////////////////
void build_tree(int indx, int st, int ed){
	
	if(st==ed){
		tr[indx]=costchain[st];
	} else {
		int mid=(st+ed)/2;
		build_tree(indx*2,st,mid);
		build_tree(indx*2+1,mid+1,ed);
		tr[indx]=max(tr[indx*2],tr[indx*2+1]);
	}
}

void Update_tree(int indx, int st, int ed, int idx, int val){
	
	if(st>idx || ed<idx) return;
	if(st==idx && ed==idx){
		tr[indx]=val;
	} else {
		int mid=(st+ed)/2;
		Update_tree(indx*2,st,mid,idx,val);
		Update_tree(indx*2+1,mid+1,ed,idx,val);
		tr[indx]=max(tr[indx*2],tr[indx*2+1]);
	}
}

int query_tree(int indx, int st, int ed, int l, int r){
	
	if(st>r || ed<l){
		return -INF;
	}
	if(st>=l && ed<=r){
		return tr[indx];
	}
	int mid=(st+ed)/2;
	int p1=query_tree(indx*2,st,mid,l,r);
	int p2=query_tree(indx*2+1,mid+1,ed,l,r);
	return max(p1,p2);
}
///////////////////// segment tree //////////////////////////

int Query_up(int a, int b, int n){
	
	if(a==b) return 0;
	
	int colora=colorchain[a], colorb=colorchain[b], ans=0;
	
	while(true){
		colora=colorchain[a];
		int l, r, Mx;
		if(colora==colorb){
			if(a==b) break;
			l=min(poschain[a],poschain[b]);
			r=max(poschain[a],poschain[b]);
			l++;
			Mx=query_tree(1,1,n,l,r);
			ans=max(ans,Mx);
			break;
		}
		l=min(poschain[headchain[colora]],poschain[a]);
		r=max(poschain[headchain[colora]],poschain[a]);
		Mx=query_tree(1,1,n,l,r);
		ans=max(ans,Mx);
		a=headchain[colora];
		a=par[0][a];
	}
	return ans;
}

int Query(int a, int b, int n){
	
	int indx=LCA(a,b);
	int ans1=Query_up(a,indx,n);
	int ans2=Query_up(b,indx,n);
	
	return max(ans1,ans2);
}

void Update(int indx, int num, int n){
	
	int idx=otherend[indx];
	Update_tree(1,1,n,poschain[idx],num);
}

int main (){
	
	int Tc;
	int a, b, c;
	char ch[10];
	
	scanf("%d", &Tc);
	CASE(){
		init();
		scanf("%d", &N);
		for(int i=1;i<N;i++){
			scanf("%d %d %d", &a, &b, &c);
			v[a].pb(mp(b,c));
			v[b].pb(mp(a,c));
			Index[a].pb(i);
			Index[b].pb(i);
		}
		lvl[0]=0;
		DFS(1,0);
		memo();
		build_HLD(1,0,0);
		build_tree(1,1,ptr-1);
		while(~scanf("%s", ch)){
			if(ch[0]=='D') break;
			scanf("%d %d", &a, &b);
			if(ch[0]=='Q'){
				int ans=Query(a,b,ptr-1);
				printf("%d\n", ans);
			} else if(ch[0]=='C'){
				Update(a,b,ptr-1);
			}
		}
	}
	
	return 0;
}