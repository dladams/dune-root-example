# dune-root-example

## Introduction
This repository is an package showing how to use duneadc classes
in Root and add utilities and (art) tools that may be used both
in Root and in other applications including larsoft event
processing.

To keep things simple, compilation is done by Root. Shared libraries
are installed in the lib directory which is added to client's
library path when the setup file is sourced.

## Usage
To build and test the package, do the following:
```
git clone https://github.com/dladams/dune-root-example.git
> cd dune-root-example
> setup duneptc v06_80_00_01
> source ./setup.sh
> root.exe
.
.
.
Root>
```

All the duneadc and local utiltities loaded in the rootlogon file should
be accessible. E.g. to run the script Script/date.C:

```
Root> date()
Date/Time = Thu Jun 14 12:53:50 2018
Root>[1] 
```

A DUNE tool manager may be constructed from a fcl file and it tools
listed:
```
Root> DuneToolManager dtm("mytools.fcl")
(DuneToolManager &) @0x7f89eb9eb220
Root> dtm.print()
Tools for mytools.fcl:
  myExampleTool
Root> 
```

For a longer listing, try one of the production fcl files:
```
root [3] DuneToolManager dtm2("protoDUNE_reco.fcl")
(DuneToolManager &) @0x7f89eb9eb308
root [4] dtm2.print()
Tools for protoDUNE_reco.fcl:
  adcChannelDumper
  adcChannelPedestalPlotter
  adcChannelPedestalRmsPlotter
  adcDPhase3x1x1LocalRoiBuilder
  adcDPhase3x1x1RoiBuilder
.
.
.
```

Tools cannot be retrieved from the Root command line but you can run
a compiled script that does. The following demonstrates use of the
example ADC channel tool that is created in this package:
```
Root> .x Tool/test/test_ExampleAdcChannelTool.cxx+
test_ExampleAdcChannelTool: -----------------------------
test_ExampleAdcChannelTool: Creating top-level FCL.
test_ExampleAdcChannelTool: -----------------------------
test_ExampleAdcChannelTool: Fetching tool manager.
DuneToolManager::instance: Configuration file: test_ExampleAdcChannelTool.fcl
Tools for test_ExampleAdcChannelTool.fcl:
  mytool
test_ExampleAdcChannelTool: -----------------------------
test_ExampleAdcChannelTool: Fetching tool.
ExampleAdcChannelTool::ctor: Parameters:
ExampleAdcChannelTool::ctor:   Label: mytool
test_ExampleAdcChannelTool: -----------------------------
test_ExampleAdcChannelTool: View with tool.
ExampleAdcChannelTool::view: mytool Run 123, event 2468
Status: 0
Integers:
  event: 2468
  run: 123
Strings:
  label: mytool
test_ExampleAdcChannelTool: -----------------------------
test_ExampleAdcChannelTool: Done.
(int) 0
```

Once you have setup this package, you can also call this tool from
the DataPrep module used in DUNE reconstruction. And following
this template, you can create and run your own DataPrep tools
without need to build or modify dunetpc. You do need to set up an
installed version.

