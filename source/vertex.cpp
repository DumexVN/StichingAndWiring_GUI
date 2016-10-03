#include <QtGui>
#include <QInputDialog>
#include <QStyle>
#include <QStyleOptiongraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFontMetricsF>
#include <QApplication>


#include "vertex.h"
#include "edge.h"

// --- VERTEX CLASSS ---
//Main class for Vertex
Vertex::Vertex()
{   // --- VERTEX CONSTRUCTOR
    //Constructing a vertex: with color and flags
    myOutlineColor = Qt::darkRed; //outline colour
    myBackgroundColor = Qt::white;//background colour
    //set item to be moveable, selectable and sending geometry information
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
}

Vertex::~Vertex()
{   // --- DELETE A VERTEX ---
    // Delete all associated edge (this will remove all adjacency accordingly)
    foreach (Edge *edge, myEdge)
        delete edge;
}

void Vertex::setName(const QString &name)
{   // --- SETTER FOR NAME ---
    prepareGeometryChange();
    myName = name;
    update();
}

QString Vertex::name() const
{   // --- GETTER FOR NAME ---
    return myName;
}

void Vertex::setOutlineColor(const QColor &color)
{   // --- SETTER FOR OUTLINE COLOUR ---
    myOutlineColor = color;
    update();
}

QColor Vertex::outlineColor() const
{   // --- GETTER FOR OUTLINE COLOUR ---
    return myOutlineColor;
}

void Vertex::setBackgroundColor(const QColor &color)
{   // --- SETTER FOR BACKGROUND COLOUR ---
    myBackgroundColor = color;
    update();
}

QColor Vertex::backgroundColor() const
{   // --- GETTER FOR BACKGROUND COLOUR ---
    return myBackgroundColor;
}

void Vertex::connectEdge(Edge *edge)
{   // --- ADD AN EDGE TO A VERTEX ---
    myEdge.insert(edge);
}

void Vertex::removeEdge(Edge *edge)
{   // --- REMOVE AN EDGE ---
    myEdge.remove(edge);
}

bool Vertex::containEdge(Edge *edge)
{   // --- CHECK IF THIS VERTEX CONTAINS THIS EDGE ---
    return myEdge.contains(edge);
}

void Vertex::addAdjVertex(Vertex *vertex)
{   // --- ADD AN ADJACENCY VERTEX ---
    myAdjList.insert(vertex);
}

void Vertex::removeAdjVertex(Vertex *vertex)
{   // --- REMOVE AN ADJACENCY VERTEX ---
    myAdjList.remove(vertex);
}

int Vertex::myDegree()
{   // --- RETURN THIS VERTEX's DEGREE ---
    return myAdjList.size();
}

QRectF Vertex::outlineRect() const
{   //--- OUTLINE A BOUNDING RECTANGLE ---
    const int padding = 4;
    QFontMetricsF metrics = QApplication::fontMetrics();
    QRectF rect = metrics.boundingRect(myName);
    rect.adjust(-padding,-padding,+padding,+padding);
    rect.translate(-rect.center());
    return rect;
}

QRectF Vertex::boundingRect() const
{   //--- SETS THE BOUNDING RECTANGLE ---
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath Vertex::shape() const
{   //--- DETERMINES A VERTEX'S SHAPE ---
    QRectF rect = outlineRect();
    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()), roundness(rect.height()));
    return path;
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   //--- DRAW A VERTEX ---
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected){
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(myBackgroundColor);

    QRectF rect = outlineRect();
    painter->drawRoundedRect(rect, roundness(rect.width()), roundness(rect.height()));

    painter->setPen(Qt::black);
    painter->drawText(rect, Qt::AlignCenter, myName);
}

QSet<Vertex *> Vertex::getAdjList()
{   // --- RETURN A VERTEX'S ADJACENCY LIST ---
    return myAdjList;
}


QVariant Vertex::itemChange(GraphicsItemChange change, const QVariant &value)
{   // --- REDRAW EDGE WHEN VERTEX'S POSITION CHANGED ---
    if (change == ItemPositionHasChanged) {
        foreach (Edge *edge, myEdge)
            edge->trackVertex();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Vertex::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{   // --- ALLOW CHANGING NAME WHEN DOUBLE CLICK A VERTEX ---
    QString name = QInputDialog::getText(event->widget(), tr("Edit Text"), tr("Enter new text:"), QLineEdit::Normal, myName);

    if (!name.isEmpty())
        setName(name);
}

int Vertex::roundness(double size) const
{   // --- SET THE VERTEX TO BE ROUNDED SHAPE ---
    const int Diameter = 8;
    return 100 * Diameter / int(size);
}

void Vertex::disableMove()
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
}
