//
//  Matrix.hpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <fstream>
#include "Coordinate.hpp"

class Matrix{
public:
    
    //Канонично представяне.
    //Конструктор по подразниране.
    Matrix();
    //Създава матрица по данните от подадения като параметър файл.
    Matrix(char* pathFile);
    //Деструктор
    ~Matrix();
    //Селектори за достъп до данните.
    Coordinate getSize() const;
    Coordinate getPositionTom()const;
    Coordinate getPositionJerry()const;
    char** getMatrix() const;

    void print() const;
    
private:
    char** matrix;
    Coordinate size;
    Coordinate tom;
    Coordinate jerry;
};

#endif /* Matrix_hpp */
