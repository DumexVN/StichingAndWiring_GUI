#include "algorithm.h"
#include "removeAdjCommand.h"
#include "algorithmthread.h"

#include <QDebug>
#include <QtAlgorithms>
#include <QtCore/qmath.h>

//Main source of Algorithm class where all calculation takes palce
Algorithm::Algorithm(QList<Vertex *> myVertexList, int vCase)
{
    vertexStack = new QUndoStack();
    vertexList = myVertexList;
    vertexCase = vCase;
    timer = -1;
}

int Algorithm::isQualified()
{   // --- CHECKING IF A GRAPH IS QUALIFIED ---
    //check if this graph is qualified to construct an Euler tour
    //check 3 cases
    if (myConnectedComponents.size() > 1)
    {
        return 0;
    }
    int oddNode = 0;
    int evenNode = 0;
    QListIterator<Vertex *> i(vertexList);
    while (i.hasNext())
    {   //iterate through vertices
            Vertex *vertex = i.next();
            int x = vertex->myDegree();
            if (x!=0 && x%2 == 0)
            {
                evenNode++;
            }
            if (x % 2 == 1)
            {
               oddNode++;
            }
        }
        if (oddNode <=2 && oddNode > 0){
            // case 1: at most 2 vertices with odd degree
            return 1;
        }
        if (oddNode == 0 && evenNode != 0 ){
            // case 2: all vertices have even degree
            return 2;
        }
        if (oddNode > 2){
            // case 3: fail, there are more than 2 node with odd degree. Required semi-eulerization.
            return 3;
        }
}

QList<Vertex *> Algorithm::getoddList()
{   // --- RETURN AN LIST OF ODD DEGREE VERTICES ---
    //return an array of odd-degree vertices
    QList<Vertex *> oddList;
    QListIterator<Vertex *> i(vertexList);
    while (i.hasNext())
    {
        Vertex *vertex = i.next();
        int x = vertex->myDegree();
        if (x % 2 == 1)
        {
            oddList.append(vertex);
        }
    }
    return oddList;
}

void Algorithm::EulerPath()
{   // --- DETERMINE A START VERTEX FOR FLEURY'S ---
    // if there are at most 2 vertices with odd degree.
    if (vertexCase == 1)
    {
        QList<Vertex *> oddList = getoddList();
        if (oddList.size() == 1) // if there is only one vertex with odd degree, start from there
        {
            Fleury(oddList.at(0));
        }
        else
        { // if there are two vertices with odd degree, choose one at random.
            int ran = qrand() % 100;
            if (ran < 55) Fleury(oddList.at(0));
            else if (ran > 55) Fleury(oddList.at(1));
        }
    }
    // if there are all even degree vertices, start at random vertex.
    else if (vertexCase == 2)
    {
        int i = qrand() % vertexList.size();
        Vertex *startVertex = vertexList.at(i);
        Fleury(startVertex);
    }
}

void Algorithm::Fleury(Vertex *startVertex)
{   // --- FLEURY'S ALGORITHM ---
    // Modified Fleury algorithm with Bridges checking algorithm
    QSetIterator<Vertex *> i(startVertex->myAdjList);
    if (!startVertex->myAdjList.empty())
    {   //from the starting vertex, visit a neighbour
        Vertex *adjVertex = 0;
        if (startVertex->myAdjList.size() == 1)
        {
            adjVertex = i.next();// if there is only one, take it
        }
        else while (i.hasNext())
        {   // if there are more than one, chose random one that is not a bridge
            int ran = (rand() % (startVertex->myAdjList.size()))+1;
            while (ran != 0)
            { //choosing a random neighbour
               adjVertex = i.next();
                ran -= 1;
            }
            if (validEdges(startVertex, adjVertex))
            {//check if they are a bridge
                break;
            }
            else i.toFront(); //repeat the loop
        } // if they are not a bridge, add them to the tour
        myEulerTour.push_back(startVertex);
        // remove their adjacency node
        // as this modifies the graph, add this command to an undo command stack for later redo.
        QUndoCommand *removeCommand = new removeAdjCommand(startVertex, adjVertex);
        vertexStack->push(removeCommand);
        // if they dont have any adjacency vertex, remove from the nodelist
        int x = startVertex->myDegree();
        if (x == 0)
        {
            vertexList.removeOne(startVertex);
        }
        // if there's only one last vertex, add it to the tour to complete the tour.
        if (vertexList.size() == 1)
        {
            myEulerTour.push_back(vertexList.at(0));
        }
        Fleury(adjVertex); //perform fleury on the adjacency vertex
    }
}

