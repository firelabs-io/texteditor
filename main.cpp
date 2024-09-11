#include <iostream>
#include "c++/keyboard.hpp"
#include <vector>

int main(){
    Keyboard keyboard;
    int key = keyboard.getKey();
    std::vector<char> output;

    while(key != 27){
        if(key == 8 || key == 127){
            if(!output.empty()){
                output.pop_back();
                std::cout << "\b \b";
            }
        } else{
            std::cout << char(key);
            output.push_back(char(key));
        }
        key = keyboard.getKey();
    }
    return 0;
}