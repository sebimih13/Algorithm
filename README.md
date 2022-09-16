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
+	OpenGL - [GLFW](https://www.glfw.org/) compiled from source code
+	OpenGL Mathematics - [GLM](https://glm.g-truc.net/0.9.9/index.html)
+	[GLAD](https://glad.dav1d.de/)
+	[FreeType](https://freetype.org/)

<br />

# Definirea simbolurilor folosite

<p align="center">
  <img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/Path.png">
</p>

Simbol  | Descriere
------------------------------------------------------------------------------------- | -------------
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/Start.PNG">  | Punctul de început
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/End.PNG">    | Punctul de sfârșit
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/BlackBlock.PNG">  | Pătrat liber, care poate fi parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/GreenBlock.PNG">  | Pătrat ocupat, care nu poate fi parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/RedBlock.PNG">    | Pătrat parcurs de algoritm
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/PinkBlock.PNG">   | Pătratul face parte din drumul determinat de algoritm

<br />

# Controlul programului

Click stânga pentru a adăuga un pătrat verde sau pentru a acționa unul dintre butonele din interfața programului  
Click dreapta pentru a șterge unul dintre pătratele verzi  

Actiune  | Descriere
------------------------------------------------------------------------------------- | -------------
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/MouseLeftKey.png">  | Click stânga pentru a adăuga un pătrat verde sau pentru a acționa unul dintre butonele din interfața programului 
<img src="https://github.com/sebimih13/Algorithm/blob/main/Resource/MouseRightKey.png">    | Click dreapta pentru a șterge unul dintre pătratele verzi  

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

