//	
//	Creado por Santiago Villahermosa y Roberson Garcia
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Un milisegundo son 1000 microsegundos usleep() usa microsegundos
// segundos a milisegundos x1000

int **limpiarMatriz(int **matriz,int filas,int columnas){
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            matriz[i][j] = 0;
}

int **crearMatriz(int filas, int columnas){

    int **pp = (int**) malloc(sizeof(int*)*filas);

    for (int i = 0; i < filas; ++i)
        pp[i] = (int *) malloc(sizeof(int)*columnas);

    limpiarMatriz(pp,filas,columnas);

    return pp;
}

void liberarMatriz(int **matriz,int filas){
    for (int i = 0; i < filas; ++i)
        free(matriz[i]);
    free(matriz);
}

void mostrarMatriz(int **matriz,int filas, int columnas){

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j)
            printf("|%d",matriz[i][j]);
        printf("|     ");
        for (int j = 0; j < columnas; ++j)
            printf("|%d",matriz[i][j]);
        printf("|     ");
        for (int j = 0; j < columnas; ++j)
            printf("|%d",matriz[i][j]);
        printf("|\n");
    }
    printf("\n");

}

void llenarMatriz(int **matriz,int filas,int columnas, char * cadena){
    int cont=0;
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            matriz[i][j]= cadena[cont++] - '0';
}

void copiarMatriz(int **matriz1,int **matriz2,int filas,int columnas){
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            matriz1[i][j] = matriz2[i][j];
}

void gClasico(int **matrizN,int **matrizC,int filas,int columnas){

    limpiarMatriz(matrizN,filas,columnas);
    int vivosN;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            vivosN=0;

            if((i!=0)&&(i!=filas-1)&&(j!=0)&&(j!=columnas-1)){
                vivosN = matrizC[i-1][j-1] + matrizC[i-1][j] + matrizC[i-1][j+1] + matrizC[i][j-1] + matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j] + matrizC[i+1][j-1];
            }else if((i==0)&&(j==0)){
                vivosN = matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j];
            }else if((i==0)&&(j==columnas-1)){
                vivosN = matrizC[i][j-1] + matrizC[i+1][j-1] + matrizC[i+1][j];
            }else if((i==filas-1)&&(j==columnas-1)){
                vivosN= matrizC[i][j-1] + matrizC[i-1][j-1] + matrizC[i-1][j];
            }else if((i==filas-1)&&(columnas==0)){
                vivosN = matrizC[i-1][j]+matrizC[i-1][j+1]+matrizC[i][j+1];
            }else if(i==0){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i+1][j-1]+matrizC[i+1][j+1]+matrizC[i+1][j];
            }else if(i==filas-1){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i-1][j-1]+matrizC[i-1][j]+matrizC[i-1][j+1];
            }else if(j==0){
                vivosN = matrizC[i-1][j]+matrizC[i+1][j]+matrizC[i+1][j+1]+matrizC[i][j+1]+matrizC[i-1][j+1];
            }else if(j==columnas-1){
                vivosN = matrizC[i-1][j] + matrizC[i+1][j] + matrizC[i-1][j-1] + matrizC[i][j-1] + matrizC[i+1][j-1];
            }

            if((matrizC[i][j]==0)&&(vivosN==3))
                matrizN[i][j] = 1;

            if((matrizC[i][j]==1)&&((vivosN<2)||(vivosN>3)))
                matrizN[i][j] = 0;
            else if(matrizC[i][j]==1)
                matrizN[i][j] = 1;

        }
    }

}

void gHorizontal(int **matrizN,int **matrizC,int filas,int columnas){
    limpiarMatriz(matrizN,filas,columnas);
    int vivosN;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            vivosN=0;

            if((i!=0)&&(i!=filas-1)&&(j!=0)&&(j!=columnas-1)){
                vivosN = matrizC[i-1][j-1] + matrizC[i-1][j] + matrizC[i-1][j+1] + matrizC[i][j-1] + matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j] + matrizC[i+1][j-1];
            }else if((i==0)&&(j==0)){
                vivosN = matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j] + matrizC[filas-1][j] + matrizC[filas-1][j+1];
            }else if((i==0)&&(j==columnas-1)){
                vivosN = matrizC[i][j-1] + matrizC[i+1][j-1] + matrizC[i+1][j] + matrizC[filas-1][j] + matrizC[filas-1][j-1];
            }else if((i==filas-1)&&(j==columnas-1)){
                vivosN= matrizC[i][j-1] + matrizC[i-1][j-1] + matrizC[i-1][j] + matrizC[0][j] + matrizC[0][j-1];
            }else if((i==filas-1)&&(columnas==0)){
                vivosN = matrizC[i-1][j]+matrizC[i-1][j+1]+matrizC[i][j+1] + matrizC[0][j] + matrizC[0][j+1];
            }else if(i==0){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i+1][j-1]+matrizC[i+1][j+1]+matrizC[i+1][j]+matrizC[filas-1][j]+matrizC[filas-1][j+1]+matrizC[filas-1][j-1];
            }else if(i==filas-1){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i-1][j-1]+matrizC[i-1][j]+matrizC[i-1][j+1]+matrizC[0][j]+matrizC[0][j+1]+matrizC[0][j-1];
            }else if(j==0){
                vivosN = matrizC[i-1][j]+matrizC[i+1][j]+matrizC[i+1][j+1]+matrizC[i][j+1]+matrizC[i-1][j+1];
            }else if(j==columnas-1){
                vivosN = matrizC[i-1][j] + matrizC[i+1][j] + matrizC[i-1][j-1] + matrizC[i][j-1] + matrizC[i+1][j-1];
            }

            if((matrizC[i][j]==0)&&(vivosN==3))
                matrizN[i][j] = 1;

            if((matrizC[i][j]==1)&&((vivosN<2)||(vivosN>3)))
                matrizN[i][j] = 0;
            else if(matrizC[i][j]==1)
                matrizN[i][j] = 1;

        }
    }
}

