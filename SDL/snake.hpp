//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Mon Mar 17 20:43:34 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_ttf.h>
# include <SDL/SDL_image.h>
# include <map>
# include "/usr/include/linux/joystick.h"
# include "../sources/IGraphic.hh"

#define NAME	"SNAKE_SDL"
#define HEIGHT	632
#define WIDTH	832
#define	BPP	32
#define SP_SIZE 32

class Snake : public IGraphic
{
public:
  SDL_Surface	*load_image(std::string &filename);
  void		apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest);
  void		my_flip();
  void		apply_wall();
  void		apply_bg();
  void		apply_snake(std::list<Pos>&);
  void		draw_img(std::list<Pos>&);
  void		init(int w, int h);
  void		end_sdl();
  void		load();

  Key		refresh_screen(std::list<Pos> &, int);
  ~Snake() {};

private:
  std::map<State, SDL_Surface *>	_snake;
  SDL_Surface	*_screen;
  SDL_Surface	*_apple;
  SDL_Surface	*_bg;
  SDL_Surface	*_wall;
  TTF_Font	*_font;
  SDL_Event	_event;
  int _width;
  int _height;

private:
  static std::string bg_path;
  static std::string wall_path;
  static std::string apple;

  static std::string head_up;
  static std::string head_down;
  static std::string head_left;
  static std::string head_right;

  static std::string body_hor;
  static std::string body_vert;

  static std::string turn_downright;
  static std::string turn_upleft;
  static std::string turn_downleft;
  static std::string turn_upright;

  static std::string tail_up;
  static std::string tail_down;
  static std::string tail_right;
  static std::string tail_left;
};

std::string Snake::bg_path = "img/bg.jpg";
std::string Snake::wall_path = "img/wood1.png";
std::string Snake::apple = "img/apple.png";

std::string Snake::head_up = "img/head_up.png";
std::string Snake::head_left = "img/head_left.png";
std::string Snake::head_down = "img/head_down.png";
std::string Snake::head_right = "img/head_right.png";

std::string Snake::body_hor = "img/body_hor.png";
std::string Snake::body_vert = "img/body_vert.png";

std::string Snake::turn_downleft = "img/turn_downleft.png";
std::string Snake::turn_upleft = "img/turn_upleft.png";
std::string Snake::turn_upright = "img/turn_upright.png";
std::string Snake::turn_downright = "img/turn_downright.png";

std::string Snake::tail_up = "img/tail_up.png";
std::string Snake::tail_down = "img/tail_down.png";
std::string Snake::tail_right = "img/tail_right.png";
std::string Snake::tail_left = "img/tail_left.png";


#endif /*!_SNAKE_HPP*/
