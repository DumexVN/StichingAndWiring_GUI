#include <QtGui>
#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QLCDnumber>
#include <QMessageBox>
#include <QMenuBar>
#include <QProgressDialog>
#include <QStatusBar>

#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "propertiesdialog.h"
#include "LineAnimator.h"
#include "revertColorCommand.h"
#include "graphview.h"

//--- MAIN CLASS WHICH DISPLAYS ALL ITEMS CREATED ---
//--- MAINTAINS ALL ITEMS, ANIMATIONS ---
Graph::Graph()
{   //---CONSTRUCTING A DISPLAY WINDOW---
    scene = new QGraphicsScene( -100, -100, 1000, 1000); //construct a graphic scene to handle graphics objects
    //construct a graphic views to display the Graphic Scene
    view = new GraphView;
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);
    //setting depth
    minZ = 0;
    maxZ = 0;
    vCase = 0;
    colorStack = new QUndoStack;
    //allows this to create actions, menus and toolbars
    createActions();
    createMenus();
    createToolBars();
    //setting signals and slots
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(updateActions()));
    setWindowTitle(tr("Euler Tour"));
    connect(&thread, SIGNAL(algorithmStarted(const QString &)),
             statusBar(), SLOT(showMessage(const QString &)));
    connect(&thread, SIGNAL(allAlgorithmsDone()),
                this, SLOT(allAlgorithmsDone()));

    updateActions();
}

void Graph::loadVertexFile()
{ // --- OPEN A FILE TO CONSTUCT THE GRAPH ---
    QString vertexFile = QFileDialog::getOpenFileName(this, "Select a text file to open",
                                                      "c:/desktop",
                                                      "Text File (*.txt)");
    readPosition(vertexFile);

}

void Graph::loadAdjFile()
{ // --- LOAD AN ADJACENCY MATRIX FILE ---
    QString adjFile = QFileDialog::getOpenFileName(this, "Select a text file to open",
                                                   "c:/desktop",
                                                   "Text File (*.txt)");
    readAdjMatrix(adjFile);
}

void Graph::saveVertexFile()
{ // --- SAVE CURRENT GRAPH TO TWO FILES: ONE FOR POSITION AND ONE FOR ADJACENCY MATRIX ---
    QMessageBox msg1;
    msg1.setIcon(QMessageBox::Information);
    msg1.setText(tr("Saving Vertices's Positions"));
    msg1.exec();
    QString vertexFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                      "VertexPos",
                                                      tr(".txt"));
    vertexFile.append(QString(".txt"));
    QMessageBox msg2;
    msg2.setIcon(QMessageBox::Information);
    msg2.setText(tr("Saving Adjacency Matrix"));
    msg2.exec();
    QString adjFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                   "AdjacencyMatrix",
                                                   tr(".txt"));
    adjFile.append(QString(".txt"));
    saveVerFile(vertexFile);
    saveAdjFile(adjFile);
}

void Graph::readPosition(const QString &vertexFile)
{ // --- READ FILE AND CONSTUCT VERTICES ---
    QFile file(vertexFile); // load the file
    reset();
    if (file.open(QIODevice::ReadOnly))
    {   // open the file
        QTextStream in(&file); // read in a text stream buffer
        QApplication::setOverrideCursor(Qt::WaitCursor); // set cursor to waiting
        int index = 0;
        while (!in.atEnd())
        {   // read the first line
            QString line = in.readLine();
            if (!line.contains(','))
            {   // check whether this is a position file which definitely contains a comma ','
                QMessageBox msg;
                msg.setIcon(QMessageBox::Critical);
                msg.setText(tr("Error when loading file: \n"
                               "This is not a Position file."));
                msg.exec();
                goto here;
            }
            addVertex();
            qreal x, y;
            QString str;
            for(int i = 0 ; i < line.size(); i++)
            {   // read each character in the line
                QChar cha = line.at(i);
                if (!cha.isDigit() && cha != ',' && cha != '.' && cha != '-')
                {   // if it is not a digit or a ',' or a '.' print error and exit
                    QMessageBox msg;
                    msg.setIcon(QMessageBox::Critical);
                    msg.setText(tr("Error when loading file!"));
                    msg.exec();
                    while (!myVertexList.empty())
                    {
                        myVertexList.removeFirst();
                    } // break out of the loop
                    goto here;
                }
                if (cha != ',')
                { // else if it is a digit, add it to the string
                    str.append(cha);
                }
                else if (cha == ',')
                {   // if it is a comma, return the X position, refresh the string
                    x = str.toDouble();
                    str.clear();
                }
                if ( i == line.size() - 1)
                {   // if this is the end return Y position
                    y = str.toDouble();
                }
            }
            Vertex *v = myVertexList.at(index);
            v->setPos(QPointF(x, y)); // set position of the newly added vertex
            index++;
        }
        loadAdjAction->setEnabled(true);
    }
    here:
    QApplication::restoreOverrideCursor();
}

