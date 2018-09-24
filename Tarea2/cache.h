// Para que no se redefina la clase
#ifndef CACHE
#define CACHE

#include<string>
#include<iostream>
using namespace std;

//Se crea una estructura llamada Bloque.
//Esta estructura poseera su tag, index, valor de dirty bit y ademas
// un atributo para verificar si esta vacio y el valor de prediccion de reuso.
typedef struct Bloque{

  long tag=0;
  long index=0;
  int dirty_bit=0;
  int vacio=1;
  int RRPV=3;

}Bloque;

class Cache {
// Esta clase Cache poseera los atributos que se muestran:
// Su numero de vias, contadores para misses, hits, dirty evictions, la mascaras
// que necesitara y los metodos que se muestran para que trabaje adecuadamente.
// Todo se trabajara de manera publica por motivos de simplicidad.
public:
  int contador_dirty_evictions = 0;
  int store_misses = 0;
  int store_hits = 0;
  int load_misses = 0;
  int load_hits=0;
  long index_mask, tag_mask;
  int bits_tag, bits_index, bits_offset;
  int vias;
  Bloque **Cabeza_vias;

  //Metodos. Void por simplicidad.
  Cache(int, int, int);
  ~Cache(void);
  void verificar_direccion(int, int);
  void reemplazar(int, int, int, int);
  void modificar_RRPV(int);
  void victimizar(int, int, int);
};
#endif
