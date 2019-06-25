/**
 * @file      container.h
 * @author    Spencer Parkin
 * @copyright 2019 - All Rights Reserved
 * @date      6/24/2019
 * @version   1.0
 *
 * @brief     Ball container can act as stack or queue.
 *
 */

#pragma once

#include "ball.h"

class BallContainer
{
public:

	BallContainer(void);
	virtual ~BallContainer(void);

	void push_front(int ball_number);
	void push_back(int ball_number);
	bool pop_front(int& ball_number);
	bool pop_back(int& ball_number);

	void clear(void);
	int size(void) const { return count; }

	const Ball* operator[](int i) const;

private:
	Ball* first;
	Ball* last;
	int count;
};