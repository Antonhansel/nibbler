//
// nibbler.cpp for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/nibbler.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Sat Mar 22 22:15:27 2014 ribeaud antonin
//

#include <error.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "nibbler.hh"

Nibbler::Nibbler(int w, int h)
{
  int		tmpw;
  int		tmph;

  this->width = w;
  this->height = h;
  tmpw = w/2;
  tmph = h/2;
  this->graphic = NULL;
  this->pos.push_back((Pos){3, 3, FOOD});
  this->pos.push_back((Pos){tmpw-2, tmph, TAIL_WEST});
  this->pos.push_back((Pos){tmpw-1, tmph, BODY_HORIZONTAL});
  this->pos.push_back((Pos){tmpw, tmph, BODY_HORIZONTAL});
  this->pos.push_back((Pos){tmpw+1, tmph, HEAD_WEST});
  _boost = 0;
  _slow = 0;
}

Nibbler::~Nibbler()
{
    delete this->graphic;
}

void        Nibbler::initGraphic(std::string &libname)
{
    void        *handle;
    IGraphic    *(*creation)();

    if (!(handle = dlopen(libname.c_str(), RTLD_LAZY)))
        error(1, 0, "dlopen failed: Unable to open library file! -> %s", dlerror());
    if (!(creation = reinterpret_cast<IGraphic *(*)()>(dlsym(handle, "init_lib"))))
        error(1, 0, "dlsym failed! -> %s", dlerror());
    this->graphic = creation();
    this->graphic->init(this->width, this->height);
}

Key	    Nibbler::handle_key(Key key)
{
  if (key == BOOST && _addop == 1)
    {
      if (_boost == 0)
	{
	  _speed -= 30;
	  _boost = 50;
	  _addop = 0;
	}
    }
  else if (key == SLOW && _addop == 1)
    {
      if (_slow == 0)
	{
	  _speed += 30;
	  _slow = 50;
	  _addop = 0;
	}
    }
  if (key == SLOW || key == BOOST)
    return (OTHER);
  else
    return (key);
}

void        Nibbler::startGame()
{
  Key     key;

  _speed = 300;
  _score = 0;
  srand(time(NULL));
  while (42)
    {
      if (_boost > 0)
	{
	  _boost--;
	  if (_boost == 0)
	    _speed += 30;
	}
      if (_slow > 0)
	{
	  _slow--;
	  if (_slow == 0)
	    _speed -= 30;
	}
      key = this->graphic->refresh_screen(this->pos, _speed, _score);
      if (key == ESCAPE)
	break;
      key = handle_key(key);
      this->loopGame(key);
      if (this->looseGame())
        {
	  std::cout << "You died!1! Score:" << _score << std::endl;
	  this->graphic->refresh_screen(this->pos, 0, _score);
	  break;
        }
    }
}

void	Nibbler::loopGame(Key key)
{
    std::list<Pos>::iterator    head, tail, food, tmp;
    Pos                         newHead;

    food = pos.begin();
    tail = pos.begin();
    advance(tail, 1);
    head = pos.end();
    advance(head, -1);
    if ((*food).x != (*head).x || (*food).y != (*head).y)
    {
        this->pos.erase(tail);
        tail = this->pos.begin();
        advance(tail, 1);
        tmp = this->pos.begin();
        advance(tmp, 2);
        if ((*tmp).x != (*tail).x)
            (*tail).state = ((*tmp).x < (*tail).x) ? TAIL_EAST : TAIL_WEST;
        else
            (*tail).state = ((*tmp).y < (*tail).y) ? TAIL_SOUTH : TAIL_NORTH;
    }
    else
        putNewFood();
    newHead.x = (*head).x;
    newHead.y = (*head).y;
    newHead.state = (State)LOOP((*head).state + key, HEAD_EAST, HEAD_NORTH);
    if (newHead.state == HEAD_WEST || newHead.state == HEAD_EAST)
        newHead.x += (newHead.state == HEAD_WEST) ? 1 : -1;
    if (newHead.state == HEAD_SOUTH || newHead.state == HEAD_NORTH)
        newHead.y += (newHead.state == HEAD_SOUTH) ? 1 : -1;
    this->pos.push_back(newHead);
    tmp = this->pos.end();
    advance(tmp, -3);
    if ((*tmp).x == (*head).x)
        (*head).state = BODY_VERTICAL;
    else if ((*tmp).y == (*head).y)
        (*head).state = BODY_HORIZONTAL;
}

bool    Nibbler::looseGame()
{
    std::list<Pos>::iterator head;

    head = this->pos.end();
    advance(head, -1);
    if ((*head).x < 0 || (*head).x >= this->width)
        return (true);
    if ((*head).y < 0 || (*head).y >= this->height)
        return (true);
    for (std::list<Pos>::iterator i = this->pos.begin(); i != head; ++i)
    {
      if ((*i).state != FOOD && (*i).x == (*head).x && (*i).y == (*head).y && 
	  (*i).state != BONUS && (*i).x == (*head).x && (*i).y == (*head).y)
	return (true);
    }
    return (false);
}

void    Nibbler::putNewFood()
{
    bool freePos[this->width * this->height];
    int  test;
    int	test2;

    std::list<Pos>::iterator it = this->pos.begin();
    if ((*it).state == 15 && _addop == 0)
      _addop = 1;
    if (_speed > 59 && _boost == 0 && _slow == 0)
      _speed -= 30;
    _score++;
    this->pos.erase(this->pos.begin());
    for(int i = 0; i < this->width * this->height; ++i)
      freePos[i] = true;
    for (std::list<Pos>::iterator i = this->pos.begin(); i != this->pos.end(); ++i)
      freePos[(*i).x * this->width + (*i).y] = false;
    do {
      test = rand() % (this->width * this->height - 1);
    } while (!freePos[test]);
    {
      test2 = (rand()%2) + 14;
      this->pos.push_front((Pos){test % this->width, test / this->width, (State)(test2)});
    }
}
