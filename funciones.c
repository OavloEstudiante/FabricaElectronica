#include <string.h> 
#include <stdio.h>  
#include "funciones.h"

void limpiarBufferEntradaStdin() {
    int c;
    while ((c = getchar()) != '\n' && c);
}

int leerCadenaValida(const char mensaje[], char destino[], int longitudMax) {
    printf("%s", mensaje);
    if (fgets(destino, longitudMax, stdin) != NULL) {
        destino[strcspn(destino, "\n")] = '\0';
        if (strlen(destino) == 0) {
            printf("Error: La entrada no puede estar vacia. Intente de nuevo.\n");
            return 0;
        }
        if (strlen(destino) == longitudMax - 1 && destino[longitudMax - 2] != '\0') {
            int c;
            int cleared = 0;
            while ((c = getchar()) != '\n' && c) {
                cleared = 1;
            }
        }
        return 1;
    } else {
        printf("Error al leer la entrada. Intente de nuevo.\n");
        clearerr(stdin); // Limpiar el estado de error del stream si es necesario
        return 0;
    }
}

int leerEntero(const char mensaje[]) {
    char buffer[100];
    int valor;
    char extra;
    while (1) {
        if (leerCadenaValida(mensaje, buffer, sizeof(buffer))) {
            if (sscanf(buffer, "%d %c", &valor, &extra) == 1) {
                return valor;
            } else {
                printf("Error: Entrada invalida. Ingrese un numero entero valido. Intente de nuevo.\n");
            }
        }
    }
}

int leerEnteroPositivo(const char mensaje[]) {
    int valor;
    while (1) {
        valor = leerEntero(mensaje);
        if (valor > 0) {
            return valor;
        } else {
            printf("Error: El numero debe ser positivo (>0). Intente de nuevo.\n");
        }
    }
}

int leerEnteroEntreLimites(const char mensaje[], int min, int max) {
    int valor;
    while (1) {
        valor = leerEntero(mensaje);
        if (valor >= min && valor <= max) {
            return valor;
        } else {
            printf("Error: El numero debe estar entre %d y %d. Intente de nuevo.\n", min, max);
        }
    }
}

float leerFlotantePositivo(const char mensaje[]) {
    char buffer[100];
    float valor;
    char extra;
    while (1) {
        if (leerCadenaValida(mensaje, buffer, sizeof(buffer))) {
            if (sscanf(buffer, "%f %c", &valor, &extra) == 1) {
                if (valor > 0.0f) {
                    return valor;
                } else {
                    printf("Error: El valor debe ser positivo (>0.0). Intente de nuevo.\n");
                }
            } else {
                printf("Error: Entrada invalida. Ingrese un numero decimal valido (ej: 10.5). Intente de nuevo.\n");
            }
        }
    }
}

int confirmarAccion(const char mensaje[]) {
    char buffer[10];
    int opcion;
    while(1) {
        printf("%s (1=Si, 0=No): ", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            if (sscanf(buffer, "%d", &opcion) == 1 && (opcion == 0 || opcion == 1)) {
                // Si hay caracteres extra después del número, invalidar
                char extra_char;
                if (sscanf(buffer, "%d %c", &opcion, &extra_char) == 1) {
                    return opcion;
                } else {
                    printf("Error: Entrada invalida. Ingrese solo 1 o 0.\n");
                }
            } else {
                printf("Error: Opcion invalida. Ingrese 1 para Si o 0 para No.\n");
            }
        } else {
            printf("Error al leer la entrada.\n");
            if (feof(stdin)) return 0; // Salir si es EOF
            limpiarBufferEntradaStdin();
        }
    }
}

