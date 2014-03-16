//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Sun Mar 16 18:10:45 2014 ribeaud antonin
//

#include <error.h>
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
  _width = w;
  _height = h;
  SDL_WM_SetCaption(NAME, NULL);
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
      !(_screen = SDL_SetVideoMode(SP_SIZE * _width, SP_SIZE * _height, BPP, SDL_HWSURFACE)))
    error(1, 0, "Couldn't initialize Graphic Mode");
  load();
  apply_bg();
  apply_wall();
  my_flip();
}

Key		Snake::refresh(std::list<Pos> &list, int delay)
{
  draw_img(list);
  SDL_Delay(delay);
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
  my_flip();
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    apply_surface((*i).x * SP_SIZE, (*i).y * SP_SIZE, _snake[(*i).state], _screen);
}

void		Snake::apply_bg()
{
  apply_surface(0, 0, _bg, _screen);
}

void		Snake::apply_wall()
{
  for (int i = 0; i < _width; ++i)
    {
      apply_surface(i * SP_SIZE, 0, _wall, _screen);
      apply_surface(i * SP_SIZE, (_height - 1) * SP_SIZE, _wall, _screen);
    }
  for (int i = 0; i < _height; ++i)
    {
      apply_surface(0, i * SP_SIZE, _wall, _screen);
      apply_surface((_width - 1) * SP_SIZE, i * SP_SIZE, _wall, _screen);
    }
}

// ---------------------------------
// ----------SDL ABSTRACT-----------
// ---------------------------------

void		Snake::end_sdl()
{
  SDL_Quit();
}

SDL_Surface     *Snake::load_image(std::string &filename)
{
  SDL_Surface   *loadedImage;
  SDL_Surface   *optimizedImage;
  Uint32	colorkey;

  if (!(loadedImage = IMG_Load(filename.c_str())))
    error(1, 0, "Couldn't load image : %s", filename.c_str());
  if (!(optimizedImage = SDL_DisplayFormat(loadedImage)))
    error(1, 0, "Couldn't optimize image");
  colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
  SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
  SDL_FreeSurface(loadedImage);
  return (optimizedImage);
}

void		Snake::apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{
  SDL_Rect	offset;

  offset.x = x;
  offset.y = y;
  if (SDL_BlitSurface(src, NULL, dest, &offset) == -1)
    error(1, 0, "Couldn't Blit surface");
}

void		Snake::my_flip()
{
  if (SDL_Flip(_screen) == -1)
    error(1, 0, "Couldn't refresh screen");
}

void		Snake::load()
{

  _bg = load_image(Snake::bg_path);
  _wall = load_image(Snake::wall_path);
  _snake[FOOD] = load_image(Snake::apple);

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
