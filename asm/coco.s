.name "zork"  
.comment "I'M ALIIIIVE"

coco:
		sti r1, %:live,
		and r1, %0, r1

live:	live %1
		zjmp %:live
