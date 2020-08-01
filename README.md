# IDS Based AODV

1: If A node receives hello request from a node S then
2: if Signal strength of S= fixed signal strength in radio
range
3: then node s is classified as a friend
4: Node accepts hello request and perform function
5: Else
6: if Signal strength of S ≈ fixed signal strength in radio range
then
7: Nodes sends test packet to node S
8: If reply of test packet comes in fixed time threshold then
9: Node is classified as friend and accepts the request include
information in routing table
10: Else Signal strength of S> fixed signal strength in radio
range
11: Node S is classified as Malicious and rejects the request.
End