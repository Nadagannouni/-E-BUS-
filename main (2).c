#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int j,m,a;
}date;
typedef struct {
    int h,m,s;
}heure;
typedef struct Bus {
    int IdB,nb_place_dispo;
    int place_dispo[100];

    char dest[50];
    date dadep;
    heure hedep;
    int nbserv;
    char services[20][101];
    struct Bus *suiv;
}Bus  ;
 typedef struct  Reservation {
    int Idres,IdB,num_place;
    char nompass[50],mdp[50];
    struct Reservation *suiv;
}Reservation;
 typedef struct Passager {
    int idpass, numtel;
    char nompass[50],email[50],motdp[50];
    struct Passager *suiv;
} Passager;
int buscpm = 0;
int rescpm = 0;
int passcpm = 0;
Passager *pass=NULL;
Reservation *res=NULL;
Bus *b=NULL;
void ajoutp(Passager *nvpassager) {
    if (pass == NULL) {
        pass = nvpassager;
        pass->suiv =NULL;
    } else {
        Passager* p = pass;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = nvpassager;
        p->suiv->suiv=NULL;
    }
}
void ajoutb(Bus *nvbus) {
    if (b == NULL) {
        b = nvbus;
        b->suiv =NULL;
    } else {
        Bus* p = b;
        while (p->suiv != NULL)
           p= p->suiv;
           nvbus->suiv=NULL;

        p->suiv = nvbus;
        //p->suiv->suiv=NULL;
    }
}
void ajoutres(Reservation *nvres) {
    if (res == NULL) {
        res = nvres;
        res->suiv =NULL;
    } else {
        Reservation* p = res;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = nvres;
        p->suiv->suiv=NULL;
    }
}
void creer_nv_cpt() {
    Passager *p = (Passager *)malloc(sizeof(Passager));
    printf("Entrez votre nom : \n");
    scanf("%s",&p->nompass);
    printf("Entrez votre email  : \n");
    scanf("%s", &p->email);
    printf("Entrez votre numero de telephone :\n ");
    scanf("%d",  &p->numtel);
    printf("Entrez votre mot de passe :\n ");
    scanf("%s",  &p->motdp);
    p->idpass =passcpm+1;
    p->suiv = NULL;
    printf("Compte cree avec succes.\nvoici votre identifinat c'est votre numero dans la liste des passagers\n%d\n",p->idpass);
    ajoutp( p);

}
void creerbus() {
    Bus *p = (Bus *)malloc(sizeof(Bus));
    printf("Entrez l'identifiant du bus :\n ");
    scanf("%d",  &p->IdB);
    printf("Entrez le nombre de places disponibles dans le bus :\n ");
    scanf("%d",  &p->nb_place_dispo);
   printf("Entrez la destination du bus :\n ");
   for (int i = 0; i < p->nb_place_dispo; i++)p->place_dispo[i]=0;
    scanf("%s",  &p->dest);
     printf("Entrez la date de depart du bus dans la format jj/mm/aaaa :\n ");
    scanf("%d/%d/%d",  &p->dadep.j,&p->dadep.m,&p->dadep.a);
    printf("Entrez l'heure' de depart du bus  dans la format hh:mm:ss :\n ");
    scanf("%d:%d:%d",  &p->hedep.h,&p->hedep.m,&p->hedep.s);
    printf("Entrez le nombre des services valables dans le bus :\n ");
    scanf("%d",  &p->nbserv);

    printf("Entrez les services valables dans le bus :\n ");
    for (int i = 0; i < p->nbserv; i++)
    scanf("%s",  &p->services[i]);
    ajoutb( p);
    printf("bus ajoute avec succee \n ");
}
void details_bus() {
    Bus *q=b;
    while(q != NULL) {
         printf("Idantifiant : %d\n Destination : %s\n nombre de places disponibles : %d\n les numeros des places disponibles dans le bus:",
               q->IdB, q->dest,q->nb_place_dispo);
        for (int i = 0; i < q->nb_place_dispo; i++)
         if(q->place_dispo[i]==0)
          printf("%d,",i+1);
          printf("\n");
         printf("date de depart: %d/%d/%d à  %d:%d:%d\n  servises valables: \n", q->dadep.j, q->dadep.m,q->dadep.a,q->hedep.h,q->hedep.m,q->hedep.s);
         for (int i = 0; i < q->nbserv; i++)
          printf("-%s,",q->services[i]);
           printf("\n");

        q = q->suiv;
    }}


