//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Wed Mar 19 18:06:42 2014 ribeaud antonin
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
  _height -= 1;
  _width -= 1;
}

void		Snake::draw_img(std::list<Pos> &list)
{
  static	int i = 0;

  int		zoom = 15;
  i += 3;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
  //   if ((*i).state == 0)
  //     gluLookAt(0, zoom, zoom, _height/2, _width/2, 0, 0, 0, 1);
  //   else if ((*i).state == 1)
  //     gluLookAt(-zoom, 0, zoom, _height/2, _width/2, 0, 0, 0, 1);
  //   else if ((*i).state == 2)
  //     gluLookAt(0, -zoom, zoom, _height/2, _width/2, 0, 0, 0, 1);
  //   else if ((*i).state == 3)
  //     gluLookAt(zoom, 0, zoom, _height/2, _width/2, 0, 0, 0, 1);
  gluLookAt(0, 0, 20, _height/2, _width/2, 0, 0, 0, 1);
  apply_bg();
  apply_wall();
  load();
  apply_snake(list);
  my_flip();
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
  glColor3ub(0,255,0);

  glVertex3d(-1,         _width + 2, -1);
  glVertex3d(_width + 2, _height + 2, -1);
  glVertex3d(_height + 2, -1, -1);
  glVertex3d(-1,         _height + 2, -1);

  glEnd();
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    draw_block((*i).x, (*i).y, (*i).state);
}

void		Snake::draw_block(int x, int y, int state)
{
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);

  if (state == 14)
    glColor3ub(255,0,0);
  else if (state == -1)
    glColor3ub(0, 255, 255);
  else
    glColor3ub(0 , 0, 255);
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

  /*teeeeest*/

  // glVertex3d(x,y,-1);
  // glVertex3d(-x,y,-1);
  // glVertex3d(-x,y,1);

  // glVertex3d(x,-y,1);
  // glVertex3d(x,-y,-1);
  // glVertex3d(x,y,-1);
  // glVertex3d(x,y,1);

  // glVertex3d(-x,-y,1);
  // glVertex3d(-x,-y,-1);
  // glVertex3d(x,-y,-1);
  // glVertex3d(x,-y,1);

  // glVertex3d(-x,y,1);
  // glVertex3d(-x,y,-1);
  // glVertex3d(-x,-y,-1);
  // glVertex3d(-x,-y,1);

  // glVertex3d(x,y,-1);
  // glVertex3d(x,-y,-1);
  // glVertex3d(-x,-y,-1);
  // glVertex3d(-x,y,-1);

  // glVertex3d(x,-y,1);
  // glVertex3d(x,y,1);
  // glVertex3d(-x,y,1);
  // glVertex3d(-x,-y,1);

  glEnd();
}

Key		Snake::refresh_screen(std::list<Pos> &list, int delay)
{
  static	int i = 1;
  Key		key;

  draw_img(list);
  usleep(delay * 1000);
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
        }
    }
  return (OTHER);
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
