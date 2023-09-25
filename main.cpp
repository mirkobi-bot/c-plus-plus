#include "Map.h"
#include <iostream>
#include "Myexception.h"
#include <vector>
#include <cassert>

typedef Pair<int, std::string> int_str;
typedef Pair<std::string, std::string> str_str;

class Numero{
    public:
    int numero;
    Numero(){}
    Numero(int n):numero(n){}
    bool operator==(const Numero &n){
        return numero == n.numero;
    }

    friend std::ostream &operator<<(std::ostream &os,const Numero &n) {
    os << "numero: ";
    os << n.numero;
    return os;
}
};
/*
metodo che testa le funzioni richieste su una Map<int,std::string>
*/
void test_funzioni_richieste_int_str(){
    
    int_str p(1, "pippo");
    int_str p2(2, "pluto");
    int_str p3(3, "paperino");
    int_str p4(1, "pietro"); //chiave doppia
    Map<int, std::string> m;
    int_str p5(p);
    //test del punto 1
    m.add(p);
    m.add(p2);
    m.add(p3);
    //test del punto 2
    m.remove(4); //rimuovi elemento non esistente
    m.remove(2); //rimuovi elemento esistente
    //test del punto 6
    std::string valore_esiste = m.trova(1);
    std::cout << valore_esiste << std::endl;
    try{
        std::string valore_non_esiste = m.trova(4);
    }
    catch(const key_not_found_exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        m.add(p4);//genera eccezione
    }
    catch(const key_not_unique_exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    //test del punto 3
    bool esiste = m.exists(1);//elemento esistente
    bool non_esiste = m.exists(4);//elemento non esistente
    std::cout << esiste << std::endl;
    std::cout << non_esiste << std::endl;

    //test del punto 4
    m.clear();
    assert(m.size()==0);

    std::cout << m << std::endl;

    //test del punto 7
    std::vector<int> g1;
    g1 = m.keys();
    for (auto i = g1.begin(); i != g1.end(); ++i)
        std::cout << *i << " ";
        std::cout << std::endl;
}

/*
metodo che testa i metodi fondamentali su una Map<int,std::string>
*/
void test_fondamentali_int_str(){
        std::cout << "*** TEST METODI FONDAMENTALI ***" << std::endl;
        std::cout << "test ctor default" << std::endl;
        Map<int, std::string> m1;
        assert(m1.size() == 0);
        std::cout << "test copy constructor" << std::endl;
        Map<int, std::string> m2(m1); 
        assert(m1.size() == m2.size());
        for(unsigned int i =0 ;i < m2.size(); i++)
            assert(m1.getCoppia(i) == m2.getCoppia(i)); 
        std::cout << "test operatore assegnamento =" << std::endl;
        Map<int, std::string> m3;
        typedef Pair<int, std::string> int_str;
        int_str p(1, "pippo");
        m3.add(p);
        m1 = m3;
        assert(m1.size() == m3.size());
        for(unsigned int i =0 ;i< m1.size(); i++)
            assert(m1.getCoppia(i) == m3.getCoppia(i));
        
    }
//test del punto 5 tipo standard
void test_iteratori_int_str(){
    std::cout << "test forward iterator" << std::endl;
    Map<int,std::string>::const_iterator it; 
    Map<int,std::string>::const_iterator ite;

    Map<int, std::string> m1;
    int_str p1(1, "pippo");
    int_str p2(2, "pluto");
    m1.add(p1);
    m1.add(p2);

    ite = m1.end();

    for (it = m1.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;

}

/*
metodo che testa le richieste del progetto su un tipo complesso
*/
void test_classe_numero(){
    Map<Numero,std::string>::const_iterator it;
    Map<Numero,std::string>::const_iterator ite;
    std::cout << "test classe Numero" << std::endl;
    Numero n1(2);
    Numero n2(100);
    Numero n3(2);
    Numero n4(22);
    Map<Numero, std::string> m1;
    typedef Pair<Numero, std::string> numero_str;
    numero_str p1(n1, "pippo");
    numero_str p2(n2, "pluto");
    numero_str p3(n3, "paperino");//chiave doppia
    numero_str p4(n4, "pietro");
    m1.add(p1);
    m1.add(p2);
    m1.add(p4);
    m1.remove(n1);
     try{
        m1.trova(n4);
    }
    catch(const key_not_found_exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        m1.add(p3);//genera eccezione
    }
    catch(const key_not_unique_exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    //test del punto 7
    std::vector<Numero> v;
    v = m1.keys();
    for (auto i = v.begin(); i != v.end(); ++i)
        std::cout << *i << " ";
        std::cout << std::endl;

    //test del punto 5 tipo complesso
    std::cout << "test forward iterator classe Numero" << std::endl;
    ite = m1.end();

    for (it = m1.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;
}
/*
metodo che testa i metodi dell'interfaccia pubblica su una Map<std::string,std::string>
*/
void test_interfaccia_pubblica(){
    Map<std::string,std::string>::const_iterator it;
    Map<std::string,std::string>::const_iterator ite;

    //test swap
    Map<std::string, std::string> m1;
    Map<std::string, std::string> m2;
    str_str p1("1", "Luigi");
    str_str p2("2", "Mario");
    m2.add(p1);
    m2.add(p2);
    std::cout << "m1 Pre-swap"<< std::endl;
    assert(m1.size()==0);
    ite = m1.end();
    for (it = m1.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;
    std::cout << "m2 Pre-swap"<< std::endl;
    assert(m2.size()==2);
    ite = m2.end();
    for (it = m2.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;
    m1.swap(m2);
    std::cout << "m1 Dopo-swap"<< std::endl;
    assert(m1.size()==2);
    ite = m1.end();
    for (it = m1.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;
    std::cout << "m2 Dopo-swap"<< std::endl;
    assert(m2.size()==0);
    ite = m2.end();
    for (it = m2.begin(); it!=ite; ++it)
        std::cout << *it << std::endl;
    //test metodo isunique
    assert(m1.isUnique(p1) == false);
    //test metodo search
    assert(m1.search("1") != -1);
}

int main(int argc, char const *argv[])
{
    
    test_fondamentali_int_str();
    test_funzioni_richieste_int_str();
    test_iteratori_int_str();
    test_classe_numero();
    test_interfaccia_pubblica();
    return 0;
}
