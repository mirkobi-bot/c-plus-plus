****Progetto C++****
Il progetto implementa una struttura dati associativa Map. 
La struttura dati memorizza una coppia di dati <chiave, valore> di tipo generico C e V.
I valori delle chiavi devono essere univoci: non è possibile inserire una
coppia <C,V> con valore della chiavi già presente. Nel caso deve essere lanciata
una eccezione. Non è previsto un ordinamento delle coppie per chiave.
La coppia di dati <C,V> è memorizzata in una struct Pair definita a parte, esterna alla classe Map e da questa usata.
Sono stati implementati:
1. Un metodo per aggiungere una nuova coppia <C,V> nella Map;
2. Un metodo per rimuovere una coppia avente una certa chiave C.;
3. Un metodo che ritorna true se è presente una coppia con una certa chiave;
4. Un metodo per svuotare la struttura dati;
5. L'accesso ai dati tramite iteratore forward in sola lettura. L’iteratore deve
dare accesso ad una struttura Pair che contiene i dati chiave e valore.
L’ordine con cui vengono ritornate le coppie non è importante;
6. Un metodo che ritorna il valore associato ad una certa chiave;
7. Un metodo keys() che ritorna in un std::vector contenente tutte le
chiavi presenti nella Map. E’ possibile usare std::vector solo in questo
metodo della classe.

****Progetto QT****
Il progetto implementa la creazione di un’interfaccia per lo studio di funzioni.
L'interfaccia consente di:

1. Specificare testualmente una funzione polinomiale a coefficienti reali di grado n
2. Tracciare e visualizzare il grafico corrispondente consentendo lo zoom (in/out) e traslazione
3. Dedurre le intersezioni con gli assi e visualizzare i punti come label.

E' stata utilizzata la versione 5.12.11 della libreria Qt.
Il contenuto dell’applicazione è adattivo rispetto alla dimensione della finestra.
