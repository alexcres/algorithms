#ifndef ALGORITHMS_SINGLY_LIST_H
#define ALGORITHMS_SINGLY_LIST_H


class singly_list {
public:
	struct node {
		int data;
		node *next{nullptr};

		explicit node(int data);
	};

	~singly_list();

	void insert_head(node *&node);

	void push_head(int data);

	// node->next is the target
	[[nodiscard]] node *find(int data) const;

	void remove(node *&cur); // O(1)

	int peek(int index=0);

	void reverse();

private:
	node *head{nullptr};
	int length{0};
};

//10.2-6: join two list in O(1) time
/* any circular list will work
 * temp = h1->next;
 * h1->next = h2->next;
 * h2->next = temp;
 */

#endif //ALGORITHMS_SINGLY_LIST_H
