#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <functional>
#include <array>
#include <memory>

void primes() {
    const int N=1000;
    std::array<bool,N> a{};
    int i{},j{};
    a[1] = false;
    for (int i=2;i<=N;i++) a[i] = true;
    for (int i=2;i<=N/2;i++) for (int j=2;j<N/i;j++) a[i*j] = false;
    for (int i=1;i<N;i++) if (a[i]) std::cout << " " << i;
}

class LinkedList {
public:
    struct Node {
        using Link = std::shared_ptr<Node>;
        int key;
        Link next;
    };
    using Link = Node::Link;
    LinkedList() :  head{std::make_shared<Node>()} ,z{std::make_shared<Node>()} {head->next=z;z->next=z;}
    void deletenext(Link const& t) {t->next = t->next->next;}
    void insertafter(int v,Link const& t) {
        Link x{std::make_shared<Node>(v,t->next)};
        t->next=x;
    }
private:
    Link head;
    Link z;
};

template <typename Key,int N>
class ArrayList {
public:
    using Link = int;
    ArrayList() {
        next[head] = z;
        next[z] = z;
    }
    void deletenext(Link const& t) {next[t] = next[next[t]];}
    void insertafter(Key v,Link t) {++x;key[x]=v;next[x]=next[t];}

private:
    Link x{1}; // current "unused" (where to create "new")
    Link head{0};
    Link z{1};
    std::array<Key,N> key;
    std::array<Link,N> next;
};



void chapter_3() {
    std::cout << "\nprimes"; primes();
}

using Skill = std::pair<std::string,std::function<void()>>;

int main(int argc,char* argv[]) {
    std::map<int,Skill> skills{
         {0,{"chapter 20 examples",chapter_3}}
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