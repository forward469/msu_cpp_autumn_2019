#include "Format.h"
using namespace std;

int main(){
    auto text = format("{0} + {1} = {2} ",  "seventeen", "twenty five",  42);
    cout<<text<< " ANSWER!" <<endl;
    assert(text == "seventeen + twenty five = 42 ");

    text = format("1:{1}, 2:{0}, 3:{2}",  "second", "first", "third");
    cout<<text<<endl;
    assert(text == "1:first, 2:second, 3:third");

    text = format("bla bla");
    cout<<text<<endl;
    assert(text == "bla bla");

    cout<<endl<<endl<<"Errors:"<<endl<<endl;

    try {
        text = format("what?{}why?");
    }
     catch (runtime_error& e) {
        cout<<e.what()<<endl;
    }
    try {
        text = format("{0}+{2}-{3} = ?", "37", "12", "7");
    } 
    catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }
    try {
        text = format("{0}+{1}-{2}+{3} = ?", "37", "12", "7");
    } 
    catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }
    try {
        text = format("what? {0} how? {{", "number", 0);
    } 
    catch (runtime_error& e) {
        cout<< e.what()<<endl;
    }
     return 0;
}