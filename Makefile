salida_out = labhilos


salida_headers = funciones.h
salida_source  = $(salida_headers:.h=.c) principal.c
salida_objects = $(salida_source:.c=.o)

CC     = gcc
CFLAGS = -Wall

depends = .depends

build : $(salida_out) 

$(salida_out) : $(salida_objects)
	$(CC) $(CFLAGS) -o $@ $^  -pthread -lm

$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(salida_source) $(salida_headers)
	@$(CC) -MM $(salida_source) > $@


clear :
	$(RM) $(salida_out) $(salida_objects) $(zipfile) $(depends)

.PHONY : build zip clean

sinclude $(depends)
