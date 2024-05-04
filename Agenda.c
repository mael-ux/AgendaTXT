#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define T_NDI 5
#define T_NAME 50
#define T_MAIL 50
#define T_PHONE 10
#define T_AGENDA 30

//Carlos Emilio González Urías
//Andrea Alexandra Arias Villaseñor
//Anahí Ramírez Rodríguez
//Rodrigo Mael Vizcarra Morquecho
typedef struct
{
    char ndi[T_NDI ];
    char nombre[T_NAME];
    char correo[T_MAIL];
    char telefono[T_PHONE];
}Agenda;

int valida_ndi(char *ndi_aux, Agenda *agenda, int contAgenda)
{
    int band = 0;
    int i;

    for (i = 0; i < contAgenda; i++)
    {
        if (strcmp(agenda[i].ndi, ndi_aux) == 0){
          if (isalpha(agenda[i].ndi)==0){
            band = 1;
          }
        }
    }

    if (band) return 0;
        else return 1;
}


int agregar_usuario(Agenda *agenda, int contAgenda)
{
    char ndi_tmp[T_NDI];

    printf("+ + Agregar Usuario + +\n");
    printf("NDI: ");
    fgets(ndi_tmp, sizeof(ndi_tmp), stdin);
    ndi_tmp[strcspn(ndi_tmp, "\n")] = '\0';

    if (!valida_ndi(ndi_tmp, agenda, contAgenda))
    {
      return -1;
    }

    strncpy(agenda[contAgenda].ndi, ndi_tmp, sizeof(agenda[contAgenda].ndi));

    printf("Nombre completo: ");
    fgets(agenda[contAgenda].nombre, sizeof(agenda[contAgenda].nombre), stdin);
    agenda[contAgenda].nombre[strcspn(agenda[contAgenda].nombre, "\n")] = '\0';

    printf("Correo: ");
    fgets(agenda[contAgenda].correo, sizeof(agenda[contAgenda].correo), stdin);
    agenda[contAgenda].correo[strcspn(agenda[contAgenda].correo, "\n")] = '\0';

    printf("Telefono: ");
    fgets(agenda[contAgenda].telefono, sizeof(agenda[contAgenda].telefono), stdin);
    agenda[contAgenda].telefono[strcspn(agenda[contAgenda].telefono, "\n")] = '\0';

    return contAgenda + 1;
 }


 int buscar_usuario(Agenda *agenda, int contAgenda)
{
    char ndi_aux[T_NDI];
    int i = 0;
    int band = 0;

    printf("Ingresa el NDI a buscar: ");
    fgets(ndi_aux, sizeof(ndi_aux), stdin);
    ndi_aux[strcspn(ndi_aux, "\n")] = '\0';

    for (i = 0; i < contAgenda && band == 0; i++)
    {
        if (strcmp(agenda[i].ndi, ndi_aux) == 0)
        {
            band = 1;
        }
    }

    printf("Elementos iterados: %i\n", i);

    if (!band)

    {
        return -1;
    }

    return i - 1;
}


 int modificar_usuario(Agenda *agenda, int posicion)
{
    printf("NDI: %s\n", agenda[posicion].ndi);
    printf("Nombre completo: ");
    fgets(agenda[posicion].nombre, sizeof(agenda[posicion].nombre), stdin);
    agenda[posicion].nombre[strcspn(agenda[posicion].nombre, "\n")] = '\0';

    printf("Correo: ");
    fgets(agenda[posicion].correo, sizeof(agenda[posicion].correo), stdin);
    agenda[posicion].correo[strcspn(agenda[posicion].correo, "\n")] = '\0';

    printf("Telefono: ");
    fgets(agenda[posicion].telefono, sizeof(agenda[posicion].telefono), stdin);
    agenda[posicion].telefono[strcspn(agenda[posicion].telefono, "\n")] = '\0';

    return (0);
 }


