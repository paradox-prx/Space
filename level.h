#include"enemy.h"
#include <iostream>
using namespace std;


class level{
public:
virtual void initialize() = 0;
virtual void update() = 0;
virtual bool isComplete() const = 0;
};


class levelOne:public level{
public:
void initialize(){

}

void update(){

}

bool isComplete(){

}
};

class levelTwo:public level{
public:
void initialize(){

}

void update(){

}

bool isComplete(){
    
}

};

class levelThree:public level{
public:
void initialize(){

}

void update(){

}

bool isComplete(){
    
}

};
