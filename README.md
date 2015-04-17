# SSP-Routing
1.  Implement Dijkstra's Single Source Shortest Path ( s s p) algorithm for undirected graphs using Fibonacci heaps. 
    Adjacency list is used to represent for graphs.
2.  Implement a routing scheme ( rout ing) for a network. 
    Each router has an IP address and packets are forwarded to the next hop router by longest prefix matching using a binary trie. 
    For each router R in the network, call ssp implemented in Part 1 to obtain shortest path from R to each destination router Y. 
    To construct the router table for R, for each destination Y, examine the shortest path from R to Y and determine the router Z just after R on this path. 
    This gives you a set of pairs <IP address of Y, next-hop router Z>. 
    Insert these pairs into a binary trie. 
    Finally, do a postorder traversal, removing subtries in which the next hop is the same for all destinations. 
    Thus, multiple destinations having a prefix match and the same next hop will be grouped together in the trie.
