//Rama gil
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nombre[50];
    int edad;
    char nacionalidad[50];
} Persona;

void agregar(Persona *personas, int *numPersonas) {
    printf("Introduce el nombre: ");
    scanf("%s", personas[*numPersonas].nombre);
    printf("Introduce la edad: ");
    scanf("%d", &personas[*numPersonas].edad);
    printf("Selecciona la nacionalidad (Mexicana, Estadounidense, Española, Chilena): ");
    scanf("%s", personas[*numPersonas].nacionalidad);
    
    // ?????????????????????????? 
    FILE *file = fopen("UNO.txt", "a");
    fprintf(file, "%s %d %s\n", personas[*numPersonas].nombre, personas[*numPersonas].edad, personas[*numPersonas].nacionalidad);
    fclose(file);
    // ??????????????????????????      
          
    (*numPersonas)++;
}

void listar(Persona *personas, int numPersonas) {
    for(int i = 0; i < numPersonas; i++) {
        printf("Nombre: %s, Edad: %d, Nacionalidad: %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
    }
}

// //////////////////////////////////////////////////////////////////////////////
void modificar(Persona *personas, int numPersonas) {
    char nombre[50];
    printf("Introduce el nombre de la persona a modificar: ");
    scanf("%s", nombre);
//    FILE *file = fopen("UNO.txt", "r");
    FILE *nuevo = fopen("nuevoUNO.txt", "w");
    //while(fscanf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad)!=EOF) {
    for(int i = 0; i < numPersonas; i++) {                     
          if(strcmp(personas[i].nombre, nombre) == 0) { 
                                                      //La función strcmp() compara dos cadenas de caracteres y devuelve un valor entero. 
                                                      // Si las cadenas son iguales, la función devuelve el valor 0. Si las cadenas son diferentes, 
                                                      // la función devuelve un valor negativo si la primera cadena es menor que la segunda cadena, 
                                                      // o un valor positivo si la primera cadena es mayor que la segunda cadena.
                                        
              printf("Introduce el nuevo nombre: ");
              scanf("%s", personas[i].nombre);
              printf("Introduce la nueva edad: ");
              scanf("%d", &personas[i].edad);
              printf("Selecciona la nueva nacionalidad (Mexicana, Estadounidense, Española, Chilena): ");
              scanf("%s", personas[i].nacionalidad);
              fprintf(nuevo, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
//              (*numPersonas)++;
              //return;
         }
         else
             fprintf(nuevo, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
//             (*numPersonas)++;
    }
//    fclose(file);
    fclose(nuevo);
    remove("UNO.txt");
    rename("nuevoUNO.txt","UNO.txt");
}
// //////////////////////////////////////////////////////////////////////////////


void borrar(Persona *personas, int *numPersonas) {
    char nombre[50];
    printf("Introduce el nombre de la persona a borrar: ");
    scanf("%s", nombre);
    for(int i = 0; i < *numPersonas; i++) {
        if(strcmp(personas[i].nombre, nombre) == 0) {
            for(int j = i; j < *numPersonas - 1; j++) {
                personas[j] = personas[j + 1];
            }
            (*numPersonas)--;
            // ??????????????????????????      
            FILE *file = fopen("nuevoUNO.txt", "w"); 
            for(int i = 0; i < *numPersonas; i++) {
                fprintf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
            }
            fclose(file);
            remove("UNO.txt");
            rename("nuevoUNO.txt","UNO.txt");  
            // ??????????????????????????        
            return;
        }
    }
    printf("No se encontró a la persona.\n");
}

void buscar(Persona *personas, int numPersonas) {
    char nombre[50];
    printf("Introduce el nombre de la persona a buscar: ");
    scanf("%s", nombre);
    for(int i = 0; i < numPersonas; i++) {
        if(strcmp(personas[i].nombre, nombre) == 0) {
            printf("Nombre: %s, Edad: %d, Nacionalidad: %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
            return;
        }
    }
    printf("No se encontró a la persona.\n");
}

void guardar(Persona *personas, int numPersonas) {
    // FILE *file = fopen("UNO.txt", "w");
    FILE *file = fopen("UNO.txt", "a");
    if(file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    for(int i = 0; i < numPersonas; i++) {
        fprintf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad);
    }
    
    fclose(file);
}

void cargar(Persona *personas, int *numPersonas) {
    FILE *file = fopen("UNO.txt", "r");
    if(file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    while(fscanf(file, "%s %d %s", personas[*numPersonas].nombre, &personas[*numPersonas].edad, personas[*numPersonas].nacionalidad) == 3) {
        (*numPersonas)++;
    }
    fclose(file);
}

int main() {
    
    setlocale(LC_ALL,"");
    
    Persona personas[50];
    int numPersonas = 0;
    int opcion;
    // ?????????????????????????????????
    cargar(personas, &numPersonas);
    // ?????????????????????????????????
    
    do {
        printf("1. Agregar persona\n");
        printf("2. Listar personas\n");
        printf("3. Modificar persona\n");
        printf("4. Borrar persona\n");
        printf("5. Buscar persona\n");
//        printf("6. Guardar personas\n");
//        printf("7. Cargar personas\n");
        printf("6. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                system("cls");
                agregar(personas, &numPersonas);
                break;
            case 2:
                system("cls");
                listar(personas, numPersonas);
                break;
            case 3:
                system("cls");
                modificar(personas, numPersonas);
                break;
            case 4:
                system("cls");
                borrar(personas, &numPersonas);
                break;
            case 5:
                system("cls");
                buscar(personas, numPersonas);
                break;
//            case 6:
                guardar(personas, numPersonas);
                break;
//            case 7:
//               cargar(personas, &numPersonas);
//                break;
        }
    } while(opcion != 6);

    return 0;
}