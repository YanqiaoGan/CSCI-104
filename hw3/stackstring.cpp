#include "stackstring.h"

/**
 * Default constructor
 */
StackString::StackString(){
	ULListStr stack;
	list_ = stack;
}

/**
 * Destructor
 */
StackString::~StackString(){
	list_.clear();
}

/**
 * Returns true if the stack is empty, false otherwise
 */
bool StackString::empty() const{
	return list_.empty();
}

/**
 * Returns the number of elements on the stack
 */
size_t StackString::size() const{
	return list_.size();
}

/**
 * Pushes a new value, val, onto the top of the stack
 */
void StackString::push(const std::string& val){
	list_.push_back(val);
}

/**
 * Returns the top value on the stack.
 * If the stack is empty, the correct behavior is to throw
 * an exception: use ULListStr::get to achieve this rather
 * than calling ULListStr::back() or ULListStr::front().
 */
const std::string& StackString::top() const{
	return list_.back();
}

/**
 * Removes the top element on the stack.
 * Should do nothing if the stack is empty.
 */
void StackString::pop(){
	list_.pop_back();
}
