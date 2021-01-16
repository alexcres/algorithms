#pragma once

#include <iostream>
//#include <math/math.h>
#include <thread>
#include <vector>

using namespace std;

enum Color { yellow, purple, orange, blue };


class Cube {
	public:
		explicit Cube(double length, enum Color color);

		double get_volume();

		double get_area();

		void set_length(double length);

		[[nodiscard]] double get_length() const;

		Cube &operator=(const Cube &other);

	private:
		double length;
		enum Color color;
};

class Stack {
	public:
		void push_back(const Cube &cube);

		Cube remove_top();

		[[nodiscard]] Cube &peek_top() const;

		[[nodiscard]] unsigned size() const;

		// like to_string
		// grant a function in ostream access privated/protected member of stack
		friend std::ostream &operator<<(ostream &os, const Stack &stack);

	private:
		vector<Cube> cubes;
};

void Stack::push_back(const Cube &cube) {
	cubes.push_back(cube);
}

Cube Stack::remove_top() {
	Cube top = peek_top();
	cubes.pop_back();
	return top;
}

Cube &Stack::peek_top() const {
	return const_cast<Cube &>(cubes.back());
}

unsigned Stack::size() const {
	return cubes.size();
}

std::ostream &operator<<(ostream &os, const Stack &stack) {
	for (unsigned i = 0; i < stack.size(); ++i) {
		os << stack.cubes[i].get_length() << " ";
	}
	os << endl;
	return os;
}

class Hanoi {
	public:
		Hanoi();

		void solve();

		void solve2();

		friend std::ostream &operator<<(ostream &os, const Hanoi &hanoi);

	private:
		vector<Stack> stacks;

		void recur_move(unsigned bottom, unsigned top, Stack &source, Stack &spare, Stack &target);

		void move(unsigned a, unsigned b);

		void move(Stack &a, Stack &b);

		void leagal_move(unsigned a, unsigned b);
};

Hanoi::Hanoi() {
	for (unsigned i = 0; i < 3; ++i) {
		Stack stack;
		stacks.push_back(stack);
	}
	Cube blue(4, Color::blue);
	stacks[0].push_back(blue);
	Cube orange(3, Color::orange);
	stacks[0].push_back(orange);
	Cube purple(2, Color::purple);
	stacks[0].push_back(purple);
	Cube yellow(1, Color::yellow);
	stacks[0].push_back(yellow);
}

std::ostream &operator<<(ostream &os, const Hanoi &hanoi) {
	for (unsigned i = 0; i < hanoi.stacks.size(); ++i) {
		os << "stack[" << i << "]: " << hanoi.stacks[i];
		// endl implemented in stack
	}
	return os;
}

void Hanoi::solve() {
	while (stacks[2].size() != 4) {
		leagal_move(0, 1);
		leagal_move(0, 2);
		leagal_move(1, 2);
	}
}

void Hanoi::move(unsigned a, unsigned b) {
	Cube cube = stacks[a].remove_top();
	stacks[b].push_back(cube);
}

void Hanoi::leagal_move(unsigned a, unsigned b) {
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

void Hanoi::solve2() {
	recur_move(
		0, stacks.size(),
		stacks[0],
		stacks[1],
		stacks[2]
	);
}

// range: bottom-top
void Hanoi::recur_move(unsigned bottom, unsigned top, Stack &source, Stack &spare, Stack &target) {
	if (bottom == top) {
		move(source, target);
		cout << *this << endl;
	} else {
		recur_move(bottom + 1, top, source, target, spare);
		recur_move(bottom, bottom, source, spare, target); // actual move
		recur_move(bottom + 1, top, spare, source, target);
	}
}

void Hanoi::move(Stack &a, Stack &b) {
	b.push_back(a.remove_top());
}


double Cube::get_volume() {
	return length * length * length;
}

double Cube::get_area() {
	return length * length * 6;
}

void Cube::set_length(double length) {
	if (length <= 0) {
		throw;
	}
	this->length = length;
}

Cube &Cube::operator=(const Cube &other) {
	length = other.length;
	return *this;
}

double Cube::get_length() const {
	return length;
}

Cube::Cube(double length, enum Color color) : length{length}, color{color} {}
