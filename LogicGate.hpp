#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
/*
 Represents gate's terminal
 */
struct Terminal
{
  bool isOutput;
  /*
 Connection number
     */
  unsigned short conn_num;
  /*
 0 - Low, 1 - High, 2 - Undefined
     */
  unsigned short state;
  /*
 Construct a new Terminal object
    isout - Is terminal an output terminal?
  conns - Number of connections
  _state - Current state
   */
  Terminal(bool isout = false, unsigned short conns = 0, unsigned short _state = 0)
      : isOutput{isout}, conn_num{conns}, state{_state}
  {
  }
  /*
 Increases number of connections if its possible
   */
  unsigned short const& connect()
  {
    if ((isOutput && conn_num < 3) || (!isOutput && conn_num == 0))
      return ++conn_num;
    throw std::runtime_error("Number of connections can't be increased!");
  }
  /*
 Decreases number of connections if its possible
   */
  unsigned short const& disconnect()
  {
    if (conn_num > 0)
      return --conn_num;
    throw std::runtime_error("Can not disconnect! No connections");
  }

  /*
 Input state from stream
    stream
   */
  std::istream& input(std::istream& stream = std::cin)
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
        state = 0;
        break;
      case '1':
        state = 1;
        break;
      case 'X':
        state = 2;
        break;
      default:
        std::cout << "Retry>";
        flag = 1;
        break;
      }
    }
    return stream;
  }
};

/*
 Gate repr
 */
struct Gate
{

  static constexpr size_t N = 20;
  /*
 Gate's terminals
     */
  Terminal terminals[N];
  /*
 Current number of terminals
     */
  size_t size;
  /*
 Construct a new Gate object (default type = invertor)
     */
  Gate() : terminals{{false, 0, 0}, {true, 0, 1}}, size{2} {}
  /*
 Construct a new Gate object
    in - number of input connections
  out - number of output connections
   */
  Gate(size_t in, size_t out)
  {
    if (in + out > N)
      throw std::runtime_error("Overflow");
    for (size = 0; size < in; size++)
      terminals[size] = Terminal(false, 0, 0);
    for (; size < in + out; size++)
      terminals[size] = Terminal(true, 0, 0);
  }
  /*
 Construct a new Gate object
    terms - contents
   */
  Gate(Terminal terms[N]) : size{N}
  {
    for (size_t i = 0; i < N; i++)
      terminals[i] = terms[i];
  };
  /*
 Construct a new Gate object
    terms - vector of terminals to construct from
   */
  Gate(std::vector<Terminal>& terms)
  {
    for (size = 0; size < N && size < terms.size(); size++)
    {
      terminals[size] = terms[size];
    }
  }

  /*
 Set the Terminal State
    n - terminal index
  val - value to set
   */
  unsigned short const& setTerminalState(size_t n, unsigned short val)
  {
    if (n >= size)
      throw std::out_of_range("");
    if (val < 3)
      return terminals[n].state = val;
    return terminals[n].state;
  }
  /*
 Get the Terminal State
    n - terminal index
   */
  unsigned short const& getTerminalState(size_t n)
  {
    if (n >= size)
      throw std::out_of_range("");
    return terminals[n].state;
  }
  /*
 Increase number of connections for terminal by index
    n - index
   */
  void connect(size_t n)
  {
    if (n >= size)
      throw std::out_of_range("");
    terminals[n].connect();
  }
  /*
 Decrease number of connections for terminal by index
    n - index
   */
  void disconnect(size_t n)
  {
    if (n >= size)
      throw std::out_of_range("");
    terminals[n].disconnect();
  }
  /*
 Add terminal to gate
    term - rvalue ref to terminal to be added
   */
  Gate& addTerminal(Terminal&& term)
  {
    if (size == N)
      throw std::runtime_error("Overflow");
    terminals[size++] = term;
    return *this;
  }

  /*
 Input states from stream
    stream
   */
  std::istream& input(std::istream& stream = std::cin)
  {
    for (size_t i = 0; i < size; i++)
    {
      std::cout << "Enter state for terminal#" << i + 1 << (terminals[i].isOutput ? " (Output)>" : " (Input)>");
      // stream >> terminals[i].state;
      terminals[i].input(stream);
    }
    return stream;
  }

  /*
 Output gate to stream
    stream
   */
  std::ostream& output(std::ostream& stream = std::cout)
  {
    stream << "Inputs:  ";
    for (size_t i = 0; i < size; i++)
      if (!terminals[i].isOutput)
        stream << (((terminals[i].state == 2) ? "  X   " : (terminals[i].state ? " High " : " Low  ")));
    stream << "\nOutputs: ";
    for (size_t i = 0; i < size; i++)
      if (terminals[i].isOutput)
        stream << (((terminals[i].state == 2) ? "  X   " : (terminals[i].state ? " High " : " Low  ")));
    return stream;
  }
};
