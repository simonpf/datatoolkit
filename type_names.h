/**
 * Type trait for human readable type names. 
 */

#define ADD_TYPENAME(A) template<> struct Type<A> {static std::string name() {return #A;}};

#include <iostream>
#include <string>
#include <typeinfo>

template<typename T>
struct Type {
    static std::string name()
    {
        return typeid(Type).name();
    }
};

ADD_TYPENAME(char);
ADD_TYPENAME(unsigned char);
ADD_TYPENAME(short);
ADD_TYPENAME(unsigned short);
ADD_TYPENAME(int);
ADD_TYPENAME(unsigned int);
ADD_TYPENAME(long);
ADD_TYPENAME(unsigned long);
ADD_TYPENAME(float);
ADD_TYPENAME(double);
