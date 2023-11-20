#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// estructura: variables del producto
typedef struct
{
    char nombre[50];
    char cantidad[20];
    float precio;
} Producto;

// funcion para agregar productos
void agregar(Producto *productos, int *numProductos)
{
    printf("Introduce el nombre: ");
    scanf("%s", productos[*numProductos].nombre);
    printf("Introduce la cantidad con unidades: ");
    scanf("%s", productos[*numProductos].cantidad);
    printf("Digite el precio del producto (solo los numeros): ");
    scanf("%f", &productos[*numProductos].precio);

    // Donde: numProductos sirve para iterar y posicionarse en el producto que se requiere
    //  Y dentro de los productos solo se pueden agregar 50

    // Apertura del Archivo, y vaciado de la informacion recopilada
    FILE *file = fopen("DESPENSA.txt", "a"); // El modo a para abirir o crear para escritura
    fprintf(file, "%s %s %.2f\n", productos[*numProductos].nombre, productos[*numProductos].cantidad, productos[*numProductos].precio);
    fclose(file);

    (*numProductos)++;
}
// lista de los productos agregados a la DESPENSA
void listar(Producto *productos, int numProductos)
{
    for (int i = 0; i < numProductos; i++)
    {
        printf("Nombre: %s, Cantidad: %s, Precio: %f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
}

// funcion para modificar un producto
void modificar(Producto *productos, int numProductos)
{
    char nombre[50];
    printf("Introduce el nombre del producto a modificar: ");
    scanf("%s", nombre);
    //    FILE *file = fopen("DESPENSA.txt", "r");
    FILE *nuevo = fopen("nuevoDESPENSA.txt", "w"); // El modo w abre o crea esctritura
    // while(fscanf(file, "%s %d %s\n", personas[i].nombre, personas[i].edad, personas[i].nacionalidad)!=EOF) {
    for (int i = 0; i < numProductos; i++)
    { // el bucle for recorre todos los productos
        if (strcmp(productos[i].nombre, nombre) == 0)
        { // mientras que for recorre, if esta a la espera de realizar el argumento

            // La funcion strcmp() compara dos cadenas de caracteres y devuelve un valor entero.
            //  Si las cadenas son  iguales, la funcion devuelve el valor 0. Silas cadenas son diferentes,
            //  la funcion devuelve un valor negativo si la primera cadena es menor que la segunda cadena,
            //  o un valor positivo si la primera cadena es mayor que la segunda cadena.
            // En este caso necesitamos que las cadenas sean iguales
            printf("Introduce el nuevo nombre: ");
            scanf("%s", productos[i].nombre);
            printf("Introduce la nueva cantidad: ");
            scanf("%s", productos[i].cantidad);
            printf("Digite el precio del producto (solo los numeros): ");
            scanf("%f", &productos[i].precio);
            // este fprintf esta reescribiendo la nueva modificacion en el lugar del producto cambiado
            fprintf(nuevo, "%s %s %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            //              (*numPersonas)++;
            // return;
        }
        /*en el caso de que la cadena no sea la misma se vuelven a vaciar los mismos datos de los prodcutos
        en el nuevo archivos, sin hacer cambios*/
        else
            fprintf(nuevo, "%s %s %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
        //             (*numPersonas)++;
    }
    //    fclose(file);//se cierra el archivo
    fclose(nuevo);
    remove("DESPENSA.txt");                      // Se borra el archivo anterior
    rename("nuevoDESPENSA.txt", "DESPENSA.txt"); // al archivo nuevo se le vuelve a asignar el nombre del anterior
}

// funcion para borrar productos
void borrar(Producto *productos, int *numProductos)
{ // tengo 4 productos
    char nombre[50];
    printf("Introduce el nombre del produto a borrar: ");
    scanf("%s", nombre); // Manzana
    for (int i = 0; i < *numProductos; i++)
    { // el iterador da 4 vueltas 0,1,2,3
        if (strcmp(productos[i].nombre, nombre) == 0)
        { // si las cadenas son identicas(Ejemplo en i=2 Manzana) hacer{}
            for (int j = i; j < *numProductos - 1; j++)
            {                                    // j=2     numProductos=4-1=3 j va una vuelta en j=i=2
                productos[j] = productos[j + 1]; /*primer vuelta producto 2(manzana)= produto3(Platano)
               por lo que, ese producto sera reemplazado por el prodcuto 3 que es platano, ahora
                platano es el producto 2*/
            }
            (*numProductos)--; // entonces se reducira en 1 el numero de productos

            FILE *file = fopen("nuevoDESPENSA.txt", "w");
            for (int i = 0; i < *numProductos; i++)
            {
                fprintf(file, "%s %s %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            }
            fclose(file); // se cierra el archivo
            remove("DESPENSA.txt");
            rename("nuevoDESPENSA.txt", "DESPENSA.txt"); // al archivo nuevo se le vuelve a asignar el nombre del anterior

            return;
        }
    }
    printf("No se encontro el producto.\n");
}
// Funcion para buscar algun producto
void buscar(Producto *productos, int numProductos)
{
    char nombre[50];
    printf("Introduce el nombre de la persona a buscar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++)
    {
        if (strcmp(productos[i].nombre, nombre) == 0)
        {
            printf("Nombre: %s, Cantidad: %s, Precio: %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
            return;
        }
    }
    printf("No se encontro a la persona.\n");
}
// Funcion para guardar
void guardar(Producto *productos, int numProductos)
{
    // FILE *file = fopen("DESPENSA.txt", "w");
    FILE *file = fopen("DESPENSA.txt", "a"); /* se abre el archivo con modo 'a'para Abrir o
     crea para escritura. Agrega despues de cualquier contenido previo.*/
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    for (int i = 0; i < numProductos; i++)
    {
        fprintf(file, "%s %s %.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }

    fclose(file);
}
// Funcion para cargar
void cargar(Producto *productos, int *numProductos)
{
    FILE *file = fopen("DESPENSA.txt", "r"); // Se abre la lectura del archivo con el modo 'r'
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    while (fscanf(file, "%s %s %.2f", productos[*numProductos].nombre, productos[*numProductos].cantidad, &productos[*numProductos].precio) == 3)
    {
        // si fscanf lee los 3 campos: nombre, cantidad y precio numProductos incrementa de 1 en 1
        (*numProductos)++;
    }
    fclose(file);
}

// funcion para traer archivo de texto al ejecutable(Hipertension)
void Hiper(const char *Hipertension)
{

    FILE *file = fopen("hipertension.txt", "r"); // 'r' para abrir lectura de archivo Hipertension
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char texto[1000]; // Se almacena cada linea del archivo
    while (fgets(texto, sizeof(texto), file))
    {                        // sizeof calcula el tamaño en bytes de su operenado
        printf("%s", texto); // imprime la linea
    }

    fclose(file); // cierre del archivo Hipertension
}

// funcion para traer archivo de texto al ejecutable(Diabetes)
void Dia(const char *Diabetes)
{
    FILE *file = fopen("Diabetes.txt", "r"); //'r' para abrir lectura del archivo Diabetes
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char texto[1000]; // se almacena cada linea de texto
    while (fgets(texto, sizeof(texto), file))
    {
        printf("%s", texto); // imprime la linea
    }
    fclose(file); // cierre del archivo Diabetes
}

// funcion para taer archivo de texto al ejecutable (Obesidad)
void Obe(const char *Obesidad)
{
    FILE *file = fopen("Obesidad.txt", "r"); //'r'para abrir la lectura del archivo Obesidad
    if (file == NULL)
    {
        printf("No se encintro el archivo\n");
        return;
    }
    char texto[1000]; // Se almacena cada linea de texto
    while (fgets(texto, sizeof(texto), file))
    {
        printf("%s", texto); // imprime la linea
    }
    fclose(file); // cierre del archivo Obesidad
}
// funcion para traer archivo de texto al ejecutable (sin enfermedad)
void No_enfer(const char *NoEfermedad)
{
    FILE *file = fopen("SinEnfermedad.txt", "r"); //'r'para abrir la lectura del archivo SinEnfermedad
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    char texto[1000]; // se almacena cada linea de texto
    while (fgets(texto, sizeof(texto), file))
    {
        printf("%s", texto); // imprime la linea
    }
    fclose(file); // cierre del archivo SinEnfermedad
}

// funcion principal int main
int main()
{

    setlocale(LC_ALL, "");

    Producto productos[50]; // cantidad posible de productos en la Despensa
    int numProductos = 0;
    int opcion;
    int n;

    cargar(productos, &numProductos);

    printf("Has sufrido o sufres alguna enfermedad como las siguientes?\n");
    do
    {
        printf("\n1. Hipertension\n");
        printf("2. Diabetes\n");
        printf("3. Obesidad\n");
        printf("4. Ninguna\n");
        printf("5. Empezar a crear despensa\n");

        scanf("%d", &n);

        switch (n)
        {

        case 1:
         system("cls");
            Hiper("hipertension.txt");
            break;

        case 2:
         system("cls");
            Dia("Diabetes.txt");
            break;
        case 3:
         system("cls");
            Obe("Obesidad.txt");
            break;
        case 4:
         system("cls");
            No_enfer("SinEnfermedad.txt");
            break;
        } // llave de switch
    } while (n != 5);

    do
    {
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Modificar producto\n");
        printf("4. Borrar producto\n");
        printf("5. Buscar producto\n");
        //        printf("6. Guardar personas\n"); //realizado por las funciones
        //        printf("7. Cargar personas\n");   //realizado por las funciones
        printf("6. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
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
            guardar(productos, numProductos); // el usaurio saldra y se guardaran sus productos en el archivo
            break;
            //            case 7:
            //               cargar(productos, &numProductos);
            //                break;
        }
    } while (opcion != 6);

    return 0;
}