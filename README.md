# 🎨 Projet C - Gestionnaire et Éditeur SVG (`.svcp`)

Application en **C natif** permettant la création, l'édition, la visualisation et la persistance de formes graphiques vectorielles de type SVG, structurées autour d'un format de sauvegarde personnalisé (`.svcp`) et d'une gestion récursive des groupes.

---

## 🚀 Fonctionnalités principales

- **Gestion complète des formes (CRUD)** : Lignes, Cercles, Ellipses, Carrés, Rectangles, Lignes Multiples, Polygones et Chemins (`Path`) avancés.
- **Groupes récursifs** : Organisation des formes en groupes imbriqués avec des transformations (translation, rotation).
- **Format de persistance personnalisé (`.svcp`)** : Format texte optimisé, séquentiel et rapide, gérant l'intégrité des listes chaînées et des commandes de chemins (M, L, C, S, Q, T, Z).
- **Module de sauvegarde intelligent** : Gestion automatique d'un dossier `save/`, vérification de l'unicité des noms de fichiers et prise en charge de l'écrasement de la sauvegarde active.
- **Visualisation cross-platform** : Aperçu rapide du projet depuis l'application.

---

## 📂 Structure du Projet

```text
.
├── code/
│   ├── main.c          # Point d'entrée et menu principal
│   ├── create_form.c   # Logique de création des formes
│   ├── edit_form.c     # Édition et modifications (ex: miroirs)
│   ├── view.c          # Visualisation du projet
│   ├── quit.c          # Nettoyage et gestion de la sortie
│   ├── save.c          # Module de sérialisation et écriture .svcp
│   └── load.c          # Module de chargement et parsing .svcp
├── bin/                # Dossier de génération des fichiers objets (.o)
├── save/               # Répertoire de stockage des projets .svcp
├── Makefile            # Fichier de compilation automatisée
└── README.md
```
---

## 📥 Clonage du projet

Pour cloner le dépôt sur ta machine, exécute la commande suivante :

```bash
git clone [https://github.com/lixis-code/projet.git](https://github.com/lixis-code/projet.git)
cd projet
```

--- 

## ⚙️ Prérequis et Compilation

Le projet utilise uniquement la bibliothèque standard C et se compile à l'aide d'un Makefile strict (-Wall -Wextra -Werror).

Pour compiler le projet, exécute la commande suivante dans ton terminal : make build
Pour nettoyer les fichiers objets et l'exécutable : make clean

---

## 🕹️ Utilisation

Une fois compilé, lance l'exécutable : ./projet

Le menu interactif te permettra de :

1. Ajouter des formes à la scène principale ou aux groupes.

2. Éditer le projet (transformations, symétries/miroirs, etc.).

3. Sauvegarder le projet dans le dossier save/ (avec gestion d'écrasement si le fichier est déjà actif).

4. Charger un projet existant en sélectionnant un fichier parmi la liste disponible.

5. Visualiser le rendu du projet.

--- 

## 🔗 Lien du dépôt

Retrouve le code source complet sur GitHub :

https://github.com/lixis-code/projet.git

---

## 👤 Auteur

Vayssiere Alexis

École : Coda