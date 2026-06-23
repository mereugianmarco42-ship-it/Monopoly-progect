//
// Created by mereu on 17/02/2026.
//
//ufficiale progetto
#ifndef MONOPOLY_MEREUGIANMARCO42_SHIP_IT_MONOPOLY_H
#define MONOPOLY_MEREUGIANMARCO42_SHIP_IT_MONOPOLY_H

#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

//batcaverna

#define RIMANI 0
#define PROVA 1
#define CONTROLLA 2

//mensa/aula

#define OCCUPA 1
#define NON_OCCUPA 0
#define METTI_SCRIVANIA 1
#define NON_METTI_SCRIVANIA 0
#define UNA_SEDIA 1
#define ZERO_SEDIE 0
#define DUE_SEDIE 2
#define TRE_SEDIE 3
#define POSIZIONA_UNA_O_PIU_SEDIE 1
#define POSIZIONA_SCRIVANIA 2
#define OCCUPA 1
#define ASTA 0
#define OCCUPA_CON_SEDIE 2
#define OCCUPA_CON_SEDIE_E_SCRIVANIA 3
#define SI 1
#define NO 0
#define ABBANDONA 0
#define CONTINUA 1

//numeri
#define ZERO 0
#define UNO 1
#define CINQUE 5
#define DIECI 10

//MAIN
#define NUOVO_GAME 1
#define CARICA_GAME 2
#define ESCI_GAME 3

#define MIN_SCELTA 1
#define MAX_SCELTA 3

#define VINCITORE 0

#define MIN_GIOCATORI 2
#define MAX_GIOCATORI 4

#define MIN_DADO 1
#define MAX_DADO 6

#define MIN_BUG 1
#define MAX_BUG 3

//SEGNAPOSTO
#define MIN_SEGNAPOSTO 1
#define MAX_SEGNAPOSTO 4

//log

#define TIRO 1
#define PESCEPESCEPESCE 2
#define VITTORIA 3
#define ELIMINAZIONE 4

//gestione turni

#define UGUALI 0

#define VISUALIZZARE_GIOCATORE 2
#define VISUALIZZARE_ALTRI_GIOCATORI 3
#define USCITA 0

#define NOME 31
#define STARTCFU 3000 //quantità di cfu iniziali
#define DESCRIZIONE 255
#define NUM_CASELLE 40
#define NUM_CARTE 33

#define PERCENTUALE_COSTO_SEDIE 80
#define PERCENTUALE_COSTO_SCRIVANIA 120
#define PERCENTUALE 100

#define PROFITTO_AULA 10
#define PROFITTO_SEDIA1 50
#define PROFITTO_SEDIA2 100
#define PROFITTO_SEDIA3 300
#define PROFITTO_SEDIA4 600
#define PROFITTO_SCRIVANIA 900

#define NUM_MENSE 4
#define MAX_SEDIE 4

#define PROFITTO_MENSA1 50
#define PROFITTO_MENSA2 400

#define ROSA 1

#define PAGA_VIA 200
#define GIOVANNA_COSTO 100
#define SEGNAPOSTO 4

#define SAVEGAME "savegame.sav"
#define FILELOG "log.txt"

    typedef enum {NESSUNO, AULA, MENSA, PARCHEGGIO, ABBONAMENTO, VIA, BUG, VAI_BATCAVERNA, BATCAVERNA} TipoCasella;  //tipologia della casella

    typedef enum {NESSUN_COLORE, MARRONE, CELESTE, FUCSIA, ARANCIONE, ROSSO, GIALLO, VERDE, BLU} Colore; //colore casella

    typedef enum {MOUSE, TASTIERA, CAVO_HDMI, PROIETTORE} Segnaposto;    //pedina dei giocatori

    typedef enum {NORMALE, SPECIALE} TipoCarta;

    typedef enum {PAGA_QUALCOSA, PAGA_TUTTO, PRENDI, SALTA_TURNO, NUOVO_TURNO, ESCI, VAI_INDIETRO, VAI_AVANTI, REGALA}Azione;   //nome di ogni azione

    typedef struct Giocatore Giocatore;
    typedef struct Casella Casella;
    typedef struct Carta Carta;
    typedef struct Effetto Effetto;

    struct Giocatore{    //struttura giocatore
        char nome [NOME];   //nome giocatore
        Segnaposto pedina;  //pedina del giocatore
        int cfu;    //cfu del giocatore
        int turniBatCaverna;   //turni che il giocatore deve fare nella bat caverna
        bool saltaTurno;   //se il giocatore deve o no saltare il turno
        int spaziOccupati; //aule/mense occupate dal giocatore
        Casella* posizione; //posizione nel tabellone
        Carta* possedute;   //carte possedute dal giocatore
    };

    struct Casella{    //struttura casella
        char nome [NOME];   //nome casella
        TipoCasella Tipologia;  //tipologia di carta
        Colore coloreCasella;   //colore della casella
        int costoCasella;     //quanto costa occupare la casella
        int numSedie;   //numero di sedie posizionate
        bool scrivania;     //presenza o meno della scrivania
        Giocatore* occupante;   //giocatore possessore della casella
        Casella* succ;
        Casella* prec;  //una lista che punta alla casella precedente e a quella successiva
    };

    struct Effetto{
        Azione azione;  //azione che svolge l'effetto
        int quantita;   //quantità applicata all'effetto
        TipoCasella casella;  //casella legata all'effetto
    };

    struct Carta{    //struttura delle carte
        char nome [NOME];   //nome carte
        char descrizione [DESCRIZIONE]; //descrizione della carta
        TipoCarta tipologia;    //tipologia della carta
        int numEffetti;     //effetti carta
        Effetto* effetti;   //effetti che applica la carta
        Carta* next;    //puntatore alla prossima carta
    };