int buscarIndicePorNombre(const char nombreBuscado[], const char listaNombres[][MAX_NOMBRE_ITEM], int cantidadItems) {
    if (strlen(nombreBuscado) == 0) return -1; // No buscar cadenas vacías
    for (int i = 0; i < cantidadItems; i++) {
        if (strlen(listaNombres[i]) > 0 && strcmp(listaNombres[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void mostrarMenuConfiguracion(const char nombreFabrica[], int cfgFabricaNombrada, int cfgComponentes, int cfgProductos, int cfgCompPorProd, int cfgTiempos) {
    printf("\n--- Menu de Configuracion de Fabrica: %s ---\n", cfgFabricaNombrada ? nombreFabrica : "(Sin Nombre)");
    printf("%s 1. Ingresar nombre de la fabrica\n", cfgFabricaNombrada ? "[OK]" : "[  ]");
    printf("%s 2. Ingresar componentes\n", cfgComponentes ? "[OK]" : "[  ]");
    printf("%s 3. Ingresar productos\n", cfgProductos ? "[OK]" : "[  ]");
    printf("%s 4. Ingresar componentes para cada producto\n", cfgCompPorProd ? "[OK]" : "[  ]");
    printf("%s 5. Ingresar tiempo de produccion por producto\n", cfgTiempos ? "[OK]" : "[  ]");
    printf("-------------------------------------------------\n");
    printf(" 6. Edicion de nombres (fabrica, componente, producto)\n");
    printf(" 7. Edicion de valores (componentes por producto, tiempo de produccion)\n");
    printf(" 8. Reemplazar componente/producto\n"); // Cambiado "Eliminacion" a "Reemplazar"
    printf(" 9. Eliminar todos los datos de la fabrica y reiniciar configuracion\n");
    printf("10. Ver restricciones generales (Ecuador)\n");
    printf("11. Continuar al menu de optimizacion\n");
    printf(" 0. Salir del Programa\n");
}

void ingresarNombreFabrica(char nombreFabrica[]) {
    printf("--- Ingresar Nombre de la Fabrica ---\n");
    while(!leerCadenaValida("Ingrese el nombre de la fabrica: ", nombreFabrica, MAX_NOMBRE_FABRICA));
    printf("Nombre de la fabrica guardado: %s\n", nombreFabrica);
}

void ingresarNombresComponentes(char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentesIngresados) {
    printf("--- Ingresar Nombres de Componentes ---\n");
    printf("Debe ingresar exactamente %d componentes.\n", MAX_COMPONENTES);
    char buffer[MAX_NOMBRE_ITEM + 50]; // Buffer para el mensaje de sprintf
    for (int i = 0; i < MAX_COMPONENTES; i++) {
        int esDuplicado;
        do {
            esDuplicado = 0;
            sprintf(buffer, "Ingrese nombre del Componente %d de %d: ", i + 1, MAX_COMPONENTES);
            while(!leerCadenaValida(buffer, nombresComponentes[i], MAX_NOMBRE_ITEM));

            for (int j = 0; j < i; j++) {
                if (strcmp(nombresComponentes[j], nombresComponentes[i]) == 0) {
                    printf("Error: El componente '%s' ya fue ingresado. Intente con un nombre diferente.\n", nombresComponentes[i]);
                    esDuplicado = 1;
                    break;
                }
            }
        } while (esDuplicado);
        printf("Componente '%s' agregado.\n", nombresComponentes[i]);
    }
    *numComponentesIngresados = MAX_COMPONENTES; // Se llenaron los 5
    printf("Los %d componentes han sido ingresados exitosamente.\n", MAX_COMPONENTES);
}

void ingresarNombresProductos(char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductosIngresados) {
    printf("--- Ingresar Nombres de Productos ---\n");
    printf("Debe ingresar exactamente %d productos.\n", MAX_PRODUCTOS);
    char buffer[MAX_NOMBRE_ITEM + 50];
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        int esDuplicado;
        do {
            esDuplicado = 0;
            sprintf(buffer, "Ingrese nombre del Producto %d de %d: ", i + 1, MAX_PRODUCTOS);
            while(!leerCadenaValida(buffer, nombresProductos[i], MAX_NOMBRE_ITEM));

            for (int j = 0; j < i; j++) {
                if (strcmp(nombresProductos[j], nombresProductos[i]) == 0) {
                    printf("Error: El producto '%s' ya fue ingresado. Intente con un nombre diferente.\n", nombresProductos[i]);
                    esDuplicado = 1;
                    break;
                }
            }
        } while (esDuplicado);
        printf("Producto '%s' agregado.\n", nombresProductos[i]);
    }
    *numProductosIngresados = MAX_PRODUCTOS; // Se llenaron los 5
    printf("Los %d productos han sido ingresados exitosamente.\n", MAX_PRODUCTOS);
}

void ingresarComponentesParaCadaProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                         const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                                         int componentesPorProducto[][MAX_COMPONENTES]) {
    printf("--- Ingresar Componentes por Producto (por unidad) ---\n");
    // No es necesario verificar numProductos < MAX_PRODUCTOS si esta función solo se llama cuando cfgProductosGlobal es true
    // Similar para numComponentes
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("\nConfigurando Producto: %s\n", nombresProductos[i]);
        for (int j = 0; j < MAX_COMPONENTES; j++) {
            char mensaje[MAX_NOMBRE_ITEM * 2 + 100]; // Suficiente espacio
            sprintf(mensaje, "  > Ingrese el numero de '%s' requeridas para fabricar una unidad de '%s' (maximo 5, 0 si no usa): ",
                    nombresComponentes[j], nombresProductos[i]);
            componentesPorProducto[i][j] = leerEnteroEntreLimites(mensaje, 0, 5);
        }
    }
    printf("Componentes para todos los productos ingresados exitosamente.\n");
}

// CORREGIDO: Definición con array 1D para tiemposProduccionPorProducto
void ingresarTiempoProduccionPorProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                         float tiemposProduccionPorProducto[]) {
    printf("--- Ingresar Tiempo de Produccion por Producto (por unidad) ---\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        char mensaje[MAX_NOMBRE_ITEM + 100];
        sprintf(mensaje, "Producto: %s. Ingrese el tiempo de produccion requerido (ej: 2.5 horas): ", nombresProductos[i]);
        tiemposProduccionPorProducto[i] = leerFlotantePositivo(mensaje);
    }
    printf("Tiempos de produccion para todos los productos ingresados exitosamente.\n");
}

void editarNombreFabricaPriv(char nombreFabrica[]) { // Renombrado para evitar conflicto si hay otra
    printf("--- Editar Nombre de la Fabrica ---\n");
    char nombreAntiguo[MAX_NOMBRE_FABRICA];
    strcpy(nombreAntiguo, nombreFabrica);
    while(!leerCadenaValida("Ingrese el nuevo nombre de la fabrica: ", nombreFabrica, MAX_NOMBRE_FABRICA));
    printf("Nombre de la fabrica cambiado de '%s' a '%s'.\n", nombreAntiguo, nombreFabrica);
}

void editarNombreComponentePriv(char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes) {
    printf("--- Editar Nombre de Componente ---\n");
    int cuantosCambiar = leerEnteroEntreLimites("Cuantos nombres de componentes desea cambiar? ", 1, numComponentes);

    for (int k = 0; k < cuantosCambiar; k++) {
        printf("\nModificacion %d de %d:\n", k + 1, cuantosCambiar);
        printf("Componentes actuales:\n");
        for (int i = 0; i < numComponentes; i++) {
            printf("%d. %s\n", i + 1, nombresComponentes[i]);
        }

        char nombreAntiguo[MAX_NOMBRE_ITEM];
        int indiceAntiguo = -1;
        while(indiceAntiguo == -1) {
            while(!leerCadenaValida("Ingrese el nombre EXACTO del componente que desea modificar: ", nombreAntiguo, MAX_NOMBRE_ITEM));
            indiceAntiguo = buscarIndicePorNombre(nombreAntiguo, nombresComponentes, numComponentes);
            if (indiceAntiguo == -1) {
                printf("Error: Componente '%s' no encontrado. Intente de nuevo.\n", nombreAntiguo);
            }
        }

        char nombreNuevo[MAX_NOMBRE_ITEM];
        int esDuplicado;
        do {
            esDuplicado = 0;
            while(!leerCadenaValida("Ingrese el nuevo nombre para el componente: ", nombreNuevo, MAX_NOMBRE_ITEM));
            for (int i = 0; i < numComponentes; i++) {
                if (i != indiceAntiguo && strcmp(nombresComponentes[i], nombreNuevo) == 0) {
                    printf("Error: El nombre '%s' ya existe para otro componente. Intente con uno diferente.\n", nombreNuevo);
                    esDuplicado = 1;
                    break;
                }
            }
        } while(esDuplicado);

        strcpy(nombresComponentes[indiceAntiguo], nombreNuevo);
        printf("Componente '%s' cambiado a '%s' exitosamente.\n", nombreAntiguo, nombreNuevo);
    }
    printf("Cambios de nombres de componentes finalizados.\n");
}

void editarNombreProductoPriv(char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                           const char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], int numComponentesGlobal, // Para referencia
                           int componentesPorProducto[][MAX_COMPONENTES], // Para posible re-ingreso
                           float tiemposProduccionPorProducto[]) { // Para posible re-ingreso
    printf("--- Editar Nombre de Producto ---\n");
    int cuantosCambiar = leerEnteroEntreLimites("Cuantos nombres de productos desea cambiar? ", 1, numProductos);

    for (int k = 0; k < cuantosCambiar; k++) {
        printf("\nModificacion %d de %d:\n", k + 1, cuantosCambiar);
        printf("Productos actuales:\n");
        for (int i = 0; i < numProductos; i++) {
            printf("%d. %s\n", i + 1, nombresProductos[i]);
        }

        char nombreAntiguo[MAX_NOMBRE_ITEM];
        int indiceAntiguo = -1;
        while(indiceAntiguo == -1) {
            while(!leerCadenaValida("Ingrese el nombre EXACTO del producto que desea modificar: ", nombreAntiguo, MAX_NOMBRE_ITEM));
            indiceAntiguo = buscarIndicePorNombre(nombreAntiguo, nombresProductos, numProductos);
            if (indiceAntiguo == -1) {
                printf("Error: Producto '%s' no encontrado. Intente de nuevo.\n", nombreAntiguo);
            }
        }

        char nombreNuevo[MAX_NOMBRE_ITEM];
        int esDuplicado;
        do {
            esDuplicado = 0;
            while(!leerCadenaValida("Ingrese el nuevo nombre para el producto: ", nombreNuevo, MAX_NOMBRE_ITEM));
            for (int i = 0; i < numProductos; i++) {
                if (i != indiceAntiguo && strcmp(nombresProductos[i], nombreNuevo) == 0) {
                    printf("Error: El nombre '%s' ya existe para otro producto. Intente con uno diferente.\n", nombreNuevo);
                    esDuplicado = 1;
                    break;
                }
            }
        } while(esDuplicado);
        
        printf("Producto '%s' cambiado a '%s'.\n", nombreAntiguo, nombreNuevo);
        strcpy(nombresProductos[indiceAntiguo], nombreNuevo);

        if(confirmarAccion("¿Desea reingresar los componentes y el tiempo de produccion para este producto renombrado?")) {
            printf("\nReconfigurando Producto: %s\n", nombresProductos[indiceAntiguo]);
            for (int j = 0; j < numComponentesGlobal; j++) { // Usar numComponentesGlobal
                char mensaje[MAX_NOMBRE_ITEM * 2 + 100];
                sprintf(mensaje, "  > Ingrese el numero de '%s' requeridas para '%s' (maximo 5, 0 si no usa): ",
                        nombresComponentesGlobal[j], nombresProductos[indiceAntiguo]); // Usar nombresComponentesGlobal
                componentesPorProducto[indiceAntiguo][j] = leerEnteroEntreLimites(mensaje, 0, 5);
            }
            char mensajeTiempo[MAX_NOMBRE_ITEM + 100];
            sprintf(mensajeTiempo, "Producto: %s. Ingrese el nuevo tiempo de produccion (ej: 2.5): ", nombresProductos[indiceAntiguo]);
            tiemposProduccionPorProducto[indiceAntiguo] = leerFlotantePositivo(mensajeTiempo);
            printf("Datos para '%s' actualizados.\n", nombresProductos[indiceAntiguo]);
        }
    }
    printf("Cambios de nombres de productos finalizados.\n");
}

void editarNombresMenu(char nombreFabrica[],
                       char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                       char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                       int componentesPorProducto[][MAX_COMPONENTES],
                       float tiemposProduccionPorProducto[],
                       const char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], int numComponentesGlobal) { // nombresComponentesGlobal es referencia
    int opcionEditor;
    do {
        printf("\n--- Menu de Edicion de Nombres ---\n");
        printf("Que nombre desea editar?\n");
        printf("1. Nombre de la fabrica\n");
        printf("2. Nombre del componente\n");
        printf("3. Nombre del producto\n");
        printf("0. Regresar al menu de configuracion\n");
        opcionEditor = leerEnteroEntreLimites("Ingrese su opcion: ", 0, 3);

        switch (opcionEditor) {
            case 1:
                editarNombreFabricaPriv(nombreFabrica);
                break;
            case 2:
                if (numComponentes < MAX_COMPONENTES) { 
                     printf("Error: Primero debe ingresar los %d componentes (Opcion 2 del menu principal).\n", MAX_COMPONENTES);
                } else {
                    editarNombreComponentePriv(nombresComponentes, numComponentes);
                }
                break;
            case 3:
                if (numProductos < MAX_PRODUCTOS) {
                    printf("Error: Primero debe ingresar los %d productos (Opcion 3 del menu principal).\n", MAX_PRODUCTOS);
                } else if (numComponentes < MAX_COMPONENTES) { 
                     printf("Error: Faltan datos de los componentes base para poder reasignarlos si es necesario.\n");
                }
                else {
                    editarNombreProductoPriv(nombresProductos, numProductos,
                                             nombresComponentesGlobal, numComponentesGlobal, // Pasar los componentes globales
                                             componentesPorProducto, tiemposProduccionPorProducto);
                }
                break;
            case 0:
                printf("Regresando al menu de configuracion...\n");
                break;
        }
    } while (opcionEditor != 0);
}

