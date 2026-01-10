#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (6);   // 6-node partial mesh

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // ---- PARTIAL MESH LINKS ----
  p2p.Install (nodes.Get (0), nodes.Get (1));
  p2p.Install (nodes.Get (0), nodes.Get (2));
  p2p.Install (nodes.Get (1), nodes.Get (2));  // triangle

  p2p.Install (nodes.Get (1), nodes.Get (3));
  p2p.Install (nodes.Get (2), nodes.Get (4));
  p2p.Install (nodes.Get (3), nodes.Get (4));  // second triangle

  p2p.Install (nodes.Get (3), nodes.Get (5));
  p2p.Install (nodes.Get (4), nodes.Get (5));  // connect node 5 to mesh

  InternetStackHelper internet;
  internet.Install (nodes);

  AnimationInterface anim ("24bce1462_mesh.xml");

  // ---- POSITIONS (CLEAR SHAPE) ----
  anim.SetConstantPosition (nodes.Get (0), 100, 200);
  anim.SetConstantPosition (nodes.Get (1), 50, 150);
  anim.SetConstantPosition (nodes.Get (2), 150, 150);
  anim.SetConstantPosition (nodes.Get (3), 50, 50);
  anim.SetConstantPosition (nodes.Get (4), 150, 50);
  anim.SetConstantPosition (nodes.Get (5), 100, 100);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
