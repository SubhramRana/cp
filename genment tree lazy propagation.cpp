// topCoder blog : https://www.topcoder.com/thrive/articles/range-operations-lazy-propagation

//question : https://cses.fi/problemset/task/1651

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pi pair<ll,ll>
#define vi vector<ll>
#define vii vector<vector<ll>>
#define vl vector<long long>
#define vll vector<vector<long long>>
#define vc vector<vector<ll>>
#define vcc vector<vector<char>>
#define vs vector<string>
#define vss vector<vector<string>>


ll n;
vl A;
struct node{
	ll val,lazy;
};
vector<node> st;

ll getMid(ll a,ll b){
	return (a+b)/2;
}

void propagate(ll si,ll ss,ll se){
	ll mid=getMid(ss,se);
	st[si].val+=st[si].lazy;
	st[2*si+1].lazy+=((st[si].lazy/(se-ss+1))*(mid-ss+1));
	st[2*si+2].lazy+=((st[si].lazy/(se-ss+1))*(se-(mid+1)+1));
	st[si].lazy=0;
}

void update(ll si,ll ss,ll se, const ll qs, const ll qe,const ll delta){
	if(ss>qe || se<qs)return ;
	if(ss>=qs && se<=qe) {
		st[si].lazy+=(se-ss+1)*delta;
		return;
	}
	ll mid=getMid(ss,se);

	propagate(si,ss,se);

	update(2*si+1,ss,mid,qs,qe,delta);
	update(2*si+2,mid+1,se,qs,qe,delta);
}

ll getVal(ll si,ll ss,ll se, const ll qi){
	if (ss==se){
		st[si].val+=st[si].lazy;
		st[si].lazy=0;
		return st[si].val;
	}
	ll mid=getMid(ss,se);

	propagate(si,ss,se);

	if(qi<=mid){
		return getVal(2*si+1,ss,mid,qi);
	}
	return getVal(2*si+2,mid+1,se,qi);
}


void build(ll si,ll ss,ll se){
	if(ss==se){
		st[si].val=A[ss];
		return;
	}
	ll mid=getMid(ss,se);
	build(2*si+1,ss,mid);
	build(2*si+2,mid+1,se);
	st[si].val=st[2*si+1].val+st[2*si+2].val;
}

void buildSegmentTree(){
	ll treeHeight = ceil(log2(n))+1;
	ll treeSize = (1<<treeHeight)-1;
	st.resize(treeSize);
	build(0,0,n-1);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif

	ll q;
	cin>>n>>q;
	// cout<<"q="<<q<<endl;
	A.resize(n);

	for(ll i=0;i<n;i++){
		cin>>A[i];
	}
	buildSegmentTree();

	ll c;
	while(q--){
		cin>>c;
		if(c==1){
			ll l,r,u;
			cin>>l>>r>>u;
			l--,r--;
			update(0,0,n-1,l,r,u);
		}
		else {
			ll i;
			cin>>i;
			i--;
			cout<<getVal(0,0,n-1,i)<<endl;
		}
	}

	return 0;
}
