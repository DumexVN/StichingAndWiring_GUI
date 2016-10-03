#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "vertex.h"
#include "graph.h"

#include <QUndoCommand>

class Algorithm
{

public:
    Algorithm(QList<Vertex *> myVertexList, int vCase);

    int isQualified();
    bool isConnected();

    void EulerPath();
    QList<Vertex *> getEulerTour();
    void Fleury(Vertex *startVertex);
    bool validEdges(Vertex *startVertex, Vertex *adjVertex);
    void findBridge();
    void DFS(Vertex *, Vertex *, int);

    QList<Vertex*> getoddList();
    QList<Vertex*> semiEulerization();

    void resetAdj();
    QString message();

    QList<Vertex*> sortPoint(QList<Vertex *>);
    void initialise();
    void depthfirstsearch(Vertex *, int, int);
    void retrieveConnectedComponents();
    void conversion();
    QQueue<Vertex *> callingcomparedistance();
    QQueue<Vertex *> connectComponents();

    QList<QPair<int, int> > compareMinDistance(QList<Vertex*>, QList<Vertex*>);
    QList<int> singleSourceComparison(qreal, QList<qreal>);
    QList<int> singleComparison(QList<qreal> sortedVList, int leftindex, int rightindex, qreal value, QList<int> minValues);

private:
    int vertexCase;
    int timer;

    QList<Vertex *> vertexList;

    QList<int> myLowArray;
    QList<int> myPreArray;

    QList<int> visited;
    QList<QList<Vertex *> > myConnectedComponents;

    QList<Vertex *> myBridge;
    QList<Vertex *> myEulerTour;

    QUndoStack *vertexStack;
};

#endif // ALGORITHM_H
