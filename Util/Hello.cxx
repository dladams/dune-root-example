// Hello.cxx

#include "Hello.h"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

//**********************************************************************

Hello::Hello(string msg) : m_msg(msg) { }

//**********************************************************************

void Hello::talk() const {
  cout << m_msg << endl;
}

//**********************************************************************