//ordinamento giocatori Funioni.c primo gruppo di funzioni

/**
 * @brief Risolve eventuali pareggi nei tiri dei dadi.
 *
 * Controlla l’array dei risultati e, quando due giocatori ottengono lo stesso
 * valore, entrambi ritirano il dado finché non ci sono più uguaglianze.
 *
 * @param dadi Array dei risultati dei dadi.
 * @param numGiocatori Numero totale di giocatori.
 * @param arrayGiocatori Array dei giocatori coinvolti.
 */


void uguaglianze(int* dadi ,int numGiocatori,Giocatore* arrayGiocatori);

/**
 * @brief Determina l’ordine di gioco dei giocatori tramite tiro di dado.
 *
 * Ogni giocatore tira un dado, vengono risolti eventuali pareggi e infine
 * l’array dei giocatori viene ordinato in base ai risultati ottenuti.
 *
 * @param numGiocatori Numero totale di giocatori.
 * @param arrayGiocatori Array dei giocatori da ordinare.
 */

void ordineGiocatori(int numGiocatori,Giocatore *arrayGiocatori);

/**
 * @brief Ordina i giocatori in base ai risultati dei dadi.
 *
 * Confronta i valori contenuti nell’array dei dadi e li riordina in modo
 * decrescente, effettuando gli stessi scambi anche nell’array dei giocatori
 * per mantenere la corrispondenza tra giocatore e tiro.
 *
 * @param dadi Array dei risultati dei dadi.
 * @param arrayGiocatori Array dei giocatori da riordinare.
 * @param numGiocatori Numero totale di giocatori.
 */

void scambio(int* dadi, Giocatore *arrayGiocatori,int numGiocatori);

/**
 * @brief Gestisce il turno del giocatore mostrando il menu delle azioni disponibili.
 *
 * Permette al giocatore di tirare i dadi, visualizzare le proprie proprietà,
 * visualizzare quelle degli altri giocatori oppure uscire dal gioco.
 * Restituisce il risultato del tiro dei dadi quando viene scelta l’opzione
 * corrispondente.
 *
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param giocatore Giocatore a cui appartiene il turno.
 * @param casella Puntatore alla prima casella del tabellone.
 * @param numGiocatori Numero totale di giocatori.
 * @param extraTurno Puntatore a flag che indica se il giocatore ottiene un turno extra.
 * @return Somma dei dadi se il giocatore sceglie di tirare, altrimenti non ritorna.
 */

int gestioneTurni(Giocatore* arrayGiocatori,Giocatore* giocatore, Casella* casella,int numGiocatori,bool* extraTurno);

/**
 * @brief Esegue il tiro dei dadi e verifica se il giocatore ottiene un turno extra.
 *
 * Genera due valori casuali tra MIN_DADO e MAX_DADO.
 * Se i due dadi sono uguali, imposta il flag extraTurno a true.
 *
 * @param extraTurno Puntatore al flag che indica se il giocatore ottiene un turno aggiuntivo.
 * @return Somma dei due dadi tirati.
 */

int tasto1(bool* extraTurno);

