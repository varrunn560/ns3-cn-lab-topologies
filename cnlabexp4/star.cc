// Name: Varun Dubey
// Reg No: 24BCE1462
// Topology: Star

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (20);   // 1 hub + 19 spokes

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Star connections: node 0 is hub
  for (uint32_t i = 1; i < 20; i++)
  {
    p2p.Install (nodes.Get (0), nodes.Get (i));
  }

  InternetStackHelper internet;
  internet.Install (nodes);

  AnimationInterface anim ("24bce1462_star.xml");

  // Positioning for clean star view
  anim.SetConstantPosition (nodes.Get (0), 100, 100); // center

  double radius = 70;
  for (uint32_t i = 1; i < 20; i++)
  {
    double angle = 2 * M_PI * i / 19;
    anim.SetConstantPosition (
      nodes.Get (i),
      100 + radius * cos(angle),
      100 + radius * sin(angle)
    );
  }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
