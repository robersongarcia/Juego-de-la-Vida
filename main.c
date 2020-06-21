//	
//	Creado por Santiago Villahermosa y Roberson Garcia
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Un milisegundo son 1000 microsegundos usleep() usa microsegundos
// segundos a milisegundos x1000

int **limpiarMatriz(int **matriz,int filas,int columnas){
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            matriz[i][j] = 0;
}

int **crearMatriz(int filas, int columnas){

    int **pp = (int**) malloc(sizeof(int*)*filas);

    if(pp==NULL){
        fprintf(stderr,
                "Error en malloc\n");
        exit(1);
    }

    for (int i = 0; i < filas; ++i){
        pp[i] = (int *) malloc(sizeof(int)*columnas);
        if(pp[i]==NULL){
            fprintf(stderr,
                    "Error en malloc\n");
            exit(1);
        }
    }

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
    int vivosN=0;

    if((filas!=1)&&(columnas!=1)) {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                vivosN = 0;

                if ((i != 0) && (i != filas - 1) && (j != 0) && (j != columnas - 1)) {
                    vivosN = matrizC[i - 1][j - 1] + matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j - 1] +
                             matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j] + matrizC[i + 1][j - 1];
                } else if ((i == 0) && (j == 0)) {
                    vivosN = matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j];
                } else if ((i == 0) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j];
                } else if ((i == filas - 1) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j];
                } else if ((i == filas - 1) && (columnas == 0)) {
                    vivosN = matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j + 1];
                } else if (i == 0) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j + 1] +
                             matrizC[i + 1][j];
                } else if (i == filas - 1) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j] +
                             matrizC[i - 1][j + 1];
                } else if (j == 0) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i + 1][j + 1] + matrizC[i][j + 1] +
                             matrizC[i - 1][j + 1];
                } else if (j == columnas - 1) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i - 1][j - 1] + matrizC[i][j - 1] +
                             matrizC[i + 1][j - 1];
                }

                if ((matrizC[i][j] == 0) && (vivosN == 3))
                    matrizN[i][j] = 1;

                if ((matrizC[i][j] == 1) && ((vivosN < 2) || (vivosN > 3)))
                    matrizN[i][j] = 0;
                else if (matrizC[i][j] == 1)
                    matrizN[i][j] = 1;

            }
        }
    }

    if((filas==1)&&(columnas!=1)){
        for (int i = 0;  i<columnas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[0][i+1];
            else if(i==columnas-1)
                vivosN = matrizC[0][i-1];
            else
                vivosN = matrizC[0][i-1]+matrizC[0][i+1];

            if ((matrizC[0][i] == 0) && (vivosN == 3))
                matrizN[0][i] = 1;

            if ((matrizC[0][i] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[0][i] = 0;
            else if (matrizC[0][i] == 1)
                matrizN[0][i] = 1;

        }
    }

    if((filas!=1)&&(columnas==1)){
        for (int i = 0;  i<filas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[i+1][0];
            else if(i==filas-1)
                vivosN = matrizC[i-1][0];
            else
                vivosN = matrizC[i-1][0]+matrizC[i+1][0];

            if ((matrizC[i][0] == 0) && (vivosN == 3))
                matrizN[i][0] = 1;

            if ((matrizC[i][0] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[i][0] = 0;
            else if (matrizC[i][0] == 1)
                matrizN[i][0] = 1;
        }
    }

}

void gHorizontal(int **matrizN,int **matrizC,int filas,int columnas){
    limpiarMatriz(matrizN,filas,columnas);
    int vivosN=0;

    if((filas!=1)&&(columnas!=1)) {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                vivosN = 0;

                if ((i != 0) && (i != filas - 1) && (j != 0) && (j != columnas - 1)) {
                    vivosN = matrizC[i - 1][j - 1] + matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j - 1] +
                             matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j] + matrizC[i + 1][j - 1];
                } else if ((i == 0) && (j == 0)) {
                    vivosN = matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j] + matrizC[filas - 1][j] +
                             matrizC[filas - 1][j + 1];
                } else if ((i == 0) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j] + matrizC[filas - 1][j] +
                             matrizC[filas - 1][j - 1];
                } else if ((i == filas - 1) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j] + matrizC[0][j] +
                             matrizC[0][j - 1];
                } else if ((i == filas - 1) && (columnas == 0)) {
                    vivosN = matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j + 1] + matrizC[0][j] +
                             matrizC[0][j + 1];
                } else if (i == 0) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j + 1] +
                             matrizC[i + 1][j] + matrizC[filas - 1][j] + matrizC[filas - 1][j + 1] +
                             matrizC[filas - 1][j - 1];
                } else if (i == filas - 1) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j] +
                             matrizC[i - 1][j + 1] + matrizC[0][j] + matrizC[0][j + 1] + matrizC[0][j - 1];
                } else if (j == 0) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i + 1][j + 1] + matrizC[i][j + 1] +
                             matrizC[i - 1][j + 1];
                } else if (j == columnas - 1) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i - 1][j - 1] + matrizC[i][j - 1] +
                             matrizC[i + 1][j - 1];
                }

                if ((matrizC[i][j] == 0) && (vivosN == 3))
                    matrizN[i][j] = 1;

                if ((matrizC[i][j] == 1) && ((vivosN < 2) || (vivosN > 3)))
                    matrizN[i][j] = 0;
                else if (matrizC[i][j] == 1)
                    matrizN[i][j] = 1;

            }
        }
    }

    if((filas==1)&&(columnas!=1)){
        for (int i = 0;  i<columnas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[0][i+1];
            else if(i==columnas-1)
                vivosN = matrizC[0][i-1];
            else
                vivosN = matrizC[0][i-1]+matrizC[0][i+1];

            if ((matrizC[0][i] == 0) && (vivosN == 3))
                matrizN[0][i] = 1;

            if ((matrizC[0][i] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[0][i] = 0;
            else if (matrizC[0][i] == 1)
                matrizN[0][i] = 1;

        }
    }

    if((filas!=1)&&(columnas==1)){
        for (int i = 0;  i<filas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[i+1][0]+matrizC[filas-1][0];
            else if(i==filas-1)
                vivosN = matrizC[i-1][0]+matrizC[0][0];
            else
                vivosN = matrizC[i-1][0]+matrizC[i+1][0];

            if ((matrizC[i][0] == 0) && (vivosN == 3))
                matrizN[i][0] = 1;

            if ((matrizC[i][0] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[i][0] = 0;
            else if (matrizC[i][0] == 1)
                matrizN[i][0] = 1;
        }
    }



}

void gVertical(int **matrizN,int **matrizC,int filas,int columnas){

    limpiarMatriz(matrizN,filas,columnas);
    int vivosN;

    if((filas!=1)&&(columnas!=1)) {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                vivosN = 0;

                if ((i != 0) && (i != filas - 1) && (j != 0) && (j != columnas - 1)) {
                    vivosN = matrizC[i - 1][j - 1] + matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j - 1] +
                             matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j] + matrizC[i + 1][j - 1];
                } else if ((i == 0) && (j == 0)) {
                    vivosN = matrizC[i][j + 1] + matrizC[i + 1][j + 1] + matrizC[i + 1][j] + matrizC[i][columnas - 1] +
                             matrizC[i + 1][columnas - 1];
                } else if ((i == 0) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j] + matrizC[i][0] +
                             matrizC[i + 1][0];
                } else if ((i == filas - 1) && (j == columnas - 1)) {
                    vivosN = matrizC[i][j - 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j] + matrizC[i][0] +
                             matrizC[i - 1][0];
                } else if ((i == filas - 1) && (columnas == 0)) {
                    vivosN = matrizC[i - 1][j] + matrizC[i - 1][j + 1] + matrizC[i][j + 1] + matrizC[i][columnas - 1] +
                             matrizC[i - 1][columnas - 1];
                } else if (i == 0) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i + 1][j - 1] + matrizC[i + 1][j + 1] +
                             matrizC[i + 1][j];
                } else if (i == filas - 1) {
                    vivosN = matrizC[i][j - 1] + matrizC[i][j + 1] + matrizC[i - 1][j - 1] + matrizC[i - 1][j] +
                             matrizC[i - 1][j + 1];
                } else if (j == 0) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i + 1][j + 1] + matrizC[i][j + 1] +
                             matrizC[i - 1][j + 1] + matrizC[i][columnas - 1] + matrizC[i - 1][columnas - 1] +
                             matrizC[i + 1][columnas - 1];
                } else if (j == columnas - 1) {
                    vivosN = matrizC[i - 1][j] + matrizC[i + 1][j] + matrizC[i - 1][j - 1] + matrizC[i][j - 1] +
                             matrizC[i + 1][j - 1] + matrizC[i][0] + matrizC[i + 1][0] + matrizC[i - 1][0];
                }

                if ((matrizC[i][j] == 0) && (vivosN == 3))
                    matrizN[i][j] = 1;

                if ((matrizC[i][j] == 1) && ((vivosN < 2) || (vivosN > 3)))
                    matrizN[i][j] = 0;
                else if (matrizC[i][j] == 1)
                    matrizN[i][j] = 1;

            }
        }
    }

    if((filas==1)&&(columnas!=1)){
        for (int i = 0;  i<columnas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[0][i+1]+matrizC[0][columnas-1];
            else if(i==columnas-1)
                vivosN = matrizC[0][i-1]+matrizC[0][0];
            else
                vivosN = matrizC[0][i-1]+matrizC[0][i+1];

            if ((matrizC[0][i] == 0) && (vivosN == 3))
                matrizN[0][i] = 1;

            if ((matrizC[0][i] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[0][i] = 0;
            else if (matrizC[0][i] == 1)
                matrizN[0][i] = 1;

        }
    }

    if((filas!=1)&&(columnas==1)){
        for (int i = 0;  i<filas ; i++) {
            vivosN=0;

            if(i==0)
                vivosN = matrizC[i+1][0];
            else if(i==filas-1)
                vivosN = matrizC[i-1][0];
            else
                vivosN = matrizC[i-1][0]+matrizC[i+1][0];

            if ((matrizC[i][0] == 0) && (vivosN == 3))
                matrizN[i][0] = 1;

            if ((matrizC[i][0] == 1) && ((vivosN < 2) || (vivosN > 3)))
                matrizN[i][0] = 0;
            else if (matrizC[i][0] == 1)
                matrizN[i][0] = 1;
        }
    }

}


void crearArchivos(){
    fopen("clasico.txt","w");
    fopen("horizontal.txt","w");
    fopen("vertical.txt","w");
}

void llenarArchivos(int **matrizCla,int **matrizHor,int **matrizVer,int filas,int columnas,int gen){
    FILE *pArchivoCla = fopen("clasico.txt","a");
    FILE *pArchivoHor = fopen("horizontal.txt","a");
    FILE *pArchivoVer = fopen("vertical.txt","a");

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j){
            matrizCla[i][j] ? fprintf(pArchivoCla,"|*") : fprintf(pArchivoCla,"| ");
            matrizHor[i][j] ? fprintf(pArchivoHor,"|*") : fprintf(pArchivoHor,"| ");
            matrizVer[i][j] ? fprintf(pArchivoVer,"|*") : fprintf(pArchivoVer,"| ");
        }
        fprintf(pArchivoVer,"|\n");
        fprintf(pArchivoHor,"|\n");
        fprintf(pArchivoCla,"|\n");
    }
    fprintf(pArchivoCla,"Generacion %i\n\n",gen);
    fprintf(pArchivoHor,"Generacion %i\n\n",gen);
    fprintf(pArchivoVer,"Generacion %i\n\n",gen);

    fclose(pArchivoCla);
    fclose(pArchivoHor);
    fclose(pArchivoVer);
}