void editarValoresComponentesPorProducto(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                         const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                                         int componentesPorProducto[][MAX_COMPONENTES]) {
    printf("\n--- Editar Numero de Componentes por Producto ---\n");
    do {
        printf("\nProductos y sus componentes (cantidad por unidad):\n");
        for (int i = 0; i < numProductos; i++) {
            printf("Producto: %s\n", nombresProductos[i]);
            for (int j = 0; j < numComponentes; j++) {
                printf("  - %s: %d\n", nombresComponentes[j], componentesPorProducto[i][j]);
            }
        }

        char nombreProdTemp[MAX_NOMBRE_ITEM];
        int idxProd = -1;
        while (idxProd == -1) {
            if (!leerCadenaValida("Ingrese el nombre EXACTO del producto que desee cambiar de valor (o 'cancelar'): ", nombreProdTemp, MAX_NOMBRE_ITEM)) continue;
            if (strcmp(nombreProdTemp, "cancelar") == 0) return;
            idxProd = buscarIndicePorNombre(nombreProdTemp, nombresProductos, numProductos);
            if (idxProd == -1) printf("Producto '%s' no encontrado.\n", nombreProdTemp);
        }

        char nombreCompTemp[MAX_NOMBRE_ITEM];
        int idxComp = -1;
        while (idxComp == -1) {
            if (!leerCadenaValida("Ingrese el nombre EXACTO del componente que desee cambiar de valor para este producto (o 'cancelar'): ", nombreCompTemp, MAX_NOMBRE_ITEM)) continue;
            if (strcmp(nombreCompTemp, "cancelar") == 0) break; // Sale para este producto, preguntará si otro cambio
            idxComp = buscarIndicePorNombre(nombreCompTemp, nombresComponentes, numComponentes);
            if (idxComp == -1) printf("Componente '%s' no encontrado.\n", nombreCompTemp);
        }
        if (idxComp == -1) continue; // Si canceló componente, va al siguiente producto o sale.

        char msgCantidad[200];
        sprintf(msgCantidad, "Ingrese el nuevo numero de '%s' para '%s' (actual: %d, max 5): ",
                nombresComponentes[idxComp], nombresProductos[idxProd], componentesPorProducto[idxProd][idxComp]);
        componentesPorProducto[idxProd][idxComp] = leerEnteroEntreLimites(msgCantidad, 0, 5);
        printf("Valor actualizado.\n");

    } while (confirmarAccion("Desea realizar otro cambio de valor de componentes por producto?"));
    printf("Edicion de numero de componentes por producto finalizada.\n");
}

void editarTiempoProduccionMenu(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                 float tiemposProduccionPorProducto[]) {
    printf("\n--- Editar Tiempo de Produccion por Producto ---\n");
    int cuantosCambiar = leerEnteroEntreLimites("De cuantos productos desea cambiar el tiempo de produccion? ", 1, numProductos);

    for (int k = 0; k < cuantosCambiar; k++) {
        printf("\nModificacion de tiempo %d de %d:\n", k + 1, cuantosCambiar);
        printf("Productos y sus tiempos actuales:\n");
        for (int i = 0; i < numProductos; i++) {
            printf("%d. %s: %.2f\n", i + 1, nombresProductos[i], tiemposProduccionPorProducto[i]);
        }

        char nombreProdTemp[MAX_NOMBRE_ITEM];
        int idxProd = -1;
        while (idxProd == -1) {
            if (!leerCadenaValida("Ingrese el nombre EXACTO del producto que desea modificar el tiempo: ", nombreProdTemp, MAX_NOMBRE_ITEM)) continue;
            idxProd = buscarIndicePorNombre(nombreProdTemp, nombresProductos, numProductos);
            if (idxProd == -1) printf("Producto '%s' no encontrado.\n", nombreProdTemp);
        }
        
        char msgTiempo[MAX_NOMBRE_ITEM + 100];
        sprintf(msgTiempo, "Ingrese el nuevo tiempo de produccion para '%s' (actual: %.2f): ",
                nombresProductos[idxProd], tiemposProduccionPorProducto[idxProd]);
        tiemposProduccionPorProducto[idxProd] = leerFlotantePositivo(msgTiempo);
        printf("Tiempo de produccion para '%s' actualizado.\n", nombresProductos[idxProd]);
    }
    printf("Edicion de tiempos de produccion finalizada.\n");
}


void editarValoresMenu(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                        const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                        int componentesPorProducto[][MAX_COMPONENTES],
                        float tiemposProduccionPorProducto[]) {
    int opcionEditor;
    if (numProductos < MAX_PRODUCTOS || numComponentes < MAX_COMPONENTES) {
        printf("Error: Deben estar definidos todos los productos y componentes primero.\n");
        return;
    }
    do {
        printf("\n--- Menu de Edicion de Valores ---\n");
        printf("Que valor desea editar?\n");
        printf("1. Numero de componentes por cada producto\n");
        printf("2. Tiempo de produccion por producto\n");
        printf("0. Regresar al menu de configuracion\n");
        opcionEditor = leerEnteroEntreLimites("Ingrese su opcion: ", 0, 2);

        switch (opcionEditor) {
            case 1:
                editarValoresComponentesPorProducto(nombresProductos, numProductos,
                                                    nombresComponentes, numComponentes,
                                                    componentesPorProducto);
                break;
            case 2:
                editarTiempoProduccionMenu(nombresProductos, numProductos, tiemposProduccionPorProducto);
                break;
            case 0:
                printf("Regresando al menu de configuracion...\n");
                break;
        }
    } while (opcionEditor != 0);
}


void reemplazarComponente(char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes) {
    printf("\n--- Reemplazar Componente ---\n");
    if (numComponentes == 0) { printf("No hay componentes para reemplazar.\n"); return; }

    printf("Componentes actuales:\n");
    for (int i = 0; i < numComponentes; i++) printf("%d. %s\n", i + 1, nombresComponentes[i]);

    char nombreViejo[MAX_NOMBRE_ITEM];
    int idx = -1;
    while (idx == -1) {
        if (!leerCadenaValida("Ingrese el nombre EXACTO del componente que desea reemplazar: ", nombreViejo, MAX_NOMBRE_ITEM)) continue;
        idx = buscarIndicePorNombre(nombreViejo, nombresComponentes, numComponentes);
        if (idx == -1) printf("Componente '%s' no encontrado.\n", nombreViejo);
    }

    printf("El componente '%s' (en la posicion %d) sera reemplazado.\n", nombresComponentes[idx], idx + 1);
    char nombreNuevo[MAX_NOMBRE_ITEM];
    int esDuplicado;
    do {
        esDuplicado = 0;
        char msgNuevoNombre[MAX_NOMBRE_ITEM + 50];
        sprintf(msgNuevoNombre, "Ingrese el nuevo nombre para el Componente en la posicion %d: ", idx + 1);
        if (!leerCadenaValida(msgNuevoNombre, nombreNuevo, MAX_NOMBRE_ITEM)) continue; // Vuelve a pedir si la lectura falla
        for (int i = 0; i < numComponentes; i++) {
            if (i != idx && strcmp(nombresComponentes[i], nombreNuevo) == 0) {
                printf("Error: El nombre '%s' ya existe para otro componente. Intente diferente.\n", nombreNuevo);
                esDuplicado = 1;
                break;
            }
        }
    } while (esDuplicado);
    strcpy(nombresComponentes[idx], nombreNuevo);
    printf("Componente en la posicion %d reemplazado por '%s'.\n", idx + 1, nombreNuevo);
    printf("Nota: Las cantidades de este componente en los productos ahora se refieren a '%s'.\n", nombreNuevo);
}

