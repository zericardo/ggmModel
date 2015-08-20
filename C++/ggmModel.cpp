#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

int main(int argc, char *argv[]){

  int N = atoi(argv[1]);
  int K = atoi(argv[2]); //Mean degree.

  int M = (int) round( (N-1)*K / 2.0 );

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, N-1);

  std::vector<std::vector<int>> edge_list(N);
  
  int count  = 0;
  int i, j;

  while(count < M) {
    
    i = distribution(generator);
    
    //Avoiding self loops! 
    do {
      j = distribution(generator);
    } while(j == i);
    
    if ( !( std::find(edge_list[i].begin(), edge_list[i].end(), j) != edge_list[i].end() )
	 && !( std::find(edge_list[j].begin(), edge_list[j].end(), i) != edge_list[j].end() ) ){
      edge_list[i].push_back(j);
      edge_list[j].push_back(i);
      count += 1;
    }
    
  }

  std::ofstream outFile;

  outFile.open(argv[3]);

  for(int k = 0; k < N; k++)
    for(std::vector<int>::iterator it = edge_list[k].begin(); it != edge_list[k].end(); ++it)
      outFile << k << " " << *it << std::endl;

  outFile.close();

  return 0;
} 
