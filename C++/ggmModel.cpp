/*
  
  Issues to be fixed:
  - Still need to check for double-connections before connecting
  - Implement update & sort CumDg
  - Start using HashNds
  - Improve BA model part (currently using vertex bag approach)
 */


#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

int main(int argc, char *argv[]){
  
  int SEED     = atoi(argv[1]);  // Seed for default_random_engine
  int N        = atoi(argv[2]);  // Number of nodes
  int M        = atoi(argv[3]);  // Number of nodes
  double alpha = atoi(argv[4]);  // Switching probability
  
  int m0 = 5;                    // Initial number of nodes
  int NConns;                    // Number of connections
  
  //int NumberOfEdges=0;           //Total number of edges
  std::vector<int>  nodeDegs(N, 0); //Vector with the degree of each node

  double *CumDg, *HashNds;
  CumDg   = (double *) malloc(N*sizeof(double));  // Cumulative sum
  HashNds = (double *) malloc(N*sizeof(double));  // Cumulative sum
  
  // Random generators
  std::default_random_engine generator(SEED);
  std::uniform_real_distribution<double> ureal(0., 1.);
  
  // Connections
  std::vector<std::vector<int>> edge_list(N);
  
  // Index variables
  int i, j, k;
  int from, to;
  
  
  // ****
  // Constructing the initial core
  //
  
  for ( j = 0; j < m0; j++ )
  {
    // Connecting the first m0 nodes
    for ( i = j+1; i < m0; i++ )
    {
      edge_list[i].push_back(j);
      nodeDegs[i] += 1;

      edge_list[j].push_back(i);
      nodeDegs[j] += 1;
    }
    
    // Initializing the cumulative vector
    CumDg[j] = (m0 - 1)*(j+1);
  }
  NConns = m0*(m0-1)/2;
  
  
  // ****
  // Growing the network
  //
  
  for ( from = m0; from < N; from++)
  {
    
    if ( ureal(generator) <= alpha) 
    {
      
      // Erdos-Renyi branch
      for ( k = 0; k < M; k++ )
      {
	
	// Logical keys
	int key = 0;         // This key checks for (1) multi-connections and (2) self-connections

	// Choosing a pair
	while ( key == 0 )
	{
	  to = (N-1)*ureal(generator);
	  if ( to != from && std::find(edge_list[to].begin(), edge_list[to].end(), from) == edge_list[to].end() )
	  {
	    key = 1;
	  }
	}
	
	edge_list[to].push_back(from);
	nodeDegs[to] += 1;
	CumDg[to]++;
		    
	edge_list[from].push_back(to);
	CumDg[from]++;
	nodeDegs[from] += 1;
      }
      
    }
    else {
      
      // Barabasi-Albert branch
      for ( k = 0; k < M; k++ )
      {
	int degSum = 0; //Sum of degree
	for(std::vector<int>::iterator it = nodeDegs.begin(); it != nodeDegs.end(); ++it)
	  degSum += *it;

	//std::cout << degSum << std::endl;

	std::vector<int> vertexBag(degSum);
	
	int index = 0;

	for(int position = 0; position < N; position++)
	  for(int number = 0; number < nodeDegs[position]; number++)
	    {
	      vertexBag[index] = position;
	      index += 1;
	    }

	bool isAValidConnection = false;
	
	while(!isAValidConnection)
	  {
	    int randPos = (degSum-1)*ureal(generator);
	    to = vertexBag[randPos];

	     if ( to != from && std::find(edge_list[to].begin(), edge_list[to].end(), from) == edge_list[to].end() )
	       isAValidConnection = true;
	  }
	
	//Free memory
	vertexBag.clear();
	vertexBag.shrink_to_fit();

	edge_list[to].push_back(from);
	nodeDegs[to] += 1;
	CumDg[to]++;
		    
	edge_list[from].push_back(to);
	CumDg[from]++;
	nodeDegs[from] += 1;

	/**
	int Q = NConns*(ureal(generator));
	i = 0;
	while( i >= 0 )
	{
	  if ( Q <= CumDg[i] )
	  {
	    to = i; // to = HashNds[i]
	    i = -10; // breaking loop
	  }
	  
	  i++;
	}
	**/

	//edge_list[from].push_back(to);
	//CumDg[from]++;
	
	//edge_list[to].push_back(from);
	//CumDg[to]++;
      }
      
    }
    
    // Updating number of connections
    NConns += M;
  }
  
  
  // ****
  // Writing the (sorted) output 
  //
  
  std::ofstream outFile;
  outFile.open(argv[5]);
  
  for(int k = 0; k < N; k++){
    
    //Sorting the elements before write them.
    std::sort(edge_list[k].begin(), edge_list[k].end());
    
    for(std::vector<int>::iterator it = edge_list[k].begin(); it != edge_list[k].end(); ++it)
      outFile << k << " " << *it << std::endl;
  }
  
  outFile.close();
  
  
  // The end, my friend
  return 0;
} 
