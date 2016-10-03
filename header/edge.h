#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>

#include "vertex.h"

class Edge : public virtual QGraphicsLineItem
{
public:
    Edge(Vertex *fromVertex, Vertex *toVertex);
    ~Edge();

    Vertex *fromVertex() const;
    Vertex *toVertex() const;

    void setColor(const QColor &color);
    QColor color() const;
    void trackVertex();
    void setBackPen(const QColor &color);
    bool isBackEdge();
    void setBackEdge(bool);
    Vertex* getMyFromVertex();
    Vertex* getMyToVertex();
private:
    Vertex *myFromVertex;
    Vertex *myToVertex;
    bool backEdge;
};

#endif // EDGE_H
