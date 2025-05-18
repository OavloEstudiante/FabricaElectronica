#include "funciones.h"
#include <string.h>

#define MAX_PEDIDOS 10
char nombreFabricaGlobal[MAX_NOMBRE_FABRICA] = "";
char nombresComponentesGlobal[MAX_COMPONENTES][MAX_NOMBRE_ITEM];
char nombresProductosGlobal[MAX_PRODUCTOS][MAX_NOMBRE_ITEM];
int componentesPorProductoGlobal[MAX_PRODUCTOS][MAX_COMPONENTES];
float tiemposProduccionPorProductoGlobal[MAX_PRODUCTOS];
int numComponentesIngresadosGlobal = 0;
int numProductosIngresadosGlobal = 0;
int cfgFabricaNombradaGlobal = 0;
int cfgComponentesGlobal = 0;
int cfgProductosGlobal = 0;
int cfgCompPorProdGlobal = 0;
int cfgTiemposGlobal = 0;
int stockComponentesGlobal[MAX_COMPONENTES];
char nombresProductosPedidosGlobal[MAX_PEDIDOS][MAX_NOMBRE_ITEM];
int cantidadesProductosPedidosGlobal[MAX_PEDIDOS];
float tiemposLimitePedidosGlobal[MAX_PEDIDOS];
int estadosPedidosGlobal[MAX_PEDIDOS] = {0};
int numPedidosActivosGlobal = 0;
int unidadesProducidasPorProductoGlobal[MAX_PRODUCTOS];
float preciosSinImpuestosPorProductoGlobal[MAX_PRODUCTOS];
int preciosAsignadosGlobal[MAX_PRODUCTOS];
int unidadesVendidasPorProductoGlobal[MAX_PRODUCTOS];
float gananciasTotalesGlobal = 0.0f;
char historialPedidosNombres[MAX_ITEMS_PEDIDOS_HISTORIAL][MAX_NOMBRE_ITEM];
int historialPedidosCantidades[MAX_ITEMS_PEDIDOS_HISTORIAL];
int numPedidosEnHistorial = 0;
char nombreProductoPedidoGlobal[MAX_NOMBRE_ITEM] = "";
int cantidadProductoPedidoGlobal = 0;
float tiempoLimitePedidoGlobal = 0.0f;
int pedidoActivoGlobal = 0;

void inicializarTodosLosDatosGlobales() {
    strcpy(nombreFabricaGlobal, "");
    
    for(int i = 0; i < MAX_COMPONENTES; i++) {
        strcpy(nombresComponentesGlobal[i], "");
        stockComponentesGlobal[i] = 0;
    }
    
    for(int i = 0; i < MAX_PRODUCTOS; i++) {
        strcpy(nombresProductosGlobal[i], "");

        for(int j = 0; j < MAX_COMPONENTES; j++) {
            componentesPorProductoGlobal[i][j] = 0;
        }
        
        tiemposProduccionPorProductoGlobal[i] = 0.0f;
        unidadesProducidasPorProductoGlobal[i] = 0;
        preciosSinImpuestosPorProductoGlobal[i] = 0.0f;
        preciosAsignadosGlobal[i] = 0;  
        unidadesVendidasPorProductoGlobal[i] = 0;
    }
    
    numComponentesIngresadosGlobal = 0;
    numProductosIngresadosGlobal = 0;
    
    cfgFabricaNombradaGlobal = 0;
    cfgComponentesGlobal = 0;
    cfgProductosGlobal = 0;
    cfgCompPorProdGlobal = 0;
    cfgTiemposGlobal = 0;

    for(int i = 0; i < MAX_PEDIDOS; i++) {
        strcpy(nombresProductosPedidosGlobal[i], "");
        cantidadesProductosPedidosGlobal[i] = 0;
        tiemposLimitePedidosGlobal[i] = 0.0f;
        estadosPedidosGlobal[i] = 0;
    }
    numPedidosActivosGlobal = 0;
    
    for(int i = 0; i < MAX_ITEMS_PEDIDOS_HISTORIAL; i++) {
        strcpy(historialPedidosNombres[i], "");
        historialPedidosCantidades[i] = 0;
    }
    numPedidosEnHistorial = 0;
    
    strcpy(nombreProductoPedidoGlobal, "");
    cantidadProductoPedidoGlobal = 0;
    tiempoLimitePedidoGlobal = 0.0f;
    pedidoActivoGlobal = 0;
    
    gananciasTotalesGlobal = 0.0f;
}

