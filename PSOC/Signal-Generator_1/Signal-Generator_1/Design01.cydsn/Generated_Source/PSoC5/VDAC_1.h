/*******************************************************************************
* File Name: VDAC_1.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the DVDAC component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_DVDAC_VDAC_1_H)
#define CY_DVDAC_VDAC_1_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Data Struct Definition
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} VDAC_1_BACKUP_STRUCT;

/* Component init state */
extern uint8 VDAC_1_initVar;


/***************************************
*        API constants
***************************************/
#define VDAC_1_RESOLUTION                 (10u)
#define VDAC_1_INTERNAL_CLOCK_USED        (1u)

#define VDAC_1_INTEGER_PORTION_SHIFT      (VDAC_1_RESOLUTION - 8u)
#define VDAC_1_DITHERED_ARRAY_SIZE        ((uint8)(1u << VDAC_1_INTEGER_PORTION_SHIFT))
#define VDAC_1_FRACTIONAL_PORTION_MASK    (VDAC_1_DITHERED_ARRAY_SIZE - 1u)
#define VDAC_1_INTEGER_PORTION_MAX_VALUE  (0xFFu)

/* DMA Configuration */
#define VDAC_1_DMA_BYTES_PER_BURST        (1u)
#define VDAC_1_DMA_REQUEST_PER_BURST      (1u)
#define VDAC_1_DMA_SRC_BASE               (CYDEV_SRAM_BASE)
#define VDAC_1_DMA_DST_BASE               (CYDEV_PERIPH_BASE)


#if   (VDAC_1_RESOLUTION ==  9u)
    #define VDAC_1_DVDAC_MAX_VALUE        (0x1FEu)
#elif (VDAC_1_RESOLUTION == 10u)
    #define VDAC_1_DVDAC_MAX_VALUE        (0x3FCu)
#elif (VDAC_1_RESOLUTION == 11u)
    #define VDAC_1_DVDAC_MAX_VALUE        (0x7F8u)
#else   /* Resolution 12 bits */
    #define VDAC_1_DVDAC_MAX_VALUE        (0xFF0u)
#endif  /* (VDAC_1_RESOLUTION ==  9u) */


/***************************************
*        Function Prototypes
***************************************/

void VDAC_1_Init(void)                ;
void VDAC_1_Enable(void)              ;
void VDAC_1_Start(void)               ;
void VDAC_1_Stop(void)                ;
void VDAC_1_SetValue(uint16 value)    ;
void VDAC_1_Sleep(void)               ;
void VDAC_1_Wakeup(void)              ;
void VDAC_1_SaveConfig(void)          ;
void VDAC_1_RestoreConfig(void)       ;

#endif /* CY_DVDAC_VDAC_1_H */


/* [] END OF FILE */