void reemplazarProducto(char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                        const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                        int componentesPorProducto[][MAX_COMPONENTES],
                        float tiemposProduccionPorProducto[],
                        int* cfgCompPorProd, int* cfgTiempos) {
    printf("\n--- Reemplazar Producto ---\n");
    if (numProductos == 0) { printf("No hay productos para reemplazar.\n"); return; }

    printf("Productos actuales:\n");
    for (int i = 0; i < numProductos; i++) printf("%d. %s\n", i + 1, nombresProductos[i]);
    
    char nombreViejo[MAX_NOMBRE_ITEM];
    int idx = -1;
    while (idx == -1) {
        if (!leerCadenaValida("Ingrese el nombre EXACTO del producto que desea reemplazar: ", nombreViejo, MAX_NOMBRE_ITEM)) continue;
        idx = buscarIndicePorNombre(nombreViejo, nombresProductos, numProductos);
        if (idx == -1) printf("Producto '%s' no encontrado.\n", nombreViejo);
    }

    printf("El producto '%s' (en la posicion %d) sera reemplazado.\n", nombresProductos[idx], idx + 1);
    char nombreNuevo[MAX_NOMBRE_ITEM];
    int esDuplicado;
    do {
        esDuplicado = 0;
        char msgNuevoNombre[MAX_NOMBRE_ITEM + 50];
        sprintf(msgNuevoNombre, "Ingrese el nuevo nombre para el Producto en la posicion %d: ", idx + 1);
        if (!leerCadenaValida(msgNuevoNombre, nombreNuevo, MAX_NOMBRE_ITEM)) continue;
        for (int i = 0; i < numProductos; i++) {
            if (i != idx && strcmp(nombresProductos[i], nombreNuevo) == 0) {
                printf("Error: El nombre '%s' ya existe para otro producto. Intente diferente.\n", nombreNuevo);
                esDuplicado = 1;
                break;
            }
        }
    } while (esDuplicado);
    strcpy(nombresProductos[idx], nombreNuevo);
    printf("Producto en la posicion %d reemplazado por '%s'.\n", idx + 1, nombreNuevo);
    
    printf("Ahora debe reingresar los componentes y tiempo para el producto '%s'.\n", nombreNuevo);
    printf("\nConfigurando Producto: %s\n", nombresProductos[idx]);
    for (int j = 0; j < numComponentes; j++) {
        char mensaje[MAX_NOMBRE_ITEM * 2 + 100];
        sprintf(mensaje, "  > Ingrese el numero de '%s' requeridas para '%s' (maximo 5): ",
                nombresComponentes[j], nombresProductos[idx]);
        componentesPorProducto[idx][j] = leerEnteroEntreLimites(mensaje, 0, 5);
    }
    
    char mensajeTiempo[MAX_NOMBRE_ITEM + 100];
    sprintf(mensajeTiempo, "Producto: %s. Ingrese el tiempo de produccion requerido (ej: 2.5): ", nombresProductos[idx]);
    tiemposProduccionPorProducto[idx] = leerFlotantePositivo(mensajeTiempo);
    
    printf("Datos para el producto '%s' actualizados.\n", nombreNuevo);
    // Como se reingresaron datos, los flags de configuración para estos podrían considerarse actualizados
    // Si todos los productos y componentes están llenos, cfgCompPorProd y cfgTiempos deberían ser 1.
    // Esta lógica es compleja si solo un producto se reconfigura.
    // Por ahora, asumimos que si se llama a esto, los flags principales de "hay 5 productos/componentes" ya son true.
}


void eliminarElementoMenu(char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentes, // numComponentes es el contador de llenos
                           char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductos,   // numProductos es el contador de llenos
                           int componentesPorProducto[][MAX_COMPONENTES],
                           float tiemposProduccionPorProducto[],
                           int* cfgCompPorProd, int* cfgTiempos, // Para actualizar si se reingresan datos
                           int cfgComponentesFull, int cfgProductosFull) { // Para saber si los arrays base están llenos
    int opcionElim;
    if (!cfgComponentesFull || !cfgProductosFull) {
        printf("Error: Deben estar definidos todos los %d componentes y %d productos primero.\n", MAX_COMPONENTES, MAX_PRODUCTOS);
        return;
    }
    do {
        printf("\n--- Menu de Reemplazo de Elementos ---\n");
        printf("Que desea reemplazar?\n");
        printf("1. Componente\n");
        printf("2. Producto\n");
        printf("0. Regresar al menu de configuracion\n");
        opcionElim = leerEnteroEntreLimites("Ingrese su opcion: ", 0, 2);

        switch (opcionElim) {
            case 1:
                reemplazarComponente(nombresComponentes, *numComponentes); // numComponentes es MAX_COMPONENTES si están llenos
                break;
            case 2:
                reemplazarProducto(nombresProductos, *numProductos, // numProductos es MAX_PRODUCTOS si están llenos
                                   (const char (*)[MAX_NOMBRE_ITEM])nombresComponentes, *numComponentes, // Casting para const, y pasar los componentes base
                                   componentesPorProducto, tiemposProduccionPorProducto,
                                   cfgCompPorProd, cfgTiempos);
                break;
            case 0:
                printf("Regresando al menu de configuracion...\n");
                break;
        }
    } while (opcionElim != 0);
}


void eliminarDatosFabrica(char nombreFabrica[],
                          char nombresComponentes[][MAX_NOMBRE_ITEM], int* numComponentesIngresados,
                          char nombresProductos[][MAX_NOMBRE_ITEM], int* numProductosIngresados,
                          int componentesPorProducto[][MAX_COMPONENTES],
                          float tiemposProduccionPorProducto[], // Cambiado para consistencia
                          int* cfgFabricaNombrada, int* cfgComponentes, int* cfgProductos,
                          int* cfgCompPorProd, int* cfgTiempos) {
    printf("--- Eliminar Todos los Datos de la Fabrica ---\n");
    if (confirmarAccion("Esta seguro que desea eliminar TODOS los datos de configuracion de la fabrica?")) {
        strcpy(nombreFabrica, "");
        for (int i = 0; i < MAX_COMPONENTES; i++) {
            strcpy(nombresComponentes[i], "");
        }
        *numComponentesIngresados = 0;
        for (int i = 0; i < MAX_PRODUCTOS; i++) {
            strcpy(nombresProductos[i], "");
            tiemposProduccionPorProducto[i] = 0.0f; // Usar nombre consistente
            for (int j = 0; j < MAX_COMPONENTES; j++) {
                componentesPorProducto[i][j] = 0;
            }
        }
        *numProductosIngresados = 0;

        *cfgFabricaNombrada = 0;
        *cfgComponentes = 0;
        *cfgProductos = 0;
        *cfgCompPorProd = 0;
        *cfgTiempos = 0;
        printf("Todos los datos de configuracion de la fabrica han sido eliminados.\n");
    } else {
        printf("Operacion cancelada.\n");
    }
}

void mostrarRestriccionesEcuador() {
    printf("\n--- Consideraciones y Restricciones Generales en Ecuador (Ejemplos) ---\n");
    printf("Estos datos son importantes para la fase de optimizacion y calculo de precios finales.\n");
    printf("Recuerde verificar siempre las tasas y regulaciones vigentes, ya que pueden cambiar.\n\n");
    printf("1.  **IVA (Impuesto al Valor Agregado):**\n");
    printf("    Tarifa general actual (Mayo 2024): 15%%. Aplica a la mayoria de bienes y servicios electronicos.\n\n");
    printf("2.  **ICE (Impuesto a los Consumos Especiales):**\n");
    printf("    Podria aplicar a ciertos productos electronicos si son considerados de lujo o caen en categorias especificas.\n    Tarifas variables.\n\n");
    printf("3.  **Impuesto a la Renta (IR):**\n");
    printf("    Las empresas pagan sobre sus utilidades (aprox. 25%% para sociedades, verificar tasa actual).\n\n");
    printf("4.  **RUC (Registro Unico de Contribuyentes):**\n");
    printf("    Indispensable para operar formalmente y emitir facturas.\n\n");
    printf("5.  **Normas Tecnicas (INEN):**\n");
    printf("    Verificar si los productos requieren certificaciones de calidad o seguridad (ej. seguridad electrica).\n\n");
    printf("6.  **Obligaciones Laborales:**\n");
    printf("    Cumplimiento con el Codigo de Trabajo, IESS, etc., si hay empleados.\n\n");
    printf("NOTA: Esta lista es general. Se recomienda asesoria legal y contable especializada.\n");
}

void mostrarMenuOptimizacion(const char nombreFabrica[]) {
    printf("\n--- Menu de Optimizacion: Fabrica %s ---\n", nombreFabrica);
    printf(" 1. Mostrar datos de configuracion ingresados\n");
    printf(" 2. Ingresar/Actualizar stock de componentes\n");
    printf(" 3. Ingresar nuevo pedido de cliente\n");
    printf(" 4. Modificar pedido de cliente actual\n");
    printf(" 5. Mostrar pedido de cliente actual\n");
    printf(" 6. Eliminar pedido de cliente actual\n");
    printf(" 7. Realizar pedido de cliente (verificar viabilidad y actualizar stock)\n");
    printf(" 8. Mostrar historial de pedidos realizados exitosamente\n");
    printf(" 9. Ingresar precios por unidad (sin impuestos) para productos fabricados\n");
    printf("10. Modificar precios de productos fabricados\n");
    printf("11. Mostrar valor total del inventario de productos fabricados (sin impuestos)\n");
    printf("12. Calcular y mostrar precios finales de productos fabricados (con impuestos)\n");
    printf("13. Vender productos fabricados\n");
    printf("14. Mostrar ganancias totales\n");
    printf("15. Eliminar todos los datos de optimizacion (stock, pedidos, ventas)\n");
    printf("16. Regresar al menu de configuracion de fabrica\n");
    printf("17. Salir del Programa\n");
}