int validacion(char * m)
{
    char *p;
    int c,j,opcion,bolean,bandera=0,cont;

    opcion=0;

    if (m[0]=='{')
    {
        opcion=0;
        cont=1;
        c=1;
        bolean=1;

        while(c<strlen(m))
        {
            if(c==1)
                if(m[1]!='{')
                    bandera=1;

            switch (opcion)
            {
                case 0:
                    if ((m[c]!='0')&&(m[c]!='1')&&(m[c]!='{')) return 0;
                    opcion=1;
                    if (m[c]=='{'){
                        cont++;
                        opcion=0;
                        if (cont==3) return 0;
                    }
                    break;

                case 1:
                    if ((m[c]!=',')&&(m[c]!='}')) return 0;
                    if (m[c]=='}'){
                        cont--;
                        if (cont<0) return 0;
                    }
                    if (m[c]==',')
                        opcion=2;
                    else
                        opcion=3;

                    break;

                case 2:
                    if ((m[c]!='0')&&(m[c]!='1')&&(m[c]!='{')) return 0;

                    if((bandera==1)&&(m[c]=='{'))
                        return 0;

                    if (m[c]=='{'){
                        opcion=0;
                        cont++;
                        if (cont==3) return 0;
                    }
                    else
                        opcion=1;

                    break;

                case 3:
                    if ((m[c]!=',')&&(m[c]!='}')) return 0;
                    if (m[c]=='}'){
                        cont--;
                        if (cont<0) return 0;
                        opcion=3;
                    }
                    else
                        opcion=2;

                    break;
            }
            c++;


        }
        if (cont!=0) return 0;
        if (bolean==0) return 0;
    }
    else return 0;

    c=0;

    for(j=0;m[j]!='}';j++){
        if ((m[j]=='0')||(m[j]=='1')) c++;
    }

    cont=0;

    for(j=0;j<(strlen(m)-1);j++){
        if ((m[j]=='0')||(m[j]=='1')) cont++;
        if (m[j]=='}'){
            if (cont!=c) return 0;
            cont=0;
        }
    }

    c = cont = 0;

    for (int i=0; m[i]!='\0';i++)
    {
        if (m[i] == '{')
            c++;
        if (m[i] == '}')
            cont++;

        if(cont>c)
            return 0;
    }

    if (cont == c)
        return 1;
    else
        return 0;
}

