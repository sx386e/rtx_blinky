
/*
 * Auto generated Run-Time-Environment Component Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'Blinky' 
 * Target:  'MK64FN1M Flash' 
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File: 
 */
#define CMSIS_device_header "fsl_device_registers.h"

#define RTE_BOARD_SUPPORT_ACCELEROMETER
#define RTE_BOARD_SUPPORT_MAGNETOMETER
#define RTE_CMSIS_RTOS                  /* CMSIS-RTOS */
        #define RTE_CMSIS_RTOS_RTX              /* CMSIS-RTOS Keil RTX */
#define RTE_Compiler_IO_STDOUT          /* Compiler I/O: STDOUT */
        #define RTE_Compiler_IO_STDOUT_ITM      /* Compiler I/O: STDOUT ITM */
#define RTE_DEVICE_CONFIGURATION_FRDM_K64F
#define RTE_DEVICE_DRIVER_EDMA
#define RTE_DEVICE_DRIVER_GPIO
#define RTE_DEVICE_DRIVER_RTC
#define RTE_DEVICE_HAL_DMAMUX
#define RTE_DEVICE_HAL_EDMA
#define RTE_DEVICE_HAL_ENET
#define RTE_DEVICE_HAL_GPIO
#define RTE_DEVICE_HAL_I2C
#define RTE_DEVICE_HAL_LPTMR
#define RTE_DEVICE_HAL_MCG
#define RTE_DEVICE_HAL_OSC
#define RTE_DEVICE_HAL_PORT
#define RTE_DEVICE_HAL_RTC
#define RTE_DEVICE_HAL_SIM
#define RTE_DEVICE_HAL_UART
#define RTE_DEVICE_OSA_BM
#define RTE_DEVICE_STARTUP_KINETIS      /* Device Startup for Kinetis Series */
#define RTE_DEVICE_SYSTEM_CLOCK
#define RTE_DEVICE_SYSTEM_INTERRUPT
#define RTE_DEVICE_UTILITY_DEBUG_CONSOLE
#define RTE_Drivers_ETH_MAC0            /* Driver ETH_MAC0 */
#define RTE_Drivers_I2C0                /* Driver I2C0 */
        #define RTE_Drivers_I2C1                /* Driver I2C1 */
        #define RTE_Drivers_I2C2                /* Driver I2C2 */
#define RTE_Drivers_PHY_KSZ8081RNA      /* Driver PHY KSZ8081RNA/RND */
#define RTE_Network_Core                /* Network Core */
          #define RTE_Network_Release             /* Network Release Version */
#define RTE_Network_Interface_ETH_0     /* Network Interface ETH 0 */
#define RTE_Network_Socket_TCP          /* Network Socket TCP */
#define RTE_Network_Socket_UDP          /* Network Socket UDP */
#define RTE_Network_Web_Server_RO       /* Network Web Server with Read-only Web Resources */

#endif /* RTE_COMPONENTS_H */
