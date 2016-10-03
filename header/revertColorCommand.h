#ifndef REVERTCOLORCOMMAND_H
#define REVERTCOLORCOMMAND_H

#include <QUndoCommand>

class Vertex;

class revertColorCommand : public QUndoCommand
{   // --- QUNDOCOMMAND FOR CHANGING A VERTEX'S BACKGROUND COLOUR ---
public:
    revertColorCommand(Vertex *vertex, QUndoCommand *parent = 0)
    {
        myVertex = vertex;
        myOldColor = Qt::white;
        myNewColor = Qt::red;
    }
    void undo()
    {
        myVertex->setBackgroundColor(myOldColor);
    }
    void redo()
    {
        myVertex->setBackgroundColor(myNewColor);
    }

private:
    Vertex *myVertex;
    QColor myOldColor;
    QColor myNewColor;
};
#endif // REVERTCOLORCOMMAND_H
