int N;
int A[SIZE];

// Binary search (note boundaries in the caller) 
int find(int start, int end, int num){
	
	while(end-start>1){
		int mid=start+(end-start)/2;
		if(temp[mid]>=num) end=mid;
		else start=mid;
	}
	return end;
}

int LIS(){
	
	vector<int>temp;
	temp.push_back(A[0]);
	
	for(int i=1;i<N;i++){
		if(temp[temp.size()-1]<A[i]){ //increasing orders
			temp.push_back(A[i]);
		} else if(temp[0]>A[i]){ //less than first in lis
			temp[0]=A[i];
		} else{
			//find a index where its make it higher number of list
			int indx=find(-1,temp.size()-1,A[i]);
			temp[indx]=A[i];
		}
	}
	return (int)temp.size(); //return a lis
}