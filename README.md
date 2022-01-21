# robert_sedgewick_algorithms

This is a C++ project with implementations of algorithm examples and exersices from Robert Sedgewick book "Algorithms" (ISBN 0-201-06673-4)

# chapter_20

*Contains the regular expression match algorithm (hard coded for pattern (A*B+AC)D)

``` c++
class Match {
public:
    Match(std::string const& s) 
        : a{s}
          ,N{s.size()}
           // Hard coded match for (A*B+AC)D
          ,ch{" A B  ACD "}
          ,next1{5,2,3,4,8,6,7,8,9,0}
          ,next2{5,2,1,4,8,2,7,8,9,0}  {
        std::cout << "\nMatch " << s << " with pattern (A*B+AC)D";
        std::cout << "\n<state deque> (+ means scan-next-charachter)";
    };
    int operator()(int j) {
        int result{0};
        const int scan{-1};
        int state{},n1{},n2{};
        put(scan);
        result = j-1;
        state = next1[0];
        do {
            if (state==scan) {
                ++j;
                put(scan);
            }
            else if (ch[state]==a[j]) {
                put(next1[state]);
            }
            else if (ch[state]==' ') {
                n1=next1[state];
                n2=next2[state];
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
    void put(int x) {deque.push_back(x);}
    void push(int x) {deque.push_front(x);}
    int pop() {auto result = deque.front(); deque.pop_front();return result;}
    std::string ch;
    std::deque<int> deque{};
    std::vector<int> next1{},next2{};
    std::string a;
    const size_t N;
};
```

* Outputs the contents of the states in deque + the part of the inoput string matched so far through the match processing.

```
Match AAABD with pattern (A*B+AC)D
<state deque> (+ means scan-next-charachter)
deque:26+ 
deque:136+ 
deque:36+2 
deque:6+2 
deque:+27 
deque:27+ A
deque:137+ A
deque:37+2 A
deque:7+2 A
deque:+2 A
deque:2+ AA
deque:13+ AA
deque:3+2 AA
deque:+2 AA
deque:2+ AAA
deque:13+ AAA
deque:3+ AAA
deque:+4 AAA
deque:4+ AAAB
deque:8+ AAAB
deque:+9 AAAB
deque:9+ AAABD
deque:0+ AAABD
match at 4

```
