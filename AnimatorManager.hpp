#pragma once

#include <list>

#include "Animator.hpp"

//! Maintains a list of Animator objects and keeps track of the last time its
//! animate method was called.
class AnimatorManager
{
public:
	AnimatorManager(void);

	//! Sends an animate call out to all added animators
	void animate();

	//! Adds an animator the list of subscribed animators
	void addanimator(const std::shared_ptr<Animator>& in)
	{ this->animators.push_back(in); }

private:
	unsigned int timelast, timenow;

	std::list<std::shared_ptr<Animator>> animators;
};