/**
 * @brief Mostra le caselle occupate e le carte possedute dal giocatore.
 *
 * Scorre l’intero tabellone per individuare le caselle appartenenti al giocatore
 * e stampa l’elenco. Successivamente elenca tutte le carte presenti nella sua
 * lista delle carte possedute.
 *
 * @param casella Puntatore alla prima casella del tabellone.
 * @param giocatore Giocatore di cui visualizzare proprietà e carte.
 */


void tasto2(Casella* casella,Giocatore* giocatore);

/**
 * @brief Mostra le caselle occupate e le carte possedute dagli altri giocatori.
 *
 * Per ogni giocatore diverso da quello corrente, scorre l’intero tabellone
 * per individuare le caselle da lui occupate e stampa l’elenco.
 * Successivamente mostra anche tutte le carte possedute dagli altri giocatori.
 *
 * @param arrayGiocatore Array di tutti i giocatori.
 * @param giocatore Giocatore corrente (da escludere dalla visualizzazione).
 * @param casella Puntatore alla prima casella del tabellone.
 * @param numGiocatori Numero totale di giocatori.
 */


void tasto3(Giocatore* arrayGiocatore,Giocatore* giocatore, Casella* casella,int numGiocatori);

/**
 * @brief Applica l’effetto della carta BUG pescata dal giocatore.
 *
 * In base al tipo di carta, esegue l’azione corrispondente, che può includere:
 * - movimento del giocatore avanti o indietro;
 * - pagamento o guadagno di CFU;
 * - spostamento in una casella specifica;
 * - ottenere un turno extra;
 * - ottenere una carta speciale (es. uscita dalla Batcaverna);
 * - obbligare altri giocatori a pagare o ricevere CFU.
 *
 * Se la carta non viene trattenuta dal giocatore, viene reinserita in fondo al mazzo.
 *
 * @param carta Carta BUG da applicare.
 * @param giocatore Giocatore che ha pescato la carta.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 * @param casella Puntatore alla prima casella del tabellone.
 * @param extra Puntatore al flag che indica se il giocatore ottiene un turno extra.
 * @param numCarte NumCarte numero di carte da pescare
 */

void effettocarta(Carta* carta,Giocatore* giocatore,Giocatore* arrayGiocatori,Casella*casella,int numGiocatori,bool* extra, int numCarte);

/**
 * @brief Gestisce il pagamento collettivo quando una carta BUG richiede che tutti i giocatori paghino.
 *
 * Ogni giocatore (tranne chi ha pescato la carta) paga una quota fissa di CFU
 * al giocatore indicato.
 * Se un giocatore non ha abbastanza CFU per pagare, viene eliminato dal gioco.
 *
 * @param giocatore Giocatore che riceve i CFU dagli altri.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 * @param carta Carta pescata.
 * @param casella Casella per vedere aule e mense presenti
 */

void paga_Tutto(Carta* carta,Giocatore* giocatore,Casella* casella,Giocatore* arrayGiocatori,int numGiocatori);
//gestione effetto REGALA

/**
 * @brief Applica l’effetto della casella su cui il giocatore è finito.
 *
 * In base alla tipologia della casella (AULA, MENSA, PARCHEGGIO, BUG,
 * ABBONAMENTO, BATCAVERNA, ecc.), esegue l’azione corrispondente:
 * pagamento, occupazione, pesca di carte BUG, spostamenti forzati,
 * gestione della Batcaverna o eventi speciali.
 *
 * @param casella Casella su cui il giocatore è arrivato.
 * @param giocatore Giocatore coinvolto nell’evento.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 * @param carta Puntatore al mazzo delle carte BUG.
 * @param extra Puntatore al flag che indica se il giocatore ottiene un turno extra.
 * @param numCarte Numero totale di carte nel mazzo BUG.
 */

void effettoCasella(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta** carta,bool* extra,int numCarte);

/**
 * @brief Gestisce l’effetto della casella di tipo MENSA.
 *
 * Se la mensa è libera, il giocatore può occuparla pagando il costo oppure
 * lasciarla andare all’asta.
 * Se è occupata da un altro giocatore, viene calcolato e pagato il pedaggio,
 * che varia in base al numero totale di mense possedute dall’occupante.
 * Se il giocatore non ha abbastanza CFU, può essere eliminato.
 *
 * @param casella Casella MENSA su cui il giocatore è arrivato.
 * @param giocatore Giocatore coinvolto nell’evento.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 * @param carta Puntatore al mazzo delle carte BUG.
 */

