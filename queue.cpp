/**
 * @file      queue.cpp
 * @author    Greg Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/8/2019
 * @version   1.0
 *
 * @brief     Queue functions used in the ball_clock program
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/**
 * @function QUEUE *pushQueue(QUEUE *top, int ball_number)
 * @brief Create a new node on the queue (link-list)
 *
 * @param QUEUE *top
 * @param int ball_number
 * @return QUEUE *
 */
QUEUE *pushQueue(QUEUE *top, int ball_number)
{
    QUEUE *t;
    QUEUE *p = (QUEUE *)malloc(sizeof(QUEUE));

    if (p == NULL)
    {
        printf("Out of memory! %s, %s LINE: %d\n", __FILE__, __FUNCTION__, __LINE__);
        exit(-1);
    }

    p->ball_number = ball_number;
    p->next = NULL;

    if (top == NULL)
    {
        top = p;
        return top;
    }

    for (t=top; t!=NULL; t=t->next)
    {
        if (t->next == NULL)
        {
            t->next = p;
            break;
        }
    }

    return top;
}

/**
 * @function QUEUE *popQueue(QUEUE *top, int *ball_number)
 * @brief Pop off a node (ball) from the queue.
 *
 * @param QUEUE *top
 * @param int *ball_number
 * @return QUEUE *
 */
QUEUE *popQueue(QUEUE *top, int *ball_number)
{
   if (top == NULL)
   {
       printf("Queue is empty!\n");
       return (QUEUE *)NULL;
   }

   *ball_number = top->ball_number;
   QUEUE *new_top = top->next;
   free(top);

   return new_top;
}

/**
 * @function void displayQueue(QUEUE *top)
 * @brief Print out the balls remaining in the queue.
 *
 * @param void
 */
void displayQueue(QUEUE *top)
{
    int x = 0;

    for (QUEUE *p=top; p!=NULL; p=p->next)
    {
        ++x;
        printf("Queue slot %3d contains ball number: %d\n", x, p->ball_number);
    }
}


