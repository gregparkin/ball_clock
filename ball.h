/**
 * @file      ball.h
 * @author    Spencer Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/24/2019
 * @version   1.0
 *
 * @brief     Ball representation
 *
 */

#pragma once

class Ball
{
public:

	Ball(int ball_number);
	virtual ~Ball(void);

	int ball_number;
	Ball* next;
	Ball* prev;
};
