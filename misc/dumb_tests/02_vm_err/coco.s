.name "coco"
.comment "et titi"

# Store indirect
# p1 -> registre = num de registre = 1 octet
# p2 -> tout
# p3 -> direct (2 octets) et regristre (1 octet)

# prend valeur dans r1, la met à l'adresse PC + 1 + 10
sti r1, %1, %10

# binaire original : coco.cor
# OCP original : 01 10 10 00 -> 0x68
# prog original : 0b 68 01 0001 000A

# Test 1
# changer l'OCP pour que p1 soit une direct de valeur 1
# -> checker si la VM de zaz considère cette valeur (1) comme le numéro de registre
# malgré que ce soit une direct, bref est ce que la VM de zaz fait quand mm le sti
# fichier : test1.cor
# OCP modifié : 10 10 10 00 -> 0xa8
# prog modifié : 0b a8 0001 0001 000A
# (modifier taille de prog : 07 -> 08)

# Test 1 - bis
# Pareil
# fichier : test1bis.cor
# OCP modifié : 10 10 10 00 -> 0xa8
# prog modifié : 0b a8 01 0001 000A

# Test 1 - ter
# Pareil
# fichier : test1bis.cor
# OCP modifié : 10 10 10 00 -> 0xa8
# prog modifié : 0b a8 00000001 0001 000A

# Test 2
# changer l'OCP en mettant un 4eme parametre, ne rien toucher aux autres
# -> checker si la VM voit qu'il y a un OCP faux (bien que ce soit correct pour
# les 3 premiers parametres)
# fichier : test2.cor
# OCP modifié : 01 10 10 11 -> 0x6b
# prog original : 0b 6b 01 0001 000A
