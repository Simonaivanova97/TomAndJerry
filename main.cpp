//
//  main.cpp
//  TomAndJerry
//
//  Created by Simona Ivanova on 11.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include <vector>
#include<string>
#include "Graph.cpp"

// Функция, която намира колко е дължината на на-късия път/късите пътища.
int findMinSizePath(const vector<string>& vec){
    //Намираме колко е дълът първият път, и приемаме че той е най-късия.
    int min=0;
    for (int i=0;i<vec[0].size();i++){
        if(vec[0][i]=='W' || vec[0][i]=='E' || vec[0][i]=='S' || vec[0][i]=='N'){
            min++;
        }
    }

    // Проверяваме дали измежду другите пътища, има някои с по-малка дължина, и ако да то това е дължината на най-късия път.
    for (int i=0;i<vec.size();i++){
        int lenOfTempElem=0;
        for(int j=0;j<vec[i].size();j++){
            if(vec[i][j]=='W' || vec[i][j]=='E' || vec[i][j]=='S' || vec[i][j]=='N'){
                lenOfTempElem++;
            }
        }
        if(lenOfTempElem<min){
            min=lenOfTempElem;
        }
    }
    return min;
}

//Функция, която намира броя на цифрите на едно число. Нужна ми е за да обработвам числата в матрицата.
int countDigit(int n){
    int count=0;
    if(n==0){
        count=1;
    }
    else{
        while(n>0){
            n/=10;
            count++;
        }
    }
    return count;
}

//Функция, която създава граф, като използва данните от стаята(матрицата).
void creategraph(Graph<int> &g,Matrix &m){
    int row=m.getSize().getX();
    int col=m.getSize().getY();
    int numberOfCol=m.getSize().getY()+1;
    int deg=countDigit(numberOfCol);
    //Добавяме всички елементи на матрицата, като върхове в графа.
    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int currentNumber=((i+1)*(pow(10,deg)))+(j+1);
            g.addTop(currentNumber);
        }
    }
    
    //Добавяме ребрата между върховете.
    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int currentNumber=((i+1)*pow(10,deg))+(j+1);
            Coordinate current=Coordinate(i,j);
            int up=0,down=0,right=0,left=0;
            Coordinate cUp,cDown,cRight,cLeft;
            //Ако текущата позиция не е мебел.
            if(m.getMatrix()[current.getX()][current.getY()]!='F'){
                //Ако текущия елемент има горен съсед.
                if(i+1-1>0){
                    up=((i+1-1)*pow(10,deg))+(j+1);
                    cUp=Coordinate(i-1,j);
                    //Ако горният съсед не е мебел, то добавяме ребро.
                    if(m.getMatrix()[cUp.getX()][cUp.getY()]!='F'){
                        g.addRib(currentNumber, up);
                    }
                }
                //Ако текущия елемент има долен съсед.
                if(i+1+1<row+1){
                    down=((i+1+1)*pow(10,deg))+(j+1);
                    cDown=Coordinate(i+1,j);
                    //Ако долният съсед не е мебел, то добавяме ребро.
                    if(m.getMatrix()[cDown.getX()][cDown.getY()]!='F'){
                        g.addRib(currentNumber, down);
                    }
                }
                //Ако текущия елемент има десен съсед.
                if(j+1+1<col+1){
                    right=((i+1)*pow(10,deg))+(j+1+1);
                    cRight=Coordinate(i,j+1);
                    //Ако десният съсед не е мебел, то добавяме ребро.
                    if(m.getMatrix()[cRight.getX()][cRight.getY()]!='F'){
                        g.addRib(currentNumber, right);
                    }
                }
                //Ако текущия елемент има ляв съсед.
                if(j+1-1>0){
                    left=((i+1)*pow(10,deg))+(j+1-1);
                    cLeft=Coordinate(i,j-1);
                    //Ако левият съсед не е мебел, то добавяме ребро.
                    if(m.getMatrix()[cLeft.getX()][cLeft.getY()]!='F'){
                        g.addRib(currentNumber, left);
                    }
                }
            }
        }
    }
}

vector<LList<int>> allPaths;
bool flag=false;
//Функция, която намира всички пътища в даден граф.
template<typename T>
vector<LList<T>> allways(const T& a, const T& b ,Graph<T>& g,LList<T>& l){
    l.toEnd(a);
    if(a==b){
        flag=true;
        //l.print();
        allPaths.push_back(l);
    }
    else{
        node<T>* q=g.point(a);
        q=q->link;
        while(q){
            if(!(member(q->inf,l))){
                allways(q->inf, b, g, l);
                deleteLast(l);
            }
            q=q->link;
        }
    }
    return allPaths;
}

