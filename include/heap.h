#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include "tagdata.h"
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

 private:
    /// Add whatever helper functions and store_ members you need below
    void heapify(const size_t loc);
    void trickleUp(const size_t loc);

 private:
   /// store_ members - These should be sufficient
    std::vector< T > store_;
    int m_;
    PComparator c_;
    KComparator kcomp;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{

}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push( const T& item)
{
  store_.push_back(item);
  keyToLocation_.insert(std::make_pair(item, store_.size()-1));
  trickleUp(store_.size()-1);
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
    if( c_(old, newVal) ){
        //|| !kcomp(old, newVal)){
        return;
    }
    if(keyToLocation_.find(old) == keyToLocation_.end()){
        throw 0;
    }

    size_t i = keyToLocation_[old];
    if(i >= store_.size()){
        return;
    }
    store_[i] = newVal;
    trickleUp(i);
}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    if(empty()){
        throw std::logic_error("can't pop an empty heap");
    }
    keyToLocation_.erase(store_[0]);
    store_[0] = store_[store_.size()-1];
    keyToLocation_[store_[0]] = 0;
    store_.pop_back();
    heapify(0);

}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::heapify(const size_t loc){
    if( m_*loc + 1 >= store_.size() ){ return; } //if loc is leaf node

    size_t smallerchild = m_*loc + 1;

    for(int i=1; i<=m_; i++){
        if( m_*loc+i < store_.size()){
            if( c_(store_[m_*loc+i] , store_[smallerchild]) ){
                smallerchild = m_*loc+i;
            }
        }
    }
    if (c_(store_[smallerchild], store_[loc])){
    T temp = store_[loc];
    store_[loc] = store_[smallerchild];
    store_[smallerchild] = temp;

    keyToLocation_[temp] = smallerchild;
    keyToLocation_[store_[smallerchild]] = loc;

    heapify(smallerchild);
   }
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleUp(const size_t loc){
    if((int)loc -1 < 0){ return; }
  int parent = (loc-1)/m_;

  if( c_(store_[loc], store_[parent]) ){
    T temp = store_[loc];
    store_[loc] = store_[parent];
    store_[parent] = temp;
    keyToLocation_[store_[loc]] = loc;
    keyToLocation_[store_[parent]] = parent;
    trickleUp(parent);
  }
}



#endif

