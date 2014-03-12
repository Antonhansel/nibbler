//
// IGraphic.hh for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/sources/IGraphic.hh
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Fri Jan 10 09:07:44 2014 guillaume besson
//

#ifndef _IGRAPHIC_H
#define _IGRAPHIC_H

#include <list>

enum State {
    HEAD_NORTH,
    HEAD_EAST,
    HEAD_WEST,
    HEAD_SOUTH,
    BODY_HORIZONTAL,
    BODY_VERTICAL,
    BODY_ANGLE_NORTH_EAST,
    BODY_ANGLE_NORTH_WEST,
    BODY_ANGLE_SOUTH_EAST,
    BODY_ANGLE_SOUTH_WEST,
    TAIL_NORTH,
    TAIL_EAST,
    TAIL_WEST,
    TAIL_SOUTH,
    FOOD
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

class IGraphic {
public:
    virtual ~IGraphic() = 0;
    virtual void init(int w, int h) = 0;
    virtual Key refresh(std::list<Pos>) = 0;
};

#endif

