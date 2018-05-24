#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include "propietario.h"

#define VACIO -1


void initPropietarios(EPropietario prop[],int tamanho,int estadoInicial)
{
    int i;
    for(i=0; i < tamanho; i++)
    {
        prop[i].estado = estadoInicial;
        prop[i].idPropietario = estadoInicial;
    }

}

int isNull (char value)
{
    if(value=='\0' || value ==' ')
    {
        return 1;
    }
    return 0;
}

int esNumerico(char array[])
{
    int i=0, flag=1;

    if(isNull(array[0]))
    {
        flag = 0;
    }
    else
    {
        while(array[i] != '\0')
        {
            if((!isdigit(array[i])))
            {
                flag = 0;
                break;
            }
            i++;
        }
    }
    return flag;
}

int esSoloLetras(char array[])
{
    int i=0, flag=1;
    if(isNull(array[0]))
    {
        flag = 0;
    } else {
    while(array[i] != '\0')
    {
        if( (!isspace(array[i])) && (!isalpha(array[i])) )
        {
            flag = 0;
            break;
        }
        i++;
    }}
    return flag;
}

int esAlfanumerico(char array[])
{
    int i=0, flag=1;
    if(isNull(array[0]))
    {
        flag = 0;
    } else {
    while(array[i] != '\0')
    {
        if((!isdigit(array[i])) && (!isalpha(array[i])) && (!isspace(array[i])))
        {
            flag = 0;
            break;
        }
        i++;
    }}
    return flag;
}

int esTarjeta(char array[])
{
    int i=0;
    int contadorGuiones=0;
    if(isNull(array[0]))
    {
        return 0;
    } else {
    while(array[i] != '\0')
    {
        if((array[i] != '-') && (!isdigit(array[i])))
            return 0;
        if(array[i] == '-')
            contadorGuiones++;
        i++;
    }
    if(contadorGuiones==1) // debe tener un guion
        return 1;
    }
    return 0;
}

void getString(char mensaje[],char input[])
{
    printf("%s",mensaje);
    gets(input);
    fflush(stdin);
}

