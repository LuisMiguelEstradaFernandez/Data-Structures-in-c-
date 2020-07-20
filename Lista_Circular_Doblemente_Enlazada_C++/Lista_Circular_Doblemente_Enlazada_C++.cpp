#include <iostream>
#include <functional>
#include <conio.h>

/*
Existen algunos errores, pero esta es la idea
*/

using namespace std;

#ifndef __ListaCircular_DoblementeEnlazada_H__
#define __ListaCircular_DoblementeEnlazada_H__

template <typename T, T NADA = 0>
class ListDouble {
    struct Node {
        T elem;
        Node* prev;
        Node* next;
        Node(T elem, Node* prev = nullptr, Node* next = nullptr) : elem(elem), prev(prev), next(next) {}
    };

    int len;
    Node* head;
    Node* tail;
public:
    ListDouble() :len(0), head(nullptr), tail(nullptr) {}
    ~ListDouble() {
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
        Node* aux;
        if (len == 0) {
            aux = new Node(n, nullptr, nullptr);
            tail = aux;
            head = aux;
        }
        else {
            aux = new Node(n, nullptr, head);
            head->prev = aux;
            head = aux;
        }
        len++;
    }

    void addPos(T n, int pos) {
        if (pos < 0 || pos > len)
            return;
        if (pos == 0)
            addFirst(n);
        else {
            Node* aux;
            Node* help;

            if (pos < (len / 2)) {
                aux = head;

                for (int i = 1; i < pos; i++)
                    aux = aux->next;

                help = new Node(n, aux, aux->next);

                aux->next->prev = help;
                aux->next = help;
            }
            else {
                aux = tail;

                for (int i = len - 1; i > pos; --i)
                    aux = aux->prev;

                help = new Node(n, aux->prev, aux);

                aux->prev->next = help;
                aux->prev = help;
            }

            len++;
        }
    }

    void addLast(T n) {
        if (len < 0)
            return;

        else if (len == 0)
            addFirst(n);

        else {
            Node* help;

            help = new Node(n, tail, nullptr);

            tail->next = help;
            tail = help;
            len++;
        }
    }

    //to get

    T getFirst() {
        if(len > 0)
            return head->elem;
        return 0;
    }

    T getPos(int pos) {
        if (pos < 0 || pos >= len)
            return 0;

        else if (pos == 0)
            return getFirst();

        else if (pos == len - 1)
            return getLast();

        else {
            Node* aux;

            if (pos < (len / 2)) {
                aux = head;
                for (int i = 0; i < pos; i++)
                {
                    aux = aux->next;
                }
            }

            else {
                aux = tail;
                for (int i = len - 1; i > pos; i--)
                    aux = aux->prev;
            }

            return aux->elem;

        }
    }

    T getLast() {
        if (len > 0)
            return tail->elem;
        return 0;
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
            Node* aux;

            if (len == 1) {
                aux = head;
                head = nullptr;
                tail = nullptr;
            }

            else {
                aux = head;
                head = head->next;
                head->prev = nullptr;
            }

            delete aux;
            --len;
        }
    }

    void deletePos(int pos) {
        if (pos < 0 || pos >= len)
            return;
        if (pos == 0)
            deleteFirst();
        if (pos == len - 1)
            deleteLast();
        else {
            Node* aux;
            Node* help;
            Node* help2;

            if (pos < (len / 2)) {
                aux = head;
                for (int i = 0; i < pos; i++)
                    aux = aux->next;
            }
            else {
                aux = tail;
                for (int i = len - 1; i > pos; i--)
                    aux = aux->prev;
            }

            help = aux->prev;
            help2 = aux->next;

            help->next = help2;
            help2->prev = help;

            delete aux;
            --len;
        }
    }

    void deleteLast() {
        if (len == 0)
            return;
        else if (len == 1)
            deleteFirst();
        else
        {
            Node* aux = tail;
            tail = tail->prev;
            tail->next = nullptr;

            delete aux;
            --len;
        }
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

    void mostrar() {
        for (int i = 0; i < len; i++)
            cout << "Element: " << i << " : " << getPos(i) << endl;
    }

};
#endif // !__ListaCircular_DoblementeEnlazada_H__

// a little example

int main() {
    ListDouble<int>* myListDouble = new ListDouble<int>();

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