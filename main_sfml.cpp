#include <cassert>
#include <memory>
#include "maziakintgrid.h"
#include "maziakmenudialog.h"
#include "sfmlmaziakgamedialog.h"
int main(int, char *[])
{
  #ifdef NDEBUG
  //Must be really release mode
  assert(1 == 2);
  #endif
  using namespace ribi::maziak;
  ribi::maziak::SfmlGameDialog w;
  w.Exec();
}