void Graph::readAdjMatrix(const QString &fileName)
{ // --- READ AN ADJACENCY MATRIX AND CONSTRUCT THE GRAPH ---
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        int index = 0;
        while (!in.atEnd())
        {
           QString line = in.readLine();
           if (line.size() != myVertexList.size())
           {
               QMessageBox msg;
               msg.setIcon(QMessageBox::Critical);
               msg.setText("Error when reading file");
               msg.exec();
               break;
           }

           Vertex *v1 = myVertexList.at(index);
           for (int i = 0; i <line.size(); i++)
           {
               QChar adj = line.at(i);
               Vertex *v2 = myVertexList.at(i);
               if (adj == '0') {}
               else if (adj == '1')
               {
                   if (!v1->myAdjList.contains(v2) && !v2->myAdjList.contains(v1))
                   {
                       Edge *newEdge = new Edge(v1, v2);
                       scene->addItem(newEdge);
                   }
               }
               else if (adj == '2')
               {
                   if (!v1->myAdjList.contains(v2) && !v2->myAdjList.contains(v1))
                   {
                       Edge *newEdge = new Edge(v1, v2);
                       newEdge->setBackEdge(true);
                       scene->addItem(newEdge);
                   }
               }
               else if (adj != '0' && adj != '1' && adj != '2')
               {
                   QMessageBox msg;
                   msg.setIcon(QMessageBox::Critical);
                   msg.setText("Error when reading file");
                   msg.exec();
               }
           }
           index++;
        }
    QApplication::restoreOverrideCursor();
    }
}

void Graph::saveVerFile(const QString &fileName)
{ // --- SAVE A VERTEX FILE CONTAINS ALL VERTEX POSITION ---
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        for (int i = 0; i < myVertexList.size(); i++)
        {
            Vertex *v = myVertexList.at(i);
            out << v->x() << ',' << v->y() << endl;
        }
    }
    QApplication::restoreOverrideCursor();
}

void Graph::saveAdjFile(const QString &fileName)
{ // --- SAVE THE GRAPH'S ADJACENCY MATRIX ---
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        int totalVertex = myVertexList.size();
        QSet<QPair<Vertex*, Vertex*> > backEdges = findBackEdge();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        for (int i = 0; i < totalVertex; i++)
        {
            QString line; // write to a new line
            QQueue<int> myAdj; // a queue for adj indexies
            Vertex *v = myVertexList.at(i);
            for ( int i = 0; i < totalVertex; i++)
            {
                line.append('0'); //initialise the first line with all 0
            }
            QSetIterator<Vertex *> i(v->myAdjList);
            while (i.hasNext())
            {   //check for adjacency vertex and add their indexies to the queue
                Vertex *adj = i.next();
                int index = myVertexList.indexOf(adj);
                myAdj.enqueue(index);
            }

            while (!myAdj.empty())
            {
                int x = myAdj.dequeue();
                Vertex *adj = myVertexList.at(x);
                QPair<Vertex*, Vertex*> thisPair(v, adj);
                if (backEdges.contains(thisPair))
                {
                    line.replace(x, 1, '2');
                }
                else line.replace(x, 1, '1');
            }
            out << line << endl;
        }
    }
    QApplication::restoreOverrideCursor();
}

void Graph::closeEvent(QCloseEvent *event)
{   // --- CLOSING THE APPLICATION ---
    Algorithm *algo = 0; //sending a signal to terminate the thread
    addAlgorithm(algo);
    thread.wait(); // wait for the thread to exit
    event->accept();//quit the application
}

void Graph::addVertex()
{   // --- ADDING A VERTEX ---
    int seqNumber = myVertexList.size();//sequential number according to vertex's container
    Vertex *vertex = new Vertex; //creating new vertex
    vertex->setName(tr("V %1").arg(seqNumber +1)); //names are set according to their sequential number
    setupVertex(vertex);
    myVertexList.push_back(vertex);//add the vertex to the list of vertex
}

