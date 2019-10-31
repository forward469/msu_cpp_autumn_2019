#include <cstdlib>
#include <iostream>
using namespace std;

class LinearAllocator{
    char* start;
    char* current;
    size_t MaxSize;
    size_t Size;

public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();    
    size_t maxsize();
    size_t currentsize();
    ~LinearAllocator(); 
};

LinearAllocator::LinearAllocator(size_t maxSize){
    MaxSize = maxSize;
    start = (char*) malloc(sizeof(char) * maxSize);
    if (start == nullptr){
        throw runtime_error("ERROR : Memory is not allocated.");
    }
    current = start;
    Size = 0;
}

char* LinearAllocator::alloc(size_t size){
    if (start == nullptr){
        throw runtime_error("ERROR : Memory is not allocated.");
        return nullptr;
    }
    if (size+Size>MaxSize){ 
        throw runtime_error("ERROR : Required size is greater MaxSize.");
        return nullptr;
    }
    current += size;
    Size += size;
    return current;
}

void LinearAllocator::reset(){
    Size = 0;
    current = start;
}

size_t LinearAllocator::maxsize(){
    return MaxSize;
}

size_t LinearAllocator::currentsize(){
    return Size;
}

LinearAllocator::~LinearAllocator(){
    free(start);
    MaxSize = 0;
    Size = 0;
}

int main(){

    try{
        LinearAllocator Allocator(30);
        cout<<Allocator.maxsize()<< endl;
        char* a = Allocator.alloc(7);
        cout<<"current size = "<<Allocator.currentsize()<<endl;
        cout << (int64_t) a << endl;
        a = Allocator.alloc(10);
        cout<<"current size = "<<Allocator.currentsize()<<endl;
        cout << (int64_t) a << endl;
        Allocator.reset();
        cout<<"Max size after reset = "<<Allocator.maxsize()<<endl;
        cout<<"current after reset = "<<Allocator.currentsize()<<endl;
        char* b = Allocator.alloc(3);
        cout<<"curr size = "<<Allocator.currentsize()<<endl;
        cout << (int64_t) b << endl;
    }
    catch(runtime_error & error){
        cerr<<error.what()<<endl;
        return 1;
    }

    return 0;

}