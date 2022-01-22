#include <iostream>
#include <map>
#include <functional>
#include <memory>

void chapter_0() {
}

using Skill = std::pair<std::string,std::function<void()>>;

int main(int argc,char* argv[]) {
    std::map<int,Skill> skills{
         {0,{"chapter 20 examples",chapter_0}}
    };
    int exersice{0};
    if (argc==2) {
        exersice = std::stoi(argv[1]);
    }
    if (skills.contains(exersice)) skills.at(exersice).second();   
    else {
        std::cout << "\nUnknown argument: " << exersice;
        std::cout << "\nAvailable options:";
        for (auto entry : skills) {
            std::cout << "\n\targument: " << entry.first << " to execute: " << entry.second.first;
        }
    } 
    std::cout << "\n";
    return 0;
}