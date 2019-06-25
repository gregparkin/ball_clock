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

#include "container.h"

#define NON_MOVEABLE_BALL   999
#define QUEUE_SIZE          28
#define CYCLES              300

void displayAll(const BallContainer& ballQueue, const BallContainer& minuteStack, const BallContainer& fiveStack, const BallContainer& hourStack, float day, int days);
void ballReturn(BallContainer& ballQueue, BallContainer& ballStack, bool isHour);

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

	BallContainer ballQueue;

    for (int i=0; i<QUEUE_SIZE; i++)
    {
		ballQueue.push_front(i + 1);
    }

	BallContainer minuteStack;
	BallContainer fiveStack;
	BallContainer hourStack;

	hourStack.push_back(NON_MOVEABLE_BALL);

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
		if(!ballQueue.pop_back(queue_ball_number))
        {
            fprintf(stderr, "Ran out of balls in the queue!\n");
            exit(-1);
        }

        //
        // When the last ball number from the queue is pulled from the queue then increment the count_cycles.
        //
        if (queue_ball_number == QUEUE_SIZE)
            ++count_cycles;

        if (minuteStack.size() == 4)
        {
            ballReturn(ballQueue, minuteStack, false);

            //
            // Queue ball drops through hole onto the five minute stack tray
            //
			if(fiveStack.size() == 11)
            {
				ballReturn(ballQueue, fiveStack, false);

                //
                // Queue ball drops through hole onto the hour stack tray
                //
				if(hourStack.size() == 12)
                {
                    day += .5;

                    if (day == 1)
                    {
                        ++days;
                        day = 0;
                    }

                    ballReturn(ballQueue, hourStack, true);  // true means don't return ball in 1st slot

                    //
                    // Push queue ball back onto queue
                    //
					ballQueue.push_front(queue_ball_number);
                }
                else
                {
					hourStack.push_back(queue_ball_number);
                }
            }
            else
            {
				fiveStack.push_back(queue_ball_number);
            }
        }
        else
        {
			minuteStack.push_back(queue_ball_number);
        }

    } while (count_cycles < number_of_cycles);

    //
    // Display clock settings and ball numbers in each tray slot and then display what is in the queue.
    //
    displayAll(ballQueue, minuteStack, fiveStack, hourStack, day, days);

    return 0;
}

/**
 * @function ballReturn
 * @brief    This function pops all the balls of a stack and returns them to the queue.
 *
 * @param BallContainer& ballQueue   ...
 * @param BallContainer& ballSTack   ...
 * @param bool isHour                Is this the hour stack?  If yes, don't remove ball in slot 1
 */
void ballReturn(BallContainer& ballQueue, BallContainer& ballStack, bool isHour)
{
    int ball_number;

	while (ballStack.size() > 0)
	{
		if (ballStack.size() == 1 && isHour)
		{
			//
			// The first ball (999) in the hour tray never moves.
			//
			break;
		}

		ballStack.pop_back(ball_number);
		ballQueue.push_front(ball_number);
	}
}

/**
 * @function void displayStack(char description[], STACK *stack_object)
 * @brief Print the contents of how this stack (minute, five, hour) looks. Lined up with displayHeader()
 *
 * @param char description[]
 * @param STACK *stack_object
 */
void displayStack(const BallContainer& ballStack, const char* description)
{
	printf("%-10s  ", description);

	for (int i = 0; i < ballStack.size(); i++)
	{
		printf("%3d ", ballStack[i]->ball_number);
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
void displayTime(const BallContainer& minuteStack, const BallContainer& fiveStack, const BallContainer& hourStack, float day, int days)
{
	int total_minutes = (fiveStack.size() * 5) + minuteStack.size();

	printf("\nCurrent TM: %d:%.2d %s, days = %d\n\n",
		hourStack.size(), total_minutes, day == 0 ? "AM" : "PM", days);
}

/**
 * @function void displayQueue(QUEUE *top)
 * @brief Print out the balls remaining in the queue.
 *
 * @param void
 */
void displayQueue(const BallContainer& ballQueue)
{
	for(int i = 0; i < ballQueue.size(); i++)
	{
		const Ball* ball = ballQueue[ballQueue.size() - 1 - i];
		printf("Queue slot %3d contains ball number: %d\n", i + 1, ball->ball_number);
	}
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
void displayAll(const BallContainer& ballQueue, const BallContainer& minuteStack, const BallContainer& fiveStack, const BallContainer& hourStack, float day, int days)
{
	printf("\n");
	printf("Tray Slots    1   2   3   4   5   6   7   8   9  10  11  12\n");
	printf("            --- --- --- --- --- --- --- --- --- --- --- ---\n");

	displayStack(minuteStack, "minute");
	displayStack(fiveStack, "five");
	displayStack(hourStack, "hour");
	displayTime(minuteStack, fiveStack, hourStack, day, days);
	displayQueue(ballQueue);
}