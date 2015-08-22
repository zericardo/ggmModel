/*
  
  Issues to be fixed:
  - Still need to check for double-connections before connecting
  - Implement update & sort CumDg
  - Start using HashNds
  
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
  
  int m0 = 5;                // Initial number of nodes
  int NConns;                // Number of connections
  
  
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
      edge_list[j].push_back(i);
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
	// Choosing a pair
	to = (from - 1)*ureal(generator);
	
	edge_list[to].push_back(from);
	CumDg[to]++;
		    
	edge_list[from].push_back(to);
	CumDg[from]++;
      }
      
    }
    else {
      
      // Barabasi-Albert branch
      for ( k = 0; k < M; k++ )
      {
	
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
	
	edge_list[from].push_back(to);
	CumDg[from]++;
	
	edge_list[to].push_back(from);
	CumDg[to]++;
      }
      
    }
    
    // Updating number of connections
    NConns += M;
  }
  
  
  
  // ****
  // Writing the output
  //
  
  std::ofstream outFile;
  outFile.open(argv[5]);

  for(int k = 0; k < N; k++)
    for(std::vector<int>::iterator it = edge_list[k].begin(); it != edge_list[k].end(); ++it)
      outFile << k << " " << *it << std::endl;

  outFile.close();
  
  
  // The end, my friend
  return 0;
} 
