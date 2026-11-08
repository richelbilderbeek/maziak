#include "maziakmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "maziakgame.h"
#include "maziakterminal.h"

ribi::maziak::MenuDialog::MenuDialog()
{

}

std::vector<std::string> ribi::maziak::MenuDialog::ConvertArguments(
  const int argc, const char * const argv[]) noexcept
{
  return std::vector<std::string>(argv, argv + argc);
}

int ribi::maziak::MenuDialog::Execute(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    Terminal terminal{CreateTestGame1()};
    terminal.Execute();
    return 0;
  }
  const std::string s{argc == 2 ? argv[1] : ""};
  if (s == "--about" || s == "-a")
  {
    std::cout << GetAbout() << '\n';
  }
  else if (s == "--history" || s == "-i")
  {
    for (const auto& line: GetVersionHistory()) std::cout << line << '\n';
  }
  else if (s == "--version" || s == "-v")
  {
    std::cout << GetVersion() << '\n';
  }
  else
  {
    std::cout << GetHelp() << '\n';
  }
  return 0;
}

std::string ribi::maziak::MenuDialog::GetAbout() const noexcept
{
  return
    "Maziak, version " + GetVersion() + "\n"
    "a simple maze game\n"
    "Copyright (C) 2007-2017 Richel Bilderbeek\n"
    "\n"
    "Maziak can be downloaded from https://github.com/richelbilderbeek/maziak\n"
    "Licenced under GPL 3.0"
  ;
}

std::string ribi::maziak::MenuDialog::GetHelp() const noexcept
{
  return
    "Maziak, a simple maze game\n"
    "\n"
    "Usage:\n"
    "  maziak            play the game\n"
    "  maziak --about    show information about the program\n"
    "  maziak --help     show this help\n"
    "  maziak --history  show the version history\n"
    "  maziak --version  show the version"
  ;
}

std::string ribi::maziak::MenuDialog::GetVersion() const noexcept
{
  return "3.2";
}

std::vector<std::string> ribi::maziak::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-10-22: version 1.0: Initial version",
    "2010-02-16: version 1.1: Changed graphics to resemble the original Maziacs more. Changed manu screen. Changed 'Game Over' screen. Changed 'Congratulations' screen.",
    "2010-02-17: version 1.2: Animated prisoners. Animated enemies. Animated player. Improved 'Menu' screen. Improved 'About' screen. Added 'What's New?' screen",
    "2010-02-18: version 1.3: Animated fights. Prevent overlapping sprites. Add 'Instructions' screen in menu. Improved 'Menu' screen",
    "2010-02-25: version 1.4: Improved 'Game Over' screen. Added animation in 'Congratulations' screen. Improved enemies' intelligence. Improved maze creation algorithm. Ensured the player is not placed too close to the exit.",
    "2010-07-31: version 2.0: Reprogrammed in Qt Creator, so Maziak is now cross-platform!",
    "2012-03-06: version 2.1: Conformized architecture and naming for ProjectRichelBilderbeek.",
    "2014-01-06: version 3.0: Seperated GUI from game logic, allow console gaming",
    "2015-12-11: version 3.1: Minor update",
    "2017-03-12: version 3.2: Added tests, simplified code",
  };
}
