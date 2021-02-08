// Cadena de prueba: 648F#fwe#DD1#5423F.#0.1#F#fdsf#1.#6.0#
#include <stdio.h>
#include <stdlib.h> //Malloc
#include <ctype.h>  //isdigit
#include <string.h> //memset

char* cadena = NULL;                    // CADENA PARA ALMACENAR LA PALABRA

void encontrarPalabras(char *cadena);   // RECONOCER LAS PALABRAS DEL LENGUAJE
char* leerCadena(void);                 // ALMACENAR LA CADENA INGRESADA POR TECLADO
int obtenerCaracter(char);

int TT[6][4] = {   {1,1,3,4},           // AFD MINIMO
                   {2,2,5,4},
                   {2,2,3,4},
                   {3,3,3,3},
                   {3,3,3,3},
                   {4,3,3,3},   };

int main(){

    char respuesta;

    do{
    	printf("Ingrese la cadena: ");
    	cadena = leerCadena();
        printf("Las palabras del lenguaje [0-9]\\.[01]?|[0-9]*F en la secuencia de texto ingresada son: \n");
        encontrarPalabras(cadena);
        printf("Desea ingresar otra cadena (S/N)\n");
        respuesta = getchar();
        fflush(stdin);
    }while(respuesta == 'S');

    free(cadena);

    return 0;
}


char* leerCadena(void){
	char caracter;
	int i;
	char* auxiliar = NULL;
	for(i = 0;(caracter = getchar()) != '\n';i++){
		auxiliar = (char*)realloc(auxiliar,(i+2)*sizeof(char));
		auxiliar[i] = caracter;
		auxiliar[i+1] = '\0';
	}
	if(auxiliar == NULL){
		auxiliar = (char*)malloc(sizeof(char));
		auxiliar[0] = '\0';
		}
    return auxiliar;
}

int obtenerCaracter(char caracter){

	switch(caracter){
		case '0':
		case '1': return 0;
		break;
		case '.': return 2;
		break;
		case 'F': return 3;
		break;
		default: if(isdigit(caracter))  // DEL 2 AL 9
					return 1;
				else
					return 4;           // CUALQUIER OTRO CARACTER
		break;
		};

}

void encontrarPalabras(char *cadena){
    int i = 0, cantDePalabrasEncontradas = 0, j=0;
	int E_actual, columna;
	char* cadenaAux = (char*)malloc(100*sizeof(char));
	while(cadena[i] != '\0'){
		E_actual = 0;
			while(cadena[i] != '#'){
				columna = obtenerCaracter(cadena[i]);
				E_actual = TT[E_actual][columna];
				cadenaAux[j++] = cadena[i++];
			}
			i++;
			if(E_actual == 4 || E_actual == 5){
                cadenaAux[j] = '\0';
                printf("%i) %s\n", ++cantDePalabrasEncontradas, cadenaAux);
			}
			memset(cadenaAux, '\0', 100*sizeof(char));
			j = 0;
}
    if(cantDePalabrasEncontradas == 0)
        printf("No se encontro ninguna palabra\n");

    free(cadenaAux);
}
