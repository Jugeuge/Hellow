#include <iostream>
#include <iomanip>
#include <list>
#include <windows.h> // para Sleep
#include <time.h> // para random
#include <stdlib.h>
#include <math.h> // multiplicación

 
/* Definiendo la estructura etiqueta de nodo. Sus campos incluyen
 * el número de nodo, el coste total del nodo, y su precedente. */
struct label {
   int nro;	/* numero del nodo */
   int prev;	/* nodo precedente (-1 para el nodo inicial )*/
   float peso;	/* peso o coste total de la trayectoria que
				 * conduce al nodo, i.e., el coste total desde
				 * el nodo inicial hasta el actual. Un valor
				 * de -1 denota el infinito */
   int marca;	/* si el nodo ha sido marcado o no */
};
typedef struct label label_t;


float velocidad;
 
using namespace std;
 
void dijkstra( int, int **, int, int );

float random () // random de 0 a 1
{
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	return r;
}
 
int main () {
 
   /* cantidad total de nodos */
   int numNodos = 9;
 
   /* Definiendo la matriz de adyacencia */
   int i, j, **A;
 
   if ( ( A = new int*[numNodos] ) == NULL ) return 1;
   for ( i = 0; i < numNodos; i++ )
      if ( ( A[i] = new int[numNodos] ) == NULL ) return 1;
 
   for ( i = 0; i < numNodos; i++ )
      for ( j = 0; j < numNodos; j++ )
         A[i][j] = 0;
 
   /* por simplicidad, completamos solo los pares de nodos conectados */
   A[0][1] = 16;
   A[0][2] = 10;
 
   A[1][0] = 16;
   A[1][2] = 2;
   A[1][3] = 4;
 
   A[2][0] = 10;
   A[2][1] = 2;
   A[2][3] = 4;
   A[2][4] = 10;
 
   A[3][1] = 4;
   A[3][2] = 4;
   A[3][4] = 15;
   A[3][5] = 16;
 
   A[4][2] = 10;
   A[4][3] = 15;
   A[4][5] = 3;
 
   A[5][3] = 16;
   A[5][4] = 3;
   A[5][6] = 8;
   A[5][7] = 16;
 
   A[6][5] = 8;
   A[6][7] = 7;
   A[6][8] = 20;
 
   A[7][5] = 16;
   A[7][6] = 7;
   A[7][8] = 25;
   
   A[8][6] = 20;
   A[8][7] = 25;
   
   
   
 
   /* Imprimir la matriz de adyacencia */
   cout << endl;
   cout << "En la siguiente matriz, se muestran las distintas distancias que vinculan un punto con otro en el recorrido:" << endl << endl;
   Sleep (1000); // genera un tiempo de espera para mostarar el siguiente paso
   for ( i = 0; i < numNodos; i++ ) {
      for ( j = 0; j < numNodos; j++ )
         cout << setw(2) << A[i][j] << "  ";
      cout << endl;
      }
   cout << endl << endl << endl;
   
   // se solicita ingresar el dato de velocidad del móvil
   Sleep (1000);
   cout << "Ingrese la velocidad expresada en kilometros por hora en la que el movil seleccionado puede realizar el recorrido:" << endl << endl;
   cout << "Velocidad del movil: ";
   cin >> velocidad;
   Sleep (1000);
   cout << endl; 
   cout << "Gracias!" << endl;
   Sleep (500);
   cout << endl << "A continuacion, en funcion de la velocidad del movil, la distancia entre los puntos del recorrido y la disponibilidad de cada tramo," << endl <<
   "calcularemos el recorrido mas conveniente" << endl << endl;
   
   Sleep (4000);
      
   cout << random () << endl;
   cout << random () << endl;
   cout << random () << endl;
   
   Sleep (4000);
 
   /* calcular dijkstra a partir del nodo 0, hasta el nodo 8 */
   dijkstra( numNodos, A, 0, numNodos-1 );
 
   /* liberar memoria */
   delete [] A;
   for ( i = 0; i < numNodos; i++ )
      delete A[i];
 
   return 0;
}


 
/* Calcula el coste minimo de alcanzar un nodo final 'b'
 * grafo no dirigido con N nodos, a partir del nodo inicial 'a',
 * dada su matriz de adyacencia A */
