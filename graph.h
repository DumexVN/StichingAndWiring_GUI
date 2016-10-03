#ifndef GRAPH_H
#define GRAPH_H

#include <QAction>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QPair>
#include <QSequentialAnimationGroup>
#include <QToolBar>
#include <QUndoStack>
#include <QUndoView>
#include <QUndoCommand>

#include "vertex.h"
#include "edge.h"
#include "algorithm.h"
#include "algorithmthread.h"

class Graph : public QMainWindow
{
    Q_OBJECT

public:
    Graph();
signals:
    void animationFinished();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void loadVertexFile();
    void loadAdjFile();
    void saveVertexFile();
    void addVertex();
    void addBackEdge();
    void addEdge();
    void del();
    void cut();
    void copy();
    void paste();
    void bringToFront();
    void sendToBack();
    void properties();
    void help();
    void updateActions();
    void isQualified();
    void prepareEulerAnimation();
    void reset();
    void completeDialog();
    void connectGraph();
    void prepareEulerTour();
    void allAlgorithmsDone();

private:
    typedef QPair<Vertex *, Vertex *> VertexPair;

    void readAdjMatrix(const QString &fileName);
    void readPosition(const QString &fileName);
    void saveVerFile(const QString &fileName);
    void saveAdjFile(const QString &fileName);
    void createActions();
    void disableAllActions();
    void createMenus();
    void createToolBars();
    void setZValue(int z);
    void showCase1();
    void showFailCase();
    void createUndoView();
    void removeLineAnimator();
    void suggestExtra();
    void setupVertex(Vertex *vertex);
    void informationWidget(int, qreal);
    void addAlgorithm(Algorithm *algo);
    Vertex *selectVertex() const;
    VertexPair selectVertexPair() const;
    Edge *selectEdge() const;
    QList<Vertex *> getOddList();
    QSet<QPair<Vertex*,Vertex*> > findBackEdge();
    void changeOddColour();

    QGraphicsScene *scene;
    QGraphicsView *view;
    QMenu *programMenu;
    QMenu *editMenu;
    QMenu *algorithmMenu;
    QMenu *fileMenu;
    QToolBar *editToolBar;
    QAction *loadVertexAction;
    QAction *loadAdjAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *addVertexAction;
    QAction *addEdgeAction;
    QAction *addBackEdgeAction;
    QAction *deleteAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *bringToFrontAction;
    QAction *sendToBackAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *helpAction;
    QAction *propertiesAction;
    QAction *EulerAction;
    QAction *qualifyAction;
    QAction *aboutQtAction;
    QAction *resetAction;
    QAction *connectAction;
    QAction *prepareEulerTourAction;

    int minZ;
    int maxZ;
    int vCase;
    QString curVerFile;
    QString curAdjFile;
    QList<Vertex *> myVertexList;
    QList<Vertex *> myEulerTour;
    AlgorithmThread thread;

    QUndoStack *colorStack;
};

#endif //GRAPH_H
