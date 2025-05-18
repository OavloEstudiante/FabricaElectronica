#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>

#define MAX_NOMBRE_FABRICA 100
#define MAX_COMPONENTES 5
#define MAX_PRODUCTOS 5
#define MAX_NOMBRE_ITEM 50
#define MAX_ITEMS_PEDIDOS_HISTORIAL 100
#define MAX_PEDIDOS 10
void limpiarBufferEntradaStdin();
int leerCadenaValida(const char mensaje[], char destino[], int longitudMax);
int leerEntero(const char mensaje[]);
int leerEnteroPositivo(const char mensaje[]);
int leerEnteroEntreLimites(const char mensaje[], int min, int max);
float leerFlotantePositivo(const char mensaje[]);
int confirmarAccion(const char mensaje[]);
int buscarIndicePorNombre(const char nombreBuscado[], const char listaNombres[][MAX_NOMBRE_ITEM], int cantidadItems);
void mostrarMenuConfiguracion(const char nombreFabrica[], int cfgFabricaNombrada, int cfgComponentes, int cfgProductos, int cfgCompPorProd, int cfgTiempos);
void ingresarNombreFabrica(char nombreFabrica[]);
void ingresarNombresComponentes(char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentesIngresados);
void ingresarNombresProductos(char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductosIngresados,
                             const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                             int componentesPorProducto[][MAX_COMPONENTES],
                             float tiemposProduccionPorProducto[]);
void ingresarComponentesParaCadaProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                       const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                                       int componentesPorProducto[][MAX_COMPONENTES]);
void ingresarTiempoProduccionPorProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                       float tiemposProduccionPorProducto[]);
void editarNombresMenu(char nombreFabrica[],
                      char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                      char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                      int componentesPorProducto[][MAX_COMPONENTES],
                      float tiemposProduccionPorProducto[],
                      const char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], int numComponentesGlobal);
void editarValoresMenu(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                      const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                      int componentesPorProducto[][MAX_COMPONENTES],
                      float tiemposProduccionPorProducto[]);
void eliminarElementoMenu(char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentes,
                         char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductos,
                         int componentesPorProducto[][MAX_COMPONENTES],
                         float tiemposProduccionPorProducto[],
                         int* cfgCompPorProd, int* cfgTiempos,
                         int cfgComponentesFull, int cfgProductosFull);
void eliminarDatosFabrica(char nombreFabrica[],
                         char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentes,
                         char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductos,
                         int componentesPorProducto[][MAX_COMPONENTES],
                         float tiemposProduccionPorProducto[],
                         int* cfgFabricaNombrada, int* cfgComponentes, int* cfgProductos,
                         int* cfgCompPorProd, int* cfgTiempos);
void mostrarRestriccionesEcuador();
void mostrarMenuOptimizacion(const char nombreFabrica[]);
void mostrarDatosIngresadosOpt(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                              const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                              const int componentesPorProducto[][MAX_COMPONENTES],
                              const float tiemposProduccion[]);
void ingresarStockComponentes(const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                             int stockComponentes[]);
void inicializarDatosOptimizacionEspecificos(int stockComponentesGlobal[],
                                            char nombreProductoPedidoGlobal[], int* cantidadProductoPedidoGlobal,
                                            float* tiempoLimitePedidoGlobal, int* pedidoActivoGlobal,
                                            int unidadesProducidasPorProductoGlobal[],
                                            float preciosSinImpuestosPorProductoGlobal[],
                                            int preciosAsignadosGlobal[],
                                            int unidadesVendidasPorProductoGlobal[],
                                            float* gananciasTotalesGlobal,
                                            int* numPedidosEnHistorial);
void bucleMenuOptimizacion(int* estadoProgramaPrincipal,
                        char nombreFabricaGlobal[],
                        char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], 
                        int numComponentesIngresadosGlobal,
                        char nombresProductosGlobal[][MAX_NOMBRE_ITEM], 
                        int numProductosIngresadosGlobal,
                        int componentesPorProductoGlobal[][MAX_COMPONENTES],
                        float tiemposProduccionPorProductoGlobal[],
                        int stockComponentesGlobal[],
                        char nombreProductoPedidoGlobal[], 
                        int* cantidadProductoPedidoGlobal,
                        float* tiempoLimitePedidoGlobal, 
                        int* pedidoActivoGlobal,
                        int unidadesProducidasPorProductoGlobal[],
                        float preciosSinImpuestosPorProductoGlobal[],
                        int preciosAsignadosGlobal[],
                        int unidadesVendidasPorProductoGlobal[],
                        float* gananciasTotalesGlobal,
                        char historialPedidosNombres[][MAX_NOMBRE_ITEM],
                        int historialPedidosCantidades[],
                        int* numPedidosEnHistorial,
                        char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                        int cantidadesProductosPedidos[],
                        float tiemposLimitePedidos[],
                        int estadosPedidos[],
                        int* numPedidosActivos);
