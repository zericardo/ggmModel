#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>

struct edge{
  int from;
  int to;
};

int main(int argc, char *argv[]){

  std::random_device rd;
  std::mt19937 gen(rd());

  int N = atoi(argv[1]);
  float K = atof(argv[2]);
  float p = K/N;

  std::vector<edge> edgeList;
  
  for(int i = 0; i < N; i++)
    for(int j = i+1; j < N; j++)
      if(std::generate_canonical<double, 10>(gen) <= p){

	edge aux;

	aux.from = i;
	aux.to = j;

	edgeList.push_back(aux);
      }

  std::ofstream outFile;

  outFile.open(argv[3]);

  for(std::vector<edge>::iterator it = edgeList.begin(); it != edgeList.end(); ++it)
    outFile << it->from << " " << it->to << std::endl;

  outFile.close();

  return 0;
} 
