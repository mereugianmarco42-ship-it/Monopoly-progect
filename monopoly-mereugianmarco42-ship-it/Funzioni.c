//
// Created by mereu on 21/02/2026.
//

#include "Monopoly.h"

//____________________________________  ORIDNAMENTO GIOCATORI

/**
 * @brief Determina l’ordine di gioco dei giocatori tramite tiro di dado.
 *
 * Ogni giocatore tira un dado, vengono risolti eventuali pareggi e infine
 * l’array dei giocatori viene ordinato in base ai risultati ottenuti.
 *
 * @param numGiocatori Numero totale di giocatori.
 * @param arrayGiocatori Array dei giocatori da ordinare.
 */


void ordineGiocatori(int numGiocatori,Giocatore *arrayGiocatori) {//funzione per stabilire l'ordine dei giocatori durante la partita inserisci il numero di giocatori e un array

    int i;

    int *dadi = NULL;
    dadi = (int*) malloc(numGiocatori * sizeof(int));//creazione arrey che conterrà i dadi lanciati
    if (dadi == NULL) {
        printf("\nErrore durante l'assegnamento dello spazio\n");
        return;
    }

    for (i = ZERO; i < numGiocatori; i++) {// tiro dei dadi
        dadi[i] = (rand() % MAX_DADO) + MIN_DADO;
        printf("\n\n %s tira il dado e ottiene %d", arrayGiocatori[i].nome, dadi[i]);

    }

    uguaglianze(dadi,numGiocatori,arrayGiocatori);

    scambio(dadi,arrayGiocatori,numGiocatori);

    printf("\n--- ORDINE DI GIOCO ---\n");
    for (i = ZERO; i < numGiocatori; i++) {
        printf("%d) %s (dado: %d)\n", i + UNO, arrayGiocatori[i].nome, dadi[i]);
    }


    free(dadi);
}

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


void uguaglianze(int* dadi ,int numGiocatori,Giocatore* arrayGiocatori) {   //controllo di uguaglianze nel tiro dei dadi
    bool pareggio = true;//pareggio controlla se durante il ciclo ci sono state uguaglianze e se ci sono state allora dovrà ripetere ancora il ciclo per assicurarsi che non c'è ne siano altre

    while (pareggio) {
        pareggio = false;

        for (int i = ZERO; i < numGiocatori; i++) {//controlla per ogni dado se gli altri sono uguali
            for (int j = i + UNO; j < numGiocatori; j++) {

                if (dadi[i] == dadi[j]) {
                    pareggio = true;

                    printf("\nPareggio tra %s e %s! Ritirano il dado...\n",arrayGiocatori[i].nome, arrayGiocatori[j].nome);


                    dadi[i] = (rand() % MAX_DADO) + MIN_DADO;
                    dadi[j] = (rand() % MAX_DADO) + MIN_DADO;

                }
            }
        }
    }

}

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

void scambio(int* dadi, Giocatore *arrayGiocatori,int numGiocatori) {
    int supint,i,o;
    Giocatore supGiocatore;

    for (i=ZERO;i<numGiocatori;i++) {
        for (o=i+UNO;o<numGiocatori;o++) {
            if (dadi[i] < dadi[o]) {
                supint = dadi[i];
                dadi[i] = dadi[o];
                dadi[o] = supint;

                supGiocatore = arrayGiocatori[i];
                arrayGiocatori[i] = arrayGiocatori[o];
                arrayGiocatori[o] = supGiocatore;
            }
        }
    }


}

//____________________________________   GESTIONE TURNI

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


int gestioneTurni(Giocatore* arrayGiocatori,Giocatore* giocatore, Casella* casella,int numGiocatori,bool* extraTurno) {
    int scelta; //scelta di cosa fare nel turno
    printf("\n\n_______________________________________\n");
    printf("\nIl turno e' di %s e ha %d CFU",giocatore->nome,giocatore->cfu);
    printf("\n_______________________________________\n");

    do{
        printf("\n\n_______MENU SCELTE DISPONIBILI_______\n[TASTO 1] tirare i dadi\n[TASTO 2] visualizzare le AULE/MENSE occupate dal giocatore e le eventuali carte in suo possesso\n[TASTO 3] visualizzare le AULE/MENSE occupate dagli altri giocatori e le eventuali carte in suo possesso\n[TASTO 0] chiudere la partita\n:");
        scanf("%d",&scelta);

        switch (scelta) {
            case TIRO:
                return tasto1(extraTurno);

            case VISUALIZZARE_GIOCATORE:
                tasto2(casella,giocatore);
                break;

            case VISUALIZZARE_ALTRI_GIOCATORI:
                tasto3(arrayGiocatori,giocatore,casella,numGiocatori);
                break;

            case ESCI:
                printf("\n Uscita dal gioco");
                exit(EXIT_FAILURE);


            default:
                printf("\n ERRORE L'OPZIONE NON ESISTE");
                break;
        }
    }while (UNO);
}

/**
 * @brief Esegue il tiro dei dadi e verifica se il giocatore ottiene un turno extra.
 *
 * Genera due valori casuali tra MIN_DADO e MAX_DADO.
 * Se i due dadi sono uguali, imposta il flag extraTurno a true.
 *
 * @param extraTurno Puntatore al flag che indica se il giocatore ottiene un turno aggiuntivo.
 * @return Somma dei due dadi tirati.
 */

int tasto1(bool* extraTurno) {
    int dado1,dado2;

    dado1 = (rand() % MAX_DADO) + MIN_DADO;
    dado2 = (rand() % MAX_DADO) + MIN_DADO;

    if (dado1==dado2) {
        *extraTurno=true;
        printf("\nhai fatto doppio di %d, hai un turno extra!!!!\n",dado1);
    }else {
        *extraTurno=false;
    }
        return dado1+dado2;

}

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

void tasto2(Casella* casella,Giocatore* giocatore) {
    int i;
    Carta* carta_sup=giocatore->possedute;
    Casella* casella_sup=casella;

    printf("\nIl giocatore %s ha occupato le caselle: ",giocatore->nome);
    for (i = ZERO; i < NUM_CASELLE; i++) {//faccio il controllo per tutte e 40 le caselle

        if (casella_sup->occupante!=NULL) {
            if (strcmp(casella_sup->occupante->nome,giocatore->nome)==UGUALI) {  //se l'occupante della casella è il giocatore
                printf("\n- %d) %s",i,casella_sup->nome);    //allora stampa il nome della casella
            }
        }
        casella_sup = casella_sup->succ;    //e al prossimo ciclo controllerò la successiva
    }
    printf("\nposside le carte");
    while (carta_sup!=NULL){//il ciclo inizia se il giocatore possiede delle carte

        printf("\n- %s", carta_sup->nome);   //stampo il nome della carta posseduta

        carta_sup =  carta_sup->next;
    }

}

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

