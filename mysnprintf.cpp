//
//  mysnprintf.cpp
//  snprintf
//
//  Created by Руслан on 5/27/15.
//  Copyright (c) 2015 Руслан. All rights reserved.
//

#include "mysnprintf.h"


#define LENGTH_OF_WIDTH 32
#define LENGHT_OF_PRECISION 32

void clearString(char* line, int len);
int length(int num);
int max(int first, int second);

char* mysnprintf(char* res, int countChar, const char* temp,  ...){
    int currentPosTmp = 0;
    int currentPosRes = 0;
    int currentNum = 0;
    int currentPrecision = 0;
    int lentemp = strlen(temp);
    char width[LENGTH_OF_WIDTH];
    char precision[LENGHT_OF_PRECISION];
    
    va_list ap;
    va_start(ap, temp);
    while( ( currentPosRes < countChar ) && ( currentPosTmp < lentemp-1 ) ) {
        // if next characters is common characters
        if ( '%' != *(temp + currentPosTmp) ){
            *(res + currentPosRes) = *(temp + currentPosTmp);
            currentPosRes++;
            currentPosTmp++;
            continue;
        }
        
        // if two '%' one by one
        if ( '%' == *(temp + currentPosTmp + 1) ){
            *(res + currentPosRes) = '%';
            currentPosRes++;
            currentPosTmp += 2;
            continue;
        }
        
        currentPosTmp++;
        clearString(width, LENGTH_OF_WIDTH);
        currentNum = 0;
        // read width
        while( isdigit(*(temp + currentPosTmp)) ){
            *(width + currentNum) = *(temp + currentPosTmp);
            currentNum++;
            currentPosTmp++;
        }
        
        //read precision
        if('.' == *(temp + currentPosTmp)) {
            currentPosTmp++;
            while(isdigit(*(temp + currentPosTmp)) ){
                *(precision + currentPrecision) = *(temp + currentPosTmp);
                currentPrecision++;
                currentPosTmp++;
            }
        }     
        
        // insert other part
        int precisionLength = atoi(precision), widthLength = atoi(width);
        switch( *(temp + currentPosTmp) ){
            case 'i': {
            case 'd':
                int arg = va_arg(ap, int);
                    
                if (widthLength == 0) widthLength = length(arg);
                if (precisionLength == 0) precisionLength = length(arg);
                
                for(int i=length(arg); i<precisionLength; i++, arg*=10);
                
                for(int i=0; i<widthLength-length(arg); i++, currentPosRes++) {
                    *(res + currentPosRes) = ' ';
                }
                
                for(int i=0, arg_tmp = arg; i<length(arg); i++, currentPosRes++) {
                    *(res + currentPosRes) = (arg_tmp - (arg_tmp % (int)pow(10, length(arg) - i - 1))) / (int)pow(10, length(arg) - i - 1) + 48;
                    arg_tmp %= (int)pow(10, length(arg) - i - 1);
                }
                
                currentPosRes += length(arg);
                break;
            }
            case 's': {
                int length = 0;
                char* arg = va_arg(ap, char*);
                for(; *(arg+length) != '\0'; length++);
                
                if (widthLength == 0) widthLength = length;
                if (precisionLength == 0) precisionLength = length;
                
                for(int i=0; i<widthLength - precisionLength; i++, currentPosRes++, countChar--) {
                    *(res + currentPosRes) = ' ';
                }
                
                for(int i=0; i<precisionLength && i<countChar-1; i++, currentPosRes++) {
                    *(res + currentPosRes) = *(arg + i);
                }
                break;
            }
            case 'c':
                if (widthLength == 0) widthLength = 1;
                
                for(int i=0; i < widthLength - 1; i++, currentPosRes++) {
                    *(res + currentPosRes) = ' ';
                }
                *(res + currentPosRes) = (char) va_arg(ap, int);
                currentPosRes++;
                break;
                
            case 'f': {
                double arg = va_arg(ap, double), fractpart, intpart;
                fractpart = modf(arg , &intpart);
                
                if (precisionLength == 0) precisionLength = 6;
                if (widthLength == 0) widthLength = length(intpart) + precisionLength + 1;
                
                for(int i=0; i<widthLength - precisionLength - length(intpart) - 1; i++, currentPosRes++) {
                    *(res + currentPosRes) = ' ';
                }
                
                for(int i=0, intpart_tmp = (int)intpart; i<length(intpart); i++, currentPosRes++) {
                    *(res + currentPosRes) = (intpart_tmp - (intpart_tmp % (int)pow(10, length(intpart) - i - 1))) / (int)pow(10, length(intpart) - i - 1) + 48;
                    intpart_tmp %= (int)pow(10, length(intpart) - i - 1);
                }
                
                *(res + currentPosRes) = '.';
                currentPosRes++;
                
                for(int i=0; i<precisionLength; i++, currentPosRes++) {
                    *(res + currentPosRes) = ((int)(fractpart * pow(10, i+1))) % 10 + 48;
                }
                break;
            }
                
            default:
                fprintf(stderr, "Undefined prefix" );
                break;
                
        }
        currentPosTmp++;
    }
    *(res + currentPosRes) = '\0';
    
    return res;
}

int length(int num){ return ( num /= 10 ) ? 1 + length(num) : 1; }
int max(int first, int second){ return (first>second) ? first : second; }

void clearString(char* line, int len){
    int i;
    
    for ( i = 0; i < len; ++i){
        line[i] = '\0';
    }
}