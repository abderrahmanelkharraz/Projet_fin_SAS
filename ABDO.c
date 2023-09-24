#include <stdio.h>
#include <string.h>
#include <time.h>
// Structure pour représenter une tache
typedef struct {
    int id;
    char titre[50];
    char description[200];
    time_t deadline;
    char statut[30];
} Tache;

Tache TableauTaches[1000];
int cpt=0;
int Identifiant=1;
struct tm saisirDeadline() {
    struct tm deadline = {0};

    printf("Enter year: ");
    scanf("%d", &(deadline.tm_year));
    deadline.tm_year-=1900;


    printf("Enter month (1-12): ");
    scanf("%d", &(deadline.tm_mon));
    deadline.tm_mon -= 1; // Months since January (0-11)

    printf("Enter day (1-31): ");
    scanf("%d", &(deadline.tm_mday));
    return deadline;
}

// Fonction pour ajouter une seule tache
void AjouterTache(){
    Tache t;
    char stat[3][10]={"todo","doing","done"};
//    printf("\nVeuillez saisir l identifiant:");
//    scanf("%d",&t.id);
	t.id=Identifiant++;
    printf("Veuillez saisir le titre:");
    scanf("%s",t.titre);
    printf("Veuillez saisir la description:");
    scanf("%s",t.description);
    printf("Veuillez saisir le statut: 1. A realiser, 2. En cours de realisation, 3. Finalisation. ");
    int x;
    scanf("%d",&x);
    if(x==1)
    	strcpy(t.statut,stat[0]);
    if(x==2)
    	strcpy(t.statut,stat[1]);
    if(x==3)
    	strcpy(t.statut,stat[2]);
    struct tm dead=saisirDeadline();
    t.deadline=mktime(&dead);
    TableauTaches[cpt++]=t;
}
// Fonction pour ajouter plusieurs taches
void ajouterPlusieurs(){
	int i,n;
	printf("Veuillez saisir le nombre de tache voulu :");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		AjouterTache();
	}
}

// Fonction pour afficher une seule tache
void afficherTache(Tache t){
    printf("\nID:\t%d",t.id);
    printf("\nTitre:\t%s",t.titre);
    printf("\nDescription:\t%s",t.description);
    printf("\nStatut:\t%s",t.statut);
    char deadlineStr[20];
    strftime(deadlineStr, sizeof(deadlineStr), "%d/%m/%Y", localtime(&t.deadline));
    printf("\nDeadline:%s\n",deadlineStr);
}
// Fonction pour afficher plusieurs taches
void afficherPlusieurTaches(){
	int i;
	if ( cpt == 0)
        printf("\nLa liste des taches est vide!\n");
	for(i=0;i<cpt;i++){
		afficherTache(TableauTaches[i]);
	}
}

// Fonction pour modifier la descreption d'une tache
void modifierTache(Tache t){
	int i;
	int n =0;
	for(i=0;i<cpt;i++){
		if(TableauTaches[i].id==t.id){
			scanf("%s",TableauTaches[i].description);
			n=1;
		}
		if(n==1){
			break;
		}
	}
	if(n==0){
		printf("\ncette tache n existe pas");
	}
}
// Fonction pour modifier le status d'une tache
void modifierTacheStatut(Tache t){
	int i;
	int n =0;
	char stat[3][10]={"todo","doing","done"};
	for(i=0;i<cpt;i++){
		if(TableauTaches[i].id==t.id){
			printf("Veuillez saisir le statut: 1. A realiser, 2. En cours de realisation, 3. Finalisation. ");
		    int x;
		    scanf("%d",&x);
		    if(x==1)
		    	strcpy(TableauTaches[i].statut,stat[0]);
		    if(x==2)
		    	strcpy(TableauTaches[i].statut,stat[1]);
		    if(x==3)
		    	strcpy(TableauTaches[i].statut,stat[2]);
			n=1;
		}
		if(n==1){
			break;
		}
			
	}
	if(n==0){
		printf("\ncette tache n existe pas");
	}
}
// Fonction pour modifier le deadline d'une tache
void modifierTacheDeadline(Tache t){
	int i;
	int n=0;
	for(i=0;i<cpt;i++){
		if(TableauTaches[i].id==t.id){
			struct tm d=saisirDeadline();
			TableauTaches[i].deadline=mktime(&d);
			n=1;

		}
		if(n==1){
			break;
		}
	}
	if(n==0)
		printf("\ncette tache n existe pas");
}

