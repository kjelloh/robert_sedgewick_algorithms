#include <iostream>
#include <deque>
#include <vector>

namespace helper {
    void print(std::deque<int> deque) {
        std::cout << "\ndeque:";
        for (auto x : deque) {
            if (x<0) std::cout << '+';
            else std::cout << x; 
        }
    }
}

struct StateMachine {
    std::string ch;
    std::vector<int> next1;
    std::vector<int> next2;
};

const StateMachine ManyAandB_or_AndC_FollowedByD{
    // Hard coded match for (A*B+AC)D
    .ch = {" A B  ACD "}
    ,.next1 = {5,2,3,4,8,6,7,8,9,0}
    ,.next2 = {5,2,1,4,8,2,7,8,9,0}
};

const StateMachine Exersice2And3{
    // Hard coded match for (A+B)* + C
    .ch = {"   AB C  "}
    ,.next1 = {1,2,3,5,5,2,7,8,0}
    ,.next2 = {1,6,4,5,5,7,7,8,0}
};

class Match {
public:
    Match(std::string const& s,StateMachine const& sm = ManyAandB_or_AndC_FollowedByD)
        : a{s}
          ,N{s.size()}
          ,sm{sm}  {
        std::cout << "\n<state deque> (+ means scan-next-charachter)";
    };
    int operator()(int j) {
        int result{0};
        const int scan{-1};
        int state{},n1{},n2{};
        put(scan);
        result = j-1;
        state = sm.next1[0];
        do {
            if (state==scan) {
                ++j;
                put(scan);
            }
            else if (sm.ch[state]==a[j]) {
                put(sm.next1[state]);
            }
            else if (sm.ch[state]==' ') {
                n1=sm.next1[state];
                n2=sm.next2[state];
                push(n1);
                if (n1 != n2) push(n2);
            }
            helper::print(this->deque); std::cout << " " << a.substr(0,j);
            state=pop();
        } while ((j<=N) and (state!=0) and (deque.size()>0));
        if (state==0) result = j-1;
        return result;
    }
private:
    std::deque<int> deque{};
    void put(int x) {deque.push_back(x);}
    void push(int x) {deque.push_front(x);}
    int pop() {auto result = deque.front(); deque.pop_front();return result;}
    StateMachine sm;
    std::string a;
    const size_t N;
};

int main(int argc,char* argv[]) {
    std::cout << "\nMatch " << "AAABD" << " with pattern (A*B+AC)D";
    Match match{"AAABD"}; // Example 20.8
    auto result = match(0);
    std::cout << "\nmatch at " << result;
    std::cout << "\nMatch " << "ABBAC" << " with pattern (A+B)* + C";
    Match match2or3{"ABBAC",Exersice2And3};
    auto result2or3 = match2or3(0);
    std::cout << "\nmatch at " << result2or3;
    std::cout << "\n";
    return 0;
}