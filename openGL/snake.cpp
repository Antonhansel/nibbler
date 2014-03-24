//
// opengl.cpp for opengl in /home/apollo/rendu/OPENGL_TUTO/test1
//
// Made by ribeaud antonin
// Login   <ribeau_a@epitech.net>
//
// Started on  Mon Mar 10 15:06:57 2014 ribeaud antonin
// Last update Mon Mar 24 17:21:12 2014 ribeaud antonin
//

#include <error.h>
#include "snake.hpp"

/*#######################################*/
/*############ INIT AND END #############*/
/*#######################################*/

void		Snake::init(int w, int h)
{
  _width = w;
  _height = h;
  _start = 1;
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 ||
      !(_screen = SDL_SetVideoMode(SP_SIZE * (_width + 2),
				   SP_SIZE * (_height + 2), BPP, SDL_OPENGL)))
    error(1, 0, "Couldn't initialize Graphic Mode");
  SDL_WM_SetCaption(NAME, NULL);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)((w+2) * 32)/((h+2) * 32), 1, 1000);
  if (TTF_Init() == -1)
    error(1, 0, "Couldn't initialize fonts");
  glEnable(GL_TEXTURE_2D);
  glMatrixMode (GL_MODELVIEW);
  _joy = -1;
  _height -= 1;
  _width -= 1;
  _help = -1;
  init_lights();
  init_joystick();
  init_font();
  glGenTextures(1, &_walltexture);
  _walltexture = load_texture(32, 32, "img/bg.bmp");
}

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

void		Snake::init_lights()
{
  glClearDepth(1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void		Snake::end_sdl()
{
  int		x = 0;
  int		rotate = _width;

  _start = x;
  while (_start < 20)
    {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      SDL_Delay(70);
      if (_start % 4 == 0)
	rotate--;
      gluLookAt(-_width/5, -_width/5, rotate, (_height/2 - _height/8), 
		(_width/2 - _height/8), x, x, x, 1);
      x++;
      apply_bg();
      apply_wall();
      apply_score();
      my_flip();
      _start++;
    }
  glDeleteTextures(1, &_walltexture);
  SDL_Quit();
}

Key		Snake::refresh_screen(std::list<Pos> &list, int delay, int score)
{
  Key		key;

  _score = score;
  _delay = delay;
  if (delay == 0)
    end_sdl();
  else
    {
      if (_start > 0)
	fancy_starter(list);
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
		      end_sdl();
		      return (ESCAPE);
		    }
		  if (_event.key.keysym.sym == SDLK_UP)
		    _help *=-1;
		  if (_event.key.keysym.sym == SDLK_DOWN)
		    _joy *=-1;
		}
	    }
	}
    }
  return (OTHER);
}

void		Snake::fancy_starter(std::list<Pos> &list)
{
  int		x = 20;
  int		rotate = _width - 5;

  _start = x;
  while (_start > 0)
    {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      SDL_Delay(70);
      if (_start % 4 == 0)
	rotate++;
      gluLookAt(-_width/5, -_width/5, rotate, (_height/2 - _height/8), 
		(_width/2 - _height/8), x, x, x, 1);
      x--;
      apply_bg();
      apply_wall();
      apply_snake(list);
      my_flip();
      _start--;
    }
}


/*#######################################*/
/*############ DRAW FUNCS ###############*/
/*#######################################*/

void		Snake::apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{
  SDL_Rect	offset;

  offset.x = x;
  offset.y = y;
  if (SDL_BlitSurface(src, NULL, dest, &offset) == -1)
    error(1, 0, "Couldn't Blit surface");
}

void		Snake::draw_img(std::list<Pos> &list)
{
  int		mode = 0;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    {
      if ((*i).state >= 0 && (*i).state <= 3 && _delay <= 30)
  	{
  	  mode = 1;
	  gluLookAt(-_width/5, -_width/5, _width, (*i).x-((*i).x/16), 
		    (*i).y-((*i).y/8), 0, 0, 0, 1);
	}
    }
  if (mode == 0)
    gluLookAt(-_width/5, -_width/5, _width, (_height/2 - _height/8), 
	      (_width/2 - _width/8), 0, 0, 0, 1);
  apply_bg();
  apply_wall();
  apply_snake(list);
  apply_score();
  if (_help == 1)
    load();
  my_flip();
}


/*#######################################*/
/*############ APPLY FUNCS ##############*/
/*#######################################*/

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

void		Snake::apply_wall()
{
  for (int i = -1; i <= _width + 2; ++i)
    {
      draw_block(i, -1, -1);
      draw_block(i, (_height + 2), -1);
    }
  for (int i = -1; i <= _height + 2; ++i)
    {
      draw_block(-1, i, -1);
      draw_block((_width + 2), i, -1);
    }
}