// Fonction pour supprimer une tache par ID
void supprimerTache(int id){
	int i;
	for(i=0;i<cpt;i++){
		if(TableauTaches[i].id==id){
			TableauTaches[i]=TableauTaches[cpt-1];
			cpt--;
			break;
		}
	}
}

// Fonction pour rechercher une tache par ID
void rechercherTacheParId(int id){
	int i;
	int n=0;
	for(i=0;i<cpt;i++){
		if(TableauTaches[i].id==id){
			afficherTache(TableauTaches[i]);
			n=1;
		}
		if(n==1){
			break;
		}
	}
	if(n==0){
		printf("\nCe identifiant n existe pas\n");
	}
}
// Fonction pour rechercher une tache par TITRE
void rechercherTacheParTitre(char titre[]){
	int i;
    int n=0;
	for(i=0;i<cpt;i++){
		if(strcmp(TableauTaches[i].titre,titre)==0){
			afficherTache(TableauTaches[i]);
			n=1;
		}
		if(n==1){
			break;
		}
	}
	if(n==0){
		printf("\nCe titre n existe pas\n");
	}
}

// Fonction pour afficher le nombre de taches
void nombreDesTaches(){
	printf("\nle nombre des taches est %d\n",cpt);
}

// Fonction pour afficher les taches et le nombre total des taches complets
void afficherTachesComplet(){
	int i;
	int nbtache=0;
	for(i=0;i<cpt;i++){
		if(strcmp(TableauTaches[i].statut,"done")==0){
			afficherTache(TableauTaches[i]);
			nbtache=nbtache+1;
		}
	}
	printf("\n le nombre de tache complet est : %d",nbtache);
}
// Fonction pour afficher les taches et le nombre total des taches incomplets
void afficherTachesIncomplet(){
	int i;
	int nbtache=0;
	for(i=0;i<cpt;i++){
		if(strcmp(TableauTaches[i].statut,"doing")==0||strcmp(TableauTaches[i].statut,"todo")==0){
			afficherTache(TableauTaches[i]);
			nbtache=nbtache+1;
		}
	}
	printf("\n le nombre de tache incomplet est : %d",nbtache);
}

int differenceJour(Tache t) {
    time_t currentTime = time(NULL);
    double differenceInSeconds =(double)difftime(t.deadline, currentTime);

    int differenceInDays = (int)(differenceInSeconds / (60 * 60 * 24));

    return differenceInDays;
}

void afficher3day(){
	int i;
	for(i=0;i<cpt;i++){
		if(differenceJour(TableauTaches[i])<=3){
			afficherTache(TableauTaches[i]);
		}
	}
}

