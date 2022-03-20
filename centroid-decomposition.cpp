// qu : https://codeforces.com/contest/1406/problem/C
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define pi pair<int, int>

int getCentroid(vector<vector<int>> &A, vector<int> &S)
{
    int cur = 0, p = -1;

    while (true)
    {
        int hvSize = 0, hvChild = -1;
        for (auto &x : A[cur])
        {
            if (x != p)
            {
                if (S[x] > hvSize)
                {
                    hvChild = x;
                    hvSize = S[x];
                }
            }
        }
        if (hvSize <= A.size() / 2)
        {
            return cur;
        }
        p = cur;
        cur = hvChild;
    }
    return cur;
}

void dfsSaveParentsAndGetSize(vector<vector<int>> &A, int v, int p, vector<int> &P, vector<int> &S)
{
    P[v] = p;
    for (auto &x : A[v])
    {
        if (x != p)
        {
            dfsSaveParentsAndGetSize(A, x, v, P, S);
            S[v] += S[x];
        }
    }
}

void Link(pi &toCut, pi &toLink, pi &twoCentroids, vector<vector<int>> &A, vector<int> &P)
{
    if (twoCentroids == make_pair(-1, -1))
        return;

    for (auto &x : A[twoCentroids.second])
    {
        if (x != twoCentroids.first)
        {
            toCut = make_pair(twoCentroids.second, x);
            toLink = make_pair(x, twoCentroids.first);
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> A(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        A[a].push_back(b);
        A[b].push_back(a);
    }

    pi toCut, toLink;
    pi twoCentroids = make_pair(-1, -1);

    vector<int> P(n, -1);
    vector<int> S(n, 1);
    dfsSaveParentsAndGetSize(A, 0, -1, P, S);
    int centroid = getCentroid(A, S);

    int cutNode = -1;

    for (int &x : A[centroid])
    {
        if (x == P[centroid])
        {
            if (S[centroid] == n / 2)
            {
                twoCentroids = make_pair(centroid, x);
                break;
            }
        }
        else
        {
            if ((double)S[x] == (double)n / 2)
            {
                twoCentroids = make_pair(centroid, x);
                break;
            }
        }
    }

    Link(toCut, toLink, twoCentroids, A, P);
    if (twoCentroids.first == -1 || twoCentroids.second == -1)
    {
        cout << 1 << " " << A[0][0] + 1 << endl
             << 1 << " " << A[0][0] + 1 << endl;
    }
    else
    {
        cout << toCut.first + 1 << " " << toCut.second + 1 << endl;
        cout << toLink.first + 1 << " " << toLink.second + 1 << endl;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
