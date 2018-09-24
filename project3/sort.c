#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//LOCAL INCLUDES
#include "sort.h"
#include "edge.h"

/*****************************************************************************/
/* sort.c BY Murray Estes                                                    */
/* PUPRPOSE: To implement a variety of sorts for general usage. Requires     */
/*           elements to be stored in a dynamic array, found in da.h         */
/* METHOD DESCRIPTIONS:                                                      */
/*     void csort(DA *, int (*)(void *, void *);                             */
/*         Implements an analog of counting sort that can be used on any     */
/*         data structure.                                                   */
/*                                                                           */
/*     void msort(DA *, int (*)(void *, void *);                             */
/*         Implements merge sort.                                            */
/*                                                                           */
/*****************************************************************************/

/*** CONSTANTS ***/
#define TRUE 1
#define FALSE 0

/*** STRUCTS ***/
//none

/*** PRIVATE FUNCTION DECLARATIONS ***/
static void **mergeSort(void **, int, int (*)(void *, void *));
static void **merge(void **, void **, int, int, int, int (*)(void *, void *));
static void countSort(void **, int, int (*)(void *, void *));

/*** PUBLIC FUNCTION DEFINITIONS ***/
void csort(DA *array, int (*c)(void *, void *)){

    int size = sizeDA(array);
    void **arr = extractDA(array);
    countSort(arr, size, c);
    for(int i = 0; i < size; i++) insertDA(array, arr[i]);

    }

void msort(DA *array, int (*c)(void *, void *)){

    int size = sizeDA(array);
    void **arr = extractDA(array);
    arr = mergeSort(arr, size, c);
    for(int i = 0; i < size; i++) insertDA(array, arr[i]);

    }

/*** PRIVATE FUNCTION DEFINITIONS ***/
void **mergeSort(void **arr, int size, int (*c)(void *, void *)){

    if(size > 1){
        int x = size / 2;
        int y = size - x;
        void **brr = malloc(sizeof(void *) * x);
        void **crr = malloc(sizeof(void *) * y);
        for(int i = 0; i < x; i++) brr[i] = arr[i];
        int j = 0;
        for(int i = x; i < size; i++) crr[j++] = arr[i];
        brr = mergeSort(brr, x, c);
        crr = mergeSort(crr, y, c);
        arr = merge(brr, crr, x, y, size, c);
        }
    
    return arr;

    }

void **merge(void **arr, void **brr, int x, int y, int size,
             int (*c)(void *, void *)){

    void **crr = malloc(sizeof(void *) * size);
    for(int i = 0; i < size; i++) crr[i] = 0;
    int i = 0; int j = 0; int k = 0;
    while(i < x && j < y){
        if(c(arr[i], brr[j]) <= 0) crr[k++] = arr[i++];
        else crr[k++] = brr[j++];
        }
    while(i < x) crr[k++] = arr[i++];
    while(j < y) crr[k++] = brr[j++];

    return crr;

    }

void countSort(void **arr, int size, int (*c)(void *, void *)){

    void *max = arr[0]; void *min = arr[0];
    for(int i = 1; i < size; i++){
        if(c(arr[i], max) > 0) max = arr[i];
        if(c(arr[i], min) < 0) min = arr[i];
        }
    int s = c(max, min) + 1;
    int *brr = malloc(sizeof(int) * s);
    for(int i = 0; i < s; i++) brr[i] = 0;
    for(int i = 0; i < size; i++) brr[c(arr[i], min)]++;
    for(int i = 1; i < s; i++) brr[i] = brr[i] + brr[i - 1];
    void **crr = malloc(sizeof(void *) * size);
    for(int i = size - 1; i >= 0; i--){
        crr[brr[c(arr[i], min)] - 1] = arr[i];
	brr[c(arr[i], min)] = brr[c(arr[i], min)] - 1;
        }
    for(int i = 0; i < size; i++) arr[i] = crr[i];

    }
