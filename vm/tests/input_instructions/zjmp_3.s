.name "zjmp_3"
.comment "test carry"

and %0, %0, r42		# invalid reg. Will the carry change anyway ? No it won't
zjmp %36
