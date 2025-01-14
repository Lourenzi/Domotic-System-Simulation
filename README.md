## **Domotic-System-Simulation** 
 

### Cosa fa?

Il programma, diviso in varie classi, gestisce l'accensione e lo spegnimento di alcuni **elettrodomestici** allacciati a una rete elettrica. Questa, supporta una potenaza massima assorbibile di 3.5 kW, a cui, va pero' sommato, l'energia derivante da un eventuale produzione fotovoltaica.

> **nota**  
> * Gli elettrodomstici gestiti dal programma sono predefeniti e l'utente non puo' definire nuovi tipi
> * La loro *potenza necessaria* e' un valore costante e dipende da dispositivo a dispositivo
> * Si divino in 2 categorie: *manuali* e *a ciclo prefissato*  
>   1. I **manuali** si possono accendere e spegnere quando si vuole 
>   2. Quelli **a ciclo prefissato**, invece, una volta accesi compiono un ciclo di durata predefinita    


---
---
### Struttura e gerarchia delle classi

Le classi non sono tutte allo stesso livello, la loro gerarchia e' molto importante non solo per il corretto funzionamento del programma ma anche per la comprensio del codice.

Il grafico qui sotto mostra l'organizzazione delle classi

*spazio per il grafico*



---
---

### Cosa fanno i vari file?
---

#### **DataStructure.cpp**  e DataSructure.h
La classe DataStructure contiene i metodi e le struttuture necesarrie per la gestione dei dati durante l'esecuzione del programma.

E' una classe essenziale perche', grazie ai vettori del tipo EntryStructure e EntryAccesi, il programma sa sempre quali sono
i dispositivi accesi e conosce anche le gli orari di accensione e spegnimento dei dispositivi *a ciclo prefissato*.

  ---
#### **Device.h**
In questo file e' definita la classe *Device*, i cui costruttori permettono la creazione di oggetti di questo tipo, passando come argomento nome, id, consumo del dispostivo e per quelli a ciclo prefissato anche anche la durata di accensione.  

E' stata inoltre aggiunta una variabile booleana *is_always_on*, che se vera, in caso venga superata la soglia massima di potenza utilizzabile(3,5kW),
 evita di spegnere elettrodomestici che devono stare sempre accesi come il frigorifero.

---
#### **EntryStructure.h**
Qui sono definite 2 classi: EntryStructure e EntryAccesi.

Entrambi vengono usate in DataStructure per creare dei vettori rispettivamente del tipo EntryStructure e EntryAccesi.

>EntryStructure: contiene tutte le informazioni necessarie per la gestione dei dispositivi(anche accensioni e spegnimenti programmati)

>EntryAccesi: viene utilizzato dal programma per sapere quali sono i dispositivi accesi(comodo per calcolare il consumo totale istantaneo etc...)

---
#### **EventLogger.h**

In questo file e' definita la classe EventLogger, i cui metodi, stampano nei formati corretti, dei messaggi, ogni volta
che un'operazione va a buon fine.

I messaggi vengono stampati sul terminale e su un file *.txt* in cui sono riportati tutti gli eventi accaduti durante
l'esecuzione del programma.

---
#### **Interface.cpp** e Interface.h

*Interface* e' un file chiave del programma che gestisce tutto quello che riguarda l'input dell'utente da terminale.

Grazie alla funzione *parseCommand(string cmd)* chiamata nel main e definita in *Interface.cpp*, infatti, viene analizzata una stringa
e a seconda del contenuto, vengono chiamate le altre funzioni di *Interface*.

---
#### **ListaDevice.h**

In ListaDevice.h vengono creati degli oggetti di tipo *Device* che corrispondo agli elettrodomestici di default su cui si 
basa questo programma e che l'utente puo' gestire da terminale.



---
#### **main.cpp**

Il main contiene un ciclo *while* contenente il metodo *getline(cin, command)*, grazie al quale, nel terminale, possono essere inserite parole dall'utente, 
che vengono poi analizzate da *parseCommand(command)*, che a seconda della stringa passata come parametro, chiama una data funzione.

Il programma termina quando viene inserita la parola chiave *end*.



 ---
 ---
---


