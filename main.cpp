#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QFuture>
#include <iostream>
#include <QReadWriteLock>


using namespace std;

int run1(int firstArg, int secondArg)
{
    for(int i=firstArg;i<secondArg;i++)
    {
        cout<<qPrintable(QString("This is "))<<firstArg<<qPrintable(QString(" "))<<i
           <<qPrintable(QString("!!!"))<<endl;
    }
    return firstArg*secondArg;
}

void run2(int* number, int id, QReadWriteLock* lock)
{
    if(id==1)
    {
        cout<<endl<<qPrintable(QString("First start!"))<<endl;
        for(int i=0;i<10;i++)
        {
            lock->lockForWrite();
            *number=i;
            QThread::sleep(3);
            lock->unlock();
        }
        cout<<endl<<qPrintable(QString("First end!"))<<endl;
    }
    else
    {
        for(int i=0;i<10;i++)
        {
            cout<<qPrintable(QString("Try to write!"))<<endl;
            lock->lockForWrite();
            cout<<qPrintable(QString("I did it!"))<<endl;
            (*number)++;
            cout<<*number<<endl;
            QThread::sleep(1);
            lock->unlock();
        }
        cout<<endl<<qPrintable(QString("Second end!"))<<endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*QFuture<int> thread1=QtConcurrent::run(run1,1,10);
    QFuture<int> thread2=QtConcurrent::run(run1,2,11);
    QFuture<int> thread3=QtConcurrent::run(run1,3,12);
    QFutureWatcher<int> watcher;
    watcher.setFuture(thread1);

    cout<<qPrintable(QString("First result: "))<<thread1.result()<<endl;
    cout<<qPrintable(QString("Second result: "))<<thread2.result()<<endl;
    cout<<qPrintable(QString("Third result: "))<<thread3.result()<<endl;*/

    int number=-1;
    QReadWriteLock lock;

    QFuture<void> thread1=QtConcurrent::run(run2,&number,1,&lock);
    QFuture<void> thread2=QtConcurrent::run(run2,&number,2,&lock);

    cout<<qPrintable(QString("Thread cout: "))<<QThread::idealThreadCount()<<endl;
    return a.exec();
}
