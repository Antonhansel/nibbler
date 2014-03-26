//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Tue Mar 25 17:37:23 2014 ribeaud antonin
//

#include "snake.hpp"

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}

void		Snake::init(const int &w, const int &h)
{
  _width = w;
  _height = h;
  initscr();
  clear();
  noecho();
  curs_set(0);
  raw();
  window = newwin(_height + 2, _width + 2, 0, 0);
  cbreak();
  nodelay(stdscr, TRUE);
  //notimeout(window, TRUE);
  scrollok(stdscr, TRUE);
  keypad(stdscr, TRUE);
  _joy = 1;
  init_joystick();
  if (ioctl(0, TIOCGWINSZ, &_w) == -1)
    error(1, 0, "ioctl failed");
  testsize();
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  my_flip();
}

void		Snake::testsize()
{
  while (_w.ws_row < _height || _w.ws_col < _width)
    {
      wclear(window);
      clear();
      move(0, 0);
      addstr("Resize your window");
      refresh();
      if (ioctl(0, TIOCGWINSZ, &_w) == -1)
      	error(1, 0, "ioctl failed");
    }
}

Key		Snake::refresh_screen(std::list<Pos> &list, const int &delay, const int &score)
{
  int	key;
  
  usleep(delay * 1000);
  key = 0;
  if (delay == 0)
    end();
  else
    {
      draw_img(list);
      if (_fd > 0 && _joy == 1)
	return (update_joystick());
      else
	{
	  wborder(window, 'L', 'L', 'L', 'L', 'L', 'L', (char)(key/10 + 48), (char)(key%10 + 48));
	  wtimeout(window, delay);
	  //key = mvwgetch(window, 0, 0);
  	  //timeout(delay);
	  key = wgetch(window);
	  wborder(window, 'L', 'L', 'L', 'L', 'L', 'L', (char)(key/10 + 48), (char)(key%10 + 48));
	  if (key == KEY_LEFT)
	    return (LEFT);
	  if (key == KEY_RIGHT)
	    return (RIGHT);
	  if (key == KEY_UP)
	    {
	      end();
	      return (ESCAPE);
	    }
	}
    }
  return (OTHER);
}

// ---------------------------------
// ------------GAME BASE------------
// ---------------------------------

void		Snake::draw_img(std::list<Pos> &list)
{
  testsize();
  wclear(window);
  box(window, 0, 0);
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
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
  wmove(window, x, y);
  if (state == 14)
    waddch(window, 'O');
  else
    waddch(window, ACS_CKBOARD);
  //move(0, 0);
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

//
// JOYSTICK
//

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
		{
		  end();
		  return (ESCAPE);
		}
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
