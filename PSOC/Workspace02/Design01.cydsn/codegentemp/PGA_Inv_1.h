/*******************************************************************************
* File Name: PGA_Inv_1.c
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the PGA_Inv User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_Inv_PGA_Inv_1_H) 
#define CY_PGA_Inv_PGA_Inv_1_H 

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PGA_Inv_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


#if(!CY_PSOC5A)
    #if(CYDEV_VARIABLE_VDDA == 1)
        #if (!defined(CY_LIB_SC_BST_CLK_EN))
            #error Component PGA_Inv_v2_0 requires cy_boot v3.30 or later
        #endif /* (!defined(CY_LIB_SC_BST_CLK_EN)) */
    #endif /* CYDEV_VARIABLE_VDDA == 1 */
#endif /* (!CY_PSOC5A) */

/***************************************
*   Data Struct Definition
***************************************/

/* Low power API Support */
typedef struct
{
    uint8   enableState;
    uint8   scCR0Reg;
    uint8   scCR1Reg;
    uint8   scCR2Reg;
}   PGA_Inv_1_BACKUP_STRUCT;


/* component init state */
extern uint8 PGA_Inv_1_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void PGA_Inv_1_Start(void)                 ;
void PGA_Inv_1_Stop(void)                  ;
void PGA_Inv_1_SetPower(uint8 power)       ;
void PGA_Inv_1_SetGain(uint8 gain)         ;
void PGA_Inv_1_Sleep(void)                 ;
void PGA_Inv_1_Wakeup(void)                ;
void PGA_Inv_1_SaveConfig(void)            ;
void PGA_Inv_1_RestoreConfig(void)         ;
void PGA_Inv_1_Init(void)                  ;
void PGA_Inv_1_Enable(void)                ;


/***************************************
*           API Constants        
***************************************/

/* Power constants for SetPower function */
#define PGA_Inv_1_MINPOWER                 (0x00u)
#define PGA_Inv_1_LOWPOWER                 (0x01u)
#define PGA_Inv_1_MEDPOWER                 (0x02u)
#define PGA_Inv_1_HIGHPOWER                (0x03u)

/* Constants for SetGain function */
#define PGA_Inv_1_GAIN_01                  (0x00u)
#define PGA_Inv_1_GAIN_03                  (0x01u)
#define PGA_Inv_1_GAIN_07                  (0x02u)
#define PGA_Inv_1_GAIN_15                  (0x03u)
#define PGA_Inv_1_GAIN_22                  (0x04u)
#define PGA_Inv_1_GAIN_24                  (0x05u)
#define PGA_Inv_1_GAIN_31                  (0x06u)
#define PGA_Inv_1_GAIN_47                  (0x07u)
#define PGA_Inv_1_GAIN_49                  (0x08u)
#define PGA_Inv_1_GAIN_MAX                 (0x08u)


/***************************************
*       Initialization Values
***************************************/

#define PGA_Inv_1_DEFAULT_GAIN             (0u)
#define PGA_Inv_1_DEFAULT_POWER            (2u)


/***************************************
*              Registers
***************************************/

#define PGA_Inv_1_CR0_REG                  (* (reg8 *) PGA_Inv_1_SC__CR0 )
#define PGA_Inv_1_CR0_PTR                  (  (reg8 *) PGA_Inv_1_SC__CR0 )
#define PGA_Inv_1_CR1_REG                  (* (reg8 *) PGA_Inv_1_SC__CR1 )
#define PGA_Inv_1_CR1_PTR                  (  (reg8 *) PGA_Inv_1_SC__CR1 )
#define PGA_Inv_1_CR2_REG                  (* (reg8 *) PGA_Inv_1_SC__CR2 )
#define PGA_Inv_1_CR2_PTR                  (  (reg8 *) PGA_Inv_1_SC__CR2 )
  /* Power manager */
#define PGA_Inv_1_PM_ACT_CFG_REG           (* (reg8 *) PGA_Inv_1_SC__PM_ACT_CFG )
#define PGA_Inv_1_PM_ACT_CFG_PTR           (  (reg8 *) PGA_Inv_1_SC__PM_ACT_CFG )
  /* Power manager */
#define PGA_Inv_1_PM_STBY_CFG_REG          (* (reg8 *) PGA_Inv_1_SC__PM_STBY_CFG )
#define PGA_Inv_1_PM_STBY_CFG_PTR          (  (reg8 *) PGA_Inv_1_SC__PM_STBY_CFG )