void Graph::setupVertex(Vertex *vertex)
{   // --- DRAWING A VERTEX ---
    //set a vertex's position on the screen, according to the window's coordinate.
    int seqNumber = myVertexList.size();
    vertex->setPos(QPointF(80 + (100 * (seqNumber % 9)), 80 + (50* ((seqNumber / 9) %9))));
    scene->addItem(vertex);//add the vertex the the scene
    ++seqNumber;

    scene->clearSelection();
    vertex->setSelected(true);
    bringToFront();//bring newly created vertex to the front
}

void Graph::bringToFront()
{   // --- BRING A SELECTED ITEM TO FRONT ---
    //select an item and brings them to front
    ++maxZ;
    setZValue(maxZ);
}

void Graph::sendToBack()
{   //send to back
    --minZ;
    setZValue(minZ);
}

void Graph::setZValue(int z)
{   //Z value is value for adjust depth of items on screen
    Vertex *vertex = selectVertex();
    if (vertex) vertex->setZValue(z);
}


Vertex *Graph::selectVertex() const
{   // --- CLICK AND SELECT A VERTEX ---
    //select a vertex, return the vertex if selected
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 1){
        return dynamic_cast<Vertex *>(items.first());
    }
    else {return 0;}
}

void Graph::addEdge()
{   // --- ADD AN EDGE ---
    //adding an edge when two vertices are selected
    VertexPair vertices = selectVertexPair();
    if (vertices == VertexPair()) return;
    if (vertices.first->myAdjList.contains(vertices.second)) return;
    Edge *edge = new Edge(vertices.first, vertices.second);
    scene->addItem(edge);
}

void Graph::addBackEdge()
{   // --- ADD AN EDGE ---
    //adding an edge when two vertices are selected
    VertexPair vertices = selectVertexPair();
    if (vertices == VertexPair()) return;
    if (vertices.first->myAdjList.contains(vertices.second)) return;
    Edge *edge = new Edge(vertices.first, vertices.second);
    edge->setBackEdge(true);
    edge->setBackPen(Qt::black);
    scene->addItem(edge);
}

Edge *Graph::selectEdge()const
{   // --- CLICK AND SELECT AN EDGE ---
    //select an edge item
    QList<QGraphicsItem *> items = scene->selectedItems();
        if (items.count() == 1) {
            return dynamic_cast<Edge *>(items.first());
        } else {
            return 0;
        }

}
Graph::VertexPair Graph::selectVertexPair() const
{   // --- SELECT A PAIR OF VERTICES ---
    //select a pair of vertex, support the adding edge function
    QList<QGraphicsItem *> items = scene->selectedItems();
    if (items.count() == 2) {
        Vertex *first = dynamic_cast<Vertex *>(items.first());
        Vertex *second = dynamic_cast<Vertex *>(items.last());
        if (first && second)
            return VertexPair(first, second);
    }
    return VertexPair();
}

void Graph::del()
{   // --- DELETE ---
    //delete function which deletes all selected items on screen
    QList<QGraphicsItem *> items = scene->selectedItems();
    QMutableListIterator<QGraphicsItem *> i(items);
    while (i.hasNext())
    {   //iterate through all edges
        Edge *edge = dynamic_cast<Edge *>(i.next());
        if (edge){
            delete edge;
            i.remove();
        }
    }
    i.toFront();
    while (i.hasNext())
    {   //iterate through all vertices
        Vertex *vertex = dynamic_cast<Vertex *>(i.next());
        if (vertex){
            myVertexList.removeOne(vertex);
        }

    }
    qDeleteAll(items); // make sure all items are deleted
}

void Graph::properties()
{   // --- DISPLAY PROPERTIES OF VERTICES(COLOUR, COORDINATES) ---
    //properties slots, show properties of vertex or edge.
    Vertex *vertex = selectVertex();
    Edge *edge = selectEdge();

    if (vertex){
        PropertiesDialog dialog(vertex, this);
        dialog.exec();
    } else if (edge) {
           QColor color = QColorDialog::getColor(edge->color(), this);
           if (color.isValid()) {
           edge->setColor(color);
        }
    }
}

void Graph::help()
{   // --- DISPLAY HELP DIALOG ---
    QMessageBox::about(this, tr("Help"),
                           tr("Help!!."));
}

