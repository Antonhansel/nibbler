//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//o
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Mon Mar 24 16:00:01 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>
# include <unistd.h>
# include <sstream>
# include <stdio.h>
# include <fcntl.h>
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
  GLuint	load_texture(int width, int height, char const *filename);
  void		draw_img(std::list<Pos>&);

  void		init(int w, int h);
  void		init_font();
  void		init_joystick();
  void		init_lights();

  void		end_sdl();
  void		load();
  void		draw_block(int x, int y, int state);
  Key		refresh_screen(std::list<Pos> &, int, int);
  void		*keySpecial(int key, int x, int y);
  Key		keyNormal(unsigned char key, int x, int y);
  GLuint       	loadTexture(const char *filename, bool useMipMap);
  SDL_Surface	*flipSurface(SDL_Surface * surface);
  void		loadColor(int i, int state);
  Key		update_joystick();

  void		apply_score();
  void		apply_wall();
  void		apply_bg();
  void		apply_snake(std::list<Pos>&);
  void		apply_lights();

  Key		game_pause();
  void		fancy_starter(std::list<Pos> &list);

  ~Snake() {};

private:
  GLuint	_walltexture;
  SDL_Event	_event;
  SDL_Surface	*_screen;
  SDL_Surface	*_text;
  TTF_Font	*_font;
  SDL_Color	_color;
  SDL_Color	_colorpause;
  TTF_Font	*_fontscore;
  TTF_Font	*_fontmenu;
  int		_width;
  int		_height;
  Key		_key;
  int		_delay;
  int		_help;
  int		_score;
  int		_fd;
  int		_joy;
  int		_start;
};

#endif /*!_SNAKE_HPP*/
