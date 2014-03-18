//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Tue Mar 18 10:29:59 2014 ribeaud antonin
//

#include "snake.hpp"

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}

void		Snake::init(int w, int h)
{
  if (ioctl(0, TIOCGWINSZ, &_w) == -1)
    error(1, 0, "ioctl failed");
  _width = w;
  _height = h;
  initscr();
  testsize();
  curs_set(0);
  cbreak();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  window = newwin(_height, _width, (LINES - _height) / 2, (COLS - _width) / 2);
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  my_flip();
}

void		Snake::testsize()
{
  if (_w.ws_row < _height || _w.ws_col < _width)
    {
      mvprintw(_w.ws_row - 2, 0, "This screen has %d rows and %d columns\n", _w.ws_row, _w.ws_col);
      printw("Try resizing your window(if possible) and then run this program again");
      while (_w.ws_row < _height || _w.ws_col < _width)
	{
	  if (ioctl(0, TIOCGWINSZ, &_w) == -1)
	    error(1, 0, "ioctl failed");
	}
    }
}

Key		Snake::refresh_screen(std::list<Pos> &list, int delay)
{
  int	key;
  
  timeout(delay);
  key = 0;
  if (delay == 0)
    end();
  else
    {
      draw_img(list);
      key = wgetch(window);
      if (key == KEY_LEFT)
	{
	  end();
	  return (LEFT);
	}
      if (key == KEY_RIGHT)
	return (RIGHT);
      if (key == KEY_UP)
	{
	  end();
	  return (ESCAPE);
	}
    }
  return (OTHER);
}

// ---------------------------------
// ------------GAME BASE------------
// ---------------------------------

void		Snake::draw_img(std::list<Pos> &list)
{
  wclear(window);
  clear();
  apply_snake(list);
  my_flip();
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    apply_surface((*i).x, (*i).y, (*i).state);
}

void	        Snake::apply_surface(int x, int y, State state)
{
  move(x, y);
  if (state == 14)
    addch('O');
  else
    addch(ACS_CKBOARD);
  move(0, 0);
}

void		Snake::my_flip()
{
  wrefresh(window);
}

void		Snake::end()
{
  noraw();
  echo();
  nocbreak();
  endwin();
}