int getStringNumeros(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esNumerico(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int getStringLetras(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esSoloLetras(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int getStringAlfaNumerico(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esAlfanumerico(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int getStringTarjeta(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esTarjeta(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int ingresoStringNumerico(char mensaje[])
{
    char auxDato[20];
    int dato;
    printf("\nIngrese %s:",mensaje);
    getString(" ",auxDato);
    while(!esNumerico(auxDato))
    {
        printf("*%s* solo puede estar compuesto por numeros.\nReingrese %s: ",mensaje,mensaje);
        fflush(stdin);
        gets(auxDato);
    }
    dato = atoi(auxDato);

    return dato;
}

int validarDatoMaxMin(int dato, char mensaje[], int min, int max)
{
    while((dato < min) || (dato > max))
    {
        printf("El item *%s* debe estar entre %d y %d.\n",mensaje,min,max);
        dato = ingresoStringNumerico(mensaje);
    }
    return dato;
}


int buscarIndexEstado(EPropietario prop[],int tamanho,int valor)
{
    int i;
    for(i=0; i < tamanho; i++)
    {
        if(prop[i].estado == valor)
        {
            return i;
        }
    }
    return VACIO;
}
int buscarID (EPropietario prop[],int tamanho,int valor)
{
    int i;
    for(i=0; i < tamanho; i++)
    {
        if((prop[i].idPropietario == valor)&& (prop[i].estado != VACIO))
        {
            return i;
        }
    }
    return VACIO;
}
int buscarTarjeta(EPropietario prop[],int tamanho,char tarj[])
{
    int i;
    for(i=0; i < tamanho; i++)
    {
        if((strcmp(tarj,prop[i].tarjetaDeCredito) == 0)&& (prop[i].estado != VACIO))
        {
            return i;
        }
    }
    return VACIO;
}




void altaProp (EPropietario prop[], int tp)
{
    int i, indexLibre, flag=0, indexTarjDuplicada;
    char nombreyapellido[50], tarjeta[8], direccion[20], respuesta='x';
    do
    {
        indexLibre = buscarIndexEstado(prop, tp, VACIO);
        if(indexLibre == VACIO)
        {
            printf("No hay lugares libres para el registro\n");
            break;
        }
        else
        {

            printf("\n *REGISTRAR PROPIETARIO* \n");

            while(!getStringLetras("Ingrese su nombre y apellido: ",nombreyapellido))
            {
                printf("Nombre y apellido solo pueden tener letras. Intente nuevamente.\n\n");
            }

            while(!getStringAlfaNumerico("Ingrese la direccion: ",direccion))
            {
                printf("La direccion solo puede tener letras y numeros. Intente nuevamente.\n\n");
            }
            do
            {
                while((!getStringTarjeta("Ingrese su nro de tarjeta de credito: ",tarjeta)) || (strlen(tarjeta)!=7))
                {
                    printf("La tarjeta debe estar en formato 123-456.\nSolo seis numeros en total y un guion. Intente nuevamente.\n");
                }
                indexTarjDuplicada = buscarTarjeta(prop,tp,tarjeta);
                if( indexTarjDuplicada != VACIO )
                {
                    printf("Ya se ha registrado un propietario con ese numero de tarjeta. Reingresar otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        flag = 1;
                        break;
                    }
                    printf("\n");
                }
                else
                {
                    break;
                }

            }
            while((respuesta=='s')||(respuesta=='S'));
            if(!flag)
            {
                printf("Confirmar alta? s/n: ");
                respuesta = getche();
                if((respuesta=='s')||(respuesta=='S'))
                {
                    strlwr(nombreyapellido);
                    for(i=0; i<50; i++)
                    {
                        if(nombreyapellido[i]==' ')
                        {
                            nombreyapellido[i+1]=toupper(nombreyapellido[i+1]);
                        }
                    }
                    nombreyapellido[0]=toupper(nombreyapellido[0]);
                    strcpy(prop[indexLibre].nombreYapellido,nombreyapellido);
                    strcpy(prop[indexLibre].tarjetaDeCredito,tarjeta);
                    strcpy(prop[indexLibre].direccion,direccion);
                    prop[indexLibre].estado = 1;
                    prop[indexLibre].idPropietario = idIncremental(prop, tp);

                    printf("\nAlta realizada correctamente, desea realizar otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
                else
                {
                    printf("\nAlta cancelada, desea realizar otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
            }
            else
            {
                printf("\nTarjeta no ingresada, alta cancelada.\n\nDesea realizar otra ALTA? s/n: ");
                respuesta = getche();
                if((respuesta!='s')&&(respuesta!='S'))
                {
                    break;
                }
            }
        }
        system("cls");
    }
    while((respuesta=='s')||(respuesta=='S'));
}

void modificarProp(EPropietario prop[], int tp)
{
    int auxID, index, indexTarjDuplicada, flag=0;
    char respuesta='x', tarjeta[8];

    do
    {
        mostrarTodoProp(prop,tp);
        auxID = ingresoStringNumerico("ID de propietario a modificar");
        index = (buscarID(prop,tp,auxID));
        if(index!=VACIO)
        {
            printf("ID\tTarjeta\tNOMBRE\n");
            printf("%d\t%s\t%s",prop[index].idPropietario,prop[index].tarjetaDeCredito,prop[index].nombreYapellido);

            do
            {
                while((!getStringTarjeta("\nIngrese el nuevo nro de tarjeta: ",tarjeta))|| (strlen(tarjeta)!=7))
                {
                    printf("La tarjeta debe estar en formato 123-456.\nSolo seis numeros en total y un guion en medio. Intente otra vez.\n");
                }
                indexTarjDuplicada = buscarTarjeta(prop,tp,tarjeta);
                if( indexTarjDuplicada != VACIO )
                {
                    printf("Ya se ha registrado un propietario con ese numero de tarjeta. Reingresar otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        flag = 1;
                        break;
                    }
                }
                else
                {
                    break;
                }

            }
            while((respuesta=='s')||(respuesta=='S'));

            if(!flag)
            {
                printf("Confirmar modificacion? s/n: ");
                respuesta = getche();
                if((respuesta=='s')||(respuesta=='S'))
                {

                    strcpy(prop[index].tarjetaDeCredito,tarjeta);
                    printf("\nModificacion exitosa.\nDesea hacer otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
                else
                {
                    printf("\nModificacion cancelada, desea realizar otra? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
            }
            else
            {
                printf("\nTarjeta no ingresada, operacion cancelada.\n\nDesea realizar otra modificacion? s/n: ");
                respuesta = getche();
                if((respuesta!='s')&&(respuesta!='S'))
                {
                    break;
                }
            }
        }
        else
        {
            printf("ID Incorrecto, intentar nuevamente? s/n: ");
            respuesta = getche();
            if((respuesta!='s')&&(respuesta!='S'))
            {
                break;
            }
        }
        system("cls");
    }
    while((respuesta=='s')||(respuesta=='S'));

}



void mostrarTodoProp(EPropietario prop[], int tp)
{
    int i;
    printf("ID\tNRO DE TARJETA\tNOMBRE Y APELLIDO\n");
    printf("-------------------------------------------\n");

    for(i=0; i<tp; i++)
    {

        if(prop[i].estado != VACIO)
        {
            printf("%d\t%s\t\t%s\n", prop[i].idPropietario, prop[i].tarjetaDeCredito, prop[i].nombreYapellido);
        }
    }

}



int idIncremental(EPropietario prop[],int tamanio)
{
    int id = 0;
    int i;
    for(i=0; i<tamanio; i++)
    {
        if(prop[i].estado == 1 && prop[i].idPropietario>id)///si el anterior esta ocupado y es mayor al retorno
        {
            id=prop[i].idPropietario;///devuelve esa id
        }
        else
        {
            break;
        }
    }

    return id+1;///y retorna el lugar siguiente
}


void propietariosHC(EPropietario prop[])
{
    int id[]= {1,2,3,4};
    char nombre[][20]= {"Alfredo Lopez","Ricardo Sul","Ruben Lamas","Tefi Luzio"};
    char tarjeta[][20]= {"111-111","222-222","333-333","444-444"};
    char direccion[][20]= {"mitre 857","urquiza 999","belgrano 123","alsina 823"};

    int i;

    for(i=0; i<4; i++)
    {
        strcpy(prop[i].nombreYapellido,nombre[i]);
        strcpy(prop[i].tarjetaDeCredito,tarjeta[i]);
        strcpy(prop[i].direccion,direccion[i]);
        prop[i].idPropietario = id[i];
        prop[i].estado = 1;
    }
}
