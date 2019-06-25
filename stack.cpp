/**
 * @file      stack.cpp
 * @author    Greg Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/8/2019
 * @version   1.0
 *
 * @brief     Stack functions used in the ball_clock program
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/**
 * @function STACK *createStack(int slot_size)
 * @brief This function is used to create and initialize a stack (minute, five, hour).
 *
 * @param int slot_size
 * @return STACK *
 */
STACK *createStack(int slot_size)
{
    STACK *p = (STACK *)malloc(sizeof(STACK));

    if (p == NULL)
    {
        printf("Out of memory: %s, %s, LINE: %d\n", __FILE__, __FUNCTION__, __LINE__);
        exit(-1);
    }

    p->slot = (int *)malloc(sizeof(int)*slot_size);

    if (p->slot == NULL)
    {
        printf("Out of memory: %s, %s, LINE: %d\n", __FILE__, __FUNCTION__, __LINE__);
        exit(-1);
    }

    p->slot_size = slot_size;
    p->number_of_balls = 0;

    for (int i=0; i<slot_size; ++i)
    {
        p->slot[i] = -1;
    }

    return p;
}

/**
 * @function int addBall(STACK *stack_object, int ball_number)
 * @brief Move a ball onto the stack object.
 *
 * @param STACK *stack_object
 * @param int ball_number
 * @return int where 1 = success, 0 = failure
 */
int addBall(STACK *stack_object, int ball_number)
{
    if (stack_object == NULL)
    {
        fprintf(stderr, "stack object is NULL\n");
        exit(-1);
    }

    for (int i=0; i<stack_object->slot_size; i++)
    {
        if (stack_object->slot[i] == -1)
        {
            stack_object->slot[i] = ball_number;
            ++stack_object->number_of_balls;
            return 1;
        }
    }

    fprintf(stderr, "Cannot add ball to stack because stack is full\n");
    return 0;
}

/**
 * @function int removetBall(STACK *stack_object)
 * @brief Remove a ball from the stack. (1st in last out)
 *
 * @param STACK *stack_object
 * @return int where -1 is failure, or the ball number
 */
int removetBall(STACK *stack_object)
{
    if (stack_object == NULL)
    {
        fprintf(stderr, "stack object is NULL\n");
        exit(-1);
    }

    if (stack_object->number_of_balls == 0)
    {
        fprintf(stderr, "Cannot remove ball from stack because it is empty\n");
        return -1;
    }

    //
    // Stack: 1st in last out
    //
    if (stack_object->number_of_balls > 0)
    {
        int ball_number = stack_object->slot[stack_object->number_of_balls - 1];
        stack_object->slot[stack_object->number_of_balls - 1] = -1;
        --stack_object->number_of_balls;
        return ball_number;
    }

    fprintf(stderr, "Cannot remove ball from stack because it is empty\n");
    exit(-1);
}

/**
 * @function void displayHeader()
 * @brief Display a header to show the position of the tray slots.
 */
void displayHeader()
{
    printf("\n");
    printf("Tray Slots    1   2   3   4   5   6   7   8   9  10  11  12\n");
    printf("            --- --- --- --- --- --- --- --- --- --- --- ---\n");
}

/**
 * @function void displayStack(char description[], STACK *stack_object)
 * @brief Print the contents of how this stack (minute, five, hour) looks. Lined up with displayHeader()
 *
 * @param char description[]
 * @param STACK *stack_object
 */
void displayStack(const char* description, STACK *stack_object)
{
    if (stack_object == NULL)
    {
        fprintf(stderr, "Cannot display stack (%s) because it is NULL\n", description);
        exit(-1);
    }

    printf("%-10s "
           " ", description);

    for (int i=0; i<stack_object->slot_size; i++)
    {
        printf("%3d ", stack_object->slot[i]);
    }

    printf("\n");
}

/**
 * @function void displayTime(STACK *minute, STACK *five, STACK *hour, float day, int days)
 * @brief Compute the time of day including whether it is AM or PM, and a count of number of days from clock start.
 *
 * @param STACK *minute
 * @param STACK *five
 * @param STACK *hour
 * @param float day
 * @param int days
 */
void displayTime(STACK *minute, STACK *five, STACK *hour, float day, int days)
{
    if (minute == NULL)
    {
        fprintf(stderr, "minute stack is NULL\n");
        exit(-1);
    }

    if (five == NULL)
    {
        fprintf(stderr, "five stack is NULL\n");
        exit(-1);
    }

    if (hour == NULL)
    {
        fprintf(stderr, "hour stack is NULL\n");
        exit(-1);
    }

    int total_minutes = (five->number_of_balls * 5) + minute->number_of_balls;

    printf("\nCurrent TM: %d:%.2d %s, days = %d\n\n",
            hour->number_of_balls, total_minutes, day == 0 ? "AM" : "PM", days);
}