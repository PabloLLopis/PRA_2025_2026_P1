#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T*  arr;                 // almacenamiento contiguo
    int max;                 // capacidad del array
    int n;                   // número de elementos usados
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;
        T* nuevo = new T[new_size];
        // copiar los n elementos actuales (o los que quepan)
        int to_copy = (n < new_size) ? n : new_size;
        for (int i = 0; i < to_copy; ++i) nuevo[i] = arr[i];
        delete[] arr;
        arr = nuevo;
        max = new_size;
        if (n > max) n = max;
    }

    // Asegura que hay capacidad para al menos need elementos
    void ensure_capacity_for(int need) {
        if (need <= max) return;
        int new_cap = (max == 0) ? MINSIZE : max * 2;
        while (new_cap < need) new_cap *= 2;
        resize(new_cap);
    }

    // Posible estrategia de reducción para evitar demasiada memoria ociosa
    void shrink_if_needed() {
        if (max > MINSIZE && n <= max / 4) {
            int new_cap = max / 2;
            if (new_cap < MINSIZE) new_cap = MINSIZE;
            if (new_cap != max) resize(new_cap);
        }
    }

public:
    // Constructor por defecto
    ListArray() : arr(nullptr), max(0), n(0) {
        resize(MINSIZE);
    }

    // Destructor
    ~ListArray() override {
        delete[] arr;
        arr = nullptr;
        max = 0;
        n   = 0;
    }

    // Tamaño y estado
    int size() const override { return n; }
    bool empty() const override { return n == 0; }

    // Acceso con comprobación
    T get(int pos) const override {
        if (pos < 0 || pos >= n) throw std::out_of_range("get: posicion invalida");
        return arr[pos]; // por valor, como pide la interfaz
    }

    // Operador [] requerido por el enunciado (devuelve por valor)
    T operator[](int pos) const {
        if (pos < 0 || pos >= n) throw std::out_of_range("operator[]: posicion invalida");
        return arr[pos];
    }

    // Inserciones
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("insert: posicion invalida");
        ensure_capacity_for(n + 1);
        // desplazar a la derecha desde el final hasta pos
        for (int i = n; i > pos; --i) arr[i] = arr[i - 1];
        arr[pos] = e;
        ++n;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    // Eliminación
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("remove: posicion invalida");
        T val = arr[pos];
        // compactar a la izquierda
        for (int i = pos; i < n - 1; ++i) arr[i] = arr[i + 1];
        --n;
        shrink_if_needed();
        return val;
    }

    // Búsqueda lineal
    int search(T e) const override {
        for (int i = 0; i < n; ++i) {
            if (arr[i] == e) return i;
        }
        return -1;
    }

    // Impresión: List => [ \n  elem \n ... ]
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const ListArray<U>& list);
};

// Implementación del operador << como plantilla amiga
template <typename U>
std::ostream& operator<<(std::ostream& out, const ListArray<U>& list) {
    out << "List => [\n";
    for (int i = 0; i < list.n; ++i) {
        out << "  " << list.arr[i] << "\n";
    }
    out << "]\n";
    return out;
}

#endif // LIST_ARRAY_H

