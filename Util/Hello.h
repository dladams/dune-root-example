// Hello.h

#ifndef Hello_H
#define Hello_H

#include <string>

class Hello {

public:

  Hello(std::string msg);

  // Broadcast message.
  void talk() const;

private:

  std::string m_msg;

};

#endif