bool Algorithm::validEdges(Vertex *startVertex, Vertex *adjVertex)
{  // --- CHECKING BRIDGE ---
   //Bridge finding algorithm to check if 2 vertex would form a bridge.
    while (!myLowArray.empty())
    { //reset low array
        int i = 0;
        myLowArray.removeAt(i);
        i++;
    }
    while (!myPreArray.empty())
    {//reset preorder array
        int i = 0;
        myPreArray.removeAt(i);
        i++;
    }
    while (!myBridge.empty())
    {//reset array containing bridges
        int i = 0;
        myBridge.removeAt(i);
        i++;
    }
    findBridge();
    if (myBridge.contains(startVertex) && myBridge.contains(adjVertex))
    {
        return false;
    }
    else return true;

}

void Algorithm::findBridge()
{   // --- CALLING BRIDGE FINDING ALGORITHM ---
    //algorithm for finding bridge in a graph
    int size = vertexList.size();
    //initialise low array with -1
    for (int x = 0; x < size; x++)
    {
        myLowArray.insert(x, -1);
    }
    //intialise pre array with -1
    for (int y = 0; y < size; y++)
    {
        myPreArray.insert(y, -1);
    }
    //call a modified DFS
    for (int v = 0; v < size; v++)
    {
        if (myPreArray.at(v) == -1 )
        {
            Vertex *thisVertex = vertexList.at(v);
            DFS(thisVertex, thisVertex, v);
        }
    }
}

void Algorithm::DFS(Vertex *parentVertex, Vertex *thisVertex, int v)
{ // --- MODIFIED DFS FOR BRIDGE FINDING ---
    // Modified version of DFS, including 2 array of low and preorder.
    static int time = 0;
    myPreArray.replace(v, time++);
    myLowArray.replace(v, myPreArray.value(v));

    QSetIterator<Vertex *> i(thisVertex->myAdjList);
    while (i.hasNext())
    {   //pointer to the adjacency vertex
        Vertex *adjVertex = i.next();
        int t = vertexList.indexOf(adjVertex); //get its indexes
        if (myPreArray.at(t) == -1) // if unvisited, perform DFS
            {
             DFS(thisVertex, adjVertex, t);
             if (myLowArray.at(v) > myLowArray.at(t))
             {
                 myLowArray.replace(v, myLowArray.at(t));
             }
             if (myLowArray.at(t) == myPreArray.at(t))
             {   //if a vertex has the same value of pre and low, means it and its parent forms a bridge
                 myBridge.push_back(thisVertex);
                 myBridge.push_back(adjVertex);
             }
        }
        else if (parentVertex != adjVertex) //if not their parent
        {//set it their lowest vertex to reach
            if(myLowArray.at(v) > myPreArray.at(t))
               myLowArray.replace(v, myPreArray.at(t));
        }
    }
}

QList<Vertex *> Algorithm::getEulerTour()
{   // --- CONSTRUCTING AN EULER TOUR ---
    //perform and return EulerTour
    EulerPath();
    return myEulerTour;
}

void Algorithm::resetAdj()
{   //as the algorithm modifies the graph, this undostack redo all the command
    //Thus, return the graph to its begin state.
    while (vertexStack->canUndo())
    {
        vertexStack->undo();
    }
}
// --- END OF FLEURY ALGORITHM ---

void Algorithm::initialise()
{   //--- MODIFIED DFS TO IDENTIFY CONNECTED COMPONENTS ---
    int timer = 0;
    for (int i = 0; i < vertexList.size(); i++)
    {   //insert all items as -1 means unvisited
        visited.insert(i, -1);
    }
    for (int i = 0; i < vertexList.size(); i++)
    {   //if vertex is unvisited
        if (visited.at(i) == -1)
        {   //perform depth first search
            Vertex *v = vertexList.at(i);
            QList<Vertex *> connected;
            myConnectedComponents.append(connected);
            depthfirstsearch(v, i, timer);
            timer++;
        }
    }
}

void Algorithm::depthfirstsearch(Vertex *vertex, int index, int timer)
{   // --- DFS ---
     visited.replace(index, timer); //mark item with their connected component using timer
     QSetIterator<Vertex *> i(vertex->myAdjList);
     while (i.hasNext())
     {
         Vertex *adjVertex = i.next();
         int t = vertexList.indexOf(adjVertex);
         if (visited.at(t) == -1)
         {  //recursive call
             depthfirstsearch(adjVertex, t, timer);
         }
     }
}

