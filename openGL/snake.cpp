//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Thu Apr  3 13:09:04 2014 ribeaud antonin
//

#include <error.h>
#include "snake.hpp"

/*#######################################*/
/*############# CORE FUNC ###############*/
/*#######################################*/

void		Snake::draw_img(std::list<Pos> &list) const
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-_width/5, -_width/5, _width, (_height/2 - _height/8), 
	    (_width/2 - _width/8), 0, 0, 0, 1);
  glEnable(GL_TEXTURE_2D);
  apply_wall();
  apply_bg();
  apply_snake(list);
  glDisable(GL_TEXTURE_2D);
  my_flip();
}

Key		Snake::refresh_screen(std::list<Pos> &list, const int &delay, const int &score)
{
  _score = score;
  _delay = delay;
  if (delay == 1)
    end_opengl(list);
  else
    {
      if (_start > 0)
	camera_movements(1, list);
      draw_img(list);
      usleep(delay * 1000);
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
		    return (RIGHT);
		  if (_event.key.keysym.sym == SDLK_RIGHT)
		    return (LEFT);
		  if (_event.key.keysym.sym == SDLK_ESCAPE)
		    {
		      end_opengl(list);
		      return (ESCAPE);
		    }
		  if (_event.key.keysym.sym == SDLK_DOWN)
		    _joy *=-1;
		}
	    }
	}
    }
  return (OTHER);
}

/*#######################################*/
/*############ INIT FUNCS ###############*/
/*#######################################*/

void		Snake::init(const int &w, const int &h)
{
  _width = w;
  _height = h;
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
      !(_screen = SDL_SetVideoMode(SP_SIZE * (_width + 2),
				   SP_SIZE * (_height + 2), BPP, SDL_OPENGL)))
    error(1, 0, "Couldn't initialize Graphic Mode");
  SDL_WM_SetCaption(NAME, NULL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)((w+2) * 32)/((h+2) * 32), 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  set_values();
  init_lights();
  init_joystick();
}

void		Snake::init_lights() const
{
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void		Snake::end_opengl(std::list<Pos> &list)
{
  camera_movements(0, list);
}

void		Snake::set_values()
{
  _texture = new GLuint[17];
  _start = 1;
  _joy = -1;
  _height -= 1;
  _width -= 1;
  glGenTextures(17, _texture);
  _texture[4] = load_texture("img/body_vert.bmp");
  _texture[5] = load_texture("img/body_hor.bmp");
  _texture[14] = load_texture("img/apple.bmp");
  _texture[15] = load_texture("img/star.bmp");
  _texture[16] = load_texture("img/wall1.bmp");
  _texture[17] = load_texture("img/bg.bmp");
}

void		Snake::camera_movements(const int &state, std::list<Pos> &list)
{
  int		x;
  int		rotate;
  int		savedx;

  x = (20 * state);
  rotate = _width - (5 * state);
  _start = (20 * state);
  if (x == 0)
    savedx = 20;
  else
    savedx = 0;
  while (_start != savedx)
    {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      SDL_Delay(70);
      if (_start % 4 == 0)
	{
	  if (state == 0)
	    rotate--;
	  else
	    rotate++;
	}
      gluLookAt(-_width/5, -_width/5, rotate, (_height/2 - _height/8), 
		(_width/2 - _height/8), x, x, x, 1);
      if (state == 0)
	{
	  x++;
	  _start++;
	}
      else
	{
	  x--;
	  _start--;
	}
      glEnable(GL_TEXTURE_2D);
      apply_bg();
      apply_wall();
      apply_snake(list);
      glDisable(GL_TEXTURE_2D);
      my_flip();
    }
}

/*#######################################*/
/*############ APPLY FUNCS ##############*/
/*#######################################*/

void		Snake::apply_wall() const
{
  for (int i = -1; i <= _width + 2; ++i)
    {
      draw_block(i, -1, 16);
      draw_block(i, (_height + 2), 16);
    }
  for (int i = -1; i <= _height + 2; ++i)
    {
      draw_block(-1, i, 16);
      draw_block((_width + 2), i, 16);
    }
}

void		Snake::apply_bg() const
{
  glMatrixMode(GL_MODELVIEW);

  glBindTexture(GL_TEXTURE_2D, _texture[17]);
  glBegin(GL_QUADS);
  
  glColor3ub(255, 255, 255);
  glTexCoord2d(0.0,0.0); glVertex3d(-1,          -1, -1);
  glTexCoord2d(1.0,0.0); glVertex3d(-1,          _height + 2, -1);
  glTexCoord2d(1.0,1.0); glVertex3d(_width + 2,  _height + 2, -1);
  glTexCoord2d(0.0,1.0); glVertex3d(_height + 2, -1, -1);

  glEnd();
}

void		Snake::apply_snake(std::list<Pos> &list) const
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    draw_block((*i).x, (*i).y, (*i).state);
}

