#pragma once

template<typename E>
class Stackable {
public:
	[[nodiscard]] virtual bool is_empty() const = 0;

	virtual void push(E const &elem) = 0;

	virtual E pop() = 0;
	// class is just an array
	// poly class is just a point from parent to child
	// you want to call children's constructor not parents'
	// hence make it virtual
	virtual ~Stackable() = default;

};
