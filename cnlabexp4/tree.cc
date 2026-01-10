#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main ()
{
  NodeContainer nodes;
  nodes.Create (7);   // ONLY 7 nodes

  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Tree links
  p2p.Install (nodes.Get (0), nodes.Get (1));
  p2p.Install (nodes.Get (0), nodes.Get (2));
  p2p.Install (nodes.Get (1), nodes.Get (3));
  p2p.Install (nodes.Get (1), nodes.Get (4));
  p2p.Install (nodes.Get (2), nodes.Get (5));
  p2p.Install (nodes.Get (2), nodes.Get (6));

  InternetStackHelper internet;
  internet.Install (nodes);

  AnimationInterface anim ("24bce1462_tree.xml");

  // TREE POSITIONS (ALL NODES)
  anim.SetConstantPosition (nodes.Get (0), 100, 200);
  anim.SetConstantPosition (nodes.Get (1), 50, 150);
  anim.SetConstantPosition (nodes.Get (2), 150, 150);
  anim.SetConstantPosition (nodes.Get (3), 30, 100);
  anim.SetConstantPosition (nodes.Get (4), 70, 100);
  anim.SetConstantPosition (nodes.Get (5), 130, 100);
  anim.SetConstantPosition (nodes.Get (6), 170, 100);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
