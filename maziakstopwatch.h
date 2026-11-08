#ifndef MAZIAKSTOPWATCH_H
#define MAZIAKSTOPWATCH_H

#include <chrono>

namespace ribi {
namespace maziak {

///Measures the time passed since construction
class Stopwatch
{
public:
  Stopwatch() noexcept : m_start{std::chrono::steady_clock::now()} {}

  ///The number of seconds passed since construction
  double GetElapsedSecs() const noexcept
  {
    const std::chrono::duration<double> d{std::chrono::steady_clock::now() - m_start};
    return d.count();
  }

private:
  std::chrono::steady_clock::time_point m_start;
};

} //~namespace maziak
} //~namespace ribi

#endif // MAZIAKSTOPWATCH_H
