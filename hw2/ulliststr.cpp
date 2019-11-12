#include <cstddef>
#include <stdexcept>
#include <string>
#include <iostream>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(NULL == ptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

  /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val){
	if(tail_== NULL){
		Item* recent = new Item();
		recent->prev = NULL;
		recent->next = NULL;
		recent->val[0]= val;
		tail_ = recent;
		head_ = recent;
	}else{
		if(ARRSIZE == tail_->last){
			Item* recent = new Item();
			recent->prev = tail_;
			recent->next = NULL;
			tail_->next = recent;
			recent->val[0] = val;
			tail_ = recent;
		}else{
            tail_->val[tail_->last] = val;
		}
	}
	tail_->last++;
	size_++;
}

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_back(){
	if(tail_ == NULL){
		return;
	}else{
		if(tail_->last == 1){
			Item* temp = tail_;
			if(tail_->prev == NULL){
				head_ = NULL;
				tail_ = NULL;
			}else{
				tail_ = tail_->prev;
				tail_->next = NULL;
			}
			delete temp;
		}else{
			tail_->last--;			
		}
		size_--;
	}
}
  
  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
void ULListStr::push_front(const std::string& val){
	if(head_==NULL){
		Item* recent = new Item();
		recent->prev = NULL;
		recent->next = NULL;
		recent->val[ARRSIZE-1]= val;
		tail_ = recent;
		head_ = recent;
		head_->last = ARRSIZE;
		head_->first = ARRSIZE-1;
	}else{
		if(head_->first == 0){
			Item* recent = new Item();
			recent->next = head_;
			recent->prev = NULL;
			recent->val[ARRSIZE-1] = val;
			head_->prev = recent;
			head_ = recent;
			head_->last = ARRSIZE;
			head_->first = ARRSIZE-1;
		}else{
			head_->val[head_->first-1] = val;
			head_->first--;
		}
	}
	size_++;
}

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front(){
	if(head_ == NULL){
		return;
	}else{
		if(head_->first == ARRSIZE-1){
			Item* current = head_;
			if(head_->next == NULL){
				head_=NULL;
				tail_=NULL;
			}else{
				head_=head_->next;
				head_->prev = NULL;
			}
			delete current;
		}else{
			head_->first++;
		}
		size_--;
	}
}
  
  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::back() const{
	return tail_->val[tail_->last-1];
}

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::front() const{
	return head_->val[head_->first];
}

  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */

std::string* ULListStr::getValAtLoc(size_t loc) const{
	Item* temp = head_;
	int num = (int)head_->last-(int)head_->first;
	if(head_ == NULL){
		return NULL;
	}else if (head_->next == NULL || (size_t)num > loc){
		if(head_->first + loc < ARRSIZE){
			int index = (int)head_->first + (int)loc;
			std::string* ptr = &(head_->val[index]);
			return ptr;
		}else{
			return NULL;
		}
	}else{
		int count = 0;
		while((size_t)count <= loc){
			num = (int)temp->last-(int)temp->first;
			count += num;
			if((size_t)count > loc){
				count -= num;
				int index = (int)loc-count;
				std::string* ptr = &(temp->val[index]);
				return ptr; 
			}	
			temp = temp->next;
		}	
	}
	return NULL;
}

