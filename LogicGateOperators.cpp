#include "LogicGateOperators.hpp"

Terminal::Terminal(bool isout, unsigned short conns, unsigned short _state) : isOutput{isout}, conn_num{conns}, state{_state} {}

unsigned short const& Terminal::connect()
{
  if ((isOutput && conn_num < 3) || (!isOutput && conn_num == 0))
    return ++conn_num;
  throw std::runtime_error("Number of connections can't be increased!");
}
unsigned short const& Terminal::disconnect()
{
  if (conn_num > 1)
    return --conn_num;
  throw std::runtime_error("Can not disconnect! No connections");
}

std::istream& operator>>(std::istream& stream, Terminal& term)
{
  char tmp;
  bool flag = 1;
  while (flag)
  {
    stream >> tmp;
    flag = 0;
    switch (tmp)
    {
    case '0':
      term.state = 0;
      break;
    case '1':
      term.state = 1;
      break;
    case 'X':
      term.state = 2;
      break;
    default:
      std::cout << "Retry>";
      flag = 1;
      break;
    }
  }
  return stream;
}

Gate::Gate() : terminals{{false, 0, 0}, {true, 0, 1}}, _size{2} {}

Gate::Gate(size_t in, size_t out)
{
  if (in + out > N)
    throw std::runtime_error("Overflow");
  for (size_t i = 0; i < in; i++)
    terminals[i] = Terminal(false, 0, 0);
  for (size_t i = in; i < (_size = in + out); i++)
    terminals[i] = Terminal(true, 0, 0);
}

Gate::Gate(Terminal terms[], size_t terms__size)
{
  if (terms__size > N)
    throw std::runtime_error("Array is too long.");
  _size = terms__size;
  for (size_t i = 0; i < _size; i++)
    terminals[i] = terms[i];
};

Gate::Gate(std::vector<Terminal>& terms)
{
  for (_size = 0; _size < N && _size < terms.size(); _size++)
  {
    terminals[_size] = terms[_size];
  }
}

unsigned short const& Gate::operator()(size_t n, unsigned short val)
{
  if (n >= _size)
    throw std::out_of_range("");
  return terminals[n].state = val;
}
unsigned short const& Gate::operator[](size_t n) { return terminals[n].state; }
unsigned short const& Gate::at(size_t n)
{
  if (n >= _size)
    throw std::out_of_range("");
  return terminals[n].state;
}
void Gate::connect(size_t n)
{
  if (n >= _size)
    throw std::out_of_range("");
  terminals[n].connect();
}
void Gate::disconnect(size_t n)
{
  if (n >= _size)
    throw std::out_of_range("");
  terminals[n].disconnect();
}
Gate& Gate::operator+=(Terminal&& term)
{
  if (_size == N)
    throw std::runtime_error("Overflow");
  terminals[_size++] = term;
  return *this;
}

std::istream& operator>>(std::istream& stream, Gate& gate)
{
  for (size_t i = 0; i < gate._size; i++)
  {
    if (&stream == &std::cin)
      std::cout << "Enter state for terminal#" << i + 1 << (gate.terminals[i].isOutput ? " (Output)>" : " (Input)>");
    stream >> gate.terminals[i];
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, Gate& gate)
{
  stream << "Inputs:  ";
  for (size_t i = 0; i < gate._size; i++)
    if (!gate.terminals[i].isOutput)
      stream << (((gate.terminals[i].state == 2) ? "  X   " : (gate.terminals[i].state ? " High " : " Low  ")));
  stream << "\nOutputs: ";
  for (size_t i = 0; i < gate._size; i++)
    if (gate.terminals[i].isOutput)
      stream << (((gate.terminals[i].state == 2) ? "  X   " : (gate.terminals[i].state ? " High " : " Low  ")));
  return stream;
}
