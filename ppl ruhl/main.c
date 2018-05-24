#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include "propietario.h"
#include "autos.h"

#define QTY_EG 100
#define qty_PROP 20
#define qty_AUTOS 20
#define VACIO -1
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTROS 4
int main()
{
    EPropietario prop[qty_PROP];
    initPropietarios(prop,qty_PROP,VACIO);
    propietariosHC(prop);

    EAuto autos[qty_AUTOS];
    initAutos(autos,qty_AUTOS,VACIO);
    autosHC(autos);

    egresosEst autosOut[QTY_EG];
    initEgresos(autosOut,QTY_EG,VACIO);
    egresosHC(autosOut);

    char seguir=1;
    int opcion=0;


    do
    {
        int i, indexA, indexP, auxIdProp, marca, horas;
        char auxNombre[50], auxPatente[5], respuesta = 'x';
        float totalAlpha=0, totalFerrari=0, totalAudi=0, totalOtros=0, totalEstacionamiento=0;
        float estadia=0, estadiaAcumulada=0;


        printf("1- Registrar Propietario\n");
        printf("2- Modificar Propietario\n");
        printf("3- Baja Propietario\n");
        printf("4- Ingreso Automovil\n");
        printf("5- Egreso Automovil\n");
        printf("6- Recaudacion Total Estacionamiento\n");
        printf("7- Recaudacion Total Por Marca\n");
        printf("8- Mostrar automoviles estacionados por propietario\n");
        printf("9- Propietarios de AUDI\n");
        printf("10- Ordenar lista de automoviles por patente\n");

        printf("0- Salir\n");
        opcion = ingresoStringNumerico("opcion");
        while(isNull(opcion))
        {
            printf("**Error: no se detecto ningun dato. Intente nuevamente\n");
            opcion = ingresoStringNumerico("opcion");
        }


        switch(opcion)
        {
        case 1: ///Registrar Propietario
            altaProp(prop,qty_PROP);
            printf("\n");
            system("pause");
            break;
        case 2: ///Modificar tarjeta de propietario
            modificarProp(prop,qty_PROP);
            printf("\n");
            system("pause");
            break;
        case 3: ///Baja de propietario y sus autos
            do
            {
                mostrarTodoProp(prop,qty_PROP);
                auxIdProp = ingresoStringNumerico("ID de propietario a realizar BAJA");
                indexP = (buscarID(prop,qty_PROP,auxIdProp));
                if(indexP!=VACIO)
                {

                    for(i=0; i<qty_AUTOS; i++)
                    {
                        if(auxIdProp==autos[i].idProp && autos[i].estado != VACIO)
                        {
                            marca = autos[i].marca;
                            horas = horasEstadia();
                            estadia=valorEstadia(marca,horas);
                            estadiaAcumulada=estadiaAcumulada+estadia;
                        }
                    }
                    printf("%d\t%s\t%s IMPORTE A PAGAR: %.2f",prop[indexP].idPropietario,prop[indexP].tarjetaDeCredito,prop[indexP].nombreYapellido, estadiaAcumulada);
                    printf("\nConfirmar baja? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                    else
                    {
                        prop[indexP].estado=VACIO;
                        system("cls");
                        for(i=0; i>qty_AUTOS; i++)
                        {
                            if(auxIdProp==autos[i].idProp && autos[i].estado != VACIO)
                            {
                                autos[i].estado = VACIO;
                                marca = autos[indexA].marca;
                                horas = horasEstadia();
                                estadia=valorEstadia(marca,horas);
                                strcpy(auxNombre,prop[indexP].nombreYapellido);
                                strcpy(auxPatente,autos[i].patente);
                                transferDatosEgreso(autosOut,QTY_EG,auxPatente,auxNombre,marca,estadia,horas);
                                printf("Importe por baja de automovil patente %s: &%.2f\n",auxPatente,estadia);

                            }
                        }
                        printf("Gracias por elegirnos!\n");
                        printf("Baja de propietario exitosa.\nDesea realizar otra? s/n: ");
                        respuesta = getche();
                        if((respuesta!='s')&&(respuesta!='S'))
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("\nID Incorrecto, intentar nuevamente? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
                system("cls");
            }
            while((respuesta=='s')||(respuesta=='S'));
            printf("\n");
            system("pause");
            break;
        case 4: ///Ingreso de autos
            ingresoAuto(autos,qty_AUTOS,prop,qty_PROP);
            printf("\n");
            system("pause");
            break;
        case 5: ///Egreso de autos

            do
            {
                mostrarTodoAutos(autos,qty_AUTOS,prop,qty_PROP);
                while((!getStringAlfaNumerico("Ingrese la patente del automovil a egresar: ",auxPatente)) || (strlen(auxPatente)!=3))
                {
                    printf("La patente solo puede ser alfanumerica y tener un maximo de tres caracteres.\n Intente nuevamente.\n");
                }
                indexA = buscarPatente(autos,qty_AUTOS,auxPatente);

                if(indexA!=VACIO)
                {
                    auxIdProp = autos[indexA].idProp;
                    indexP = buscarID(prop,qty_PROP,auxIdProp);
                    ///copiamos datos a auxiliares
                    marca = autos[indexA].marca;
                    horas = horasEstadia();
                    strcpy(auxNombre,prop[indexP].nombreYapellido);
                    strcpy(auxPatente,autos[indexA].patente);
                    estadia=valorEstadia(marca,horas);

                    printf("Datos del coche: %s\t%s\t$%.2f\t\n", prop[indexP].nombreYapellido, autos[indexA].patente,estadia);
                    printf("Confirmar egreso? s/n: ");
                    respuesta = getche();
                    if((respuesta=='s')||(respuesta=='S'))
                    {
                        transferDatosEgreso(autosOut,QTY_EG,auxPatente,auxNombre,marca,estadia,horas);
                        system("cls");
                        autos[indexA].estado = VACIO;
                        printf("\nPropietario:\t %s\n",prop[indexP].nombreYapellido);
                        printf("Patente:\t %s\n", autos[indexA].patente);
                        printf("Marca:\t\t ");
                        imprimirMarca(marca);
//                        importesTot[0].egresosTotales = importesTot[0].egresosTotales+estadia;
                        printf("\nValor estadia:\t %dhs\t$%.2f\n",horas,estadia);
                        printf("Gracias por elegirnos!\n\n");

                        printf("Egreso exitoso, desea realizar otro? s/n: ");
                        respuesta = getche();
                        if((respuesta!='s')&&(respuesta!='S'))
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf("\nEgreso cancelado, desea realizar otro? s/n: ");
                        respuesta = getche();
                        if((respuesta!='s')&&(respuesta!='S'))
                        {
                            break;
                        }
                    }

                }
                else
                {
                    printf("\nPatente no registrada, reintentar? s/n: ");
                    respuesta = getche();
                    if((respuesta!='s')&&(respuesta!='S'))
                    {
                        break;
                    }
                }
                system("cls");

            }
            while((respuesta=='s')||(respuesta=='S'));
            printf("\n");
            system("pause");
            break;
        case 6: ///Mostrar recaudacion total del estacionamiento
            totalEstacionamiento=0;
            for(i=0; i<QTY_EG; i++)
            {
                if(autosOut[i].estado == VACIO)
                {
                    break;
                }
                totalEstacionamiento = totalEstacionamiento + autosOut[i].importe;
                printf("%s\t\t%s\t",autosOut[i].nombreYApellido,autosOut[i].patente);
                imprimirMarca(autosOut[i].marca);
                printf("\t%d\t%.2f\n",autosOut[i].tiempo,autosOut[i].importe);
            }
            printf("La recaudacion total actual del estacionamiento es de $%.2f",totalEstacionamiento);
            printf("\n");
            system("pause");
            break;
        case 7: ///Mostrar recaudacion total por marca

            for(i=0; i<QTY_EG; i++)
            {
                if(autosOut[i].estado != VACIO)
                {
                    switch(autosOut[i].marca)
                    {
                    case ALPHA_ROMEO:
                        totalAlpha = totalAlpha + autosOut[i].importe;
                        break;
                    case FERRARI:
                        totalFerrari = totalFerrari + autosOut[i].importe;
                        break;
                    case AUDI:
                        totalAudi = totalAudi + autosOut[i].importe;
                        break;
                    case OTROS:
                        totalOtros = totalOtros + autosOut[i].importe;
                        break;
                    }
                }
            }
            printf("Recaudacion total por marca: \n\n");
            printf("ALPHA ROMEO:\t %.2f\n",totalAlpha);
            printf("FERRARI:\t %.2f\n",totalFerrari);
            printf("AUDI:\t\t %.2f\n",totalAudi);
            printf("OTROS:\t\t %.2f\n",totalOtros);
            system("pause");
            break;
        case 8: ///Mostrar propietario y sus autos
            mostrarPropietarioConAutos(prop,qty_PROP,autos,qty_AUTOS);
            printf("\n");
            system("pause");
            break;
        case 9: ///Mostrar propietarios de Audi
            mostrarPropAudi(prop,qty_PROP,autos,qty_AUTOS);
            printf("\n");
            system("pause");
            break;
        case 10: ///Ordenar por patente y mostrar
            mostrarPorPatente(prop,autos,qty_AUTOS,qty_PROP);
            printf("\n");
            system("pause");
            break;
        case 0: ///
            seguir = 0;
            break;
        default:
            printf("Opcion invalida, intente de nuevo.\n");
            break;
        }
        printf("\n");
        system("cls");
    }
    while(seguir!=0);
    return 0;
}


