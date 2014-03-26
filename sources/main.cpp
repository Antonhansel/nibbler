//
// main.cpp for nibbler in /home/geekuillaume/Dropbox/Epitech/tek2/current/nibbler/sources/main.cpp
//
// Made by guillaume besson
// Login   <besson_g@epitech.net>
//
// Started on  Fri Jan 10 09:07:44 2014 guillaume besson
// Last update Wed Mar 26 12:43:13 2014 ribeaud antonin
//

#include <error.h>
#include <cstdlib>
#include <iostream>
#include "nibbler.hh"

int		main(int argc, char const *argv[])
{
  Nibbler	*nibbler;
  int		width, height;
  std::string	graphiclib;

  if (argc != 4)
    error(1, 0, "Usage : [width] [height] [graphiclib]");
  width = std::atoi(argv[1]);
  height = std::atoi(argv[2]);
  graphiclib = argv[3];
  if (width == height)
    {
      if (width < 3 || height > 30)
	error(1, 0, "Map size too small");
    }
  nibbler = new Nibbler(width, height);
  nibbler->initGraphic(graphiclib);
  nibbler->startGame();
  return 0;
}
