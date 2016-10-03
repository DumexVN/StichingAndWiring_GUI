#ifndef REMOVEADJCOMMAND_H
#define REMOVEADJCOMMAND_H

#include "vertex.h"

#include <QUndoCommand>

class removeAdjCommand : public QUndoCommand
{   // --- REMOVE TWO VERTICES FROM EACH OTHER ADJACENCY LIST ---
    // --- This is a QUndoCommand to use with QUndoStack ---
public:
    removeAdjCommand(Vertex *vertex, Vertex *adjVertex, QUndoCommand *parent = 0)
    {
        thisV = vertex;
        thatV = adjVertex;
    }
    void undo()
    {
        thisV->myAdjList.insert(thatV);
        thatV->myAdjList.insert(thisV);
    }
    void redo()
    {
        thisV->myAdjList.remove(thatV);
        thatV->myAdjList.remove(thisV);
    }

private:
    Vertex *thisV;
    Vertex *thatV;
};
#endif // REMOVEADJCOMMAND_H
