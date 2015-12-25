#ifndef SLEEPER_H
#define SLEEPER_H

#include <QThread>

class Sleeper : public QThread
{
public:
    static void sleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

#endif // SLEEPER_H
