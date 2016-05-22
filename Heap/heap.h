#pragma once

template <typename T>
class Heap {
private:
    int capacity;

    // position[i] = pozitia din heap pe care se afla elementul inserat al i-lea in ordine cronologica
    int *position;
    int dimension, index;
    Array < Pair < T, int > > H;

    int parent(int pos);
    void pushUp(int pos);
    void pushDown(int pos);
    int leftSubtree(int pos);
    int rightSubtree(int pos);
    void Swap(const int x, const int y);
    // pointer la o functie care comparara doua elemente
    int (*cmp)(const Pair <T, int> &, const Pair <T, int>&);
public:
    Heap(int capacity, int (*compare)(const Pair <T, int>&, const Pair <T, int>&));
    ~Heap();

    // Copy constructor
    Heap(const Heap &other);

    T peek();
    int size();
    T extract();
    void insert(T x);
    T getValue(int pos);

    // updatez elementul care a fost inserat al k-lea in ordine cronologica
    void update(int k, T newData);
};

template < typename T >
Heap <T> :: Heap(const Heap &other) {
    H = other.H;
    cmp = other.cmp;
    index = other.index;
    capacity = other.capacity;
    dimension = other.dimension;

    position = new int[capacity];
    if (dimension > 0) {
        for (int i = 0; i < other.dimension; ++i) {
            position[i] = other.position[i];
        }
    }
}

template <typename T>
void Heap <T> :: Swap(const int x, const int y) {
    swap(H[x], H[y]);
    swap(position[H[x].second], position[H[y].second]);
}

template <typename T>
void Heap <T> :: update(int k, T newData) {
    int pos = position[k - 1];
    H[pos].first = newData;
    if (pos > 1 && cmp(H[pos], H[parent(pos)])) {
        return pushUp(pos);
    } else {
        return pushDown(pos);
    }
}

template <typename T>
T Heap <T> :: getValue(int pos) {
    return H[pos].first;
}

template <typename T>
int Heap <T> :: size() {
    return dimension;
}

template <typename T>
Heap <T> :: Heap(int capacity, int (*compare)(const Pair <T, int>&, const Pair <T, int>&)) {
    index = 0;
    cmp = compare;
    dimension = 0;
    this->capacity = capacity;
    position = new int[capacity];
}

template <typename T>
Heap <T> :: ~Heap() {
    delete[] position;
}

template <typename T>
int Heap <T> :: parent(int pos) {
    return ((pos - 1) >> 1);
}

template <typename T>
int Heap <T> :: leftSubtree(int pos) {
    return (pos << 1) + 1;
}

template <typename T>
int Heap <T> :: rightSubtree(int pos) {
    return (pos << 1) + 2;
}

template <typename T>
void Heap <T> :: pushUp(int pos) {
    while ( pos > 0 && cmp(H[pos], H[parent(pos)]) ) {
        Swap(pos, parent(pos));
        pos = parent(pos);
    }
}

template <typename T>
void Heap <T> :: pushDown(int pos) {
    while (1) {
        int rightSon = rightSubtree(pos);
        int leftSon = leftSubtree(pos);
        if (rightSon > dimension) { // daca nu am fiu dreapta
            if (leftSon > dimension) { // daca nu am fiu stanga
                break;
            } else if ( cmp(H[leftSon], H[pos]) ) {
                Swap(leftSon, pos);
                pos = leftSon;
            } else {
                break;
            }
        } else {
            if (H[leftSon].first <= H[rightSon].first && cmp(H[leftSon], H[pos])) {
                Swap(leftSon, pos);
                pos = leftSon;
            } else if (H[rightSon].first <= H[leftSon].first && cmp(H[rightSon], H[pos])) {
                Swap(rightSon, pos);
                pos = rightSon;
            }
        }
    }
}

template <typename T>
void Heap <T> :: insert(T x) {
    if (capacity == dimension) {
        std::cerr << "Heapul e plin!\n";
        return;
    }

    position[index] = dimension++;
    Pair <T, int> aux;
    aux.makePair(x, index++);
    H.push_back(aux);
    pushUp(dimension - 1);
}

template <typename T>
T Heap <T> :: peek() {
    if (dimension == 0) {
        std::cerr << "Heapul e gol! \n";
        T x;
        return x;
    }
    
    return H[1].first;
}

template <typename T>
T Heap <T> :: extract() {
    if (dimension == 1) {
        std::cerr << "Heapul e gol! \n";
        T x;
        return x;
    }

    T value = H[1].first;
    H[1] = H[--dimension];

    if (dimension > 1) {
        pushDown(1);
    }

    return value;
}