#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(int argc, char const *argv[]) {

//fixer jmax
int j_max=;
int eps=;
int d=;
int N=;
//lire points de controle et n nbre de pts de controle


//boucle sur 0:jmax{
for( int i=0; i<j_max; i++){
  //DC
  deCasljeau( int N, int d ,  float pointDeControl[][N], float eps, float** gamma, float** delta );

  //tracer poly successif: soritr les points dans un fichier

  //remplir les nvx points de controle


}

//sortie: obtenir 2^n+1 pts a ecrire dans un fichier

  return 0;
}

int deCasljeau( int N, int d,  float pointDeControl[][N], float eps, float** gamma, float** delta ){


//initialisation les deux extremites de P1
for ( int i=0; i<d; i++){
  gamma[i][0]=pointDeControl[i][0];
  delta[i][0]=pointDeControl[i][N];
}


for( int k=0; k<N; k++ ){
  for( int i=0; i<N-k; i++){
    for( int j=0; j<d; j++){
      //recurrence DC
      pointDeControl[j][i] = pointDeControl[j][i] * (1 - eps) + pointDeControl[j][i + 1] * eps;
    }
    //remplir gamma delta pour chaque iteration
    for( int i=0; i<d ; i++){
      gamma[i][k]= pointDeControl[i][0];
      delta[i][n-k]= pointDeControl[i][n-k];
    }
  }
}
}

int