void tasto3(Giocatore* arrayGiocatore,Giocatore* giocatore, Casella* casella,int numGiocatori) {
    int i,o;
    Carta* carta_sup=NULL;
    Casella* casella_sup;
    printf("\nGli altri giocatori hanno occupato le caselle\n");
    for (o=ZERO;o<numGiocatori;o++) {
        casella_sup=casella;
        if (strcmp(arrayGiocatore[o].nome,giocatore->nome)!=UGUALI) {// se il giocatore non è il giocatore che ha scelto allora stampo le aule e le mense

            printf("\n---> %s:",arrayGiocatore[o].nome);

            for (i = ZERO; i < NUM_CASELLE; i++) {//faccio il controllo per tutte e 40 le caselle
                if (casella_sup->occupante!=NULL) {
                    if (strcmp(casella_sup->occupante->nome,arrayGiocatore[o].nome)==UGUALI) {  //se l'occupante della casella è il giocatore che vogliamo visualizzare
                        printf("\n- %d) %s",i, casella_sup->nome);    //allora stampa il nome della casella
                    }
                }
                casella_sup = casella_sup->succ;    //e al prossimo ciclo controllerò la successiva
            }

        }

    }

    printf("\n");

    for (i = ZERO; i < numGiocatori; i++) {

        carta_sup=arrayGiocatore[i].possedute;

        if (strcmp(arrayGiocatore[i].nome,giocatore->nome)!=UGUALI) {
            printf("\n---> il giocatore %s posside le carte: ",arrayGiocatore[i].nome);

            while (carta_sup!=NULL){

                printf("\n- %s",carta_sup->nome);

                carta_sup = carta_sup->next;
            }
        }
    }
}

//____________________________________GESTIONE EFFETTI CASELLE

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


void effettoCasella(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta** carta,bool* extra,int numCarte) {
    Casella* casella_sup=casella;
    int rosa;
    int i=ZERO;
    switch (casella_sup->Tipologia) {
        case AULA:
            aula(casella_sup, giocatore,arrayGiocatori,numGiocatori,*carta);
            break;

        case MENSA:
            mensa(casella_sup, giocatore,arrayGiocatori,numGiocatori,*carta);
            break;

        case PARCHEGGIO:
            printf("\nSei finito nel parcheggio sei tranquillo");
            if (rand()%DIECI==CINQUE) {
                printf("......\n.........\n.........\nfinche' un signore si avvicina e ti chiede con fare allegro se vuoi una rosa");
                printf("\nvuoi comprare la rosa per 1 cfu(0 no): ");
                scanf("%d",&rosa);
                if (rosa!=ZERO) {
                    giocatore->cfu-=ROSA;
                    printf("\nGRAZIE AMICO BUONA GIORNATA");
                    eliminazione(giocatore,arrayGiocatori,casella_sup,*carta,numGiocatori);
                }
            }
            break;

        case ABBONAMENTO:
            printf("\nAbbonamento CTM paghi %d cfu",casella_sup->costoCasella);
            giocatore->cfu -= casella_sup->costoCasella;
            eliminazione(giocatore,arrayGiocatori,casella_sup,*carta,numGiocatori);
            break;

        case VIA:
            printf("\nSei finito sul via:");
            break;

        case BUG:

            while (i<numCarte) {// scorro tutte le carte da pescare
                if (*carta == NULL) {
                    printf("\nIl mazzo e' esaurito, non ci sono piu' carte da pescare.");
                    break;
                }
                Carta *primaCarta = *carta; //stacco la carta da prende dal mazzo
                *carta = (*carta)->next;
                primaCarta->next = NULL;
                effettocarta(primaCarta, giocatore, arrayGiocatori, casella_sup, numGiocatori, extra, numCarte);  //applico l'effetto

                // Se l'effetto NON e' ESCI, rimetti la carta in fondo al mazzo
                if (primaCarta->tipologia == NORMALE && primaCarta->effetti->azione != ESCI) {
                    // cerca la fine del mazzo e reinserisce la carta
                    if (*carta == NULL) {
                        *carta = primaCarta;
                    } else {
                        Carta *fine = *carta;
                        while (fine->next != NULL) {
                            fine = fine->next;
                        }
                        fine->next = primaCarta;
                        primaCarta->next = NULL;
                    }
                }
                i++;
            }

            break;

        case VAI_BATCAVERNA:
            printf("\n vai in batcaverna ");
            while (giocatore->posizione->Tipologia!=BATCAVERNA) {
                giocatore->posizione=giocatore->posizione->succ;
            }
            giocatore->turniBatCaverna=3;
            break;

        case BATCAVERNA:
            batcaverna(giocatore,arrayGiocatori,carta,numGiocatori);
            break;

        default:
            break;
    }
}

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

void batcaverna(Giocatore* giocatore,Giocatore *arrayGiocatori,Carta** carta,int numGiocatori) {
    int scelta,pls=ZERO,dado1,dado2;
    Carta *inserimentoMazzo=*carta;
    Carta* prec = giocatore->possedute;
    Carta* supporto = giocatore->possedute;
    if (giocatore->turniBatCaverna>ZERO) {//controlla se ha turni da scontare nella batcaverna se ne ha allora si trova dentro oppure è nella sezione di transito
        do {
            printf("\n\n%s scegli tra \nTASTO[0] vuoi rimanere nella batcaverna al fresco \nTASTO[1] prova a tirare i dadi e se escono uguali esci immediatamente\nTASTO[2] se possiedi una carta BUG che ti permetta di uscire dalla batcaverna usala, altrimenti prova a comprarla da un'altro giocatore\nScelta: ",giocatore->nome);
            scanf(" %d", &scelta);
            switch (scelta) {
                case RIMANI:
                    giocatore->turniBatCaverna--;
                    break;
                case PROVA:
                    dado1 = rand()%MAX_DADO+MIN_DADO;
                    dado2 = rand()%MAX_DADO+MIN_DADO;//lancia i dadi e se sono uguali esce altrimenti un turno in meno

                    if (dado1==dado2) {
                        printf("\nPORK CHE FORTUNA SEI USCITO DALLA BATCAVERNA");
                        giocatore->turniBatCaverna=ZERO;
                    }else {
                        printf("\nMi dispiace non sei stato fortunato");
                        giocatore->turniBatCaverna--;
                    }
                    scelta=ZERO;
                    break;

                case CONTROLLA:
                    while (supporto!=NULL && giocatore->turniBatCaverna>ZERO) {//se ha carte allora controlla le carte possonon farlo uscire
                        if (supporto->effetti->azione==ESCI) {
                            printf("\nHai usato la carta %s",supporto->nome);
                            giocatore->turniBatCaverna=ZERO;
                        }else {
                            supporto=supporto->next;
                        }
                    }
                    if (giocatore->turniBatCaverna>ZERO) {// se tra le carte c'era una carta che ti permette di uscire  allora avrai i turni a 0
                        printf("\nmi dispiace non hai carte che ti permettono di uscire ora se vuoi puoi provare a comprarla");

                        astaCarte(giocatore, arrayGiocatori, numGiocatori);
                        scelta=UNO;//imposto scelta a 1 così che potrà scegliere di nuovo se tirare i dadi o non fare nulla
                    }else {
                        if (giocatore->possedute->effetti->azione==ESCI) {//se la carta da usare è la prima
                            giocatore->possedute = supporto->next;  //dico che il mazzo posseduto dal giocatore iniziala da quella dopo
                            supporto->next=NULL;    //e poi isolo la carta che devo usare
                        }else {
                            while (prec->next != NULL) {
                                if (prec->next->effetti->azione==ESCI) {
                                    prec->next=supporto->next;//collego la carta precedente a quella che ho usato alla carta successiva di quella che ho usato togliendolo effettivamente da l mazzo del giocatore
                                    supporto->next=NULL;// e la isolo
                                }else {
                                    prec=prec->next;
                                }
                            }
                        }

                        while (inserimentoMazzo->next!=NULL) {inserimentoMazzo=inserimentoMazzo->next;}

                        inserimentoMazzo->next=supporto;//inserisco la carta alla fine del mazzo e puntando già a NULL non ci devo ripensare

                    }

                    break;

                default:
                    pls=opzioniplsssss(pls);
                    scelta=UNO;
                    break;
            }
        }while (scelta);
    }else {
        printf("\nsei nel transito della batcaverna");
    }
}

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

