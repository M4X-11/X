#include <iostream>

int main(){
    int* test = new int;
    *test = 3;
    std::cout << "ptr: " << test << std::endl;
}