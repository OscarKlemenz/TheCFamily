/* Program: riffle.h
 *  --------------
 *  riffle.h is the header file for riffle.c driver
 * 
 *  Author: Oscar Klemenz
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void riffle_once(void *,int, int, void *);
void riffle(void *,int, int, int);
int check_shuffle(void *, int , int , int (*)(void *, void *));
int cmp_int(void *, void *);
int cmp_str(void *, void *);
float quality(int *, int);
float average_quality(int, int, int);