int main() {
    int estadoPrograma = 1;
    int opcionConfigSalida = -1;

    printf("¡Vamos a crear una fabrica electronica!\n");
    inicializarTodosLosDatosGlobales();

    while (estadoPrograma != 0) {
        if (estadoPrograma == 1) {
            opcionConfigSalida = -1;
            do {
                mostrarMenuConfiguracion(nombreFabricaGlobal, cfgFabricaNombradaGlobal,
                                         cfgComponentesGlobal, cfgProductosGlobal,
                                         cfgCompPorProdGlobal, cfgTiemposGlobal);
                opcionConfigSalida = leerEnteroEntreLimites("Ingrese su opcion: ", 0, 11);

                switch (opcionConfigSalida) {
                    case 1:
                        ingresarNombreFabrica(nombreFabricaGlobal);
                        cfgFabricaNombradaGlobal = (strlen(nombreFabricaGlobal) > 0);
                        break;
                    case 2:
                        ingresarNombresComponentes(nombresComponentesGlobal, &numComponentesIngresadosGlobal);
                        cfgComponentesGlobal = (numComponentesIngresadosGlobal == MAX_COMPONENTES);
                        break;
                    case 3:
                        ingresarNombresProductos(nombresProductosGlobal, &numProductosIngresadosGlobal,
                                                nombresComponentesGlobal, numComponentesIngresadosGlobal,
                                                componentesPorProductoGlobal,
                                                tiemposProduccionPorProductoGlobal);
                        cfgProductosGlobal = (numProductosIngresadosGlobal >= 1);
                        break;
                    case 4:
                        if (!cfgComponentesGlobal || numProductosIngresadosGlobal < 1) { 
                            printf("Error: Debe ingresar al menos 1 componente (opcion 2) y al menos 1 producto (opcion 3) primero.\n");
                        } else {
                            ingresarComponentesParaCadaProducto(nombresProductosGlobal, numProductosIngresadosGlobal,
                                                            nombresComponentesGlobal, numComponentesIngresadosGlobal,
                                                            componentesPorProductoGlobal);
                            cfgCompPorProdGlobal = 1;
                        }
                        break;
                    case 5:
                        if (numProductosIngresadosGlobal < 1) { 
                            printf("Error: Debe ingresar al menos 1 producto (opcion 3) primero.\n");
                        } else {
                            ingresarTiempoProduccionPorProducto(nombresProductosGlobal, numProductosIngresadosGlobal,
                                                            tiemposProduccionPorProductoGlobal);
                            cfgTiemposGlobal = 1;
                        }
                        break;
                    case 6:
                        if (!cfgFabricaNombradaGlobal && !cfgComponentesGlobal && !cfgProductosGlobal) {
                            printf("Error: Ingrese primero el nombre de la fabrica, componentes y productos.\n");
                        } else {
                            editarNombresMenu(nombreFabricaGlobal,
                                            nombresComponentesGlobal, numComponentesIngresadosGlobal,
                                            nombresProductosGlobal, numProductosIngresadosGlobal,
                                            componentesPorProductoGlobal, tiemposProduccionPorProductoGlobal,
                                            nombresComponentesGlobal, numComponentesIngresadosGlobal);
                        }
                        break;
                    case 7:
                        if (numComponentesIngresadosGlobal < 1 || numProductosIngresadosGlobal < 1) {  
                            printf("Error: Debe ingresar al menos 1 componente y 1 producto primero.\n");
                        } else {
                            editarValoresMenu(nombresProductosGlobal, numProductosIngresadosGlobal,
                                            nombresComponentesGlobal, numComponentesIngresadosGlobal,
                                            componentesPorProductoGlobal,
                                            tiemposProduccionPorProductoGlobal);
                        }
                        break;
                    case 8:
                        if (!cfgComponentesGlobal || !cfgProductosGlobal) {
                            printf("Error: Ingrese componentes y productos primero (Opciones 2 y 3).\n");
                        } else {
                            eliminarElementoMenu(nombresComponentesGlobal, &numComponentesIngresadosGlobal,
                                               nombresProductosGlobal, &numProductosIngresadosGlobal,
                                               componentesPorProductoGlobal,
                                               tiemposProduccionPorProductoGlobal,
                                               &cfgCompPorProdGlobal, &cfgTiemposGlobal,
                                               cfgComponentesGlobal, cfgProductosGlobal);
                        }
                        break;
                    case 9:
                        eliminarDatosFabrica(nombreFabricaGlobal,
                                            nombresComponentesGlobal, &numComponentesIngresadosGlobal,
                                            nombresProductosGlobal, &numProductosIngresadosGlobal,
                                            componentesPorProductoGlobal, tiemposProduccionPorProductoGlobal,
                                            &cfgFabricaNombradaGlobal, &cfgComponentesGlobal, &cfgProductosGlobal,
                                            &cfgCompPorProdGlobal, &cfgTiemposGlobal);
                        break;
                    case 10:
                        mostrarRestriccionesEcuador();
                        break;
                    case 11:
                        if (cfgFabricaNombradaGlobal && cfgComponentesGlobal && numProductosIngresadosGlobal >= 1 && 
                            cfgCompPorProdGlobal && cfgTiemposGlobal) {
                            printf("\nDirigiendose al menu de optimizacion...\n");
                            estadoPrograma = 2;
                        } else {
                            printf("Error: Debe completar todos los pasos de configuracion (1-5) antes de continuar.\n");
                            printf("Estado: Fabrica:%d, Comp:%d, Prod:%d, CompXProd:%d, Tiempos:%d\n",
                                cfgFabricaNombradaGlobal, cfgComponentesGlobal, numProductosIngresadosGlobal >= 1, 
                                cfgCompPorProdGlobal, cfgTiemposGlobal);
                        }
                        break;
                    case 0:
                        printf("Saliendo del programa...\n");
                        estadoPrograma = 0;
                        break;
                }
                if (opcionConfigSalida != 0 && !(opcionConfigSalida == 11 && estadoPrograma == 2)) {
                    printf("\nPresione Enter para continuar...");
                    getchar();
                }
            } while (opcionConfigSalida != 0 && !(opcionConfigSalida == 11 && estadoPrograma == 2));
        } else if (estadoPrograma == 2) {
            bucleMenuOptimizacion(&estadoPrograma,
                nombreFabricaGlobal,
                nombresComponentesGlobal, 
                numComponentesIngresadosGlobal,
                nombresProductosGlobal, 
                numProductosIngresadosGlobal,
                componentesPorProductoGlobal,
                tiemposProduccionPorProductoGlobal,
                stockComponentesGlobal,
                nombreProductoPedidoGlobal, 
                &cantidadProductoPedidoGlobal,
                &tiempoLimitePedidoGlobal, 
                &pedidoActivoGlobal,
                unidadesProducidasPorProductoGlobal,
                preciosSinImpuestosPorProductoGlobal,
                preciosAsignadosGlobal,
                unidadesVendidasPorProductoGlobal,
                &gananciasTotalesGlobal,
                historialPedidosNombres,
                historialPedidosCantidades,
                &numPedidosEnHistorial,
                nombresProductosPedidosGlobal,
                cantidadesProductosPedidosGlobal,
                tiemposLimitePedidosGlobal,
                estadosPedidosGlobal,
                &numPedidosActivosGlobal);
        }
    }

    printf("\nFin del programa Lindo dia.\n");
    return 0;
}
