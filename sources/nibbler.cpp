//
// nibbler.cpp for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/nibbler.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Jan 10 09:07:44 2014 guillaume besson
//

#include <error.h>
#include <dlfcn.h>
#include <stdlib.h>
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

void Nibbler::initGraphic(std::string &libname)
{
    void *handle;
    IGraphic *(*creation)();

    creation = NULL;
    if (!(handle = dlopen(libname.c_str(), RTLD_LAZY))
        || !(creation = (IGraphic *(*)())dlsym(handle, "initlib")))
        error(1, 0, "Wrong librairy file");
    this->graphic = creation();
}

void Nibbler::startGame()
{
    Key key;

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
    for (std::list<Pos>::iterator i = this->pos.begin(); i != this->pos.end(); ++i)
    {

    }
}

