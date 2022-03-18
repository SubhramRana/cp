//qu link -> https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A?csrf_token=7522790a3a1b2f3a5ca1a8925b96137f

//solution ;;;;>


#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m;
vector<ll> A,st;

ll getMid(ll a,ll b){
	return a+(b-a)/2;
}

ll buildUtils(ll ss,ll se, ll si){
	if(ss==se){
		return st[si]=A[ss];
	}
	ll mid=getMid(ss,se);
	ll leftSum=buildUtils(ss,mid,2*si+1);
	ll rightSum=buildUtils(mid+1,se,2*si+2);
	return st[si]=leftSum+rightSum;
}

void buildSegmentTree(){
	ll treeHeight= ceil(log2(n))+1;
	ll treeSize=(1<<(treeHeight))-1;
	st.resize(treeSize,0);
	buildUtils(0,n-1,0);
}

ll add(ll ss, ll se, ll si, const ll i,const ll delta){
	if(i<ss || i>se)return st[si];
	if(ss==se){
		A[i]+=delta;
		return st[si]=A[i];
	}
	ll mid=getMid(ss,se);
	ll leftSum=add(ss,mid,2*si+1,i,delta);
	ll rightSum=add(mid+1,se,2*si+2,i,delta);
	return st[si]=leftSum+rightSum;
}

void update(ll i,ll val){
	ll delta = val-A[i];
	add(0,n-1,0,i,delta);
}

ll getSumUtils(ll ss,ll se,ll si,const ll qs,const ll qe){
	if(se<qs || ss>qe)return 0;
	if(ss>=qs && se<=qe)return st[si];
	ll mid=getMid(ss,se);
	ll leftSum=getSumUtils(ss,mid,2*si+1,qs,qe);
	ll rightSum=getSumUtils(mid+1,se,2*si+2,qs,qe);
	return leftSum+rightSum;
}

ll getSum(ll l,ll r){
	return getSumUtils(0,n-1,0,l,r);
}

int main() {
	cin>>n>>m;
	A.resize(n);
	for(ll i=0;i<n;i++)cin>>A[i];
	buildSegmentTree();
	// for(auto x:st)cout<<x<<" ";
	// cout<<endl;
	while(m--){
		ll tp;
		cin>>tp;
		if(tp==1){
			//update A[i]
			ll i,val;
			cin>>i>>val;
			update(i,val);
		}
		else  if(tp==2){
			ll l,r;
			cin>>l>>r;
			r--;
			cout<<getSum(l,r)<<endl;
		}
	}
	// for(auto x:A)cout<<x<<" ";
}
