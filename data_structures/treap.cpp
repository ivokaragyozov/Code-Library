#include <bits/stdc++.h>

std::mt19937 mt(69);

struct Vertex {
	int32_t key, prior, sum, val, lazy;
	Vertex *l, *r;

	Vertex() {}
	Vertex(int32_t _key) : key(_key), prior(mt()), sum(0), val(0), lazy(0), l(nullptr), r(nullptr) {}

	void push_lazy() {
		val += lazy;

		if(l != nullptr) {
			l->lazy += lazy;
		}
		if(r != nullptr) {
			r->lazy += lazy;
		}

		lazy = 0;
	}

	void update() {
		sum = val;

		if(l != nullptr) {
			sum += l->sum;
		}
		if(r != nullptr) {
			sum += r->sum;
		}
	}
};

Vertex *root = nullptr;

std::pair< Vertex*, Vertex* > split(Vertex *x, int32_t key) {
	if(x == nullptr) {
		return { nullptr, nullptr };
	}

	x->push_lazy();

	if(x->key <= key) {
		auto aux = split(x->r, key);
		x->r = aux.first;
		
		x->update();

		return { x, aux.second };
	}
	else {
		auto aux = split(x->l, key);
		x->l = aux.second;

		x->update();

		return { aux.first, x };
	}
}

Vertex* merge(Vertex *x, Vertex *y) {
	if(x == nullptr) {
		return y;
	}
	if(y == nullptr) {
		return x;
	}

	x->push_lazy();
	y->push_lazy();

	if(x->prior >= y->prior) {
		x->r = merge(x->r, y);
		x->update();
		return x;
	}
	else {
		y->l = merge(x, y->l);
		y->update();
		return y;
	}
}

Vertex* insert(Vertex *x, int32_t key) {
	if(x == nullptr) {
		x = new Vertex(key);
		return x;
	}
	
	auto aux = split(x, key);
	aux.first = merge(aux.first, new Vertex(key));
	x = merge(aux.first, aux.second);
	return x;
}

Vertex* remove(Vertex *x, int32_t key) {
	auto aux1 = split(x, key);
	auto aux2 = split(aux1.first, key - 1);
	x = merge(aux2.first, aux1.second);
	return x;
}

void add_on_interval(Vertex *x, int32_t low, int32_t high, int32_t val) {
	auto aux1 = split(x, low - 1);
	auto aux2 = split(aux1.second, high);

	aux2.first->lazy += val;

	aux1.second = merge(aux2.first, aux2.second);
	x = merge(aux1.first, aux1.second);
}

int32_t get_sum_on_interval(Vertex *x, int32_t low, int32_t high) {
	auto aux1 = split(x, low - 1);
	auto aux2 = split(aux1.second, high);

	int32_t ans = (aux2.first == nullptr ? 0 : aux2.first->sum);

	aux1.second = merge(aux2.first, aux2.second);
	x = merge(aux1.first, aux1.second);

	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int32_t q;
	std::cin >> q;

	for(int32_t i = 0; i < q; i++) {
		std::string type;
		std::cin >> type;

		if(type == "insert") {
			int32_t key;
			std::cin >> key;

			root = insert(root, key);
		}
		else if(type == "remove") {
			int32_t key;
			std::cin >> key;

			root = remove(root, key);
		}
		else if(type == "add") {
			int32_t low, high, val;
			std::cin >> low >> high >> val;

			add_on_interval(root, low, high, val);
		}
		else {
			int32_t low, high;
			std::cin >> low >> high;

			std::cout << get_sum_on_interval(root, low, high) << '\n';
		}
	}
}

