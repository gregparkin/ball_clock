/**
 * @file      main.cpp
 * @author    Greg Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/8/2019
 * @version   1.0
 *
 * @brief     I am interpreting a "ball cycle" to mean all balls from the queue have been used or cycled
 *            into the clock trays at least once. I determine this when I pull the last ball number from
 *            the queue which is ball number 28 in this example.
 *
 *            I have used JetBrains CLION IDE on Windows 10 which is uses gcc and gdb from CYGWIN located
 *            also on my computer. So it is easier to hard code number of cycles and and queue size and run
 *            it in debug mode.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define NON_MOVEABLE_BALL   999
#define QUEUE_SIZE          28
#define CYCLES              300

void displayAll(QUEUE *top, STACK *minute, STACK *five, STACK *hour, float day, int days);
QUEUE *ballReturn(QUEUE *top, STACK *stack_object, int isHour);
int cycleComplete(QUEUE *top);

/**
 * @function int main()
 * @brief Entry point of program.
 * @return int 0
 */
int main()
{
    int  number_of_cycles = CYCLES;
    int  count_cycles = 0;
    long count_loops = 0L;

    //
    // Initialize the clock to 1:00
    //
    QUEUE *top_queue = (QUEUE *)NULL;

    for (int i=0; i<QUEUE_SIZE; i++)
    {
        top_queue = pushQueue(top_queue, i + 1);
    }

    STACK *minute = createStack(5);
    STACK *five   = createStack(12);
    STACK *hour   = createStack(12);

    addBall(hour, NON_MOVEABLE_BALL);

    //
    // Step through the clock
    //
    int   queue_ball_number;
    int   days = 0;
    float day  = .0;

    printf("Processing %d cycles on a queue size of %d\n", number_of_cycles, QUEUE_SIZE);

    do
    {
        ++count_loops;

        //
        // Cycle the clock by taking one ball from the queue and adding it to the minute stack.
        //
        if ((top_queue = popQueue(top_queue, &queue_ball_number)) == (QUEUE *)NULL)
        {
            fprintf(stderr, "Ran out of balls in the queue!\n");
            exit(-1);
        }

        //
        // When the last ball number from the queue is pulled from the queue then increment the count_cycles.
        //
        if (queue_ball_number == QUEUE_SIZE)
            ++count_cycles;

        if (minute->number_of_balls == 4)
        {
            top_queue = ballReturn(top_queue, minute, 0);

            //
            // Queue ball drops through hole onto the five minute stack tray
            //
            if (five->number_of_balls == 11)
            {
                top_queue = ballReturn(top_queue, five, 0);

                //
                // Queue ball drops through hole onto the hour stack tray
                //
                if (hour->number_of_balls == 12)
                {
                    day += .5;

                    if (day == 1)
                    {
                        ++days;
                        day = 0;
                    }

                    top_queue = ballReturn(top_queue, hour, 1);  // 1 means don't return ball in 1st slot

                    //
                    // Push queue ball back onto queue
                    //
                    top_queue = pushQueue(top_queue, queue_ball_number);
                }
                else
                {
                    addBall(hour, queue_ball_number);
                }
            }
            else
            {
                addBall(five, queue_ball_number);
            }
        }
        else
        {
            addBall(minute, queue_ball_number);
        }

    } while (count_cycles < number_of_cycles);

    //
    // Display clock settings and ball numbers in each tray slot and then display what is in the queue.
    //
    displayAll(top_queue, minute, five, hour, day, days);

    return 0;
}

/**
 * @function QUEUE *ballReturn(QUEUE *top, STACK *stack_object, int isHour)
 * @brief This function pops all the balls of a stack and returns them to the queue.
 *
 * @param QUEUE *top            This is the top of the queue
 * @param STACK *stack_object   This is the stack we want to operate on
 * @param int isHour            Is this the hour stack? If yes, don't remove ball in slot 1
 * @return QUEUE *              New pointer to queue top
 */
QUEUE *ballReturn(QUEUE *top, STACK *stack_object, int isHour)
{
    QUEUE *new_top = top;
    int ball_number;

    while (stack_object != NULL && stack_object->number_of_balls > 0)
    {
        if (stack_object->number_of_balls == 1 && isHour)
        {
            //
            // The first ball (999) in the hour tray never moves.
            //
            break;
        }

        ball_number = removetBall(stack_object);
        new_top = pushQueue(new_top, ball_number);
    }

    return new_top;
}

/**
 * @function void displayAll(QUEUE *top, STACK *minute, STACK *five, STACK *hour, float day, int days)
 * @brief This function is used to display all the time data in the ball clock.
 *
 * @param QUEUE *top      Top of the queue
 * @param STACK *minute   Minute stack
 * @param STACK *five     Five minute stack
 * @param STACK *hour     Hour stack
 * @param float day       What part of the day is it 0 is AM, .5 is PM
 * @param int days        Number of days since clock start
 */
void displayAll(QUEUE *top, STACK *minute, STACK *five, STACK *hour, float day, int days)
{
    displayHeader();
    displayStack("minute", minute);
    displayStack("five", five);
    displayStack("hour", hour);
    displayTime(minute, five, hour, day, days);
    displayQueue(top);
}
