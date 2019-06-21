#include "Particle.h"

Particle::Particle()
: rad(1.0), mass(1.0)
{
	pos.setX(0.0);
	pos.setY(0.0);
	vel.setX(0.0);
	vel.setY(0.0);
}

Particle::Particle(const Point& newpos, const double newmass)
: mass(newmass), rad((MAX_RADIUS*newmass)/MAX_MASS + 20)
{
	pos.setX(newpos.getX());
	pos.setY(newpos.getY());
	vel.setX(0.0);
	vel.setY(0.0);
}

void Particle::setTexture(SDL_Texture* newText)
{
	text = newText;
}

SDL_Texture* Particle::getTexture() const
{
	return text;
}

Particle::~Particle()
{
	if (text != NULL)
    {
        SDL_DestroyTexture(text);
    }
}

Point& Particle::calculateDistance(const Particle& target) const
{
	
	double xdist = target.getXPos() - getXPos();
	double ydist = target.getYPos() - getYPos();
	Point dist(xdist, ydist);
	return dist;
}

void Particle::gforce(const Particle& target, const double dt)
{
	if(this == &target)
	{
		return;
	}
	
	Point dist = calculateDistance(target);
	if(dist.getX() < 0)
	{
		setXVel(getXVel() - (G*target.getMass()/(dist.getX()*dist.getX()))*dt);
	}
	else
	{
		setXVel(getXVel() + (G*target.getMass()/(dist.getX()*dist.getX()))*dt);
	}
	if(dist.getY() < 0)
	{
		setYVel(getYVel() - (G*target.getMass()/(dist.getY()*dist.getY()))*dt);
	}
	else
	{
		setYVel(getYVel() + (G*target.getMass()/(dist.getY()*dist.getY()))*dt);
	}
}