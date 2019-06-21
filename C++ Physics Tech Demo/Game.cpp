//Joeshua Baker
//Homework 5
//Completed 3/13/2016

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game(int argc) 
    : width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), 
      start(0), last(0), current(0), 
      good(true), running(false), 
      particles(std::vector<Particle>())
{
    // Seed the random number generator
    srand(time(0));
	
	// Check if doppler mode is enabled
	if(argc == 1)
	{
		doppler = false;
	}
	else
	{
		doppler = true;
	}
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        good = false;
        return;
    }
    
    // initialize SDL window
    window = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        good = false;
        return;
    }
    
    // initialize SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        good = false;
        return;
    }
    
    // initialize particle texture
    SDL_Surface* bmp = SDL_LoadBMP("particle.bmp");
    if (bmp == NULL)
    {
        good = false;
        return;
    }
    particleTexture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    
    // initialize our particles
    for (int i = 0; i < PARTICLE_COUNT; ++i)
    {
        particles.push_back(randomParticle());
		SDL_Surface* bmp = SDL_LoadBMP("particle.bmp");
		if (bmp == NULL)
		{
			good = false;
			return;
		}
		particles[i].setTexture(SDL_CreateTextureFromSurface(renderer, bmp));
		SDL_FreeSurface(bmp);
    }
}

