1. Temps de calcul en séquentiel : 16.47s
   Temps de calcul en parallèle en utilisant 4 tâches MPI (découpage static), 2 threads OMP par tâche : 4.81s
	-le speed-up est égal à 3.42
   Temps de calcul en parallèle en utilisant le TBB:
   	-avec un partitioneur simple : 4.18s
	-avec un auto-partitioneur : 4.48s
	-avec un partitioneur static : 6.01s

2. Temps de calcul en séquentiel : 3.78s
   Temps de calcul en parallèle :
   	-avec un partitioneur simple : 1.05s
	-avec un auto-partitioneur : 0.96s - le meilleur resultat
   	-avec un partitioneur static : 0.97s