void mostrarDatosIngresadosOpt(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                               const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                               const int componentesPorProducto[][MAX_COMPONENTES],
                               const float tiemposProduccion[]) { // Este es tiemposProduccionPorProductoGlobal
    printf("\n--- Datos de Configuracion de la Fabrica ---\n");
    if (numProductos < MAX_PRODUCTOS) { // Debería ser numProductos > 0 o verificar el flag de config
        printf("No hay productos completamente configurados.\n");
        return;
    }

    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        if (strlen(nombresProductos[i]) == 0) continue; // Saltar si el producto no tiene nombre
        printf("\nProducto %d: %s\n", i + 1, nombresProductos[i]);
        printf("  Tiempo de produccion por unidad: %.2f\n", tiemposProduccion[i]);
        printf("  Componentes requeridos por unidad:\n");
        if (numComponentes < MAX_COMPONENTES) {
            printf("    No hay componentes completamente configurados.\n");
        }
        for (int j = 0; j < MAX_COMPONENTES; j++) {
            if (strlen(nombresComponentes[j]) == 0) continue; // Saltar si el componente no tiene nombre
            printf("    - %s: %d unidad(es)\n", nombresComponentes[j], componentesPorProducto[i][j]);
        }
    }
}

void ingresarStockComponentes(const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                              int stockComponentes[]) {
    printf("\n--- Ingresar/Actualizar Stock de Componentes ---\n");
    if (numComponentes < MAX_COMPONENTES) { // Chequea si los 5 componentes base están definidos
        printf("No hay componentes base configurados para ingresar stock.\n");
        return;
    }
    for (int i = 0; i < MAX_COMPONENTES; i++) {
        if (strlen(nombresComponentes[i]) == 0) { // Si un slot de componente está vacío (no debería pasar con la lógica de 5 exactos)
            printf("Advertencia: Componente %d no tiene nombre asignado, no se puede ingresar stock.\n", i + 1);
            continue;
        }
        char mensaje[MAX_NOMBRE_ITEM + 100];
        sprintf(mensaje, "Ingrese cantidad a AGREGAR al stock de '%s' (actual: %d): ", nombresComponentes[i], stockComponentes[i]);
        int cantidadAgregar = leerEnteroEntreLimites(mensaje, 0, 1000000); // Permitir 0 para no agregar
        stockComponentes[i] += cantidadAgregar;
        printf("Nuevo stock de '%s': %d\n", nombresComponentes[i], stockComponentes[i]);
    }
    printf("Stock de componentes actualizado.\n");
}

void inicializarDatosOptimizacionEspecificos(
    int stockComponentesGlobal[],
    char nombreProductoPedidoGlobal[], int* cantidadProductoPedidoGlobal,
    float* tiempoLimitePedidoGlobal, int* pedidoActivoGlobal,
    int unidadesProducidasPorProductoGlobal[],
    float preciosSinImpuestosPorProductoGlobal[],
    int preciosAsignadosGlobal[],
    int unidadesVendidasPorProductoGlobal[],
    float* gananciasTotalesGlobal,
    int* numPedidosEnHistorial) {

    for (int i = 0; i < MAX_COMPONENTES; i++) {
        stockComponentesGlobal[i] = 0;
    }
    strcpy(nombreProductoPedidoGlobal, "");
    *cantidadProductoPedidoGlobal = 0;
    *tiempoLimitePedidoGlobal = 0.0f;
    *pedidoActivoGlobal = 0;
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        unidadesProducidasPorProductoGlobal[i] = 0;
        preciosSinImpuestosPorProductoGlobal[i] = 0.0f;
        preciosAsignadosGlobal[i] = 0;
        unidadesVendidasPorProductoGlobal[i] = 0;
    }
    *gananciasTotalesGlobal = 0.0f;
    *numPedidosEnHistorial = 0;
    // No se borran los nombres de historialPedidosNombres ni cantidades aquí,
    // solo el contador. Se sobreescribirán.
}

void bucleMenuOptimizacion(int* estadoProgramaPrincipal,
                            char nombreFabricaGlobal[],
                            char nombresComponentesGlobal[][MAX_NOMBRE_ITEM], int numComponentesIngresadosGlobal,
                            char nombresProductosGlobal[][MAX_NOMBRE_ITEM], int numProductosIngresadosGlobal,
                            int componentesPorProductoGlobal[][MAX_COMPONENTES],
                            float tiemposProduccionPorProductoGlobal[],
                            int stockComponentesGlobal[],
                            char nombreProductoPedidoGlobal[], int* cantidadProductoPedidoGlobal,
                            float* tiempoLimitePedidoGlobal, int* pedidoActivoGlobal,
                            int unidadesProducidasPorProductoGlobal[],
                            float preciosSinImpuestosPorProductoGlobal[],
                            int preciosAsignadosGlobal[],
                            int unidadesVendidasPorProductoGlobal[],
                            float* gananciasTotalesGlobal,
                            char historialPedidosNombres[][MAX_NOMBRE_ITEM],
                            int historialPedidosCantidades[],
                            int* numPedidosEnHistorial,
                            // Nuevos parámetros:
                            char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                            int cantidadesProductosPedidos[],
                            float tiemposLimitePedidos[],
                            int estadosPedidos[],
                            int* numPedidosActivos) {
    int opcionOpt = -1;
    printf("\nVamos a optimizar la fabrica: %s\n", nombreFabricaGlobal);

    do {
        mostrarMenuOptimizacion(nombreFabricaGlobal);
        opcionOpt = leerEnteroEntreLimites("Ingrese su opcion: ", 1, 17);

        switch (opcionOpt) {
            case 1:
                mostrarDatosIngresadosOpt(nombresProductosGlobal, numProductosIngresadosGlobal,
                                         nombresComponentesGlobal, numComponentesIngresadosGlobal,
                                         componentesPorProductoGlobal,
                                         tiemposProduccionPorProductoGlobal);
                break;
            case 2:
                if (numComponentesIngresadosGlobal < MAX_COMPONENTES) {
                    printf("Error: Los componentes base no han sido completamente configurados en el menu anterior.\n");
                } else {
                    ingresarStockComponentes(nombresComponentesGlobal, numComponentesIngresadosGlobal, stockComponentesGlobal);
                }
                break;
            case 3:
                ingresarNuevoPedido(nombresProductosGlobal, 
                                    numProductosIngresadosGlobal,
                                    nombresProductosPedidos,  // <-- Usa el parámetro recibido, no la variable global
                                    cantidadesProductosPedidos,
                                    tiemposLimitePedidos,
                                    estadosPedidos,
                                    numPedidosActivos);
                break;
            case 4:
                modificarPedidoActual(nombresProductosGlobal, cantidadesProductosPedidos,
                                    tiemposLimitePedidos, estadosPedidos,
                                    numPedidosActivos);
                break;
            case 5:
                mostrarPedidosActuales(nombresProductosPedidos, cantidadesProductosPedidos,
                                    tiemposLimitePedidos, estadosPedidos,
                                    *numPedidosActivos);
                break;
            case 6:
                eliminarPedidoActual(nombresProductosPedidos, cantidadesProductosPedidos,
                                    tiemposLimitePedidos, estadosPedidos,
                                    numPedidosActivos);
                break;
            case 7:
                realizarPedido(nombresProductosPedidos, cantidadesProductosPedidos,
                            tiemposLimitePedidos, estadosPedidos,
                            numPedidosActivos,
                            nombresProductosGlobal, numProductosIngresadosGlobal,
                            nombresComponentesGlobal, numComponentesIngresadosGlobal,
                            componentesPorProductoGlobal, tiemposProduccionPorProductoGlobal,
                            stockComponentesGlobal,
                            unidadesProducidasPorProductoGlobal,
                            historialPedidosNombres, historialPedidosCantidades,
                            numPedidosEnHistorial);  // Sin & porque ya es un puntero
                break;
            case 8:
                mostrarHistorialPedidos(historialPedidosNombres, historialPedidosCantidades,
                                       *numPedidosEnHistorial);
                break;
            case 9:
                ingresarPreciosUnidad(nombresProductosGlobal, numProductosIngresadosGlobal,
                                     unidadesProducidasPorProductoGlobal,
                                     preciosSinImpuestosPorProductoGlobal,
                                     preciosAsignadosGlobal);
                break;
            case 10:
                modificarPrecios(nombresProductosGlobal, numProductosIngresadosGlobal,
                                unidadesProducidasPorProductoGlobal,
                                preciosSinImpuestosPorProductoGlobal,
                                preciosAsignadosGlobal);
                break;
            case 11:
                mostrarValorTotalInventario(nombresProductosGlobal, numProductosIngresadosGlobal,
                                          unidadesProducidasPorProductoGlobal,
                                          preciosSinImpuestosPorProductoGlobal,
                                          preciosAsignadosGlobal);
                break;
            case 12:
                calcularPreciosConImpuestos(nombresProductosGlobal, numProductosIngresadosGlobal,
                                          unidadesProducidasPorProductoGlobal,
                                          preciosSinImpuestosPorProductoGlobal,
                                          preciosAsignadosGlobal);
                break;
            case 13:
                venderProductos(nombresProductosGlobal, numProductosIngresadosGlobal,
                              unidadesProducidasPorProductoGlobal,
                              preciosSinImpuestosPorProductoGlobal,
                              preciosAsignadosGlobal,
                              unidadesVendidasPorProductoGlobal,
                              gananciasTotalesGlobal);
                break;
            case 14:
                mostrarGananciasTotales(nombresProductosGlobal, numProductosIngresadosGlobal,
                                      unidadesVendidasPorProductoGlobal,
                                      preciosSinImpuestosPorProductoGlobal,
                                      *gananciasTotalesGlobal);
                break;
            case 15:
                if(confirmarAccion("Esta seguro que desea eliminar TODOS los datos de optimizacion?")) {
                    inicializarDatosOptimizacionEspecificos(
                        stockComponentesGlobal,
                        nombreProductoPedidoGlobal, cantidadProductoPedidoGlobal,
                        tiempoLimitePedidoGlobal, pedidoActivoGlobal,
                        unidadesProducidasPorProductoGlobal,
                        preciosSinImpuestosPorProductoGlobal,
                        preciosAsignadosGlobal,
                        unidadesVendidasPorProductoGlobal,
                        gananciasTotalesGlobal,
                        numPedidosEnHistorial);
                    printf("Datos de optimizacion eliminados.\n");
                } else {
                    printf("Operacion cancelada.\n");
                }
                break;
            case 16:
                printf("Regresando al menu de configuracion de fabrica...\n");
                *estadoProgramaPrincipal = 1; // Indicar a main que cambie de estado
                return;
            case 17:
                printf("Entendido, tenga un lindo dia.\n");
                *estadoProgramaPrincipal = 0; // Indicar a main que salga del programa
                return;
        }
         if (opcionOpt != 16 && opcionOpt != 17) {
             printf("\nPresione Enter para continuar...");
             getchar();
        }
    } while (opcionOpt != 16 && opcionOpt != 17);
}

