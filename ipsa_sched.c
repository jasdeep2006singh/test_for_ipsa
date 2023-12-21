
#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"

/* Priorities at which the tasks are created. */
#define ipsaTEMP   	   ( tskIDLE_PRIORITY + 2 )
#define ipsaPRINT	       ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define ipsaTEMP_FREQUENCY         pdMS_TO_TICKS( 2000UL )
#define ipsaPRINT_FREQUENCY		   pdMS_TO_TICKS( 500UL )
#define mainFREQUENCY_MS		   pdMS_TO_TICKS( 20UL )

/* The number of items the queue can hold at once. */
#define mainQUEUE_LENGTH                   ( 2 )

/* The values sent to the queue receive task from the queue send task and the
 * queue send software timer respectively. */
#define mainVALUE_SENT_FROM_TASK           ( 100UL )
#define mainVALUE_SENT_FROM_TIMER          ( 200UL )
static void vTemp( void  );
static void vPrinter( void );
static TimerHandle_t xTimer = NULL;
static QueueHandle_t xQueue = NULL;


void ipsa_sched( void )
{
    const TickType_t xTimerPeriod = mainFREQUENCY_MS;

    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
         * file. */
        xTaskCreate( vTemp,             /* The function that implements the task. */
                     "Temp",                            /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                     configMINIMAL_STACK_SIZE,        /* The size of the stack to allocate to the task. */
                     NULL,                            /* The parameter passed to the task - not used in this simple case. */
                     ipsaTEMP, /* The priority assigned to the task. */
                     NULL );                          /* The task handle is not required, so NULL is passed. */

        xTaskCreate( vPrinter, "Printer", configMINIMAL_STACK_SIZE, NULL, ipsaPRINT, NULL );

        /* Create the software timer, but don't start it yet. */
        xTimer = xTimerCreate( "Timer",                     /* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
                               xTimerPeriod,                /* The period of the software timer in ticks. */
                               pdTRUE,                      /* xAutoReload is set to pdTRUE. */
                               NULL,                        /* The timer's ID is not used. */
                               vPrinter ); /* The function executed when the timer expires. */

        if( xTimer != NULL )
        {
            xTimerStart( xTimer, 0 );
        }

        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks	to be created.  See the memory management section on the
     * FreeRTOS web site for more details. */
    for( ; ; )
    {
    }
}

void vTemp(void)
{
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = ipsaTEMP_FREQUENCY;
	float F=118;
	float C=(F-32)/1.8;
    xNextWakeTime = xTaskGetTickCount();

	for( ; ; )
    {
        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        printf("Temp: %f\n", C);
		vTaskDelayUntil( &xNextWakeTime, xBlockTime );
		
	}
}

void vPrinter(void)
{
	TickType_t xNextWakeTime;
    const TickType_t xBlockTime = ipsaPRINT_FREQUENCY;
    xNextWakeTime = xTaskGetTickCount();

	for( ; ; )
    {
        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
		printf("Working \n");
		vTaskDelayUntil( &xNextWakeTime, xBlockTime );
		
	}
}