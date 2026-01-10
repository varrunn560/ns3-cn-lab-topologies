#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (20);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  csma.Install (nodes);

  InternetStackHelper internet;
  internet.Install (nodes);

  AnimationInterface anim ("24bce1462_bus.xml");

  // Place nodes in straight line (this IS the bus)
  for (uint32_t i = 0; i < nodes.GetN (); i++)
  {
    anim.SetConstantPosition (nodes.Get (i), 20 + i * 15, 60);
  }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
