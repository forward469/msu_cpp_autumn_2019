#include "Serializer.h"
#include <iostream>
#include <cassert>
#include <cstdint>
#include <sstream>

using namespace std;
struct Data
{
    uint64_t Num_1;
    bool Bool_1;
    uint64_t Num_2;
    bool Bool_2;

    template <class Serializer>
    Error serialize(Serializer& serializer){
        return serializer(Num_1, Bool_1, Num_2, Bool_2);}
    
    template <class Serializer>
     Error deserialize(Deserializer& deserializer){
        return deserializer(Num_1, Bool_1, Num_2, Bool_2);}
};

int main(){

    Data SEQ1;
    SEQ1.Num_1 = 1; SEQ1.Bool_1 = true; SEQ1.Num_2 = 2; SEQ1.Bool_2 = false;
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(SEQ1);

    Data SEQ2;
    SEQ2.Num_1 = 3; SEQ2.Bool_1 = false; SEQ2.Num_2 = 5; SEQ2.Bool_2 = false;
    Deserializer deserializer(stream);
    const Error err = deserializer.load(SEQ2);

    assert(err == Error::NoError);

    assert(SEQ1.Num_1 == SEQ2.Num_1);
    assert(SEQ1.Bool_1 == SEQ2.Bool_1);
    assert(SEQ1.Num_2 == SEQ2.Num_2);
    assert(SEQ1.Bool_2 == SEQ2.Bool_2);

    cout<<"Complete!"<<endl;
    return 0;
}

