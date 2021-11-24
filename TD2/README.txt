Temps de calcul (avec 4 processus):
	-en séquentiel : 38.91 s
	-avec un découpage statique : 24.21 s -> Speedup S(4) = 1.61
	-en utilisant la stratégie maître-esclave : 27.94 s -> Speedup S(4) = 1.39

Le speedup est moins élevé avec la stratégie maître-esclave qu'avec 
un découpage statique. Ce peut paraître contre-intuitif, mais il faut noter 
que dans le cas de stratégie maître-esclave on n'utilise que 3 noeuds pour 
faire des calculs, car un est dédier à la distribution des tâches
[ou, peut-être j'ai écris, simplement, le code inefficace et lent :)]

