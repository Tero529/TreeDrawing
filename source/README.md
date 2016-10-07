\mainpage Computer Graphics IS F311 Assignment 1 
\section Contributors
 *  Varun Natu 2014A7PS841H
 *  Ayush Sharma 2014A7PS   H
 *  Akanksha Pandey 2014A7PS151H
\section Implementations
\subsection algo1 Wetherell Shannon (WS) 
The algorithm specified by Wetherell and Shannon has been implemented, and the source code can be found in the directory "source/WetherellShannon" \n The Implementation has support for both variations of the algorithm mentioned in the paper i.e 
* The NORMAL implementation which centers parents over it's children but is not minimum in width
* The MODIFIED implementation which provides minimum width but may produce 'UGLY' trees due to the absence of centering 
\n The trees that have been generated (both on user input and otherwise) and used for WS binary search trees.\n
\see mainWS.c WetherellShannon.h
\subsection algo2 Tilford Reingold (TR)
The algorithm specified by Tilford and Reingold has been implemented and the source code can be found in the directory "source/TilfordReingold".\nOnce again the tree type that has been used for this implementation of TR is the binary search tree.
\see mainTR.c TilfordReingold.h
\subsection algo3 Extension to N-ary Trees
Using the previous two papers as inspiration we have extended the main concept of the WS Algorithm to accomodate arbtrarily size trees.
\n We use a modifed version of the tree node used in WS by adding sibling pointers. The algorithm performs two walks similar to WS. Before performing an addional pre order walk to draw  the tree with the generated coordinates.
\see main.c nAry.h

\subsection extra_algos Drawing Algorithms 
We have used 3 fundamental algorithms to accomplish the rendering part of the project.
1. <b> Generalised Bresenham's Line Drawing </b> 
2. <b> Midpoint Circle Algorithm Using 8-Way symmetry </b>
3. <b> Variation of 4-Neighbour Boundary Fill </b> \n Starting from circle's center a 4 neighbour fill is applied while the point has not been visited and does not lie outside the circle

\see drawFunctions.h