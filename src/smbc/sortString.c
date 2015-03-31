/*
 * sortString.c
 *
 *  Created on: Dec 8, 2014
 *      Author: swapnesh
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortString(char *a) {
    int i, j;
    char value;
    for (i = 1; i < strlen(a); i++) {
        value = a[i];
        for (j = i; j > 0 && value > a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = value;
    }
}



