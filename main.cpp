//
//  main.cpp
//  snprintf
//
//  Created by Руслан on 5/27/15.
//  Copyright (c) 2015 Руслан. All rights reserved.
//

#include <stdio.h>
#include "mysnprintf.h"

int main(){
    char buf[256];
    
    mysnprintf(buf, 123, "%15.10d", 123);
    printf("%s\n", buf);
    
    return 0;
}