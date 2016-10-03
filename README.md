# StichingAndWiring_GUI
A GUI program for Stitching and Wiring Problem i.e. Euler Tour || 'drawing without lifting pen' written during my MSc year

# Problem description: construct the [shortest Eulerian-path] for any input graph G(V,E). 

An Euler Path (or sometimes called Euler Trail) is a path/trail in a graph which visits every edge exactly once. A graph is Eulerian (containing at least one Euler Path) is required to have all even-degree vertices or only two odd-degree vertices.

G can be connected, dis-connected or having too many vertices with odd-degree. This requires further modifications to the graph to construct a suitable Euler Circuit/Path that meets the requirements. The process of adding edges (or possibly vertices) are refered as Eulerisation. 

This program performs Eulerisation using heuristics approach in comparison with Skiena’s Algorithm , then computes Eulerian path using Hierholzer’s Algorithm and Fleury’s Algorithm [to find the graph's bridges, Tarjan's bridge finding algorithm was implemented (which is a modified DFS)]

#Application: 

some wonders why this simple problem (dated back in 1700) still being studied nowadays, not only under mathematics or computer science but also many other disciplines such as business and management, logistics, etc. The answer is probably: because finding Euler Circuit/Path or constructing Eulerian graph provides the most elegant, efficient and optimal solutions for almost every kind of problems where tasks or activites are taken along edges of a graph such as garbage collecting, planning deliveries activities, route planning, electronic circuit design, to complex problems such as reconstruction of DNA sequence and so much more.

Furthermore, every person probably come across this puzzle once a child: can you draw this shape without lifting your pencil?

![Alt text](https://cloud.githubusercontent.com/assets/19204793/19038344/005a1f88-8973-11e6-93cb-88c8e94fe97f.jpg)

Compiled with qmake (2012); libs: qt5, BoostGraphLibrary; some dependencies from QtCreator. Looks natively (on Windows) i.e.:

![Alt text](https://cloud.githubusercontent.com/assets/19204793/19038465/83d3ff14-8973-11e6-9e8d-0b9462cc546d.JPG)
