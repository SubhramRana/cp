// n-> length of original array
// just an example of BIT/fenwick tree (1 based indexing in BIT)
// qu link -> https://www.codechef.com/problems/SPREAD
void add(ll i,ll delta){
	for(ll j=i;j<=n;j=j+(j&-j)){
		bit[j]+=delta;
	}
}

ll getSumUpto(ll r){
	ll ans=0;
	for(ll i=r;i>=1;i-=(i&-i)){
		ans+=bit[i];
	}
	return ans;
}

void constructBIT(){
	bit.resize(n+1,0);
}

//youtube tutorial-> https://www.youtube.com/watch?v=DPiY9wFxGIw
// segment tree VS BIT --> https://stackoverflow.com/questions/64190332/fenwick-tree-vs-segment-tree
