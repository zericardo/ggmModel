# -*- coding: utf-8 -*-

import igraph as ig
import numpy as np


def preferentialAttachment():
    #To do: Create a version of preferential attachment function.
    return "Preferential attachment"


def ggmModel(N, alpha, A, m0, m):
    """
    This function creates a undirected network. It uses the model of
    Gómez-Gardeñes and Moreno (ref here) to create networks with adjustable
    tunable topology from scale-free to Erdös-Rényi.

    Parameters
    ----------
    N : int
        The size of the final netwrok.
    alpha: float
        Must be on the interval [0,1) and represents the probability of a node
        with no connections be uniformely linked with any other node in the
        network.
    A : function
        The preferential attachment function used for the preferential
        attachment connections.
    m0 : int
        Number of nodes on the initial fully connected network.
    m : int
        Number of times that each chosen node can create a uniformely of
        preferential attachment to different nodes.
    """

    G = ig.Graph.Full(m0, directed = False, loops = False)

    #Adds the remaining nodes to the graph. No edges are added.
    G.add_vertices(N-m0)

    count = m0

    while(count != N): #Repeats for all new nodes.

        chosenID = np.random.randint(low = m0, high = N)

        for i in range(m): #Repeats m times for the chosen node.

            probChosen = np.random.rand()

            if(probChosen <= alpha):

                ## ER section
                erID = np.random.randint(low = 0, high = (N-1))

                if (erID >= chosenID): #No self-loops.
                    erID += 1

                G.add_edge(chosenID, erID)

            else:

                ## BA section
                j = 1 #Just for avoid identation problems.

        count +=1


    return G



if __name__ == "__main__":
    # A simple test
    G = ggmModel(1000, 0.5, preferentialAttachment, 4, 5)
    print G.vcount(), G.ecount()
