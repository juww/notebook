int expo(int a, int p, int m){
	int res=1; a%=m;
	while(b>0){
		if(b%2==1) res=(res*a)%m;
		b/=2; a=(a*a)%m;
	}
	return res;
}