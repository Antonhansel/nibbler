//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
// 
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
// 
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Thu Mar 13 17:24:26 2014 ribeaud antonin
//

#include "snake.hpp"

Snake::Snake()
{
  std::string	s1;
  std::string	s2;

  init_values();
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

Snake::~Snake()
{
  SDL_Quit();
}

// IGraphic	*Snake::initlib()
// {
//   return (*this);
// }

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

// ---------------UGLY--------------
// ------------KEY HANDLER----------
// ----------TO BE REPLACED --------

void		Snake::keys()
{
  if (SDL_PollEvent(&_event))
    {
      if (_event.type == SDL_KEYDOWN)
	event[_event.key.keysym.sym] = 1;
      if (_event.type == SDL_KEYUP)
	event[_event.key.keysym.sym] = 0;
      if (_event.type == SDL_QUIT)
	_quit = 1;
      if (event[SDLK_LEFT])
	{
	  printf("Left is pressed\n");
	  event[SDLK_LEFT] = 0;
	}
      else if (event[SDLK_RIGHT])
	{
	  printf("Right is pressed\n");
	  event[SDLK_RIGHT] = 0;
	}
      else if (event[SDLK_ESCAPE])
	{
	  printf("Escape is pressed\n");
	  event[SDLK_ESCAPE] = 0;
	}
    }
  //envoie des events a guillaume qui me renvoie une liste chainée de positions
}

// ---------------------------------
// ------------GAME BASE------------
// ---------------------------------

void		Snake::init_values()
{
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
}

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