// Función para ingresar un nuevo pedido de cliente
void ingresarNuevoPedido(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                         char nombresProductosPedidos[][MAX_NOMBRE_ITEM], 
                         int cantidadesProductosPedidos[],
                         float tiemposLimitePedidos[],
                         int estadosPedidos[],
                         int* numPedidosActivos) {
    printf("\n--- Ingresar Nuevo Pedido ---\n");
    
    if (*numPedidosActivos >= MAX_PEDIDOS) {
        printf("Error: Has alcanzado el máximo número de pedidos (%d).\n", MAX_PEDIDOS);
        return;
    }
    
    // Mostrar productos disponibles
    printf("Productos disponibles:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("- %s\n", nombresProductos[i]);
    }
    
    // Pedir nombre del producto
    char nombreProducto[MAX_NOMBRE_ITEM];
    int indiceProducto = -1;
    while (indiceProducto == -1) {
        if (!leerCadenaValida("\nIngrese el nombre EXACTO del producto a realizar: ", 
                             nombreProducto, MAX_NOMBRE_ITEM)) {
            continue;
        }
        
        indiceProducto = buscarIndicePorNombre(nombreProducto, nombresProductos, numProductos);
        if (indiceProducto == -1) {
            printf("Error: Producto '%s' no encontrado. Intente de nuevo.\n", nombreProducto);
        }
    }
    
    // Pedir cantidad
    char mensajeCantidad[100];
    sprintf(mensajeCantidad, "Ingrese el numero de %s a realizar: ", nombreProducto);
    int cantidad = leerEnteroPositivo(mensajeCantidad);
    
    // Pedir tiempo
    char mensajeTiempo[100];
    sprintf(mensajeTiempo, "Ingrese el tiempo para realizar el pedido de %s: ", nombreProducto);
    float tiempo = leerFlotantePositivo(mensajeTiempo);
    
    // Guardar el pedido
    int indicePedido = *numPedidosActivos;
    strcpy(nombresProductosPedidos[indicePedido], nombreProducto);
    cantidadesProductosPedidos[indicePedido] = cantidad;
    tiemposLimitePedidos[indicePedido] = tiempo;
    estadosPedidos[indicePedido] = 1;
    (*numPedidosActivos)++;
    
    printf("Pedido ingresado exitosamente.\n");
}

void mostrarPedidosActuales(const char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                           const int cantidadesProductosPedidos[],
                           const float tiemposLimitePedidos[],
                           const int estadosPedidos[],
                           const int numPedidosActivos) {
    printf("\n--- Pedidos Actuales ---\n");
    
    if (numPedidosActivos == 0) {
        printf("No hay pedidos activos.\n");
        return;
    }
    
    printf("%-5s %-30s %-15s %-15s\n", "No.", "Producto", "Cantidad", "Tiempo limite");
    printf("----- ------------------------------ -------------- --------------\n");
    
    for (int i = 0; i < numPedidosActivos; i++) {
        if (estadosPedidos[i]) {
            printf("%-5d %-30s %-15d %-15.2f\n", i+1, 
                   nombresProductosPedidos[i], 
                   cantidadesProductosPedidos[i], 
                   tiemposLimitePedidos[i]);
        }
    }
}

int seleccionarPedido(const char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                     const int estadosPedidos[],
                     int numPedidosActivos) {
    if (numPedidosActivos == 0) {
        printf("No hay pedidos para seleccionar.\n");
        return -1;
    }
    
    mostrarPedidosActuales(nombresProductosPedidos, NULL, NULL, estadosPedidos, numPedidosActivos);
    
    int opcion = leerEnteroEntreLimites("\nSeleccione el numero del pedido (0 para cancelar): ", 
                                       0, numPedidosActivos);
    
    if (opcion == 0) return -1;
    
    return opcion - 1; // Convertir a índice base 0
}

void modificarPedidoActual(char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                         int cantidadesProductosPedidos[],
                         float tiemposLimitePedidos[],
                         int estadosPedidos[],
                         int* numPedidosActivos) {
    printf("\n--- Modificar Pedido Actual ---\n");
    
    if (*numPedidosActivos == 0) {
        printf("No hay pedidos para modificar.\n");
        return;
    }
    
    // Mostrar lista de pedidos disponibles para modificar
    printf("Pedidos actuales:\n");
    for (int i = 0; i < *numPedidosActivos; i++) {
        printf("%d. %s - Cantidad: %d - Tiempo: %.2f\n", 
               i+1, nombresProductosPedidos[i], 
               cantidadesProductosPedidos[i], 
               tiemposLimitePedidos[i]);
    }
    
    int opcion = leerEnteroEntreLimites("\nSeleccione el número del pedido a modificar (0 para cancelar): ", 
                                      0, *numPedidosActivos);
    if (opcion == 0) {
        printf("Operación cancelada.\n");
        return;
    }
    
    int indice = opcion - 1;
    
    // Modificar cantidad
    char mensajeCantidad[100];
    sprintf(mensajeCantidad, "\nIngrese el nuevo número de %s a realizar (actual: %d): ",
            nombresProductosPedidos[indice], cantidadesProductosPedidos[indice]);
    cantidadesProductosPedidos[indice] = leerEnteroPositivo(mensajeCantidad);
    
    // Modificar tiempo
    char mensajeTiempo[100];
    sprintf(mensajeTiempo, "Ingrese el nuevo tiempo para realizar el pedido de %s (actual: %.2f): ",
            nombresProductosPedidos[indice], tiemposLimitePedidos[indice]);
    tiemposLimitePedidos[indice] = leerFlotantePositivo(mensajeTiempo);
    
    printf("Modificación exitosa.\n");
}

