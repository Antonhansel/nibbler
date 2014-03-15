//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Fri Mar 14 19:48:12 2014 ribeaud antonin
//

#include "snake.hpp"

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}

void		Snake::start_snake()
{
  while (_quit == 0)
    {
      _current = SDL_GetTicks();
      if (_current > _next)
	keys();
      else
	SDL_Delay(20);
      _next = _current + 20;
    }
}

void		Snake::init(int w, int h)
{
  std::string	s1;
  std::string	s2;

  _screen = NULL;
  _snake = NULL;
  _wall = NULL;
  _apple = NULL;
  _bg = NULL;
  _current = 0;
  _next = 0;
  _quit = 0;
  event[SDLK_LEFT] = 0;
  event[SDLK_RIGHT] = 0;
  event[SDLK_ESCAPE] = 0;
  s1 = "img/bg.jpg";
  s2 = "img/wood1.png";
  SDL_WM_SetCaption("SNAKE", NULL);
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    exit(1);
  _screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
  _bg = load_image(s1);
  _wall = load_image(s2);
  apply_surface(0, 0, _bg, _screen);
  apply_wall();
  my_flip();
  start_snake();
}

// ---------------UGLY--------------
// ------------KEY HANDLER----------
// ----------TO BE REPLACED --------

// ---------------------------------
// ------------GAME BASE------------
// ---------------------------------

void		Snake::apply_wall()
{
  int		i = 0;
  int		j = 0;

  while (i < WIDTH - 64)
    {
      apply_surface(i, j, _wall, _screen);
      i += 64;
    }
  while (j < HEIGHT - 64)
    {
      apply_surface(i, j, _wall, _screen);
      j += 64;
    }
  while (i > 0)
    {
      apply_surface(i, j, _wall, _screen);
      i -= 64;
    }
  while (j > 0)
    {
      apply_surface(i, j, _wall, _screen);
      j -= 64;
    }
}

// ---------------------------------
// ----------SDL ABSTRACT-----------
// ---------------------------------

SDL_Surface     *Snake::load_image(std::string &filename)
{
  SDL_Surface   *loadedImage;
  SDL_Surface   *optimizedImage;
  Uint32        colorkey;

  loadedImage = IMG_Load(filename.c_str());
  if (loadedImage != NULL)
    {
      optimizedImage = SDL_DisplayFormat(loadedImage);
      if (optimizedImage != NULL)
	{
	  colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
	  SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
	}
      SDL_FreeSurface(loadedImage);
    }
  else
    exit (1);
  return (optimizedImage);
}

void		Snake::apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{
  SDL_Rect	offset;

  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, dest, &offset);
}

void		Snake::my_flip()
{
  SDL_Flip(_screen);
}


Key		Snake::returnKey()
{
  if (event[SDLK_LEFT])
    {
      event[SDLK_LEFT] = 0;
      return (LEFT);
    }
  else if (event[SDLK_RIGHT])
    {
      event[SDLK_RIGHT] = 0;
      return (LEFT);
    }
  else if (event[SDLK_ESCAPE])
    {
      event[SDLK_ESCAPE] = 0;
      return (ESCAPE);
    }
}

Key		Snake::refresh(std::list<Pos> list)
{
  if (SDL_PollEvent(&_event))
    {
      if (_event.type == SDL_KEYDOWN)
	event[_event.key.keysym.sym] = 1;
      if (_event.type == SDL_KEYUP)
	event[_event.key.keysym.sym] = 0;
      if (_event.type == SDL_QUIT)
	_quit = 1;
    }
  return (returnKey());
}
