//
//  Graph.cpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include "Graph.hpp"
template <typename T>
    void Graph<T>::addTop(const T& a){
        LList<T> l;
        l.toEnd(a);
        g.toEnd(l);
    }

template <typename T>
    void Graph<T>::deleteTop(const T& a){
        g.iterStart();
        node<LList<T>>* p=g.iter(), *r;
        while(p){
            p->inf.iterStart();
            node<T>* q=p->inf.iter();
            if(rib(q->inf,a)){
                deleteRib(q->inf,a);
            }
            p=p->link;
        }
        g.iterStart();
        node<T>* q;
        do{
            r=g.iter();
            r->inf.iterStart();
            q=r->inf.iter();
        }while(q->inf !=a);
        LList<T> x;
        g.deleteElem(r,x);
    }

template <typename T>
    void Graph<T>::addRib(const T& a, const T& b){
        node<T>* q=point(a), *p;
        p=new node<T>;
        assert(p!=nullptr);
        p->inf=b;
        p->link=q->link;
        q->link=p;
    }

template <typename T>
void Graph<T>::deleteRib(const T& a,const T& b){
        g.iterStart();
        node<LList<T>>* p;
        node<T>* q;
        do{
            p=g.iter();
            p->inf.iterStart();
            q=p->inf.iter();
        }while(q->inf!=a);
        q=q->link;
        while(q->inf !=b){
            q=q->link;
        }
        T x;
        p->inf.deleteElem(q,x);
    }

template <typename T>
    bool Graph<T>::top(const T& a){
        if(g.empty()){
            return false;
        }
        g.iterStart();
        node<LList<T>> *p=g.iter();
        node<T>* q;
        do{
            p->inf.iterStart();
            q=p->inf.iter();
            p=p->link;
        }while(q->inf!=a && p);
        return q->inf == a;
    }

template <typename T>
    bool Graph<T>::rib(const T& a,const T& b){
        node<T>* p=point(a);
        p=p->link;
        while(p && p->inf!=b ){
            p=p->link;
        }
        return p!=nullptr;
    }

template <typename T>
    bool Graph<T>::empty() const{
        return g.empty();
    }

template <typename T>
    node<T>* Graph<T>::point(const T& a){
        g.iterStart();
        node<LList<T>>* p;
        node<T>* q;
        do{
            p=g.iter();
            p->inf.iterStart();
            q=p->inf.iter();
        }while((q->inf)!=a);
        return q;
    }
    
template <typename T>
    LList<T> Graph<T>::vertexes(){
        LList<T> l;
        g.iterStart();
        node<LList<T>>* p=g.iter();
        while(p){
            p->inf.iterStart();
            node<T>* q=p->inf.iter();
            l.toEnd(q->inf);
            p=p->link;
        }
        return l;
    }
    
template <typename T>
    void Graph<T>::print(){
        g.iterStart();
        node<LList<T>>* p=g.iter();
        while(p){
            p->inf.print();
            p=p->link;
        }
        cout<<endl;
    }
