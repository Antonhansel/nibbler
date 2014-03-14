//
// IGraphic.hh for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/sources/IGraphic.hh
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Mar 14 18:08:16 2014 ribeaud antonin
//

#ifndef _IGRAPHIC_H
#define _IGRAPHIC_H

#include <list>

enum State {
    HEAD_NORTH = 0,
    HEAD_SOUTH = 1,
    HEAD_EAST = 2,
    HEAD_WEST = 3,
    BODY_HORIZONTAL = 4,
    BODY_VERTICAL = 5,
    BODY_ANGLE_NORTH_EAST = 6,
    BODY_ANGLE_NORTH_WEST = 7,
    BODY_ANGLE_SOUTH_EAST = 8,
    BODY_ANGLE_SOUTH_WEST = 9,
    TAIL_NORTH = 10,
    TAIL_SOUTH = 11,
    TAIL_EAST = 12,
    TAIL_WEST = 13,
    FOOD = 14
};

enum Key {
    RIGHT,
    LEFT,
    ESCAPE
};

typedef struct {
    int x;
    int y;
    State state;
} Pos;

/*
** Implement a child class from IGraphic for your graphic library
** then write a function called "IGraphic *initlib();" returning a new instance of your class
** Compile it as a shared library and then you can use it with the nibbler project
*/

class IGraphic {
public:
  virtual ~IGraphic() = 0;
  virtual void init(int w, int h) = 0;
  virtual Key refresh(std::list<Pos>) = 0;
};

#endif
