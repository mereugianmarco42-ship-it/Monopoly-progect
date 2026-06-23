//
// Created by mereu on UNO7/ZERO2/2ZERO26.
//

#include "Monopoly.h"

#include <stdlib.h>

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

Giocatore* nuovaPartita(Casella* casella,int* numGiocatori) {
    //NUOVA PARTITA
    int i,o,pedinePrese[SEGNAPOSTO]={ZERO},scelta;

    *numGiocatori=2;   //numero di giocatori presenti nella partita

    Casella* via = casella;
    while (via->Tipologia != VIA) {
        via = via->succ;
    }

    do {
        printf("\n\nquanti giocatori vogliono giocare (da 2 a 4) :");
        scanf(" %d", numGiocatori);
    }while (*numGiocatori < MIN_GIOCATORI || *numGiocatori > MAX_GIOCATORI);

    Giocatore* arrayGiocatori = malloc(sizeof(Giocatore)*(*numGiocatori));

    if (arrayGiocatori == NULL) {
        printf("\n problemi con la memoria allocata");
        exit(EXIT_FAILURE);
    }

    for (i=ZERO; i<*numGiocatori; i++) {    //creo un ciclo che dia la possibilità di inserire le informazioni di ogni giocatore
        arrayGiocatori[i].cfu=STARTCFU;
        printf("\ninserisci il nome del giocatore numero %d : ",i+UNO);
        scanf(" %30[^\n]", arrayGiocatori[i].nome);
        do {
            for (o=ZERO; o<SEGNAPOSTO; o++) {
                switch (o) {
                    case MOUSE:
                        if (!pedinePrese[o]) {
                            printf("\n\nTASTO[UNO] MOUSE");
                        }
                        break;

                    case TASTIERA:
                        if (!pedinePrese[o]) {
                            printf("\n\nTASTO[2] TASTIERA");
                        }
                        break;

                    case CAVO_HDMI:
                        if (!pedinePrese[o]) {
                            printf("\n\nTASTO[3] CAVO_HDMI");
                        }
                        break;

                    case PROIETTORE:
                        if (!pedinePrese[o]) {
                            printf("\n\nTASTO[4] PROIETTORE");
                        }
                        break;

                    default:
                        break;

                }
            }
            printf("\n\nscegli il tuo segnaposto :");
            scanf("%d", &scelta);
        }while (scelta<MIN_SEGNAPOSTO || scelta>MAX_SEGNAPOSTO || pedinePrese[scelta-UNO]);//controllare se la condizione è giusta
        arrayGiocatori[i].pedina=scelta-UNO;
        pedinePrese[scelta-UNO]++;
        arrayGiocatori[i].possedute=NULL;
        arrayGiocatori[i].saltaTurno=false;
        arrayGiocatori[i].posizione=via;
        arrayGiocatori[i].spaziOccupati=ZERO;
        arrayGiocatori[i].turniBatCaverna=ZERO;
    }
    return arrayGiocatori;
}

/**
 * @brief Carica il tabellone di gioco dal file "tabellone.txt".
 *
 * Per ogni casella vengono inizializzati anche i campi variabili della partita:
 * numero di sedie, presenza della scrivania e occupante.
 *
 * @return Puntatore alla prima casella (head) della lista circolare.

 */


