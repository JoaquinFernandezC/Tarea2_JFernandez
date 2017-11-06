#include <vector>
#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;
const int nmax = 1e6; //Max value for total nodes
int n, b, f, c; //Total nodes, back edges, forward edges and cross edges
vector<int> children[nmax];
vector<pair<int,int>> cross;
vector<pair<int,int>> down;
vector<int> ancestors;

bool discovered[nmax];
bool finished[nmax];
vector<int> Graph(nmax);
vector<pair<int,int>> forward;
vector<pair<int,int>> backward;
vector<pair<int,int>> cross2;
stack<int> dstack;

void dfs2(int u){
	//u is on the stack now
	dstack.push(u);
	discovered[u] = true;
	for(int v:Graph[u]){
		if(finished[v]){
			if(
			cross2.push_back({u,v});
			continue;
		}
		if(discovered[v]){
			if(u == v) continue;
			backward.push_back({u,v});
			continue;
		}
	}
}
			

void dfs(int a, int next) {
	if(next > n) return;
	for(int i = 0; i < (int) ancestors.size() && (int) down.size() < max(f, b); ++i)
		down.push_back({ancestors[i], next});
	children[a].push_back(next);
	int rem = n - next + 1;
	if(c - (int) cross.size() >= rem - 1) {
		for(int i = next + 1; i <= n && (int) cross.size() < c; ++i) {
			cross.push_back({i, next});
		}
		dfs(a, next + 1);
	}
	else {
		ancestors.push_back(a);
		dfs(next, next + 1);
		ancestors.pop_back();
	}
}

vector<int> tmp[nmax];

int main() {
	scanf("%d%d%d%d", &n, &b, &f, &c);
	++n;// n starts as tree edges, then becomes total nodes. Nodes = Tree edges+1 
	b -= n - 1;
	dfs(1, 2);
	if((int) down.size() < max(f, b) || (int) cross.size() < c) {
		puts("-1");
		return 0;
	}
	b += n - 1;
	for(int a = 1; a <= n; ++a)
		for(int x : children[a])
			if(b) {
				--b;
				tmp[x].push_back(a);
			}
	for(int a = 1; a <= n; ++a)
		for(int x : tmp[a])
			children[a].push_back(x);
	
	for(auto p : cross)
		children[p.first].push_back(p.second);
	
	for(auto p : down) {
		if(f) {
			--f;
			children[p.first].push_back(p.second);
		}
		if(b) {
			--b;
			children[p.second].push_back(p.first);
		}
	}
	printf("Total Nodes = %d\n", n);
	for(int i = 1; i <= n; ++i) {
		printf("%d ", (int) children[i].size());
		for(int x : children[i]) printf("%d ", x);
		puts("");
	}
}
