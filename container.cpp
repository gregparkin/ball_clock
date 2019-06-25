/**
 * @file      container.cpp
 * @author    Spencer Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/24/2019
 * @version   1.0
 *
 * @brief     Ball container can act as stack or queue.
 *
 */

#include "container.h"

 /**
  * @function
  * @brief
  */
BallContainer::BallContainer(void)
{
	first = nullptr;
	last = nullptr;
	count = 0;
}

/*virtual*/ BallContainer::~BallContainer(void)
{
	clear();
}

/**
 * @function clear
 * @brief    Free all container memory.
 */
void BallContainer::clear(void)
{
	int ball_number;

	while (pop_back(ball_number))
	{
	}
}

/**
 * @function push_back
 * @brief Push a ball into the back of the container.
 *
 * @param ball_number -- input
 */
void BallContainer::push_back(int ball_number)
{
	Ball* ball = new Ball(ball_number);

	if (count == 0)
		first = last = ball;
	else
	{
		last->next = ball;
		ball->prev = last;
		last = ball;
	}

	count++;
}

/**
 * @function push_front
 * @brief Push a ball into the front of the container.
 *
 * @param ball_number -- input
 */
void BallContainer::push_front(int ball_number)
{
	Ball* ball = new Ball(ball_number);

	if (count == 0)
		first = last = ball;
	else
	{
		first->prev = ball;
		ball->next = first;
		first = ball;
	}

	count++;
}

/**
 * @function pop_back
 * @brief Pop a ball from the back of the container.
 *
 * @param ball_number -- output
 * @return Return false if already empty.
 */
bool BallContainer::pop_back(int& ball_number)
{
	if (count == 0)
		return false;

	Ball* ball = last;

	if (count == 1)
	{
		first = nullptr;
		last = nullptr;
	}
	else
	{
		last = last->prev;
		last->next = nullptr;
	}

	ball_number = ball->ball_number;
	delete ball;
	count--;
	return true;
}

/**
 * @function pop_front
 * @brief Pop a ball from the front of the container.
 *
 * @param ball_number -- output
 * @return Return false if already empty.
 */
bool BallContainer::pop_front(int& ball_number)
{
	if (count == 0)
		return false;

	Ball* ball = last;

	if (count == 1)
	{
		first = nullptr;
		last = nullptr;
	}
	else
	{
		first = first->next;
		first->prev = nullptr;
	}

	ball_number = ball->ball_number;
	delete ball;
	count--;
	return true;
}

const Ball* BallContainer::operator[](int i) const
{
	Ball* ball = first;

	// This is not very efficient, but it will work.
	while (i > 0 && ball != nullptr)
	{
		ball = ball->next;
		i--;
	}

	return ball;
}