Game::~Game()
{
    if (!good)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    }
    if (particleTexture != NULL)
    {
        SDL_DestroyTexture(particleTexture);
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

int Game::operator()()
{
    if (!good)
    {
        return -1;
    
	
	//init start of game state
    running = true;
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    start = SDL_GetTicks();
    last = start;

	//main game loop
    while (running) // every iteration is 1 frame
    {
        current = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            handleEvent(event);
        }
        update((current - last) / 1000.0);
        render();
        last = current;
    }

    return 0;
}

// dt is time since last frame in seconds
void Game::update(double dt)
{
	
	double diffX;
	double diffY;
	double distance;
	
	//calculate distance from each particle to each other particle
	for (Particle& p: particles)
	{
		SDL_SetTextureColorMod(p.getTexture(), 255, 255, 255);
		
		double tempaX = 0;
		double tempaY = 0;
		std::vector<Particle> collisions;
		collisions.clear();
		for(const Particle& t: particles)
		{
			if(&p == &t)
				continue;
			
			diffX = p.getXPos() - t.getXPos();
			diffY = p.getYPos() - t.getYPos();
			
			//If these two particles are not colliding, calculate the force 
			//of gravity this particle exerts on our main particle and add
			//it to the average of all particles checked.
			if(!collideBoundingCircle(p.getXPos(), p.getYPos(), p.getRadius(),
									  t.getXPos(), t.getYPos(), t.getRadius(), 0))
			{
				distance = sqrt((diffX*diffX) + (diffY*diffY));
				double Fnet = ((G * p.getMass() * t.getMass()))/(distance * distance);
				double theta = atan2(diffY, diffX);
				double accel = Fnet / p.getMass();
				tempaX += -(accel * cos(theta));
				tempaY += -(accel * sin(theta));
			}
			//otherwise, add this to the collision list to be handled later
			else
			{
				collisions.push_back(t);
			}
			
		}
		
		//apply forces due to gravity
		p.setXVel(tempaX);
		p.setYVel(tempaY);

		//for each collision, calculate force using formula for elastic collision
		//between two rigid bodies. This is kind of gross, but only used here.
		for(Particle& t: collisions)
		{
			
			double pxv = p.getXVel()/dt;
			double pyv = p.getYVel()/dt;
			double txv = t.getXVel()/dt;
			double tyv = t.getYVel()/dt;
			double piv = sqrt((pxv*pxv) + (pyv*pyv));
			double ptheta = atan2(pyv, pxv);
			double tiv = sqrt((txv*txv) + (tyv*tyv));
			double ttheta = atan2(tyv, txv);
			diffX = p.getXPos() - t.getXPos();
			diffY = p.getYPos() - t.getYPos();
			double ctheta = atan2(diffY, diffX);
			double m1 = p.getMass();
			double m2 = t.getMass();
			
			
			p.setXVel((((((piv*cos(ptheta-ctheta)*(m1 - m2)) + (2*m2*tiv*cos(ttheta-ctheta)))/(m1 + m2))*cos(ctheta)) + (piv*sin(ptheta-ctheta)*cos(ctheta + (PI/2))))*dt);
			p.setYVel((((((piv*cos(ptheta-ctheta)*(m1 - m2)) + (2*m2*tiv*cos(ttheta-ctheta)))/(m1 + m2))*sin(ctheta)) + (piv*sin(ptheta-ctheta)*sin(ctheta + (PI/2))))*dt);
			
			t.setXVel((((((tiv*cos(ttheta-ctheta)*(m2 - m1)) + (2*m1*piv*cos(ptheta-ctheta)))/(m2 + m1))*cos(ctheta)) + (tiv*sin(ttheta-ctheta)*cos(ctheta + (PI/2))))*dt);
			t.setYVel((((((tiv*cos(ttheta-ctheta)*(m2 - m1)) + (2*m1*piv*cos(ptheta-ctheta)))/(m2 + m1))*sin(ctheta)) + (tiv*sin(ttheta-ctheta)*sin(ctheta + (PI/2))))*dt);
			
		}
		
		//finally, check if we've passed one of our walls. If we have,
		//bounce off elastically by reversing x or y velocity
		if(p.getXPos() < 0 || p.getXPos() > 800)
		{
			p.setXVel(p.getXVel()*-1);
		}
		if(p.getYPos() < 0 || p.getYPos() > 600)
		{
			p.setYVel(p.getYVel()*-1);
		}
		
	}
	
	//calculate new positions for all our particles and move them.
	for (Particle& j:particles)
	{
		Point pos(j.getXPos() + j.getXVel(), j.getYPos() + j.getYVel());
		j.setPos(pos);
	}
}

void Game::render()
{
    SDL_RenderClear(renderer);
    
    // rendering here would place objects beneath the particles
    
    for (const Particle& p : particles)
    {
		if(doppler)
		{
			drawDoppler(p);
		}
		else
		{
			drawParticle(p);
		}
    }
    
    // rendering here would place objects on top of the particles
    
    SDL_RenderPresent(renderer);
}

void Game::handleEvent(const SDL_Event& event)
{
	//currently, only need to handle quit event,
	//TODO: add event for pause
    switch (event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    default:
        break;
    }
}

//make renderer calls to draw the particleTexture over a radius r
void Game::drawParticle(const Particle& p)
{
    SDL_Rect dst;
    double shift = p.getRadius();
    dst.x = (int) (p.getPos().getX() - shift);
    dst.y = (int) (p.getPos().getY() - shift);
    dst.w = shift * 2;
    dst.h = shift * 2;
    SDL_RenderCopy(renderer, particleTexture, NULL, &dst);
}

//Function to apply the doppler effect to particles traveling towards/away
//from the center of the game
void Game::drawDoppler(const Particle& p)
{
	SDL_Rect dst;
    double shift = p.getRadius();
    dst.x = (int) (p.getPos().getX() - shift);
    dst.y = (int) (p.getPos().getY() - shift);
    dst.w = shift * 2;
    dst.h = shift * 2;
	
	if(p.getVel().getX() > 0)
	{
		SDL_SetTextureColorMod(p.getTexture(), 255, 255 - (int)p.getXVel()* 25500, 255 - (int)p.getXVel()* 25500);
	}
	else if(p.getVel().getX() < 0)
	{
		SDL_SetTextureColorMod(p.getTexture(), 255 - (int)p.getXVel()* 25500, 255 - (int)p.getXVel()* 25500 , 255);
	}
    SDL_RenderCopy(renderer, p.getTexture(), NULL, &dst);
}

//Generate a particle with random mass and position.
Particle Game::randomParticle() const
{
    Point pos(rand() % width, rand() % height);
    
    // using random percentage of MAX_MASS
    double mass = ((double) rand() / RAND_MAX) * MAX_MASS + 1.0;
    
    return Particle(pos, mass);
}

//Check collision between two objects given x,y,r for each.WS
bool Game::collideBoundingCircle(int x1, int y1, int radius1, int x2, int y2, int radius2, int offset)
{
	int distx = abs((int)(x1 - x2));
	int disty = abs((int)(y1 - y2));
	return(sqrt((distx * distx) + (disty * disty)) - radius1 - radius2 <= offset);
}