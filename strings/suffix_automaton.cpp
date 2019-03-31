#include <bits/stdc++.h>

const int32_t MAX_N = 1e5;

struct SuffixAutomaton {
	int32_t cntNodes, lastNode;
	int32_t len[2 * MAX_N + 5];
	int32_t link[2 * MAX_N + 5];
	std::map< char, int32_t > edges[2 * MAX_N + 5];
	
	void init() {
		for(int32_t i = 0; i < 2 * MAX_N + 5; i++) {
			len[i] = 0;
			link[i] = 0;
			edges[i].clear();
		}

		cntNodes = 1;
		lastNode = 0;
	}

	void add_letter(char letter) {
		int32_t p, q, clone;

		p = lastNode;
		lastNode = cntNodes++;
		len[lastNode] = len[p] + 1;

		while(edges[p].count(letter) == 0) {
			edges[p][letter] = lastNode;
			p = link[p];
		}

		if(edges[p][letter] == lastNode) {
			link[lastNode] = p;
			return;
		}

		q = edges[p][letter];
		if(len[q] == len[p] + 1) {
			link[lastNode] = q;
			return;
		}

		clone = cntNodes++;
		len[clone] = len[p] + 1;
		edges[clone] = edges[q];
		link[clone] = link[q];
		link[q] = clone;
		link[lastNode] = clone;

		while(edges[p][letter] == q) {
			edges[p][letter] = clone;
			p = link[p];
		}
	}

	void dfs(int32_t node, std::string s) {
		std::cout << s << '\n';

		for(auto &x : edges[node]) {
			dfs(x.second, s + x.first);
		}
	}
};

SuffixAutomaton sa;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;
	
	sa.init();
	for(auto &c : s) {
		sa.add_letter(c);
	}

	sa.dfs(0, "");
}

