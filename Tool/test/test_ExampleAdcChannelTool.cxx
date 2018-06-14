// test_ExampleAdcChannelTool.cxx
//
// David Adams
// April 2017
//
// Test ExampleAdcChannelTool.

#include <string>
#include <iostream>
#include <fstream>
#include "dune/DuneInterface/Tool/AdcChannelTool.h"
#include "dune/ArtSupport/DuneToolManager.h"

#undef NDEBUG
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using fhicl::ParameterSet;

//**********************************************************************

int test_ExampleAdcChannelTool(bool useExistingFcl =false) {
  const string myname = "test_ExampleAdcChannelTool: ";
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << myname << line << endl;
  string fclfile = "test_ExampleAdcChannelTool.fcl";
  if ( ! useExistingFcl ) {
    cout << myname << "Creating top-level FCL." << endl;
    ofstream fout(fclfile.c_str());
    fout << "tools: {" << endl;
    fout << "  mytool: {" << endl;
    fout << "    tool_type: ExampleAdcChannelTool" << endl;
    fout << "    Label: \"mytool\"" << endl;
    fout << "  }" << endl;
    fout << "}" << endl;
    fout.close();
  } else {
    cout << myname << "Using existing " << fclfile << endl;
  }

  cout << myname << line << endl;
  cout << myname << "Fetching tool manager." << endl;
  DuneToolManager* ptm = DuneToolManager::instance(fclfile);
  assert ( ptm != nullptr );
  DuneToolManager& tm = *ptm;
  tm.print();
  assert( tm.toolNames().size() == 1 );

  cout << myname << line << endl;
  cout << myname << "Fetching tool." << endl;
  auto ptoo = tm.getPrivate<AdcChannelTool>("mytool");
  assert( ptoo != nullptr );

  cout << myname << line << endl;
  cout << myname << "View with tool." << endl;
  AdcChannelData acd;
  acd.run=123;
  acd.event = 2468;
  DataMap dm = ptoo->view(acd);
  dm.print();

  cout << myname << line << endl;
  cout << myname << "Done." << endl;
  return 0;

}

//**********************************************************************

#if 0

int main(int argc, char* argv[]) {
  bool useExistingFcl = false;
  if ( argc > 1 ) {
    string sarg(argv[1]);
    if ( sarg == "-h" ) {
      cout << "Usage: " << argv[0] << " [ARG]" << endl;
      cout << "  If ARG = true, existing FCL file is used." << endl;
      return 0;
    }
    useExistingFcl = sarg == "true" || sarg == "1";
  }
  return test_exampleAdcChannelTool(useExistingFcl);
}

#endif

//**********************************************************************


  

