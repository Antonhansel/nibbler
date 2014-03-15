//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Fri Mar 14 19:46:53 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include "/usr/include/linux/joystick.h"
# include "../sources/IGraphic.hh"

#define NAME	SNAKE_SDL
#define HEIGHT	632
#define WIDTH	832
#define	BPP	32

#define SP_SIZE 64

class Snake : public IGraphic
{
public:
  SDL_Surface	*load_image(std::string &filename);
  void		apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest);
  void		my_flip();
  void		apply_wall();
  void		init(int w, int h);
  Key		refresh(std::list<Pos>, int);
  ~Snake() {};
private:
  static std::string bg_path;
  static std::string wall_path;
private:
  SDL_Surface	*_screen;
  SDL_Surface	*_snake;
  SDL_Surface	*_apple;
  SDL_Surface	*_bg;
  SDL_Surface	*_wall;
  TTF_Font	*_font;
  SDL_Event	_event;
  int _width;
  int _height;
};

std::string Snake::bg_path = "SDL/img/bg.jpg";
std::string Snake::wall_path = "SDL/img/wood1.png";

#endif /*!_SNAKE_HPP*/