void dijkstra( int N, int **A, int a, int b ) {
 
   label_t *Labels; // array de nodos
   int i, i0, j, peso;
   int *ruta;		/* array de nodos de la ruta mas rapida */
 
   /* Crea dinamicamente el arreglo de etiquetas de nodo */
   if ( ( Labels = new label_t[N] ) == NULL ) return;
 
   /* chequea que el nodo inicial 'a' esté entre 0 y N - 1 */
   if ( a < 0 || a > N - 1 ) return;
   /* chequea que el nodo final 'b' esté entre 0 y N - 1 */
   if ( b < 0 || b > N - 1 ) return;
 
   /* inicializar las etiquetas de nodo */
   for ( i = 0; i < N; i++ ) {
      Labels[i].nro = i;
      if ( i != a ) {
         Labels[i].prev = -1;	/* a'un no se ha definido predecesor */
         Labels[i].peso = -1;	/* infinito */
         Labels[i].marca = 0;
      }
      else {
         Labels[i].prev = -1;	/* a'un no se ha definido predecesor */
         Labels[i].peso = 0;		/* coste del nodo inicial a s'i mismo es cero */
         Labels[i].marca = 0;
      }
   }
 
   /* continuamos este ciclo mientras existan nodos no marcados */
   while ( 1 ) {
      /* busca entre todos los nodos no marcados el de menor peso, descartando los
       * de peso infinito (-1) */
      peso = -1;
      i0 = -1;
      for ( i = 0; i < N; i++ ) {
         if ( Labels[i].marca == 0 && Labels[i].peso >= 0 )
            if ( peso == -1 ) {
               peso = (Labels[i].peso * (velocidad * random())); //este es el primer intento de modificar el peso con la velocidad y el random. No me estaría funcionando el operador!
               i0 = i;
            }
            else if ( Labels[i].peso <= peso ) {
               peso = Labels[i].peso;
               i0 = i;
            }
      }
      if ( i0 == -1 ) {	/* termina si no encuentra */
         cout << "Ya no quedan nodos por analizar." << endl;
         break;
      }
 
      cout << "*** Analizando nodo " << i0 << " ***" << endl;
 
      /* actualiza el peso de todos los sucesores (si los hay) del nodo
       * encontrado y luego se~nala dicho nodo como marcado */
      for ( i = 0; i < N; i++ ) {
         if ( A[i0][i] > 0 ) {
            /* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
             * es menor al coste del nodo i (o si el coste del nodo i es infinito),
             * debemos actualizar */
            if ( Labels[i].peso == -1 || Labels[i0].peso + A[i0][i] < Labels[i].peso ) {
               if ( Labels[i0].peso + A[i0][i] < Labels[i].peso )
                  cout << "   [ mejorando coste de nodo " << i << " ]" << endl;
               Labels[i].peso = Labels[i0].peso + A[i0][i];
               Labels[i].prev = i0;
               cout << "   coste de nodo " << i << " desde nodo " << i0 << ": " << Labels[i].peso << endl;
            }
         }
      }
      Labels[i0].marca = 1;
      cout << "   [ nodo " << i0 << " marcado ]" << endl;
 
      /* para verificar, imprime los costes calculados hasta el momento */
      for ( i = 0; i < N; i++ ) {
         cout << i << ": [";
         if ( Labels[i].peso == -1 ) cout << "Inf";
         else cout << Labels[i].peso;
         cout << ", " << Labels[i].prev ;
         if ( Labels[i].marca == 1 ) cout <<  ", x]" << endl;
         else cout << "]" << endl;
      }
      cout << endl;
 
      /* pausa (opcional) */
      cout << "presione ENTER para continuar ...";
      cin.get();
   }
 
   /* Ruta desde el nodo 'a' hasta el nodo 'b' */
   int longitud = 2;
   i = b;
   while ( ( i = Labels[i].prev ) != a ) longitud++;	/* primero estimamos la longitud de la ruta */
   if ( ( ruta = new int[longitud] ) == NULL ) return;
 
   ruta[longitud - 1] = b;		/* luego rellenamos */
   i = b;
   j = 0;
   for ( j = 1; j < longitud; j++ ) {
      i = Labels[i].prev;
      ruta[longitud - j - 1] = i;
   }
 
   cout << "================================================================" << endl;
   cout << endl << "Ruta mas economica entre nodo " << a << " y nodo " << b << ":" << endl << endl;
   for ( i = 0; i < longitud; i++ ) {
      cout << ruta[i];
      if ( i < longitud - 1 ) cout << " - ";
   }
   cout << endl << endl << "Costo total: " << Labels[b].peso << endl << endl;
 
   delete ruta;
   delete [] Labels;
}
