//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Sun Apr  6 14:55:04 2014 ribeaud antonin
//

#include "snake.hpp"

void		Snake::init(const int &w, const int &h)
{
  _width = w;
  _height = h;
  initscr();
  clear();
  noecho();
  cbreak();
  nodelay(stdscr, TRUE);
  nodelay(window, TRUE);
  score = newwin(3, _width + 2, 0, 0);
  window = newwin(_height + 1, _width + 2, 3, 0);
  keypad(stdscr, TRUE);
  keypad(window, TRUE);
  _joy = -1;
  curs_set(0);
  init_joystick();
  testsize();
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  wborder(score, '|', '|', '-', '-', '+', '+', '+', '+');
  my_flip();
}

void		Snake::testsize()
{
  struct   winsize _w;

  if (ioctl(1, TIOCGWINSZ, &_w) == -1)
    error(1, 0, "ioctl failed");
  if (_w.ws_row < _height + 1 || _w.ws_col < _width + 4)
    {
      endwin();
      while (_w.ws_row < _height + 1 || _w.ws_col < _width + 4)
	{
	  wclear(window);
	  clear();
	  move(0, 0);
	  addstr("Resize your window");
	  refresh();
	  if (ioctl(1, TIOCGWINSZ, &_w) == -1)
	    error(1, 0, "ioctl failed");
	}
      score = newwin(3, _width + 2, 0, 0);
      window = newwin(_height + 1, _width + 2, 3, 0);
    }
}

void            Snake::check_konami(const int code)
{
  static        int i = 0;

  if (i <= 1 && code == 0403)
    i++;
  else if ((i == 2 || i == 3) && code == 0402)
    i++;
  else if ((i == 4 || i == 6) && code == 0404)
    i++;
  else if ((i == 5  || i == 7) && code == 0405)
    i++;
  else if (i == 8 && code == 'b')
    i++;
  else if (i == 9 && code == 'a')
    _joy *= -1;
  else
    i = 0;
}

Key		Snake::refresh_screen(const std::list<Pos> &list, const int &delay, const int &score)
{
  int	key;

  _score = score;
  usleep(delay * 1000);
  key = 0;
  if (delay == 1)
    end();
  else
    {
      draw_img(list);
      if (_fd > 0 && _joy == 1)
	return (update_joystick());
      else
	{
	  wtimeout(window, 0);
	  key = getch();
	  check_konami(key);
	  if (key == 0404)
	    return (LEFT);
	  if (key == 0405)
	    return (RIGHT);
	  if (key == 27)
	    {
	      end();
	      return (ESCAPE);
	    }
	}
    }
  return (OTHER);
}

/*#######################################*/
/*############ APPLY FUNCS ##############*/
/*#######################################*/

void		Snake::draw_img(const std::list<Pos> &list)
{
  std::stringstream	newscore;
  std::string		temp;
  char const		*temp2;
  
  newscore << "Score: " <<  _score;
  temp = newscore.str();
  temp2 = (char*)temp.c_str();
  testsize();
  wclear(window);
  wclear(score);
  wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  wborder(score, '|', '|', '-', '-', '+', '+', '+', '+');
  mvwaddstr(score, 1, (_width/2) - 3, temp2);
  apply_snake(list);
  my_flip();
}

void		Snake::apply_snake(const std::list<Pos> &list)
{
  for (std::list<Pos>::const_iterator i = list.begin(); i != list.end(); ++i)
    apply_surface((*i).x, (*i).y, (*i).state);
}

void	        Snake::apply_surface(int x, int y, const State &state) const
{
  static	int blink = -1;

  wmove(window, y+1, x+1);
  if (state == 14)
    waddch(window, 'O');
  else if (state == 15)
    {
      if (blink == -1)
	{
	  wattron(window, A_REVERSE |A_BLINK);
	  waddch(window, '0');
	  wattroff(window, A_REVERSE | A_BLINK);
	}
      else
	waddch(window, '0');
      blink *= -1;
    }
  else
    waddch(window, ACS_CKBOARD);
}

void		Snake::my_flip() const
{
  wrefresh(window);
  wrefresh(score);
}

void		Snake::end() const
{
  noraw();
  echo();
  nocbreak();
  endwin();
}

/*#######################################*/
/*############## JOYSTICK ###############*/
/*#######################################*/

void		Snake::init_joystick()
{
  _fd = open("/dev/input/js1", O_NONBLOCK);
  if (_fd > 0)
    std::cout << "Joystick detected. Use KONAMI code to activate\n" << std::endl;
  else
    std::cout << "Unable to detect joystick\n" << std::endl;
}

Key			Snake::game_pause() const
{
  struct js_event	e;

  while (42)
    {
      usleep(100);
      if (read(_fd, &e, sizeof(struct js_event)) > 0 && 
	  (e.type &= JS_EVENT_BUTTON) && e.value == 1 && e.number == 8)
	return (OTHER);
    }
}

Key		Snake::update_joystick() const
{
  struct js_event	e;

  while (read(_fd, &e, sizeof(struct js_event)) > 0)
    {
      if (e.type &= JS_EVENT_BUTTON)
	{
	  if (e.value == 1)
	    {
	      if (e.number == 8)
		return (game_pause());
	    }	
	}
      else
	{
	  if (e.number == 0)
	    {
	      if (e.value > 32700)
		return (RIGHT);
	      else if (e.value < -32700)
		return (LEFT);
	    }
	}
    }
  return (OTHER);
}

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}
