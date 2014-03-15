//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Fri Mar 14 19:48:12 2014 ribeaud antonin
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
    SDL_WM_SetCaption("SNAKE", NULL);
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
        !(_screen = SDL_SetVideoMode(SP_SIZE * _width, SP_SIZE * _height, BPP, SDL_HWSURFACE)))
        error(1, 0, "Couldn't initialize Graphic Mode");
    _bg = load_image(Snake::bg_path);
    _wall = load_image(Snake::wall_path);
    apply_surface(0, 0, _bg, _screen);
    apply_wall();
    my_flip();
}

// ---------------UGLY--------------
// ------------KEY HANDLER----------
// ----------TO BE REPLACED --------

// ---------------------------------
// ------------GAME BASE------------
// ---------------------------------

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

SDL_Surface     *Snake::load_image(std::string &filename)
{
    SDL_Surface   *loadedImage;
    SDL_Surface   *optimizedImage;

    if (!(loadedImage = IMG_Load(filename.c_str())))
        error(1, 0, "Couldn't load image : %s", filename.c_str());
    if (!(optimizedImage = SDL_DisplayFormat(loadedImage)))
        error(1, 0, "Couldn't optimize image");
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

Key		Snake::refresh(std::list<Pos> list, int delay)
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
                return (ESCAPE);
        }
    }
    SDL_Delay(delay);
    return (OTHER);
}
