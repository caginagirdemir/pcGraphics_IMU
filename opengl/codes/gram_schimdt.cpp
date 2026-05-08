#include <stdio.h>
#include <iostream>
#include <math.h>

double dot_p(double *x, double *y) {
 
    int i;
    double ans = 0;
 
    for(i=0; i<3; ++i)
        ans += x[i]*y[i];
 
    return ans;
}


void normalize(double *x) {
 
    double norm = sqrt(dot_p(x, x));
    
    int i;
    for(i=0; i<3; ++i)
        x[i] /= norm;
}


void gram_schimdt_o(double q[][3], int n) {
 
    int i, j, k;
 
    for(i=1; i<n; ++i) {
        for(j=0; j<i; ++j) {
            double scaling_factor = dot_p(q[j], q[i]) 
                                    / dot_p(q[j], q[j]);

            for(k=0; k<3; ++k)
                q[i][k] -= scaling_factor*q[j][k];
        }
    }
 
    for(i=0; i<n; ++i)
        normalize(q[i]);
}
 
int main() {

    double e[3][3] = {{ 0.7071067811865475, 0.7071067811865475, 0},{-1, 1, -1},{0, -2, -2}};
 
    gram_schimdt_o(e, 3);
    std::cout <<"orthonormal vectors : \n \n";
 
    for(int i=0; i<3; ++i) {
        printf("q[%d] = [ ", i);
        for(int j=0; j<3; ++j)
            printf("%lf  ", e[i][j]);
        printf("]\n");
    }
}
