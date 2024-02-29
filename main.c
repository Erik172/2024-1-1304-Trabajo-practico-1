#include <stdio.h>
#include <stdlib.h>

//NOMBRE: Erik Alejandro Garcia Duarte
//CODIGO: 202225328
//CORREO: ea.garciad1@uniandes.edu.co

#define NOMBRES_SIZE 50 // Erik
#define APELLIDOS_SIZE 43 // Garcia Duarte
#define CEDULA_SIZE 13 // 1016592716
#define CODIGO_SIZE 4 // 202225328
#define EDAD_SIZE 1 // 20
#define CIENANACIMIENTO_SIZE 2 
#define FILE_SIZE ( NOMBRES_SIZE + APELLIDOS_SIZE + CEDULA_SIZE + CODIGO_SIZE + EDAD_SIZE + CIENANACIMIENTO_SIZE )

//TO DO: Declare el tipo y tama�o adecuados para que las variables puedan contener el correspondiente valor
//del archivo de entrada
// NO MODIFIQUE NINGUNA OTRA COSA EN EL PROGRAMA
// Estructura para manejar los datos de entrada.
struct Datos {
   unsigned int codigo;
   char nombres[NOMBRES_SIZE];
   char apellidos[APELLIDOS_SIZE];
   char cedula[CEDULA_SIZE];
   unsigned int edad;
   short cienANacimiento;
} datos;

unsigned int getFileSize ( FILE * );
unsigned int loadData ( struct Datos *, char * );
unsigned int getNumber ( FILE *, char *, unsigned int );
void printChrs ( char *, unsigned int );

int main( int argc, char *argv[] )
{

   if ( argc != 2 ){
      printf( "*** ATENCION! Uso del comando:\n\tprograma archivo-de-datos\n" );
      return 1;
   }

   if ( loadData( &datos, argv[1] ) != FILE_SIZE ) return 1;

   printf( "Codigo:%u\n", datos.codigo );
   printf( "Nombres:" );
   printChrs( datos.nombres, sizeof( datos.nombres ) );
   printf( "\n" );
   printf( "Apellidos:" );
   printChrs( datos.apellidos, sizeof( datos.apellidos ) );
   printf( "\n" );
   printf( "Cedula:" );
   printChrs( datos.cedula, sizeof( datos.cedula ) );
   printf( "\n" );
   printf( "Edad:%u\n", datos.edad );
   printf( "Diferencia a 100:%d\n", datos.cienANacimiento);

   return 0;
} // main

/**
 * Calcula la longitud en bytes de un archivo.
 * Pre   El archivo esta abierto.
 * Parametros  f Apuntador al descriptor del archivo.
 * Retorna  la longitud en bytes del archivo apuntado por f.
 */
unsigned int getFileSize ( FILE * f ){

   unsigned int longArchivo;

   if ( fseek( f, 0, SEEK_END ) || ( longArchivo = ftell( f ) ) < 0 || fseek( f, 0, SEEK_SET ) ) {
      longArchivo = 0;
   }

  return longArchivo;
} // getFileSize

/**
 * Lee del archivo un n�mero binario de n bytes en la variable apuntada por p.
 * El n�mero se supone en formato big endian y lo convierte a little endian.
 */
unsigned int getNumber ( FILE * f, char * p, unsigned int n ){

   int i;

   p = p + n - 1;
   for ( i = 0; i < n && ( fread( p-i, sizeof( char ), 1, f ) == sizeof( char ) ); i++ );

   return i;
} // getNumber

/**
 * Inicializa una estructura con los datos del archivo.
 * Abre el archivo de datos, lo carga en memoria y los guarda en una estructura de datos.
 */
unsigned int loadData ( struct Datos * datosP, char * nombreArchivo ){

   FILE * f = NULL;
   unsigned int longFisica = 0;
   unsigned int nBytes;

   if ( !( f = fopen( nombreArchivo, "rb" ) ) ) {
      printf( "*** ATENCION! No se logro abrir el archivo %s\n", nombreArchivo );
   }
   else if ( getFileSize( f ) != FILE_SIZE ){
         printf( "*** ATENCION! Tamanio del archivo %s no concuerda\n", nombreArchivo );
   }
   else {
	  nBytes = CODIGO_SIZE;
      if ( getNumber( f, (char *)(&datosP->codigo), sizeof( datosP->codigo ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer completo el codigo del archivo %s\n", nombreArchivo );
         return longFisica;
      }
      longFisica += nBytes;
      nBytes = NOMBRES_SIZE;
      if ( fread( datosP->nombres, sizeof( char ), sizeof( datosP->nombres ), f ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer completos los nombres del archivo %s\n", nombreArchivo );
         return longFisica;
      }
      longFisica += nBytes;
      nBytes = APELLIDOS_SIZE;
      if ( fread( datosP->apellidos, sizeof( char ), sizeof( datosP->apellidos ), f ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer completos los apellidos del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
      nBytes = CEDULA_SIZE;
      if ( fread( datosP->cedula, sizeof( char ), sizeof( datosP->cedula ), f ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer completa la cedula del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
      nBytes = EDAD_SIZE;
      if ( getNumber( f, (char *)(&datosP->edad), sizeof( datosP->edad ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer la edad del archivo %s\n", nombreArchivo );
         return longFisica;
      }
	  longFisica += nBytes;
      nBytes = CIENANACIMIENTO_SIZE;
      if ( getNumber( f, (char *)(&datosP->cienANacimiento), sizeof( datosP->cienANacimiento ) ) != nBytes ) {
         printf( "*** ATENCION! No se pudo leer completa la diferencia a 100 %s\n", nombreArchivo );
         return longFisica;
      }
      longFisica += nBytes;
   }

   fclose( f );

   return longFisica;
} // loadData

/**
 * Imprime l caracteres a partir del caracter apuntado por p.
 */
void printChrs ( char * p, unsigned int n ){

   int i;

   for ( i = 0; i < n; i++ ){
      printf( "%c", p[i] );
   }

} // printChrs
