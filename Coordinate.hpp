//
//  Coordinate.hpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef Coordinate_hpp
#define Coordinate_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include<cmath>
using namespace std;

class Coordinate {
public:
    Coordinate();
    Coordinate(int,int);
    Coordinate(string coordinates);
    
    int getX() const;
    int getY() const;

    void print() const;
    
private:
    int x;
    int y;
    int counvertFromCharToInt(const char*) const;

};

#endif /* Coordinate_hpp */