void mensa(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta* carta) {
    int scelta=ZERO,i,pls=ZERO;
    Casella* casella_sup=casella;
    if (casella->occupante==NULL) {
        printf("\n(casella libera)\n");
        if (giocatore->cfu<casella->costoCasella) {
            printf("\nNon hai abbastanza soldi per prenderela la casella va direttamente all'asta");
            astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
        }else {
            do {
                printf("\nTASTO[1] occupa la mensa pagando %d\nTASTO[0] non fare nulla e lascia la mensa all'asta\n:",casella->costoCasella);
                scanf(" %d",&scelta);
                switch (scelta) {
                    case OCCUPA:
                        casella->occupante=giocatore;
                        giocatore->cfu-=casella->costoCasella;
                        scelta=ZERO;
                        break;

                    case NON_OCCUPA:
                        astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                        break;

                    default:
                        pls=opzioniplsssss(pls);
                        scelta=UNO;
                        break;
                }
            }while (scelta);
        }
    }else {
        if (casella->occupante!=giocatore) {
            for (i = ZERO; i < NUM_CASELLE; i++) {// controllo tutte le mense e se il giocatore che la occupa ha tutte le mense paghi un sacco
                if (casella->Tipologia==casella_sup->Tipologia && casella_sup->occupante==casella->occupante) {scelta++;}
                casella_sup = casella_sup->succ;
            }
            if (scelta<NUM_MENSE) {
                printf("\n sei finito nella mensa di %s e devi pagare %d",casella->occupante->nome,(casella->costoCasella*PROFITTO_MENSA1)/PERCENTUALE);
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_MENSA1)/PERCENTUALE;
                giocatore->cfu-=(casella->costoCasella*PROFITTO_MENSA1)/PERCENTUALE;
                eliminazione(giocatore,arrayGiocatori,casella,carta,numGiocatori);
            }else {
                printf("\n sei finito nella mensa di %s e devi pagare %d",casella->occupante->nome,(casella->costoCasella*PROFITTO_MENSA2)/PERCENTUALE);
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_MENSA2)/PERCENTUALE;
                giocatore->cfu-=(casella->costoCasella*PROFITTO_MENSA2)/PERCENTUALE;
                eliminazione(giocatore,arrayGiocatori,casella,carta,numGiocatori);
            }
        }else {
            printf("\n la mensa è già tua");
        }
    }
}

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