void mostrar_usuario(Agenda *agenda, int posicion)
{
    printf("NDI: %s\n", agenda[posicion].ndi);
    printf("Nombre completo: %s\n", agenda[posicion].nombre);
    printf("Correo: %s\n", agenda[posicion].correo);
    printf("Telefono: %s\n", agenda[posicion].telefono);
}


int mostrar_todos(Agenda *agenda, int contAgenda)
{
    int i = 0;

    printf("+ + Mostrar Usuarios + + \n");

    for (i = 0; i < contAgenda; i++)
    {
        mostrar_usuario(agenda, i);
        printf("\n");
    }

    printf("Elementos mostrados: %i\n", i);

    return (0);
 }


int eliminar_usuario(Agenda *agenda, int contAgenda, int pos)
{
    if (pos == contAgenda - 1)
    {
        return contAgenda - 1;
    }

    while (pos <= contAgenda - 1){
        strcpy(agenda[pos].ndi, agenda[pos + 1].ndi);
        strcpy(agenda[pos].nombre, agenda[pos + 1].nombre);
        strcpy(agenda[pos].correo, agenda[pos + 1].correo);
        strcpy(agenda[pos].telefono, agenda[pos + 1].telefono);
        pos++;
    }

    return contAgenda - 1;
}


int eliminar_usuario_2(Agenda *agenda, int contAgenda, int pos)
{
    if (pos == contAgenda - 1)
    {
        return contAgenda - 1;
    }

    strcpy(agenda[pos].ndi, agenda[contAgenda - 1].ndi);
    strcpy(agenda[pos].nombre, agenda[contAgenda - 1].nombre);
    strcpy(agenda[pos].correo, agenda[contAgenda - 1].correo);
    strcpy(agenda[pos].telefono, agenda[contAgenda - 1].telefono);
    contAgenda--; //decrementa la posicion en el arreglo de usuarios

    return contAgenda - 1;
}

int abrir_txt(Agenda *agenda, int *contAgenda) {
    FILE *fptr = fopen("Usuarios.txt", "r");

    fseek(fptr,0,SEEK_END);
    if (ftell(fptr)==0){
        printf("El archivo esta vacio");
        return -1;
    }

    fseek(fptr,0,SEEK_SET);
    if (fptr == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }
    char character;
    int encabezado = 1;

    while ((character = fgetc(fptr))!= EOF) {
        if (encabezado) {
            if (character == '\n') {
                encabezado = 0;
            }
        } else {
            putchar(character);
        }
    }

    rewind(fptr);
    while (fscanf(fptr, "%3[^,],%49[^,],%49[^,],%9[^\n]%*c",
           agenda[*contAgenda].ndi, agenda[*contAgenda].nombre,
           agenda[*contAgenda].correo, agenda[*contAgenda].telefono) == 4) {
        (*contAgenda)++;
    }

    fclose(fptr);
    system("cls");
    return *contAgenda;
}

