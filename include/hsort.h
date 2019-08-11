#include <iostream>
#include <cmath>
#include <vector>

template <typename T, typename Comparator>
void pop(std::vector<T>& data, size_t& effsize, Comparator& c);

template <typename T, typename Comparator>
void make_heap(std::vector<T>& data, Comparator& c);

template <typename T, typename Comparator>
void trickledown(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c);



template <typename T, typename Comparator>
void hsort(std::vector<T>& data, Comparator c = Comparator()){

	make_heap(data, c);
	
	size_t effsize = data.size();
	for(size_t i = 0; i<data.size(); i++){
		pop(data, effsize, c);
	}

	for(size_t i=0; i<data.size()/2; i++){
		T temp = data[i];
		data[i] = data[data.size()-1-i];
		data[data.size()-1-i] = temp;
	} 
}

template <typename T, typename Comparator>
void pop(std::vector<T>& data, size_t& effsize, Comparator& c){
	if(effsize > 0){
		T temp = data[0];
		data[0] = data[--effsize];
		data[effsize] = temp;

		trickledown(data, 0, effsize, c);
	}
}

template <typename T, typename Comparator>
void make_heap(std::vector<T>& data, Comparator& c){
	for( int i = (int)((data.size()-1)/2); i >= 0; i--){ 
		trickledown(data, i, data.size(), c);
	}
}


template <typename T, typename Comparator>
void trickledown(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c){

   size_t child1 = 2*loc + 1;
   size_t child2 = 2*loc + 2;

   if( child1 >= effsize ){ return; } //if loc is leaf node

   size_t smallerchild = child1;

   if( child2 < effsize ){
   	if( c(data[child2] , data[child1]) ){
   		smallerchild = child2;
   	}
   }
   if (c(data[smallerchild], data[loc])){
   	T temp = data[loc];
   	data[loc] = data[smallerchild];
   	data[smallerchild] = temp;

	
    trickledown(data, smallerchild, effsize, c);
   }
}
