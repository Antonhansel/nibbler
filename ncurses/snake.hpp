//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Fri Mar 21 11:33:06 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <curses.h>
# include <map>
# include <error.h>
# include <sys/ioctl.h>
# include <dlfcn.h>
# include <unistd.h>
# include "/usr/include/linux/joystick.h"
# include "../sources/IGraphic.hh"

class Snake : public IGraphic
{
public:
  void		my_flip();
  void		apply_snake(std::list<Pos>&);
  void		draw_img(std::list<Pos>&);
  void		init(int w, int h);
  void		testsize();

  void		end();
  void		load();
  
  void		init_joystick();
  Key		update_joystick();
  
  Key		refresh_screen(std::list<Pos> &, int, int);
  void	        apply_surface(int x, int y, State state);
  ~Snake() {};

struct   winsize _w;
  int		_width;
  int		_height;
  WINDOW	*window;
  int		_fd;
  int		_joy;
};

#endif /*!_SNAKE_HPP*/
