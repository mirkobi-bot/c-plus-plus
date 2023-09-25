#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <stdexcept>
#include <string>

/**
	@brief 
	Classe eccezione custom che deriva da std::runtime_error.
	La classe gestisce il caso di tentato inserimento di una Pair avente
	una chiave preesistente all'interno della struttura dati Map
*/
class key_not_unique_exception : public std::runtime_error {
public:
	/**
		Costruttore che prende un messaggio d'errore
	*/
	key_not_unique_exception(const std::string &message)
    : std::runtime_error(message){

    }

};
/**
	@brief 
	Classe eccezione custom che deriva da std::runtime_error.
	La classe gestisce il caso in cui si vuole recuperare il valore di una chiave non presente
	nella struttura dati Map
*/
class key_not_found_exception : public std::runtime_error {
public:
	/**
		Costruttore che prende un messaggio d'errore
	*/
	key_not_found_exception(const std::string &message)
    : std::runtime_error(message){

    }

};

#endif


