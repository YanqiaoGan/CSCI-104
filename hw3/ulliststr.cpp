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

/**
   * Copy constructor (initiale list with deep copy of `other`)
   *
   * It is fine to consolodate the contents of `other` to start at the head
   *  Item's location 0.
   *
   * MUST RUN in O(n) where n is the size of other
   */
  ULListStr::ULListStr (const ULListStr& other){
  	this->head_ = NULL;
  	this->tail_ = NULL;
  	this->size_ = 0;
  	appendContents(other);
  }

  /**
   * Assignment Operator (replace current contents with deep copy of `other`)
   *  Note: It is fine to deallocate the current contents and construct
   *  a whole new set of internal Items maintaining the same internal data
   *  element positions, or consolodating the elements to start at the head
   *  Item's location 0.
   *
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other` and not O(n^2) or O(m^2)
   */
  ULListStr& ULListStr::operator= (const ULListStr& other){
  	clear();
  	appendContents(other);
  	return *this;
  }

  /**
   * Concatenation operator.
   * Returns a separate list consisting of other appended to this.
   * Does not modify this nor other.
   *
   *  Note: It is fine to consolodate the elements from both lists 
   *  to start at the returned list's head Item's location 0.
   *
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other`
   */
  ULListStr ULListStr::operator+ (const ULListStr& other) const{
  	ULListStr result;
  	result.appendContents(*this);
  	result.appendContents(other);
  	return result;
  }


/**
   * Remove the last 'num' strings from the **back** of this list
   * 
   * Returns a reference to this list.
   *
   *  MUST RUN in O(num)
   */
  ULListStr& ULListStr::operator-= (size_t num){
  	for( size_t i = 0; i < num; i ++){
  		if(empty()){
  			break;
  		}
  		pop_back();
  	}
  	return *this;
  }

  /**
   * Const access Operator of element at location/position: loc
   */
  std::string const & ULListStr::operator[] (size_t loc) const{
  	return get(loc);
  }


  /**
   * Non-const access Operator of element at location/position: loc
   */
  std::string & ULListStr::operator[] (size_t loc){
  	return get(loc);
  }

  /*
   * Appends the contents of `other` to the end of `this` list
   * allocating new Items and updating pointers and first/last
   * indices of `this` as necessary.
   *
   * Does not modify `other`.
   *
   * Runs in O(m) where m is the size of `other`
   */
  void ULListStr::appendContents(const ULListStr& other){
  	for(size_t i = 0; i < other.size(); i++){
  		push_back(other.get(i));
  	}
  }
