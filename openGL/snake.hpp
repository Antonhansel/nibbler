//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//o
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Sun Apr  6 13:41:56 2014 ribeaud antonin

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
# include <map>
# include <unistd.h>
# include "/usr/include/linux/joystick.h"
# include "../sources/IGraphic.hh"

#define NAME	"SNAKE_OPENGL"
#define	BPP	32
#define SP_SIZE 32

class Snake : public IGraphic
{
public:
  /**
   **loop funcs
   **/
  void		draw_block(const int &x, const int &y, const int &state) const;
  Key		refresh_screen(const std::list<Pos> &, const int&, const int&);
  void		my_flip() const;
  void		draw_img(const std::list<Pos>&) const;
  /**
   **init funcs
   **/
  void		init(const int &w, const int &h);
  void		init_lights() const;
  void		set_values();
  GLuint	load_texture(char const *filename) const;
  void		camera_movements(const int &state, const std::list <Pos> &list);
  void		end_opengl(const std::list <Pos> &list);
  /**
   **apply funcs
   **/
  void		apply_wall() const;
  void		apply_bg() const;
  void		apply_snake(const std::list<Pos>&) const;
  /**
   **joy funcs
   **/
  Key		game_pause() const;
  Key		update_joystick() const;
  void		init_joystick();
  void          check_konami(int);
  ~Snake() {};

private:
  GLuint	*_texture;
  SDL_Event	_event;
  SDL_Surface	*_screen;
  Key		_key;
  int		_width;
  int		_height;
  int		_delay;
  int		_score;
  int		_fd;
  int		_joy;
  int		_start;
};

#endif /*!_SNAKE_HPP*/
