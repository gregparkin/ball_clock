/**
 * @file      queue.h
 * @author    Greg Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/8/2019
 * @version   1.0
 *
 * @brief     Queue header definitions for queue.c in the ball_clock program
 *
 */
#ifndef BALL_CLOCK_QUEUE_H
#define BALL_CLOCK_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _queue
{
    int ball_number;
    struct _queue *next;
} QUEUE;

QUEUE *pushQueue(QUEUE *top, int ball_number);
QUEUE *popQueue(QUEUE *top, int *ball_number);
void displayQueue(QUEUE *top);

#endif //BALL_CLOCK_QUEUE_H
