//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Wed Mar 26 10:36:44 2014 ribeaud antonin
//

#include <error.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "snake.hpp"

void		Snake::init_font()
{
  _fontscore = TTF_OpenFont("img/snake.ttf", 60);
  _fontmenu = TTF_OpenFont("img/menu.ttf", 60);
  _color.r = 255;
  _color.g = 0;
  _color.b = 0;
  _colorpause.r = 255;
  _colorpause.g = 255;
  _colorpause.b = 255;
}

void		Snake::init(const int &w, const int &h)
{
  _width = w;
  _height = h;
  SDL_WM_SetCaption(NAME, NULL);
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
      !(_screen = SDL_SetVideoMode(SP_SIZE * (_width + 2), SP_SIZE * (_height + 2), BPP, SDL_HWSURFACE)))
    error(1, 0, "Couldn't initialize Graphic Mode");
  if (TTF_Init() == -1)
    error(1, 0, "Couldn't initialize fonts");
  _fd = 0;
  _joy = -1;
  init_font();
  init_joystick();
  load();
  apply_bg();
  apply_wall();
  my_flip();
}

void		Snake::end_sdl()
{
  SDL_Quit();
}

Key		Snake::refresh_screen(std::list<Pos> &list, const int &delay, const int &score)
{
  _score = score;
  draw_img(list);
  SDL_Delay(delay);
  if (_fd > 0 && _joy == 1)
    return (update_joystick());
  else
    {
      while (SDL_PollEvent(&_event))
	{
	  if (_event.type == SDL_QUIT)
	    return (ESCAPE);
	  if (_event.type == SDL_KEYDOWN)
	    {
	      if (_event.key.keysym.sym == SDLK_LEFT)
		return (LEFT);
	      if (_event.key.keysym.sym == SDLK_RIGHT)
		return (RIGHT);
	      if (_event.key.keysym.sym == SDLK_ESCAPE)
		{
		  end_sdl();
		  return (ESCAPE);
		}
	      if (_event.key.keysym.sym == SDLK_DOWN)
		_joy *= -1;
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
  apply_bg();
  apply_wall();
  apply_snake(list);
  apply_score();
  my_flip();
}

void		Snake::apply_score()
{
  std::stringstream newscore;
  std::string	    temp;
  char const * temp2;
  
  newscore << "Score: " <<  _score;
  temp = newscore.str();
  temp2 = (char*)temp.c_str();
  _text = TTF_RenderText_Solid(_fontscore, temp2, _color);
  apply_surface((WIDTH/2 - 64), 0, _text, _screen);
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    apply_surface((*i).x * SP_SIZE + SP_SIZE, (*i).y * SP_SIZE + SP_SIZE, _snake[(*i).state], _screen);
}

void		Snake::apply_bg()
{
  apply_surface(0, 0, _bg, _screen);
}

void		Snake::apply_wall()
{
  for (int i = 0; i <= _width + 1; ++i)
    {
      apply_surface(i * SP_SIZE, 0, _wall, _screen);
      apply_surface(i * SP_SIZE, (_height + 1) * SP_SIZE, _wall, _screen);
    }
  for (int i = 0; i <= _height + 1; ++i)
    {
      apply_surface(0, i * SP_SIZE, _wall, _screen);
      apply_surface((_width + 1) * SP_SIZE, i * SP_SIZE, _wall, _screen);
    }
}

// ---------------------------------
// ----------SDL ABSTRACT-----------
// ---------------------------------

SDL_Surface     *Snake::load_image(const std::string &filename)
{
  SDL_Surface   *loadedImage;

  if (!(loadedImage = IMG_Load(filename.c_str())))
    error(1, 0, "Couldn't load image : %s", filename.c_str());
  return (loadedImage);
}

void		Snake::apply_surface(const int &x, const int &y, SDL_Surface *src, SDL_Surface *dest)
{
  SDL_Rect	offset;

  offset.x = x;
  offset.y = y;
  if (SDL_BlitSurface(src, NULL, dest, &offset) == -1)
    error(1, 0, "Couldn't Blit surface");
}

void		Snake::my_flip() const
{
  if (SDL_Flip(_screen) == -1)
    error(1, 0, "Couldn't refresh screen");
}

void		Snake::load()
{
  _bg = load_image(Snake::bg_path);
  _wall = load_image(Snake::wall_path);
  _snake[FOOD] = load_image(Snake::apple);
  _snake[BONUS] = load_image(Snake::star);

  _snake[HEAD_NORTH] = load_image(Snake::head_up);
  _snake[HEAD_SOUTH] = load_image(Snake::head_down);
  _snake[HEAD_WEST] = load_image(Snake::head_right);
  _snake[HEAD_EAST] = load_image(Snake::head_left);

  _snake[TAIL_NORTH] = load_image(Snake::tail_up);
  _snake[TAIL_SOUTH] = load_image(Snake::tail_down);
  _snake[TAIL_WEST] = load_image(Snake::tail_right);
  _snake[TAIL_EAST] = load_image(Snake::tail_left);

  _snake[BODY_HORIZONTAL] = load_image(Snake::body_hor);
  _snake[BODY_VERTICAL] = load_image(Snake::body_vert);

  _snake[BODY_ANGLE_SOUTH_EAST] = load_image(Snake::turn_downleft);
  _snake[BODY_ANGLE_SOUTH_WEST] = load_image(Snake::turn_downright);
  _snake[BODY_ANGLE_NORTH_EAST] = load_image(Snake::turn_upleft);
  _snake[BODY_ANGLE_NORTH_WEST] = load_image(Snake::turn_upright);
}

void		Snake::init_joystick()
{
  _fd = open("/dev/input/js1", O_NONBLOCK);
  if (_fd > 0)
      std::cout << "Joystick detected. Press 'down' to activate\n" << std::endl;
  else
    std::cout << "Unable to detect joystick\n" << std::endl;
}

Key		Snake::game_pause()
{
  struct js_event	e;
  int		pos;
  
  pos = -1;
  while (42)
    {
      SDL_Delay(20);
      if (pos == -1)
	{
	  _text = TTF_RenderText_Solid(_fontmenu, "RETURN TO GAME", _color);
	  apply_surface((WIDTH/2) - BPP * 2, (HEIGHT/2) + BPP * 2, _text, _screen);
	  _text = TTF_RenderText_Solid(_fontmenu, "QUIT", _colorpause);
	  apply_surface((WIDTH/2) - BPP * 2, (HEIGHT/2) + BPP * 4, _text, _screen);
	}
      else
	{
	  _text = TTF_RenderText_Solid(_fontmenu, "RETURN TO GAME", _colorpause);
	  apply_surface((WIDTH/2) - BPP * 2, (HEIGHT/2) + BPP * 2, _text, _screen);
	  _text = TTF_RenderText_Solid(_fontmenu, "QUIT", _color);
	  apply_surface((WIDTH/2) - BPP * 2, (HEIGHT/2) + BPP * 4, _text, _screen);
	}
      my_flip();
      if (read(_fd, &e, sizeof(struct js_event)) > 0) 
	{
	  if (!(e.type &= JS_EVENT_BUTTON) && e.number == 7 && e.value >= 32767)
	    pos *= -1;
	  if (!(e.type &= JS_EVENT_BUTTON) && e.number == 7 && e.value <= -32767)
	    pos *= -1;
	  if ((e.type &= JS_EVENT_BUTTON) && e.value == 1 && e.number == 0)
	    {
	      if (pos == -1)
		return (OTHER);
	      else
		return (ESCAPE);
	    }
	}
    }
}

Key		Snake::update_joystick()
{
  struct js_event	e;
  int			button;

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
	  else if (e.number == 2)
	    {
	      if (e.value > 32700)
		return (SLOW);
	    }
	  else if (e.number == 5)
	    {
	      if (e.value > 32700)
		return (BOOST);
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
