// ExampleAdcChannelTool_tool.cc

#include "ExampleAdcChannelTool.h"

//**********************************************************************

ExampleAdcChannelTool::ExampleAdcChannelTool(fhicl::ParameterSet const& ps)
: m_Label(ps.get<string>("Label")) {
  const string myname = "ExampleAdcChannelTool::ctor: ";
  cout << myname << "Parameters:" << endl;
  cout << myname << "  Label: " << m_Label << endl;
}

//**********************************************************************

DataMap ExampleAdcChannelTool::view(const AdcChannelData& acd) const {
  const string myname = "ExampleAdcChannelTool::view: ";
  DataMap res;
  cout << myname << m_Label << " Run " << acd.run << ", event " << acd.event << endl;
  res.setString("label", m_Label);
  res.setInt("run", acd.run);
  res.setInt("event", acd.event);
  return res;
}

//**********************************************************************
