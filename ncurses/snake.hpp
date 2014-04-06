//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Sun Apr  6 13:50:00 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>
# include <unistd.h>
# include <sstream>
# include <fcntl.h>
# include <stdio.h>
# include <ncurses.h>
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
  /**
   **loop funcs
   **/
  void		my_flip() const;
  void		apply_snake(const std::list<Pos>&);
  void		draw_img(const std::list<Pos>&);
  void		init(const int &w, const int &h);
  void		testsize();
  /**
   **init funcs
   **/
  void		end() const;
  void		load();
  /**
   **apply funcs
   **/
  Key		refresh_screen(const std::list<Pos> &, const int&, const int&);
  void	        apply_surface(int x, int y, const State &state) const;
  void          check_konami(const int);
  /**
   **joy funcs
   **/
  Key		game_pause() const;
  void		init_joystick();
  Key		update_joystick() const;
  ~Snake() {};

private:
  int		_score;
  int		_width;
  int		_height;
  WINDOW	*window;
  WINDOW	*score;
  int		_fd;
  int		_joy;
};

#endif /*!_SNAKE_HPP*/