void aula(Casella* casella, Giocatore* giocatore, Giocatore* arrayGiocatori,int numGiocatori,Carta* carta) {
    int scelta,sediemancanti,i,pls=ZERO;
    bool controllo=true;//lo uso per aiutarmi a controllare se il giocatore ha tutte le caselle dello stesso medesimo colorito
    Casella* casella_sup = casella;
    for (i = ZERO; i < NUM_CASELLE; i++) {//faccio il controllo per tutte e 40 le caselle
        if (casella->coloreCasella==casella_sup->coloreCasella && casella_sup->occupante!=giocatore && casella_sup!=casella) {  //controllo se le altre caselle dello stesso colore sono tutte di questo giocatore
            controllo=false;
        }
        casella_sup = casella_sup->succ;    //e al prossimo ciclo controllerò la successiva
    }//se dopo questo for controllo sarà false il giocatore non avrà tutte le caselle di questo colore
    if (casella->occupante==giocatore) {
        printf("\n(occupata da te)");
        if (controllo) {//se ha tutte le caselle dello stesso colore
            if (casella->scrivania==false) {// se non ha la scrivania
                if (casella->numSedie==MAX_SEDIE) {//possinità in cui nella casella il giocatore abbia 4 sedie
                    if (giocatore->cfu<(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE) {//opzione in cui il giocatore possa solo comprare la scrivania ma non abbia abbastanza soldi
                        printf("\nnon hai abbastanza soldi per comprare la scrivania");
                    }else {//possibilità nella quale abbia i soldini
                        do {
                            printf("\nTASTO[1] inserisci la scrivania per %d cfu\nTASTO[0] non fare nulla\n:",(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE);
                            scanf(" %d",&scelta);
                            switch (scelta) {
                                case METTI_SCRIVANIA:
                                    casella->scrivania=true;
                                    casella->numSedie=ZERO;
                                    giocatore->cfu-=(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE;
                                    break;

                                case NON_METTI_SCRIVANIA:
                                    break;

                                default:
                                    pls=opzioniplsssss(pls);
                                    scelta=UNO;
                                    break;
                            }

                        }while (scelta);
                    }
                }else {// il giocatore non ha ancora tutte le sedie
                    if (giocatore->cfu<(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE) {//il giocatore non può comprare neanche una sedia
                        printf("\nNon puoi fare nulla non hai abbastanza soldi per aggiungere neanche una sedia");
                    }else {//
                        sediemancanti=MAX_SEDIE-casella->numSedie;
                        if (giocatore->cfu>=(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE+(sediemancanti*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE))) {//opzione nella quale il giocatore possa comprare tutte le sedie mancanti più la scrivania
                            compra_Sedie_Scrivania(casella,giocatore);
                        }else {
                            compra_Sedie(casella,giocatore);
                        }

                    }
                }
            }
        }else {
            printf("\n per poter aggiungere sedie devi possedere le altre aule dello stesso colore");
        }
    }else {
        if (casella->occupante == NULL) {//casella libera
            printf("(casella libera)\n");
            if (controllo) {//se ha tutte le caselle del colore della casella in cui sta
                if (giocatore->cfu>=(((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)*MAX_SEDIE)+((casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE)+casella->costoCasella) {//se si può permettere di compare tutte le sedie più la scrivania e la casella
                    occupare_Aula_Scrivania(casella,giocatore,arrayGiocatori,numGiocatori);
                }else {
                    if (giocatore->cfu>=casella->costoCasella+((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)) {// se il giocatore non può compare tutto compresa la scrivania ma può compare la casella + almeno una sedia
                        occupare_Aula_E_Almeno_Una_Sedia(casella,giocatore,arrayGiocatori,numGiocatori);
                    }else {
                        if (giocatore->cfu>=casella->costoCasella) {//se può al massimo permettersi la casella senza sedie
                            occupare_Aula(casella,giocatore,arrayGiocatori,numGiocatori);
                        }else {
                            printf("\n %s spoiler sei povero btw (l'aula va in asta)",giocatore->nome);
                            astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                        }
                    }
                }
            }else {//può o mettere in asta o compare l'aula e se non ha abbastanza soldi la mette in asta da solo
                if (giocatore->cfu>=casella->costoCasella) {
                    occupare_Aula(casella,giocatore,arrayGiocatori,numGiocatori);
                }else {
                    printf("\n %s spiler sei povero btw (l'aula va in asta)",giocatore->nome);
                    astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                }
            }

        }else {
            pagamento_Pedaggio(casella,giocatore,carta,numGiocatori,arrayGiocatori);
        }
    }
}

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

void pagamento_Pedaggio(Casella* casella,Giocatore* giocatore,Carta* carta,int numGiocatori,Giocatore* arrayGiocatori) {
    printf("\nl'aula e' di %s e dovrai pagare :",casella->occupante->nome);
    if (casella->scrivania) {
        printf("%d",(casella->costoCasella*PROFITTO_SCRIVANIA)/PERCENTUALE);
        giocatore->cfu-=(casella->costoCasella*PROFITTO_SCRIVANIA)/PERCENTUALE;
        casella->occupante->cfu+=(casella->costoCasella*PROFITTO_SCRIVANIA)/PERCENTUALE;

    }else {
        switch (casella->numSedie) {
            case ZERO_SEDIE:
                printf("%d",(casella->costoCasella*PROFITTO_AULA)/PERCENTUALE);
                giocatore->cfu-=(casella->costoCasella*PROFITTO_AULA)/PERCENTUALE;
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_AULA)/PERCENTUALE;
                break;

            case UNA_SEDIA:
                printf("%d",(casella->costoCasella*PROFITTO_SEDIA1)/PERCENTUALE);
                giocatore->cfu-=(casella->costoCasella*PROFITTO_SEDIA1)/PERCENTUALE;
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_SEDIA1)/PERCENTUALE;
                break;

            case DUE_SEDIE:
                printf("%d",(casella->costoCasella*PROFITTO_SEDIA2)/PERCENTUALE);
                giocatore->cfu-=(casella->costoCasella*PROFITTO_SEDIA2)/PERCENTUALE;
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_SEDIA2)/PERCENTUALE;
                break;

            case TRE_SEDIE:
                printf("%d",(casella->costoCasella*PROFITTO_SEDIA3)/PERCENTUALE);
                giocatore->cfu-=(casella->costoCasella*PROFITTO_SEDIA3)/PERCENTUALE;
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_SEDIA3)/PERCENTUALE;
                break;

            case MAX_SEDIE:
                printf("%d",(casella->costoCasella*PROFITTO_SEDIA4)/PERCENTUALE);
                giocatore->cfu-=(casella->costoCasella*PROFITTO_SEDIA4)/PERCENTUALE;
                casella->occupante->cfu+=(casella->costoCasella*PROFITTO_SEDIA4)/PERCENTUALE;
                break;

            default:
                printf("\n SIGNOR PROGRAMMATORE C'è UN PROBELEMINOOOOOOOO");//non dovrebbe mai e poi mai succedere
                break;
        }
    }
    eliminazione(giocatore,arrayGiocatori,casella,carta,numGiocatori);
}

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

void compra_Sedie_Scrivania(Casella* casella,Giocatore* giocatore) {
    int sedie_mancanti,scelta,sedie,pls=ZERO;
    sedie_mancanti=MAX_SEDIE-casella->numSedie;
    do {
        printf("\nTASTO[1]posiziona da 1 a %d sedie (ogni sedia costa %d cfu)\n"
        "TASTO[2]posiziona la scrivania (tutto costa %d cfu)"
        "TASTO[0] non fare nulla\n:",sedie_mancanti,(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE,(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE+(sedie_mancanti*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)));
        scanf(" %d",&scelta);

        switch (scelta) {
            case POSIZIONA_UNA_O_PIU_SEDIE:
                do {
                    printf("\nquante sedie vuoi prendere :");
                    scanf(" %d",&sedie);
                    if (sedie>ZERO && sedie<sedie_mancanti+UNO) {
                        casella->numSedie+=sedie;
                        giocatore->cfu -=sedie*(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE;
                        scelta=ZERO;
                    }else {
                        printf("\n ricordati di scegliere di inserire da 1 a 4 sedie massimo e ognuna costa %d cfu",(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                        scelta=UNO;
                    }
                }while (scelta);

                break;
            case POSIZIONA_SCRIVANIA:
                casella->numSedie = ZERO;
                giocatore->cfu -= (casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE+(sedie_mancanti*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE));
                casella->scrivania=true;
                scelta=ZERO;
                break;
            case ZERO:
                break;
            default:
                pls=opzioniplsssss(pls);
                scelta=UNO;
                break;
        }
    }while (scelta);
}

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

void compra_Sedie(Casella*casella,Giocatore* giocatore) {
    int scelta,sedieMancanti=4-casella->numSedie,sedie,pls=ZERO;
    do {
        printf("\nTASTO[1] compra da 1 a %d sedie(ogniuna costa %d)\nTASTO[0] non fare nulla \n:",sedieMancanti,(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
        scanf(" %d",&scelta);
        switch (scelta) {
            case POSIZIONA_UNA_O_PIU_SEDIE:
                do {
                    printf("\nquante sedie vuoi prendere :");
                    scanf(" %d",&sedie);
                    if (sedie>ZERO && sedie<=sedieMancanti && giocatore->cfu>=sedie*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)) {
                        casella->numSedie+=sedie;
                        giocatore->cfu-=sedie*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                        scelta=ZERO;
                    }else {
                        printf("\n inserisci un numero di sedie valide e non prenderne troppe se non hai abbastanza soldi (ne hai %d)",giocatore->cfu);
                        scelta=UNO;
                    }
                }while (scelta);
                break;
            case ZERO:
                break;

            default:
                pls=opzioniplsssss(pls);
                scelta=UNO;
                break;
        }
    }while (scelta);
}

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

void occupare_Aula(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori) {
            int scelta,pls=ZERO;
            do {
                printf("\nTASTO[1] occupare l'aula pagando %d cfu\n"
                       "TASTO[0] non fare nulla(mettendo all'asta la seguente aula)\n:",casella->costoCasella);
                scanf(" %d",&scelta);

                switch (scelta) {
                    case OCCUPA:
                        casella->occupante = giocatore;
                        giocatore->cfu -= casella->costoCasella;
                        scelta=ZERO;
                        break;

                    case ASTA:
                        astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                        break;
                    default:
                        pls=opzioniplsssss(pls);
                        scelta=UNO;
                        break;
                }

            }while (scelta);
}

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

void occupare_Aula_E_Almeno_Una_Sedia(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori) {
            int scelta,sedie,pls=ZERO;
            do {
                printf("\nTASTO[1] occupare l'aula pagando %d cfu\n"
                       "TASTO[2] occupare l'aula posizionando da 1 a 4 sedie (ogni sedia costa %d )\n"
                       "TASTO[0] non fare nulla(mettendo all'asta la seguente aula)\n:",casella->costoCasella,(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                scanf(" %d",&scelta);

                switch (scelta) {
                    case OCCUPA:
                        casella->occupante = giocatore;
                        giocatore->cfu -= casella->costoCasella;
                        scelta=ZERO;
                        printf("\nHai pagato %d CFU, ti rimangono %d CFU", casella->costoCasella, giocatore->cfu);
                        break;
                    case OCCUPA_CON_SEDIE:
                        do {
                            printf("\nquante sedie vuoi prendere :");
                            scanf("%d",&sedie);
                            if (sedie>ZERO && sedie<CINQUE && ((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)*sedie<=giocatore->cfu) {
                                casella->occupante = giocatore;
                                casella->numSedie=sedie;
                                giocatore->cfu -= casella->costoCasella+(sedie*(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                                scelta=ZERO;
                            }else {
                                printf("\n ricordati di scegliere di inserire da 1 a 4 sedie massimo e ognuna costa %d cfu\n e che non puoi compare se non hai abbastanza cfu (ne hai %d)",(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE,giocatore->cfu);
                                scelta=UNO;
                            }
                        }while (scelta);

                        break;

                    case ASTA:
                        astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                        break;
                    default:
                        pls=opzioniplsssss(pls);
                        scelta=UNO;
                        break;
                }
            }while (scelta);
}

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

void occupare_Aula_Scrivania(Casella*casella,Giocatore* giocatore,Giocatore* arrayGiocatori,int numGiocatori) {
            int scelta,sedie,pls=ZERO;
            do {
                printf("\nTASTO[1] occupare l'aula pagando %d cfu\n"
                       "TASTO[2] occupare l'aula posizionando da 1 a 4 sedie (ogni sedia costa %d cfu)\n"
                       "TASTO[3] occupare l'aula posizionando la scrivania (tutto costa %d cfu)"
                       "TASTO[0] non fare nulla(mettendo all'asta la seguente aula)\n:",casella->costoCasella,(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE,casella->costoCasella+(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE+(4*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE)));
                scanf(" %d",&scelta);

                switch (scelta) {
                    case OCCUPA:
                        casella->occupante = giocatore;
                        giocatore->cfu -= casella->costoCasella;
                        scelta=ZERO;
                        break;
                    case OCCUPA_CON_SEDIE:
                        do {
                            printf("\nquante sedie vuoi prendere :");
                            scanf("%d",&sedie);
                            if (sedie>ZERO && sedie<CINQUE) {
                                casella->occupante = giocatore;
                                casella->numSedie=sedie;
                                giocatore->cfu -= casella->costoCasella+(sedie*(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                                scelta=ZERO;
                            }else {
                                printf("\n ricordati di scegliere di inserire da 1 a 4 sedie massimo e ognuna costa %d cfu",(casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE);
                                scelta=UNO;
                            }
                        }while (scelta);

                        break;
                    case OCCUPA_CON_SEDIE_E_SCRIVANIA:
                        casella->occupante = giocatore;
                        giocatore->cfu -= casella->costoCasella+(casella->costoCasella*PERCENTUALE_COSTO_SCRIVANIA)/PERCENTUALE+(4*((casella->costoCasella*PERCENTUALE_COSTO_SEDIE)/PERCENTUALE));
                        casella->scrivania=true;
                        scelta=ZERO;
                        break;
                    case ASTA:
                        astaAulaMensa(arrayGiocatori,giocatore,casella,numGiocatori);
                        break;
                    default:
                        pls=opzioniplsssss(pls);
                        scelta=UNO;
                        break;
                }
            }while (scelta);
}

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

void astaAulaMensa(Giocatore* arrayGiocatori, Giocatore* giocatore,Casella* casella,int numGiocatori) {
    int i,giro=ZERO,o,offerta=casella->costoCasella,pls=ZERO;//giro lo uso per controllare a che giro dell'asta siamo poichè al primo giro i giocatori sono obbligatia fare un'offerta maggiore di quella del precedente
    int giocatoriInGioco=ZERO;
    int scelta,controllo=ZERO; //prima lo utilizzo per vedere se i giocatori e controllo lo uso per vedere se qualuno nessuno vuole partecipare all'asta
    bool* giocatoriGiocanti = NULL;
    giocatoriGiocanti = (bool*)malloc(sizeof(bool)*numGiocatori);//array che mi segna quali giocatori possono o no giocare

    for (i = ZERO; i < numGiocatori; i++) {//da la possibilità ai giocatori di partecipare all'asta oppure no con i dovuti controlli
        giocatoriGiocanti[i] = false;//metto il giocatore di default a false
        if (arrayGiocatori[i].nome!=giocatore->nome && arrayGiocatori[i].cfu >= casella->costoCasella) {// controllo che i giocatori che parteciperanno all'asta abbiano abbastanza cfu e che non siano il giocatore che ha messo in asta
            printf("\n%s vuoi partecipare all'asta ? (0:no 1:si) :", arrayGiocatori[i].nome);
            scanf(" %d",&scelta);
            do {
                switch (scelta) {
                    case SI:
                        giocatoriGiocanti[i] = true;// se il giocatore  vuole e può partecipare all'alta lo imposto a true
                        controllo++;
                        scelta = ZERO;
                        printf("\nottima scelta buona fortuna");
                        break;

                    case NO:
                        printf("\nmi dispiace ti sei perso un'opporturnita'");
                        break;

                    default:
                        pls=opzioniplsssss(pls);
                        scelta = UNO;
                        break;
                }
            }while (scelta);
            pls=ZERO;

        }
    }
    if (controllo==ZERO) {//se controllo è uguale a 0 allora nessuno vuole partecipare all'asta
        return;
    }

    scelta = UNO;

    for (i = ZERO; scelta ; i++) {

        if (i==numGiocatori) {  //serve per resettare l'indice del for così a fare l'offerta dopo l'ultimo giocatore il prissimo sarà il primo
            i=ZERO;
        }

        for (o=ZERO;o<numGiocatori;o++) {// controlla quanti giocatori stanno ancora partecipando all'asta
            if (giocatoriGiocanti[o]==true) {
                giocatoriInGioco++;
            }
        }
        if (giocatoriInGioco==UNO) { //se c'è solo un giocatore nell'asta gli darà la proprietà
            for (o=ZERO;o<numGiocatori;o++) {// scorre tutto l'array per controllare quale sarà l'unico ancora nell'asta e gli da la proprietà
                if (giocatoriGiocanti[o]==true) {
                    arrayGiocatori[o].cfu -= offerta;// do l'aula al giocatore
                    casella->occupante = &arrayGiocatori[o];
                    printf("\nIl giocatore %s ha compato la casella in asta congratulazioni",arrayGiocatori[o].nome);
                    return;
                }
            }

            scelta = UNO;
        }
        giocatoriInGioco = ZERO; //reset

        if (giocatoriGiocanti[i]==true) {
            if (giro==ZERO) {
                do {
                    printf("\n %s fai un offerta maggiore o uguale a: %d\nOfferta: ",arrayGiocatori[i].nome,offerta);
                    scanf("%d",&scelta);// scegli quanto offrire
                    if (scelta>offerta && arrayGiocatori[i].cfu>=scelta) { //verifica se la scelta è maggiore o uguale all'offerta iniziale
                        offerta = scelta;   //se la scelta va bene allora sarà la nuova offerta
                        scelta = ZERO; //scelta diventa 0 facendo finire il while
                    }else {
                        printf("\nla tua offerta dev'essere maggiore o uguale di %d e minore o uguale ai tuoi cfu(%d)",offerta,arrayGiocatori[i].cfu);
                        scelta = UNO;//ripete la scelta dell'offerta
                    }
                }while (scelta);
                scelta = UNO;
            }else{
                if(arrayGiocatori[i].cfu <= offerta) {
                    printf("\n%s non hai abbastanza cfu per fare un offerta mi dispiace sei fuori dall'asta",arrayGiocatori[i].nome);
                    giocatoriGiocanti[i] = false;
                }else {
                    do {//do la possibiltà di scegliere
                        printf("\n %s \nTASTO[0] Vuoi abbandonare l'asta \nTASTO[1] Continua l'asta\n:",arrayGiocatori[i].nome);
                        scanf("%d",&scelta);

                        switch (scelta) {
                            case ABBANDONA://se abbandona la partita
                                printf("\nIl giocatore %s ha abbandonato l'asta ",arrayGiocatori[i].nome);
                                giocatoriGiocanti[i] = false;
                                break;

                            case CONTINUA://se vuole fare l'offerta
                                do {
                                    printf("\nfai un offerta maggiore a %d :",offerta);
                                    scanf(" %d",&scelta);
                                    if (scelta>offerta && arrayGiocatori[i].cfu>=scelta) {// controllo validirà offerta
                                        offerta = scelta;
                                        scelta = ZERO;
                                    }else {
                                        printf("\nla tua offerta dev'essere maggiore di %d e minore o uguale ai tuoi cfu(%d)",offerta,arrayGiocatori[i].cfu);
                                        scelta = UNO;
                                    }
                                }while (scelta);
                                break;

                            default://se non ha selezionato uno dei due tasti e dovrà rifare la scelta
                                pls=opzioniplsssss(pls);
                                scelta=UNO;
                                break;
                        }
                    }while (scelta);
                    scelta = UNO;
                }

            }
            giro++;
        }

    }
    free(giocatoriGiocanti);
}

/**
 * @brief Gestisce l’asta di una carta BUG quando il giocatore che l’ha pescata decide di non usarla.
 *
 * Tutti i giocatori partecipano all’asta effettuando rilanci finché rimane
 * un solo offerente.
 * Ogni rilancio viene verificato rispetto ai CFU disponibili; chi non può
 * più competere viene escluso automaticamente.
 *
 * @param giocatore Giocatore che mette all'asta.
 * @param arrayGiocatori Array di tutti i giocatori.
 * @param numGiocatori Numero totale di giocatori.
 */

void astaCarte(Giocatore* giocatore, Giocatore* arrayGiocatori, int numGiocatori) {
    int i, offerta=ZERO, pre_offerta, scelta, indiceTrovato=-UNO,e;
    bool found=false, fine=true;
    Carta* cartaEsci = NULL;
    Carta* corrente = NULL;
    Carta* prec = NULL;    // prec è la carta precedente alla carta esci così che poi possa toglierla dalle carte del giocatore

    // cerca se un giocatore possiede una carta con azione ESCI
    for (i=ZERO; i<numGiocatori && !found; i++) {
        if (strcmp(arrayGiocatori[i].nome, giocatore->nome) != UGUALI) {
            corrente = arrayGiocatori[i].possedute;// giocatore al quale controlla se ha una carta esci
            prec = NULL;

            while (corrente != NULL && !found) {// scorre tutte le carte del giocatore finche o non finiscono le carte che possiede o finche non la trova
                for (e=ZERO; e<corrente->numEffetti; e++) {// per ogni effetto controlla se ha l'effetto esci
                    if (corrente->effetti[e].azione == ESCI) {// se ha l'effetto esci
                        found = true;   // l'abbiamo trovata
                        cartaEsci = corrente;   // carta esci è la carta da dare all'aquirente
                        indiceTrovato = i;  //indice del giocatore
                        break;
                    }
                }
                if (!found) {// se non l'ha trovata
                    prec = corrente;    // prec diventa la carta che ha controllato e poi va alla prossima
                    corrente = corrente->next;
                }
            }
        }
    }

    if (!found) {// se alla fine del for non l'ha trovata allora
        printf("\nNessun giocatore possiede una carta per uscire dalla batcaverna");
        return;
    }

    // chiedi al giocatore se vuole comprare la carta
    printf("\n%s possiede una carta per uscire dalla batcaverna\nvuoi provare a comprarla?", arrayGiocatori[indiceTrovato].nome);

    while (fine) {// finche non metto a false la variabile fine continua
        if (giocatore->cfu <= offerta) {//se il giocatore non ha abbastanza cfu per fare l'offerta che deve essere maggiore
            printf("\nNon hai abbastanza CFU per fare un'altra offerta");
            return;
        }

        do {
            printf("\n%s\nTASTO[0] Abbandona l'asta\nTASTO[1] Fai un'offerta\n:", giocatore->nome);
            scanf(" %d", &scelta);// do la possibilità di scegliere

            switch (scelta) {
                case ABBANDONA:
                    printf("\nsei uscito dall'asta");
                    return;

                case UNO:
                    pre_offerta = offerta;
                    do {
                        printf("\n%s fai un'offerta a %s (deve essere > %d e <= %d CFU):",giocatore->nome, arrayGiocatori[indiceTrovato].nome,pre_offerta, giocatore->cfu);
                        scanf(" %d", &offerta);//fa l'offerta
                    } while (offerta > giocatore->cfu || offerta <= pre_offerta);// controlla la validità dell'offerta

                    printf("\n%s vuoi accettare l'offerta di %d CFU? (0=no, altro=si):",arrayGiocatori[indiceTrovato].nome, offerta);// chiedo se va bene l'offerta
                    scanf(" %d", &scelta);

                    if (scelta == ZERO) {
                        printf("\n%s ha rifiutato, prova con un'offerta piu' alta", arrayGiocatori[indiceTrovato].nome);
                    } else {
                        scelta=UNO;
                        // trasferisci CFU
                        giocatore->cfu -= offerta;
                        arrayGiocatori[indiceTrovato].cfu += offerta;

                        // rimuovi carta dal venditore
                        if (prec == NULL) {//se la carta esci è la prima del giocatore
                            arrayGiocatori[indiceTrovato].possedute = cartaEsci->next;
                        } else {// altrimenti collega il mazzo
                            prec->next = cartaEsci->next;
                        }

                        // aggiungi carta al compratore in coda
                        cartaEsci->next = NULL;

                        if (giocatore->possedute == NULL) {// se non possiede carte
                            giocatore->possedute = cartaEsci;
                        } else {//altrimenti se ne possiede
                            Carta* temp = giocatore->possedute;
                            while (temp->next != NULL) {
                                temp = temp->next;
                            }
                            temp->next = cartaEsci;
                        }

                        cartaEsci->next = NULL;

                        printf("\n%s ha acquistato la carta %s da %s per %d CFU",giocatore->nome, cartaEsci->nome,arrayGiocatori[indiceTrovato].nome, offerta);

                        fine = false;
                    }
                    break;

                default:
                    break;
            }
        } while (scelta != ZERO && scelta != UNO);
    }
}

int opzioniplsssss(int pls) {
    int i;
    printf("\nScegli una delle opzioni!\n");
    for (i=ZERO;i<pls;i++) {printf(" pls");}
    return pls++;
}

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


void eliminazione(Giocatore* giocatore,Giocatore* arrayGiocatori,Casella* casella,Carta* carta,int numGiocatori) {

    int i, idx = -UNO;
    Carta* coda_mazzo = NULL;

    if (giocatore->cfu < ZERO) {
        printf("\n %s hai usato tutti i tuoi cfu e sei stato eliminato", giocatore->nome);
        scriviLog(giocatore, NULL, ZERO, ZERO, ELIMINAZIONE);

        /* Rimuove le proprieta' del giocatore dal tabellone */
        Casella* cas = casella;
        for (i = ZERO; i < NUM_CASELLE; i++) {
            if (cas->occupante == giocatore) {
                cas->numSedie = ZERO;
                cas->scrivania = false;
                cas->occupante = NULL;
            }
            cas = cas->succ;
        }

        /* Reinserisce le carte possedute dal giocatore in fondo al mazzo */
        if (giocatore->possedute != NULL && carta != NULL) {
            coda_mazzo = carta;
            while (coda_mazzo->next != NULL) { coda_mazzo = coda_mazzo->next; }
            coda_mazzo->next = giocatore->possedute;
            giocatore->possedute = NULL;
        } else {
            giocatore->possedute = NULL;
        }

        /* Trova l'indice del giocatore nell'array */
        for (i = ZERO; i < numGiocatori; i++) {
            if (&arrayGiocatori[i] == giocatore) { idx = i; break; }
        }
        /* Compatta l'array spostando i giocatori successivi indietro */
        if (idx >= ZERO) {
            for (i = idx; i < numGiocatori - UNO; i++) {
                arrayGiocatori[i] = arrayGiocatori[i + UNO];
            }
        }

    }
}

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

void effettocarta(Carta* carta ,Giocatore* giocatore,Giocatore* arrayGiocatori,Casella*casella,int numGiocatori,bool* extra, int numCarte){
    int i,o;
    Casella* casellaGiocatore = NULL;
    Carta *supporto=NULL;//la uso per scorrere le carte del giocatore così che il riferimento del giocatore resti alla prima
    bool trovata=false;
    scriviLog(giocatore,carta,ZERO,ZERO,PESCEPESCEPESCE);
    printf("\n--- hai pescato %s ---\n%s \n\n",carta->nome,carta->descrizione);
    if (carta->tipologia) {
        //printf("\n carte speciali");
        if (strcmp(carta->nome,"DAKI") == UGUALI) {
            paga_Tutto(carta,giocatore,casella,arrayGiocatori,numGiocatori);
        }else {
            if (strcmp(carta->nome,"SBRUNCARE") == UGUALI) {
                giocatore->cfu+=carta->effetti[ZERO].quantita;
                giocatore->saltaTurno=true;
            }else {
                if (strcmp(carta->nome,"TOKYO GHOUL") == UGUALI) {
                    for (o=ZERO;o<NUM_CASELLE;o++) {
                        casella=casella->succ;
                        if (casella->occupante==giocatore) {trovata=true;}
                    }
                    if (trovata) {
                        while (casella->occupante!=giocatore && casella->Tipologia!=UNO) {
                            casella=casella->succ;
                        }
                        printf("\nti è stata tolta la casella %s",casella->nome);
                        casella->numSedie=ZERO;
                        casella->scrivania=false;
                        casella->occupante=NULL;
                    }else {
                        printf("\n non hai aule da donare");
                    }
                    giocatore->cfu+=carta->effetti[UNO].quantita;
                }else {
                    if (strcmp(carta->nome,"GIOVANNA D'ARCO") == UGUALI) {
                        while (strcmp(casella->nome,"Aula_Magna_Matematica") != UGUALI){casella=casella->succ;}
                        if (casella->occupante==giocatore) {
                            giocatore->cfu-=GIOVANNA_COSTO;
                        }else {
                            giocatore->saltaTurno=true;
                        }
                    }else {
                        if (strcmp(carta->nome,"ZONA FRANCA") == UGUALI) {
                            for (i=ZERO;i<NUM_CASELLE;i++) {
                                if (casella->occupante==giocatore) {
                                    giocatore->cfu-=casella->scrivania*carta->effetti[ZERO].quantita;
                                    giocatore->cfu-=casella->numSedie*carta->effetti[ZERO].quantita;
                                    if (giocatore->cfu<ZERO) {
                                        eliminazione(giocatore,arrayGiocatori,casella,carta,numGiocatori);
                                        return;
                                    }
                                }
                                casella=casella->succ;
                            }
                            while (giocatore->posizione->Tipologia!=carta->effetti->casella) {casella=casella->prec;}
                            giocatore->posizione=casella;
                            printf("\nsei arrivato in %s",casella->nome);

                        }
                    }
                }
            }
        }
    }else{

        switch (carta->effetti->azione) {
            case PAGA_QUALCOSA:
                printf("\n\nti vengono tolti %d cfu ai tuoi %d cfu\n",carta->effetti->quantita,giocatore->cfu);
                giocatore->cfu-=carta->effetti->quantita;
                if (giocatore->cfu<ZERO) {
                    eliminazione(giocatore,arrayGiocatori,casella,carta,numGiocatori);
                }else {
                    printf("\nora hai %d cfu",giocatore->cfu);
                }

                break;

            case PAGA_TUTTO:
                paga_Tutto(carta,giocatore,casella,arrayGiocatori,numGiocatori);
                break;

            case PRENDI:
                printf("\n\nti vengono accreditati %d cfu ai tuoi %d cfu\n",carta->effetti->quantita,giocatore->cfu);
                giocatore->cfu+=carta->effetti->quantita;
                printf("\nora hai %d cfu",giocatore->cfu);
                break;

            case SALTA_TURNO:
                giocatore->saltaTurno=true;
                break;

            case NUOVO_TURNO:
                *extra=true;
                break;

            case ESCI:
                printf("\nhai aggiunto una carta al  tuo mazzo");
                if (giocatore->possedute==NULL) {   //se il giocatore ha già delle carte
                    giocatore->possedute = carta;
                }else { //se non ha ancora delle carte
                    supporto = giocatore->possedute;
                    while (supporto->next!=NULL) { //scorro tutte le carte che ha e metto questa carta come ultima
                        supporto=supporto->next;
                    }
                    supporto->next=carta;
                }
                carta->next = NULL;
                break;

            case VAI_INDIETRO:
                casella=giocatore->posizione;
                if (carta->effetti->quantita==ZERO) {
                    while (casella->Tipologia!=carta->effetti->casella) {
                        casella=casella->prec;
                    }
                    giocatore->posizione=casella;
                }else {

                    for (i=ZERO;i<carta->effetti->quantita;i++) {
                        casella=casella->prec;
                    }

                }
                giocatore->posizione=casella;
                printf("\nsei arrivato in %s", giocatore->posizione->nome);
                effettoCasella(casella, giocatore, arrayGiocatori, numGiocatori, &carta, extra, numCarte);

                break;

            case VAI_AVANTI:
                casella=giocatore->posizione;
                if (carta->effetti->quantita==ZERO) {
                    while (casella->Tipologia!=carta->effetti->casella) {
                        casella=casella->succ;
                    }

                }else {

                    for (i=ZERO;i<carta->effetti->quantita;i++) {
                        casella=casella->succ;
                    }

                }
                giocatore->posizione=casella;
                printf("\nsei arrivato in %s",giocatore->posizione->nome);
                effettoCasella(casella, giocatore, arrayGiocatori, numGiocatori, &carta, extra, numCarte);
                break;

            case REGALA:
                for (i=ZERO;i<carta->effetti->quantita;i++) {
                    casellaGiocatore=NULL;
                    for (o=ZERO;o<NUM_CASELLE;o++) {
                        casella=casella->succ;
                        if (casella->occupante==giocatore && casella->Tipologia == AULA) {
                            trovata=true;
                            casellaGiocatore = casella;
                        }
                    }
                    if (trovata) {
                        casellaGiocatore->numSedie = ZERO;
                        casellaGiocatore->scrivania = false;
                        casellaGiocatore->occupante = NULL;
                        giocatore->spaziOccupati--;
                        
                        while (casella->occupante!=giocatore && casella->Tipologia!=UNO) {
                            casella=casella->succ;
                        }
                        printf("\nti è stata tolta la casella %s",casella->nome);
                        casella->numSedie=ZERO;
                        casella->scrivania=false;
                        casella->occupante=NULL;
                    }else {
                        printf("\n non hai aule da donare");
                        return;
                    }

                }
                break;

            default:
                break;
        }
    }
}

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


void paga_Tutto(Carta* carta,Giocatore* giocatore,Casella* casella,Giocatore* arrayGiocatori,int numGiocatori) {
    Casella *sup_casella=casella;
    int i;
    if (carta->effetti->quantita==UNO) {//se  la quantita è uno allora tolgo tutti i cfu altrimenti controllo se deve pagare solo le sedie o anche le scrivanie
        giocatore->cfu=ZERO;
        printf("\n i tuoi cfu vengono impostati a 0");
    }else {
        if (carta->numEffetti>UNO) {
            printf("\ndevi pagare per ogni sedia e scrivania che possiedi");
            for (i=ZERO;i<NUM_CASELLE;i++) {
                if (sup_casella->occupante==giocatore) {
                    if (carta->effetti[ZERO].quantita>carta->effetti[UNO].quantita) {
                        giocatore->cfu-=sup_casella->numSedie*carta->effetti[UNO].quantita;
                        giocatore->cfu-=sup_casella->scrivania*carta->effetti[ZERO].quantita;
                    }else {
                        giocatore->cfu-=sup_casella->numSedie*carta->effetti[ZERO].quantita;
                        giocatore->cfu-=sup_casella->scrivania*carta->effetti[UNO].quantita;
                    }
                    if (giocatore->cfu<ZERO) {
                        eliminazione(giocatore,arrayGiocatori,sup_casella,carta,numGiocatori);
                        return;
                    }

                }
                sup_casella=sup_casella->succ;
            }
        }else {
            printf("\ndevi pagare per ogni sedia che possiedi");

            for (i=ZERO;i<NUM_CASELLE;i++) {
                if (sup_casella->occupante==giocatore) {
                    giocatore->cfu-=carta->effetti->quantita*sup_casella->numSedie;
                }
                if (giocatore->cfu<ZERO) {
                    eliminazione(giocatore,arrayGiocatori,sup_casella,carta,numGiocatori);
                    return;
                }
            }
        }
    }
}

