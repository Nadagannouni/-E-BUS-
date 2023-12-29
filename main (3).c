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
//Passager *pass=NULL;
//Reservation *res=NULL;
//Bus *b=NULL;
void ajoutp(Passager *nvpassager,const char *voyfich) {
    FILE *voy = fopen("voyfich", "ab");
    fwrite(nvpassager, sizeof(Passager), 1, voy );
        fclose(voy );

}
void ajoutb(Bus *nvbus,const char *busfich) {
    FILE *bs = fopen("busfich", "ab");
    fwrite(nvbus, sizeof(Bus), 1, bs );
        fclose(bs  );
}
void ajoutres(Reservation *nvres,const char *resfich) {
    FILE *reser= fopen("resfich", "ab");
    fwrite(nvres, sizeof(Reservation), 1, reser );
        fclose(reser );
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
    ajoutp( p,"passfich");

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
    ajoutb( p,"busfich");
    printf("bus ajoute avec succee \n ");
}
void details_bus(const char *busfich) {
    FILE *f= fopen("busfich", "rb");
    Bus *q;
    while (fread(q, sizeof(Bus), 1, f) == 1) {
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


    } fclose(f); }


void creer_res() {

    Reservation *p = (Reservation *)malloc(sizeof(Reservation));
    printf("Entrez le nom du voyageur:\n ");
    scanf("%s", &p->nompass);
    printf("Entrez votre identifiant:\n ");
    scanf("%d", &p->Idres);
     printf("Entrez votre mot de passe: \n");
     scanf("%s", &p->mdp);
    printf("les bus disponibles sont :\n");
    details_bus("busfich");
    FILE *f= fopen("busfich", "rb");
    Bus *l;
    int nbr=0,i=0;//Bus *l=b;
    while(nbr==0){
    nbr=0;
    printf("Entrez l'identifiant du bus choisi : ");
    scanf("%d", &p->IdB);

     while (nbr==0 ){
         i=0;

         while(nbr==0 && fread(l, sizeof(Bus), 1, f) == 1&&i<l->nb_place_dispo&& l->IdB==p->IdB){
        if(l->place_dispo[i]==0)
        nbr++;
        i++;}


    }
        if(nbr==0)printf("Oups bus complet!\n");
    }fclose(f);
    int nb=1;
    while(nb==1){
     FILE *f= fopen("busfich", "rb");
     Bus *h;
    nb=0;
    printf("Entrez le numero de la place choisi : ");
    scanf("%d", &p->num_place);
    while (nb==0 && fread(h, sizeof(Bus), 1, f) == 1){
        if(h->place_dispo[p->num_place]==1&& h->IdB==p->IdB)
        nb++;

    }fclose(f);
    if(nb==1)
    printf("place deja reservee.\n");}
    printf("reservation faite avec succee\n");
    ajoutres(p,"resfich");
}
Reservation* recherche_reservation(int id , char mtdp[50] ){
    FILE *f= fopen("resfich", "rb");
    Reservation* r;
    int nb=0;
    while(fread(r, sizeof(Reservation), 1, f) == 1){

        if(r->Idres==id&&r->mdp==mtdp)return r;

    } fclose(f);




            return NULL;


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
            FILE *f= fopen("busfich", "rb");
            Bus *l;
            int nbr=0,i=0;int idt;
    while (fread(l, sizeof(Bus), 1, f) == 1&& nbr==0){
    nbr=0;
    printf("entrez l'identifinat du nouveau bus choisi\n: ");

    scanf("%d",idt);

     while (nbr==0 && fread(l, sizeof(Bus), 1, f) == 1){
         i=0;

         while(nbr==0 &fread(l, sizeof(Bus), 1, f) == 1&&i<l->nb_place_dispo&& l->IdB==idt){
        if(l->place_dispo[i]==0)
        nbr++;

        i++;}


    }fclose(f);
        if(nbr==0)printf("Oups bus complet!\n");
    else{
      FILE *f= fopen("busfich", "rb");
    Bus *h;

    int nb=1;int num_plc;
    while(nb==1&&fread(h, sizeof(Bus), 1, f) == 1){


    nb=0;
    printf("Entrez le numero de la place choisi dans le nouveau bus  : ");
    scanf("%d", &num_plc);
    while (nb==0 &&fread(h, sizeof(Bus), 1, f) == 1){
        if(h->place_dispo[num_plc]==1&& h->IdB==idt)
        nb++;

    }
    if(nb==1)
    printf("place deja reservee.\n");}fclose(f);
     p->IdB=idt;
      p->num_place = num_plc;
    printf("modification faite avec succee\n");}

        }}
    else if(x==2){
        FILE *f= fopen("busfich", "rb");
   Bus *h;
        int num_plc;
int nb=1;
    while(nb==1){


    nb=0;
    printf("Entrez le numero de la nouvelle place choisi:\n ");
    scanf("%d", &num_plc);
    while (nb==0 &&fread(h, sizeof(Bus), 1, f) == 1){
        if(h->place_dispo[num_plc]==1&& h->IdB==p->IdB)
        nb++;

    }fclose(f);
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
          case 1:details_bus("busfich");
          break;
          case 2:creer_res();  break;
          case 3: modif_res();  break;
          case 4:return 0;  break;
      }

     }





}
