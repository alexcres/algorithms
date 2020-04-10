#ifndef ALGORITHMS_HANOI_H
#define ALGORITHMS_HANOI_H

#include <iostream>
//#include <math/math.h>
#include <thread>
#include <vector>

using namespace std;

enum color { yellow, purple, orange, blue };


class cube {
	public:
		explicit cube(double length, enum color color);

		double get_volume();

		double get_area();

		void set_length(double length);

		[[nodiscard]] double get_length() const;

		cube &operator=(const cube &other);

	private:
		double length;
		enum color color;
};

class stack {
	public:
		void push_back(const cube &cube);

		cube remove_top();

		[[nodiscard]] cube &peek_top() const;

		[[nodiscard]] unsigned size() const;

		// like to_string
		// grant a function in ostream access privated/protected member of stack
		friend std::ostream &operator<<(ostream &os, const stack &stack);

	private:
		vector<cube> cubes;
};

void stack::push_back(const cube &cube) {
	cubes.push_back(cube);
}

cube stack::remove_top() {
	cube top = peek_top();
	cubes.pop_back();
	return top;
}

cube &stack::peek_top() const {
	return const_cast<cube &>(cubes.back());
}

unsigned stack::size() const {
	return cubes.size();
}

std::ostream &operator<<(ostream &os, const stack &stack) {
	for (unsigned i = 0; i < stack.size(); ++i) {
		os << stack.cubes[i].get_length() << " ";
	}
	os << endl;
	return os;
}

class hanoi {
	public:
		hanoi();

		void solve();

		void solve2();

		friend std::ostream &operator<<(ostream &os, const hanoi &hanoi);

	private:
		vector<stack> stacks;

		void recur_move(unsigned bottom, unsigned top, stack &source, stack &spare, stack &target);

		void move(unsigned a, unsigned b);

		void move(stack &a, stack &b);

		void leagal_move(unsigned a, unsigned b);
};

hanoi::hanoi() {
	for (unsigned i = 0; i < 3; ++i) {
		stack stack;
		stacks.push_back(stack);
	}
	cube blue(4, color::blue);
	stacks[0].push_back(blue);
	cube orange(3, color::orange);
	stacks[0].push_back(orange);
	cube purple(2, color::purple);
	stacks[0].push_back(purple);
	cube yellow(1, color::yellow);
	stacks[0].push_back(yellow);
}

std::ostream &operator<<(ostream &os, const hanoi &hanoi) {
	for (unsigned i = 0; i < hanoi.stacks.size(); ++i) {
		os << "stack[" << i << "]: " << hanoi.stacks[i];
		// endl implemented in stack
	}
	return os;
}

void hanoi::solve() {
	while (stacks[2].size() != 4) {
		leagal_move(0, 1);
		leagal_move(0, 2);
		leagal_move(1, 2);
	}
}

void hanoi::move(unsigned a, unsigned b) {
	cube cube = stacks[a].remove_top();
	stacks[b].push_back(cube);
}

void hanoi::leagal_move(unsigned a, unsigned b) {
	if (stacks[a].size() == 0 && stacks[b].size() > 0) {
		move(b, a);
	} else if (stacks[a].size() > 0 && stacks[b].size() == 0) {
		move(a, b);
	} else if (stacks[a].size() > 0 && stacks[b].size() > 0) {
		if (stacks[a].peek_top().get_length() < stacks[b].peek_top().get_length()) {
			move(a, b);
		} else {
			move(b, a);
		}
	}

	cout << *this << endl;
}

void hanoi::solve2() {
	recur_move(
		0, stacks.size(),
		stacks[0],
		stacks[1],
		stacks[2]
	);
}

// range: bottom-top
void hanoi::recur_move(unsigned bottom, unsigned top, stack &source, stack &spare, stack &target) {
	if (bottom == top) {
		move(source, target);
		cout << *this << endl;
	} else {
		recur_move(bottom + 1, top, source, target, spare);
		recur_move(bottom, bottom, source, spare, target); // actual move
		recur_move(bottom + 1, top, spare, source, target);
	}
}

void hanoi::move(stack &a, stack &b) {
	b.push_back(a.remove_top());
}


double cube::get_volume() {
	return length * length * length;
}

double cube::get_area() {
	return length * length * 6;
}

void cube::set_length(double length) {
	if (length <= 0) {
		throw;
	}
	this->length = length;
}

cube &cube::operator=(const cube &other) {
	length = other.length;
	return *this;
}

double cube::get_length() const {
	return length;
}

cube::cube(double length, enum color color) : length{length}, color{color} {}


#endif //ALGORITHMS_HANOI_H
