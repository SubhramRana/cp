// qu : https://www.spoj.com/problems/RMQSQ/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pi pair<int,int>
#define vi vector<int>
#define vii vector<vector<int>>
#define vl vector<long long>
#define vll vector<vector<long long>>
#define vc vector<vector<int>>
#define vcc vector<vector<char>>
#define vs vector<string>
#define vss vector<vector<string>>

vi A;
vii dp;
int n,q,l;

void preCompute(){
	for(int i=0;i<n;i++){
		dp[i][0]=A[i];
	}
	for(int j=1;j<=l;j++){
		for(int i=0;i+(1<<j)<=n;i++){
			dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		}
	}
}

void buildSparseTable(){
	l=ceil(log2(n));
	dp.resize(n);
	for(int i=0;i<n;i++){
		dp[i].resize(l+1);
	}
	preCompute();
}

int getMin(int l,int r){
	int len=r-l+1;
	int ans=INT_MAX;
	for(int i=0;i<=(int)ceil(log2(n));i++){
		if((1<<i)&len){
			ans=min(ans,dp[l][i]);
			l+=(1<<i);
		}
	}
	return ans;
	// int k=log2(len);
	// return min(dp[l][k],dp[r-(1<<k)+1][k]);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

	cin>>n;
	A.resize(n);

	for(auto &x:A){
		cin>>x;
	}

	buildSparseTable();
	// for(auto &x:dp){
	// 	for(auto &y:x){
	// 		cout<<y<<" ";
	// 	}
	// 	cout<<endl;
	// }

	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<getMin(l,r)<<endl;
	}

	return 0;
}
