#include <bits/stdc++.h>

// MAX_S is the maximum sum of all patterns
const int32_t MAX_S = 1e5;

struct Vertex {
	int32_t failLink, successLink;
	std::map< char, int32_t > edges;
	std::vector< int32_t > endingWords;

	Vertex() : failLink(0) {}
};

struct Aho {
	int32_t nxtV;
	Vertex v[MAX_S + 5];	
	
	Aho() : nxtV(1) {}

	void add_word(const std::string &s, int32_t wordId) {		
		int32_t u = 0;

		for(auto &x : s) {
			if(v[u].edges.count(x) == 0) {
				v[u].edges[x] = nxtV++;
			}

			u = v[u].edges[x];
		}

		v[u].endingWords.push_back(wordId);
	}

	void build_fail_links() {
		std::queue< int32_t > q;
		
		q.push(0);
		while(!q.empty()) {
			int32_t u = q.front();
			q.pop();

			for(auto &x : v[u].edges) {
				int32_t p = v[u].failLink;

				while(p != 0 && v[p].edges.count(x.first) == 0) {
					p = v[p].failLink;
				}

				if(v[p].edges.count(x.first) != 0 && p != u) {
					v[x.second].failLink = v[p].edges[x.first];
				}

				q.push(x.second);
			}
		}
	}

	void build_success_links() {
		std::queue< int32_t > q;
		
		q.push(0);
		while(!q.empty()) {
			int32_t u = q.front();
			q.pop();

			int32_t p = v[u].failLink;
			while(p != 0 && v[p].endingWords.empty()) {
				p = v[p].failLink;
			}
			v[u].successLink = p;
		
			for(auto &x : v[u].edges) {
				q.push(x.second);
			}
		}
	}

	std::vector< std::pair< int32_t, int32_t > > get_matches(const std::string &s) {
		std::vector< std::pair< int32_t, int32_t > > matches;
		
		int32_t u = 0;
		for(int32_t i = 0; i < (int32_t) s.size(); i++) {
			auto &c = s[i];

			if(v[u].edges.count(c) == 0) {
				u = v[u].failLink;
			}

			u = v[u].edges[c];

			if(!v[u].endingWords.empty()) {
				for(auto &p : v[u].endingWords) {
					matches.push_back({ i, p });
				}
			}

			int32_t q = v[u].successLink;
			while(q != 0) {
				for(auto &p : v[q].endingWords) {
					matches.push_back({ i, p });
				}

				q = v[q].successLink;
			}
		}
		
		return matches;
	}
};

Aho aho;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;

	int32_t n;
	std::cin >> n;

	for(int32_t i = 0; i < n; i++) {
		std::string t;
		std::cin >> t;

		aho.add_word(t, i);
	}

	aho.build_fail_links();
	aho.build_success_links();
	
	auto matches = aho.get_matches(s);
	
	for(auto &x : matches) {
		std::cout << x.first << " " << x.second << '\n';
	}
}