void Graph::cut()
{   //--- CUT ---
    Vertex *vertex = selectVertex();
    if (!vertex){
        return;
    }
    copy();
    delete vertex;
}

void Graph::copy()
{   // --- COPY ---
    //copy, pin selected items on clipboard, for later use when paste
    Vertex *vertex = selectVertex();
    if (!vertex)
        return;

    QString str = QString("V %1 %2 %3")
        .arg(vertex->outlineColor().name())
        .arg(vertex->backgroundColor().name())
        .arg(vertex->name());
    QApplication::clipboard()->setText(str);
}

void Graph::paste()
{   // --- PASTE ---
    //paste items pinned on clipboard
    QString str = QApplication::clipboard()->text();
    QStringList parts = str.split(" ");
    if (parts.count() >= 4 && parts.first() == "V" ){
        addVertex();
        Vertex *vertex = myVertexList.last();
        vertex->setName(QStringList(parts.mid(3)).join(" "));
        vertex->setOutlineColor(QColor(parts[1]));
        vertex->setBackgroundColor(QColor(parts[2]));
    }
}

// --- END OF BASIC FUNCTIONALITIES ---
// ------------------------------------
// ------------------------------------
// --- GRAPH/ALGORITHMS FUNCTIONS: ----
void Graph::isQualified()
{   // --- CHECKING IF A GRAPH IS QUALIFIED ---
    //check if this graph is qualified to construct an Euler tour
    //check 3 cases
    QMessageBox msgBox;
    Algorithm *algo = new Algorithm(myVertexList, vCase);
    algo->initialise();
    for (int i = 0; i < myVertexList.size(); i++)
    {
        Vertex *v = myVertexList.at(i);
        v->setBackgroundColor(Qt::white);
    }
    vCase = algo->isQualified();
    if (vCase == 0)
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("The graph is not CONNECTED!. \n"
                       "Return and connect disconnected components.");
        msgBox.exec();
        connectAction->setEnabled(true);
    }
    else vCase = algo->isQualified();
    if (vCase == 1 )
    {
         showCase1();
    }
    if (vCase == 2)
    {
            // case 2: all vertices have even degree
         prepareEulerTourAction->setEnabled(true);
         msgBox.setIcon(QMessageBox::Information);
         msgBox.setText("Yes, all vertices have even degree. \n"
                         "At least one Euler CIRCUIT is available.");
         msgBox.exec();
    }
    if (vCase == 3){
         // case 3: fail, there are more than 2 node with odd degree. Required semi-eulerization
        showFailCase();
    }
}

void Graph::showCase1()
{   // --- SHOW QUALIFIED CASE 1 ---
    //Display dialog for Case 1: there are TWO odd degree vertices.
    QMessageBox msgBox;
    msgBox.setText(tr("Yes, there is at least one Euler PATH. \n"
                   "It will start from one vertex with ODD degree and end in another."));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setInformativeText("Do you want to colour them ODD vertices?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch(ret) {
    case QMessageBox::No:
    break;
    case QMessageBox::Yes:
    changeOddColour();
    }
    prepareEulerTourAction->setEnabled(true);
}

void Graph::showFailCase()
{   // --- SHOW FAIL CASE ---
    //Display dialog for a FAIL case where: too many vertices with odd degree.
    QMessageBox msgBox;
    msgBox.setText(tr("No. There are too many vertices with odd degree. \n"
                      "This required adding extra vertices."));
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setInformativeText("How do you want to proceed?");
    QPushButton *selfButton = msgBox.addButton(tr("I'll do it!"), QMessageBox::AcceptRole);
    QPushButton *autoButton = msgBox.addButton(tr("Suggest some!"), QMessageBox::AcceptRole);
    msgBox.setDefaultButton(autoButton);
    msgBox.exec();
    if (msgBox.clickedButton() == autoButton) {
        changeOddColour();
        suggestExtra();
        }
    else if (msgBox.clickedButton() == selfButton) {
        changeOddColour();
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setText(tr("Add extra edges to the colored vertices to: \n"
                       "1. Make them all even degree. \n"
                       "2. Left 2 with odd degree."));
        msg.exec();
    }
}

