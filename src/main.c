//EJERCICIO 3 TP14

/*==================[inclusions]=============================================*/

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/*==================[macros and definitions]=================================*/

#define PRIO_TAREA1 2
#define PRIO_TAREA2 1
#define TAM_PILA 150

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";

TaskHandle_t task1;
TaskHandle_t task2;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void vTarea1(void *pvParameters)
{
	char *pcTaskName;
	UBaseType_t priority;
	pcTaskName = ( char * ) pvParameters;
	priority = uxTaskPriorityGet(task1);
   for ( ;; ){
        printf( pcTaskName );
	vTaskPrioritySet (task2, (UBaseType_t)(priority + 1));
   }
}

static void vTarea2(void *pvParameters)
{
	char *pcTaskName;
	UBaseType_t priority;
	pcTaskName = ( char * ) pvParameters;
	priority = uxTaskPriorityGet(task2);

   for ( ;; ){
        printf( pcTaskName );
	vTaskPrioritySet (NULL , (UBaseType_t) (priority - 2));
   }
}

/*==================[external functions definition]==========================*/


int main(void)
{
    //Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+2, &task1 );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+1, &task2 );
	vTaskStartScheduler(); /* y por o se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}

/*==================[end of file]============================================*/