void mensa(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta* carta);

/**
 * @brief Gestisce tutte le azioni disponibili quando un giocatore si trova in Batcaverna.
 *
 * Se il giocatore deve ancora scontare turni, può scegliere se:
 * - rimanere in Batcaverna (riducendo i turni rimanenti),
 * - tentare l’uscita tirando due dadi uguali,
 * - usare una carta BUG che permette di uscire,
 * - provare ad acquistare tale carta da un altro giocatore.
 *
 * Se il giocatore esce, eventuali carte usate vengono reinserite in fondo al mazzo.
 *
 * @param giocatore Giocatore attualmente in Batcaverna.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param carta Puntatore al mazzo delle carte BUG.
 * @param numGiocatori Numero totale di giocatori.
 */

void batcaverna(Giocatore* giocatore,Giocatore *arrayGiocatori,Carta** carta,int numGiocatori);
//effetto vasi in bst caverna

/**
 * @brief Gestisce l’effetto della casella di tipo AULA.
 *
 * Se l’aula è del giocatore, permette di aggiungere sedie o acquistare la
 * scrivania, ma solo se possiede tutte le aule dello stesso colore.
 * Se l’aula è libera, il giocatore può occuparla, eventualmente acquistando
 * sedie o scrivania in base ai CFU disponibili; in caso contrario va all’asta.
 * Se l’aula appartiene a un altro giocatore, viene calcolato e pagato il
 * pedaggio in base al numero di sedie o alla presenza della scrivania.
 *
 * @param casella Aula su cui il giocatore è arrivato.
 * @param giocatore Giocatore coinvolto nell’evento.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 * @param carta Puntatore al mazzo delle carte BUG.
 */

void aula(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta* carta);

/**
 * @brief Gestisce il pagamento del pedaggio quando un giocatore entra in un’aula occupata.
 *
 * Calcola il costo da pagare in base allo stato dell’aula:
 * - se è presente la scrivania, applica il pedaggio massimo;
 * - altrimenti il pedaggio varia in base al numero di sedie presenti.
 *
 * Dopo il pagamento verifica se il giocatore deve essere eliminato per mancanza di CFU.
 *
 * @param casella Aula occupata da un altro giocatore.
 * @param giocatore Giocatore che deve pagare il pedaggio.
 * @param carta Puntatore al mazzo delle carte BUG.
 * @param numGiocatori Numero totale di giocatori.
 * @param arrayGiocatori Array di tutti i giocatori.
 */

void pagamento_Pedaggio(Casella* casella,Giocatore* giocatore,Carta* carta,int numGiocatori,Giocatore* arrayGiocatori);

/**
 * @brief Permette al giocatore di acquistare sedie e/o la scrivania per un’aula.
 *
 * Mostra le opzioni disponibili in base alle sedie mancanti e ai CFU del giocatore.
 * Il giocatore può:
 * - acquistare da 1 a tutte le sedie mancanti;
 * - acquistare direttamente la scrivania (che azzera le sedie);
 * - non effettuare alcuna azione.
 *
 * @param casella Aula su cui effettuare i miglioramenti.
 * @param giocatore Giocatore che effettua l’acquisto.
 */

void compra_Sedie_Scrivania(Casella*casella,Giocatore* giocatore);

/**
 * @brief Permette al giocatore di acquistare una o più sedie per un’aula.
 *
 * Mostra quante sedie mancano per completare l’aula e consente al giocatore
 * di comprarne da 1 al massimo consentito, purché abbia abbastanza CFU.
 * In alternativa, può scegliere di non effettuare alcun acquisto.
 *
 * @param casella Aula in cui aggiungere le sedie.
 * @param giocatore Giocatore che effettua l’acquisto.
 */

void compra_Sedie(Casella*casella,Giocatore* giocatore);

/**
 * @brief Permette al giocatore di occupare un’aula libera.
 *
 * Il giocatore può scegliere se acquistare l’aula pagando il costo indicato
 * oppure lasciarla andare all’asta.
 * Se non ha abbastanza CFU per occuparla, l’aula viene automaticamente messa all’asta.
 *
 * @param casella Aula da occupare.
 * @param giocatore Giocatore che tenta l’occupazione.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 */

void occupare_Aula(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori);

