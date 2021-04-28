#README0: Programme "codiDeco"
codiDeco demande l'entrée d'un char, puis il le codifie, lui met du bruit, le décodifie et l'affiche en écran avec un diagnostique.

Le bruit est choisi  par l'utilisateur comme un nombre de bits à changer sur le octet d'un codeword.

## Utilisation du programme

### 0.- Préface
codideco.c travaille avec: n=8, k=4, g(x)=x^4+x+1, mais pas avec des matrices.
   
Dans le fichier: restes8_1e.h il y a les restes des codeWords avec 1 erreur dans chaque bit.

Ne pas modifier!

### 1.-Compiler avec:

```bash
make all
```

### 2.-Démarrer avec:

```bash
./codideco <typeRuid>
```
où typeRuid: 0, 1 , 2 , nf, qui signalent 0, 1 , 2 ou <nf> bits de change par char (0 <= nf0 <= 8)

Ex. ./codideco 1


### 3. Le programe en fonctionnement
#### A-Le programme demande:

```bash
	Entrez symbole (1 char) s.v.p?. (terminer processus avec CONTROL D)
	

	Entrez par exemple:

	k
```

#### B-Le programme affiche en écran:

```bash
___________________________________________________________
_________________________________________________________
	avant medium code entrée nibble bas   10111110
	après medium code entrée nibble bas   11111110
	avant medium code entrée nibble haut  01101010
	après medium code entrée nibble haut  00101010
	char entrée;   01101011
	char recupéré; 01101011
	message originel:  k
	message recupéré: k
___________________________________________________________
 erreur en 1 bit dans deux codes et corrigé
___________________________________________________________
Entrez symbole  (1 char) s.v.p... (terminer avec CONTROL D)
```
et puis il revient à A.

#### C-Pour changer le nombre de bits d'erreur, il est nécessaire de terminer et commencer avec autre typeRuid.

Redémarrer le programme