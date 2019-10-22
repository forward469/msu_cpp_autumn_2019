#include <cstdlib>
#include <iostream>
 using namespace std;

class LinearAllocator
{
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
    current = start;
    Size = 0;
}

char* LinearAllocator::alloc(size_t size){

    if (size+Size>MaxSize){ 
    cout<<"requested size is larger than MaxSize"<<endl;    
    return NULL;
    }

    *current +=size;
    Size +=size;
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

    LinearAllocator Allocator(15);
    cout<<Allocator.maxsize()<< endl;
    char* a  = Allocator.alloc(7) ;
    cout<<"current size = "<<Allocator.currentsize()<<endl;
    Allocator.alloc(10) ;
    cout<<"current size = "<<Allocator.currentsize()<<endl;
    Allocator.reset();
    cout<<"Max size after reset = "<<Allocator.maxsize()<<endl;
    cout<<"current after reset = "<<Allocator.currentsize()<<endl;
    char* b = Allocator.alloc(3);
    cout<<"curr size = "<<Allocator.currentsize()<<endl;
    return 0;

}