#include "idleTask.h"
#include "fsl_debug_console.h"

static TaskHandle_t     pHandle_                = NULL;
static bool             suspend_                = false;

static void idleTask( void *pvParameters );

BaseType_t createIdleTask( void )
{
    BaseType_t result;


    PRINTF("idleTask(): Starting...\r\n" );
    
     /* create printer task thread */
    result = xTaskCreate( idleTask,  "IdleTask", configMINIMAL_STACK_SIZE,
                                        NULL, idle_task_PRIORITY, &pHandle_ );
    return result;    
}

/******************************************************************************/
/*!   \fn TaskHandle_t getIdleHandle( void )
                                            
      \brief
        This function returns the idle task handle.
       
      \author
          Aaron Swift
*******************************************************************************/                
TaskHandle_t getIdleHandle( void )
{
    return pHandle_;
}

/******************************************************************************/
/*!   \fn static void idleTask( void *pvParameters )
                                            
      \brief
        This function is the idle task function.
       
      \author
          Aaron Swift
*******************************************************************************/                
static void idleTask( void *pvParameters )
{
    PRINTF("idleTask(): Thread running...\r\n" );
    vTaskDelay( pdMS_TO_TICKS( 500 ) );
     
    while( !suspend_ ) {
        
        while(1)
        {            
            vTaskDelay( pdMS_TO_TICKS( 20 ) );
        }
    }
    vTaskSuspend(NULL);  
    
}
