#ifndef MAZIAKMENUDIALOG_H
#define MAZIAKMENUDIALOG_H

#include <string>
#include <vector>

namespace ribi {
namespace maziak {

///The console menu: handles the command-line arguments
struct MenuDialog final
{
  MenuDialog();

  ///Convert the arguments of 'main' to a std::vector
  static std::vector<std::string> ConvertArguments(
    const int argc, const char * const argv[]) noexcept;

  ///Respond to the command-line arguments
  int Execute(const std::vector<std::string>& argv) noexcept;

  ///Text about the program: title, version, author, URL, licence
  std::string GetAbout() const noexcept;

  ///Text on how to use the program from the command line
  std::string GetHelp() const noexcept;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKMENUDIALOG_H
