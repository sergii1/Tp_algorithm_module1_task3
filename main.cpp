#include <iostream>
#include <sstream>
#include <cassert>
/*3_2. Реализовать дек с динамическим зацикленным буфером.
Требования: Дек должен быть реализован в виде класса.
*/
using namespace std;

template<class T>
class Deque {
public:
    Deque(int p_capacity = 4, float p_expansionCoefficient = 2) : capacity(p_capacity), head(0), tail(0) {
        expansionCoefficient = p_expansionCoefficient;
        buffer = new T[capacity];
    }

    ~Deque() {
        delete[] buffer;
    }
    Deque( const Deque& ) = delete;
    void operator=( const Deque& ) = delete;
    // PushBack записывает в элемент следующий за последним
    void PushBack(const T &element) {
        if (getNext(tail) == head)
            expansion();
        buffer[tail] = element;
        tail = getNext(tail);
    }

    //PushFront записывает в элемент до первого
    void PushFront(const T &element) {
        if (getPrev(head) == tail) {
            expansion();
            //head в expansion поменялся, поэтому надо заново получить его
        }
        head = getPrev(head);
        buffer[head] = element;

    }

    T PopBack() {
        if (isEmpty()) {
            throw "deque is empty";
        }
        T tmp = buffer[getPrev(tail)];
        tail = getPrev(tail);
        return tmp;
    }

    T PopFront() {
        if (isEmpty()) {
            throw "deque is empty";
        }
        T tmp = buffer[head];
        head = getNext(head);
        return tmp;
    }

    bool isEmpty() {
        return head == tail;
    }

    void print() {
        for (int i = head, j = 0; i != tail; i = getNext(i)) {
            cout << buffer[i] << " ";
        }
        cout << endl;
    }

private:

    void expansion() {
        int new_capacity = capacity * expansionCoefficient;
        T *newBuffer = new T[new_capacity];
        //cout<<endl<<"new capacity = "<<new_capacity<<endl;
        //голова у нового массива будет в нуле, а у старого голова могла сместиться, поэтому разные индексы
        for (int i = head, j = 0; i != tail; i = getNext(i), ++j) {
            newBuffer[j] = buffer[i];
            // cout<<"i = "<<i<<" j = "<<j<< "buffer[i] = "<<buffer[i]<<" newBuffer[j] = "<<newBuffer[j]<< endl;
        }
        head = 0;
        tail = capacity - 1;
        capacity = new_capacity;
        delete[] buffer;
        buffer = newBuffer;
    }

    int getNext(const int &index) {
        return (index + 1) % capacity;
    }

    int getPrev(const int &index) {
        if (index == 0)
            return capacity - 1;
        return index - 1;
    }

    T *buffer;
    //head - текущее положение головы, а tail следующий за последним
    int capacity, head, tail;
    float expansionCoefficient;
};

void test() {
    stringstream in;
    int n;
    in >> n;


}

void run(istream &in, ostream &out) {
    Deque<int> d;
    int n;
    in >> n;
    int operation, val;
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        cin >> operation >> val;
        switch (operation) {
            //pushFront
            case 1: {
                d.PushFront(val);
                break;
            }
                //popFront
            case 2: {
                int res;
                try {
                    res = d.PopFront();
                }
                catch (...) {
                    res = -1;
                }
                if (res != val)
                    flag = false;
                break;
            }

                //pushBack
            case 3: {

                d.PushBack(val);
                break;
            }
                //popBack
            case 4: {
                int res;
                try {
                    res = d.PopBack();
                }
                catch (...) {
                    res = -1;
                }
                if (res != val)
                    flag = false;
                break;
            }
        }
    }
    if (flag)
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    run(cin, cout);

    return 0;
}
