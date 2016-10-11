# TP1
### SIF-1015
> Dave Corbin

> Marco Guillemette

> Nicolas Boisvert

# Manuel

### Compiler
**Assurez-vous d'avoir le compilateur `gcc` pour pouvoir compiler** et déplacez vous dans le dossier `./src`

```
make
./linked_info
```

### Néttoyer le dossier de Travail
La commande suivante supprimera tous les fichiers compilé dans le dossier courant.
```
make clean
```

# Devis
Travail Pratique 1 (LINUX)
Concurrence et exclusion mutuelle : gestion de ressources partagées

En vous inspirant des utilitaires de gestion de membres d’un regroupement de professionnels en informatique linkedINFO et  d’une liste chaînée qui vous sont fournis dans le dossier `/exempleLinkedinINFO-A16` qui est disponible sur le site ftp de l’UQTR (`dmiftp.uqtr.ca/FMeunier/sif1015/exemples`) et sur le serveur [DMILinux.uqtr.ca](ftp://DMILinux.uqtr.ca) ainsi que  des notions de gestion du partage des ressources présentées en classe, vous devez implanter un programme permettant la gestion des échanges de messages entre membres de ce regroupement de professionnels en informatique. Ce programme devrait comporter les spécifications suivantes:


## Étape 1
Au départ, votre programme (`main()`) fait la lecture d’un fichier de transactions, dont le nom de fichier est passé en ligne de commande par l'usager. Le programme (`main()`) fait l’ouverture du fichier de transactions et fait la lecture de chaque transaction. Un thread est ensuite démarré pour traiter chaque transaction.  Chaque transaction contenue dans un fichier de transactions est sur une ligne individuelle du fichier de transactions (ex : `trans1.txt`).  Par exemple :

```
A rog ProgrammeurC DEC 1
A ben AnalysteSysteme BAC 5
A joe AdminReseau DEC 10
A jojo AnalysteSysteme BAC 6
A gigi AnalysteSysteme BAC 15
A jaja AdminReseau DEC 9
A jiji GestionnaireTI BAC 20
A fm AnalysteSysteme BAC 25
A bb AnalysteSecurite BAC 25
A mm ProgrammeurC DEC 4
A kk GestionnaireTI BAC 25
A titi AnalysteSecurite BAC 17
A rig ProgrammeurC BAC 25
L C 1-15
M 2 tiben AnalysteSysteme BAC 5
L C 1-15
T PG tiben AnalysteSysteme  Je cherche un analyste specialiste des structures de donnees avec au moins 15 ans d'experience
T PP gigi ben Je vous transmet mon CV
L SE AnalysteSysteme 10-20
L S GestionnaireTI
L SF ProgrammeurC BAC
L SFE AnalysteSecurite BAC 15-20
E titi
L C 1-15
```
## Étape 2
Chaque ligne d’un fichier de transactions commence par une lettre qui représente le type de transaction à effectuer.

### A (Ajout)
Pour l’ajout d’un membre  du regroupement LinkedINFO, en spécifiant son nick (unique), sa spécialité, sa formation et  son expérience,

### M (Modification)
Pour la modification des informations d’un  membre, en spécifiant le numéro de nœud à modifier, le nouveau nick, la nouvelle spécialité, la nouvelle formation et la nouvelle expérience,

### E (Elimination)
Pour l’élimination (sortir) un membre  en spécifiant son nick,

### L (Lecture)
Pour l’affichage à la console des informations des membres selon les options suivantes :
- `C` pour l’affichage complet des informations des membres dont le numéro de nœud est spécifié dans un intervalle
- `T` pour la transmission d’un message texte provenant d’un membre à acheminer aux membres ayant une spécialité donnée  (option `PG`) ou acheminé à un autre membre (option `GG`).

## Étape 3
Votre programme (`main()`) crée une liste chaînée devant contenir la liste des membres. Chaque nœud de cette liste correspond à une structure de la forme :

```c
struct noeud {
	struct infoMembre membre;
	struct noeud* suivant;
}
```

La structure infoMembre correspond:

```c
struct infoMembre {
	char ptrNick[100];
	char ptrSpecialite[100];
	char ptrFormation[100];
	int Experience;
}
```

## Étape 4

Étant donné que la liste chaînée des membres de groupes du regroupement LinkedINFO  est une structure pouvant être partagée par plusieurs threads pouvant ainsi causer des problèmes d’intégrité au niveau des informations contenues dans les nœuds de la liste chaînée. Il faut donc éviter que l’accès à chaque nœud de cette structure se fasse de façon simultanée par plusieurs threads, l’accès à chaque nœud de la liste chaînée doit être restreint à un seul thread à la fois. De plus, l’accès au pointeur de tête et de queue devra aussi être en exclusion mutuelle.

### Contraintes de la partie 1 (10 points):
Le rapport de ce travail doit être remis le  **1 novembre 2016**.  La correction du travail est basée sur les critères suivants :

#### Fonctionnement des programmes 50 %
Programmes (code du `main()`, codes des procédures, fichier en-tête, makefile)

#### Style de programmation 50 %
(modularité, documentation, indentation, utilisation de constantes, efficacité des programmes, validation, originalité)

### Documents à remettre :
Vous devez déposer un manuel d’utilisateur de votre application sur le portail de cours, incluant votre Username, Password sur le serveur DMILinux ainsi que le chemin pour accéder à votre dossier TP1, le nom du fichier exécutable et le nom du fichier de transactions utilisé pour tester votre application.
