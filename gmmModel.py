# -*- coding: utf-8 -*-

import igraph as ig
import numpy as np


def preferentialAttachment():
    #To do: Create a version of preferential attachment function.
    return True


def gmmModel(N, alpha, A, m0, m):
    """
    This function creates a undirected network. it uses the model of
    Gómez-Gardeñes and Moreno (ref here) to create networks with adjustable
    tunable topology from scale-free to Erdös-Rényi.
    """

    G = ig.Graph.Full(m0, directed = False, loops = False)

    #Adds the remaining nodes to the graph. No edges are added.
    G.add_vertices(N-m0)

    newNodes = np.arange(m0, N) #IDs of the remaining nodes.
    probList = np.random.rand(N-m0) #Probability for each node.

    
    while(np.size(newNodes) != 0): #Repeats for all new nodes.

        chosedID = np.random.randint(low = 0, high = np.size(newNodes))

        for i in range(m): #Repeats m times for the chosen node.

            if(probList[chosedID] <= alpha):

                ## ER section

                p = 1.0/(N-1)

                erID = chosenID
                while(erID == chosenID):
                    erID = np.random.randint(N)

                probER = np.random.rand()

                if(probER <= p):
                    G.add_edge(chosenID, erID)

                #print "Menor igual a aplha."
            else:
                
                ## BA section
                



        newNodes = np.delete(newNodes, chosedID)
        probList = np.delete(probList, chosedID)


    return G



if __name__ == "__main__":
    # A simple test
    G = gmmModel(10000, 0.5, preferentialAttachment(), 4, 5)
    print G.vcount(), G.ecount()
