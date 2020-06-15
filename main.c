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

void mostrarMatriz(int **matrizCla,int **matrizHor,int **matrizVer,int filas, int columnas){

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j)
            matrizCla[i][j]?printf("|*"):printf("| ");
        printf("|     ");
        for (int j = 0; j < columnas; ++j)
            matrizHor[i][j]?printf("|*"):printf("| ");
        printf("|     ");
        for (int j = 0; j < columnas; ++j)
            matrizVer[i][j]?printf("|*"):printf("| ");
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

  000000000000000000000000
  000000000000000000000000
  010010000000000000000000    cadena: 000000000000000000000000000000000000000000000000010010000000000000000000000001000000000000000000010001000000000000000000001111000000000000000000000000000000000000000000000000000000000000000000
  000001000000000000000000
  010001000000000000000000
  001111000000000000000000
  000000000000000000000000    nave espacial hacia la derecha  8 filas  24 columnas
  000000000000000000000000



  00000000000000000000
  00000000101000000000
  00000001000000000000
  00000001000000000000
  00000001001000000000  cadena: 0000000000000000000000000000101000000000000000010000000000000000000100000000000000000001001000000000000000011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
  00000001110000000000
  00000000000000000000
  00000000000000000000
  00000000000000000000
  00000000000000000000  nave espacial hacia abajo  11 x 20
  00000000000000000000

 */

int main(int argc, char const *argv[])
{

    char cadena[255] = "0000000000000000000000000000101000000000000000010000000000000000000100000000000000000001001000000000000000011100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    int filas=11,columnas=20,cont=1,nGeneraciones=50;

    int **matrizCla = crearMatriz(filas,columnas);
    int **matrizHor = crearMatriz(filas,columnas);
    int **matrizVer = crearMatriz(filas,columnas);
    int **matrizAux = crearMatriz(filas,columnas);

    llenarMatriz(matrizCla,filas,columnas,cadena);
    llenarMatriz(matrizHor,filas,columnas,cadena);
    llenarMatriz(matrizVer,filas,columnas,cadena);
    llenarMatriz(matrizAux,filas,columnas,cadena);

    while (cont<=nGeneraciones){
        mostrarMatriz(matrizCla,matrizHor,matrizVer,filas,columnas);
        printf("Generación %i\n\n",cont++);

        copiarMatriz(matrizAux,matrizCla,filas,columnas);
        gClasico(matrizCla,matrizAux,filas,columnas);

        copiarMatriz(matrizAux,matrizHor,filas,columnas);
        gHorizontal(matrizHor,matrizAux,filas,columnas);

        copiarMatriz(matrizAux,matrizVer,filas,columnas);
        gVertical(matrizVer,matrizAux,filas,columnas);

        usleep(5000*1000);
    }

    return 0;
}