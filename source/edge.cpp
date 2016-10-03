#include <QtGui>
#include <QPainterPath>

#include "edge.h"
#include "vertex.h"

// --- EDGE CLASS ---
Edge::Edge(Vertex *fromVertex, Vertex *toVertex)
{ //--- INITIALISE AN EDGE ---
    //an edge must be drawn between 2 vertex
    myFromVertex = fromVertex;
    myToVertex = toVertex;
    //add this edge to its verteices' edge list
    myFromVertex->connectEdge(this);
    myToVertex->connectEdge(this);
    //add 2 vertices to each other's adjacency list
    myFromVertex->addAdjVertex(toVertex);
    myToVertex->addAdjVertex(fromVertex);
    //set the edge to be selectable
    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);
    backEdge = false;
    //set colour
    setColor(Qt::black);
    //draw the edge
    trackVertex();

}

Edge::~Edge()
{  // --- DESTROY AN EDGE ---
    //when destroy an edge, remove their according adjacency vertices
    myFromVertex->removeEdge(this);
    myToVertex->removeEdge(this);

    myFromVertex->removeAdjVertex(myToVertex);
    myToVertex->removeAdjVertex(myFromVertex);
}

void Edge::setColor(const QColor &color)
{// --- SET PEN'S WIDTH TO DRAW EDGE ---
    setPen(QPen(color, 1.0));
}

void Edge::trackVertex()
{//--- DRAW THE EDGE ONTO THE SCENE ---
    setLine(QLineF(myFromVertex->pos(), myToVertex->pos()));
}

QColor Edge::color() const
{//--- RETURN AN EDGE'S COLOUR ---
    return pen().color();
}

void Edge::setBackEdge(bool isBack)
{// --- SET THIS AS AN BACK EDGE ---
   backEdge = isBack;
   setBackPen(Qt::black);
}

bool Edge::isBackEdge()
{// --- CHECK IF THIS IS AN BACK EDGE ---
    return backEdge;
}

void Edge::setBackPen(const QColor &color)
{// --- USE A DIFFERENT PEN FOR BACKEDGE ---
    setPen(QPen(color, 1.0, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    update();
}

Vertex * Edge::getMyFromVertex()
{// --- RETURN A POINTER TO MYFROMVERTEX ---
    return myFromVertex;
}

Vertex * Edge::getMyToVertex()
{// --- RETURN A POINTER TO MYTOVERTEX ---
    return myToVertex;
}
