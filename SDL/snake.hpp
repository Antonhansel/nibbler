//
// opengl.hpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:08:13 2014 ribeaud antonin
// Last update Wed Mar 26 10:36:55 2014 ribeaud antonin

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <fcntl.h>
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
  /*
  **SDL funcs
  */
  SDL_Surface	*load_image(const std::string &filename);
  void		apply_surface(const int &x, const int &y, SDL_Surface *src, SDL_Surface *dest);
  /*
  **loop funcs
  */
  void		my_flip() const;
  Key		refresh_screen(std::list<Pos> &, const int&, const int&);
  void		apply_wall();
  void		apply_bg();
  void		apply_score();
  void		apply_snake(std::list<Pos>&);
  void		draw_img(std::list<Pos>&);
  /*
  **init funcs
  */
  void		init(const int &w, const int &h);
  void		end_sdl();
  void		load();
  void		init_font();
  /*
  **joystick funcs
  */
  void		init_joystick();
  Key		update_joystick();
  Key		game_pause();
  ~Snake() {};

private:
  std::map<State, SDL_Surface *>	_snake;
  SDL_Surface	*_screen;
  SDL_Surface	*_bg;
  SDL_Surface	*_wall;
  SDL_Surface	*_text;
  SDL_Event	_event;
  SDL_Color	_color;
  SDL_Color	_colorpause;
  TTF_Font	*_fontscore;
  TTF_Font	*_fontmenu;
  int		_score;
  int		_width;
  int		_height;
  int		_fd;
  int		_joy;

private:
  static std::string bg_path;
  static std::string wall_path;
  static std::string apple;
  static std::string star;

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
std::string Snake::star = "img/star.png";

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
