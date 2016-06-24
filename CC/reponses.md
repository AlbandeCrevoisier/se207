---
lang      : fr
title     : Contrôle de connaissances SE207 "SystemC"
date      : 24 juin 2016
---

# Instructions

Ce contrôle de connaissances est strictement individuel.
Vous devez modifier ce fichier pour y inclure vos réponses. Seules les parties entre *---* sont à modifier.

# Questions

### Question 1

En SystemC, pour représenter une donnée signée sur 32bits vous pouvez utiliser l'un des types suivants:

- `unsigned int32_t` (`unsigned int`),
- `sc_int<32>`
- `sc_bv<32>`
- `sc_lv<32>`

Quels critères vous feraient choisir un type plutôt qu'un autre?

---

 `int32_t` : comme c'est un type natif du C++, on profite des avantages de vitesse et de simplicité d'utilisation du type,
 par contre on ne peut pas faire de sélection de bits facilement.
 `sc_int<32>` : pratiques pour de la sélection de bits etc, mais permet tout de même de faire de l'arithmétique etc.
 `sc_bv<32>` : adapté pour accéder à des éléments, i.e. bit ou plage de bits, mais ne permet pas de faire d'arithmétique.
 `sc_lv<32>` : pareil que pour `sc_bv`, sauf que ce type autorise les états X  et Z en plus.

---

### Question 2

Pourquoi ne peut-on pas connecter *directement* la sortie d'une module (par exemple `sc_out<bool> o`)  à l'entrée d'un autre module (par exemple `sc_in<bool> i`)?

---

Les sorties et entrées du module sont des port, pas des signaux, il faut donc connecter les ports avec des signaux.
Cela paraît cohérent de ne pas avoir une transmission instantanée des données entre deux modules quand on modélise
du matériel.

---

### Question 3

- Pourquoi doit-on avoir une boucle infinie dans un `SC_THREAD`?
- Que se passe-t-il s'il n'y a pas cette boucle?

---

Un `SC_THREAD` est lancé lors du start(), s'il s'arrête, il n'est pas possible de le relancer. On fait donc une boucle infinie pour garder
le thread vivant (comme un bump sur 4chan, en fait). Sans cette boucle, tout return stoppera définitivement le thread.

---

### Question 4

Nous voulons modéliser un bloc matériel synchrone (à une horloge `clk`) dans lequel une étape de traitement doit attendre le passage à `true` d'un signal de validation `start`.
Pour ce fait, on utilise un `SC_THREAD` sensible au seul front montant de l'horloge (`sensitive << clk.pos();`).

Nous proposons les deux implémentations suivantes pour cette attente (le reste du code n'est pas montré):

**Version 1**
```{.cpp}
 …
 // attente du passage à 1 de start
 wait(start.posedge_event());
 // passage à l'étape suivante
 …
```

**Version 2**
```{.cpp}
 …
 // attente du passage à 1 de start
 while(!start)
    wait();
 // passage à l'étape suivante
 …
```

- Expliquez brièvement la différence de comportement entre ces deux versions.
- Pourquoi choisiriez-vous l'une par rapport à l'autre?

```

---

La première version attend un `sc_event`, à savoir le passage à 1 de start. Dès que start passera à 1,l'event sera notify et l'exécution
avancera. Le wait n'est donc stoppé que sur passage de start à 1.
Dans la seconde version, le bloc est réveillé à chaque événement de la liste de sensibilité du module. Le while regarde ensuite quel
était cet event, et si c'état start qui est encore à 1, alors l'exécution continue.
Je ne vois pas pourquoi réveiller la boucle à chaque event, je prendrais donc la première version.

---


### Question 5

- Pourquoi devons-nous prendre des précautions quand nous utilisons une `sc_fifo` dans une `SC_METHOD`?


---

`sc_fifo` utilise des wait(), ce qui est interdit dans un `SC_METHOD` puisque ce thread doit s'exécuter entièrement à chaque appel
(event de la liste de sensibilité). Ainsi, un wait() bloquerait l'exécution, mais le thread ne rend jamais la main puisqu'il doit
s'exécuter en entier, programme bloqué.
Donc, `sc_fifo` et `SC_METHOD` ne font pas bon ménage.

---


/!\ Attention /!\
=================

Ne sachant pas que nous ne pouvions pas utiliser le cours, je l'ai regardé pour vérifier le problème avec les
`sc_fifo` et les `SC_METHOD`. Honnêtement, je ne savais pas que les méthodes des fifo utilisent des wait et n'aurais
donc probablement pas pu répondre à cette question (bon, c'est le principal soucis avec les `SC_METHOD`, donc
j'aurais tout de même cherché dans cette direction.

Bref, je voulais le signaler pour des questions d'honnêteté intellectuelle.

Merci, et bonne correction.