char *filasColumnas(int*filas,int*columnas,char*cadena)
{
    int a=0,b=0,i;
    char aux[500],*n;

    for(i=0;cadena[i]!='}';i++){
        if ((cadena[i]=='0')||(cadena[i]=='1'))
            a++;
    }
    *columnas=a;
    a=0;

    if (i==strlen(cadena)-1)
        *filas=1;
    else{
        for(i=0;i<(strlen(cadena)-1);i++){
            if (cadena[i]=='}') a++;
        }
        *filas=a;
    }
    a=0;

    for (i=0;(cadena[i]!='1')&&(cadena[i]!='0');i++);
    b=i;

    if (cadena[i]=='1')
        strcpy(aux,"1");
    else
        strcpy(aux,"0");

    b++;

    if (*filas==1){
        for(i=b;i<(strlen(cadena)-1);i++){
            if (cadena[i]=='0'){
                a++;
                strcat(aux,"0");
            }
            if (cadena[i]=='1'){
                a++;
                strcat(aux,"1");
            }
        }
    }
    else{
        for(i=b;i<(strlen(cadena)-2);i++){
            if (cadena[i]=='0'){
                a++;
                strcat(aux,"0");
            }
            if (cadena[i]=='1'){
                a++;
                strcat(aux,"1");
            }
        }
    }

    n=(char*)malloc((a+1)*sizeof(char));

    if(n==NULL){
        fprintf(stderr,"Error en malloc\n");
        exit(1);
    }

    strcpy(n,aux);
    return n;
}

