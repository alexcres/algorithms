#ifndef ALGORITHMS_STACKABLE_H
#define ALGORITHMS_STACKABLE_H
template<typename E>
class stackable {
public:
	[[nodiscard]] virtual bool is_empty() const = 0;

	virtual void push(E const &elem) = 0;

	virtual E pop() = 0;
	// class is just an array
	// poly class is just a point from parent to child
	// you want to call children's constructor not parents'
	// hence make it virtual
	virtual ~stackable() = default;

};
#endif //ALGORITHMS_STACKABLE_H
