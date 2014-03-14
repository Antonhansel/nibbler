//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Fri Mar 14 13:06:51 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include "SDL/SDL.h"
# include "SDL/SDL_mixer.h"
# include "SDL/SDL_ttf.h"
# include "SDL/SDL_image.h"
# include "GL/gl.h"
# include "GL/glu.h"
# include "/usr/include/linux/joystick.h"
# include "../../sources/IGraphic.hh"
# include <string>
# include <iostream>

#define NAME	SNAKE_SDL
#define HEIGHT	632
#define WIDTH	832
#define	BPP	32

class Snake : public IGraphic
{
public:
  SDL_Surface	*load_image(std::string &filename);
  void		apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest);
  void		my_flip();
  void		start_snake();
  void		keys();
  void		apply_wall();
  virtual  void		init(int w, int h);
  Key		refresh(std::list<Pos>);

private:
  SDL_Surface	*_screen;
  SDL_Surface	*_snake;
  SDL_Surface	*_apple;
  SDL_Surface	*_bg;
  SDL_Surface	*_wall;
  TTF_Font	*_font;	
  size_t	_current;
  size_t	_next;
  size_t	_quit;
  SDL_Event	_event;
  char		event[SDLK_LAST];
};

#endif /*!_OPENGL_HPP*/