void eliminarPedidoActual(char nombresProductosPedidos[][MAX_NOMBRE_ITEM],
                         int cantidadesProductosPedidos[],
                         float tiemposLimitePedidos[],
                         int estadosPedidos[],
                         int* numPedidosActivos) {
    printf("\n--- Eliminar Pedido Actual ---\n");
    
    if (*numPedidosActivos == 0) {
        printf("No hay pedidos para eliminar.\n");
        return;
    }
    
    // Mostrar lista de pedidos
    printf("Pedidos actuales:\n");
    for (int i = 0; i < *numPedidosActivos; i++) {
        printf("%d. %s - Cantidad: %d - Tiempo: %.2f\n", 
               i+1, nombresProductosPedidos[i], 
               cantidadesProductosPedidos[i], 
               tiemposLimitePedidos[i]);
    }
    
    int opcion = leerEnteroEntreLimites("\nSeleccione el número del pedido a eliminar (0 para cancelar): ", 
                                      0, *numPedidosActivos);
    if (opcion == 0) {
        printf("Operación cancelada.\n");
        return;
    }
    
    int indice = opcion - 1;
    
    if (confirmarAccion("¿Está seguro que desea eliminar este pedido?")) {
        // Desplazar los pedidos posteriores
        for (int i = indice; i < *numPedidosActivos - 1; i++) {
            strcpy(nombresProductosPedidos[i], nombresProductosPedidos[i+1]);
            cantidadesProductosPedidos[i] = cantidadesProductosPedidos[i+1];
            tiemposLimitePedidos[i] = tiemposLimitePedidos[i+1];
            estadosPedidos[i] = estadosPedidos[i+1];
        }
        
        (*numPedidosActivos)--;
        printf("Pedido eliminado exitosamente.\n");
    } else {
        printf("Operación cancelada.\n");
    }
}

int verificarPedidoViable(const char nombreProducto[], int cantidad, float tiempoLimite,
                         int estadoPedido,
                         const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                         const char nombresComponentes[][MAX_NOMBRE_ITEM], int numComponentes,
                         const int componentesPorProducto[][MAX_COMPONENTES],
                         const float tiemposProduccion[],
                         const int stockComponentes[]) {
    // Implementación básica - debes completar según tu lógica
    if (estadoPedido != 1) return 0;
    
    int indiceProducto = buscarIndicePorNombre(nombreProducto, nombresProductos, numProductos);
    if (indiceProducto == -1) return 0;
    
    // Verificar tiempo de producción
    float tiempoTotal = tiemposProduccion[indiceProducto] * cantidad;
    if (tiempoTotal > tiempoLimite) return 0;
    
    for (int i = 0; i < numComponentes; i++) {
        int requeridos = componentesPorProducto[indiceProducto][i] * cantidad;
        if (stockComponentes[i] < requeridos) return 0;
    }
    
    return 1;
}
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
                   int* numPedidosEnHistorial) {
    printf("\n--- Realizar Pedido ---\n");
    
    if (*numPedidosActivos == 0) {
        printf("No hay pedidos para realizar.\n");
        return;
    }
    
    // Mostrar lista de pedidos
    printf("Pedidos actuales:\n");
    for (int i = 0; i < *numPedidosActivos; i++) {
        printf("%d. %s - Cantidad: %d - Tiempo: %.2f\n", 
               i+1, nombresProductosPedidos[i], 
               cantidadesProductosPedidos[i], 
               tiemposLimitePedidos[i]);
    }
    
    int opcion = leerEnteroEntreLimites("\nSeleccione el número del pedido a realizar (0 para cancelar): ", 
                                      0, *numPedidosActivos);
    if (opcion == 0) {
        printf("Operación cancelada.\n");
        return;
    }
    
    int indice = opcion - 1;
    
    // Verificar viabilidad
    int indiceProducto = buscarIndicePorNombre(nombresProductosPedidos[indice], 
                              nombresProductos, numProductos);
    if (indiceProducto == -1) {
        printf("Error: Producto no encontrado.\n");
        return;
    }
    
    // Verificar tiempo
    float tiempoNecesario = tiemposProduccionPorProducto[indiceProducto] * cantidadesProductosPedidos[indice];
    if (tiempoNecesario > tiemposLimitePedidos[indice]) {
        printf("No es viable en dicho tiempo realizar el pedido. Tiempo necesario: %.2f (Tiempo disponible: %.2f)\n",
              tiempoNecesario, tiemposLimitePedidos[indice]);
        printf("Debe cambiar el parámetro del pedido.\n");
        return;
    }
    
    // Verificar componentes
    for (int i = 0; i < numComponentes; i++) {
        int requeridos = componentesPorProducto[indiceProducto][i] * cantidadesProductosPedidos[indice];
        if (stockComponentes[i] < requeridos) {
            printf("No es viable debido a que faltan %d unidades de %s (necesarias: %d, disponibles: %d)\n",
                  requeridos - stockComponentes[i], nombresComponentes[i], requeridos, stockComponentes[i]);
            printf("Debe reabastecer o modificar el pedido.\n");
            return;
        }
    }
    
    // Confirmar pedido
    if (!confirmarAccion("El pedido es viable. ¿Desea confirmar el pedido?")) {
        printf("Pedido cancelado.\n");
        return;
    }
    
    // Actualizar stock
    for (int i = 0; i < numComponentes; i++) {
        int requeridos = componentesPorProducto[indiceProducto][i] * cantidadesProductosPedidos[indice];
        stockComponentes[i] -= requeridos;
    }
    
    // Actualizar unidades producidas
    unidadesProducidasPorProducto[indiceProducto] += cantidadesProductosPedidos[indice];
    
    // Agregar al historial
    if (*numPedidosEnHistorial < MAX_ITEMS_PEDIDOS_HISTORIAL) {
        strcpy(historialPedidosNombres[*numPedidosEnHistorial], nombresProductosPedidos[indice]);
        historialPedidosCantidades[*numPedidosEnHistorial] = cantidadesProductosPedidos[indice];
        (*numPedidosEnHistorial)++;
    }
    
    // Eliminar el pedido de la lista de activos
    for (int i = indice; i < *numPedidosActivos - 1; i++) {
        strcpy(nombresProductosPedidos[i], nombresProductosPedidos[i+1]);
        cantidadesProductosPedidos[i] = cantidadesProductosPedidos[i+1];
        tiemposLimitePedidos[i] = tiemposLimitePedidos[i+1];
        estadosPedidos[i] = estadosPedidos[i+1];
    }
    
    (*numPedidosActivos)--;
    printf("Pedido realizado exitosamente. Stock actualizado.\n");
}

// Función para mostrar historial de pedidos
void mostrarHistorialPedidos(const char historialPedidosNombres[][MAX_NOMBRE_ITEM],
                             const int historialPedidosCantidades[],
                             int numPedidosEnHistorial) {
    printf("\n--- Historial de Pedidos Realizados Exitosamente ---\n");
    
    if (numPedidosEnHistorial == 0) {
        printf("No hay pedidos en el historial.\n");
        return;
    }
    
    printf("%-30s %-15s\n", "Producto", "Cantidad");
    printf("-------------------------------- --------\n");
    for (int i = 0; i < numPedidosEnHistorial; i++) {
        printf("%-30s %-15d\n", historialPedidosNombres[i], historialPedidosCantidades[i]);
    }
}

// Función para ingresar precios por unidad
void ingresarPreciosUnidad(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                           const int unidadesProducidasPorProducto[],
                           float preciosSinImpuestosPorProducto[],
                           int preciosAsignados[]) {
    printf("\n--- Ingresar Precios por Unidad (sin impuestos) ---\n");
    
    for (int i = 0; i < numProductos; i++) {
        if (unidadesProducidasPorProducto[i] > 0) {
            char mensaje[100];
            sprintf(mensaje, "Ingrese el precio de %s (unidades producidas: %d): ", 
                    nombresProductos[i], unidadesProducidasPorProducto[i]);
            preciosSinImpuestosPorProducto[i] = leerFlotantePositivo(mensaje);
            preciosAsignados[i] = 1;
        }
    }
    printf("Precios ingresados exitosamente.\n");
}