void ingresarNuevoPedido(const char nombresProductos[][MAX_NOMBRE_ITEM], 
                            int numProductos,
                            char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                            int cantidadesProductosPedidos[],
                            float tiemposLimitePedidos[],
                            int estadosPedidos[],
                            int* numPedidosActivos);
void modificarPedidoActual(char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                         int cantidadesProductosPedidos[],
                         float tiemposLimitePedidos[],
                         int estadosPedidos[],
                         int* numPedidosActivos);
void mostrarPedidosActuales(const char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                          const int cantidadesProductosPedidos[],
                          const float tiemposLimitePedidos[],
                          const int estadosPedidos[],
                          const int numPedidosActivos);  
void eliminarPedidoActual(char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                         int cantidadesProductosPedidos[],
                         float tiemposLimitePedidos[],
                         int estadosPedidos[],
                         int* numPedidosActivos);
void realizarPedido(char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                   int cantidadesProductosPedidos[],
                   float tiemposLimitePedidos[],
                   int estadosPedidos[],
                   int* numPedidosActivos,
                   const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                   const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                   const int componentesPorProducto[][MAX_COMPONENTES],
                   const float tiemposProduccionPorProducto[],
                   int stockComponentes[],
                   int unidadesProducidasPorProducto[],
                   char historialPedidosNombres[][MAX_NOMBRE_ITEM],
                   int historialPedidosCantidades[],
                   int* numPedidosEnHistorial);
void mostrarHistorialPedidos(const char historialPedidosNombres[][MAX_NOMBRE_ITEM],
                             const int historialPedidosCantidades[],
                             int numPedidosEnHistorial);
void ingresarPreciosUnidad(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                           const int unidadesProducidasPorProducto[],
                           float preciosSinImpuestosPorProducto[],
                           int preciosAsignados[]);
void modificarPrecios(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                      const int unidadesProducidasPorProducto[],
                      float preciosSinImpuestosPorProducto[],
                      const int preciosAsignados[]);
void mostrarValorTotalInventario(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                const int unidadesProducidasPorProducto[],
                                const float preciosSinImpuestosPorProducto[],
                                const int preciosAsignados[]);
void calcularPreciosConImpuestos(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                 const int unidadesProducidasPorProducto[],
                                 const float preciosSinImpuestosPorProducto[],
                                 const int preciosAsignados[]);
void venderProductos(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                     int unidadesProducidasPorProducto[],
                     const float preciosSinImpuestosPorProducto[],
                     const int preciosAsignados[],
                     int unidadesVendidasPorProducto[],
                     float* gananciasTotales);
void mostrarGananciasTotales(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                             const int unidadesVendidasPorProducto[],
                             const float preciosSinImpuestosPorProducto[],
                             float gananciasTotales);
void editarNombreFabricaPriv(char nombreFabrica[]);
void editarNombreComponentePriv(char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes);
void editarNombreProductoPriv(char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                           const char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], int numComponentesGlobal,
                           int componentesPorProducto[][MAX_COMPONENTES],
                           float tiemposProduccionPorProducto[]);
void editarValoresComponentesPorProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                         const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                                         int componentesPorProducto[][MAX_COMPONENTES]);
void editarTiempoProduccionMenu(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                 float tiemposProduccionPorProducto[]);
void reemplazarComponente(char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes);
void reemplazarProducto(char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                        const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                        int componentesPorProducto[][MAX_COMPONENTES],
                        float tiemposProduccionPorProducto[],
                        int* cfgCompPorProd, int* cfgTiempos);
int verificarPedidoViable(const char nombreProducto[], int cantidad, float tiempoLimite,
                         int estadoPedido,
                         const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                         const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                         const int componentesPorProducto[][MAX_COMPONENTES],
                         const float tiemposProduccion[],
                         const int stockComponentes[]);
#endif



