#include <iostream>
#include <functional>
#include <conio.h>

using namespace std;

#ifndef __ListaCircular_SimplementeEnlazada_H__
#define __ListaCircular_SimplementeEnlazada_H__

template <typename T, T NADA = 0>
class ListaSimpCirc {
    struct Node {
        T elem;
        Node* next;
        Node(T elem, Node* next) : elem(elem), next(next) {}
    };

    int len;
    Node* head;
    Node* tail;
public:
    ListaSimpCirc() :len(0), head(nullptr), tail(nullptr) {}
    ~ListaSimpCirc() {
        while (head != nullptr) {
            auto aux = head;
            head = head->next;
            delete aux;
        }
    }

    int size() {
        return len;
    }
    bool is_empity() {
        return len == 0;
    }

    //to add

    void addFirst(T n) {
        if (len == 0) {
            head = new Node(n, head);
            tail = new Node(0, head);
        }
        else {
            Node* nuevo = new Node(n, head);
            head = nuevo;
            tail->next = head;
        }
        ++len;
    }

    void addPos(T n, int pos) {
        if (pos < 0 || pos > len)
            return;
        if (pos == 0)
            addFirst(n);
        else {
            Node* aux = head;
            //auto aux = head; <- is correct
            for (int i = 1; i < pos; i++) {
                aux = aux->next;
            }

            Node* nuevo = new Node(n, aux->next);
            if (nuevo != nullptr) {
                aux->next = nuevo;

                if (pos == len) {
                    tail = nuevo;
                    tail->next = head;
                }
                len++;
            }
        }
    }

    void addLast(T n) {
        addPos(n, len);
    }

    //to get

    T getFirst() {
        return head->elem;
    }

    T getPos(int pos) {
        if (pos < 0 || pos >= len)
            return -1;
        if (pos == 0)
            getFirst();
        else {
            Node* aux = head;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }

            return aux->elem;
        }
    }

    T getLast() {
        return getPos(len - 1);
    }

    // my element is here?

    bool findElem(T n) {
        Node* aux = head;

        for (int i = 0; i < len; i++) {
            if (aux->elem == n)
                return true;
            aux = aux->next;

        }
        return false;
    }

    //to remove

    void deleteFirst() {
        if (len > 0) {
            tail->next = head->next;
            delete head;
            head = tail->next;
            --len;
        }
    }

    void deletePos(int pos) {
        if (pos < 0 || pos >= len)
            return;
        if (pos == 0)
            deleteFirst();
        else {
            auto aux = head;
            auto aux1 = head;

            for (int i = 1; i < pos; ++i) {
                aux = aux->next;
            }
            for (int i = 2; i < pos; ++i) {
                aux1 = aux1->next;
            }
            aux1->next = aux->next;
            delete aux;
            --len;
        }
    }

    void deleteLas() {
        deletePos(len - 1);
    }

    //to find the position

    int findPos(T n) {
        if (len > 0) {
            auto aux = head;
            for (int i = 0; i < len; ++i) {
                if (aux->elem == n)
                    return i;
                aux = aux->next;
            }
            return -1;
        }
    }

    //class iterator

    class iterator {
        Node* aux;
        int pos;
    public:
        iterator(Node* aux, int pos)
            : aux(aux), pos(pos) {}

        bool operator!=(iterator other) {
            return pos != other.pos;
        }

        int operator++() {
            aux = aux->next;
            ++pos;
            return 0;
        }

        float operator*() {
            return aux->elem;
        }
    };
    iterator begin() {
        return iterator(head, 0);
    }
    iterator end() {
        return iterator(nullptr, len);
    }

};
#endif // !__ListaCircular_SimplementeEnlazada_H__

// a little example

int main() {
    ListaSimpCirc<int>* myListSimpleCircular = new ListaSimpCirc<int>();

    int opt = 0;
    int c = 0;

    int myElement;
    int pos;

    while (opt != 7) {
        system("cls");
        cout << "\t.:My List:." << endl;
        cout << "1. Add" << endl;
        cout << "2. Return" << endl;
        cout << "3. My element is here?" << endl;
        cout << "4. Remove" << endl;
        cout << "5. Find the position of your element" << endl;
        cout << "6. List all items" << endl;
        cout << "7. Leave" << endl;
        cout << "Option: ";
        cin >> opt;
        system("cls");

        switch (opt)
        {
        case 1:
            cout << "Your new element is: ";
            cin >> myElement;
            myListSimpleCircular->addPos(myElement, c);
            ++c;
            break;
        case 2:
            cout << "Your pos: ";
            cin >> myElement;
            myElement = myListSimpleCircular->getPos(myElement);
            cout << "Your elemen is: " << myElement;
            _getch();
            break;
        case 3:
            cout << "Your element to find: ";
            cin >> myElement;

            if (myListSimpleCircular->findElem(myElement)) {
                cout << "Yes, your element is here";
            }
            else {
                cout << "Know, your element is not here";
            }
            _getch();
            break;
        case 4:
            cout << "Your pos: ";
            cin >> myElement;
            myListSimpleCircular->deletePos(myElement);
            cout << "All ok";
            --c;
            _getch();
            break;
        case 5:
            cout << "Your element is: ";
            cin >> myElement;
            pos = myListSimpleCircular->findPos(myElement);
            cout << "The position is: " << pos;
            _getch();
            break;
        case 6:
            for (auto f : *myListSimpleCircular) {
                cout << f << "->";
            }
            _getch();
            break;
        }

    }

    return 0;
}