void creer_res() {

    Reservation *p = (Reservation *)malloc(sizeof(Reservation));
    printf("Entrez le nom du voyageur:\n ");
    scanf("%s", &p->nompass);
    printf("Entrez votre identifiant:\n ");
    scanf("%d", &p->Idres);
     printf("Entrez votre mot de passe: \n");
     scanf("%s", &p->mdp);
    printf("les bus disponibles sont :\n");
    details_bus(b);
    int nbr=0,i=0;Bus *l=b;
    while(nbr==0){
    nbr=0;l=b;
    printf("Entrez l'identifiant du bus choisi : ");
    scanf("%d", &p->IdB);

     while (nbr==0 && l!=NULL){
         i=0;

         while(nbr==0 && l!=NULL&&i<l->nb_place_dispo&& l->IdB==p->IdB){
        if(l->place_dispo[i]==0)
        nbr++;
        i++;}
         l=l->suiv;

    }
        if(nbr==0)printf("Oups bus complet!\n");
    }
    int nb=1;Bus *h=b;
    while(nb==1){
     h=b;
    nb=0;
    printf("Entrez le numero de la place choisi : ");
    scanf("%d", &p->num_place);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[p->num_place]==1&& h->IdB==p->IdB)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("place deja reservee.\n");}
    printf("reservation faite avec succee\n");
    ajoutres(p);
}
Reservation* recherche_reservation(int id , char mtdp[50] ){
    Reservation* r=res;
    int nb=0;
    while(r->suiv!=NULL){

        if(r->Idres==id&&r->mdp==mtdp)return r;
        r=r->suiv;
    }


        if(r->mdp==mtdp ){
            if( r->Idres==id)
            return r;}
        else {

            return NULL;
        }

}

void modif_res() {
    int id;
    char modp[50];
     printf("entrez votre identifiant:\n");
     scanf("%d",&id);
     printf("entrez votre mot de passe:\n");
     scanf("%s",&modp);
    Reservation *p = recherche_reservation(id,modp);

    if (p!= NULL) {
        int x=0;
        while(x!=1&&x!=2){
         printf("que souhaitez vous modifier?\n1-le bus\n2-le numero de votre place\n");
         scanf("%d",&x);}
        if(x==1){
            int nbr=0,i=0;Bus *l=b;int idt;
    while(nbr==0){
    nbr=0;l=b;
    printf("entrez l'identifinat du nouveau bus choisi\n: ");

    scanf("%d",idt);

     while (nbr==0 && l!=NULL){
         i=0;

         while(nbr==0 & l!=NULL&&i<l->nb_place_dispo&& l->IdB==idt){
        if(l->place_dispo[i]==0)
        nbr++;

        i++;}
         l=l->suiv;

    }
        if(nbr==0)printf("Oups bus complet!\n");
    else{


    int nb=1;Bus *h=b;int num_plc;
    while(nb==1){

     h=b;
    nb=0;
    printf("Entrez le numero de la place choisi dans le nouveau bus  : ");
    scanf("%d", &num_plc);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[num_plc]==1&& h->IdB==idt)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("place deja reservee.\n");}
     p->IdB=idt;
      p->num_place = num_plc;
    printf("modification faite avec succee\n");}

        }}
    else if(x==2){
        int num_plc;
int nb=1;Bus *h=b;
    while(nb==1){

     h=b;
    nb=0;
    printf("Entrez le numero de la nouvelle place choisi:\n ");
    scanf("%d", &num_plc);
    while (nb==0 & h!=NULL){
        if(h->place_dispo[num_plc]==1&& h->IdB==p->IdB)
        nb++;
        h=h->suiv;
    }
    if(nb==1)
    printf("place deja reservee.\n");}

      p->num_place = num_plc;
    printf("modification faite avec succee\n");}

        }





else {

        printf("oups reservation non trouvee.\n");
    }

}


int main() {
    creerbus();
     printf("bienvenus cher client!\nsi vous voulez utulizer notre application vous devez creer un compte s'il vous plait!\n");
     creer_nv_cpt();
     int x,y;
     while(x!=1&&x!=2&&x!=3&&x!=4){
      printf("1-afficher les details des bus diponibles\n2-creer une reservation\n3-modifier une reservation deja faite\n4-pour quitter ");
      scanf("%d",&x);
      switch(x){
          case 1:details_bus();
          break;
          case 2:creer_res();  break;
          case 3: modif_res();  break;
          case 4:return 0;  break;
      }

     }





}
