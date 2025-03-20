/*******************************************************************************
* File Name: VDAC_1_PM.c
* Version 2.10
*
* Description:
*  This file provides the power management source code to the API for the
*  DVDAC component.
*
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "VDAC_1.h"
#include "VDAC_1_VDAC8.h"

static VDAC_1_BACKUP_STRUCT  VDAC_1_backup;


/*******************************************************************************
* Function Name: VDAC_1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The
*  VDAC_1_Sleep() API saves the current component state. Then it
*  calls the VDAC_1_Stop() function and calls
*  VDAC_1_SaveConfig() to save the hardware configuration. Call the
*  VDAC_1_Sleep() function before calling the CyPmSleep() or the
*  CyPmHibernate() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void VDAC_1_Sleep(void) 
{
    /* Save VDAC8's enable state */
    if(0u != (VDAC_1_VDAC8_PWRMGR & VDAC_1_VDAC8_ACT_PWR_EN))
    {
        VDAC_1_backup.enableState = 1u;
    }
    else
    {
        VDAC_1_backup.enableState = 0u;
    }

    VDAC_1_Stop();
    VDAC_1_SaveConfig();
}


/*******************************************************************************
* Function Name: VDAC_1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  VDAC_1_Sleep() was called. The VDAC_1_Wakeup() function
*  calls the VDAC_1_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  VDAC_1_Sleep() function was called, the DVDAC_Wakeup() function
*  will also re-enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void VDAC_1_Wakeup(void) 
{
    VDAC_1_RestoreConfig();

    if(VDAC_1_backup.enableState == 1u)
    {
        VDAC_1_Enable();
    }
}


/*******************************************************************************
* Function Name: VDAC_1_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the VDAC_1_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void VDAC_1_SaveConfig(void) 
{
    VDAC_1_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: VDAC_1_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the VDAC_1_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void VDAC_1_RestoreConfig(void) 
{
    VDAC_1_VDAC8_RestoreConfig();
}


/* [] END OF FILE */
