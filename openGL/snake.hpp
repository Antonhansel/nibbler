//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Wed Mar 19 15:02:46 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <map>
# include <unistd.h>
# include "/usr/include/linux/joystick.h"
# include "../sources/IGraphic.hh"

#define NAME	"SNAKE_OPENGL"
#define HEIGHT	632
#define WIDTH	832
#define	BPP	32
#define SP_SIZE 32

class Snake : public IGraphic
{
public:
  SDL_Surface	*load_image(std::string &filename);
  void		apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest);
  void		my_flip();
  void		apply_wall();
  void		apply_bg();
  void		apply_snake(std::list<Pos>&);
  void		draw_img(std::list<Pos>&);
  void		init(int w, int h);
  void		end_sdl();
  void		load();
  void		draw_block(int x, int y, int state);
  Key		refresh_screen(std::list<Pos> &, int);
  void		*keySpecial(int key, int x, int y);
  Key		keyNormal(unsigned char key, int x, int y);
  ~Snake() {};

private:
  std::map<State, SDL_Surface *>	_snake;
  SDL_Surface	*_screen;
  SDL_Surface	*_apple;
  SDL_Surface	*_bg;
  SDL_Surface	*_wall;
  TTF_Font	*_font;
  SDL_Event	_event;
  int _width;
  int _height;
  Key	_key;

};

#endif /*!_SNAKE_HPP*/