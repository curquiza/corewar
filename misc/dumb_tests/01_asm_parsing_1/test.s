.name "coco et titi"
.comment "yo"

#sti r1, %:live, %1		# -> label n'existe pas
#sti r1, r2, r3			# -> ok
#fork 12 				# -> parametre 0 invalide. Attend une valeur directe

#sti r1, 12, 12			# -> parametre 2 invalide. Ne prends pas de valeur indirect pour le param2 (mais pour le 1 oui !)
#sti r1, 12, %12		# -> ok

#ld 4,r5
#ld 4,r5					# identiques et sortent exactement les mêmes octets

#toto:  live %1
#ld :toto, r1
#ld :toto, r1 				# identiques mais ne sortent pas exactement les même octets

toto:  live %1
ld %:toto, r1
ld %:toto, r1 				# même idée et même logique que le test précédent, mais avec des directs = sur 4 octets

# Conclusion : l'asm s'en fout que ce soit des direct ou indirect, s'il voit %4
# ou 4 pour lui c'est la même chose, c'est juste qu'il va stocker sur 4 octets
# dans le premier cas et sur 2 octets dans le second.
# C'est la VM qui choisira d'utiliser la valeur 4 ou bien la valeur située à
# l'adresse PC + 4 (modulo blablabla)
