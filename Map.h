#ifndef MAP_H
#define MAP_H
#include "Pair.h"
#include <iostream>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include "Myexception.h"
#include <vector>
#include <cassert>

/**
  @brief classe Map
  La classe implementa una struttura dati associativa Map. 
  La struttura dati memorizza una coppia di dati <chiave, valore> di tipo generico C
  e V. I valori delle chiavi devono essere univoci: non e' possibile inserire una
  coppia <C,V> con valore della chiavi gia' presente. Non e' previsto un ordinamento delle coppie per chiave.
*/
template <typename C, typename V> 
class Map{
  /**
   @brief classe Map
   classe che viene usata per implementare la struttura dati Map
  */
public:
  typedef unsigned int size_type; //tipo del dato size
  typedef Pair<C,V> coppia; //tipo del dato della Map

  /**
   @brief costruttore default
   costruttore di default
   @post _map == nullptr
   @post _size = 0
  */

  Map(): _map(nullptr), _size (0){
    #ifndef NDEBUG
      std::cout << "Map::Map()" << std::endl;
    #endif
  }

  /**
   @brief distruttore
   distruttore
  */

  ~Map() {
    clear();
    #ifndef NDEBUG
      std::cout << "Map::~Map()" << std::endl;
    #endif
  }

  /**
    Copy constructor
    Copiamo i dati membro a membro.
    Essendo un a struttura di supporto a Map scelgo di condividere i dati

    @param other map da copiare
    @post _map != nullptr
    @post _size = other._size
*/

  Map(const Map &other): _map(nullptr), _size(0){
    _map = new coppia[other._size];
    _size = other._size;
    try {
    for(size_type i=0; i<_size; ++i)
      _map[i] = other._map[i];
  }
  catch(...) {
    clear();
    throw;
  }
  #ifndef NDEBUG
  std::cout << "Map::Map(const Map&)"<< std::endl;
  #endif
  }

/**
      Operatore di assegnamento. 

      @param other Map da copiare
      @return reference al Map this
*/