/**
 * @brief Permette al giocatore di occupare un’aula libera e acquistare almeno una sedia.
 *
 * Il giocatore deve decidere se:
 * - occupare l’aula pagando il costo base;
 * - acquistare almeno una sedia (obbligatorio in questa variante);
 * - rinunciare, lasciando l’aula all’asta.
 *
 * @param casella Aula da occupare e migliorare.
 * @param giocatore Giocatore che effettua l’acquisto.
 * @param arrayGiocatori ArrayGiocatori i giocatori .
 * @param numGiocatori NumGiocatori totali.
 */

void occupare_Aula_E_Almeno_Una_Sedia(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori);

/**
 * @brief Permette al giocatore di occupare un’aula libera acquistando direttamente la scrivania.
 *
 * Il giocatore può scegliere se:
 * - occupare l’aula pagando il costo base;
 * - acquistare immediatamente la scrivania (che azzera le sedie);
 * - rinunciare, lasciando l’aula all’asta.
 *
 * @param casella Aula da occupare e migliorare.
 * @param giocatore Giocatore che effettua l’acquisto.
 * @param arrayGiocatori ArrayGiocatori i giocatori .
 * @param numGiocatori NumGiocatori totali.
 */

void occupare_Aula_Scrivania(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori);

/**
 * @brief Gestisce l’asta per un’aula o una mensa non acquistata dal giocatore che vi è arrivato.
 *
 * Tutti i giocatori partecipano all’asta a turno, effettuando rilanci finché
 * rimane un solo offerente.
 * Vengono verificati i CFU disponibili per ogni rilancio e chi non può più
 * competere viene escluso automaticamente.
 * Il vincitore paga il prezzo finale e diventa proprietario della casella.
 *
 * @param casella Casella (AULA o MENSA) messa all’asta.
 * @param giocatore Giocatore che lancia l'asta.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 */

void astaAulaMensa(Giocatore* arrayGiocatori, Giocatore* giocatore, Casella* casella,int numGiocatori);

/**
 * @brief Inizializza una nuova partita creando i giocatori e impostando le loro proprietà iniziali.
 *
 * La funzione chiede all'utente quanti giocatori parteciperanno (da 2 a 4), alloca dinamicamente
 * l'array dei giocatori, imposta i valori iniziali (CFU, posizione, pedina, carte possedute, ecc.)
 * e assegna a ciascun giocatore la casella di partenza corrispondente al TipoCasella VIA.
 *
 * @param casella Puntatore a una casella del tabellone, utilizzato per cercare la casella VIA.
 * @param numGiocatori Puntatore a intero in cui verrà salvato il numero di giocatori scelto.
 *
 * @return Puntatore all'array dinamico di Giocatore inizializzato.
 *
 */

Giocatore* nuovaPartita(Casella* casella,int* numGiocatori);

/**
 * @brief Carica il tabellone di gioco dal file "tabellone.txt".
 *
 * Per ogni casella vengono inizializzati anche i campi variabili della partita:
 * numero di sedie, presenza della scrivania e occupante.
 *
 * @return Puntatore alla prima casella (head) della lista circolare.

 */

Casella* caricaTabellone();

/**
 * @brief Carica il mazzo di carte BUG dal file "mazzo.txt" e lo mescola.
 *
 *
 * Ogni carta viene allocata dinamicamente e inserita in una lista singolarmente
 * concatenata. Una volta caricate tutte le carte, il mazzo viene mescolato tramite
 * un array temporaneo di puntatori, e la lista viene ricostruita nell’ordine
 * mescolato.
 *
 * @return Puntatore alla prima carta del mazzo mescolato.
 */

Carta* caricaMazzo();
//svago
int opzioniplsssss(int pls);

/**
 * @brief Elimina un giocatore dal gioco quando non ha più CFU sufficienti.
 *
 * Imposta il giocatore come eliminato e libera tutte le sue proprietà:
 * - aule e mense tornano libere e senza miglioramenti;
 * - eventuali carte BUG vengono restituite al mazzo;
 * - il giocatore non partecipa più ai turni successivi.
 *
 * @param giocatore Giocatore da eliminare.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param casella Casella tabellone per visitare le aule e mense occupate dal giocatore.
 * @param numGiocatori Numero totale di giocatori.
 * @param carta Puntatore al mazzo delle carte BUG.
 */

void eliminazione(Giocatore* giocatore,Giocatore* arrayGiocatori,Casella* casella,Carta* carta,int numGiocatori);

