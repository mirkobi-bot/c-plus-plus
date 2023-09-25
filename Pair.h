#ifndef PAIR_H
#define PAIR_H
#include <iostream>

/**
  @brief struct Pair
  La struct e' composta da due campi: chiave di tipo C e valore di tipo V
*/
template <typename C, typename V> 
struct Pair { 
  C chiave; 
  V valore;

  Pair(){}

  /**
      costruttore secondario che crea una Pair a partire dai campi C e V

      @param chiave di tipo C, valore di tipo V
      @post chiave = c, valore = v
*/

  Pair (const C& c, const V& v){
  chiave = c;
  valore = v;
  }

  ~Pair(){}

   /**
      copy constructor che crea una Pair a partire da un'altra
      copiando i dati membro a membro

      @param Pair <C,V> p
      @post chiave = p.chiave, valore = p.valore
*/
  Pair(const Pair &p){
    chiave = p.chiave;
    valore = p.valore;
  }
  /**
      Operatore di assegnamento. 

      @param other Pair da copiare
      @return reference al Pair this
*/

  Pair& operator=(const Pair &other){
  if (this != &other) {

    Pair tmp(other);

    this->swap(tmp);
  }

  #ifndef NDEBUG
  std::cout << "Pair::operator=(const Pair &)" << std::endl;
  #endif

  return *this;
}

/**
    operatore di uguaglianza
    @param Pair other
    @return true/false se la coppia e' uguale/diversa
*/
bool operator==(const Pair& other)
{
  #ifndef NDEBUG
  std::cout << "Pair::operator==(const Pair &other)" << std::endl;
  #endif
   return chiave == other.chiave && valore == other.valore;
}
//operatore di disuguaglianza
bool operator!=(const Pair& other) {
   return !(this == other);
}
//operatore di stream
friend std::ostream &operator<<(std::ostream &os,const Pair<C,V> &c) {
    os << "coppia: ";
    os << c.chiave << " " << c.valore;
    return os;
}
//funzione di swap
void swap(Pair &other) {
  std::swap(chiave, other.chiave);
  std::swap(valore, other.valore);
}
};



#endif