#include <iostream>
#include <functional>
#include <conio.h>

/*
Existen algunos errores en los métodos de la lista doble, tener presente
*/


using namespace std;

#ifndef __Lista_DoblementeEnlazada_H__
#define __Lista_DoblementeEnlazada_H__

template <typename T, T NADA = 0>
class ListaDoble {
    struct Node {
        T elem;
        Node* prev;
        Node* next;
        Node(T elem, Node* prev, Node* next) : elem(elem), prev(prev), next(next) {}
    };

    int len;
    Node* head;
public:
    ListaDoble() :len(0), head(nullptr) {}
    ~ListaDoble() {
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
        if (len == 0)
            head = new Node(0, nullptr, nullptr);

        Node* nuevo = new Node(n, head->prev, head);

        if (nuevo != nullptr) {
            head = nuevo;
            ++len;
        }
    }

    void addPos(T n, int pos) {
        if (pos < 0 || pos > len)
            return;
        if (pos == 0) {
            addFirst(n);
            return;
        }
            
        else {
            Node* aux = head;
            //auto aux = head; <- is correct
            for (int i = 1; i < pos; i++) {
                aux = aux->next;
            }
            aux->next = new Node(n, aux, aux->next);
            ++len;
        }
    }

    void addLast(T n) {
        addPos(n, len + 1);
    }

    //to get

    T getFirst() {
        return head->elem;
    }

    T getPos(int buscar) {
        auto aux = head;
        auto lamba_comparar = [](T comp, T buscar) {

            if (comp - buscar == 0)
                return true;
            else
                return false;

        };

        while (aux != nullptr) {

            if (lamba_comparar(aux->elem, buscar))
                return aux->elem;

            aux = aux->next;

        }
        return NADA;
    }

    T getLast() {
        return getPos(len - 1);
    }

    // my element is here?

    bool findElem(T n) {
        Node* aux = head;
        while (aux != nullptr) {
            if (aux->elem == n)
                return true;
            aux = aux->next;
        }
        return false;
    }

    //to remove

    void deleteFirst() {
        if (len > 0) {
            auto aux = head;
            head = head->next;
            delete aux;
            --len;
        }
    }

    void deletePos(int pos) {
        if (pos < 0 || pos >= len)
            return;
        if (pos == 0)
            deleteFirst();
        else {
            Node* aux = head;
            Node* aux2 = head->next;

            for (int i = 1; i < pos; i++) {
                if (i < pos - 1) {
                    aux = aux->next;
                    aux2 = aux2->next;
                }
            }
            if (pos != len) {
                Node* aux3 = aux2->next;
                aux3->prev = aux;
            }
            aux->next = aux2->next;

            delete aux2;
            len--;
        }
    }

    void deleteLas() {
        deletePos(len);
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
#endif // !__Lista_DoblementeEnlazada_H__

// a little example

int main() {
    ListaDoble<int>* myListDouble = new ListaDoble<int>();

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
            myListDouble->addPos(myElement, c);
            ++c;
            break;
        case 2:
            cout << "Your pos: ";
            cin >> myElement;
            myElement = myListDouble->getPos(myElement);
            cout << "Your elemen is: " << myElement;
            _getch();
            break;
        case 3:
            cout << "Your element to find: ";
            cin >> myElement;

            if (myListDouble->findElem(myElement)) {
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
            myListDouble->deletePos(myElement);
            cout << "All ok";
            --c;
            _getch();
            break;
        case 5:
            cout << "Your element is: ";
            cin >> myElement;
            pos = myListDouble->findPos(myElement);
            cout << "The position is: " << pos;
            _getch();
            break;
        case 6:
            for (auto f : *myListDouble) {
                cout << f << "->";
            }
            _getch();
            break;
        }

    }

    return 0;
}