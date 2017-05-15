.name "rdavila"
.comment "This is a comment"

l2:		fork %1
		sti r1, %:live, %1
		and r1, %1, r1

live:	live %1
		zjmp %:live
