/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include "IDAC_1.h"
#include "UART_1.h"

#define BUFFER_SIZE 6312

uint8_t rxBuffer1[BUFFER_SIZE];
uint8_t rxBuffer2[BUFFER_SIZE];
uint8_t* currentRxBuffer;
uint8_t* plotBuffer;
volatile uint8_t receivedData;
volatile int bufferFilled = 0; // Flag to indicate buffer is completely filled
volatile uint32_t tc_count = 0;
uint32_t count;
uint8_t OneToSend = 0x01;
char string[128];

CY_ISR(timer_tc_isr) {
    Timer_1_ReadStatusRegister();
    tc_count++;
}

void start_measure(void) {
    Timer_1_Stop();
    Timer_1_ReadStatusRegister();
    Timer_1_WriteCounter(0);
    isr_timer_ClearPending();
    tc_count = 0;
    Timer_1_Start();
}

uint32_t stop_measure(void) {
    Timer_1_Stop();
    count = Timer_1_ReadPeriod() - Timer_1_ReadCounter();
    if (tc_count) {
        count += tc_count * Timer_1_ReadPeriod();
    }
    return (count);
}

void initializeComponents(void) {
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_timer_ClearPending();
    isr_timer_StartEx(timer_tc_isr);

    Timer_1_Start();
    UART_1_Start();    // Start UART communication
    IDAC_1_Start();    // Start DAC component
    PGA_Inv_1_Start();
    TIA_1_Start();
    Opamp_1_Start();
    UART_1_ClearRxBuffer(); // Clear UART receive buffer
    UART_1_ClearTxBuffer(); // Clear UART transmit buffer
    currentRxBuffer = rxBuffer1;
    plotBuffer = rxBuffer2;
    //UART_1_PutChar(OneToSend); // Initial request for data
}

// ISR Handler for UART RX
CY_ISR(UART_Rx_Handler) {
    static int index = 0;
    isr_1_ClearPending();

    if (bufferFilled == 0) { // Only receive new data if the buffer is not yet filled
        while (UART_1_GetRxBufferSize() > 0) {
            receivedData = UART_1_ReadRxData(); /* Read received data */
            currentRxBuffer[index++] = receivedData; /* Store received data in buffer */
            //sprintf(string, "%d\t", (int)currentRxBuffer[index-1]);
            //UART_1_PutString(string);
           
            if (index >= BUFFER_SIZE) {
                bufferFilled = 1; // Set flag to indicate buffer is full
                index = 0; // Reset index for next reception
               
                /*uint8_t* temp = plotBuffer;
                plotBuffer = currentRxBuffer;
                currentRxBuffer = temp;*/
            }
        }
    }
}

void plotData(void) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        IDAC_1_SetValue(plotBuffer[i]); // Set IDAC value
        CyDelayUs(2777);                     // 2 ms delay between points
    }
}

int main(void) {
    initializeComponents();
    isr_1_StartEx(UART_Rx_Handler); // Start UART RX ISR
   
    while (1) {
        if (bufferFilled) { // Plot data only if buffer is filled
            // Critical section start
            CyGlobalIntDisable; // Disable interrupts to avoid race condition
           
            // Swap buffers before plotting so that new data can be received while plotting
            uint8_t* temp = plotBuffer;
            plotBuffer = currentRxBuffer;
            currentRxBuffer = temp;
           
            CyGlobalIntEnable; // Re-enable interrupts
            // Critical section end
        }
       
        bufferFilled = 0; // Reset the flag to allow new data reception
       
        UART_1_WriteTxData(OneToSend); // Transmit 1 byte to request the next chunk of data
        //CyDelay(1);
       
        plotData(); // Plot data from the plotBuffer
       
        //bufferFilled = 0; // Reset the flag to allow new data reception
       
       
    }
}



/* [] END OF FILE */