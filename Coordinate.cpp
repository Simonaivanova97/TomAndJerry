//
//  Coordinate.cpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include "Coordinate.hpp"
Coordinate::Coordinate(){
    x=0;
    y=0;
}
Coordinate::Coordinate(int nX, int nY){
    x=nX;
    y=nY;
}

Coordinate::Coordinate(string coordinates){
    int i=0;
    int lenX=0;
    while(coordinates[i]!=' '){
        i++;
        lenX++;
    }
    int lenY=(coordinates.length())-1-lenX;
    char* cX=new char[lenX+1];
    char* cY=new char[lenY+1];
    i=0;
    while(coordinates[i]!=' '){
        cX[i]=coordinates[i];
        i++;
    }
    i=lenX+1;
    int j=0;
    while(coordinates[i]!='\0'){
        cY[j]=coordinates[i];
        i++;
        j++;
    }
    x=counvertFromCharToInt(cX);
    y=counvertFromCharToInt(cY);
    cX=nullptr;
    cY=nullptr;
    delete cX;
    delete cY;
}

int Coordinate::getX() const{
    return x;
}
int Coordinate::getY() const{
    return y;
}

void Coordinate::print() const{
    cout<<"["<<x<<";"<<y<<"]"<<endl;
}
int Coordinate::counvertFromCharToInt(const char* c) const{
    int i=0;
    int len=0;
    while(c[i]!='\0'){
        len++;
        i++;
    }
    int degree=len-1;
    int result=0;
    i=0;
    while(c[i]!='\0'){
        int currentNumber=c[i]-48;
        result+=(currentNumber*(pow(10,degree)));
        degree--;
        i++;
    }
    return result;
}

