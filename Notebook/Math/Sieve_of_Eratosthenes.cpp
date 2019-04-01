bool prime[SIZE];
void sieve(){
	memset(prime,true,sizeof(prime));
	prime[0]=false; prime[1]=false;
	for(int i=4;i<SIZE;i+=2) prime[i]=false;
	for(int i=3;i*i<SIZE;i+=2) if(prime[i]==true)
		for(int j=i*i;j<SIZE;j+=i) prime[j]=false;
}