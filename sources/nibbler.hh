//
// nibbler.hh for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/sources/nibbler.hh
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Sun Mar 16 14:39:32 2014 ribeaud antonin
//

#ifndef _NIBBLER_H
#define _NIBBLER_H

#include <exception>
#include <string>

#include "IGraphic.hh"

class Nibbler {
public:
    Nibbler(int w, int h);
    ~Nibbler();
public:
    void initGraphic(std::string &libname);
    void startGame();
private:
    void loopGame(Key key);
    bool looseGame();
private:
    IGraphic *graphic;
    int width;
    int height;
private:
    std::list<Pos> pos;
};

#define LOOP(a, b, c) ((((a - c) < 0) ? ((a - c) % (b + 1) + b + 1) : ((a - c) % (b + 1))) + c)

#endif
