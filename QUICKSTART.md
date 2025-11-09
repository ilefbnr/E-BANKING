# 🚀 Guide de Démarrage Rapide - E-Banking

## 📦 Installation et Compilation

```bash
# Compiler le projet
make clean && make

# Exécuter
./bin/ebank
```

## 🎯 Scénario de Test Complet

### 1️⃣ Mode Utilisateur - Créer des Comptes

```
Menu Principal → 1 (Mode Utilisateur)

1. Créer un compte
   Nom: Alice
   → Compte ACC001001 créé

1. Créer un autre compte  
   Nom: Bob
   → Compte ACC001002 créé

9. Retour
```

### 2️⃣ Effectuer des Opérations

```
Menu Principal → 1 (Mode Utilisateur)

3. Déposer de l'argent
   Compte: ACC001001
   Montant: 5000

3. Déposer de l'argent (encore)
   Compte: ACC001002
   Montant: 3000

7. Transférer de l'argent
   Compte source: ACC001001
   Compte destinataire: ACC001002
   Montant: 500

8. Générer un relevé
   Compte: ACC001001
   → Fichier releve_ACC001001.txt créé

9. Retour
```

### 3️⃣ Mode Admin - Gestion Avancée

```
Menu Principal → 2 (Mode Admin)
Username: admin
Password: admin123

1. Voir tous les comptes
   → Affiche Alice et Bob

7. Appliquer les intérêts
   → Option 2 (tous les comptes)
   → Intérêts appliqués

8. Sauvegarder les données
   → Option 1 (Sauvegarder)
   → Données sauvegardées dans data/

9. Retour
```

### 4️⃣ Quitter et Relancer

```
Menu Principal → 3 (Quitter)
→ Sauvegarde automatique

# Relancer le programme
./bin/ebank

→ Toutes les données sont rechargées ! ✅
```

## 📁 Fichiers Générés

Après utilisation, vous trouverez :

```
data/
├── accounts.csv          # Tous les comptes
├── transactions.csv      # Toutes les transactions
└── admins.csv           # Administrateurs

releve_ACC001001.txt     # Relevé du compte Alice
releve_ACC001002.txt     # Relevé du compte Bob (si généré)
```

## 🔧 Commandes Utiles

```bash
# Compiler
make

# Nettoyer et recompiler
make clean && make

# Exécuter
make run
# OU
./bin/ebank

# Voir les données CSV
cat data/accounts.csv
cat data/transactions.csv

# Voir un relevé
cat releve_ACC001001.txt
```

## 🎓 Fonctionnalités Principales

### Mode Utilisateur
1. ✅ Créer un compte
2. ✅ Consulter mon compte
3. ✅ Déposer de l'argent
4. ✅ Retirer de l'argent
5. ✅ Consulter le solde
6. ✅ Voir l'historique
7. ✅ **Transférer de l'argent** (NOUVEAU)
8. ✅ **Générer un relevé** (NOUVEAU)

### Mode Admin
1. ✅ Voir tous les comptes
2. ✅ Consulter un compte
3. ✅ Fermer un compte
4. ✅ Réactiver un compte
5. ✅ Ajouter un administrateur
6. ✅ Historique d'un compte
7. ✅ **Appliquer les intérêts** (NOUVEAU)
8. ✅ **Sauvegarder/Charger données** (NOUVEAU)

## ⚠️ Points Importants

1. **Persistence Automatique**
   - Données sauvegardées à la fermeture
   - Données chargées au démarrage

2. **Admin par Défaut**
   - Username: `admin`
   - Password: `admin123`

3. **Taux d'Intérêt**
   - 3% annuel
   - Calculé au prorata des jours

4. **Formats de Fichiers**
   - CSV pour les données
   - TXT pour les relevés

## 🐛 Dépannage

### Erreur "Impossible de créer data/"
```bash
mkdir data
chmod 755 data
```

### Fichiers CSV corrompus
```bash
rm -rf data/
# Relancer le programme
```

### Relevés non générés
Vérifiez les permissions d'écriture :
```bash
ls -la
chmod 644 releve_*.txt
```

## 📞 Support

Pour plus de détails, consultez :
- `README.md` : Documentation générale
- `FEATURES.md` : Nouvelles fonctionnalités détaillées
- `.github/copilot-instructions.md` : Instructions techniques

---

**🎉 Bon développement avec E-Banking !** 🏦
