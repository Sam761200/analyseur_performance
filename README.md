# Analyseur de Performance Système
## Description
Ce programme en C est conçu pour fournir une surveillance en temps réel des principales métriques de performance d'un système Debian. Il mesure et affiche l'utilisation du CPU, la mémoire, l'activité du disque, et l'utilisation du réseau.

## Fonctionnalités
Utilisation du CPU : Affiche le pourcentage d'utilisation du CPU.

Utilisation de la mémoire : Montre la mémoire totale, utilisée et le pourcentage d'utilisation.
Activité du disque : Rapporte les lectures et écritures pour chaque périphérique de disque.

Utilisation du réseau : Indique les données reçues et transmises pour chaque interface réseau.

## Installation
### Prérequis

Un système Debian ou compatible.
GCC pour compiler le code source.
### Compilation
Clonez ce dépôt sur votre machine locale en utilisant la commande suivante :

```bash
git clone https://github.com/Sam761200/analyseur_performance.git
```

Naviguez dans le répertoire du projet, puis compilez le code source :

```bash
cd analyseur_performance
gcc analyseur.c -o performance_analyzer
```
Utilisation
Exécutez le programme compilé avec la commande :

```bash
./performance_analyzer
```
Le programme affichera les statistiques de performance mises à jour toutes les secondes. Pour arrêter l'exécution, utilisez CTRL+C.

## Contributions
Les contributions à ce projet sont les bienvenues. Vous pouvez contribuer de plusieurs façons :

Améliorations du Code : Proposez des améliorations pour le code existant.

Nouvelles Fonctionnalités : Ajoutez de nouvelles fonctionnalités ou étendez les fonctionnalités existantes.

Rapports de Bugs : Signalez les bugs rencontrés lors de l'utilisation du programme.
Pour contribuer, veuillez soumettre une pull request ou ouvrir un problème dans le dépôt GitHub.

## Licence
Ce projet est distribué sous la licence MIT. Voir le fichier LICENSE pour plus d'informations.