void gVertical(int **matrizN,int **matrizC,int filas,int columnas){

    limpiarMatriz(matrizN,filas,columnas);
    int vivosN;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            vivosN=0;

            if((i!=0)&&(i!=filas-1)&&(j!=0)&&(j!=columnas-1)){
                vivosN = matrizC[i-1][j-1] + matrizC[i-1][j] + matrizC[i-1][j+1] + matrizC[i][j-1] + matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j] + matrizC[i+1][j-1];
            }else if((i==0)&&(j==0)){
                vivosN = matrizC[i][j+1] + matrizC[i+1][j+1] + matrizC[i+1][j]+matrizC[i][columnas-1]+matrizC[i+1][columnas-1];
            }else if((i==0)&&(j==columnas-1)){
                vivosN = matrizC[i][j-1] + matrizC[i+1][j-1] + matrizC[i+1][j] + matrizC[i][0] + matrizC[i+1][0];
            }else if((i==filas-1)&&(j==columnas-1)){
                vivosN= matrizC[i][j-1] + matrizC[i-1][j-1] + matrizC[i-1][j] + matrizC[i][0] + matrizC[i-1][0];
            }else if((i==filas-1)&&(columnas==0)){
                vivosN = matrizC[i-1][j]+matrizC[i-1][j+1]+matrizC[i][j+1]+matrizC[i][columnas-1]+matrizC[i-1][columnas-1];
            }else if(i==0){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i+1][j-1]+matrizC[i+1][j+1]+matrizC[i+1][j];
            }else if(i==filas-1){
                vivosN = matrizC[i][j-1]+matrizC[i][j+1]+matrizC[i-1][j-1]+matrizC[i-1][j]+matrizC[i-1][j+1];
            }else if(j==0){
                vivosN = matrizC[i-1][j]+matrizC[i+1][j]+matrizC[i+1][j+1]+matrizC[i][j+1]+matrizC[i-1][j+1]+matrizC[i][columnas-1]+matrizC[i-1][columnas-1]+matrizC[i+1][columnas-1];
            }else if(j==columnas-1){
                vivosN = matrizC[i-1][j]+matrizC[i+1][j]+matrizC[i-1][j-1]+matrizC[i][j-1]+matrizC[i+1][j-1]+matrizC[i][0]+matrizC[i+1][0]+matrizC[i-1][0];
            }

            if((matrizC[i][j]==0)&&(vivosN==3))
                matrizN[i][j] = 1;

            if((matrizC[i][j]==1)&&((vivosN<2)||(vivosN>3)))
                matrizN[i][j] = 0;
            else if(matrizC[i][j]==1)
                matrizN[i][j] = 1;

        }
    }

}


/* Automatas para probar

  000000000
  000000000
  000010000
  000010000     Cadena: 000000000000000000000010000000010000000010000000010000000010000000000000000000000
  000010000
  000010000
  000010000
  000000000
  000000000    Palo 9 filas 9 columnas

  000   cadena: 000111000
  111   palo 3 filas 3 columnas
  000

  0000000000000
  0000000000000
  0000000000000
  0000000000000  cadena: 0000000000000000000000000000000000000000000000000000000000000000000000010000000000011100000000001010000000000010000000000000000000000000000000000000000000000000000000000
  0000000000000
  0000001000000
  0000011100000
  0000010100000
  0000001000000
  0000000000000
  0000000000000  Mini explorador 13 filas 13 columnas
  0000000000000
  0000000000000

 */

int main(int argc, char const *argv[])
{

    char cadena[255] = "0000000000000000000000000000000000000000000000000000000000000000000000010000000000011100000000001010000000000010000000000000000000000000000000000000000000000000000000000";
    int filas=13,columnas=13,cont=1;

    int **matriznueva = crearMatriz(filas,columnas);
    int **matrizact = crearMatriz(filas,columnas);
    llenarMatriz(matrizact,filas,columnas,cadena);

    while (cont<=18){
        mostrarMatriz(matrizact,filas,columnas);
        printf("Generación %i\n\n",cont++);
        gClasico(matriznueva,matrizact,filas,columnas);
        copiarMatriz(matrizact,matriznueva,filas,columnas);
        usleep(5000*1000);
    }

    return 0;
}