void		Snake::apply_bg()
{
  glMatrixMode(GL_MODELVIEW);
  glBegin(GL_QUADS);
  
  glColor3ub(120, 255, 120);
  glTexCoord2d(0.0,0.0); glVertex3d(-1,          -1, -1);
  glTexCoord2d(1.0,0.0); glVertex3d(-1,          _height + 2, -1);
  glColor3ub(50, 255, 50);
  glTexCoord2d(1.0,1.0); glVertex3d(_width + 2,  _height + 2, -1);
  glTexCoord2d(0.0,1.0); glVertex3d(_height + 2, -1, -1);

  glEnd();
}

void		Snake::apply_snake(std::list<Pos> &list)
{
  for (std::list<Pos>::iterator i = list.begin(); i != list.end(); ++i)
    draw_block((*i).x, (*i).y, (*i).state);
}

void		Snake::loadColor(int i, int state)
{
  if (i == 1)
    {
      if (state == 14)
	glColor3ub(255,0,0);
      else if (state == -1)
	glColor3ub(0, 255, 255);
      else
	glColor3ub(0 , 0, 255);
    }
  else
    {
      if (state == 14)
	glColor3ub(0,0,255);
      else if (state == -1)
	glColor3ub(255, 255, 0);
      else
	glColor3ub(255, 0, 0);
    }
}

void		Snake::draw_block(int x, int y, int state)
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  //glBindTexture(GL_TEXTURE_2D, _walltexture);
  glBegin(GL_QUADS);

  if (state == 14)
    glColor3ub(255,0,0);
  else if (state == -1 || state == 15)
    glColor3ub(rand()%255, rand()%255, rand()%255);
  else if (state <= 3)
    glColor3ub(0 , 0, 255);
  else if (state == 6 || state == 7 || state == 8 || state == 9)
    glColor3ub(255, 150, 255);
  else
    glColor3ub(50 , 0, 190);

  glVertex3d(x,     y,      1);
  glVertex3d(x,     y,     -1);
  glVertex3d(x + 1, y,     -1);
  glVertex3d(x + 1, y,      1);

  glVertex3d(x,     y + 1,  1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x,     y,     -1);
  glVertex3d(x,     y,      1);

  glVertex3d(x + 1, y + 1,  1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x,     y + 1,  1);

  glVertex3d(x + 1, y,      1);
  glVertex3d(x + 1, y,     -1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x + 1, y + 1,  1);

  glVertex3d(x,     y,     -1);
  glVertex3d(x,     y + 1, -1);
  glVertex3d(x + 1, y + 1, -1);
  glVertex3d(x + 1, y,     -1);

  glVertex3d(x,     y + 1,  1);
  glVertex3d(x,     y,      1);
  glVertex3d(x + 1, y,      1);
  glVertex3d(x + 1, y + 1,  1);

  glEnd();
  //glPopMatrix();
}

/*#######################################*/
/*################ MISC #################*/
/*#######################################*/

extern "C"
{
  IGraphic	*init_lib()
  {
    return (new Snake);
  }
}

void		Snake::my_flip()
{
  glFlush();
  SDL_GL_SwapBuffers();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void		Snake::load() 
{
  int xPointCount = 40;
  int yPointCount = 40;
  double xSpacing = 1;
  double ySpacing = 1;
  double width = xSpacing * (xPointCount-1); 
  double height = ySpacing * (yPointCount-1); 
  double minX = -width/2; 
  double minY = -height/2;
  
  glBegin(GL_POINTS);
  glColor3ub(255,255,255);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 0;
	  glVertex3f(x, y, z); 
	} 
    }
  glColor3ub(255,255,150);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 5; 
	  glVertex3f(x, y, z); 
	} 
    }
  glColor3ub(150,150,255);
  for(int i = 0; i<xPointCount; i++) 
    { 
      for(int j = 0; j<yPointCount; j++) 
	{ 
	  double x = minX + i*xSpacing; 
	  double y = minY + j*ySpacing; 
	  double z = 10; 
	  glVertex3f(x, y, z); 
	} 
    }
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

Key			Snake::game_pause()
{
  struct js_event	e;
  int			pos;
  
  pos = -1;
  while (42)
    {
      usleep(100);
      if (read(_fd, &e, sizeof(struct js_event)) > 0 && 
	  (e.type &= JS_EVENT_BUTTON) && e.value == 1 && e.number == 8)
	return (OTHER);
    }
}

Key			Snake::update_joystick()
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

GLuint		Snake::load_texture(int widthold, int heightold, char const *filename)
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
  //le header doit faire 54 bytes
  if (fread(header, 1, 54, file)!= 54)
    std::cout << filename << " is not a BMP file!" << std::endl;
  //le header doit commencer par BM --> hexdump *.bmp
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
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
}