// Función para modificar precios
void modificarPrecios(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                      const int unidadesProducidasPorProducto[],
                      float preciosSinImpuestosPorProducto[],
                      const int preciosAsignados[]) {
    printf("\n--- Modificar Precios ---\n");
    
    // Mostrar productos con precios
    printf("Productos con precios asignados:\n");
    printf("%-30s %-15s %-15s\n", "Producto", "Unidades", "Precio Unitario");
    printf("-------------------------------- -------- --------------\n");
    
    int hayProductos = 0;
    for (int i = 0; i < numProductos; i++) {
        if (unidadesProducidasPorProducto[i] > 0 && preciosAsignados[i]) {
            printf("%-30s %-15d %-15.2f\n", nombresProductos[i], 
                   unidadesProducidasPorProducto[i], preciosSinImpuestosPorProducto[i]);
            hayProductos = 1;
        }
    }
    
    if (!hayProductos) {
        printf("No hay productos con precios asignados.\n");
        return;
    }
    
    // Pedir producto a modificar
    char nombreProducto[MAX_NOMBRE_ITEM];
    int indiceProducto = -1;
    while (indiceProducto == -1) {
        if (!leerCadenaValida("\nIngrese el nombre EXACTO del producto que desea modificar el precio: ", 
                             nombreProducto, MAX_NOMBRE_ITEM)) {
            continue;
        }
        
        indiceProducto = buscarIndicePorNombre(nombreProducto, nombresProductos, numProductos);
        if (indiceProducto == -1 || unidadesProducidasPorProducto[indiceProducto] == 0 || !preciosAsignados[indiceProducto]) {
            printf("Error: Producto '%s' no encontrado o sin precio asignado. Intente de nuevo.\n", nombreProducto);
            indiceProducto = -1;
        }
    }
    
    // Modificar precio
    char mensaje[100];
    sprintf(mensaje, "Ingrese el nuevo precio de %s (actual: %.2f): ", 
            nombresProductos[indiceProducto], preciosSinImpuestosPorProducto[indiceProducto]);
    preciosSinImpuestosPorProducto[indiceProducto] = leerFlotantePositivo(mensaje);
    
    printf("Precio modificado exitosamente.\n");
}

// Función para mostrar valor total del inventario (sin impuestos)
void mostrarValorTotalInventario(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                const int unidadesProducidasPorProducto[],
                                const float preciosSinImpuestosPorProducto[],
                                const int preciosAsignados[]) {
    printf("\n--- Valor Total del Inventario (sin impuestos) ---\n");
    
    printf("%-30s %-15s %-15s %-15s\n", "Producto", "Unidades", "Precio Unitario", "Valor Total");
    printf("-------------------------------- -------- -------------- --------------\n");
    
    float valorTotalGeneral = 0.0f;
    int hayProductos = 0;
    
    for (int i = 0; i < numProductos; i++) {
        if (unidadesProducidasPorProducto[i] > 0 && preciosAsignados[i]) {
            float valorTotal = unidadesProducidasPorProducto[i] * preciosSinImpuestosPorProducto[i];
            printf("%-30s %-15d %-15.2f %-15.2f\n", nombresProductos[i], 
                   unidadesProducidasPorProducto[i], preciosSinImpuestosPorProducto[i], valorTotal);
            valorTotalGeneral += valorTotal;
            hayProductos = 1;
        }
    }
    
    if (!hayProductos) {
        printf("No hay productos en el inventario.\n");
        return;
    }
    
    printf("\nValor total del inventario: %.2f\n", valorTotalGeneral);
}

// Función para calcular precios con impuestos
void calcularPreciosConImpuestos(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                                 const int unidadesProducidasPorProducto[],
                                 const float preciosSinImpuestosPorProducto[],
                                 const int preciosAsignados[]) {
    printf("\n--- Precios con Impuestos ---\n");
    
    // Restricciones de Ecuador
    const float IVA = 0.15f;       // 15% IVA
    const float ICE = 0.05f;       // 5% ICE (ejemplo para productos electrónicos)
    const float otrosImpuestos = 0.03f; // 3% otros impuestos
    
    printf("Consideraciones fiscales aplicadas:\n");
    printf("- IVA (15%%)\n");
    printf("- ICE (5%% para productos electronicos)\n");
    printf("- Otros impuestos (3%%)\n");
    printf("Total de impuestos aplicados: 23%%\n\n");
    
    printf("%-30s %-15s %-15s %-15s\n", "Producto", "Precio sin imp.", "Impuestos", "Precio final");
    printf("-------------------------------- -------------- ----------- --------------\n");
    
    int hayProductos = 0;
    
    for (int i = 0; i < numProductos; i++) {
        if (unidadesProducidasPorProducto[i] > 0 && preciosAsignados[i]) {
            float impuestos = preciosSinImpuestosPorProducto[i] * (IVA + ICE + otrosImpuestos);
            float precioFinal = preciosSinImpuestosPorProducto[i] + impuestos;
            
            printf("%-30s %-15.2f %-15.2f %-15.2f\n", nombresProductos[i], 
                   preciosSinImpuestosPorProducto[i], impuestos, precioFinal);
            
            hayProductos = 1;
        }
    }
    
    if (!hayProductos) {
        printf("No hay productos con precios asignados.\n");
    }
}

// Función para vender productos
void venderProductos(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                     int unidadesProducidasPorProducto[],
                     const float preciosSinImpuestosPorProducto[],
                     const int preciosAsignados[],
                     int unidadesVendidasPorProducto[],
                     float* gananciasTotales) {
    printf("\n--- Vender Productos ---\n");
    
    // Mostrar productos disponibles para vender
    printf("Productos disponibles para vender:\n");
    printf("%-5s %-30s %-15s %-15s\n", "No.", "Producto", "Disponibles", "Precio unitario");
    printf("----- ------------------------------ -------------- --------------\n");
    
    int productosDisponibles[MAX_PRODUCTOS] = {0};
    int count = 0;
    
    for (int i = 0; i < numProductos; i++) {
        if (unidadesProducidasPorProducto[i] > 0 && preciosAsignados[i]) {
            printf("%-5d %-30s %-15d %-15.2f\n", count + 1, nombresProductos[i], 
                   unidadesProducidasPorProducto[i], preciosSinImpuestosPorProducto[i]);
            productosDisponibles[count] = i;
            count++;
        }
    }
    
    if (count == 0) {
        printf("No hay productos disponibles para vender.\n");
        return;
    }
    
    // Seleccionar producto
    int opcion = leerEnteroEntreLimites("\nSeleccione el numero del producto a vender (0 para cancelar): ", 0, count);
    if (opcion == 0) {
        printf("Operacion cancelada.\n");
        return;
    }
    
    int indiceProducto = productosDisponibles[opcion - 1];
    
    // Cantidad a vender
    char mensaje[100];
    sprintf(mensaje, "Ingrese el numero de %s a vender (max %d): ", 
            nombresProductos[indiceProducto], unidadesProducidasPorProducto[indiceProducto]);
    int cantidad = leerEnteroEntreLimites(mensaje, 1, unidadesProducidasPorProducto[indiceProducto]);
    
    // Calcular total
    float total = cantidad * preciosSinImpuestosPorProducto[indiceProducto];
    printf("\nResumen de venta:\n");
    printf("- Producto: %s\n", nombresProductos[indiceProducto]);
    printf("- Cantidad: %d\n", cantidad);
    printf("- Precio unitario: %.2f\n", preciosSinImpuestosPorProducto[indiceProducto]);
    printf("- Total: %.2f\n", total);
    
    if (!confirmarAccion("Confirmar venta?")) {
        printf("Venta cancelada.\n");
        return;
    }
    
    // Actualizar inventario y ganancias
    unidadesProducidasPorProducto[indiceProducto] -= cantidad;
    unidadesVendidasPorProducto[indiceProducto] += cantidad;
    *gananciasTotales += total;
    
    printf("Venta realizada exitosamente.\n");
}

// Función para mostrar ganancias totales
void mostrarGananciasTotales(const char nombresProductos[][MAX_NOMBRE_ITEM], int numProductos,
                             const int unidadesVendidasPorProducto[],
                             const float preciosSinImpuestosPorProducto[],
                             float gananciasTotales) {
    printf("\n--- Ganancias Totales ---\n");
    
    printf("%-30s %-15s %-15s %-15s\n", "Producto", "Unidades vendidas", "Precio unitario", "Total");
    printf("-------------------------------- ---------------- -------------- --------------\n");
    
    int hayVentas = 0;
    float totalCalculado = 0.0f;
    
    for (int i = 0; i < numProductos; i++) {
        if (unidadesVendidasPorProducto[i] > 0) {
            float totalProducto = unidadesVendidasPorProducto[i] * preciosSinImpuestosPorProducto[i];
            printf("%-30s %-17d %-15.2f %-15.2f\n", nombresProductos[i], 
                   unidadesVendidasPorProducto[i], preciosSinImpuestosPorProducto[i], totalProducto);
            totalCalculado += totalProducto;
            hayVentas = 1;
        }
    }
    
    if (!hayVentas) {
        printf("No hay ventas registradas.\n");
        return;
    }
    
    printf("\nGanancias totales: %.2f\n", gananciasTotales);
    
    if (totalCalculado != gananciasTotales) {
        printf("Advertencia: Las ganancias totales no coinciden con la suma de ventas.\n");
    }
}