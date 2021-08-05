//
// Created by subrahmanyam on 03/08/21.
//

#ifndef CH02_LISTING_2_8_H
#define CH02_LISTING_2_8_H
#include "headers.h"

void create_random_data(std::vector<int>& input){
    input.reserve(250);
    for(int i =0; i<250; ++i){
        input.push_back(i);
    }
}

template<typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator start, Iterator last, T& result){
        result = std::accumulate(start, last, result);
        std::cout<<"\n inside count::"<<result<<"\t distance is::"<<std::distance(start, last);
    }
};


void list2_8_main(){
    std::vector<int> mydata;
    unsigned long  count = 0;
    create_random_data(mydata);
    using iter = std::vector<int>::iterator;
    auto length = mydata.size();
    unsigned long const block_size = 25;                                 // Assign 25 elements per thread so
    unsigned int num_threads = (length+block_size-1)/block_size; // to protect if length < 25
    std::vector<std::thread> mythreads(num_threads -1);
    iter  start = mydata.begin();
    std::vector<int> vcount(num_threads);
    iter end = start;

    for ( auto i =0; i<num_threads-1; ++i){
        end = start;
        std::advance(end, block_size);
        mythreads.push_back({std::thread(accumulate_block<iter, unsigned long >(),start,end, std::ref(vcount[i]))});
        start = end;
    }

    end = mydata.end();
    //accumulate_block<iter, unsigned long>()(start,end, vcount.at(num_threads-1));

    for_each(mythreads.begin(), mythreads.end(), std::mem_fn(&std::thread::join));
    std::cout<<"\n The count is::"<<std::accumulate(vcount.begin(), vcount.end(),count);


}
#endif //CH02_LISTING_2_8_H
