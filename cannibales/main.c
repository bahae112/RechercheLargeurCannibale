#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char position;
    int x;
    int y;

} etat;

typedef struct Noeud {
    struct Noeud *suivant;
    etat Etat;
} noeud;

typedef struct {
    noeud* sommet;
} liste;

liste listeNoeuds;
int n;

void Inserer(etat etatCourant, liste *L0) {
    liste L1 = *L0;
    noeud *nouveaunoeud = (noeud *)malloc(sizeof(noeud));
    nouveaunoeud->Etat = etatCourant;
    nouveaunoeud->suivant = L1.sommet ;
    L1.sommet = nouveaunoeud;
    *L0 = L1;
    //printf("(%c %i %i)\n",L1.sommet->Etat.position,L1.sommet->Etat.x,L1.sommet->Etat.y);
}

int Vide(liste L) {
    return (L.sommet == NULL );
}

etat Extraire(liste *L) {
    liste L0;
    L0 = *L;
    etat e;
    noeud *temp;
    if (!Vide(L0)) {
        e = L0.sommet->Etat;
        temp = L0.sommet;
        L0.sommet = L0.sommet->suivant;
        free(temp);
        *L = L0;
        return e;
    }
}

int Appartient(etat e, liste L) {
    noeud *p = L.sommet;
    while (p != NULL) {
        if (p->Etat.x == e.x && p->Etat.y == e.y && p->Etat.position == e.position){
            return 1;
        }
        p = p->suivant;
    }
    return 0;
}

int etatSolution(etat e) {
    return (e.x == 0 && e.y==0 && e.position=='G');
}

void genererSuccesseurs(etat e) {
    etat et;
    int x0, y0;
    char p = e.position;
    x0 = e.x;
    y0 = e.y;
    if ( p == 'D'){
    if(x0 > 0 && ((x0 == y0 +1) || ( x0 == 1)))  {
    et.position = 'G';
    et.x = x0 - 1;
    et.y = y0 ;
    Inserer(et, &listeNoeuds); }
    if (y0 > 0 && ((x0 == 0) || (x0 == 3))) {
    et.position = 'G';
    et.x = x0;
    et.y = y0 - 1 ;
    Inserer(et, &listeNoeuds); }
    if ( x0 > 1 && ((x0 == y0 +2) || ( x0 == 2))) {
    et.position = 'G';
    et.x = x0 - 2;
    et.y = y0 ;
    Inserer(et, &listeNoeuds); }
    if ( y0 > 1 && ((x0 == 0) || (x0 == 3))) {
    et.position = 'G';
    et.x = x0;
    et.y = y0 - 2 ;
    Inserer(et, &listeNoeuds); }

    if ( x0 > 0 && y0 > 0 && (x0 == y0)) {
    et.position = 'G';
    et.x = x0 - 1;
    et.y = y0 - 1 ;
    Inserer(et, &listeNoeuds); }



    }
    if ( p == 'G'){
    if (  3 - x0 > 0 && (( x0 == y0 -1 )|| ((x0 == 2) && ( y0 == 2) ))) {
    et.position = 'D';
    et.x = x0 + 1;
    et.y = y0 ;
    Inserer(et, &listeNoeuds);}
    if ( 3 - y0 > 0 && ((x0 >= y0 +1) || (x0 == 0))) {
            et.position = 'D';
    et.x = x0;
    et.y = y0 + 1 ;
    Inserer(et, &listeNoeuds); }

    if ( 3 - x0 > 1 && (( x0 == 0) || ((x0 == 1) && (y0 == 1)))) {
    et.position = 'D';
    et.x = x0 + 3;
    et.y = y0 ;
    Inserer(et, &listeNoeuds); }

    if( 3 - y0 > 1 && ((x0 == 0) || (x0 == 3))) {
    et.position = 'D';
    et.x = x0;
    et.y = y0 + 2 ;
    Inserer(et, &listeNoeuds); }

    if ( 3 - x0 > 0 && 3 - y0 > 0 && (x0 == y0)) {
    et.position = 'D';
    et.x = x0 + 1;
    et.y = y0 + 1 ;
    Inserer(et, &listeNoeuds); }

    }
}

void RechercheProfondeur(etat etatInitial, etat etatFinal) {
    liste NoeudsDejaTraites;
    etat etatCourant;
    listeNoeuds.sommet = NULL;
    Inserer(etatInitial, &listeNoeuds);
    NoeudsDejaTraites.sommet =  NULL;
    while (!Vide(listeNoeuds)) {
        etatCourant = Extraire(&listeNoeuds);
        if (etatSolution(etatCourant)) {
            printf("(%c,%d,%d)\n",etatCourant.position,etatCourant.x,etatCourant.y);
            printf("\nSuccess ! Arret sur le noeud:(%c,%d, %d)\n\n Nombre de noeuds explores: %d\n", etatCourant.position,etatCourant.x, etatCourant.y, n);
            exit(0);
        } else if (Appartient(etatCourant, NoeudsDejaTraites)==0){
            genererSuccesseurs(etatCourant);
            printf("(%c,%d,%d)\n",etatCourant.position,etatCourant.x,etatCourant.y);

            Inserer(etatCourant, &NoeudsDejaTraites);
            n++;
        }
    }
    puts("\nPas de solution");
}

int main() {
    etat etatInitial = {'D',3,3}, etatFinal = {'G',0,0};
    RechercheProfondeur(etatInitial, etatFinal);

    return 0;
}
