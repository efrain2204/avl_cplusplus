#ifndef AVL_H
#define AVL_H


#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/* AVL node */
template <class T>
class node {
public:
    T dato;
    int FE;
    node *left, *right, *padre;
    node(T k, node *p) : dato(k), FE(0), padre(p),left(NULL), right(NULL) {}

    ~node() {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(T dato);
    void deletedato(const T dato);
    void display()const ;
private:
    node<T> *root;
    node<T>* rotateLeft          ( node<T> *a );
    node<T>* rotateRight         ( node<T> *a );
    node<T>* rotateLR ( node<T> *n );
    node<T>* rotateRL ( node<T> *n );
    void rebalance                  ( node<T> *n );
    int height                      ( node<T> *n );
    void setBalance                 ( node<T> *n );
    void print_dot(ostream &out, node<T>* p)const ;
    string dot()const ;

};

/* AVL class definition */
template <class T>
void AVLtree<T>::rebalance(node<T> *n) {
    setBalance(n);

    if (n->FE == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLR(n);
    }
    else if (n->FE == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRL(n);
    }

    if (n->padre != NULL) {
        rebalance(n->padre);
    }
    else {
        root = n;
    }
}

template <class T>
node<T>* AVLtree<T>::rotateLeft(node<T> *a) {
    node<T> *b = a->right;
    b->padre = a->padre;
    a->right = b->left;

    if (a->right != NULL)
        a->right->padre = a;

    b->left = a;
    a->padre = b;

    if (b->padre != NULL) {
        if (b->padre->right == a) {
            b->padre->right = b;
        }
        else {
            b->padre->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
node<T>* AVLtree<T>::rotateRight(node<T> *a) {
    node<T> *b = a->left;
    b->padre = a->padre;
    a->left = b->right;

    if (a->left != NULL)
        a->left->padre = a;

    b->right = a;
    a->padre = b;

    if (b->padre != NULL) {
        if (b->padre->right == a) {
            b->padre->right = b;
        }
        else {
            b->padre->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
node<T>* AVLtree<T>::rotateLR(node<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
node<T>* AVLtree<T>::rotateRL(node<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(node<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(node<T> *n) {
    n->FE = height(n->right) - height(n->left);
}


template <class T>
AVLtree<T>::AVLtree(void) : root(NULL) {}

template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T dato) {
    if (root == NULL) {
        root = new node<T>(dato, NULL);
    }
    else {
        node<T>
            *n = root,
            *padre;

        while (true) {
            if (n->dato == dato)
                return false;

            padre = n;

            bool goLeft = n->dato > dato;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    padre->left = new node<T>(dato, padre);
                }
                else {
                    padre->right = new node<T>(dato, padre);
                }

                rebalance(padre);
                break;
            }
        }
    }

    return true;
}

template <class T>
void AVLtree<T>::deletedato(const T deldato) {
    if (root == NULL)
        return;

    node<T>
        *n       = root,
        *padre  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        padre = n;
        n = child;
        child = deldato >= n->dato ? n->right : n->left;
        if (deldato == n->dato)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->dato = n->dato;

        child = n->left != NULL ? n->left : n->right;

        if (root->dato == deldato) {
            root = child;
        }
        else {
            if (padre->left == n) {
                padre->left = child;
            }
            else {
                padre->right = child;
            }

            rebalance(padre);
        }
    }
}


template<class T>
void AVLtree<T>::print_dot(ostream &out, node<T>* p)const
{
    if(p != NULL)
    {
        static int cont=0;
        out << p->dato << "[label=" << p->dato << ",fontcolor=black];\n";
        if (p->left){
            out << p->dato << " -> "<< p->left->dato << ";\n";
            }
        else{
            cont++;
            out << "Nodo"<<cont<<"[label=null,fillcolor=skyblue,fontcolor=black];\n";
            out << p->dato << " -> "<< "Nodo"<<cont<<";\n";
        }
        if (p->right){
            out << p->dato << " -> "<< p->right->dato << ";\n";
        }
        else{
            cont++;
            out<< "Nodo"<<cont<<"[label=null,fillcolor=skyblue,fontcolor=black];\n";
            out << p->dato << " -> "<< "Nodo"<<cont<<";\n";
        }
        print_dot(out, p->left);
        print_dot(out, p->right);
    }
}
template<class T>
string AVLtree<T>::dot()const
{
    stringstream stm;
    stm << "digraph {\ node [shape=circle, style=filled]\n";
    print_dot(stm, root);
    stm << "}\n";
    return stm.str();
}
template<class T>
void AVLtree<T>::display()const
{
    ofstream out("out.gv");
    out << dot() << endl;
    out.close();
    system("dot.exe -Tpng out.gv -o out.png");
}

#endif // AVL_H
