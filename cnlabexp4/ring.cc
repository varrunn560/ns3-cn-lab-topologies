#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include <cmath>

using namespace ns3;

int main ()
{
  uint32_t nNodes = 20;
  NodeContainer nodes;
  nodes.Create (nNodes);

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  for (uint32_t i = 0; i < nNodes - 1; i++)
    p2p.Install (nodes.Get (i), nodes.Get (i + 1));

  p2p.Install (nodes.Get (nNodes - 1), nodes.Get (0));

  InternetStackHelper internet;
  internet.Install (nodes);

  AnimationInterface anim ("24bce1462_ring.xml");

  double radius = 50.0, cx = 100.0, cy = 100.0;

  for (uint32_t i = 0; i < nNodes; i++)
  {
    double angle = 2 * M_PI * i / nNodes;
    anim.SetConstantPosition (nodes.Get (i),
                              cx + radius * cos(angle),
                              cy + radius * sin(angle));
  }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
