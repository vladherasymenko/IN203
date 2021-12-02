1. Produit sclaire
-OpenMP
	1 processeur - temps : 0.46, speedup : 1, efficacité :  100%
	2 processeurs - temps : 0.24, speedup : 1.91, efficacité :  95.5%
	3 processeurs - temps : 0.19, speedup : 2.42, efficacité :  80.6%
	4 processeurs - temps : 0.16, speedup : 2.88, efficacité :  71.9%
-Threads C++
	1 thread - temps 0.89: 
	2 threads - temps 1.17: 
	3 threads - temps 1.46: 
	4 threads - temps 2.09: 
	8 threads - temps 3.81:  ???

2. Produit Matrice-Matrice
	1. N = 1023, MFlops = 122.6, t = 17.46s
	   N = 1024, MFlops = 112.7, t = 19.02s
	   N = 1025, MFlops = 122.8, t = 17.43s
	Cette différence est liée au fait que 1024 est le multiple de (16?) ce qui veut
	dire que, à chaque itération, les valeurs dans le cache seront remplacées l'application
	devient, donc, encore plus memory bound

	2. Avec la séquence k-j-i le code s'exécute plus vite : pour N = 1024, le temps
	d'exécution devient 17.37s avec 123.6 MFlops
	-Cet ordonnancement est le plus efficace, car on réutilise au maximum (parmi tous les
	pemutations) les valeurs déjà chargées dans le cache : en effet, puisqu'on itére sur "k"
	simultanément dans les matrices A et B (en même temps que "i" et "j" sont présent uniquement
	dans A et B, respectivement), si on transforme k en boucle principale, à chaque itération
	(dans la boucle la plus intérieure), seulement une valeure changera - on itére sur i dans 
	cette boucle-là pour prendre chaque fois des valeurs contigües. 

	3. En utilisant les outils de OpenMP, avec 4 threads le code s'exécute ~3.25 fois plus vite :
	pour N =1024, le temps nécaissaire de calcul est 5.15s avec 417 MFlops

	4. L'application est toujours memory bound, car il y a O(N^3) opérations ce qui est inférieure
	à O(3*N^2) lectures/écritures

	5.-6. En utilisant le découpage en blocs (sans parallélisation) pour N = 1024, j'ai obtenu le
	même résultat qu'en question 2, notemment : 17.24s avec 400 MFlops. C'est un résulata inattendu
	(et je crois que je me suis trompé dans le code), mais une explication possible pour cela est que 
	l'application n'est pas, en fait, memory bound pour N = 1024 sur ma machine.  [la taille des blocs = 128]

	7. Après avoir parallélisé le produit matrice-matrice par bloc, on obtient, encore une fois,
	le résultat juste légèrement qu'en question 3 : pour N =1024, le temps de calcul : 4.71s avec 454 MFlops

3. Temps d'exécution en séquentiel = 20.11s
		     en parallèle = 5.79s
   Donc, le speed-up est égal à 3.47 étant donné que ma machine possède 4 coeurs physiques. 
   (Le temps de calcul pour vecteurs est trop élevé j'y reviendrai plus tard)

4. Temps de calcul en séquenciel: 
	-Bhudda 1 : 4.18s
	-Bhudda 2 : 4.27s
	-Bhudda 3 : 0.27s
	-Ensemble : 8.72s

   Temps de calcul en parallèle sur 4 coeurs (physiques):
 	-Bhudda 1 : 1.57s
	-Bhudda 2 : 1.18s
	-Bhudda 3 : 0.08s
	-Ensemble : 2.83s
	Donc, en somme, le speed-up est égal à 3.08 ce qui est très proche de limite maximale de 4 (sur 4 processeurs)

