//
//  Graph.hpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include "LList.cpp"
#include "Matrix.hpp"


template <typename T>
class Graph{
public:
    void addTop(const T& a);
    void deleteTop(const T& a);
    void addRib(const T& a, const T& b);
    void deleteRib(const T& a,const T& b);
    bool top(const T& a);
    bool rib(const T& a,const T& b);
    bool empty() const;
    node<T>* point(const T& a);
    LList<T> vertexes();
    void print();
    
private:
    LList< LList<T> > g;
    
};

#endif /* Graph_hpp */
