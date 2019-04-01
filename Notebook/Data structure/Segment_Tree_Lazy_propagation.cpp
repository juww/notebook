const int INF = 1e9;
const int SIZE = 1e5 + 5;

int N, Q;
int tr[SIZE*4], lazy[SIZE*4];
int A[SIZE];

void build(int indx, int st, int ed){
	
	if(st==ed){
		tr[indx]=A[st];
	} else {
		int mid=(st+ed)/2;
		build(indx*2,st,mid);
		build(indx*2+1,mid+1,ed);
		tr[indx]=tr[indx*2]+tr[indx*2+1];
	}
}

void update(int indx, int st, int ed, int l, int r, int v){
	
	if(lazy[indx]!=0){
		tr[indx]+=(lazy[indx]*(ed-st+1));
		if(st!=ed){
			lazy[indx*2]+=lazy[indx];
			lazy[indx*2+1]+=lazy[indx];
		}
		lazy[indx]=0;
	}
	if(st>r || ed<l || st>ed) return;
	if(st>=l && ed<=r){
		tr[indx]+=(v*(ed-st+1));
		if(st!=ed){
			lazy[indx*2]+=v;
			lazy[indx*2+1]+=v;
		}
	} else {
		int mid=(st+ed)/2;
		upadate(indx*2,st,mid,l,r,v);
		upadate(indx*2+1,mid+1,ed,l,r,v);
		tr[indx]=tr[indx*2]+tr[indx*2+1];
	}
}

int query(int indx, int st, int ed, int l, int r){
	
	if(lazy[indx]!=0){
		tr[indx]+=(lazy[indx]*(ed-st+1));
		if(st!=ed){
			lazy[indx*2]+=lazy[indx];
			lazy[indx*2+1]+=lazy[indx];
		}
		lazy[indx]=0;
	}
	if(st>r || ed<l || st>ed) return 0;
	if(st>=l && ed<=r) return tr[indx];
	
	int mid=(st+ed)/2;
	int q1=query(indx*2,st,mid,l,r);
	int q2=query(indx*2+1,mid+1,ed,l,r);
	
	return p1+p2;
}
