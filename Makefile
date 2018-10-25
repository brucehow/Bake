# Make file for Bake

C99 = cc -std=c99 -Werror -Wall -pedantic -o bake
DEPENDENCIES = append.c bake.c curl.c expandvar.c filedate.c main.c process.c readfile.c targets.c variables.c

Bake : $(DEPENDENCIES)
	@$(C99) $(DEPENDENCIES)
	@echo "make: 'Bake' successfully built."
clean :
	rm -f bake
