#ifndef unrolledLL_h_
#define unrolledLL_h_

#include <cassert>
#include<iostream>
const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS

/*same node class except instead of one value, it will hold an array of values
contains an integer to represent the number of values inside it right now*/
template <class T>
class Node 
{
  public:
    Node() : next_(NULL), prev_(NULL) {}
    Node(const T& v) : num_elements(1), next_(NULL), prev_(NULL) {elements[0] = v;}

    // REPRESENTATION
    int num_elements;
    Node<T>* next_;
    Node<T>* prev_;
    T elements[NUM_ELEMENTS_PER_NODE];
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------

// LIST ITERATOR
template <class T>
class list_iterator 
{
  public:
    //constructor
    list_iterator(Node<T>* p=NULL) : ptr_(p) {}
    // dereferencing operator gives pointer to the current node plus the current offset
    T& operator*()  { return ptr_->elements[offset];  }

    /*increment operators will advance to next node when at the end of the array
    otherwise, it will just increment offset*/
    list_iterator<T>& operator++() 
    { // pre-increment, e.g., ++iter
      if(this->offset == this->ptr_->num_elements-1)
      {
        offset = 0;  
        ptr_ = ptr_->next_;
        return *this;
      }
      else
      {
        ++offset;
        return *this;
      }
    }
    list_iterator<T> operator++(int) 
    { // post-increment, e.g., iter++
      if (this->offset >= this->ptr_->num_elements-1)
      {
        offset = 0;
        list_iterator<T> temp(*this);
        ptr_ = ptr_->next_;
        return temp;
      }
      else
      {
        list_iterator<T> temp(*this);
        ++offset;
        return temp;
      }
    }
    /*decrement operators operate the same way, except when they move to a previous node, 
    offset will be set to 5*/
    list_iterator<T>& operator--() 
    { // pre-decrement, e.g., --iter
      if(this->offset == 0)
      {
        ptr_ = ptr_->prev_;
        offset = 5;
        return *this;
      }
      else
      {
        --offset;
      }
    }
    list_iterator<T> operator--(int) 
    { // post-decrement, e.g., iter--
      list_iterator<T> temp(*this);
      if(this->offset == 0)
      {
        ptr_ = ptr_->prev_;
        offset = 5;
      }
      else
      {
        offset --;
      }
      return temp;
    }
    // the dslist class needs access to the private ptr_ member variable
    friend class UnrolledLL<T>;

    // Comparions operators are straightforward
    bool operator==(const list_iterator<T>& r) const {return ptr_ == r.ptr_ && offset == r.offset;}
    bool operator!=(const list_iterator<T>& r) const {return ptr_ != r.ptr_ || offset != r.offset;}
  private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int offset = 0;   //offset in array
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL 
{
  public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
    UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
    UnrolledLL& operator= (const UnrolledLL<T>& old);
    ~UnrolledLL() { destroy_list(); }

    typedef list_iterator<T> iterator;

    // simple accessors & modifiers
    unsigned int size() const { return size_; }
    bool empty() const { return head_ == NULL; }
    void clear() { destroy_list(); }

    // read/write access to contents
    const T& front() const { return head_->elements[0];  }
    T& front() { return head_->elements[0]; }
    const T& back()  const { return tail_->elements[tail_->num_elements-1]; }
    T& back() { return tail_->elements[tail_->num_elements-1]; }

    // modify the linked list structure
    void push_front(const T& v);
    void pop_front();
    void push_back(const T& v);
    void pop_back();
    void print(std::ostream& out);
    iterator erase(iterator itr);
    iterator insert(iterator itr, const T& v);
    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(NULL); }

  private:
    // private helper functions
    void copy_list(const UnrolledLL<T>& old);
    void destroy_list();