QList<Vertex *> Graph::getOddList()
{ // --- RETURN AN ARRAY OF ODD-DEGREE VERTICES ---
        QList<Vertex *> oddList;
        QListIterator<Vertex *> i(myVertexList);
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
void Graph::changeOddColour()
{
    QList<Vertex *> oddList = getOddList();
    for (int i = 0; i < oddList.size(); i++)
    {
        Vertex *v = oddList.at(i);
        revertColorCommand *changeColour = new revertColorCommand(v);
        colorStack->push(changeColour);
    }

}

void Graph::suggestExtra()
{   // --- SEMI-EULERISATION ---
    //suggesting extra vertices to be added
    Algorithm *algo = new Algorithm(myVertexList, 0);
    QList<Vertex*> oddList = algo->semiEulerization();
    // sort the odd list
    int secV = 1;
    for (int i = 0; i < oddList.size(); i+=2)
    {
        Vertex *thisV = oddList.at(i);
        Vertex *thatV = oddList.at(secV);
        if (thisV->myAdjList.contains(thatV) || thatV->myAdjList.contains(thisV))
        {   // if the two vertices are adjacent, add an extra vertex
            qreal x = (thisV->x() + thatV->x()) /2;
            qreal y = (thisV->y() + thatV->y())/ 2;
            addVertex(); // add a new vertex
            Vertex *newV = myVertexList.last();
            newV->setPos(x,y); // set its new position
            newV->setBackgroundColor(Qt::darkYellow); // set its colour
            Edge *newEdge = new Edge(thisV, newV); // connect these three vertices
            Edge *secnewEdge =new Edge(newV, thatV);
            newEdge->setBackEdge(true);
            newEdge->setBackPen(Qt::darkBlue);
            secnewEdge->setBackEdge(true);
            secnewEdge->setBackEdge(Qt::darkBlue);
            scene->addItem(newEdge);
            scene->addItem(secnewEdge);
        }
        else // if they are not adjacent, connect them directly by a back edge
        {
            Edge *newEdge = new Edge(thisV, thatV);
            newEdge->setBackEdge(true);
            newEdge->setBackPen(Qt::darkYellow);
            scene->addItem(newEdge);
        }
        secV += 2;
    }
    delete algo;
}

void Graph::addAlgorithm(Algorithm *algo)
{   // --- ADDING AN ALGORITHM TO A THREAD ---
    thread.addAlgorithm(algo);
    foreach (QAction *action, editMenu->actions())
    {
        action->setEnabled(false);
    }
    foreach (QAction *action, algorithmMenu->actions())
    {
        action->setEnabled(false);
    }
}

void Graph::connectGraph()
{   // --- CONNECTING DISONNECTED COMPONENTS ---
    Algorithm *algo = new Algorithm(myVertexList, 0);
    QQueue<Vertex *> extraEdges = algo->connectComponents();
    int x = 1;
    int newline = 0;
    qreal length = 0;
    for (int i = 0; i < extraEdges.size()-1; i+= 2)
    {
        Vertex *v1 = extraEdges.at(i);
        Vertex *v2 = extraEdges.at(x);
        Edge *newEdge = new Edge(v1, v2);
        newEdge->setBackEdge(true);
        newEdge->setBackPen(Qt::darkGreen);
        scene->addItem(newEdge);
        newline++;
        length = length + QLineF(v1->pos(), v2->pos()).length();
        x+=2;
    }
    this->informationWidget(newline, length);
    delete algo;
    connectAction->setEnabled(false);
}

void Graph::prepareEulerTour()
{   // --- CONSTRUCTING AN EULER TOUR ---
    Algorithm *algo = new Algorithm(myVertexList, vCase);
    addAlgorithm(algo);
    qualifyAction->setEnabled(false);
    connectAction->setEnabled(false);
    prepareEulerTourAction->setEnabled(false);
    EulerAction->setEnabled(true);
}

void Graph::allAlgorithmsDone()
{   // --- IF ALGORITHM IS FINISHED ---
    foreach (QAction *action, algorithmMenu->actions())
    {
        action->setEnabled(true);
    }
    foreach (QAction *action, editMenu->actions())
    {
        action->setEnabled(true);
    }
    statusBar()->showMessage(tr("Ready"), 10000);
}

void Graph::prepareEulerAnimation()
{   // --- PERFORM EULER ANIMATION ---
    for (int i = 0; i < myVertexList.size(); i++)
    {
        Vertex *v = myVertexList.at(i);
        v->disableMove();
    }
   // disable all menus and action while the animation is drawing
    disableAllActions();
    // calling a thread to calculate Euler Tour
    myEulerTour = thread.getEulerTour();
    thread.resetTour();

    int y = 1;
    int lineNumber = 0;
    qreal length = 0;
    QSet<QPair<Vertex*, Vertex*> > backEdges = findBackEdge();
    QSequentialAnimationGroup *topanim = new QSequentialAnimationGroup; //setup a group of animation
    for (int x = 0; x < myEulerTour.size() - 1; x++)
    {   //iterating through Euler Tour array
        //selecting a pair of vertex to construct a line animator
        Vertex *startVertex = myEulerTour.at(x);
        QPointF p1 = startVertex->pos();

        Vertex *endVertex = myEulerTour.at(y);
        QPointF p2 = endVertex->pos();
        QPair<Vertex*,Vertex*> thisPair(startVertex, endVertex);
        //creating a line animator
        LineAnimator *item = new LineAnimator(p1,p1);
        lineNumber++;
        QLineF measure(p1,p2);
        length = length + measure.length();
        //set Pen
        if (backEdges.contains(thisPair))
        {
            item->setPen(QPen(Qt::red, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        }
        else item->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        scene->addItem(item);
        //setting a line animation
        QPropertyAnimation *line = new QPropertyAnimation(item, "endPoint");
        line->setStartValue(QPointF(p1));
        line->setEndValue(QPointF(p2));
        line->setDuration(1000);
        //adding an animation to the group animation
        topanim->addAnimation(line);
        y++;
     }
    //set pause time between animation
    topanim->addPause(1000);
    topanim->start(); // start the group animation
    //adding a widget showing numbers of: line and total length.
    informationWidget(lineNumber, length);
    connect(topanim, SIGNAL(finished()), this, SLOT(completeDialog()));
    connect(topanim, SIGNAL(finished()), this, SLOT(updateActions()));
}

void Graph::informationWidget(int lineNumber, qreal length)
{ // --- ADDING A WIDGET SHOWING INFORMATION ---
    QWidget *window = new QWidget;
    window->setWindowTitle("Information");

    QLCDNumber *totalLineNumber = new QLCDNumber;
    QLCDNumber *totalLengthNumber = new QLCDNumber;

    QLabel *lineLabel = new QLabel;
    QLabel *lengthLabel = new QLabel;

    lineLabel->setText(tr("Total lines:"));
    lengthLabel->setText(tr("Total Length:"));
    lineLabel->setBuddy(totalLineNumber);
    lengthLabel->setBuddy(totalLengthNumber);

    totalLineNumber->display(lineNumber);
    totalLengthNumber->display(length);
    totalLineNumber->setPalette(Qt::black);
    totalLengthNumber->setPalette(Qt::black);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(lineLabel);
    layout->addWidget(totalLineNumber);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout->addWidget(lengthLabel);
    layout->addWidget(totalLengthNumber);

    window->setLayout(layout);
    window->move(500,100);
    window->show();
    connect(this, SIGNAL(animationFinished()), window, SLOT(close()));
}

void Graph::completeDialog()
{   //--- DISPLAY A DIALOG UPON COMPLETEING EULER TOUR ---
    QMessageBox msg;
    msg.setText(tr("That completes the Euler Tour."));
    msg.setInformativeText(tr("What do you want to do next?"));
    QPushButton *startanewButton = msg.addButton(tr("Start A New Graph."), QMessageBox::AcceptRole);
    QPushButton *redrawButton = msg.addButton(tr("Show it again."), QMessageBox::AcceptRole);
    msg.exec();
    if (msg.clickedButton() == startanewButton)
    {
       emit animationFinished();
       reset();
    }
    else if (msg.clickedButton() == redrawButton)
    {
        emit animationFinished();
        removeLineAnimator();
        while(!myEulerTour.empty())
        {
            myEulerTour.removeFirst();
        }
        prepareEulerTour();
        prepareEulerAnimation();
    }
}

void Graph::removeLineAnimator()
{   //--- REMOVE ALL LINE ANIMATED ON SCENE ---
    QList<QGraphicsItem *> items = scene->items();
    QMutableListIterator<QGraphicsItem *> i(items);
    while (i.hasNext())
    {
        LineAnimator *line = dynamic_cast<LineAnimator *>(i.next());
        if (line)
        {
            delete line;
            i.remove();
        }
    }
}


QSet<QPair<Vertex*,Vertex*> > Graph::findBackEdge()
{ // --- FIND BACK EDGES ---
    QList<QGraphicsItem*> items = scene->items();
    QMutableListIterator<QGraphicsItem*> i(items);
    QSet<QPair<Vertex*,Vertex*> > backEdges;
    while (i.hasNext())
    {
        Edge *edge = dynamic_cast<Edge*>(i.next());
        if (edge)
        {
            if (edge->isBackEdge())
            {
                backEdges.insert(qMakePair(edge->getMyFromVertex(), edge->getMyToVertex()));
                backEdges.insert(qMakePair(edge->getMyToVertex(), edge->getMyFromVertex()));
            }
        }
    }
    return backEdges;
}

void Graph::reset()
{   //--- DELETE ALL ITEMS ON SCREEN ---
    QList<QGraphicsItem *> items = scene->items();
    QMutableListIterator<QGraphicsItem *> i(items);
    while(i.hasNext())
    {
        Edge *edge = dynamic_cast<Edge *>(i.next());
        if (edge){
            delete edge;
            i.remove();
            }
        }
        i.toFront();
    while (i.hasNext())
    {
            Vertex *vertex = dynamic_cast<Vertex *>(i.next());
            if (vertex){
                myVertexList.removeOne(vertex);
            }

        }
    qDeleteAll(items);
    scene->clear();
    vCase = 0;
    updateActions();
}

// --- END OF GRAPH ALGORITHMS ---
// -------------------------------
// -------------------------------
// -- ADDING MENUS AND TOOLBARS --

void Graph::createActions()
{   //--- CREATE ACTIONS THAT CAN BE PERFORMED IN APPLICATION ---
    loadVertexAction = new QAction(tr("Load V&ertex"), this);
    connect(loadVertexAction, SIGNAL(triggered()), this, SLOT(loadVertexFile()));

    loadAdjAction = new QAction(tr("Load &Adjacency"), this);
    connect(loadAdjAction, SIGNAL(triggered()), this, SLOT(loadAdjFile()));

    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveVertexFile()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    resetAction = new QAction(tr("S&tart Again"), this);
    connect(resetAction, SIGNAL(triggered()), this, SLOT(reset()));

    addVertexAction = new QAction(tr("Add a Vertex"), this);
    addVertexAction->setIcon(QIcon(":/image/node.png"));
    addVertexAction->setShortcut(tr("Ctrl+N"));
    connect(addVertexAction, SIGNAL(triggered()), this, SLOT(addVertex()));

    addEdgeAction = new QAction(tr("Draw an Edge"), this);
    addEdgeAction->setIcon(QIcon(":/image/link.png"));
    addEdgeAction->setShortcut(tr("Ctrl+L"));
    connect(addEdgeAction, SIGNAL(triggered()), this, SLOT(addEdge()));

    addBackEdgeAction = new QAction(tr("Draw a back edge"), this);
    addBackEdgeAction->setIcon(QIcon(":/image/dotline.png"));
    connect(addBackEdgeAction, SIGNAL(triggered()), this, SLOT(addBackEdge()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    deleteAction->setShortcut(tr("Del"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/image/cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/image/copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/image/paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    bringToFrontAction = new QAction(tr("Bring to &Front"), this);
    bringToFrontAction->setIcon(QIcon(":/image/bringtofront.png"));
    connect(bringToFrontAction, SIGNAL(triggered()),
               this, SLOT(bringToFront()));

    sendToBackAction = new QAction(tr("&Send to Back"), this);
    sendToBackAction->setIcon(QIcon(":/image/sendtoback.png"));
    connect(sendToBackAction, SIGNAL(triggered()),
               this, SLOT(sendToBack()));

    propertiesAction = new QAction(tr("P&roperties..."), this);
    connect(propertiesAction, SIGNAL(triggered()),
               this, SLOT(properties()));

    helpAction = new QAction(tr("&Help"), this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

    aboutQtAction = new QAction(tr("&About"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    EulerAction = new QAction(tr("&Euler"), this);
    EulerAction->setIcon(QIcon(":image/Euler.png"));
    connect(EulerAction, SIGNAL(triggered()), this, SLOT(prepareEulerAnimation()));

    qualifyAction = new QAction(tr("&Is Qualify"), this);
    qualifyAction->setIcon(QIcon(":/image/check.png"));
    connect(qualifyAction, SIGNAL(triggered()), this, SLOT(isQualified()));

    connectAction = new QAction(tr("&Connect Graph"), this);
    connectAction->setIcon(QIcon(":image/connect.jpg"));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(connectGraph()));

    prepareEulerTourAction = new QAction(tr("&Construct Tour"), this);
    prepareEulerTourAction->setIcon(QIcon(":image/prepare.jpg"));
    connect(prepareEulerTourAction, SIGNAL(triggered()), this, SLOT(prepareEulerTour()));
}

void Graph::createMenus()
   {   // --- ADDING ACTIONS ---
       //adding Action to the menu bar
       fileMenu = menuBar()->addMenu(tr("&File"));
       fileMenu->addAction(loadVertexAction);
       fileMenu->addAction(loadAdjAction);
       fileMenu->addAction(saveAction);

       editMenu = menuBar()->addMenu(tr("&Edit"));
       editMenu->addAction(resetAction);
       editMenu->addAction(addVertexAction);
       editMenu->addAction(addEdgeAction);
       editMenu->addAction(addBackEdgeAction);
       editMenu->addAction(deleteAction);
       editMenu->addSeparator();
       editMenu->addAction(cutAction);
       editMenu->addAction(copyAction);
       editMenu->addAction(pasteAction);
       editMenu->addSeparator();
       editMenu->addAction(bringToFrontAction);
       editMenu->addAction(sendToBackAction);
       editMenu->addSeparator();
       editMenu->addAction(propertiesAction);

       algorithmMenu = menuBar()->addMenu(tr("Algorithm"));
       algorithmMenu->addAction(qualifyAction);
       algorithmMenu->addAction(connectAction);
       algorithmMenu->addAction(prepareEulerTourAction);
       algorithmMenu->addAction(EulerAction);

       programMenu = menuBar()->addMenu(tr("&Program"));
       programMenu->addAction(helpAction);
       programMenu->addAction(aboutQtAction);
       programMenu->addAction(exitAction);
   }

void Graph::createToolBars()
{   // --- ADDING ACTIONS ON TOOLBARS ---
    //adding Action on the Toolbars
       editToolBar = addToolBar(tr("Show Edit Toolbar"));
       editToolBar->addAction(addVertexAction);
       editToolBar->addAction(addEdgeAction);
       editToolBar->addAction(addBackEdgeAction);
       editToolBar->addAction(deleteAction);
       editToolBar->addSeparator();
       editToolBar->addAction(qualifyAction);
       editToolBar->addAction(connectAction);
       editToolBar->addAction(prepareEulerTourAction);
       editToolBar->addSeparator();
       editToolBar->addAction(EulerAction);
}

void Graph::updateActions()
{   // --- SET ACTIONS' VISIBILITY ---
    //set visibility of each Action
    foreach (QAction *action, editMenu->actions())
    {
        action->setEnabled(true);
    }

    bool hasSelection = !scene->selectedItems().isEmpty();
    bool isVertex = (selectVertex() != 0);
    bool isProperties = (selectVertex() != 0 || selectEdge() != 0);
    bool isVertexPair = (selectVertexPair() != VertexPair());
    bool hasVertex = (!myVertexList.empty());

    addEdgeAction->setEnabled(isVertexPair);
    addBackEdgeAction->setEnabled(isVertexPair);
    deleteAction->setEnabled(hasSelection);
    cutAction->setEnabled(isVertex);
    copyAction->setEnabled(isVertex);
    bringToFrontAction->setEnabled(isVertex);
    sendToBackAction->setEnabled(isVertex);
    propertiesAction->setEnabled(isProperties);
    loadAdjAction->setEnabled(false);

    foreach (QAction *action, algorithmMenu->actions())
    {
        action->setEnabled(false);
    }
    qualifyAction->setEnabled(hasVertex);

    foreach (QAction *action, view->actions())
        view ->removeAction(action);
    foreach (QAction *action, editMenu->actions()){
        if (action->isEnabled()){
            view->addAction(action);
        }
    }
}

void Graph::disableAllActions()
{ // --- DISABLE ALL ACTIONS ---
    foreach (QAction *action, editMenu->actions())
    {
        action->setEnabled(false);
    }
    foreach (QAction *action, algorithmMenu->actions())
    {
        action->setEnabled(false);
    }
}