// Fonction pour trier les taches par titre
void trierTacheAlpha() {
    Tache tmp;
    int i,j;

    for (i = 0; i < cpt; i++) {
        for (j = i + 1; j < cpt; j++) {
            if (strcmp(TableauTaches[i].titre, TableauTaches[j].titre) > 0) {
                tmp = TableauTaches[i];
                TableauTaches[i] = TableauTaches[j] ;
                TableauTaches[j]  = tmp;
            }
        }
    }

}
// Fonction pour trier les taches par deadline
void trierTacheDeadline() {
    Tache tmp;
	int i,j;
    for (i = 0; i < cpt; i++) {
        for (j = i + 1; j < cpt; j++) {
            if (TableauTaches[i].deadline > TableauTaches[j].deadline) {
                tmp = TableauTaches[i];
                TableauTaches[i] = TableauTaches[j] ;
                TableauTaches[j]  = tmp;
            }
        }
    }
}
// Fonction pour ajouter le nombre de jours restant pour chaque tache
void affiche_jour_rest(){
	int i=0;
	for(i=0;i<cpt;i++){
		printf("Le nombre de jours restants de la tache %d est %d\n",i+1,differenceJour(TableauTaches[i]));
	}
}
int main() {
    int choix;
    do {
        printf("\n===== Menu =====\n");
        printf("1. Ajouter une nouvelle tache\n");
        printf("2. Ajouter plusieurs taches\n");
        printf("3. Afficher la liste de toutes les taches\n");
        printf("4. Afficher les taches dont le deadline est dant 3 jours ou moin \n");
        printf("5. Modifier une tache\n");
        printf("6. Supprimer une tache par identifiant\n");
        printf("7. Trier la liste de toutes les taches\n");
        printf("8. Rechercher les Taches\n");
        printf("9. Statistiques\n");
        printf("10. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                AjouterTache();
                break;
            case 2:
                ajouterPlusieurs();
                break;
            case 3:
                afficherPlusieurTaches();
                break;
            case 4:
            	afficher3day();
            	break;
            case 5:
                printf("\nChoisissez une option de modification :");
                printf("\n1. Modifier la description d'une tache");
                printf("\n2. Modifier le statut d'une tache");
                printf("\n3. Modifier le deadline d'une tache\n");
                int modification;
                scanf("%d", &modification);
                Tache t;
                printf("\nEntrez l'identifiant de la tache à modifier : ");
                scanf("%d", &t.id);
                switch (modification) {
                    case 1:
                        modifierTache(t);
                        break;
                    case 2:
                        modifierTacheStatut(t);
                        break;
                    case 3:
                        modifierTacheDeadline(t);
                        break;
                    default:
                        printf("\nOption de modification invalide.\n");
                        break;
                }
                break;
            case 6:
                printf("\nEntrez l'identifiant de la tache a supprimer : ");
                int id;
                scanf("%d", &id);
                supprimerTache(id);
                break;
            case 7:
                printf("\nChoisissez une option de trie :");
                printf("\n1. Trier la liste des taches par Titre");
                printf("\n2. Trier la liste des taches par deadline\n");
                int tri;
                scanf("%d", &tri);
                switch (tri) {
                   case 1:
                        trierTacheAlpha();
                        printf("\nLa liste des taches apres le tri par TITRE.\n");
                        afficherPlusieurTaches();
                        break;
                   case 2:
                        trierTacheDeadline();
                        printf("\nLa liste des taches apres le tri par DEADLINE.\n");
                        afficherPlusieurTaches();
                        break;
                    default:
                        printf("\nOption de recherche invalide.\n");
                        break;
                }
                break;
            case 8:
                printf("\nChoisissez une option de recherche :");
                printf("\n1. Rechercher une tache par identifiant");
                printf("\n2. Rechercher une tache par titre\n");
                int recherche;
                scanf("%d", &recherche);
                switch (recherche) {
                    case 1:
                        printf("\nEntrez l'identifiant de la tache à rechercher : ");
                        int idRecherche;
                        scanf("%d", &idRecherche);
                        rechercherTacheParId(idRecherche);
                        break;
                    case 2:
                        printf("\nEntrez le titre de la tache a rechercher : ");
                        char titreRecherche[50];
                        scanf("%s", titreRecherche);
                        rechercherTacheParTitre(titreRecherche);
                        break;
                    default:
                        printf("\nOption de recherche invalide.\n");
                        break;
                }
                break;
            case 9:
                printf("\nChoisissez une option de statistiques :");
                printf("\n1. Afficher le nombre total des taches");
                printf("\n2. Afficher le nombre de taches completes et incompletes");
                printf("\n3. Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");
                int statistiques;
                scanf("%d", &statistiques);
                switch (statistiques) {
                    case 1:
                        nombreDesTaches();
                        break;
                    case 2:
                        afficherTachesComplet();
                        afficherTachesIncomplet();
                        break;
                    case 3:
                        affiche_jour_rest();
                        break;
                    default:
                        printf("\nOption de statistiques invalide.\n");
                        break;
                }
                break;
            case 10:
                printf("\nAu revoir !\n");
                break;
            default:
                printf("\nOption invalide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 10);
    return 0;
}