/**
 * @brief Scrive una riga nel file di log in base all'evento di gioco.
 *
 * In base al valore di @p caso, registra nel file log.txt il tiro dei dadi,
 * la pesca di una carta, la vittoria o l'eliminazione di un giocatore.
 *
 * @param giocatore Giocatore coinvolto nell'evento.
 * @param carta Carta pescata, se applicabile.
 * @param turno Numero del turno corrente.
 * @param tiroDadi Risultato del lancio dei dadi.
 * @param caso Tipo di evento da registrare nel log.
 */


void scriviLog(Giocatore* giocatore,Carta* carta,int turno,int tiroDadi,int caso);

/**
 * @brief Carica una partita salvata dal file binario SAVEGAME.
 *
 * La funzione ricostruisce l'intero stato della partita leggendo dal file:
 * numero di giocatori, loro dati, carte possedute, tabellone aggiornato,
 * mazzo delle carte BUG, turno corrente e indice del giocatore in turno.
 * Ricrea inoltre la lista circolare delle caselle e assegna a ogni giocatore
 * la corretta posizione tramite l'indice salvato.
 *
 * @param tocca_a Puntatore all'indice del giocatore a cui spetta il turno.
 * @param arrayGiocatore Puntatore all'array dinamico dei giocatori da allocare.
 * @param numGiocatori Puntatore al numero totale di giocatori.
 * @param turno Puntatore al numero del turno corrente.
 * @param head Puntatore alla testa della lista circolare del tabellone.
 * @param mazzo Puntatore alla testa del mazzo delle carte BUG.
 * @param numCarte Puntatore al numero totale di carte nel mazzo.
 */


void caricaPartita(int *tocca_a,Giocatore **arrayGiocatore, int *numGiocatori, int *turno,Casella **head, Carta **mazzo,int *numCarte);

/**
 * @brief Salva lo stato completo della partita nel file binario SAVEGAME.
 *
 * La funzione scrive su file tutti i dati necessari per ripristinare la partita:
 * giocatori, loro proprietà, posizione, carte possedute, tabellone aggiornato,
 * mazzo delle carte BUG, turno corrente e indice del giocatore in turno.
 *
 * @param tocca_a Indice del giocatore a cui spetta il turno successivo.
 * @param arrayGiocatore Array dei giocatori della partita.
 * @param numGiocatori Numero totale di giocatori.
 * @param turno Numero del turno corrente.
 * @param head Puntatore alla prima casella del tabellone.
 * @param carta Puntatore alla prima carta del mazzo BUG.
 * @param numCarte Numero totale di carte nel mazzo.
 */

void salvaPartita(int tocca_a,Giocatore* arrayGiocatore,int numGiocatori,int turno,Casella* head,Carta* carta,int numCarte);

/**
 * @brief Restituisce l'indice di una casella all'interno del tabellone.
 *
 * Scorre la lista circolare delle caselle partendo da head e restituisce
 * l'indice della casella target. Se la casella non viene trovata, restituisce -1.
 *
 * @param head Puntatore alla prima casella del tabellone.
 * @param target Casella di cui cercare l'indice.
 * @return Indice della casella oppure -1 se non trovata.
 */

int indiceCasella(Casella *head, Casella *target);

/**
 * @brief Restituisce la casella corrispondente a un dato indice del tabellone.
 *
 * Scorre la lista circolare delle caselle partendo da head e avanza
 * di un numero di passi pari all'indice fornito.
 *
 * @param head Puntatore alla prima casella del tabellone.
 * @param indice Indice della casella da raggiungere.
 * @return Puntatore alla casella corrispondente oppure NULL se indice = -1.
 */


Casella* casellaIndice(Casella *head, int indice);

/**
 * @brief Conta il numero di carte presenti in una lista di carte.
 *
 * Scorre la lista concatenata delle carte e restituisce il numero totale
 * di nodi presenti.
 *
 * @param carta Puntatore alla prima carta della lista.
 * @return Numero di carte nella lista.
 */


int nCarteMazzo(Carta* carta);

/**
 * @brief Gestisce l’asta di una carta BUG quando il giocatore che l’ha pescata decide di non usarla.
 *
 * Tutti i giocatori partecipano all’asta effettuando rilanci finché rimane
 * un solo offerente.
 * Ogni rilancio viene verificato rispetto ai CFU disponibili; chi non può
 * più competere viene escluso automaticamente.
 *
 * @param giocatore Giocatore che mette in asta.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 */

void astaCarte(Giocatore* giocatore, Giocatore* arrayGiocatori, int numGiocatori);
#endif //MONOPOLY_MEREUGIANMARCO42_SHIP_IT_MONOPOLY_H