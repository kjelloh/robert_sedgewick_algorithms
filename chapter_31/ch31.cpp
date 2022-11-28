#include <iostream>
#include <map>
#include <functional>
#include <memory>
#include <vector>
#include  <limits>

const int V{};

namespace chapter_29 {
    

    namespace recursive {

        // Depth first search
        class dfs {
        private:
            struct Node {
                using Link = std::shared_ptr<Node>;
                int v;
                Link next;
            };
            Node::Link z{};
            int id,k;
            std::vector<int> val;
            std::vector<Node::Link> adj;
            void visit(int k) {
                Node::Node::Link t;
                ++id;val[k]=id;
                t=adj[k];
                while (t!=z) {
                    if (val[t->v]==0) {
                        visit(t->v);
                        t=t->next;
                    }
                }
            }
        public:
            // list depth first search 
            void listdfs() {
                id = 0;
                for (int k=0;k<V;++k) val[k]=0;
                for (int k=0;k<V;++k) {
                    if (val[k]==0) visit(k);
                }
            }
        };
    }
    namespace nonrecursive {
        class dfs {
        private:
            struct Node {
                using Link = std::shared_ptr<Node>;
                int v;
                Link next;
            };
            using Link = std::shared_ptr<Node>;
            Link z{};
            int id,k;
            std::vector<int> val{};
            std::vector<Node::Link> adj{};
            void stackinit() {}
            void push(int k) {}
            int pop() {return 0;}
            bool stackempty() {return true;}
            void visit(int k) {
                Node::Link t;
                push(k);
                do {
                    k=pop();
                    ++id; val[k]=id;
                    t=adj[k];
                    while (t!=z) {
                        if (val[t->v]==0) {
                            push(t->v); val[t->v]=-1;
                        }
                        t=t->next;
                    }
                } while (not stackempty());
            }
        public:
            // list depth first search 
            void listdfs() {
                id = 0; stackinit();
                for (int k=0;k<V;++k) val[k]=0;
                for (int k=0;k<V;++k) {
                    if (val[k]==0) visit(k);
                }
            }
        };

        // breath first search
        class bfs {
        private:
            struct Node {
                using Link = std::shared_ptr<Node>;
                int v;
                Link next;
            };
            Node::Link z{};
            int id,k;
            std::vector<int> val;
            std::vector<Node::Link> adj{};
            void queueinitialize() {}
            void put(int k) {}
            int get() {return 0;}
            bool queueempty() {return true;}
            void visit(int k) {
                Node::Link t;
                put(k);
                do {
                    k=get();
                    ++id; val[k]=id;
                    t=adj[k];
                    while (t!=z) {
                        if (val[t->v]==0) {
                            put(t->v); val[t->v]=-1;
                        }
                        t=t->next;
                    }
                } while (not queueempty());
            }
        public:
            // list depth first search 
            void listbfs() {
                id = 0; queueinitialize();
                for (int k=0;k<V;++k) val[k]=0;
                for (int k=0;k<V;++k) {
                    if (val[k]==0) visit(k);
                }
            }
        };
    }
} // namespace chapter_29

namespace chapter_31 {

    namespace nonrecursive {
                
        // Priority first search
        class pfs {
        private:
            const int unseen{std::numeric_limits<int>::max()}; // unique sentinel value
            struct Node {
                using Link = std::shared_ptr<Node>;
                Link next;
                int v;
                int w; // weight
            };
            Node::Link z{};
            int id,k;
            std::vector<int> val;
            std::vector<int> dad{};
            std::vector<Node::Link> adj{};
            void pqinitialize() {}
            bool pqupdate(int k,int priority) {return false;} // TODO: Ensure vertex k appears on the priority queue with provided priority (See page 455)
            int pqremove() {return 0;}
            bool pqempty() {return true;}
            int priority(Node::Link t) {return unseen;} // TODO: Implement appropriate priority function (t->w for minimum spanning tree. See page 455..457, val[k]+t-w page 463 for Shortest-path) 
            void visit(int k) {
                Node::Link t;
                if (pqupdate(k,unseen)) {
                    dad[k]=0;
                }
                do {
                    ++id;
                    k=pqremove();val[k]=-val[k];
                    if (val[k]==unseen) val[k]=0;
                    t=adj[k];
                    while (t!=z) {
                        if (val[t->v]<0) {
                            if (pqupdate(t->v,priority(t))) {
                                val[t->v]=-(priority(t));dad[t->v]=k;
                            }
                        }
                    t=t->next;
                    }
                } while (not pqempty());
            }

        public:
            void listpfs() {
                id = 0;
                pqinitialize();
                for (int k = 0;k<V;++k) val[k]=-unseen;
                for (int k = 0;k<V;++k) {
                    if (val[k]==-unseen) visit(k);
                }
            }

        };
    }

    void examples() {
        nonrecursive::pfs{}.listpfs();
    } 
}

using Skill = std::pair<std::string,std::function<void()>>;

int main(int argc,char* argv[]) {
    std::map<int,Skill> skills{
         {0,{"chapter 31 examples",chapter_31::examples}}
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