#ifndef LINEANIMATOR_H
#define LINEANIMATOR_H

#include <QGraphicsLineItem>

class LineAnimator : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint)
public:
    LineAnimator(const QPointF &startPoint, const QPointF &endPoint) : QObject()
    {
        p1 = startPoint;
        p2 = endPoint;
        this->setLine(QLineF(p1,p2));
    }
    QPointF endPoint() const
    {
        return p2;
    }

public slots:
    void setEndPoint(const QPointF point)
    {
        p2 = point;
        this->setLine(QLineF(p1,p2));
    }
public:
    QPointF p1;
    QPointF p2;

};
#endif // LINEANIMATOR_H
