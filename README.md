# Descriere Fișiere de Test - FixItNow

Acest folder conține fișierele de intrare utilizate pentru validarea funcționalităților aplicației și testarea cazurilor limită.

## 1. modele.txt
**Rol:** Definește catalogul de electrocasnice suportate de service.
**Scenariu:** Conține o listă diversă de mărci și modele (Samsung, Arctic, Whirlpool, etc.). Orice cerere pentru un model care nu se află în acest fișier va fi respinsă automat de aplicație.

## 2. angajati.txt
**Rol:** Inițializează lista de angajați și testează validările la citire.
**Cazuri testate:**
* **Angajați Valizi:** Conține 3 Tehnicieni, 1 Recepționer și 1 Supervizor (minimul necesar pentru funcționare).
* **CNP Invalid (Lungime):** Linia cu `T,Scurt,CNP,123...` testează detecția CNP-urilor incomplete.
* **Vârstă Invalidă:** Linia cu `T,Prea,Mic,620...` testează regula de vârstă minimă (16 ani).
* **Tip Invalid:** Linia cu `X,Gresit...` testează respingerea caracterelor necunoscute pentru tipul angajatului.

## 3. specializari.txt
**Rol:** Asociază competențele tehnice fiecărui tehnician (legătura între CNP și Marca/Tipul aparatului).
**Cazuri testate:**
* **Competențe Multiple:** Unii tehnicieni au mai multe specializări (ex: TV și Frigider).
* **CNP Inexistent:** Ultima linie conține un CNP care nu există în `angajati.txt`, pentru a verifica dacă aplicația ignoră corect liniile orfane.

## 4. cereri.txt
**Rol:** Simulează un flux de cereri din partea clienților pentru a testa motorul de alocare.
**Scenarii complexe:**
* **Sarcini "Grele":** Primele cereri sunt pentru aparate foarte vechi (anii 2010-2015) cu complexitate maximă (5). Acestea sunt menite să blocheze tehnicienii pentru o durată lungă în simulare.
* **Supraîncărcare (Coada de așteptare):** Fișierul conține mai multe cereri valide decât pot prelua tehnicienii simultan. Acest lucru forțează intrarea cererilor în coada de așteptare (`cereriAsteptare`) și demonstrarea alocării ulterioare, pe măsură ce tehnicienii se eliberează.
* **Model Nesuportat:** Cererea pentru "TV Nei Vechi" testează respingerea aparatelor care nu există în `modele.txt`.
* **Tehnician Indisponibil:** O cerere (ex: LG) pentru care nu există niciun tehnician cu acea specializare în `specializari.txt`, demonstrând că cererea rămâne în așteptare infinită (sau până la angajarea unui specialist).