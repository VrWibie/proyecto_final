//Rama gil
#include<stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <locale.h>

// estructura: variables del producto
typedef struct {
    char nombre[50];
    char cantidad[20];
    float precio;
} Producto;

//función para agregar productos
void agregar(Producto *productos, int *numProductos) {
    printf("Introduce el nombre: ");
    scanf("%s", productos[*numProductos].nombre);
    printf("Introduce la cantidad con unidades: ");
    scanf("%s", productos[*numProductos].cantidad);
    printf("Digite el precio del producto (solo los números): ");
    scanf("%f", &productos[*numProductos].precio);

    //Donde: numProductos sirve para iterar y posicionarse en el producto que se requiere
    // Y dentro de los productos solo se pueden agregar 50


//Apertura del Archivo, y vaciado de la información recopilada
FILE *file = fopen("DESPENSA.txt", "a"); //El modo a para abirir o crear para escritura
    fprintf(file, "%s %s %f\n", productos[*numProductos].nombre, productos[*numProductos].cantidad, productos[*numProductos].precio);
    fclose(file);

     (*numProductos)++;

}
// lista de los productos agregados a la DESPENSA
void listar(Producto *productos, int numProductos) {
    for(int i = 0; i < numProductos; i++) {
        printf("Nombre: %s, Cantidad: %s, Precio: %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
}

//funcion para modificar un producto
void modificar(Producto *productos, int numProductos) {
    char nombre[50];
    printf("Introduce el nombre del producto a modificar: ");
    scanf("%s", nombre);
//    FILE *file = fopen("DESPENSA.txt", "r");
    FILE *nuevo = fopen("nuevoDESPENSA.txt", "w"); // El modo w abre o crea esctritura
    //while(fscanf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad)!=EOF) {
    for(int i = 0; i < numProductos; i++) {   //el bucle for recorre todos los productos                   
          if(strcmp(productos[i].nombre, nombre) == 0) { // mientras que for recorre, if esta a la espera de realizar el argumento 

                                                      //La función strcmp() compara dos cadenas de caracteres y devuelve un valor entero. 
                                                      // Si las cadenas son  iguales, la función devuelve el valor 0. Silas cadenas son diferentes, 
                                                      // la función devuelve un valor negativo si la primera cadena es menor que la segunda cadena, 
                                                      // o un valor positivo si la primera cadena es mayor que la segunda cadena.
                                        //En este caso necesitamos que las cadenas sean iguales
              printf("Introduce el nuevo nombre: ");
              scanf("%s", productos[i].nombre);
              printf("Introduce la nueva cantidad: ");
              scanf("%s", productos[i].cantidad);
              printf("Digite el precio del producto (solo los números): ");
              scanf("%f", &productos[i].precio);
              //este fprintf esta reescribiendo la nueva modificación en el lugar del producto cambiado
              fprintf(nuevo, "%s %s %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
//              (*numPersonas)++;
              //return;
         }
         /*en el caso de que la cadena no sea la misma se vuelven a vaciar los mismos datos de los prodcutos 
         en el nuevo archivos, sin hacer cambios*/
         else
             fprintf(nuevo, "%s %s %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
//             (*numPersonas)++;
    }
//    fclose(file);//se cierra el archivo
    fclose(nuevo);
    remove("DESPENSA.txt"); //Se borra el archivo anterior
    rename("nuevoDESPENSA.txt","DESPENSA.txt"); // al archivo nuevo se le vuelve a asignar el nombre del anterior 
}

//funcion para borrar productos
void borrar(Producto *productos, int *numProductos) { //tengo 4 productos
    char nombre[50];
    printf("Introduce el nombre del produto a borrar: "); 
    scanf("%s", nombre); //Manzana
    for(int i = 0; i < *numProductos; i++) { //el iterador da 4 vueltas 0,1,2,3
        if(strcmp(productos[i].nombre, nombre) == 0) { // si las cadenas son idénticas(Ejemplo en i=2 Manzana) hacer{}
            for(int j = i; j < *numProductos - 1; j++) { //j=2     numProductos=4-1=3 j va una vuelta en j=i=2
                productos[j] = productos[j + 1];  /*primer vuelta producto 2(manzana)= produto3(Platano)
                por lo que, ese producto será reemplazado por el prodcuto 3 que es platano, ahora
                 platano es el producto 2*/
            }
            (*numProductos)--; //entonces se reducira en 1 el numero de productos
               
            FILE *file = fopen("nuevoDESPENSA.txt", "w"); 
            for(int i = 0; i < *numProductos; i++) {
                fprintf(file, "%s %s %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            }
            fclose(file); // se cierra el archivo
            remove("DESPENSA.txt");
            rename("nuevoDESPENSA.txt","DESPENSA.txt"); // al archivo nuevo se le vuelve a asignar el nombre del anterior
               
            return;
        }
    }
    printf("No se encontró el producto.\n");
}
//Función para buscar algun producto
void buscar(Producto *productos, int numProductos) {
    char nombre[50];
    printf("Introduce el nombre de la persona a buscar: ");
    scanf("%s", nombre);
    for(int i = 0; i < numProductos; i++) {
        if(strcmp(productos[i].nombre, nombre) == 0) {
            printf("Nombre: %s, Cantidad: %s, Precio: %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            return;
        }
    }
    printf("No se encontró a la persona.\n");
}
//Función para guardar
void guardar(Producto *productos, int numProductos) {
    // FILE *file = fopen("DESPENSA.txt", "w");
    FILE *file = fopen("DESPENSA.txt", "a");/* se abre el archivo con modo 'a'para Abrir o 
    crea para escritura. Agrega después de cualquier contenido previo.*/
    if(file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    for(int i = 0; i < numProductos; i++) {
        fprintf(file, "%s %s %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
    
    fclose(file);
}
//Función para cargar
void cargar(Producto *productos, int *numProductos) {
    FILE *file = fopen("DESPENSA.txt", "r"); //Se abre la lectura del archivo con el modo 'r'
    if(file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    while(fscanf(file, "%s %s %f", productos[*numProductos].nombre, productos[*numProductos].cantidad, &productos[*numProductos].precio) == 3) { 
        //si fscanf lee los 3 campos: nombre, cantidad y precio numProductos incrementa de 1 en 1 
        (*numProductos)++;
    }
    fclose(file);
}
//función principal int main
int main() {
    
    setlocale(LC_ALL,"");
    
    Producto productos[50];//cantidad posible de productos en la Despensa
    int numProductos = 0;
    int opcion;
    
    cargar(productos, &numProductos);
    
    do {
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Modificar producto\n");
        printf("4. Borrar producto\n");
        printf("5. Buscar producto\n");
//        printf("6. Guardar personas\n"); //realizado por las funciones
//        printf("7. Cargar personas\n");   //realizado por las funciones
        printf("6. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                system("cls");
                agregar(productos, &numProductos);
                break;
            case 2:
                system("cls");
                listar(productos, numProductos);
                break;
            case 3:
                system("cls");
                modificar(productos, numProductos);
                break;
            case 4:
                system("cls");
                borrar(productos, &numProductos);
                break;
            case 5:
                system("cls");
                buscar(productos, numProductos);
                break;
//            case 6:
                guardar(productos, numProductos); //el usaurio saldra y se guardaran sus productos en el archivo
                break;
//            case 7:
//               cargar(productos, &numProductos);
//                break;
        }
    } while(opcion != 6);

    return 0;
}
