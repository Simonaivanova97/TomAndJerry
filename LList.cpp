//
//  LList.cpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include "LList.hpp"
template<typename T>
    LList<T>::LList(){
        start=end=nullptr;
    }

template<typename T>
    LList<T>::~LList(){
        deleteList();
    }

template<typename T>
    LList<T>::LList(const LList<T>& other){
        copyList(other);
    }

template<typename T>
    LList<T>& LList<T>::operator=(const LList<T>& other){
        if (this!=&other){
            deleteList();
            copyList(other);
        }
        return *this;
    }


template <typename T>
void LList<T>::iterStart(node<T>* p){
    if(p){
               current=p;
           }
           else{
               current=start;
           }
}

template <typename T>
    node<T>* LList<T>::iter(){
        node<T>* p=current;
        if(current){
            current=current->link;
        }
        return p;
    }

template<typename T>
    void LList<T>::toEnd(const T& x){
        node<T>* p=end;
        end=new node<T>;
        assert(end!=nullptr);
        end->inf=x;
        end->link=nullptr;
        if(p){
            p->link=end;
        }
        else{
            start=end;
        }
    }

template<typename T>
    void LList<T>::deleteAfter(node<T>* p,T& x){
        if(p->link){
            node<T>* q=p->link;
            x=q->inf;
            p->link=q->link;
            if(q==end){
                end=p;
            }
            delete q;
        }
        else{
            cout<<"There is not an element after p"<<endl;
            exit(1);
        }
    }

    template<typename T>
    void LList<T>::deleteElem(node<T>* p,T& x){
        if(p==start){
            x=p->inf;
            if(start==end){
                start=end=nullptr;
            }
            else{
                start=start->link;
            }
            delete p;
        }
        else{
            node<T>* q=start;
            while(q->link!=p){
                q=q->link;
            }
            deleteAfter(q,x);
        }
    }

template<typename T>
    void LList<T>::print() const{
        node<T>* p=start;
        while(p){
            cout<<p->inf<<" ";
            p=p->link;
        }
        cout<<endl;
    }
    

template<typename T>
    int LList<T>::findLen() const{
        node<T>* p=start;
        int len=0;
        while(p){
            len++;
            p=p->link;
        }
        return len;
    }

template<typename T>
    void LList<T>::copyList(const LList<T>& other){
        node<T>* p=other.start;
        node<T>* q;
        if(other.start){
            start =new node<T>;
            assert(start!=nullptr);
            end=start;
            while(p){
                end->inf=p->inf;
                end->link=nullptr;
                p=p->link;
                if(p){
                    q=end;
                    end=new node<T>;
                    assert(end!=nullptr);
                    q->link=end;
                }
            }
        }
        else{
            start=end=nullptr;
        }
    }

template<typename T>
    void LList<T>::deleteList(){
        node<T>* p;
        while(start){
            p=start;
            start=start->link;
            delete p;
            p=nullptr;
        }
        end=nullptr;
    }

template <typename T>
bool member(const T& x,LList<T>& l){
    l.iterStart();
    node<T>* p=l.iter();
    while(p && p->inf!=x){
        p=p->link;
    }
    return p !=nullptr;
}

template<typename T>
void deleteLast(LList<T>& l){
    l.iterStart();
    T x;
    node<T>* p=l.iter();
    while(p->link){
        p=l.iter();
    }
    l.deleteElem(p, x);
}
