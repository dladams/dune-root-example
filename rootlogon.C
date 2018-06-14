// rootlogon_load.C
//
// David Adams
// August 2017
//
// Root startup file for dunefemb.

{
  cout << "Welcome to the DUNE root example package." << endl;

  // Define a build directory so object and library files don't pollute
  // the local directory.
  // User may want/need to delete this if mods are made in dunetpc.
  // The location is specified by the env variable ACLICDIR which is
  // defined in a setup file. The location changes with the dunetpc version.
  string buildDir;
  const char* pch = gSystem->Getenv("ACLICDIR");
  if ( pch == nullptr ) {
    cout << "ACLICDIR must be defined" << endl;
    cout << "Please source ./setup.sh" << endl;
    exit(2);
  } else {
    buildDir = pch;
  }
  cout << "ACLiC build dir: " << buildDir << endl;
  string utilLibDir = buildDir + "/lib";
  string toolLibDir = utilLibDir;
  cout << "Util library dir: " << utilLibDir << endl;
  cout << "Tool library dir: " << toolLibDir << endl;
  gSystem->SetBuildDir(buildDir.c_str());
  string dtinc = gSystem->Getenv("DUNETPC_INC");
  cout << "Dunetpc include dir: " << dtinc << endl;
  string sarg = "-I" + dtinc;
  string drinc = gSystem->Getenv("DUNE_RAW_DATA_INC");
  cout << "Dune_raw data include dir: " << drinc << endl;
  sarg = "-I" + drinc;
  gSystem->AddIncludePath(sarg.c_str());

  // Load the dunetpc and other supporting libraries.
  vector<string> libs;
  libs.push_back("$FHICLCPP_LIB/libfhiclcpp");
  libs.push_back("$DUNETPC_LIB/libdune_ArtSupport");
  libs.push_back("$DUNETPC_LIB/libdune_DuneServiceAccess");
  libs.push_back("$DUNETPC_LIB/libdune_DuneCommon");
  string libext = "so";
  string arch = gSystem->GetBuildArch();
  if ( arch.substr(0,3) == "mac" ) libext = "dylib";
  for ( string lib : libs ) {
    string libpath = lib + "." + libext;
    string libres = gSystem->ExpandPathName(libpath.c_str());
    if ( 1 ) cout << "AddLinkedLibs: " << libres << endl;
    gSystem->AddLinkedLibs(libres.c_str());
  }

  // Load the dunetpc classes we would like available on the command line.
  cout << "Loading dunetpc classes." << endl;
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/ArtSupport/DuneToolManager.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/DuneCommon/TPadManipulator.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/DuneInterface/AdcChannelData.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/DuneInterface/Tool/AdcChannelTool.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/ArtSupport/ArtServiceHelper.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/DuneServiceAccess/DuneServiceAccess.h+");
  gROOT->ProcessLine(".L $DUNETPC_INC/dune/DuneCommon/coldelecResponse.h+");

  // Build scripts to be used only from the Root command line.
  cout << "Loading local libraries." << endl;
  gROOT->ProcessLine(".L Script/date.C");

  // Build utilities, i.e. classes, functions, etc. whose libraries
  // are installed at buildDir/lib and so visible to clients.
  // The source for utility UNAME is taken from Util/UNAME.cxx and
  // the library is libUNAME.so 
  vector<string> unames = {"Hello"};
  string oldBuildDir = gSystem->GetBuildDir();
  gSystem->SetBuildDir(utilLibDir.c_str());
  for ( string uname : unames ) {
    string sname = "Util/" + uname + ".cxx";
    string lname = "lib" + uname;   // Root adds the extension.
    gSystem->CompileMacro(sname.c_str(), "-ck", lname.c_str());
  }
  gSystem->SetBuildDir(oldBuildDir.c_str());
 
  // Build local tools.
  // These are art tools--configured with fcl and discovered automatically.
  // The source for tool TNAME is taken from Tool/TNAME_tool.cc.
  vector<string> tnames = {"ExampleAdcChannelTool"};
  cout << "Building tools." << endl;
  oldBuildDir = gSystem->GetBuildDir();
  gSystem->SetBuildDir(toolLibDir.c_str());
  for ( string tname : tnames ) {
    string sname = "Tool/" + tname + "_tool.cc";
    string lname = "lib" + tname + "_tool";   // Root adds the extension.
    gSystem->CompileMacro(sname.c_str(), "-ck", lname.c_str());
  }
  gSystem->SetBuildDir(oldBuildDir.c_str());

  cout << "Finished loading." << endl;
}