int guardar_txt(Agenda *agenda, int contAgenda) {
    FILE *fptr; // Corrección en la declaración del puntero FILE

    // Abre el archivo para escribir, si no se puede abrir, devuelve -1
    fptr = fopen("agenda_datos_test.txt", "w");
    if (fptr == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    // Escribe los datos de la agenda en el archivo
    for (int i = 0; i < contAgenda; i++) {
        fprintf(fptr, "%s,", agenda[i].ndi);
        fprintf(fptr, "%s,", agenda[i].nombre);
        fprintf(fptr, "%s,", agenda[i].correo);
        fprintf(fptr, "%s\n", agenda[i].telefono); // Cambiado "\n" a "%s\n"
    }

    // Cierra el archivo
    fclose(fptr);
    return 0;
}

int ordenar_agenda(Agenda *agenda, int contAgenda){
	int i,j,cont;

	for (cont=0;cont<contAgenda;cont++){
		for (i=0;i<contAgenda-1;i++){
			if(atoi(agenda[i].ndi)>atoi(agenda[i+1].ndi)){
                Agenda aux=agenda[i];
                agenda[i]=agenda[i+1];
                agenda[i+1]=aux;
			}
		}
	}
    mostrar_todos(agenda,contAgenda);

    return 0;
}

int main(){
    Agenda agenda[T_AGENDA];
    int contAgenda = 0;
    abrir_txt(agenda, &contAgenda);
    char clear;
    int opc;
    char opc_elimina;
    int pos, retorno;
    clock_t inicio, fin;
    double tiempo;

    do
    {
        printf("\n>> AGENDA ELECTRONICA <<\n\n");
        printf("[1] Alta de usuario \n");
        printf("[2] Modifica usuario \n");
        printf("[3] Busca usuario \n");
        printf("[4] Muestra todos \n");
        printf("[5] Elimina usuario \n");
        printf("[6] Guardar cambios \n");
        printf("[7] Salir del programa \n");
        printf("[8] Ordenar la agenda \n");
        printf("Ingresa opcion: ");

        scanf("%i", &opc);
        do{clear=getchar();}while(clear !='\n');
        printf("\n");

        switch (opc)
        {
            case 1:
                if (contAgenda < T_AGENDA){
                    retorno = agregar_usuario(agenda, contAgenda);
                    if ( retorno == -1)
                    {
                        printf("El NDI ya existe\n");
                    }else{
                        contAgenda = retorno;
                        printf("Usuario %i, agregado\n", contAgenda);
                    }
                }else{
                    printf("La agenda tiene su maximo registro de usuarios");
                }

            break;

            case 2:
                printf("+ + Modifica usuario + +\n");

                pos = buscar_usuario(agenda, contAgenda);
                if (pos >= 0)
                {
                    modificar_usuario(agenda, pos);
                }else{
                    printf("No se encontro registro en la busqueda\n");
                }

            break;

            case 3:
                printf("+ + Busca usuario + +\n");

                pos = buscar_usuario(agenda, contAgenda);
                if (pos >= 0)
                {
                    mostrar_usuario(agenda, pos);
                }else{
                    printf("No se encontro registro en la busqueda\n");
                }

            break;

            case 4:
                if (contAgenda > 0)
                {
                    inicio = clock();
                    mostrar_todos(agenda, contAgenda);
                    fin = clock();
                    tiempo = ((double) (fin - inicio));
                    printf("Tiempo de busqueda: %f segundos\n", tiempo);
                }else{
                    printf("No hay usuarios registrados\n");
                }
            break;

            case 5:
                printf("+ + Elimina usuario + +\n");
                pos = buscar_usuario(agenda, contAgenda);

                if (pos >= 0)
                {
                    printf("Posicion a eliminar: %i - Total de usuarios: %i\n", pos, contAgenda);
                    mostrar_usuario(agenda, pos);

                    printf("Presiona [y] para confirmar,\npresiona cualquier otra tecla para cancelar: ");
                    scanf("%c", &opc_elimina);
                    do{clear=getchar();}while(clear !='\n');

                    opc_elimina = toupper(opc_elimina);
                    if (opc_elimina == 'Y')
                    {
                        contAgenda = eliminar_usuario(agenda, contAgenda, pos);
                        printf("Usuario eliminado...\n");

                    }else{
                        printf("Usuario no eliminado\n");
                    }

                }else{
                    printf("No se encontro registro para eliminar\n");
                }
                // mostrar_Archivo();
            break;

           case 6:
                printf("+ + Guardar cambios + +\n");
                guardar_txt(agenda, contAgenda);

            break;

            case 7:
                printf("Se ejecuta salir del programa...");

            break;

            case 8:
            	printf("+ + Ordenar agenda + +\n");
                inicio = clock();
            	ordenar_agenda(agenda, contAgenda);
            	fin = clock();
                tiempo = ((double) (fin - inicio));
                printf("Tiempo de ordenamiento: %f segundos\n", tiempo);
             break;

            default: printf("Eleccion fuera de rango");
        } //Fin del switch
    }while (opc != 7);

    return 0;

}
