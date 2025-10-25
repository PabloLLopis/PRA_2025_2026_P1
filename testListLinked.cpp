#include <iostream>
#include "List.h"
#include "ListLinked.h"

int main() {
    ListLinked<int> l;

    std::cout << l;
    std::cout << "size(): " << l.size() << "\n";
    std::cout << "empty(): " << std::boolalpha << l.empty() << "\n\n";

    l.append(-5);
    l.append(0);
    l.append(5);
    l.append(10);

    std::cout << l;
    std::cout << "size(): " << l.size() << "\n";
    std::cout << "empty(): " << std::boolalpha << l.empty() << "\n\n";

    std::cout << "l.get(0) => " << l.get(0) << "; l[0] => " << l[0] << "\n";
    std::cout << "l.get(3) => " << l.get(3) << "; l[3] => " << l[3] << "\n\n";

    std::cout << "l.remove(3) => " << l.remove(3) << ": \n";
    std::cout << "l.remove(1) => " << l.remove(1) << ": \n";
    std::cout << "l.remove(0) => " << l.remove(0) << ": \n\n";

    std::cout << l;
    std::cout << "size(): " << l.size() << "\n";
    std::cout << "empty(): " << std::boolalpha << l.empty() << "\n\n";

    l.prepend(33);          
    l.insert(1, 14);        
    if (l.get(1) == 14 && l.get(2) == 5) {
        int a = l.remove(1);  
        l.append(a);          
    }

    std::cout << l;
    std::cout << "size(): " << l.size() << "\n";
    std::cout << "empty(): " << std::boolalpha << l.empty() << "\n\n";

    std::cout << "l.search(14) => " << l.search(14) << "\n";
    std::cout << "l.search(55) => " << l.search(55) << "\n";

    auto try_insert = [&](int pos, int val){
        try { l.insert(pos, val); }
        catch (const std::out_of_range& ex) {
            std::cout << "l.insert(" << pos << ", " << val << ") => std::out_of_range: Posición inválida!\n";
        }
    };
    auto try_get = [&](int pos){
        try { (void)l.get(pos); }
        catch (const std::out_of_range& ex) {
            std::cout << "l.get(" << pos << ") => std::out_of_range: Posición inválida!\n";
        }
    };
    auto try_remove = [&](int pos){
        try { (void)l.remove(pos); }
        catch (const std::out_of_range& ex) {
            std::cout << "l.remove(" << pos << ") => std::out_of_range: Posición inválida!\n";
        }
    };

    try_insert(-1, 99);
    try_insert(4, 99);
    try_get(-1);
    try_get(3);
    try_remove(-1);
    try_remove(3);
    return 0;
}

