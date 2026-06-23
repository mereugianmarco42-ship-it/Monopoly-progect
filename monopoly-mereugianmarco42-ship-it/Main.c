#include "Monopoly.h"
//QUESTO è IL PROGETTO UFFICIALE A CUI DEVI LAVORARE RICORDATI DI FARE UN  PUSH APPENA SEI A CASA
int main() {
    int scelta,numGiocatori=ZERO,tocca_a=ZERO,tiroDadi,avanzata,numCarte,turno=ZERO;//tocca_a serve per sapere a chi tooca, turno sono i turni totali svolti durante la partita
    srand(time(NULL));
    bool extraTurno=false;
    Carta* carta=NULL;
    Casella* casella=NULL;
    Giocatore* arrayGiocatori = NULL;   //array che contiene tutti i giocatori
    FILE *f = fopen(SAVEGAME, "rb");
    do {

        printf("\n WELCOME TO MONOPOLI - PR1 EDITION");
        printf("\n\nTASTO[1] Inizia una nuova partita\n");
        if (f != NULL) {
            printf("\nTASTO[2] Caricare una partita\n");
            printf("\nTASTO[3] Uscire dal gioco\n");
            printf("\nHai una partita in sospeso premi 2 per continuarla\n:");
        }else {
            printf("\nTASTO[3] Uscire dal gioco\n:");
        }

        scanf(" %d", &scelta);
        switch (scelta) {
            case NUOVO_GAME:
                if (f != NULL) {
                    fclose(f);
                    remove(SAVEGAME);
                }
                FILE *log = fopen("log.txt", "w");  //cancella e ricrea il file log
                fclose(log);
                carta=caricaMazzo();
                casella=caricaTabellone();
                arrayGiocatori=nuovaPartita(casella,&numGiocatori);
                ordineGiocatori(numGiocatori,arrayGiocatori);
                do {
                    printf("\n Inserisci il numero di carte che pesca il giocatore quando capita sulla casella bug(1-3) \n:");
                    scanf(" %d", &numCarte);
                }while (numCarte>MAX_BUG || numCarte<MIN_BUG);
                break;

            case CARICA_GAME:
                if (f==NULL) {
                    printf("\nNon ci sono salvataggi disponibili");
                    scelta = CINQUE;//imposto scelta a 5 così che dovrà rifare la scelta
                }else {
                    caricaPartita(&tocca_a,&arrayGiocatori,&numGiocatori,&turno,&casella,&carta,&numCarte);
                    printf("\nhai caricato l'ultimo salvataggio");
                    fclose(f);
                }

                break;

            case ESCI_GAME:
                if (f != NULL) {
                    fclose(f);
                    remove(SAVEGAME);
                }
                printf("\n_________FINE PARTITA__________\n");
                return ZERO;

            default:
                break;
        }

    }while (scelta>MAX_SCELTA || scelta<MIN_SCELTA);

    for (;numGiocatori>UNO;tocca_a++) {
        salvaPartita(tocca_a,arrayGiocatori,numGiocatori,turno,casella,carta,numCarte);

        if (arrayGiocatori[tocca_a].cfu < ZERO) {//< Controllo se il giocatore e' stato eliminato durante il turno precedente
            numGiocatori--;
            if (tocca_a >= numGiocatori) {
                tocca_a = -UNO;
            }
        } else {
            if (arrayGiocatori[tocca_a].turniBatCaverna==ZERO && !arrayGiocatori[tocca_a].saltaTurno) {
                tiroDadi=gestioneTurni(arrayGiocatori,&arrayGiocatori[tocca_a],casella,numGiocatori,&extraTurno);

                for (avanzata=ZERO;avanzata<tiroDadi;avanzata++) {
                    arrayGiocatori[tocca_a].posizione=arrayGiocatori[tocca_a].posizione->succ;

                    if (arrayGiocatori[tocca_a].posizione->Tipologia==VIA) {
                        printf("\nsei passato dal via ti vengono accreditati 200 cfu");
                        arrayGiocatori[tocca_a].cfu+=PAGA_VIA;
                    }
                }

                printf("\n%s sei finito nella casella %s\n", arrayGiocatori[tocca_a].nome,arrayGiocatori[tocca_a].posizione->nome);
                scriviLog(&arrayGiocatori[tocca_a],carta,turno,tiroDadi,TIRO);
            }

            effettoCasella(arrayGiocatori[tocca_a].posizione,&arrayGiocatori[tocca_a],arrayGiocatori,numGiocatori,&carta,&extraTurno,numCarte);

            if (arrayGiocatori[tocca_a].cfu < ZERO) {//controllo se durante il turno è stato eliminato il giocatore e riassegno i valori
                numGiocatori--;
                if (tocca_a >= numGiocatori) {
                    tocca_a = -UNO;
                }
                extraTurno = false;
                if (tocca_a == numGiocatori - UNO) {
                    tocca_a = -UNO;
                    turno++;
                }
            } else {
                if (extraTurno){tocca_a--;extraTurno=false;}
                if (tocca_a==numGiocatori-UNO) {tocca_a=-UNO;turno++;}
            }
        }
    }
    printf("\nCOMPLIMENTI %s HAI VINTO LA PARTITA!!!!!",arrayGiocatori[VINCITORE].nome);
    scriviLog(&arrayGiocatori[VINCITORE],NULL,ZERO,ZERO,VITTORIA);
    remove(SAVEGAME);

}