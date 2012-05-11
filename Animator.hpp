#pragma once

//! This is an interface for an object that is animated (i.e. may change over
//! time)
class Animator
{
public:
	//! update based on the amount of time passed, dt.
	//! \param dt The amount of time since this was last called, in seconds.
	virtual void animate(double dt) = 0;
};

