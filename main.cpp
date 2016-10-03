#include <QApplication>
#include <QSplashScreen>

#include "graph.h"

// --- STARTING THE MAINTHREAD LOOP---
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graph view;
    view.show();
    return a.exec();
}
