// ExampleAdcChannelTool.h
//
// Example AdcChannelTool.

#ifndef ExampleAdcChannelTool_H
#define ExampleAdcChannelTool_H

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dune/DuneInterface/Tool/AdcChannelTool.h"

class ExampleAdcChannelTool : AdcChannelTool {

public:

  // Ctor from fcl.
  ExampleAdcChannelTool(fhicl::ParameterSet const& ps);

  // View one channel of ADC data.
  // To modify the data, override modify instead.
  DataMap view(const AdcChannelData& acd) const override;

  // This indicates that calls to update are to be routed to view.
  bool updateWithView() const override { return true; }

private:

 std:: string m_Label;

};

#endif

DEFINE_ART_CLASS_TOOL(ExampleAdcChannelTool)
