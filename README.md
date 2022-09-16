# Algorithm

Acest proiect a fost realizat pentru a vizualiza grafic căutarea unui drum într-un tablou bidimensional folosind doi algoritmi elementari de căutare:                
+ BFS (Breadth-First Search)
+ DFS (Depth-First Search)

Dimensiunile tabloului bidimensional sunt: 22 de linii si 52 de coloane.  
Proiectul își propune să arate eficiența si complexitatea algoritmilor, fiecare având avantaje și dezavantaje în funcție de:
+	configurația tabloului bidimensional 
+	poziția de început 
+	poziția de sfârșit

<br />

# Tehnologiile folosite

Pentru realizarea proiectului am folosit:
+	C++
+	OpenGL 
+	FreeType

<br />

# Definirea simbolurilor folosite

<p align="center">
  <img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/Path.png">
</p>

Simbol  | Descriere
------------------------------------------------------------------------------------- | -------------
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/StartPoint.png">  | Punctul de început
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/EndPoint.png">    | Punctul de sfârșit
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/BlackBlock.png">  | Pătrat liber, care poate fi parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/GreenBlock.png">  | Pătrat ocupat, care nu poate fi parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/RedBlock.png">    | Pătrat parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/PinkBlock.png">   | Pătratul face parte din drumul determinat de algoritm

<br />

# Controlul programului

Click stânga pentru a adăuga un pătrat verde sau pentru a acționa unul dintre butonele din interfața programului  
Click dreapta pentru a șterge unul dintre pătratele verzi  

<br />

# Funcționalitate

Utilizatorul trebuie să aleagă una dintre cele două metode de a găsi un drum (BFS sau DFS) și să configureze următorii parametrii: începutul, respectiv sfârșitul drumului și pătratele care pot fi parcurse de algoritm. Cu toate aceste informații algoritmul va rezolva configurația labirintului și va afișa utilizatorului pătratele parcurse pentru determinarea drumului și soluția găsită pentru a ajunge la destinație din punctul de pornire. În cazul în care nu poate fi găsit un drum, programul va afișa doar pătratele parcurse.


<br /> <br />
<p align="center">
  <img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/draw.gif">
</p>

<br /> <br />

### BFS                       DFS
<img align="left" src="https://github.com/sebimih13/Algorithm/blob/main/Resource/BFS.gif">
<img align="right" src="https://github.com/sebimih13/Algorithm/blob/main/Resource/DFS.gif">