//Функция,която връща string, който представлява указания път намиран със съкратените посоки.
template<typename T>
string pathWithDirection(LList<T> l,int degree,Matrix& m){
    string result;
    Coordinate c;
    l.iterStart();
    node<T>* p=l.iter();
    result="T->";
    while(p->link){
        int a=pow(10,degree);
        int coordinateY=p->inf%a;
        int coordinateX=p->inf/pow(10,degree);
        c=Coordinate(coordinateX-1,coordinateY-1);
        
        if((p->inf)==((p->link->inf)-1)){
           if(m.getMatrix()[c.getX()][c.getY()]=='P'){
                result += "P->";
            }
            result += "E->";
        }
        else if((p->inf)==((p->link->inf)+1)){
            if(m.getMatrix()[c.getX()][c.getY()]=='P'){
                result += "P->";
            }
            result += "W->";
        }
        else if((p->inf)==((p->link->inf)+(pow(10,degree)))){
            if(m.getMatrix()[c.getX()][c.getY()]=='P'){
                result += "P->";
            }
            result += "N->";
        }
        else if((p->inf)==((p->link->inf)-(pow(10,degree)))){
            if(m.getMatrix()[c.getX()][c.getY()]=='P'){
                result += "P->";
            }
            result += "S->";
        }
        p=p->link;
    }
    result += "J";
    return result;
}

//За конкретен път извежда, какви команди трябва да въведе Тон на дрона си.
template <typename T>
void printCommand(const LList<T>& path,Matrix& m){
    int i=0;
    int numberOfCol=m.getSize().getY()+1;
    int deg=countDigit(numberOfCol);
    string sPath=pathWithDirection(path, deg,m);
    while(sPath[i]!='J'){
        if(sPath[i]=='N'){
            cout<<"The drone is going North."<<endl;
        }
        else if(sPath[i]=='E'){
            cout<<"The drone is going East."<<endl;
        }
        else if(sPath[i]=='S'){
            cout<<"The drone is going South."<<endl;
        }
        else if(sPath[i]=='W'){
            cout<<"The drone is going West."<<endl;
        }
        else if(sPath[i]=='P'){
            cout<<"Paint."<<endl;
        }
        i+=3;
    }
}

//Намира броя на местата с боя по указания път.
template<typename T>
int findNumberOfPaintInPath(LList<T>& path,Matrix& m){
    int countPaint=0;
    int numberOfCol=m.getSize().getY()+1;
    int deg=countDigit(numberOfCol);
    path.iterStart();
    node<T>* p=path.iter();
    while(p->link){
        int getCoordinateX=(p->inf)/(pow(10,deg));
        int num=pow(10,deg);
        int getCoordinateY=(p->inf)%num;
        //cout<<m.getMatrix()[getCoordinateX-1][getCoordinateY-1]<<endl;
        if(m.getMatrix()[getCoordinateX-1][getCoordinateY-1]=='P'){
            countPaint++;
        }
        p=p->link;
    }
    return countPaint;
}

//Намира броя на завоите в даден път.
template<typename T>
int numberOfTurnsInPath(const LList<T>& path,Matrix& m){
    int countTurns=0;
    int numberOfCol=m.getSize().getY()+1;
    int deg=countDigit(numberOfCol);
    string sPath=pathWithDirection(path, deg,m);
    int i=0;
    while(sPath[i+3]!='J'){
        //cout<<sPath[i]<<" "<<sPath[i+3]<<endl;
        if((sPath[i]=='N' && sPath[i+3]=='E') || (sPath[i]=='N' && sPath[i+3]=='W') ||
           (sPath[i]=='E' && sPath[i+3]=='N') || (sPath[i]=='E' && sPath[i+3]=='S') ||
           (sPath[i]=='S' && sPath[i+3]=='E') || (sPath[i]=='S' && sPath[i+3]=='W') ||
           (sPath[i]=='W' && sPath[i+3]=='N') || (sPath[i]=='W' && sPath[i+3]=='S')){
            countTurns++;
        }
        i+=3;
    }
    return countTurns;
}

