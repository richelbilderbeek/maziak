#include "maziakmenudialog.h"

int main(int argc, char * argv[])
{
  const auto args = ribi::maziak::MenuDialog::ConvertArguments(argc, argv);
  return ribi::maziak::MenuDialog().Execute(args);
}
