#include <stdio.h>
#include <math.h>
#include "glfem.h"


double integrate(double x[3], double y[3], double (*f) (double, double))
{
    double I=0;
    //double xLoc[3];
    //double yLoc[3];
    //double Jaco = cabs((x[1]-x[0])*(y[2]-y[0])-(x[2]-x[0])*(y[1]-y[0]));
    //double xi[3] = {(double)1/6 , (double)1/6 , (double)2/3 };
    //double mu[3] = { (double)1/6 ,(double)2/3 ,(double)1/6 };
    
    int n = 3;
    //for (int i = 0; i < n; i++) {
      //      xLoc[i] =x[0]* (1 - xi[i] - mu[i]) +x[1]* xi[i] +x[2]* mu[i];
        //    yLoc[i] = y[0] * (1 - xi[i] - mu[i]) + y[1] * xi[i] + y[2] * mu[i];
    //}
    
    double w[3] = { (double) (1 / 6),(double)(1 / 6),(double)(1 / 6) };
    for (int u = 0; u < n; u++) {
        I += (w[u] * f(x[u], y[u]));
    }
//
// Pour dessiner l'element, les sommets du triangle :-)
// Decommenter la ligne pour dessiner aussi les points d'integration
//

  glfemSetColor(GLFEM_BLACK); glfemDrawElement(x,y,3);
  glfemSetColor(GLFEM_BLUE);  glfemDrawNodes(x,y,3);
//  glfemSetColor(GLFEM_RED);   glfemDrawNodes(xLoc,yLoc,3);
    


    return I;
}

double integrateRecursive(double x[3], double y[3], double (*f)(double,double), int n)
{

//
// ... A modifier :-)
// y-compris la ligne juste en dessous :-)
//
    double xLoc[3];
    double yLoc[3];
    double xi[3] = { (double)(1 / 6) , (double)(1 / 6) , (double)(2 / 3) };
    double mu[3] = { (double)(1 / 6) ,(double)(2 / 3) ,(double)(1 / 6) };

    int m = 3;
    for (int i = 0; i < m; i++) {
        xLoc[i] = x[0] * (1 - xi[i] - mu[i]) + x[1] * xi[i] + x[2] * mu[i];
        yLoc[i] = y[0] * (1 - xi[i] - mu[i]) + y[1] * xi[i] + y[2] * mu[i];
    }
    double Jaco = (x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]);
    
    double I = 0;
    if (n > 0) {
        n--;
        //double noeudx[3] = {(double)cabs((x[2] - x[0]))/2, (double)cabs((x[0] - x[1])) / 2, (double)cabs((x[1] - x[2])) / 2 };
        //double noeudy[3] = {(double)cabs((y[2] - y[0])) / 2,(double)cabs((y[0] - y[1])) / 2 ,(double)cabs((y[1] - y[2])) / 2 };
        double noeudx[3] = { xLoc[0],(double) xLoc[1] / 2 ,(double) xLoc[1] / 2 };
        double noeudy[3] = { (double)yLoc[2] / 2,(double)yLoc[0] / 2 ,(double)yLoc[2] / 2 };

        
        double x1[3] = { x[0],noeudx[1],noeudx[0] };
        double y1[3] = { y[0],noeudy[1],noeudy[0] };
        double a = integrateRecursive(x1, y1, f, n);
        double x2[3] = { noeudx[1], x[1],noeudx[2] };
        double y2[3] = { noeudy[1],y[1],noeudy[2] };
        double b = integrateRecursive(x2, y2, f, n);
        double x3[3] = { noeudx[0],x[2],noeudx[2] };
        double y3[3] = { noeudy[0], y[2],noeudy[2] };
        double c = integrateRecursive(x3, y3, f, n);
        double x4[3] = { noeudx[2],noeudx[0],noeudx[1] };
        double y4[3] = { noeudy[2], noeudy[0],noeudy[1] };
        double d = integrateRecursive(x4, y4, f, n);
        return a+b+c+d ;
    }
    else{
        double I = integrate(xLoc, yLoc, f);
        return I*Jaco;
    }
}