//Намира пътя/пътищата с максимално разливане на боя и минимален брои завои.
template <typename T>
vector<LList<T>> findThisPathsMaxPaint(vector<LList<T>>& q,Matrix& m){

    int max=findNumberOfPaintInPath(q.front(), m);
    for (int i=0;i<q.size();i++){
        if(max<findNumberOfPaintInPath(q[i], m)){
            max=findNumberOfPaintInPath(q[i], m);
        }
    }
    
    vector<LList<T>> maxPaintPath;
    for (int i=0;i<q.size();i++){
        if(findNumberOfPaintInPath(q[i], m)==max){
            maxPaintPath.push_back(q[i]);
        }
    }
    return maxPaintPath;
}

template<typename T>
vector<LList<T>> findPathsMaxPaintMinTurns(vector<LList<T>>& q,Matrix& m){
    vector<LList<T>> maxPaintPath=findThisPathsMaxPaint(q, m);
    int minTurns=numberOfTurnsInPath(maxPaintPath[0], m);
    for (int i=0;i<maxPaintPath.size();i++){
        if(numberOfTurnsInPath(maxPaintPath[i], m)<minTurns){
            minTurns=numberOfTurnsInPath(maxPaintPath[i], m);
        }
    }
    
    vector<LList<T>> maxPaintMinTurnPath;
    for (int i=0;i<maxPaintPath.size();i++){
        if(numberOfTurnsInPath(maxPaintPath[i], m)==minTurns){
            maxPaintMinTurnPath.push_back(maxPaintPath[i]);
        }
    }
    return maxPaintMinTurnPath;
}

//Пътищата, по които могат да мината двата дрона, така че да разлеят максимално боя, като стигнат едновременно и възможно най-бързо. Взимат се най-късите пътища, защото пише възможно най-бързо, и от тях взимаме два от тях, които са различни и разливат най-много боя.
template<typename T>
void twoDrone(vector<LList<T>>& q,Matrix& m){
    int numberOfColum=m.getSize().getY()+1;
    int deg=countDigit(numberOfColum);
    int maxPaint=0;

    for (int i=0;i<q.size()-1;i++){
        int countPaintFirstPath=findNumberOfPaintInPath(q[i], m);
        for(int j=i+1;j<q.size();j++){
            int countPaintSecondPath=findNumberOfPaintInPath(q[j], m);
            if(maxPaint<(countPaintFirstPath+countPaintSecondPath)){
                maxPaint=countPaintFirstPath+countPaintSecondPath;
            }
        }
    }
    
    if(q.size()==1){
        cout<<"There is only one path form Tom to Jerry, and the two drones pass over it:"<<endl;
        cout<<pathWithDirection(q.front(), deg,m)<<endl;
    }
    else{
        for (int i=0;i<q.size()-1;i++){
            int countPaintFirstPath=findNumberOfPaintInPath(q[i], m);
            for (int j=i+1;j<q.size();j++){
                int countPaintSecondPath=findNumberOfPaintInPath(q[j], m);
                if(maxPaint==countPaintFirstPath+countPaintSecondPath){
                    cout<<"Drone 1: "<<pathWithDirection(q[i], deg,m)<<endl;
                    cout<<"Drone 2: "<<pathWithDirection(q[j], deg,m)<<endl;
                    cout<<endl;
                }
            }
        }
    }
}

//От всични пътища, по които се разлива най-много боя, се извеждат, ако има такива, два с равна дължина и при това най-малка.
template<typename T>
void otherTwoDrone(vector<LList<T>>& q,Matrix& m){
    int numberOfColum=m.getSize().getY()+1;
    int deg=countDigit(numberOfColum);
    vector<LList<T>> pathMaxPaint=findThisPathsMaxPaint(q, m);
    vector<LList<T>> result;

    bool havePathsWithSameLen=false;
    int minLenOfPair=pathMaxPaint[0].findLen();
    for(int i=0;i<pathMaxPaint.size()-1;i++){
        for(int j=i+1;j<pathMaxPaint.size();j++){
            if(pathMaxPaint[i].findLen()==pathMaxPaint[j].findLen()){
                havePathsWithSameLen=true;
                if(pathMaxPaint[i].findLen()<minLenOfPair){
                    minLenOfPair=pathMaxPaint[i].findLen();
                }
            }
        }
    }
    
    if(havePathsWithSameLen){
        for(int i=0;i<pathMaxPaint.size();i++){
            if(pathMaxPaint[i].findLen()==minLenOfPair){
                result.push_back(pathMaxPaint[i]);
            }
        }
        for(int i=0;i<result.size()-1;i++){
            for(int j=i+1;j<result.size();j++){
                cout<<"Drone 1: "<<pathWithDirection(result[i], deg,m)<<endl;
                cout<<"Drone 2: "<<pathWithDirection(result[j], deg,m)<<endl;
            }
        }
    }
    else{
        cout<<"There is no path with same length."<<endl;
    }
}

