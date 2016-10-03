#ifndef ALGORITHMTHREAD_H
#define ALGORITHMTHREAD_H

#include <QImage>
#include <QMutex>
#include <QQueue>
#include <QThread>
#include <QWaitCondition>

#include "vertex.h"

class Algorithm;

class AlgorithmThread : public QThread
{
    Q_OBJECT
public:
    AlgorithmThread();
    ~AlgorithmThread();

    void addAlgorithm(Algorithm *algorithm);
    QList<Vertex *> getEulerTour();
    void resetTour();
protected:
    void run();

signals:
    void algorithmStarted(const QString &message);
    void allAlgorithmsDone();

private:
    QQueue<Algorithm *> algorithms;
    QWaitCondition algorithmsAdded;
    QMutex mutex;
    QList<Vertex *> myEulerTour;
};

#endif // ALGORITHMTHREAD_H
