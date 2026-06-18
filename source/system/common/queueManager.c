#include "queueManager.h"
#include "fsl_debug_console.h"
#include "usb_misc.h"

USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static QueueHandle_t    pUSBInPrQueue_          = NULL;
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static QueueHandle_t    pUSBInWrQueue_          = NULL;
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static QueueHandle_t    pUSBOutPrQueue_         = NULL;
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static QueueHandle_t    pUSBOutWrQueue_         = NULL;
USB_DMA_NONINIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static QueueHandle_t    pUSBOutBlkQueue_        = NULL;
static QueueHandle_t    pThreadManagerQueue_    = NULL;

QueueHandle_t getUsbInPrQueueHandle( void )
{
    return pUSBInPrQueue_;
}

QueueHandle_t getUsbInWrQueueHandle( void )
{
    return pUSBInWrQueue_;
}

QueueHandle_t getUsbOutPrQueueHandle( void )
{
    return pUSBOutPrQueue_;
}

QueueHandle_t getUsbOutWrQueueHandle( void )
{
    return pUSBOutWrQueue_;
}

QueueHandle_t getUsbOutBlkQueueHandle( void )
{
    return pUSBOutBlkQueue_;
}

QueueHandle_t getThreadManagerQueueHandle( void )
{
    return pThreadManagerQueue_;
}

int getUsbInQueueLength( void )
{
    return MAX_USB_IN_LENGTH;    
}

int getUsbOutQueueLength( void )
{
    return MAX_USB_OUT_LENGTH;    
}

unsigned int getQueueDepth( QueueHandle_t handle_ )
{       
    int depth = 0;
    if( ( handle_ ==  pUSBInPrQueue_ ) || ( handle_ ==  pUSBInWrQueue_ ) )
        depth = MAX_USB_IN_DEPTH;
    if( ( handle_ == pUSBOutPrQueue_ ) || ( handle_ == pUSBOutWrQueue_ ) )
        depth = MAX_USB_OUT_DEPTH;
    return depth;
}

unsigned int getQueueSize( QueueHandle_t handle_ )
{
    int size = 0;
    if( ( handle_ ==  pUSBInPrQueue_ ) || ( handle_ ==  pUSBInWrQueue_ ) )
        size = MAX_USB_IN_LENGTH;
    if( ( handle_ == pUSBOutPrQueue_ ) || ( handle_ == pUSBOutWrQueue_ ) )
        size = MAX_USB_OUT_LENGTH;
    return size;  
}

void initializeQueueManager( PeripheralModel_t model )
{
    /* create common queues */
    pThreadManagerQueue_  = xQueueCreate( MAX_TM_MSG_LENGTH, MAX_TM_MSG_DEPTH );
    if( pThreadManagerQueue_ == NULL ) {
      PRINTF("initializeQueueManager(): Failed to create Thread Manager message queue!\r\n" );
    }
    
    if( ( model == GLOBAL_SCALE_HB_GT ) || ( model == GLOBAL_SCALE_HB_DT ) ) {
        /* create USB in weigher and printer coming message queues */   
        pUSBOutPrQueue_ = xQueueCreate( MAX_USB_OUT_LENGTH, MAX_USB_OUT_DEPTH );   
        pUSBOutWrQueue_ = xQueueCreate( MAX_USB_OUT_LENGTH, MAX_USB_OUT_DEPTH );   
        
        /* create USB out going weigher and printer message queues */ 
        pUSBInPrQueue_ = xQueueCreate( MAX_USB_IN_LENGTH, MAX_USB_IN_DEPTH ); 
        pUSBInWrQueue_ = xQueueCreate( MAX_USB_IN_LENGTH, MAX_USB_IN_DEPTH ); 
        
    } else {
        if( ( model == GLOBAL_SCALE_AV_XPRO ) || ( model == GLOBAL_SCALE_AV_XONE ) ) {
      
            /* create USB in coming weigher and printer message queues */   
            pUSBOutPrQueue_ = xQueueCreate( MAX_USB_OUT_LENGTH, MAX_USB_OUT_DEPTH );   
            pUSBOutWrQueue_ = xQueueCreate( MAX_USB_OUT_LENGTH, MAX_USB_OUT_DEPTH );   
            
            /* create USB out going weigher and printer message queues */ 
            pUSBInPrQueue_ = xQueueCreate( MAX_USB_IN_LENGTH, MAX_USB_IN_DEPTH ); 
            pUSBInWrQueue_ = xQueueCreate( MAX_USB_IN_LENGTH, MAX_USB_IN_DEPTH ); 
        } else {
            PRINTF("initializeQueueManager(): Unsupported model!\r\n" );
        }
    }
}

bool addThreadManagerMsg( unsigned char * pMsg )
{
    bool result = false;
    BaseType_t x;
    
    if( pThreadManagerQueue_ != NULL ) {
        x = xQueueSend(pThreadManagerQueue_, pMsg, 0);
        if( x == pdPASS ) {
            result = true;  
        }
    }
    return result;  
}

