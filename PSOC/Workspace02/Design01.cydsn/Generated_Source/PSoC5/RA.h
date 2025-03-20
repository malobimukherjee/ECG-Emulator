/*******************************************************************************
* File Name: RA.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RA_H) /* Pins RA_H */
#define CY_PINS_RA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RA__PORT == 15 && ((RA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RA_Write(uint8 value);
void    RA_SetDriveMode(uint8 mode);
uint8   RA_ReadDataReg(void);
uint8   RA_Read(void);
void    RA_SetInterruptMode(uint16 position, uint16 mode);
uint8   RA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RA_SetDriveMode() function.
     *  @{
     */
        #define RA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RA_DM_RES_UP          PIN_DM_RES_UP
        #define RA_DM_RES_DWN         PIN_DM_RES_DWN
        #define RA_DM_OD_LO           PIN_DM_OD_LO
        #define RA_DM_OD_HI           PIN_DM_OD_HI
        #define RA_DM_STRONG          PIN_DM_STRONG
        #define RA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RA_MASK               RA__MASK
#define RA_SHIFT              RA__SHIFT
#define RA_WIDTH              1u

/* Interrupt constants */
#if defined(RA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RA_SetInterruptMode() function.
     *  @{
     */
        #define RA_INTR_NONE      (uint16)(0x0000u)
        #define RA_INTR_RISING    (uint16)(0x0001u)
        #define RA_INTR_FALLING   (uint16)(0x0002u)
        #define RA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RA_INTR_MASK      (0x01u) 
#endif /* (RA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RA_PS                     (* (reg8 *) RA__PS)
/* Data Register */
#define RA_DR                     (* (reg8 *) RA__DR)
/* Port Number */
#define RA_PRT_NUM                (* (reg8 *) RA__PRT) 
/* Connect to Analog Globals */                                                  
#define RA_AG                     (* (reg8 *) RA__AG)                       
/* Analog MUX bux enable */
#define RA_AMUX                   (* (reg8 *) RA__AMUX) 
/* Bidirectional Enable */                                                        
#define RA_BIE                    (* (reg8 *) RA__BIE)
/* Bit-mask for Aliased Register Access */
#define RA_BIT_MASK               (* (reg8 *) RA__BIT_MASK)
/* Bypass Enable */
#define RA_BYP                    (* (reg8 *) RA__BYP)
/* Port wide control signals */                                                   
#define RA_CTL                    (* (reg8 *) RA__CTL)
/* Drive Modes */
#define RA_DM0                    (* (reg8 *) RA__DM0) 
#define RA_DM1                    (* (reg8 *) RA__DM1)
#define RA_DM2                    (* (reg8 *) RA__DM2) 
/* Input Buffer Disable Override */
#define RA_INP_DIS                (* (reg8 *) RA__INP_DIS)
/* LCD Common or Segment Drive */
#define RA_LCD_COM_SEG            (* (reg8 *) RA__LCD_COM_SEG)
/* Enable Segment LCD */
#define RA_LCD_EN                 (* (reg8 *) RA__LCD_EN)
/* Slew Rate Control */
#define RA_SLW                    (* (reg8 *) RA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RA_PRTDSI__CAPS_SEL       (* (reg8 *) RA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RA_PRTDSI__OE_SEL0        (* (reg8 *) RA__PRTDSI__OE_SEL0) 
#define RA_PRTDSI__OE_SEL1        (* (reg8 *) RA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RA_PRTDSI__OUT_SEL0       (* (reg8 *) RA__PRTDSI__OUT_SEL0) 
#define RA_PRTDSI__OUT_SEL1       (* (reg8 *) RA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RA_PRTDSI__SYNC_OUT       (* (reg8 *) RA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RA__SIO_CFG)
    #define RA_SIO_HYST_EN        (* (reg8 *) RA__SIO_HYST_EN)
    #define RA_SIO_REG_HIFREQ     (* (reg8 *) RA__SIO_REG_HIFREQ)
    #define RA_SIO_CFG            (* (reg8 *) RA__SIO_CFG)
    #define RA_SIO_DIFF           (* (reg8 *) RA__SIO_DIFF)
#endif /* (RA__SIO_CFG) */

/* Interrupt Registers */
#if defined(RA__INTSTAT)
    #define RA_INTSTAT            (* (reg8 *) RA__INTSTAT)
    #define RA_SNAP               (* (reg8 *) RA__SNAP)
    
	#define RA_0_INTTYPE_REG 		(* (reg8 *) RA__0__INTTYPE)
#endif /* (RA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RA_H */


/* [] END OF FILE */
