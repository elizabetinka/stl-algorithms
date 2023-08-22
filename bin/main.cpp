#include <lib/algoritmics.h>
#include <array>
#include <list>

int main(){
    auto a = std::array<int, 3>({1, 2, 3});
    //auto b = std::array<int, 3>({6, 7, 8});

    std::array<int, 3> c = {1, 2, 3};
    auto w = liza::xrange(6, 9, 1);
    auto b = std::list<int>(w.begin(), w.end());
    for(auto v : liza::zip(a,b)) {
        std::cout<<v.first<<" "<<v.second << std::endl;
    }
    return 0;
}
