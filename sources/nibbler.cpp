//
// nibbler.cpp for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/nibbler.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Mar 14 18:21:36 2014 ribeaud antonin
//

#include <error.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include "nibbler.hh"

Nibbler::Nibbler(int w, int h)
{
  this->width = w;
  this->height = h;
  this->graphic = NULL;
  this->pos.push_back((Pos){1, 1, TAIL_WEST});
  this->pos.push_back((Pos){1, 2, BODY_HORIZONTAL});
  this->pos.push_back((Pos){1, 3, HEAD_WEST});
  this->pos.push_back((Pos){2, 1, FOOD});
}

Nibbler::~Nibbler()
{
  delete this->graphic;
}

void		Nibbler::initGraphic(std::string &libname)
{
  void		*handle;
  IGraphic	*(*creation)();

  if (!(handle = dlopen(libname.c_str(), RTLD_LAZY)))
    error(1, 0, "dlopen failed: Unable to open library file!");
  if (!(creation = reinterpret_cast<IGraphic *(*)()>(dlsym(handle, "init_lib"))))
    error(1, 0, "dlsym failed!");
  this->graphic = creation();
}

void		Nibbler::startGame()
{
  Key		key;

  while (42)
    {
      key = this->graphic->refresh(this->pos);
      if (key == ESCAPE)
	break;
      this->loopGame(key);
    }
}

void Nibbler::loopGame(Key key)
{
    std::list<Pos>::iterator head, tail, food;
    bool eated;
    Pos newTail, newHead;

    for (std::list<Pos>::iterator i = this->pos.begin(); i != this->pos.end() && (*i).state <= 3 ; ++i)
        head = i;
    ++head;
    for (std::list<Pos>::iterator i = this->pos.begin(); i != this->pos.end() && (*i).state >= 10 && (*i).state <= 13 ; ++i)
        tail = i;
    ++tail;
    for (std::list<Pos>::iterator i = this->pos.begin(); i != this->pos.end() && (*i).state == 14; ++i)
        food = i;
    ++food;
    eated = ((*food).x == (*head).x && (*food).y == (*head).y) ? true : false;
    if (!eated)
    {
        newTail.x = (*tail).x;
        newTail.y = (*tail).y;
        if ((*tail).state == TAIL_NORTH || (*tail).state == TAIL_SOUTH)
            newTail.y += ((*tail).state == TAIL_NORTH) ? 1 : -1;
        if ((*tail).state == TAIL_EAST || (*tail).state == TAIL_WEST)
            newTail.y += ((*tail).state == TAIL_EAST) ? 1 : -1;
        this->pos.push_back(newTail);
        this->pos.erase(tail);
    }

}
