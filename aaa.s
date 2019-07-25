.name "aaaa"
.comment "aaaaaaaa"

trap:	st	r1,0
		ld	-5,r1	# hohoho

st	r1,6

a:		live	%0
		st	r1,13		#if line 13 is a comment
#		st	r1,16		#if line 13 is not a comment
		ld	%0,r2
#		fork	%:a

b:		live	%0
#		fork	%:b
		ld	%0,r2
		zjmp	%:a
