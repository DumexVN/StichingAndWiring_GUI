#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QApplication>
#include <QColor>
#include <QSet>

class Edge;

class Vertex : public QGraphicsItem
{
    Q_DECLARE_TR_FUNCTIONS(Vertex)

public:
    Vertex();
    ~Vertex();

    void setName(const QString &name);
    QString name() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addAdjVertex(Vertex *vertex);
    void removeAdjVertex(Vertex *vertex);
    int myDegree();
    void connectEdge(Edge *edge);
    void removeEdge(Edge *edge);
    bool containEdge(Edge *edge);
    void disableMove();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QSet<Vertex *> getAdjList();
    QSet<Vertex *> myAdjList;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    QSet<Edge *> myEdge;
    QString myName;
    QColor myOutlineColor;
    QColor myBackgroundColor;
};

#endif // VERTEX_H
