//
//  Matrix.cpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include "Matrix.hpp"
Matrix::Matrix(){
    matrix=nullptr;
}

//Създава матрица по данните от подадения като параметър файл.
Matrix::Matrix(char* pathFile){
    fstream file(pathFile,ios::in);
    if(!file){
        cout<<"File not exist!"<<endl;
        exit(1);
    }
    else{
        string str;
        int numberOfFurniture=0;
        int numberCanPaint=0;
        int i=0;
        Coordinate c;
        Coordinate startPositionFurniture;
        Coordinate positionPaint;
        // Намиране размерността на матрицата.
        getline(file,str);
        size=Coordinate(str);
        //size.print();
        // Създаваме матрицата.
        matrix=new char*[size.getX()+1];
        for (int i=0;i<size.getX();i++){
            matrix[i]=new char[size.getY()+1];
        }
        //Попълваме матрицата със данните.
        while(getline(file,str)){
            if(i==0){
                jerry=Coordinate(str);
                matrix[jerry.getX()][jerry.getY()]='J';
            }
            else if(i==1){
                tom=Coordinate(str);
                matrix[tom.getX()][tom.getY()]='T';
            }
            else if(i==2){
                c=Coordinate(str);
                numberOfFurniture=c.getX();
                numberCanPaint=c.getY();
                if(numberOfFurniture>0){
                    for(int j=0;j<numberOfFurniture;j++){
                        getline(file,str);
                        startPositionFurniture=Coordinate(str);
                        int coutRowFurn=0;
                        while(str!="==="){
                            getline(file,str);
                            for (int k=0;k<str.length();k++){
                                if(str[k]=='1'){
                                    matrix[startPositionFurniture.getX()+coutRowFurn][startPositionFurniture.getY()+k]='F';
                                }
                            }
                            coutRowFurn++;
                        }
                    }
                }
                if(numberCanPaint>0){
                    for (int j=0;j<numberCanPaint;j++){
                        while(getline(file,str)){
                            positionPaint=Coordinate(str);
                            matrix[positionPaint.getX()][positionPaint.getY()]='P';
                        }
                    }
                }
            }
            i++;
        }
        //Запълваме останалите позиции в матрицата
        for (int i=0;i<size.getX();i++){
            for (int j=0;j<size.getY();j++){
                if(matrix[i][j]!='J' && matrix[i][j]!='T' && matrix[i][j]!='F' && matrix[i][j]!='P'){
                    matrix[i][j]='0';
                }
            }
        }
    }
    file.close();
}

//Деструктор
Matrix::~Matrix(){
    for(int i=0;i<size.getX();i++){
        delete []matrix[i];
    }
    delete []matrix;
}

Coordinate Matrix::getSize() const{
    return size;
}

Coordinate Matrix::getPositionTom()const{
    return tom;
}

Coordinate Matrix::getPositionJerry()const{
       return jerry;
   }

char** Matrix::getMatrix() const{
    char** temp=new char*[size.getX()+1];
    for(int i=0;i<size.getX();i++){
        temp[i]=new char [size.getY()+1];
    }
    
    for(int i=0;i<size.getX();i++){
        for(int j=0;j<size.getY();j++){
            temp[i][j]=matrix[i][j];
        }
    }
    return temp;
}

void Matrix::print() const{
    for (int i=0;i<size.getX();i++){
        for (int j=0;j<size.getY();j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
