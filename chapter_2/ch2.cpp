#include <iostream>
#include <map>
#include <functional>
#include <utility>
#include <memory>
#include <sstream>
#include <algorithm>
#include <deque>
#include <numeric>


// See https://en.wikipedia.org/wiki/Euclidean_algorithm for a more in depth about gcd and chinese reminder theorem
namespace classic {
    int gcd(int u,int v) {
        do {
            if (u<v) std::swap(u,v);
            u -= v;
        } while (u!=0);
        return v;
    } 
}

namespace mod {
    int gcd(int u,int v) {
        do {
            if (u<v) std::swap(u,v);
            u %= v; // original u -= v until u<v is the same as u/v and keep the remainder, i.e. u mod v
        } while (u!=0); 
        return v;
    } 
}

enum class GcdType {classic,mod}; 

void gcd_on_stream(std::istream& in,std::ostream& out,GcdType gcd_type) {
    int u,v;    
    out << "Enter u and v>";
    in >> u >> v;
    out << "gcd(" << u << "," << v << ")=";
    if (gcd_type==GcdType::classic) std::cout << classic::gcd(u,v);
    else std::cout << mod::gcd(u,v);
}

void exersice_1() {
    gcd_on_stream(std::cin,std::cout,GcdType::classic);
}

void exersice_2() {
    for (auto i : {-21,7,1,5,36}) {
        for (auto j : {-3,-14,3,14,15,8}) {
            if (i!=j) std::cout << "\n" << i << " mod " << j << " = " << i%j;
        }
    }
}

void exersice_3() {
    struct Fraction {int numerator,denominator;};
    Fraction fraction{.numerator=36,.denominator=8};
    std::cout << "\n" << fraction.numerator << "/" << fraction.denominator;
    auto gcd = mod::gcd(fraction.numerator,fraction.denominator);
    fraction.numerator /= gcd;
    fraction.denominator /= gcd;
    std::cout << " = " << fraction.numerator << "/" << fraction.denominator;
}

int convert(std::string const& digits) {
    int result{0};
    for (auto digit : digits) {
        result = 10*result + (digit-'0');
    }
    return result;
}

void exersice_4() {
    std::string digits{};
    std::cout << "\ndigits>";
    // Note: C++ has no notion of "keyboard" so there is no standard way to read char-by-char
    std::getline(std::cin,digits);
    std::cout << "\nYou entered: " << convert(digits);
}

std::string binary(int x) {
    std::string result{};
    while (x>0) {
        result.insert(result.begin(),(x%2==0)?'0':'1');
        x /= 2;
    }
    return result;
}

void exersice_5() {
    std::cout << "\nNumber> ";
    int x;
    std::cin >> x;
    std::cout << x << " is binary " << binary(x);
}

void exersice_8() {
    // gcd of n numbers is the accumulated gcd of reducing each number with the gcd of the prevouds numbers
    // This can be expressed recursively as:
    // gcd0 = n0
    // gcd1 = gcd(gcd0,n1)
    // gcd2 = gcd(gcd1,n2)
    // gcdN = gcd(gcdn-1,N)
    std::cout << "\nnumbers>";
    std::string entry{};
    std::getline(std::cin,entry);
    std::deque<int> numbers{};
    auto first=entry.begin();
    while (first!=entry.end() and *first==' ') ++first; // skip spaces
    auto second=first;
    while (true) {
        second = std::find(first,entry.end(),' ');
        numbers.push_back(std::stoi(std::string{first,second}));
        if (second == entry.end()) break;
        first = second;
        while (first!=entry.end() and *first==' ') ++first; // skip spaces
    }
    auto gcd0 = numbers.front(); numbers.pop_front();
    auto gcd = std::accumulate(numbers.begin(),numbers.end(),gcd0,mod::gcd);
    std::cout << "\ngcd of ";
    for (auto n : numbers) std::cout << " " << n;
    std::cout << " is " << gcd;
}

void chapter_2() {
    exersice_1();
}

using Skill = std::pair<std::string,std::function<void()>>;

int main(int argc,char* argv[]) {
    std::map<int,Skill> skills{
          {0,{"chapter 2 examples",chapter_2}}
         ,{1,{"exersice 1 - classig gcd",exersice_1}}
         ,{2,{"exersice 2 - negative modulus tries",exersice_2}}
         ,{3,{"exersice 3 - numerator/denominator reduce with gcd",exersice_3}}
         ,{4,{"exersice 4 - convert decimal digits to int",exersice_4}}
         ,{5,{"exersice 5 - convert int to binary",exersice_5}}
         ,{8,{"exersice 8 - gcd of multipple integers",exersice_8}}
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