    //REPRESENTATION
    Node<T>* head_;
    Node<T>* tail_;
    unsigned int size_;
};

// -----------------------------------------------------------------
// Implementation, very similar to DSList with some functions being exactly the same

//same as ds list
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) 
{
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}
/*it first checks if the list isn't empty. If it is empty, it will create a new
node, set to head and tail, and put in the value v. If it isn't empty, it will only 
create a new node if the current node is full. Otherwise it will just add v to the current 
node*/
template <class T>
void UnrolledLL<T>::push_front(const T& v) 
{
  if(head_ != NULL)
  {
    if(head_->num_elements == NUM_ELEMENTS_PER_NODE)
    {
      Node<T>* newp = new Node<T>(v);
      newp->next_ = head_;
      head_->prev_ = newp;
      head_ = newp;
      ++size_;
    }
    else
    {
      for(int i = head_->num_elements; i != 0; --i)
      {
        head_->elements[i] = head_->elements[i - 1];
      }
      head_->elements[0] = v;
      ++size_;
      ++head_->num_elements;
    }
  }
  else
  {
    Node<T>* newp = new Node<T>(v);
    newp->next_ = NULL;
    head_ = newp;
    tail_ = head_;
    ++size_;
  }
}
/*Checks if node needs to be removed. If node does not need to be removed, it will
shift all values to the left by one. If it does need to be removed, it will delete the head
and set the next node to the new head. if there is only one node left, then it will set
all pointers to null. If the list is already null, it will do nothing.*/
template <class T>
void UnrolledLL<T>::pop_front() 
{
  if(head_ == NULL){}

  else if(head_->num_elements == 1)
  {
    if(head_ == tail_)
    {
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else
    {
      Node<T>* temp = head_;
      head_ = head_->next_;
      head_->prev_ = NULL;
      delete temp;
    }
    --size_;
  }
  else
  {
    for(int i = 1; i != head_->num_elements; ++i)
    {
      head_->elements[i-1] = head_->elements[i];
    }
    --head_->num_elements;
    --size_;
  }
}
/*Very similar to the DS list push back, it will perform the same functionality if there needs to be a new
node added. If not, it will simply add to the current node, and increment the number of elements
*/
template <class T>
void UnrolledLL<T>::push_back(const T& v) 
{
  if(tail_ && tail_->num_elements != NUM_ELEMENTS_PER_NODE)
  {
    tail_->elements[tail_->num_elements] = v;
    ++tail_->num_elements;
  }
  else
  {
    Node<T>* newp = new Node<T>(v);
    // special case: initially empty list
    if (!tail_) 
    {
      head_ = tail_ = newp;
    } 
    else 
    {
      // normal case: at least one node already
      newp->prev_ = tail_;
      tail_->next_ = newp;
      tail_ = newp;
    }
  }
  ++size_;
}
/*pop back will perform the same as DS list if there needs to be a node
removed. If not, it will just decrement the number of elements and the 
last element will now be ignored until it is rewritten or the node is deleted.*/
template <class T>
void UnrolledLL<T>::pop_back() 
{
  if(!tail_){}

  else if(tail_->num_elements == 1)
  {
    if(head_ == tail_)
    {
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else
    {
      Node<T>* temp = tail_->prev_;
      temp->prev_ = tail_->prev_->prev_;
      delete tail_;
      tail_ = temp;
      tail_->next_ = NULL;
    }
    --size_;
  }
  else
  {
    --size_;
    --tail_->num_elements;
  }
}

// == operator, exactly the same as the DS list
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) 
{
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) 
  {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }
/*erase will work exactly the same as ds list if there needs to be a node erased.
If not, it will shift everything from the offset point back by one.*/
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) 
{
  assert (size_ > 0);
  --size_;
  if(itr.ptr_->num_elements == 1)
  {
    iterator result(itr.ptr_->next_);
    // One node left in the list.
    if (itr.ptr_ == head_ && head_ == tail_) 
    {
      head_ = tail_ = 0;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == head_) 
    {
      head_ = head_->next_;
      head_->prev_ = 0;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == tail_) 
    {
      tail_ = tail_->prev_;
      tail_->next_ = 0;
    }
    // Normal remove
    else 
    {
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete itr.ptr_;
    return result;
  }
  else
  {
    for(int i = itr.offset; i != itr.ptr_->num_elements-1; ++i)
    {
      itr.ptr_->elements[i] = itr.ptr_->elements[i+1];
    }
    --itr.ptr_->num_elements;
    if(itr.offset >= itr.ptr_->num_elements)
    {
      itr++;

    }
    return itr;
  }
}

/*If no node needs to be created, it will move everything after the offset to the right by one
and set the element at hte offset to the value needed to be inserted. If there needs to be a new node,
it will take everything before the offset, and put it in a new node. It erases all the elements before the offset
in the current node, and connects the new node to the list behind the current node. The value v is set to the end of the new node.*/
template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) 
{
  ++size_ ;
  if(itr.ptr_->num_elements == NUM_ELEMENTS_PER_NODE)
  {
    Node<T>* p = new Node<T>(itr.ptr_->elements[0]);
    if(itr.offset > 0)
    {
      for(int i = 1 ; i != itr.offset; ++i)
      {
        p->elements[i] = itr.ptr_->elements[i];
        ++p->num_elements;
      }
      ++p->num_elements;
    }
    p->elements[itr.offset] = v;
    for(int i = 0; i != itr.ptr_->num_elements-itr.offset; ++i)
    {
      itr.ptr_->elements[i] = itr.ptr_->elements[i+itr.offset];
    }
    itr.ptr_->num_elements -= itr.offset;
    p->prev_ = itr.ptr_->prev_;
    p->next_ = itr.ptr_;
    itr.ptr_->prev_ = p;
    if (itr.ptr_ == head_)
      head_ = p;
    else
      p->prev_->next_ = p;

    iterator ret_it = iterator(p);
    ret_it.offset = itr.offset;
  return ret_it;
  }
  else
  {
    ++itr.ptr_->num_elements;
    for(int i = itr.ptr_->num_elements-1; i != itr.offset; --i)
    {
      itr.ptr_->elements[i] = itr.ptr_->elements[i-1];
    }
    itr.ptr_->elements[itr.offset] = v;
    return itr;
  }
}

/*copy_list functions almost exactly the same as the original copy list except now it copys
all array values over instead of just one value*/
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) 
{
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) 
  {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>();
  for(int i = 0; i != old.head_->num_elements; ++i)
  {
    this->head_->elements[i] = old.head_->elements[i];
  }
  this->head_->num_elements = old.head_->num_elements;
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) 
  {
    tail_->next_ = new Node<T>();
    for(int i = 0; i != old_p->num_elements; ++i)
    {
      this->tail_->next_->elements[i] = old_p->elements[i];
    }
    this->tail_->next_->num_elements = old_p->num_elements;
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}
//destroys all nodes in the list starting from the head
template <class T>
void UnrolledLL<T>::destroy_list() 
{
  Node<T>* i = head_;
  while(head_ != NULL)
  {
    head_ = i->next_;
    delete i;
    i = head_;
  }
  size_ = 0;
}
//print function that prints out all elements in each node along with the nodes current size.
template <class T>
void UnrolledLL<T>::print( std::ostream& out)
{
  if(head_ == NULL && tail_ == NULL)
  {
    out << "EMPTY LIST" << std::endl;
  }
  for (UnrolledLL<T>::iterator itr = this->begin(); itr != this->end(); itr++)
  {
    if(itr.offset == 0)
    {
      out <<  "node:[" << itr.ptr_->num_elements << "] ";
    }
    out << *itr << " ";
    if(itr.offset == itr.ptr_->num_elements-1)
    {
      out << std::endl;
    }
  }
  out << std::endl;
}

#endif