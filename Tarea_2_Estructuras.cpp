#include <vector>
#include <iostream>
#include <stdio.h>
#include <stack>
using namespace std;
const int nmax = 1e6; //Max value for total nodes.
int n, b, f, c; //Total nodes, back edges, forward edges and cross edges.
vector<int> finished[nmax];//Finished nodes.
vector<pair<int,int>> cross;
vector<pair<int,int>> down;//Store both forward and backward edges. Easier to handle.
vector<int> discovered;//Stack of nodes being analized.

void dfs(int a, int next) {//next is equal to v on the edge (u,v).
	if(next > n) return;
	for(int i = 0; i < (int) discovered.size(); ++i){
		if((int) down.size() < max(f, b)){
			down.push_back({discovered[i], next});
		}
	}
	finished[a].push_back(next);
	int rem = n - next + 1;
	if(c - (int) cross.size() >= rem - 1) {//We check for if we make a cross edge or not.
		for(int i = next + 1; i <= n; ++i) {
			if((int) cross.size() < c){
				cross.push_back({i, next});
			}
		}
		dfs(a, next + 1);
	}
	else {
		discovered.push_back(a);
		dfs(next, next + 1);
		discovered.pop_back();//remove from stack.
	}
}

vector<int> tmp[nmax];//Temporal vector for later reordering

int main() {
	scanf("%d%d%d%d", &n, &b, &f, &c);
	++n;// n starts as tree edges, then becomes total nodes. Nodes = Tree edges+1 
	b -= n - 1;
	dfs(1, 2);
	if((int) down.size() < max(f, b) || (int) cross.size() < c) {//Case where there is no graph
		puts("-1");
		return 0;
	}
	b += n - 1;
	for(int a = 1; a <= n; ++a)
		for(int x : finished[a])
			if(b) {
				--b;
				tmp[x].push_back(a);
			}
	for(int a = 1; a <= n; ++a)
		for(int x : tmp[a])
			finished[a].push_back(x);
	
	for(auto p : cross)//reorder
		finished[p.first].push_back(p.second);
	
	for(auto p : down) {
		if(f) {//First we reorder forwards
			--f;
			finished[p.first].push_back(p.second);
		}
		if(b) {//Then backwards
			--b;
			finished[p.second].push_back(p.first);
		}
	}
	printf("Total Nodes = %d\n", n);
	printf("N = node\nQ = quantity\nCT = connected to\n");
	printf("N: Q CT\n");
	for(int i = 1; i <= n; ++i) {
		printf("%d: %d ", i, (int) finished[i].size());
		for(int x : finished[i]) printf("%d ", x);
		puts("");
	}
}
