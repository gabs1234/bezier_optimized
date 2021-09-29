#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** alloctab( int dim1, int dim2 );
void freetab( void *ptr );

int recurseDeCasteljau( int startIndex, int N, float eps, int d, float** GM, float** gamma, float** delta, int j, int jmax );
int deCasljeau( int startIndex, int N, int d, float** GM, float eps, float** gamma, float** delta );
void print_matrix( int a, int b, float** matrix );

int main(int argc, char const *argv[]) {
	// Parametres
	int j_max = 3;
	float eps = 0.5;
	int d = 2;
	int N = 3; //le nbre de pts de cont

	//vecteur contenant les 2^j*n+1 points de la fin
	float** GM = alloctab(pow(2,j_max)*N+1, d);

	//lire les points de contrôle
	FILE *data;
	data = fopen("data.dat", "r");

	if( data == NULL ){
		printf( " Impossible d'ouvrir le fichier texte");
		return 1;
	}

	for( int i = 0; i < N; i++ ){
		for( int j = 0; j < d; j++ ){
			fscanf(data, "%f ", &GM[i][j]);
		}
	}

	fclose(data);

	print_matrix(N, d, GM);

	float** gamma = alloctab( N, d );
	float** delta = alloctab( N, d );

	// Recursivement trouver Gamma et Delta
	printf("Begin recursion\n");
	recurseDeCasteljau(0, N, eps, d, GM, gamma, delta, 0, j_max);
	printf("End recursion\n");

	//sortie: obtenir 2^n+1 pts a ecrire dans un fichier
	//tracer pol final Ecriture dans un fichier
	//Ecriture dans un fichier
	FILE *result;
	result = fopen( "resultats.txt", "w");
	if( result == NULL ){
		printf( " Impossible d'ouvrir le fichier texte");
	}

	// Ecriture resultat dans un fichier
	for( int i = 0; i < pow(2, j_max)*N+1; i++ ){
		for( int j = 0; j < d; j++ ){
			fprintf( result, "%f ", GM[i][j]);
		}
		fprintf( result, "\n");
	}

	fclose(result);
	freetab(GM);
	freetab(gamma);
	freetab(delta);

  return 0;
}



int recurseDeCasteljau( int startIndex, int N, float eps, int d, float** GM, float** gamma, float** delta, int j, int jmax){
	printf("Iteration %d\n", j);
	// Dondition d'arret
	if( jmax < j ){
		return 0;
	}

	// On cherche les Gamma et Delta avec DeCasteljau
	deCasljeau(startIndex, N, d, GM, eps, gamma, delta);

	print_matrix(N, 2, GM);

	// On insert les Gamma dans GM
	int tmp_counter = 0;
	for( int j = startIndex; j < startIndex+N; j++ ){
		for( int k = 0; k < d; k++ ){
			GM[j][k] = gamma[tmp_counter][k];
			// printf("delta, %f, GM: %f\n", delta[tmp_counter][k], GM[j][k] );
			printf("delta: %f\n", gamma[tmp_counter][k] );
		}
		tmp_counter++;
	}

	// On insert les Delta dans GM
	tmp_counter = 0;
	for( int j = startIndex+N; j < startIndex + 2*N-1; j++ ){
		for( int k = 0; k < d; k++ ){
			GM[j][k]=delta[tmp_counter][k];
			printf("gamma: %f\n", delta[tmp_counter][k] );
		}
		tmp_counter++;
	}

	// On applique la fonction recursivement sur les Delta d'abord
	recurseDeCasteljau( startIndex+N,  N-1, eps, d, GM, gamma, delta, j+1, jmax);
	printf("Gamma finished. J is %d\n", j);
	// Puis, on applique la fonction recursivement sur les Gamma
	recurseDeCasteljau( startIndex, N, eps, d, GM, gamma, delta, j+1, jmax);
	printf("Delta finished. J is %d\n", j);
}

int deCasljeau( int startIndex, int N, int d, float** GM, float eps, float** gamma, float** delta ){

	//initialisation les deux extremites de P1
	for ( int i = 0; i < d; i++){
	  gamma[0][i] = GM[startIndex][i];
	  delta[0][i] = GM[startIndex+N-1][i];
	}
	int k = 0;
	int counter = 1;
	for( int j = startIndex+1; j < startIndex+N; j++ ){
	  for( k = startIndex; k < startIndex+N-j; k++){
	    for( int p = 0; p < d; p++){
	      GM[k][p] = GM[k][p] * (1 - eps) + GM[k + 1][p] * eps;
	    }
	  }
		//remplir gamma delta pour chaque iteration
		for( int i = 0; i < d ; i++){
			gamma[counter][i] = GM[startIndex][i];
			delta[counter][i] = GM[k][i];
		}
		counter++;
	}
}

void print_matrix(int a, int b, float** matrix ){
	for (size_t i = 0; i < a; i++) {
		for (size_t j = 0; j < b; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}

float **alloctab(int dim1, int dim2) {
  float **ptr;

  ptr = malloc(dim1*sizeof(float *));
	if (ptr != NULL) {
		int i, taille_ligne = dim2*sizeof(float);
		float *tmp = malloc(dim1*taille_ligne);
		if (tmp != NULL) {
			for (i = 0; i < dim1; i++) {
				ptr[i] = tmp;
				tmp += dim2;
			}
		}
		else
			ptr = NULL;
	}
	return(ptr);
}

void freetab(void *ptr) {
	void **ptrT=ptr;
	free(ptrT[0]);
	free(ptr);
}
