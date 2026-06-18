#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H
#include "FreeRTOS.h"
#include "queue.h"
#include "threadManager.h"
#include "deviceProperties.h"


/* USB IN queue dimensions */
#define MAX_USB_IN_LENGTH       90
#define MAX_USB_IN_DEPTH        64

/* USB OUT queue dimensions */
#define MAX_USB_OUT_LENGTH      30
#define MAX_USB_OUT_DEPTH       64

/* USB OUT BLK queue dimensions */
#define MAX_USB_BLK_OUT_LENGTH  2
#define MAX_USB_BLK_OUT_DEPTH   512

/* Thread Manager queue dimensions */
#define MAX_TM_MSG_LENGTH       20
#define MAX_TM_MSG_DEPTH        sizeof(ManagerMsg)


/*************************** common public functions **************************/
/******************************************************************************/
void initializeQueueManager( PeripheralModel_t model ); 
QueueHandle_t getUsbInPrQueueHandle( void );
QueueHandle_t getUsbInWrQueueHandle( void );
QueueHandle_t getUsbOutPrQueueHandle( void );
QueueHandle_t getUsbOutWrQueueHandle( void );

QueueHandle_t getThreadManagerQueueHandle( void );


bool addThreadManagerMsg( unsigned char * pMsg );

int getUsbInQueueLength( void );
int getUsbOutQueueLength( void );
bool addThreadManagerMsg( unsigned char * pMsg );

unsigned int getQueueDepth( QueueHandle_t handle_ );
unsigned int getQueueSize( QueueHandle_t handle_ );
/******************************************************************************/
/******************************************************************************/
#endif
