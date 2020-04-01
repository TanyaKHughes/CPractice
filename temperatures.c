//
//  temperatures.c
//  CPractice
//
//  Created by Tanya Hughes on 3/18/20.
//  Copyright © 2020 Tanya Hughes. All rights reserved.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "temperatures.h"

//locally-used only function
float convertedTemp(bool celsius, float originalValue);

/*This function will print a table of temperatures in both Celsius and Fahrenheit. It asks the user for a lower bound, an upper bound, and a step size, and it asks whether the user is giving these bounds in C or F.*/
int printTemperatures(void){
    
    float lower, upper, step; //The starting temp, the ending temp, and the step-size
    char yesorno[3]; //whether celsius or not
    bool inCelsius;  //whether or not the lower/upper/step are given in celsius

    lower = 1; upper = 0; step = 1;
    
    // Get values needed to construct the table from the user
    printf("I need you to give me the range for table.  Are you entering temperatures in Celsius? (yes or no)\n");
    //scanf("%s",yesorno);  // works, but if they input something really long it could crash
    fgets(yesorno,3,stdin); //this just grabs the first 2 characers & adds a null to the end
    while ((getchar()) != '\n'); //flush the input buffer of any extra characters
    
    //so we only grabbed the first two characters of the input string
    if (strcmp(yesorno, "ye")==0) inCelsius = true;
    else if (strcmp(yesorno, "no")==0) inCelsius = false;
    else{
        printf("I don't understand.\n");
        return 1;
    }
    
    printf("What's the lowest temperature you want me to list?\n");
    scanf("%f", &lower);
    printf("What's the highest temperature you want me to list?\n");
    scanf("%f", &upper);
    printf("What's the step size?\n");
    scanf("%f", &step);
    if (lower > upper) {
        printf("Your temperatures are backwards.\n");
        return (2);
    }
    
    //Print the table, starting with the header
    if (inCelsius) printf("   %s   \t   %s   \n", "C", "F");
    else printf("   %s   \t   %s   \n", "F", "C");
    
    //lower will become the current temperature we are working with, as it gets incremented
    while (lower < upper){
        // print one line of the table
        printf("  %.1f\t  %.1f\n", lower, convertedTemp(inCelsius,lower));
        lower = lower + step;
    }
    //print the line belonging to the upper bound,
    //whether it was on an exact increment or not
    printf("  %.1f\t  %.1f\n", upper, convertedTemp(inCelsius,upper));
    
    return 0;
}

/*Converts a temperature from celsius to fahrenheit or vice-versa*/
float convertedTemp(bool inCelsius, float originalValue){
    if (inCelsius) return originalValue*9.0/5.0 + 32.0;
    else return (originalValue - 32.0)*5.0/9.0;
}

