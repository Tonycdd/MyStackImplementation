#pragma once
#include <iostream>

template<class T>
struct Node
{
    Node* next = nullptr;
    T data;

    Node(const T& value):data(value), next(nullptr){};
};


template <class T>
class Stack
{
private:
    Node<T>* top;
    std::size_t size;     
    void clear()
    {
        Node<T>* curr = this->top;
        while (curr)
        {
           Node<T>* toDel = curr;
           curr = curr->next;
           delete toDel;
           size--;
        }
        top = nullptr;
        // v sluchai che prexvurlim size_t
        size = 0;
    }   

    void copy(const Stack<T>& other){
        this->clear();

        if(!other.top){
            this->top = nullptr;
            this->size = 0;
            return;
        }

        // ako other e validen stack i ima elementi, pone edin, to:
        // nie sme iztrili veche nashiqt, togava;
        // Създаване на първия елемент от other
        this->top = new Node<T>(other.top->data);
        this->size = 1;  // Увеличаваме размера за първия елемент

        Node<T>* otherTop = other.top->next;

        // Добавяне на останалите елементи в обратен ред
         while (otherTop) {
            Node<T>* newCurr = new Node<T>(otherTop->data);
            newCurr->next = this->top;
            this->top = newCurr;
            otherTop = otherTop->next;
            this->size++;  // Увеличаваме размера за всеки нов добавен елемент
        }
    }

public:
    //default ctor
    Stack() :size(0), top(nullptr){};
    //copy
    Stack(const Stack<T>& other) : top(nullptr), size(0){
        this->copy(other);

    };
    //operator =
    Stack<T>& operator=(const Stack<T>& other){
        if(this != &other){
           this->copy(other);
        }
        return *this;
    }
    //dtor
    ~Stack(){
        this->clear();
    }


    // pushvame element v steka, nai-otgore
    void push(const T& value) {
        try {
            Node<T>* newNode = new Node<T>(value);
            newNode->next = this->top;
            this->top = newNode;
            size++;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Stack overflow: " << e.what() << std::endl;
        }
    }

    //premaxvame elementa na vurxa na steka
    void pop(){
        //prazen stek
        if (!this->top)
        {
            std::cerr << "Empty stack!" << std::endl;
            return;
        }
        //inache imame pone edin element;
        Node<T>* toDel = this->top;
        this->top = this->top->next;
        delete toDel;
        size--;
    };

    //da vidim elementa na vurxa na steka
    T& peek(){
        if (!this->top) {
            throw std::out_of_range("Empty stack!");
        }
        return this->top->data;
    };

    const T& peek() const {
        if (!this->top) {
            throw std::out_of_range("Empty stack!");
        }
        return this->top->data;
    };


    bool isEmpty()const
    {
        return this->size == 0;
    };

    void print()const{
        Node<T>* cur = this->top;
        while(cur)
        {
            std::cout << cur->data;
            if (cur->next)
            {
                std::cout << "->";
            }
            cur=cur->next;
        }
    };

};