int main() {
    
    Matrix m=Matrix("room.txt");
    cout<<"The room"<<endl;
    m.print();
    cout<<endl;
    
    int numberOfColum=m.getSize().getY()+1;
    int deg=countDigit(numberOfColum);
    int xPositionTom=m.getPositionTom().getX();
    int yPositionTom=m.getPositionTom().getY();
    int startPosition=((xPositionTom+1)*pow(10,deg))+(yPositionTom+1);
    
    int xPositionJerry=m.getPositionJerry().getX();
    int yPositionJerry=m.getPositionJerry().getY();
    int endPosition=((xPositionJerry+1)*pow(10,deg))+(yPositionJerry+1);
    
    Graph<int> g;
    creategraph(g, m);
    LList<int> l;
    vector<LList<int>> allPaths=allways(startPosition, endPosition, g,l);

    if(allPaths.empty()){
        cout<<"There is no path from Tom to Jerry."<<endl;
    }
    else{
        vector<string> allpaths;
        vector<string> minPaths;
    
        cout<<"Print all paths: "<<endl;
        for (int i=0;i<allPaths.size();i++){
            string path=pathWithDirection(allPaths[i],deg,m);
            allpaths.push_back(path);
        }
        for (int i=0;i<allpaths.size();i++){
            cout<<allpaths[i]<<endl;
        }
        cout<<endl;
    
        vector<LList<int>> saveMinPaths;
        cout<<"The shortest path/paths is/are: "<<endl;
        for (int i=0;i<allPaths.size();i++){
            int currentLen=allPaths[i].findLen()-1;
            if(currentLen==findMinSizePath(allpaths)){
                minPaths.push_back(pathWithDirection(allPaths[i],deg,m));
                saveMinPaths.push_back(allPaths[i]);
            }
        }
        for(int i=0;i<minPaths.size();i++){
            cout<<"Shortes path "<<i+1<<": "<<minPaths[i]<<endl;
        }
    
        int x;
        do{
            cout<<"Choose one of the shortest paths to show you detailed information about it: ";
            cin>>x;
        }while(x<=0 || x>minPaths.size());
        cout<<endl;
        
        for(int i=0;i<minPaths.size();i++){
            if(x==i+1){
                cout<<"The commands that Tom must enter on his drone are:"<<endl;
                printCommand(saveMinPaths[i],m);
                cout<<"The number of paint on this path is: "<<findNumberOfPaintInPath(saveMinPaths[i], m)<<endl;
                cout<<"The number of turns on this path is: "<<numberOfTurnsInPath(saveMinPaths[i],m)<<endl;
                cout<<"The length of the path is: "<<findMinSizePath(allpaths)<<endl;
            }
        }
        cout<<endl;
        
        cout<<"Path/Paths with max paint and min turns is: "<<endl;
        vector<LList<int>> some=findPathsMaxPaintMinTurns(allPaths, m);
        for (int i=0;i<some.size();i++){
            cout<<pathWithDirection(some[i], deg,m)<<endl;
        }
        cout<<endl;

        cout<<"--- Two drone ---"<<endl;
        
        //Двата дрона минават, по най-късите пътища, които са изведени по-горе, така че да разлеят максимално количество боя.
        cout<<"The ways that Tom can navigate two drone. The different ways in which the two drones pass by the shortest paths (reach Jerry as quickly as possible) and spill the maximum amount of paint."<<endl;
        twoDrone(saveMinPaths,m);
        
        //Двата дрона минават по два пътя с равна дължина (при това най-къса от всички пътища с максимално разливане на боя) , през които се разлива най-голямо количесто боя.
        cout<<"The ways that Tom can navigate two drone. The two drones pass on two roads of equal length (the shortest of all roads with maximum paint spillage), through which the largest amount of paint is spilled."<<endl;
        otherTwoDrone(allPaths, m);
    }
    
    
    return 0;
}

