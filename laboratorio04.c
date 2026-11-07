#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* =====================================================
   PREGUNTA 1: Procesamiento concurrente de pedidos
   ===================================================== */

void pregunta1() {

    double monto = 250.0;
    int cantidad = 10;

    printf("[INICIO] PID=%d\n", getpid());
    fflush(stdout);

    // TODO 1: Crear un proceso hijo utilizando fork().
    // TODO 2: Gestionar el error de creación.
    // TODO 3: Implementar las operaciones del proceso hijo
    //         (monto += 50, esperar 1 segundo, imprimir PID y monto).
    // TODO 4: Implementar las operaciones del proceso padre
    //         (cantidad += 5, imprimir PID y cantidad).
    // TODO 5: Explicar en un comentario por qué el hijo
    //         no modifica las variables del padre.
}

/* =====================================================
   PREGUNTA 2: Supervisión de una tarea de respaldo
   ===================================================== */
void pregunta2() {

    pid_t pid = fork();
    int status;
    if (pid == ...) {
        perror("fork");
        return;
    }
    if (pid == ...) {
        printf("[HIJO] Iniciando respaldo...\n");
        sleep(2);
        // TODO: Terminar el proceso con código 0.
    } else {
        printf("[PADRE] Esperando finalización del respaldo...\n");
        // TODO: Esperar al hijo mediante waitpid().
        // TODO: Comprobar si waitpid() falló.
        // TODO: Comprobar si el hijo terminó normalmente.
        // TODO: Obtener e imprimir el código de salida.
        // TODO: Mostrar si el respaldo fue exitoso o falló.
    }
}

/* =====================================================
   PREGUNTA 3: Diagnóstico del sistema mediante execvp()
   ===================================================== */

void pregunta3() {

    pid_t pid;
    int status;
    char *argumentos[] = {
        // TODO: Completar los argumentos para uname -a.
        //       (recuerde qué va en la primera posición, argv[0])
        NULL
    };
    pid = fork();
    if (pid == ...) {
        perror("fork");
        return;
    }
    if (pid == ...) {
        printf("[HIJO] Consultando información del sistema...\n");
        fflush(stdout);
        // TODO: Ejecutar uname mediante execvp().
        // TODO: Si execvp() falla, mostrar el error
        //       y terminar con código 127.
    } else {
        // TODO: Esperar al hijo mediante waitpid().
        if (/* TODO: comprobar terminación normal */) {
            // TODO: Mostrar código de salida.
        } else if (/* TODO: comprobar terminación por señal */) {
            // TODO: Mostrar número de señal.
        }
    }
}

/* =====================================================
   PREGUNTA 4: Monitoreo de múltiples procesos con WNOHANG
   ===================================================== */
void pregunta4() {
    pid_t pid1, pid2;
    int status1, status2;
    int terminado1 = 0;
    int terminado2 = 0;

    // Crear el primer proceso hijo.
    pid1 = fork();
    if (pid1 == ...) {
        perror("fork");
        return;
    }
    if (pid1 == ...) {
        printf("[HIJO 1] Ejecutando tarea 1...\n");
        sleep(2);
        // TODO: Terminar con código 10.
        // No debe continuar ejecutando el código del padre.
    }

    // Crear el segundo proceso hijo.
    pid2 = fork();
    if (pid2 == ...) {
        perror("fork");
        // Esperar al primer hijo antes de abandonar la función.
        waitpid(pid1, &status1, 0);
        return;
    }
    if (pid2 == ...) {
        printf("[HIJO 2] Ejecutando tarea 2...\n");
        sleep(4);
        // TODO: Terminar con código 20.
        // No debe continuar ejecutando el código del padre.
    }

    // A partir de aquí solamente continúa el proceso padre.
    while (!terminado1 || !terminado2) {
        // TODO: Consultar el estado del primer hijo
        //       utilizando waitpid() y WNOHANG
        //       (solo si todavía no ha terminado).
        // TODO: Si terminó, actualizar terminado1
        //       y mostrar su PID y código de salida.
        // TODO: Consultar el estado del segundo hijo
        //       utilizando waitpid() y WNOHANG
        //       (solo si todavía no ha terminado).
        // TODO: Si terminó, actualizar terminado2
        //       y mostrar su PID y código de salida.
        if (!terminado1 || !terminado2) {
            printf("[PADRE] Supervisando tareas...\n");
            sleep(1);
        }
    }
    printf("[PADRE] Todas las tareas finalizaron.\n");

    // TODO: Explicar en un comentario qué ocurre si el padre consulta
    //       con waitpid() a un hijo que ya fue recogido.
}

/* =====================================================
   PROGRAMA PRINCIPAL
   ===================================================== */

int main() {

    int opcion;
    printf("====================================\n");
    printf("     LABORATORIO CALIFICADO 04\n");
    printf("====================================\n");

    printf("1. Pregunta 1\n");
    printf("2. Pregunta 2\n");
    printf("3. Pregunta 3\n");
    printf("4. Pregunta 4\n");

    printf("Seleccione una pregunta: ");

    if (scanf("%d", &opcion) != 1) {
        printf("Entrada no valida.\n");
        return 1;
    }

    switch (opcion) {
        case 1:
            pregunta1();
            break;
        case 2:
            pregunta2();
            break;
        case 3:
            pregunta3();
            break;
        case 4:
            pregunta4();
            break;
        default:
            printf("Opcion no válida.\n");
    }
    return 0;
}