void		Snake::draw_block(const int &x, const int &y, const int &state) const
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glColor3ub(255, 255, 255);
  glBindTexture(GL_TEXTURE_2D, _texture[state]);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (state == 15)
    glColor3ub(rand()%100+155, rand()%100+155, rand()%100+155);
  else if (state <= 3)
    glColor3ub(0, 0, 255);
  else if (state >= 6 && state <= 9)
    glColor3ub(0, 255, 100);
  else if (state >= 10 && state <= 13)
    glColor3ub(100, 255, 100);

  glBegin(GL_QUADS);
  glTexCoord2d(0.0,0.0);	glVertex3d(x,     y,      1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x,     y,     -1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x + 1, y,     -1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x + 1, y,      1);

  glTexCoord2d(0.0,0.0);	glVertex3d(x,     y + 1,  1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x,     y + 1, -1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x,     y,     -1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x,     y,      1);

  glTexCoord2d(0.0,0.0);	glVertex3d(x + 1, y + 1,  1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x + 1, y + 1, -1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x,     y + 1, -1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x,     y + 1,  1);

  glTexCoord2d(0.0,0.0);	glVertex3d(x + 1, y,      1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x + 1, y,     -1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x + 1, y + 1, -1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x + 1, y + 1,  1);

  glTexCoord2d(0.0,0.0);	glVertex3d(x,     y,     -1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x,     y + 1, -1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x + 1, y + 1, -1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x + 1, y,     -1);

  glTexCoord2d(0.0,0.0);	glVertex3d(x,     y + 1,  1);
  glTexCoord2d(1.0,0.0);	glVertex3d(x,     y,      1);
  glTexCoord2d(1.0,1.0);	glVertex3d(x + 1, y,      1);
  glTexCoord2d(0.0,1.0);	glVertex3d(x + 1, y + 1,  1);
  glEnd();
}

/*#######################################*/
/*############## JOYSTICK ###############*/
/*#######################################*/

void		Snake::init_joystick()
{
  _fd = open("/dev/input/js1", O_NONBLOCK);
  if (_fd > 0)
    std::cout << "Joystick detected. Press 'down' to activate\n" << std::endl;
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

Key			Snake::update_joystick() const
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
		return (LEFT);
	      else if (e.value < -32700)
		return (RIGHT);
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

GLuint		Snake::load_texture(char const *filename) const
{
  GLuint	textureID;
  unsigned char	header[54];
  unsigned int	dataPos;
  unsigned int	width, height;
  unsigned int	imageSize;
  unsigned char *data;
  FILE		*file = fopen(filename, "rb");

  if (!file)
    std::cout << "Cannot load " << filename << std::endl;
  if (fread(header, 1, 54, file)!= 54)
    std::cout << filename << " is not a BMP file!" << std::endl;
  if (header[0] != 'B' || header[1] != 'M')
    std::cout << filename << ": wrong header, first two bytes must start with BM" << std::endl;
  dataPos = *(int*)&(header[0x0A]);
  imageSize = *(int*)&(header[0x22]);
  width = *(int*)&(header[0x12]);
  height = *(int*)&(header[0x16]);
  if (imageSize == 0)
    imageSize = width * height * 3;
  if (dataPos == 0)
    dataPos = 54;
  data = new unsigned char[imageSize];
  fread(data, 1, imageSize, file);
  fclose(file);
  glGenTextures(1, &textureID); 
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
  glDisable(GL_TEXTURE_2D);
  free(data);
  return (textureID);
}

/*#######################################*/
/*################ MISC #################*/
/*#######################################*/

void		Snake::my_flip() const
{
  glFlush();
  SDL_GL_SwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}
