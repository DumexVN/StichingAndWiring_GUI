#include "algorithmthread.h"
#include "algorithm.h"

// --- SPAWNING A THREAD TO PERFORM ALGORITHMS ---
Algorithm *EndAlgo = 0; //Define an ending algorithm which terminates the thread

AlgorithmThread::AlgorithmThread()
{ // --- START THE THREAD ---
    start();
}

AlgorithmThread::~AlgorithmThread()
{ // --- TERMINATE THE THREAD ---
    {
     QMutexLocker locker(&mutex);
     while (!algorithms.isEmpty())
     delete algorithms.dequeue();
     algorithms.enqueue(EndAlgo);
     algorithmsAdded.wakeOne();
     }
    wait();
}

void AlgorithmThread::addAlgorithm(Algorithm *algorithm)
{ // --- ADD AN ALGORITHM TO THE THREAD QUEUE ---
    QMutexLocker locker(&mutex);
    algorithms.enqueue(algorithm);
    algorithmsAdded.wakeOne();
}

void AlgorithmThread::run()
{ // --- RUN A THREAD ---
    Algorithm *algo = 0;
    forever{
    QMutexLocker locker(&mutex);
    if (algorithms.empty())
    {   // if the queue is empty, wait!
        algorithmsAdded.wait(&mutex);
    }
        algo = algorithms.dequeue();
        // dequeue
        if (algo == EndAlgo)
        { // if its an ending signal
            break;
        }
        else emit algorithmStarted(algo->message());
        myEulerTour = algo->getEulerTour();
        algo->resetAdj();
        delete algo;
        if (algorithms.isEmpty())
        emit allAlgorithmsDone();
    }
}

QList<Vertex *> AlgorithmThread::getEulerTour()
{   // --- RETURN THE EULER TOUR ---
    return myEulerTour;
}

void AlgorithmThread::resetTour()
{  // --- RESET THE EULER TOUR (IN CASE OF REDRAWING) ---
    while(!myEulerTour.empty())
    {
        myEulerTour.removeFirst();
    }
}
