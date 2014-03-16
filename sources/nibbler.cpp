//
// nibbler.cpp for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/nibbler.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Sun Mar 16 18:10:26 2014 ribeaud antonin
//

#include <error.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "nibbler.hh"

Nibbler::Nibbler(int w, int h)
{
    this->width = w;
    this->height = h;
    this->graphic = NULL;
    this->pos.push_back((Pos){3, 3, FOOD});
    this->pos.push_back((Pos){1, 1, TAIL_WEST});
    this->pos.push_back((Pos){2, 1, BODY_HORIZONTAL});
    this->pos.push_back((Pos){3, 1, HEAD_WEST});
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

void        Nibbler::startGame()
{
    Key     key;

    while (42)
    {
        key = this->graphic->refresh(this->pos, 300);
        if (key == ESCAPE)
            break;
        this->loopGame(key);
        if (this->looseGame())
        {
            std::cout << "You looooooooose !" << std::endl;
            break;
        }
    }
}

void        Nibbler::loopGame(Key key)
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
        if ((*i).state != FOOD && (*i).x == (*head).x && (*i).y == (*head).y)
            return (true);
    }
    return (false);
}
