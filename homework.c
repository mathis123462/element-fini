#include <stdio.h>
#include <math.h>
#include "glfem.h"


double integrate(double x[3], double y[3], double (*f) (double, double))
{
    double I = 0;
    double xLoc[3];
    double yLoc[3];
    double wLoc[3];

    double xi[3] = {1/6,1/6,2/3};
    double mu[3] = {1/6,2/3,1/6};
    double w[3] = {1/6,1/6,1/6};
    
    int n = 3;
    int i;
    for (i = 0; i < n; i++) {
        double phi[3] = { 1 - xi[i]-mu[i],xi[i],mu[i] };
        for (int j = 0; j < n; j++) {
            xLoc[i] +=x[j]*phi[j] ;
            yLoc[i] += y[j] * phi[j];
            wLoc[i] += w[j] * phi[j];
        }
    }
    for (i = 0; i < n; i++) {
        I += (wLoc[i] * f(xLoc[i], yLoc[i]));
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
    double noeudx[3];
    double noeudy[3];
    if (n == 0) {
        double I = integrate(x, y, f);
        return I;
    }
    else {
        for (int j = 0; j < 3; j++) {
            noeudx[j] = abs((x[j-1]-x[j])) / 2;
            noeudy[j] = abs((y[j - 1] - y[j])) / 2;
        }
        n--;
        double x1[3] = {x[0],noeudx[0],noeudx[1]};
        double y1[3] = { y[0],noeudy[0],noeudy[1]};
        integrateRecursive(x1, y1, f, n);
        double x2[3] = { noeudx[0], x[1],noeudx[2] };
        double y2[3] = { noeudy[0],y[1],noeudy[2] };
        integrateRecursive(x2,y2, f, n);
        double x3[3] = { noeudx[1],x[2],noeudx[2] };
        double y3[3] = { noeudy[1], y[2],noeudy[2] };
        integrateRecursive(x3, y3, f, n);
        integrateRecursive(noeudx, noeudy, f, n);

    }   
}
