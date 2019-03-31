#include <bits/stdc++.h>

std::vector< int32_t > compute_lps(std::string &s) {
	std::vector< int32_t > lps(s.size());

	lps[0] = 0;
	int32_t k = 0;
	for(int32_t i = 1; i < (int32_t) s.size(); i++) {
		while(k > 0 && s[i] != s[k]) {
			k = lps[k - 1];
		}

		if(s[i] == s[k]) {
			k++;
		}

		lps[i] = k;
	}

	return lps;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s, t;
	std::cin >> s >> t;

	std::vector< int32_t > lps = compute_lps(t);
	
	int32_t indT = 0;
	for(int32_t i = 0; i < (int32_t) s.size(); i++) {
		while(indT > 0 && s[i] != t[indT]) {
			indT = lps[indT - 1];
		}
	
		if(s[i] == t[indT]) {
			indT++;
		}

		if(indT == (int32_t) t.size()) {
			std::cout << i - t.size() + 1 << '\n';
			indT = lps[indT - 1];
		}
	}
}