/* Switched Capacitor Routing Register */
#define PGA_Inv_1_SW0_REG                  (* (reg8 *) PGA_Inv_1_SC__SW0 )
#define PGA_Inv_1_SW0_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW0 )
#define PGA_Inv_1_SW2_REG                  (* (reg8 *) PGA_Inv_1_SC__SW2 )
#define PGA_Inv_1_SW2_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW2 )
#define PGA_Inv_1_SW3_REG                  (* (reg8 *) PGA_Inv_1_SC__SW3 )
#define PGA_Inv_1_SW3_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW3 )
#define PGA_Inv_1_SW4_REG                  (* (reg8 *) PGA_Inv_1_SC__SW4 )
#define PGA_Inv_1_SW4_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW4 )
#define PGA_Inv_1_SW6_REG                  (* (reg8 *) PGA_Inv_1_SC__SW6 )
#define PGA_Inv_1_SW6_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW6 )
#define PGA_Inv_1_SW7_REG                  (* (reg8 *) PGA_Inv_1_SC__SW7 )
#define PGA_Inv_1_SW7_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW7 )
#define PGA_Inv_1_SW8_REG                  (* (reg8 *) PGA_Inv_1_SC__SW8 )
#define PGA_Inv_1_SW8_PTR                  (  (reg8 *) PGA_Inv_1_SC__SW8 )
#define PGA_Inv_1_SW10_REG                 (* (reg8 *) PGA_Inv_1_SC__SW10 )
#define PGA_Inv_1_SW10_PTR                 (  (reg8 *) PGA_Inv_1_SC__SW10 )

/* Switched Capacitor Clock Selection Register */
#define PGA_Inv_1_CLK_REG                  (* (reg8 *) PGA_Inv_1_SC__CLK )
#define PGA_Inv_1_CLK_PTR                  (  (reg8 *) PGA_Inv_1_SC__CLK )

/* Switched Capacitor Boost Clock Selection Register */
#define PGA_Inv_1_BSTCLK_REG               (* (reg8 *) PGA_Inv_1_SC__BST )
#define PGA_Inv_1_BSTCLK_PTR               (  (reg8 *) PGA_Inv_1_SC__BST )

 /* Pump clock selectin register */
#define PGA_Inv_1_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define PGA_Inv_1_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Pump Register for SC block */
#define PGA_Inv_1_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define PGA_Inv_1_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define PGA_Inv_1_ACT_PWR_EN               PGA_Inv_1_SC__PM_ACT_MSK
#define PGA_Inv_1_STBY_PWR_EN              PGA_Inv_1_SC__PM_STBY_MSK


/***************************************
*           Register Constants
***************************************/

/* CR0 SC/CT Control Register 0 definitions */
#define PGA_Inv_1_MODE_PGA                 (0x0Cu)

/* CR1 SC/CT Control Register 1 definitions */

/* Bit Field  SC_COMP_ENUM */
#define PGA_Inv_1_COMP_MASK                (0x0Cu)
#define PGA_Inv_1_COMP_3P0PF               (0x00u)
#define PGA_Inv_1_COMP_3P6PF               (0x04u)
#define PGA_Inv_1_COMP_4P35PF              (0x08u)
#define PGA_Inv_1_COMP_5P1PF               (0x0Cu)

/* Bit Field  SC_DIV2_ENUM */
#define PGA_Inv_1_DIV2_MASK                (0x10u)
#define PGA_Inv_1_DIV2_DISABLE             (0x00u)
#define PGA_Inv_1_DIV2_ENABLE              (0x10u)

/* Bit Field  SC_DRIVE_ENUM */
#define PGA_Inv_1_DRIVE_MASK               (0x03u)
#define PGA_Inv_1_DRIVE_280UA              (0x00u)
#define PGA_Inv_1_DRIVE_420UA              (0x01u)
#define PGA_Inv_1_DRIVE_530UA              (0x02u)
#define PGA_Inv_1_DRIVE_650UA              (0x03u)

/* Bit Field  SC_PGA_MODE_ENUM */
#define PGA_Inv_1_PGA_MODE_MASK            (0x20u)
#define PGA_Inv_1_PGA_INV                  (0x00u)
#define PGA_Inv_1_PGA_NINV                 (0x20u)

/* CR2 SC/CT Control Register 2 definitions */