QList<Vertex*> Algorithm::sortPoint(QList<Vertex*> thisList)
{   //sorting Vertex according to their position (using manhattenlength)
    //this is selection sort.
    qreal minLength = 0;
    int minIndex = 0;
    for (int i = 0; i < thisList.size()-1; i++)
    {        
        Vertex *thisV = thisList.at(i);
        qreal length1 = (thisV->pos().manhattanLength());
        minLength = length1;
        minIndex = i;
        for (int y = i+1; y < thisList.size(); y++)
        {
            Vertex *thatV = thisList.at(y);
            qreal length2 = (thatV->pos().manhattanLength());

            if (length2 < minLength)
            {
                minIndex = y;
                minLength = length2;
            }
        }
        if (minIndex != i)
        {
            thisList.swap(minIndex, i);
        }
    }
    return thisList;
}
QList<Vertex*> Algorithm::semiEulerization()
{   //suggeting extra vertices to the graph to make it valid for Euler tour
    QList<Vertex *> oddList = this->getoddList();
    oddList = sortPoint(oddList);
    return oddList;
}

void Algorithm::retrieveConnectedComponents()
{   //--- PUT EACH CONNECTED COMPONENTS SET INTO DIFFERENT ARRAY ---
    //--- PUT EVERY SETS INTO A LIST ---
    for (int i = 0; i < myConnectedComponents.size(); i++)
    {
        QList<Vertex *> list = myConnectedComponents.at(i);
        for ( int x = 0; x < visited.size(); x++)
        {
            if (visited.at(x) == i)
            {
                Vertex *v = vertexList.at(x);
                list.append(v);
            }
        }
        myConnectedComponents.replace(i, list);
    }
}

void Algorithm::conversion()
{   // --- CONVERT AN ARRAY OF VERTEX POINTER TO A SORTED ARRAY OF MANHATTAN LENGTH ---
    if (myConnectedComponents.empty()) {return ;}
    else for (int i = 0 ; i < myConnectedComponents.size(); i++)
    {
        QList<Vertex *> connected = myConnectedComponents.at(i);
        connected = sortPoint(connected);
        myConnectedComponents.replace(i, connected);
    }
}

QQueue<Vertex*> Algorithm::callingcomparedistance()
{ // --- FINDING MINIMUM DISTANCE BETWEEN CONNECTED COMPONENTS ---
   int x = 1;
   QQueue<Vertex *> result;
   for (int i =0; i < myConnectedComponents.size(); i++)
   {
       if (x == myConnectedComponents.size()) // if this is the last pair
       {
           x = 0;
       }
       QList<Vertex*> list1 = myConnectedComponents.at(i); // first connected components
       QList<Vertex*> list2 = myConnectedComponents.at(x); // second connected components
       QList<QPair<int, int> > minDistance = compareMinDistance(list1,list2); // find minimum difference/distance
       if (minDistance.size() >1 )
          {}
       QPair<int, int> pair = minDistance.at(0);//extract result
       Vertex *v1 = myConnectedComponents.at(i).at(pair.first);
       Vertex *v2 = myConnectedComponents.at(x).at(pair.second);
       result.enqueue(v1);
       result.enqueue(v2);
       x++;
   }
   return result;
}

QList<QPair<int, int> > Algorithm::compareMinDistance(QList<Vertex*> list1, QList<Vertex*> list2)
{ // --- FINDING MINIMUM DIFFERENCE BETWEEN TWO SORTED LISTS ---
    QList<QPair<int, int> > result;
    qreal minDistance = 99999;
    int i = 0, j = 0;
    int index1, index2;
    while (i < list1.size() && j < list2.size())
    {
        qreal localDistance = (list1.at(i)->pos() - list2.at(j)->pos()).manhattanLength();
        if (localDistance < minDistance)
        {
            minDistance = localDistance;
            index1 = i;
            index2 = j;
        }
        if (list1.at(i)->pos().manhattanLength() < list2.at(j)->pos().manhattanLength())//
        {
            i++;
        }
        else j++;
    }
    result.append(qMakePair(index1,index2));
    return result;
}

// --- END OF FINDING MIN DISTANCE BETWEEN DISCONNECTED COMPONENTS ---

QString Algorithm::message()
{ //---SEND A MESSAGE WHILE A THREAD IS DOING COMPUTATION---
    return QObject::tr("Constructing an Euler Tour ...");
}

QQueue<Vertex *> Algorithm::connectComponents()
{ // --- PERFORM CONNECTING MIN DISTANCE COMPONENTS ---
    this->initialise();
    this->retrieveConnectedComponents();
    this->conversion();
    return callingcomparedistance();
}
