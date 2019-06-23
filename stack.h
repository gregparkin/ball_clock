/**
 * @file      stack.h
 * @author    Greg Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/8/2019
 * @version   1.0
 *
 * @brief     Stack header definitions for stack.c in the ball_clock program
 *
 */
#ifndef BALL_CLOCK_STACK_H
#define BALL_CLOCK_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _stack
{
    int slot_size;         // How big to make the slot[]
    int *slot;             // Array of slots
    int number_of_balls;   // Number of balls currently in the stack
} STACK;

STACK *createStack(int slot_size);

int isStackFull(STACK *stack_object);
int addBall(STACK *stack_object, int ball_number);
int removetBall(STACK *stack_object);
void displayHeader();
void displayStack(char discription[], STACK *stack_object);
void displayTime(STACK *minute, STACK *five, STACK *hour, float day, int days);

#endif //BALL_CLOCK_STACK_H

