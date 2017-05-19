#include "alert.h"
#include <iostream>

using namespace std;

Alert::Alert(QObject *parent) : QObject(parent)
{

}

Alert::~Alert()
{
    cout<<"Object destroyed!!!!"<<endl;
}

void Alert::a()
{
    cout<<qPrintable("Thread finished!!!");
}
