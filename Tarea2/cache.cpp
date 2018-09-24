#include"cache.h"
#include"math.h"
#include"cmath"
#include <bitset>

// En el constructor del cache:
// Se calcula el numero de bloques con el tamano del cache, de bloques y el # de vias.
// Con ello se obtiene el index, tag, y offset.
// Se crean mascaras para el index y el tag.
// Se crea la matriz de bloques.
Cache::Cache(int tam_cache, int tam_bloque, int vias){
  int numero_bloques = tam_cache/tam_bloque/vias;
  this->vias=vias;

  // Bits del index y offset.
  // Se necesitaba trabajar con floats debido a la funcion log2.
  float numero_bloques_float = (float)numero_bloques;
  float n_bits_float = log2(numero_bloques_float);
  this->bits_index = (int)n_bits_float;
  float tam_bloque_float = (float)tam_bloque;
  float bits_offset_float = log2(tam_bloque_float);
  this->bits_offset = (int)bits_offset_float;
  this->bits_tag = 32-this->bits_offset-this->bits_index;

  //Fors para mascara de index y de tag
  for (int i = 0; i < this->bits_index; i++) {
    this->index_mask = this->index_mask << 1;
    this->index_mask = this->index_mask + 1;
  }
    this->index_mask = this->index_mask << this->bits_offset;

  for (int i = 0; i < this->bits_tag; i++) {
    this->tag_mask = this->tag_mask << 1;
    this->tag_mask = this->tag_mask + 1;
  }
    this->tag_mask = this->tag_mask << (this->bits_offset+this->bits_index);

  //Matriz de bloques
  //Se inicializa el vector con punteros a tipo bloque.
  //A cada uno de esos punteros se le asigna un arrego de tipo bloque de la cantidad de bloques que hay por via.
  this->Cabeza_vias= new Bloque*[vias];
  for (int i = 0; i < vias; i++) {
    this->Cabeza_vias[i]= new Bloque[numero_bloques];
    }
  int cont_index=0;
  for (int j = 0; j < numero_bloques; j++) {
    for (int i = 0; i < vias; i++) {
      this->Cabeza_vias[i][j].index=j;
    }
  }
}

// Destructor de la clase
Cache::~Cache(void){

}


// En este metodo se verifican las direcciones y se revisa si hay un hit o miss y se
// toma la accion correspondiente: cambiando dirty bit, valor de prediccion cercano y
// en un contador se van antando los load misses, store misses, load hits y store hits.
// Hay que tomar en cuenta que en la instruccion cero = load (leer) && uno = store (escribir).
// Las entradas son la direccion y la instruccion.
void Cache::verificar_direccion(int dir, int instr){

  int Index_dir = dir & this->index_mask;
  int Tag_dir = dir & this->tag_mask;
  int contador_vias=0;
  Index_dir = Index_dir >> this->bits_offset;
  Tag_dir = Tag_dir >> (this->bits_offset+this->bits_index);


  while (contador_vias < this->vias) {
    if (this->Cabeza_vias[contador_vias][Index_dir].vacio==1) {
     this->reemplazar(contador_vias, Index_dir, Tag_dir, instr);
     if (instr==0) {
       load_misses++;
     } else {
       store_misses++;
     }
     break;
      }
      else{
        if (this->Cabeza_vias[contador_vias][Index_dir].tag == Tag_dir ) {
          // esto significaria que es un hit. Entonces verificamos instruccion.
          if (instr==0) {
            load_hits++;
          } else {
            store_hits++;
            this->Cabeza_vias[contador_vias][Index_dir].dirty_bit=1; // caso de stor: dirty bit se cambia a 1. 
          }
          this->Cabeza_vias[contador_vias][Index_dir].RRPV = 0;  // valor de predicción cercano
          break;
        } else{
          contador_vias++;
        }
    }
    if (contador_vias == this->vias) {
    this->victimizar(Index_dir, Tag_dir, instr);
      if (instr==0) {
        load_misses++;
      } else {
        store_misses++;
        }
    }

  }
}

// Este metodo fue creado para el reemplazo de un bloque.
// Entradas: el index, el tag, la via y el dirty bit.
void Cache::reemplazar(int via, int index, int tag, int db){
  this->Cabeza_vias[via][index].tag=tag;
  this->Cabeza_vias[via][index].vacio=0;
  this->Cabeza_vias[via][index].RRPV=2;
  this->Cabeza_vias[via][index].dirty_bit=db;

}

// Este metodo se encarga de decidir cual bloque se victimiza en el caso
// de que el cache este lleno. Se utiliza el valor de prediccion cercano.
// Ademas posee un contador de dirty evictions.
// Entradas: el index, el tag y el dirty bit.
void Cache::victimizar(int index, int tag, int db){

  int contador_vias=0;
  while (true) {
    if (contador_vias==this->vias) {
      modificar_RRPV(index);
      contador_vias=0;
    }
    if (this->Cabeza_vias[contador_vias][index].RRPV == 3) {
      if (this->Cabeza_vias[contador_vias][index].dirty_bit ==1) {
        contador_dirty_evictions ++;
      }
      this->reemplazar(contador_vias, index, tag, db);
      break;
    } else {
      contador_vias++;
    }
  }
}

// Este metodo se encarga de incrementar el RRPV para los casos
// en los que se necesita.
void Cache::modificar_RRPV(int index){
  for ( int i = 0; i < this->vias; i++) {
    if (this->Cabeza_vias[i][index].RRPV != 3) {
      this->Cabeza_vias[i][index].RRPV ++;
    }
  }
}
