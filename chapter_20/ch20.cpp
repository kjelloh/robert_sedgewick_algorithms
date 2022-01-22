#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <functional>

namespace helper {
    void print(std::deque<int> v) {
        std::cout << "deque:";
        for (auto x : v) {
            if (x<0) std::cout << '+';
            else std::cout << x; 
        }
    }
    void print(std::vector<int> v) {
        std::cout << " vect:";
        for (auto x : v) {
            if (x<0) std::cout << '+';
            else std::cout << x; 
        }
    }
}

struct StateMachine {
    std::string caption;
    std::string ch;
    std::vector<int> next1;
    std::vector<int> next2;
    void print() const {        
        std::vector<std::string> rows{4,std::string(ch.size()*3,' ')};
        for (int i=0;i<ch.size();i++) {
            auto col = 3*i;
            auto s0 = std::to_string(i);
            std::copy(s0.begin(),s0.end(),rows[0].begin()+col);
            rows[1][col] = ch[i];
            auto s1 = std::to_string(next1[i]);
            std::copy(s1.begin(),s1.end(),rows[2].begin()+col);
            auto s2 = std::to_string(next2[i]);
            std::copy(s2.begin(),s2.end(),rows[3].begin()+col);
        }
        for (int r=0;r<rows.size();++r) {
            auto row = rows[r];
            std::string label{};
            switch (r) {
                case 0: label = "state: "; break;
                case 1: label = "   ch: "; break;
                case 2: label = "next1: "; break;
                case 3: label = "next2: "; break;
            }
            std::cout << "\n" << label << row;
        }
    }
};

class Match {
public:
    Match(std::string const& s,StateMachine const& sm)
        : a{s}
          ,N{s.size()}
          ,sm{sm}  {
    };
    int operator()(int j) {
        sm.print();
        std::cout << "\na = " << a; 
        int result{0};
        const int SCAN{-1};
        int state{},n1{},n2{};
        put(SCAN);
        result = j-1;
        state = sm.next1[0];
        do {
            std::cout << "\na[" << j << "] ";
            if (state==SCAN) {
                // scan next character = move scan point j to next in input
                ++j;
                put(SCAN); // put = push_back a new scan operation after states to match a[j] 
            }
            else if (sm.ch[state]==a[j]) {
                // this state is a match = update deque with next state for next pattern char to match
                put(sm.next1[state]); // put = push_back = next after SCAN
            }
            else if (sm.ch[state]==' ') {
                // continue for state that is NOT a match pattern state
                n1=sm.next1[state];
                n2=sm.next2[state];
                // push = push_front = Candidate states before SCAN
                push(n1);
                if (n1 != n2) push(n2); // push_front alternative state
            }
            helper::print(this->deque); std::cout << " " << a.substr(0,j) << "." << a.substr(j);
            state=pop(); // process next = pop_front = state before next SCAN
            // loop while more input and states 
        } while ((j<=N) and (state!=0) and (deque.size()>0));
        // Q: I do not understand how we can make a closure end in state 0 (a closure ends only on match failure?)
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

void chapter_20() {
    const StateMachine sm{
        // Hard coded match for (A*B+AC)D (page 299)
        .caption = "pattern: (A*B+AC)D"
        ,.ch = " A B  ACD "
        ,.next1 = {5,2,3,4,8,6,7,8,9,0}
        ,.next2 = {5,2,1,4,8,2,7,8,9,0}
    };    
    std::string s = "AAABD";
    std::cout << "\nMatch " << s << " with " << sm.caption;
    Match match{s,sm}; // Example 20.8
    auto result = match(0);
    std::cout << "\nmatch at " << result << " in " << s;
}

void exersice_3() {
    // Q: I do not understand how we can make a closure end in state 0 (a closure ends only on match failure?)
    // const StateMachine sm{
    //     // Hard coded match for (A+B)*
    //     // state: 0  1  2  3  4  5
    //     //    ch:          A  B     
    //     // next1: 1  2  3  1  1  0
    //     // next2: 1  2  4  1  1  0
    //     .caption = "pattern: (A+B)*"
    //     ,.ch = "   AB "
    //     ,.next1 = {1,2,3,1,1,0}
    //     ,.next2 = {1,2,4,1,1,0}
    // };
    const StateMachine sm{
        // Hard coded match for (A+B)*+C
        // Meaning: any number of A or B, OR - a single C
        // This must mean that as soon we match the closure we can no lobger match a C, and vise versa
        // state: 0  1  2  3  4  5  6  7  8
        //    ch:          A  B     C
        // next1: 5  2  3  1  1  1  7  8  0
        // next2: 5  2  4  1  1  6  7  8  0
        .caption = "pattern: (A+B)* + C"
        ,.ch = "   AB C  "
        ,.next1 = {5,2,3,1,1,1,7,8,0}
        ,.next2 = {5,2,4,1,1,6,7,8,0}
    };
    std::string s = "ABBAC";
    std::cout << "\nMatch " << s << " with " << sm.caption;
    Match match{s,sm}; // Exersice 2 and 3
    {
        auto result = match(0); // should match ABBA in "ABBAC"
        std::cout << "\nmatch at " << result << " in " << s;
    }
    {
        auto result = match(4); // should match "C" in "ABBAC"
        std::cout << "\nmatch at " << result << " in " << s;
    }
}

using Skill = std::pair<std::string,std::function<void()>>;

int main(int argc,char* argv[]) {
    std::map<int,Skill> skills{
         {0,{"chapter 20 examples",chapter_20}}
        ,{3,{"exersice 3",exersice_3}}
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