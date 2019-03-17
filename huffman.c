// Incluimos las librerias
#include <stdio.h>
#include <stdlib.h>

// Definicion de las estructuras
typedef struct defLista{
  char simbolo, codigo[100];
  int probabilidad, status, tipo;
  struct defLista* sig;
}TipoLista;
// Prototipos de funciones
void menu();
void creditos();
void agregar(TipoLista**);
void listar(TipoLista*);
void borrar(TipoLista**);
void modificarSimbolo(TipoLista*);
void guardarenArchivo(TipoLista*);
void leerdeArchivo(TipoLista**);
// Funcion principal
int main() {
  int opcion;
  TipoLista* Inicio = NULL;
  creditos();
  do {
    menu();
    scanf("%d", &opcion);
    switch (opcion) {
      case 1:
        agregar(&Inicio);
        break;
      case 2:
        listar(Inicio);
        break;
      case 3:
        borrar(&Inicio);
        break;
      case 4:
        modificarSimbolo(Inicio);
        break;
      case 5:
        guardarenArchivo(Inicio);
        break;
      case 6:
        leerdeArchivo(&Inicio);
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        printf("Saliendo del programa...\n");
        exit(0);
        break;
      default:
        printf("Ingresa una opcion valida!\n");
    }
    printf("Presiona enter para continuar...");
    __fpurge(stdin);
    getchar();
  } while(opcion != 10);
  return 0;
}

// Desarrollando las funciones
void menu(){
  system("clear");
  printf("\t\t\t Codificacion de Huffman\n");
  printf("\t1.- Introducir simbolo\n");
  printf("\t2.- Listar simbolos\n");
  printf("\t3.- Borrar simbolo\n");
  printf("\t4.- Modificar simbolo\n");
  printf("\t5.- Guardar simbolos en archivo\n");
  printf("\t6.- Leer simbolos de archivo\n");
  printf("\t7.- Generar códigos\n");
  printf("\t8.- Codificar mensaje\n");
  printf("\t9.- Decodificar mensaje\n");
  printf("\t10.- Salir\n");
  printf("\nDel anterior menu, selecciona la opcion deseada-> ");
}
void creditos(){
  system("clear");
  printf("\t\t\t Codificacion de Huffman\n");
  printf("Desarrollado por:\n\tCesar Mauricio Arellano Velasquez\n\tRaul Gonzalez Portillo\n\tAllan Jair Escamilla Hernandez\n\n");
  printf("Presione una tecla para continuar...");
  getchar();
  system("clear");
  printf("Objetivo: Codificar y decodificar mensajes usando la codificacion de Huffman.\n");
  printf("Presione una tecla para continuar...");
  getchar();
}
void agregar(TipoLista** Inicio){
  char caracter;
  int probabilidad;
  TipoLista* Nuevo = (TipoLista*)malloc(sizeof(TipoLista));
  TipoLista* temp;
  system("clear");
  printf("Ingresar un caracter: ");
  __fpurge(stdin);
  caracter = getchar();
  printf("Ingresar la probabilidad de aparicion: ");
  scanf("%d", &probabilidad);
  Nuevo->simbolo = caracter;
  Nuevo->probabilidad = probabilidad;
  Nuevo->status = 0;
  Nuevo->tipo = 0;
  Nuevo->sig = NULL;
  if(*Inicio == NULL){
    *Inicio = Nuevo;
  }else{
    temp = *Inicio;
    while(temp->sig != NULL){
      temp = temp->sig;
    }
    temp->sig = Nuevo;
  }
}
void listar(TipoLista* Inicio){
  system("clear");
  printf("\t\t\t Codificacion de Huffman\n");
  TipoLista* temp = Inicio;
  while (temp != NULL) {
    printf("\tSimbolo: %c. Probabilidad: %d.\n", temp->simbolo, temp->probabilidad);
    temp = temp->sig;
  }
  printf("\n");
}
void borrar(TipoLista** Inicio){
  system("clear");
  char simbolo;
  TipoLista* aux = *Inicio, *ant = NULL;
  printf("Ingresar el simbolo a borrar: ");
  __fpurge(stdin);
  simbolo = getchar();
  while ((aux != NULL) && (aux->simbolo != simbolo)) {
    ant = aux;
    aux = aux->sig;
  }
  if (aux!=NULL) {
    if (ant!=NULL) {
      ant->sig = aux->sig;
    }else{
      *Inicio = aux->sig;
    }
    free(aux);
  }
}
void modificarSimbolo(TipoLista* Inicio){
  system("clear");
  char simbolo;
  int flag = 0, probabilidad;
  TipoLista* temp = Inicio, *temp2;
  printf("Ingresar el simbolo a modificar: ");
  __fpurge(stdin);
  simbolo = getchar();
  while(temp != NULL && flag == 0){
    if(temp->simbolo == simbolo){
      flag = 1;
      temp2 = temp;
    }
    temp = temp->sig;
  }
  if(flag == 0)
    printf("No se puede modificar el simbolo introdicido, ya que no se encuentra en la lista\n");
  else{
    printf("Ingresa la nueva probabilidad de aparicion del simbolo: ");
    scanf("%d", &probabilidad);
    temp2->probabilidad = probabilidad;
    printf("Se ha modificado correctamente\n");
  }
}
void guardarenArchivo(TipoLista* Inicio){
  system("clear");
  TipoLista* temp = Inicio;
  FILE* Archivo;
  char nombreArchivo[200];
  if(temp == NULL)
    printf("La lista de simbolos se encuentra vacia, no puedes guardarla en un archivo\n");
  else{
    printf("Ingresar el nombre del archivo donde se desea guardar: ");
    __fpurge(stdin);
    gets(nombreArchivo);
    Archivo = fopen(nombreArchivo, "wt");
    while (temp != NULL) {
      fprintf(Archivo, "%d/%c\n", temp->probabilidad, temp->simbolo);
      temp = temp->sig;
    }
    printf("Se ha guardado con exito\n");
    fclose(Archivo);
  }
}
void leerdeArchivo(TipoLista** Inicio){
  system("clear");
  FILE* Archivo;
  TipoLista* temp = *Inicio, *temp2;
  char nombre[200], simbolo;
  int probabilidad;
  printf("Ingresar nombre del archivo a ser cargado: ");
  __fpurge(stdin);
  gets(nombre);
  Archivo = fopen(nombre, "rb");
  if (Archivo == NULL) {
    printf("Ha ocurrdo un error al abrir el archivo\n");
  }else{
    while(*Inicio != NULL){
      temp = (*Inicio)->sig;
      free(*Inicio);
      *Inicio = temp;
    }
    while (fscanf(Archivo, "%d/%c\n", &probabilidad, &simbolo) == 2) {
      temp = (TipoLista*)malloc(sizeof(TipoLista));
      temp->probabilidad = probabilidad;
      temp->simbolo = simbolo;
      temp->status = 0;
      temp->tipo = 0;
      temp->sig = NULL;
      if(*Inicio == NULL){
        *Inicio = temp;
      }else{
        temp2 = *Inicio;
        while(temp2->sig != NULL)
          temp2 = temp2->sig;
        temp2->sig = temp;
      }
    }
    fclose(Archivo);
    printf("Se ha leido correctamente la lista del archivo\n");
  }
}