  Map& operator=(const Map &other){
  if (this != &other) {

    Map tmp(other);

    this->swap(tmp);
  }

  #ifndef NDEBUG
  std::cout << "Map::operator=(const Map &)" << std::endl;
  #endif

  return *this;
}

/**
    Scambia due Map

    @param Map da scambiare
*/

void swap(Map &other) {
  std::swap(_map, other._map);
  std::swap(_size, other._size); 
}
/**
      Metodo che stabilisce l'unicita' di una chiave all'interno di una Map

      @param coppia
      @return true/false se chiave unica/non unica
*/
  bool isUnique(const coppia &p){
    size_type i;
    for(i=0;i<_size;i++){
      if(_map[i].chiave == p.chiave)
      //if(_map[i] == p)
      return false;
    }
    return true;
  }
  /**
      Metodo per aggiungere una nuova coppia <C,V> nella Map

      @param coppia da inserire nella Map
      @post _size = _size+1
      @throw std::bad_alloc possibile eccezione di allocazione
      @throw key_not_unique_exception lanciata se viene passata una chiave gia' presente
  */
  void add(const coppia &p){
    if(_size==0){
      try
      {
        _map = new coppia[_size+1];
        _map[_size] = p;
        _size++;
      }
      catch(...)
      {
        clear();
        throw;
      }
      
      
    }
    else{
      if(isUnique(p)){
				coppia *tmp;
        try{
          tmp = new coppia[_size+1];
          size_type i;
          for(i=0;i<_size;i++)
          tmp[i]=_map[i];
          tmp[i]=p;
          delete[] _map;
          _map = nullptr;
          _map = tmp;
          _size++;
        }
        catch(...)
        {
          delete[] tmp;
          tmp = nullptr;
          clear();
          throw;
        }
      }
      else{
        throw(key_not_unique_exception("Chiave presente! Elemento non inserito."));
      }
    }
  }
 /**
    Metodo che svuota la Map

    @post _map == nullptr
    @post _size == 0
*/
  void clear(){

   #ifndef NDEBUG
  std::cout << "clear()" << std::endl;
  #endif
  
  delete[] _map;
  _map = nullptr;
  _size = 0;
}
 /**
    Metodo che ricerca una chiave C all'interno della struttura dati

    @param chiave di tipo C
    @return i indice della chiave (se presente), -1 altrimenti
*/
  size_type search(const C &chiave){
  for(size_type i = 0; i<_size;i++)
    if(_map[i].chiave==chiave)
      return i;
  return -1;
}
/**
      Metodo che restituisce il valore di una Pair data una chiave C 
			presente all'interno della Map

      @param chiave di tipo C
      @return valore V 
      @throw key_not_found_exception lanciata se la chiave non e' presente
*/
V& trova(const C &chiave){
	size_type i = search(chiave);
	if(i!=-1)
		return _map[i].valore;
	else
	throw(key_not_found_exception("Chiave non presente nella struttura dati!"));
}

/**
      Metodo che restituisce un vettore contenente tutte le chiavi di tipo C
      presenti nella struttura dati
      @return std::vector<C> v vettore delle chiavi 
*/

std::vector<C> keys(){
  std::vector<C> v;
  for(size_type i = 0; i<_size;i++)
    v.push_back(_map[i].chiave);
  return v;
}

/**
    Rimuove una coppia con una certa chiave presente nella Map

    @param C chiave della coppia da rimuovere
    @post _size = _size-1

    @throw std::bad_alloc possibile eccezione di allocazione
*/
void remove(const C &chiave){
    //array di zero elementi
  if(_size==0){
    return;
  }
  else{
  size_type index = search(chiave);
  //valore non trovato: la funzione non restituisce nulla
  if(index==-1)
  return;
    else{
			coppia* tmp;
      try
      {
        tmp = new coppia[_size-1];
        size_type i;
        for(i=0;i!=index;i++)
          tmp[i]=_map[i];
        for(;i<_size-1;i++)
          tmp[i]=_map[i+1];
        delete[] _map;
        _map = nullptr;
        _map = tmp;
        _size--;
      }
      catch(...)
      {
        delete[] tmp;
        tmp = nullptr;
        clear();
        throw;
      } 
    }
  }
  }

/**
    Funzione che implementa l'operatore di stream.
    La funzione e' templata sulla Map ed e' dichiarata
    friend perche' voglio accedere ai dati privati di Map

    @param os stream di output
    @param m Map da inviare allo stream di output

    @return lo stream di output
*/
  friend std::ostream &operator<<(std::ostream &os,const Map<C,V> &m) {
    os << "size: " << m._size << std::endl;
    os << "map: ";
    for(size_type i=0; i< m._size;i++){
      os << m._map[i].chiave << " " << m._map[i].valore << " ";
    }
    return os;
}

/**
    Metodo che valuta se esiste una coppia con una certa chiave all'interno della Map

    @param C chiave della coppia da ricercare
		@return true/false se la coppia e'/non e' stata trovata
*/
bool exists(const C &chiave){
  for(size_type i = 0; i<_size;i++){
    if(_map[i].chiave==chiave)
    return true;
  }
  
  return false;
}
/**
    Metodo che restituisce la dimensione della struttura dati

		@return size
*/
size_type size() const{
	return _size;
}
/**
    Metodo che restituisce una coppia presente nella struttura dati
    dato un indice
    @param index

		@return la coppia presente all'indice dato
*/
coppia& getCoppia(size_type index) const{
  assert(index<_size);
	return _map[index];
}

/**
    @brief classe const_interator

    La classe implementa un iteratore forward in sola lettura

*/
class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef coppia                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const coppia*                  pointer;
		typedef const coppia&                  reference;

	
		const_iterator() {
			ptr = nullptr;
		}
		
		const_iterator(const const_iterator &other) {
			ptr = other.ptr;
		}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
      return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return ptr;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(ptr);
      ++ptr;
      return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
      ++ptr;
      return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return ptr != other.ptr;
		}

    private:
		//Dati membro

    const coppia *ptr;
		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Map; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const coppia *p) { 
			ptr = p; 
		}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_map);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_map+_size);
	}

private:
  coppia *_map;
  size_type _size;
};
#endif