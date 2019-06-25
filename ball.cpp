/**
 * @file      ball.cpp
 * @author    Spencer Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/24/2019
 * @version   1.0
 *
 * @brief     Ball representation
 *
 */

#include "Ball.h"

Ball::Ball(int ball_number)
{
	this->ball_number = ball_number;
	next = nullptr;
	prev = nullptr;
}

/*virtual*/ Ball::~Ball(void)
{
}
