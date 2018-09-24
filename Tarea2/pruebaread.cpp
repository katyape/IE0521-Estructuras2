#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include"cache.h"
#include <bitset>

using namespace std;

//Definimos variables que utilizaremos para la lectura del trace.
string line;
string Tipo_inst;
int Instrucc;
string Direcc;
int DireccH;
// puntero a objeto tipo cache.
Cache *prueba_cache;


int main(int argc, char* argv[]){

// Esto servia para ejecutarlo de una manera diferente.
  // string TCs=argv[2];
  // string Vs=argv[3];
  // string TBs=argv[4];
  // int TC= stoi(TCs);
  // int V= stoi(Vs);
  // int TB = stoi(TBs);
  // cout << argv[0] << endl;
  // cout << argv[1] << endl;
  // cout << argv[2] << endl;
  // cout << argv[3] << endl;
  // cout << argv[4] << endl;
  // cout << argv[5] << endl;
  // cout << argv[6] << endl;

//  Convertimos string a int los argumentos.
  int TC = stoi(argv[2]);
  int TB = stoi(argv[4]);
  int V = stoi(argv[6]);

// Creacion cache
  prueba_cache = new Cache(TC,TB,V);


// Para leer el archivo y separar instruccion y direccion
  while (getline(cin, line))
  {
      line.erase(0,2);
      stringstream linestream(line);

      getline(linestream, Tipo_inst, ' ');
      getline(linestream, Direcc, ' ');

      Instrucc = stoi(Tipo_inst);
      stringstream hexDirecc(Direcc);
      hexDirecc>>hex>>DireccH;

      prueba_cache->verificar_direccion(DireccH, Instrucc);


  }

// Imprimir lo requerido:
cout << "Cache Parameters:"<< '\n';
cout << "Cache size (kB):"  << dec << TC/1000 << '\n';
cout << "Cache Associativity:" << dec << V << '\n';
cout << "Cache Block Size (B):" << dec << TB << '\n';
cout << "Simulation Results:"<< '\n';
cout << "Store hits:" << dec << prueba_cache->store_hits<< '\n';
cout << "Store misses: " << dec << prueba_cache->store_misses << '\n';
cout << "Load hits: " << dec << prueba_cache->load_hits << '\n';
cout << "Load misses: " << dec << prueba_cache->load_misses << '\n';
cout << "Dirty evictions: " << dec << prueba_cache->contador_dirty_evictions <<'\n';
}
