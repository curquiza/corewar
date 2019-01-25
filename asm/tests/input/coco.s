.name "zork"  
.comment "I'M ALIIIIVE"

titi: live %1
coco: live %:titi
lulu: live %2147483647
live %2
ld :coco        ,r8
ld %2147483647        ,r8