Casella* caricaTabellone() {
    int i;
    FILE *f = fopen("tabellone.txt", "r");  //apro il file tabellone per leggerlo
    if (f == NULL) {       //controllo se ci sono stati errori durante l'apertura
        printf("\nErrore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    Casella* head = NULL;
    Casella* tail = NULL;

    for (i=ZERO; i<NUM_CASELLE; i++) {
        Casella* c = malloc(sizeof(Casella));
        if (c == NULL) {
            printf("\nErrore nella creazione dell'array dinamico\n");
            fclose(f);
            exit(EXIT_FAILURE);
        }

        int index;
        fscanf(f, "%d %30s %d %d %d",   //leggo i valori della singola riga e li assegno
               &index,
               c->nome,
               (int*)&c->Tipologia,
               (int*)&c->coloreCasella,
               &c->costoCasella);

        c->numSedie=ZERO;  //setto a null e a ZERO i vari campi che cambieranno durante la partita
        c->occupante = NULL;
        c->scrivania = false;
        c->succ = NULL;
        c->prec = tail;

        if (head == NULL) {
            head = c;   // la prima casella sarà la head
        }else {
            tail->succ = c; //dopo il primo ciclo inposto a c il sucessivo così da incatenare tutto
        }

        tail = c;
    }

    head->prec = tail;  //collego "l'ultima alla prima creando una sorta di cerchio"
    tail->succ = head;

    fclose(f);
    return head;
}

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


Carta* caricaMazzo() {
    int i,o,effect;
    int index;//indice carta
    int copieCarta;//copie della carta
    int totCarte=ZERO,posizone;

    FILE *m = fopen("mazzo.txt", "r");//apertura file
    if (m == NULL) {
        printf("\nErrore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    Carta* supp = NULL;// carta di supporto per collegare le altre carte
    Carta* head = NULL;//la prima carta
    bool cont=true;

    for (i=ZERO; i<NUM_CARTE; i++) {

        fscanf(m, "%d", &index);
        fscanf(m, "%d", &copieCarta);
        for (o=ZERO; o<copieCarta; o++) {
            Carta* card = malloc(sizeof(Carta));
            if (card == NULL) {
                printf("\nErrore nella creazione dell'array dinamico\n");
                fclose(m);
                exit(EXIT_FAILURE);
            }
            totCarte++;

            fscanf(m, " %[^\n]", card->nome);
            fscanf(m, " %[^\n]", card->descrizione);
            fscanf(m, "%d", &card->tipologia);
            fscanf(m, "%d", &card->numEffetti);

            card->effetti = malloc(sizeof(Effetto) * card->numEffetti);

            if (card->effetti == NULL) {
                printf("\nErrore nella creazione dell'array dinamico\n");
                fclose(m);
                exit(EXIT_FAILURE);
            }

            for (effect=ZERO; effect<card->numEffetti; effect++) {
                fscanf(m, "%d %d %d", &card->effetti[effect].azione, &card->effetti[effect].quantita, &card->effetti[effect].casella);
            }

            card->next = NULL;  // imposto il puntatore alla prossima carta a null

            if (supp != NULL) {// se non è la prima carta che inserisco
                supp->next = card;
            }

            supp = card;

            if (cont) {
                head = card;
                cont=false;
            }

        }
    }
    Carta** mazzo = malloc(sizeof(Carta*) * totCarte);
    if (mazzo == NULL) {
        printf("\nErrore nella creazione dell'array dinamico\n");
        exit(EXIT_FAILURE);
    }
    supp=head;

    for (i=ZERO; supp!=NULL; i++) {
        mazzo[i] = supp;
        supp=supp->next;
    }

    for (i=ZERO; i<totCarte; i++) {
        posizone=rand()%totCarte;
        supp=mazzo[posizone];
        mazzo[posizone] = mazzo[i];
        mazzo[i] = supp;
    }

    for (i=ZERO; i<totCarte-UNO; i++) {
        mazzo[i]->next = mazzo[i+UNO];  // collego ogni carta alla successiva nell'ordine mescolato
    }
    mazzo[totCarte-UNO]->next = NULL;  // l'ultima carta non ha successiva
    head = mazzo[ZERO];  // la nuova testa è la prima carta mescolata

    free(mazzo);
    return head;
}

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

void salvaPartita(int tocca_a,Giocatore* arrayGiocatore,int numGiocatori,int turno,Casella* head,Carta* carta,int numCarte) {
    FILE *f = fopen(SAVEGAME, "wb");

    int i,indice,e,nCarte,proprietario = -UNO;

    Carta* c = NULL;
    Casella* casella = head;
    Carta* cart = NULL;

    if (!f) {
        printf("\nErrore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&numGiocatori,sizeof(int),UNO,f);
    fwrite(&numCarte,sizeof(int),UNO,f);

    for (i=ZERO; i<numGiocatori; i++) {
        fwrite(arrayGiocatore[i].nome, sizeof(char), NOME, f);
        fwrite(&arrayGiocatore[i].pedina, sizeof(int), UNO, f);
        fwrite(&arrayGiocatore[i].cfu, sizeof(int), UNO, f);
        fwrite(&arrayGiocatore[i].turniBatCaverna, sizeof(int), UNO, f);
        fwrite(&arrayGiocatore[i].saltaTurno, sizeof(bool), UNO, f);
        fwrite(&arrayGiocatore[i].spaziOccupati, sizeof(int), UNO, f);

        indice = indiceCasella(head,arrayGiocatore[i].posizione);
        fwrite(&indice, sizeof(int), UNO, f);

        int nCartePossedute = nCarteMazzo(arrayGiocatore[i].possedute);
        fwrite(&nCartePossedute, sizeof(int), UNO, f);

        c = arrayGiocatore[i].possedute;

        while (c != NULL) {
            fwrite(c->nome, sizeof(char), NOME, f);
            fwrite(c->descrizione, sizeof(char), DESCRIZIONE, f);
            fwrite(&c->tipologia, sizeof(int), UNO, f);
            fwrite(&c->numEffetti, sizeof(int), UNO, f);
            for (e = ZERO; e < c->numEffetti; e++) {
                fwrite(&c->effetti[e].azione, sizeof(int), UNO, f);
                fwrite(&c->effetti[e].quantita, sizeof(int), UNO, f);
                fwrite(&c->effetti[e].casella, sizeof(int), UNO, f);
            }
            c = c->next;
        }
    }
    for (i=ZERO;i<NUM_CASELLE;i++) {

        fwrite(casella->nome, sizeof(char), NOME, f);
        fwrite(&casella->Tipologia, sizeof(int), UNO, f);
        fwrite(&casella->coloreCasella, sizeof(int), UNO, f);
        fwrite(&casella->costoCasella, sizeof(int), UNO, f);
        fwrite(&casella->numSedie, sizeof(int), UNO, f);
        fwrite(&casella->scrivania, sizeof(bool), UNO, f);
        proprietario = -UNO;
        if (casella->occupante != NULL) {
            for (e = ZERO; e < numGiocatori && proprietario == -UNO; e++) {
                if (strcmp(casella->occupante->nome, arrayGiocatore[e].nome) == ZERO) {
                    proprietario = e;
                }
            }
        }

        fwrite(&proprietario, sizeof(int), UNO, f);

        casella=casella->succ;
    }
    nCarte = nCarteMazzo(carta);
    fwrite(&nCarte, sizeof(int), UNO, f);
    cart = carta;
    while (cart) {
        fwrite(cart->nome, sizeof(char), NOME, f);
        fwrite(cart->descrizione, sizeof(char), DESCRIZIONE, f);
        fwrite(&cart->tipologia, sizeof(int), UNO, f);
        fwrite(&cart->numEffetti, sizeof(int), UNO, f);
        for (i = ZERO; i < cart->numEffetti; i++) {
            fwrite(&cart->effetti[i].azione, sizeof(int), UNO, f);
            fwrite(&cart->effetti[i].quantita, sizeof(int), UNO, f);
            fwrite(&cart->effetti[i].casella, sizeof(int), UNO, f);
        }
        cart=cart->next;
    }

    fwrite(&turno,sizeof(int),UNO,f);
    fwrite(&tocca_a,sizeof(int),UNO,f);

    fclose(f);
}

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


void caricaPartita(int *tocca_a,Giocatore **arrayGiocatore, int *numGiocatori, int *turno,Casella **head, Carta **mazzo,int *numCarte) {

    int i,e,r,*indice=NULL,nCarte,proprietario;
    Carta* c =NULL,* carta;
    Carta* tail_carte = NULL;
    Carta* tail_mazzo = NULL;
    Casella* casella = NULL;
    Casella *prec = NULL;
    FILE *f = fopen(SAVEGAME,"rb");


    if (f == NULL) {
        printf("Errore durante l'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    fread(numGiocatori,sizeof(int),UNO,f);
    fread(numCarte,sizeof(int),UNO,f);

    *arrayGiocatore = (Giocatore*) malloc((*numGiocatori) * sizeof(Giocatore));
    indice = malloc(sizeof(int)*(*numGiocatori));

    for (i=ZERO;i<*numGiocatori;i++) {
        fread((*arrayGiocatore)[i].nome, sizeof(char), NOME, f);
        fread(&(*arrayGiocatore)[i].pedina, sizeof(int), UNO, f);
        fread(&(*arrayGiocatore)[i].cfu, sizeof(int), UNO, f);
        fread(&(*arrayGiocatore)[i].turniBatCaverna, sizeof(int), UNO, f);
        fread(&(*arrayGiocatore)[i].saltaTurno, sizeof(bool), UNO, f);
        fread(&(*arrayGiocatore)[i].spaziOccupati, sizeof(int), UNO, f);

        fread(&indice[i],sizeof(int),UNO,f);

        fread(&nCarte,sizeof(int),UNO,f);
        (*arrayGiocatore)[i].possedute=NULL;
        for (e=ZERO;e<nCarte;e++) {
            c = malloc(sizeof(Carta));

            if (c == NULL) {
                printf("\nErrore nella creazione della carta\n");
                exit(EXIT_FAILURE);
            }

            fread(c->nome, sizeof(char), NOME, f);
            fread(c->descrizione, sizeof(char), DESCRIZIONE, f);
            fread(&c->tipologia, sizeof(int), UNO, f);
            fread(&c->numEffetti, sizeof(int), UNO, f);

            c->effetti = malloc(c->numEffetti * sizeof(Effetto));

            if (c->effetti == NULL) {
                printf("\nErrore nella creazione degli effetti\n");
                exit(EXIT_FAILURE);
            }

            for (r = ZERO; r < c->numEffetti; r++) {
                fread(&c->effetti[r].azione, sizeof(int), UNO, f);
                fread(&c->effetti[r].quantita, sizeof(int), UNO, f);
                fread(&c->effetti[r].casella, sizeof(int), UNO, f);
            }
            c->next = NULL;
            if (tail_carte == NULL) {
                (*arrayGiocatore)[i].possedute = c;
            } else {
                tail_carte->next = c;
            }
            tail_carte = c;
        }
    }
    for (i=ZERO;i<NUM_CASELLE;i++) {
        casella=malloc(sizeof(Casella));

        if (casella == NULL) {
            printf("\nErrore nella creazione della casella\n");
            exit(EXIT_FAILURE);
        }

        fread(casella->nome, sizeof(char), NOME, f);
        fread(&casella->Tipologia, sizeof(int), UNO, f);
        fread(&casella->coloreCasella, sizeof(int), UNO, f);
        fread(&casella->costoCasella, sizeof(int), UNO, f);
        fread(&casella->numSedie, sizeof(int), UNO, f);
        fread(&casella->scrivania, sizeof(bool), UNO, f);

        fread(&proprietario, sizeof(int), UNO, f);

        if (proprietario == -UNO) {
            casella->occupante=NULL;
        }else {
            casella->occupante=&(*arrayGiocatore)[proprietario];
        }

        casella->succ=NULL;
        casella->prec = prec;

        if (prec) {
            prec->succ=casella;
        }else {
            *head=casella;
        }
        prec=casella;
    }
    prec->succ = *head;
    (*head)->prec = prec;

    for (i=ZERO;i<(*numGiocatori);i++) {(*arrayGiocatore)[i].posizione=casellaIndice(*head,indice[i]);}

    fread(&nCarte,sizeof(int),UNO,f);

    *mazzo = NULL;
    tail_mazzo = NULL;
    for (i=ZERO;i<nCarte;i++) {
        carta = malloc(sizeof(Carta));

        if (carta == NULL) {
            printf("\nErrore nella creazione della carta mazzo\n");
            exit(EXIT_FAILURE);
        }

        fread(carta->nome, sizeof(char), NOME, f);
        fread(carta->descrizione, sizeof(char), DESCRIZIONE, f);
        fread(&carta->tipologia, sizeof(int), UNO, f);
        fread(&carta->numEffetti, sizeof(int), UNO, f);

        carta->effetti = malloc(carta->numEffetti * sizeof(Effetto));

        if (carta->effetti == NULL) {
            printf("\nErrore nella creazione degli effetti\n");
            exit(EXIT_FAILURE);
        }

        for (e=ZERO;e<carta->numEffetti;e++) {
            fread(&carta->effetti[e].azione, sizeof(int), UNO, f);
            fread(&carta->effetti[e].quantita, sizeof(int), UNO, f);
            fread(&carta->effetti[e].casella, sizeof(int), UNO, f);
        }

        carta->next = NULL;
        if (tail_mazzo == NULL) {
            *mazzo = carta;
        } else {
            tail_mazzo->next = carta;
        }
        tail_mazzo = carta;

    }
    fread(turno,sizeof(int),UNO,f);
    fread(tocca_a,sizeof(int),UNO,f);
    free(indice);
    fclose(f);
}

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


void scriviLog(Giocatore* giocatore,Carta* carta,int turno,int tiroDadi,int caso) {
    FILE *f = fopen(FILELOG,"a");

    if (f == NULL) {
        printf("\nErrore apertura log\n");
        return;
    }

    switch (caso) {
        case TIRO:
            fprintf(f,"\nTURNO %d: %s tira i dadi e fa %d finendo nella casella %s",turno,giocatore->nome,tiroDadi,giocatore->posizione->nome);
            break;

        case PESCEPESCEPESCE:
            fprintf(f,"\n%s ha pescato %s",giocatore->nome,carta->nome);
            break;

        case VITTORIA:
            fprintf(f,"\n%s ha vinto la partita",giocatore->nome);
            break;

        case ELIMINAZIONE:
            fprintf(f,"\n%s sei stato eliminato ",giocatore->nome);
            break;

        default:
            printf("\n errore! -> LOG");
            break;
    }

    fclose(f);
}

/**
 * @brief Conta il numero di carte presenti in una lista di carte.
 *
 * Scorre la lista concatenata delle carte e restituisce il numero totale
 * di nodi presenti.
 *
 * @param carta Puntatore alla prima carta della lista.
 * @return Numero di carte nella lista.
 */


int nCarteMazzo(Carta* carta) {
    Carta* c = carta;
    int cont=ZERO;
    while (c != NULL) {
        cont++;
        c=c->next;
    }
    return cont;
}


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

int indiceCasella(Casella *head, Casella *target) {
    if (head == NULL || target == NULL){return -UNO;}

    Casella *supp = head;
    int indice = ZERO;

    do {
        if (supp == target) {return indice;}

        supp = supp->succ;
        indice++;

    } while (supp != head);

    return -UNO;


}

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


Casella* casellaIndice(Casella *head, int indice) {
    if (indice == -UNO) return NULL;
    Casella *supp = head;
    int i;
    for (i=ZERO;i<indice;i++) {
        supp = supp->succ;
    }
    return supp;
}
