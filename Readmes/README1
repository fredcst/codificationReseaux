# README1: Programme "codi1"
Codi1, utilise le formalisme avec matrices G et H por trouver les codeWords et les syndromes du polynôme: x^4+x+1 avec n=8 et k=4.

## Utilisation du programme

### 0- (optionnel) Modifier headers/base.h pour changer: NN, KK, G, H
NN: taille de codeWords\
KK: taille de blocs\
G: matrice generatrice\
H: matrice des syndromes(dépend de G)

### 1.-Compiler avec:

```bash
make all
```

### 2.-Démarrer avec:

```bash
./codi1
```

### 3. Le programe en fonctionnement
#### A-Le programme demande:

```bash
Entrez une nombre binaire de 4 chiffres (0,1) (sans espaces). 
Exemple: 0011, S il vous plaît...

Les chiffres en excès ne seront pas considérés...

Entrez par exemple:
1010
```

Si le nombre a moins de 4 chiffres ou il est vide le programme affiche: "CHIFFRE avec erreurs", et demande à nouveau.

#### B-Le programme affiche en écran:

```bash
	Nombre: 1010
	MATRICE G:
	1 0 0 0 1 0 1 1 
	0 1 0 0 1 1 0 0 
	0 0 1 0 0 1 1 0 
	0 0 0 1 0 0 1 1 
	codeW: 10101101
	syndrome de codeW: 0000
```

#### C-Le programme demande:

```bash
Entrez une nombre binaire de 8 chiffres (0,1) (sans espaces). 
Exemple: 00110011, S il vous plaît...

Les chiffres en excès ne seront pas considérés...
	
Entrez par exemple:
11110000
```
Si le nombre a moins de 8 chiffres ou il y est vide le programme affiche: "CHIFFRE avec erreurs", et demande a nouveau.

#### D-Le programme affiche en écran:

```bash
MATRICE H:
	1 1 0 0 1 0 0 0 
	0 1 1 0 0 1 0 0 
	1 0 1 1 0 0 1 0 
	1 0 0 1 0 0 0 1 

	Code: 11110000
	Syndrome de code: 0010
	Code avec erreurs!!

	S il y a 1 erreur, ceci est dans le bit 6 du codeWord. [0...7]
	CodeWord avec 1 erreur:
	11110000
	CodeWord corrigé:
	11110010

	Ensemble complet de codeWords et leurs distance de Hamming: 
	11110010	d=5 
	01111001	d=5 
	10111110	d=6 
	00110101	d=4 
	11010100	d=4 
	01011111	d=6 
	10011000	d=3 
	00010011	d=3 
	11100001	d=4 
	01101010	d=4 
	10101101	d=5 
	00100110	d=3 
	11000111	d=5 
	01001100	d=3 
	10001011	d=4 
	00000000	d=0 
	Distance de Hamming de code: 3

	Ensemble de syndromes pour 1 erreur dans codeWord 0
---------------------------------------------------
codeWord 0: 11110010
11110010 01110010 1011
11110010 10110010 1100
11110010 11010010 0110
11110010 11100010 0011
11110010 11111010 1000
11110010 11110110 0100
11110010 11110000 0010
11110010 11110011 0001



```