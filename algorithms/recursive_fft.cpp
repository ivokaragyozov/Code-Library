#include <bits/stdc++.h>

const double PI = acos(-1);

void print_polynomial(const std::vector< int32_t > &p) {
	for(auto &x : p) {
		std::cout << x << " ";
	}
	std::cout << '\n';
}

void fft(std::vector< std::complex< double > > &a, bool invert) {
	int32_t n = a.size();
	if(n == 1) {
		return;
	}

	std::vector< std::complex< double > > a0(n / 2), a1(n / 2);
	for(int32_t i = 0; i < n / 2; i++) {
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}

	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * PI / n * (invert ? -1 : 1);
	std::complex< double > w(1), wn(cos(ang), sin(ang));
	for(int32_t i = 0; i < n / 2; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];

		if(invert) {
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}

		w *= wn;
	}
}

std::vector< int32_t > multiply(const std::vector< int32_t > &a, const std::vector< int32_t > &b) {
	std::vector< std::complex< double > > fa(a.begin(), a.end()), fb(b.begin(), b.end());
	
	int32_t n = 1;
	while(n < a.size() + b.size()) {
		n <<= 1;
	}

	fa.resize(n, 0);
	fb.resize(n, 0);

	fft(fa, false);
	fft(fb, false);
	
	for(int32_t i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}

	fft(fa, true);
	
	std::vector< int32_t > res(n);
	for(int32_t i = 0; i < n; i++) {
		res[i] = round(fa[i].real());	
	}

	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int32_t n, m;
	std::cin >> n >> m;
	
	n++;
	m++;
	std::vector< int32_t > a(n, 0), b(m, 0);
	
	for(int32_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	for(int32_t i = 0; i < m; i++) {
		std::cin >> b[i];
	}

	auto res = multiply(a, b);
	res.resize(a.size() + b.size() - 1);
	print_polynomial(res);
}

