## IDS Based AODV

### What is The Scenario?
1. if A node receives hello request from a node S then
2. if Signal strength of S=fixed signal strength in radio
range
3. then node s is classified as a friend
4. Node accepts hello request and perform function
5. Else
6. if Signal strength of S ≈ fixed signal strength in radio range
then
7. Nodes sends test packet to node S
8. If reply of test packet comes in fixed time threshold
9. Then
10. Node is classified as friend and accepts the request include
information in routing table
11. Else Signal strength of S> fixed signal strength in radio range
12. Node S is classified as Malicious and rejects the request.
13. End

### How Does The Code Work?
1. Hello Message propagates.
2. Receiver node checks destinaton and RSS of the betwen itself and sender node. If there is no any risk, it sets the sender as a neighbor node. Optimum distance and radius can be set from omnet.ini file.

    ![](https://i.imgur.com/s4Khprl.png)

3. In isHelloAttack(), it checks the RSS. If radius less than average RSS there is no problem but, if RSS greater than average, it is considered as a suspicious node. If RSS would be bigger than MAX_RSS, we consider it directly malicious.
4. For suspicious nodes, TEST_MSG is sent. If response is greater than average response it consier as malicious but if is not, so it can be added neighbor by node which sends TEST_MSG.
5. After these process, all nodes have non-malicious neighbor and AODV works as is.