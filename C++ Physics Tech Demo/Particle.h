#ifndef PARTICLE_H
#define	PARTICLE_H
#include <SDL2/SDL.h>

#include "Point.h"
#include "Constants.h"

class Particle
{
	private:
		Point pos;
		Point vel;
		const double rad;
		const double mass;
		SDL_Texture* text;
	
	public:
		Particle();
		~Particle();
		Particle(const Point& newpos, const double newmass);
		double aX;
		double aY;
		
		Point getPos() const { return pos; };
		double getXPos() const { return pos.getX();};
		double getYPos() const { return pos.getY();};
		void setPos(const Point& newpos) { pos.setX(newpos.getX()); pos.setY(newpos.getY());};
		void setPos(const double newx, const double newy){pos.setX(newx); pos.setY(newy);};
		void setXPos(const double newx){pos.setX(newx);};
		void setYPos(const double newy){pos.setY(newy);};
		
		Point getVel() const { return vel; };
		double getXVel() const { return vel.getX();};
		double getYVel() const { return vel.getY();};
		void setVel(const Point& newvel) {vel = newvel;};
		void setVel(const double newx, const double newy) {vel.setX(newx); vel.setY(newy);};
		void setXVel(const double newx) {vel.setX(newx);};
		void setYVel(const double newy) {vel.setY(newy);};
		
		void setTexture(SDL_Texture* newText);
		SDL_Texture* getTexture() const;
		
		double getRadius() const { return rad;};
		double getMass() const { return mass;};
		
		Point& calculateDistance(const Particle& target) const;
		void gforce(const Particle& target, const double dt);

};

#endif
