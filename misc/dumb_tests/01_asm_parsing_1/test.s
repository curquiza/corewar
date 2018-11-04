.name "coco et titi"
.comment "yo"

#sti r1, %:live, %1		# -> label n'existe pas
#sti r1, r2, r3			# -> ok
#fork 12 				# -> parametre 0 invalide. Attend une valeur directe

#sti r1, 12, 12			# -> parametre 2 invalide. Ne prends pas de valeur indirect pour le param2 (mais pour le 1 oui !)
#sti r1, 12, %12		# -> ok

#ld 4,r5
#ld 4,r5					# identiques et sortent exactement les mêmes octets

toto:  live %1
ld :toto, r1
ld :toto, r1 				# identiques mais ne sortent pas exactement les même octets

