#include <iostream>
#include "Node.h"

int main(){
    Node<char>* first = new Node<char>('A');
    first = new Node<char>('R', first);
    first = new Node<char>('P', first);

    std::cout << "Secuencia: ";
    Node<char>* aux = first;
    while (aux != nullptr){
        std::cout << aux->data << " ";
        aux = aux->next;
    }
    std::cout << std::endl;

    // Liberamos memoria (buena práctica)
    aux = first;
    while (aux != nullptr) {
        Node<char>* nxt = aux->next;
        delete aux;
        aux = nxt;
    }
}

