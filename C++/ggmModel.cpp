#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

int main(int argc, char *argv[]){
  
  int SEED = atoi(argv[1]);  // Seed
  int N = atoi(argv[2]);     // Number of nodes
  int M = atoi(argv[3]);     // Number of nodes
  double *V;
  V = (double *) malloc(N*sizeof(double));
  
  
  int m0 = 5;                // Initial number of nodes
  double alpha = 1.;         // Switching probability
  
  // Random generators
  std::default_random_engine generator;
  std::uniform_real_distribution<double> ureal(0., 1.);
  
  // Connections
  std::vector<std::vector<int>> edge_list(N);
  
  // Index variables
  int i, j, k;
  
  
  
  // Connecting the initial core
  for ( j = 0; j < m0; j++ )
  {
    for ( i = j+1; i < m0; i++ )
    {
      edge_list[i].push_back(j);
      edge_list[j].push_back(i);
    }
  }
  
  
  // Growing the network
  for ( j = m0; j < N; j++)
  {
    
    if ( ureal(generator) <= alpha) 
    {
      
      // Erdos-Renyi branch
      
      for ( k = 0; k < M; k++ )
      {
	// Choosing a pair
	i = (j-1)*ureal(generator);
	edge_list[i].push_back(j);
	edge_list[j].push_back(i);
      }
      
    }
    else {
      
      // Barabasi-Albert branch
      
      
      
    }
  }
  
  
  std::ofstream outFile;

  outFile.open(argv[4]);

  for(int k = 0; k < N; k++)
    for(std::vector<int>::iterator it = edge_list[k].begin(); it != edge_list[k].end(); ++it)
      outFile << k << " " << *it << std::endl;

  outFile.close();

  return 0;
} 