/* Bit Field  SC_BIAS_CONTROL_ENUM */
#define PGA_Inv_1_BIAS_MASK                (0x01u)
#define PGA_Inv_1_BIAS_NORMAL              (0x00u)
#define PGA_Inv_1_BIAS_LOW                 (0x01u)

/* Bit Field  SC_PGA_GNDVREF_ENUM */
#define PGA_Inv_1_GNDVREF_MASK             (0x80u)
#define PGA_Inv_1_GNDVREF_DI               (0x00u)
#define PGA_Inv_1_GNDVREF_E                (0x80u)

/* Bit Field  SC_R20_40B_ENUM */
#define PGA_Inv_1_R20_40B_MASK             (0x02u)
#define PGA_Inv_1_R20_40B_40K              (0x00u)
#define PGA_Inv_1_R20_40B_20K              (0x02u)

/* Bit Field  SC_REDC_ENUM */
#define PGA_Inv_1_REDC_MASK                (0x0Cu)
#define PGA_Inv_1_REDC_00                  (0x00u)
#define PGA_Inv_1_REDC_01                  (0x04u)
#define PGA_Inv_1_REDC_10                  (0x08u)
#define PGA_Inv_1_REDC_11                  (0x0Cu)

/* Bit Field  SC_RVAL_ENUM */
#define PGA_Inv_1_RVAL_MASK                (0x70u)
#define PGA_Inv_1_RVAL_20K                 (0x00u)
#define PGA_Inv_1_RVAL_30K                 (0x10u)
#define PGA_Inv_1_RVAL_40K                 (0x20u)
#define PGA_Inv_1_RVAL_60K                 (0x30u)
#define PGA_Inv_1_RVAL_120K                (0x40u)
#define PGA_Inv_1_RVAL_250K                (0x50u)
#define PGA_Inv_1_RVAL_500K                (0x60u)
#define PGA_Inv_1_RVAL_1000K               (0x70u)

/* SC_MISC constants */
#define PGA_Inv_1_PUMP_FORCE               (0x20u)
#define PGA_Inv_1_PUMP_AUTO                (0x10u)
#define PGA_Inv_1_DIFF_PGA_1_3             (0x02u)
#define PGA_Inv_1_DIFF_PGA_0_2             (0x01u)

/* Bit Field  PGA_INVERTING_GAIN_ENUM */
#define PGA_Inv_1_PGA_INV_GAIN_MASK        (0x72u)
#define PGA_Inv_1_PGA_INV_GAIN_00          (0x00u)
#define PGA_Inv_1_PGA_INV_GAIN_01          (0x10u)
#define PGA_Inv_1_PGA_INV_GAIN_03          (0x20u)
#define PGA_Inv_1_PGA_INV_GAIN_07          (0x30u)
#define PGA_Inv_1_PGA_INV_GAIN_15          (0x40u)
#define PGA_Inv_1_PGA_INV_GAIN_22          (0x50u)
#define PGA_Inv_1_PGA_INV_GAIN_24          (0x70u)
#define PGA_Inv_1_PGA_INV_GAIN_31          (0x52u)
#define PGA_Inv_1_PGA_INV_GAIN_47          (0x62u)
#define PGA_Inv_1_PGA_INV_GAIN_49          (0x72u)

/* ANIF.PUMP.CR1 Constants */
#define PGA_Inv_1_PUMP_CR1_SC_CLKSEL       (0x80u)

#define PGA_Inv_1_SC_REG_CLR               (0x00u)

/* Boost Clock Enable */
#define PGA_Inv_1_BST_CLK_EN               (0x08u)
#define PGA_Inv_1_BST_CLK_INDEX_MASK       (0x07u)
#define PGA_Inv_1_PM_ACT_CFG_MASK          (0x0Fu)

/* Constants for VDDA Threshold */
#define PGA_Inv_1_CYDEV_VDDA_MV             (CYDEV_VDDA_MV)
#define PGA_Inv_1_MINIMUM_VDDA_THRESHOLD_MV (2700u)

/*******************************************************************************
* Following code are OBSOLETE and must not be used starting from PGA_inv 2.0
*******************************************************************************/
#define PGA_Inv_1_BST_REG            (PGA_Inv_1_BSTCLK_REG)
#define PGA_Inv_1_BST_PTR            (PGA_Inv_1_BSTCLK_PTR)

#endif /* CY_PGA_Inv_PGA_Inv_1_H */


/* [] END OF FILE */