char *buscarArchivo(char *archivo){
    FILE *pArchivo = fopen(archivo,"r");
    char caracter,*n;
    int cont=0;
    if(pArchivo!=NULL){
        while((caracter = fgetc(pArchivo)) != EOF)
        {
            if(caracter!=' ')
                cont++;
        }
        n = (char*)malloc(sizeof(char)*(cont+1));
        if(n==NULL){
            fprintf(stderr,
                    "Error en malloc\n");
            exit(1);
        }
        cont=0;
        rewind(pArchivo);
        while((caracter = fgetc(pArchivo)) != EOF){
            if(caracter!=' ')
                n[cont++]=caracter;
        }
        return n;
    }else
        return NULL;

}

int main(int argc, char const *argv[])
{
    char *cadena,*aux,ruta[255];
    int filas,columnas,cont=1,nGeneraciones;
    long long int tiempo;

    printf("///// Bienvenido al Juego de la vida /////\n");
    printf("Introduzca el numero de generaciones: ");
    scanf("%i",&nGeneraciones);
    printf("Introduzca la ruta y nombre del archivo: ");
    scanf("%s",ruta);
    printf("Introduzca el tiempo entre generaciones en milisegundos: ");
    scanf("%i",&tiempo);

    aux = buscarArchivo(ruta);

    if(aux!=NULL){

        if (validacion(aux)) {
            cadena = filasColumnas(&filas, &columnas, aux);
            int **matrizCla = crearMatriz(filas, columnas);
            int **matrizHor = crearMatriz(filas, columnas);
            int **matrizVer = crearMatriz(filas, columnas);
            int **matrizAux = crearMatriz(filas, columnas);

            llenarMatriz(matrizCla,filas,columnas,cadena);
            llenarMatriz(matrizHor,filas,columnas,cadena);
            llenarMatriz(matrizVer,filas,columnas,cadena);
            llenarMatriz(matrizAux,filas,columnas,cadena);
            crearArchivos();

            while (cont<=nGeneraciones){
                mostrarMatriz(matrizCla,matrizHor,matrizVer,filas,columnas);
                printf("Generación %i\n\n",cont);
                llenarArchivos(matrizCla,matrizHor,matrizVer,filas,columnas,cont++);

                copiarMatriz(matrizAux,matrizCla,filas,columnas);
                gClasico(matrizCla,matrizAux,filas,columnas);

                copiarMatriz(matrizAux,matrizHor,filas,columnas);
                gHorizontal(matrizHor,matrizAux,filas,columnas);

                copiarMatriz(matrizAux,matrizVer,filas,columnas);
                gVertical(matrizVer,matrizAux,filas,columnas);
                usleep(tiempo*1000);
            }
            free(cadena);
            free(aux);
            liberarMatriz(matrizCla,filas);
            liberarMatriz(matrizVer,filas);
            liberarMatriz(matrizHor,filas);
            liberarMatriz(matrizAux,filas);
        } else
            printf("No cumplio la validacion,formato incorrecto");
    }else
        printf("No se consiguio el archivo");


    return 0;
}