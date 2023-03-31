/**
  LED Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    led.h

  @Summary
    This is the generated header file for the LED driver using Board Support Library

  @Description
    This header file provides APIs for driver for LED.
    Generation Information :
        Product Revision  :  Board Support Library - 2.0.0
        Device            :  PIC24FJ128GA202
        Driver Version    :  0.97-b
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/


/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
/**
  Section: Included Files
*/

#ifndef LED_H
#define LED_H

#include <xc.h>
#include <stdbool.h>
#include "led.h"

static bool isEnabled = false;

void LED_Initialize()
{
    //Selected pin is Non-PPS 
}

void LED_On(void)
{
    _LATA0 = 1;// Intensity control module is not loaded
}

void LED_Off(void)
{
     _LATA0 = 0;
    // Intensity control module is not loaded
}

void LED_Toggle(void)
{
     _LATA0 = ~ _LATA0;
    // Intensity control module is not loaded
}

void LED_IntensitySet(uint16_t new_intensity)
{  
    // Intensity control module is not loaded
}
#endif /* LED_H */
