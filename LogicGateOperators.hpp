#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Terminal
{
  bool isOutput;
  unsigned short conn_num;
  /*
  0 - Low, 1 - High, 2 - Undefined
   */
  unsigned short state;

  Terminal(bool isout = false, unsigned short conns = 0, unsigned short _state = 0);
  unsigned short const& connect();
  unsigned short const& disconnect();

  friend std::istream& operator>>(std::istream& stream, Terminal& term);
};
class Gate
{
public:
  static constexpr size_t N = 20;

private:
  Terminal terminals[N];
  size_t _size;

public:
  Gate();
  Gate(size_t in, size_t out);

  Gate(Terminal terms[], size_t terms_size);

  Gate(std::vector<Terminal>& terms);
  unsigned short const& operator()(size_t n, unsigned short val);
  unsigned short const& operator[](size_t n);
  unsigned short const& at(size_t n);
  void connect(size_t n);
  void disconnect(size_t n);
  Gate& operator+=(Terminal&& term);

  friend std::istream& operator>>(std::istream& stream, Gate& gate);

  friend std::ostream& operator<<(std::ostream& stream, Gate& gate);
  inline size_t const& size() const {
      return _size;
  }
};
