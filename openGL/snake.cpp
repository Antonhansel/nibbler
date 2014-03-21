//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Fri Mar 21 18:07:59 2014 ribeaud antonin
//

#include <error.h>
#include "snake.hpp"

void		Snake::init(int w, int h)
{
  _width = w;
  _height = h;
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
      !(_screen = SDL_SetVideoMode(SP_SIZE * (_width + 2), SP_SIZE * (_height + 2), BPP, SDL_OPENGL)))
    error(1, 0, "Couldn't initialize Graphic Mode");
  SDL_WM_SetCaption(NAME, NULL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)((w+2) * 32)/((h+2) * 32), 1, 1000);
  glEnable(GL_DEPTH_TEST);
  _joy = -1;
  init_joystick();
  _height -= 1;
  _width -= 1;
  _help = -1;
}

Key		Snake::refresh_screen(std::list<Pos> &list, int delay, int score)
{
  Key		key;

  _score = score;
  _delay = delay;
  draw_img(list);
  usleep(delay * 1000);
  if (_fd > 0 && _joy == 1)
    return (update_joystick());
  else
    {
      while (SDL_PollEvent(&_event))
	{
	  if (_event.type == SDL_QUIT)
	    return (ESCAPE);
	  if (_event.type == SDL_KEYDOWN)
	    {
	      if (_event.key.keysym.sym == SDLK_LEFT)
		return (RIGHT);
	      if (_event.key.keysym.sym == SDLK_RIGHT)
		return (LEFT);
	      if (_event.key.keysym.sym == SDLK_ESCAPE)
		{
		  end_sdl();
		  return (ESCAPE);
		}
	      if (_event.key.keysym.sym == SDLK_UP)
		_help *=-1;
	      if (_event.key.keysym.sym == SDLK_DOWN)
		_joy *=-1;
	    }
	}
    }
  return (OTHER);
}

void		Snake::draw_img(std::list<Pos> &list)
{
  int		mode = 0;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    {
      if ((*i).state >= 0 && (*i).state <= 3 && _delay <= 30)
  	{
  	  mode = 1;
	  gluLookAt(-_width/5, -_width/5, _width, (*i).x-((*i).x/16), (*i).y-((*i).y/8), 0, 0, 0, 1);
	}
    }
  if (mode == 0)
    gluLookAt(-_width/5, -_width/5, _width, (_height/2 - _height/8), (_width/2 - _height/8), 0, 0, 0, 1);
  apply_bg();
  apply_wall();
  apply_snake(list);
  apply_score();
  if (_help == 1)
    load();
  my_flip();
}

void			Snake::apply_score()
{
  std::stringstream	newscore;
  std::string		temp;
  char const *		temp2;

  newscore << "Score: " <<  _score;
  temp = newscore.str();
  temp2 = (char*)temp.c_str();
}

void		Snake::apply_wall()
{
  for (int i = -1; i <= _width + 2; ++i)
    {
      draw_block(i, -1, -1);
      draw_block(i, (_height + 2), -1);
    }
  for (int i = -1; i <= _height + 2; ++i)
    {
      draw_block(-1, i, -1);
      draw_block((_width + 2), i, -1);
    }
}

void		Snake::apply_bg()
{  
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  
  glColor3ub(120, 255, 120);
  glVertex3d(-1,          -1, -1);
  glVertex3d(-1,          _height + 2, -1);
  glColor3ub(50, 255, 50);
  glVertex3d(_width + 2,  _height + 2, -1);
  glVertex3d(_height + 2, -1, -1);

  glEnd();
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    draw_block((*i).x, (*i).y, (*i).state);
}

void		Snake::loadColor(int i, int state)
{
  if (i == 1)
    {
      if (state == 14)
	glColor3ub(255,0,0);
      else if (state == -1)
	glColor3ub(0, 255, 255);
      else
	glColor3ub(0 , 0, 255);
    }
  else
    {
      if (state == 14)
	glColor3ub(0,0,255);
      else if (state == -1)
	glColor3ub(255, 255, 0);
      else
	glColor3ub(255, 0, 0);
    }
}

void		Snake::draw_block(int x, int y, int state)
{
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);

  if (state == 14)
    glColor3ub(255,0,0);
  else if (state == -1 || state == 15)
    glColor3ub(rand()%255, rand()%255, rand()%255);
  else if (state <= 3)
    glColor3ub(0 , 0, 255);
  else if (state == 6 || state == 7 || state == 8 || state == 9)
    glColor3ub(255, 150, 255);
  else
    glColor3ub(50 , 0, 190);
  glVertex3d(x,     y,      1);
  glVertex3d(x,     y,     -1);
  glVertex3d(x + 1, y,     -1);
  glVertex3d(x + 1, y,      1);

  glVertex3d(x,     y + 1,  1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x,     y,     -1);
  glVertex3d(x,     y,      1);

  glVertex3d(x + 1, y + 1,  1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x,     y + 1,  1);

  glVertex3d(x + 1, y,      1);
  glVertex3d(x + 1, y,     -1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x + 1, y + 1,  1);

  glVertex3d(x,     y,     -1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x + 1, y,     -1);

  glVertex3d(x,     y + 1,  1);
  glVertex3d(x,     y,      1);
  glVertex3d(x + 1, y,      1);
  glVertex3d(x + 1, y + 1,  1);

  glEnd();
}

void		Snake::end_sdl()
{
  SDL_Quit();
}

void		Snake::my_flip()
{
  glFlush();
  SDL_GL_SwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void		Snake::load() 
{
  int xPointCount = 40;
  int yPointCount = 40;
  double xSpacing = 1;
  double ySpacing = 1;
  double width = xSpacing * (xPointCount-1); 
  double height = ySpacing * (yPointCount-1); 
  double minX = -width/2; 
  double minY = -height/2;
  
  glBegin(GL_POINTS);
  glColor3ub(255,255,255);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 0;
	  glVertex3f(x, y, z); 
	} 
    }
  glColor3ub(255,255,150);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 5; 
	  glVertex3f(x, y, z); 
	} 
    }
  glColor3ub(150,150,255);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 10; 
	  glVertex3f(x, y, z); 
	} 
    }
  glEnd();
}

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}

void		Snake::init_joystick()
{
  _fd = open("/dev/input/js1", O_NONBLOCK);
  if (_fd > 0)
    std::cout << "Joystick detected. Press 'down' to activate\n" << std::endl;
  else
    std::cout << "Unable to detect joystick\n" << std::endl;
}

Key		Snake::update_joystick()
{
  struct js_event	e;

  while (read(_fd, &e, sizeof(struct js_event)) > 0)
    {
      if (e.type &= JS_EVENT_BUTTON)
	{
	  if (e.value == 1)
	    {
	      if (e.number == 8)
		return (ESCAPE);
	    }	
	}
      else
	{
	  if (e.number == 0)
	    {
	      if (e.value > 32700)
		return (LEFT);
	      else if (e.value < -32700)
		return (RIGHT);
	    }
	}
    }
  return (OTHER);
}
