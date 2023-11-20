#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct
{
    char nombre[50];
    float precio;
    int cantidad;
} Producto;

void agregar(Producto *productos, int *numProducto)
{
    printf("Introduce el nombre del producto: ");
    scanf("%s", productos[*numProducto].nombre);
    printf("Introduce el precio: ");
    scanf("%f", &productos[*numProducto].precio);
    printf("Selecciona la nacionalidad (Mexicana, Estadounidense, Española, Chilena): ");
    scanf("%i", productos[*numProducto].cantidad);

    // ??????????????????????????
    FILE *file = fopen("UNO.txt", "a");
    fprintf(file, "%s %d %s\n", productos[*numProducto].nombre, productos[*numProducto].precio, productos[*numProducto].cantidad);
    fclose(file);
    // ??????????????????????????

    (*numProducto)++;
}

void listar(Producto *productos, int numProducto)
{
    for (int i = 0; i < numProducto; i++)
    {
        printf("Nombre: %s, Precio: %f, Cantidad: %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
    }
}

// //////////////////////////////////////////////////////////////////////////////
void modificar(Producto *productos, int numProducto)
{
    char nombre[50];
    printf("Introduce el nombre del producto a modificar: ");
    scanf("%s", nombre);
    //    FILE *file = fopen("UNO.txt", "r");
    FILE *nuevo = fopen("nuevoUNO.txt", "w");
    // while(fscanf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad)!=EOF) {
    for (int i = 0; i < numProducto; i++)
    {
        if (strcmp(productos[i].nombre, nombre) == 0)
        {
            // La función strcmp() compara dos cadenas de caracteres y devuelve un valor entero.
            //  Si las cadenas son iguales, la función devuelve el valor 0. Si las cadenas son diferentes,
            //  la función devuelve un valor negativo si la primera cadena es menor que la segunda cadena,
            //  o un valor positivo si la primera cadena es mayor que la segunda cadena.

            printf("Introduce el nuevo nombre del producto: ");
            scanf("%s", productos[i].nombre);
            printf("Introduce la nueva edad: ");
            scanf("%f", &productos[i].precio);
            printf("Selecciona la nueva nacionalidad (Mexicana, Estadounidense, Española, Chilena): ");
            scanf("%d", productos[i].cantidad);
            fprintf(nuevo, "%s %f %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
            //              (*numPersonas)++;
            // return;
        }
        else
            fprintf(nuevo, "%s %f %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
        //             (*numPersonas)++;
    }
    //    fclose(file);
    fclose(nuevo);
    remove("UNO.txt");
    rename("nuevoUNO.txt", "UNO.txt");
}
// //////////////////////////////////////////////////////////////////////////////

void borrar(Producto *productos, int *numProducto)
{
    char nombre[50];
    printf("Introduce el nombre del producto a borrar: ");
    scanf("%s", nombre);
    for (int i = 0; i < *numProducto; i++)
    {
        if (strcmp(productos[i].nombre, nombre) == 0)
        {
            for (int j = i; j < *numProducto - 1; j++)
            {
                productos[j] = productos[j + 1];
            }
            (*numProducto)--;
            // ??????????????????????????
            FILE *file = fopen("nuevoUNO.txt", "w");
            for (int i = 0; i < *numProducto; i++)
            {
                fprintf(file, "%s %f %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
            }
            fclose(file);
            remove("UNO.txt");
            rename("nuevoUNO.txt", "UNO.txt");
            // ??????????????????????????
            return;
        }
    }
    printf("No se encontró al producto.\n");
}

void buscar(Producto *productos, int numProducto)
{
    char nombre[50];
    printf("Introduce el nombre del producto a buscar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProducto; i++)
    {
        if (strcmp(productos[i].nombre, nombre) == 0)
        {
            printf("Nombre: %s, Edad: %f, Nacionalidad: %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
            return;
        }
    }
    printf("No se encontró al producto.\n");
}

void guardar(Producto *productos, int numProducto)
{
    // FILE *file = fopen("UNO.txt", "w");
    FILE *file = fopen("UNO.txt", "a");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < numProducto; i++)
    {
        fprintf(file, "%s %f %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
    }

    fclose(file);
}

void cargar(Producto *productos, int *numProducto)
{
    FILE *file = fopen("UNO.txt", "r");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    while (fscanf(file, "%s %d %s", productos[*numProducto].nombre, &productos[*numProducto].precio, productos[*numProducto].cantidad) == 3)
    {
        (*numProducto)++;
    }
    fclose(file);
}

int main()
{

    setlocale(LC_ALL, "");

    Producto productos[50];
    int numProducto = 0;
    int opcion;
    // ?????????????????????????????????
    cargar(productos, &numProducto);
    // ?????????????????????????????????

    do
    {
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Modificar producto\n");
        printf("4. Borrar producto\n");
        printf("5. Buscar producto\n");
        //        printf("6. Guardar productos\n");
        //        printf("7. Cargar productos\n");
        printf("6. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            system("cls");
            agregar(productos, &numProducto);
            break;
        case 2:
            system("cls");
            listar(productos, numProducto);
            break;
        case 3:
            system("cls");
            modificar(productos, numProducto);
            break;
        case 4:
            system("cls");
            borrar(productos, &numProducto);
            break;
        case 5:
            system("cls");
            buscar(productos, numProducto);
            break;
            //            case 6:
            guardar(productos, numProducto);
            break;
            //            case 7:
            //               cargar(productos, &numProducto);
            //                break;
        }
    } while (opcion != 6);

    return 0;
}