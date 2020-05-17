#pragma once

class array_queue {
public:
	void enqueue(int data);

	int dequeue();

	[[nodiscard]] bool is_empty() const { return length == 0; }

	[[nodiscard]] int get_length() const { return length; }

	~array_queue();

private:
	int capacity{2};
	int *queue{new int[capacity]};
	int head{0};
	int tail{0};
	int length{0};

	bool shrinkable();

	void resize(int new_cap);
};
