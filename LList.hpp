//
//  LList.hpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef LList_hpp
#define LList_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

template <typename T>
struct node{
    T inf;
    node<T>* link;
};

template <typename T>
class LList{
public:
    LList();
    ~LList();
    LList(const LList&);
    LList& operator=(const LList&);
    void iterStart(node<T>* = nullptr);
    node<T>* iter();
    void toEnd(const T& x);
    void deleteAfter(node<T>* p,T& x);
    
    void deleteElem(node<T>* p,T& x);
    void print() const;
    
    int findLen() const;
    bool member(const T& x,LList<T>& l);
    void deleteLast(LList<T>& l);
    
private:
    node<T>* start;
    node<T>* end;
    node<T>* current;

    void copyList(const LList& other);
    void deleteList();
};


#endif /* LList_hpp */
