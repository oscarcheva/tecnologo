

# --------------------------------------------------------------------
#  Makefile de tarea 1.

#  Obligatorio EDA.
#  UTU-Latu-Turno Nocturno

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega claves

ARCHIVO_ENTREGA=Entrega1.tar.gz

ENTREGAR = linea cadena version archivo


MODULOS = $(ENTREGAR) utils 

# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

INDIR     = test
OUTDIR    = test
SALIDADIR = test/salidas


# extensión de los archivos
EXT = cpp
# compilador
CC = g++ # gcc -x c 
LD = g++ # gcc

# opciones de compilación
# para que los assert tengan efecto 
#CCFLAGS = -Wall -Werror -I$(HDIR) -g

# para que los assert NO tengan efecto y no impacten en el tiempo de ejecución
CCFLAGS = -Wall -Werror -I$(HDIR) -g -DNDEBUG



# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.$(EXT))
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal


ARCHIVO_CLAVES=claves.txt
COMANDO_CLAVES=shasum


# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).$(EXT)
	@printf 'Compilando $(<) \n'; \
	$(CC) $(CCFLAGS) -c $< -o $@




$(ODIR)/%.o: $(CPPDIR)/%.$(EXT)  $(HDIR)/%.h
	@printf 'Compilando $(<) \n'; \
	$(eval resced = $(shell grep -E '/\*[[:blank:]]*[[:digit:]]{7}[[:blank:]]*\*/' $<)) \
	$(eval resr = $(shell grep -n -P '_rep_(?!$(basename $(notdir $<)))' $<)) \
	$(eval resh = $(subst #,\#,$(shell grep -n -P 'include(?!.*[.]h)' $< ))) \
	if [ -n "$(resced)" ] && [ -z "$(resr)" ] && [ -z "$(resh)" ];  \
	then $(CC) $(CCFLAGS) -c $< -o $@ ; \
	else \
		if [ -z "$(resced)" ]; then printf ' No incluye cedula.\n' ; fi ; \
		if [ -n "$(resh)" ]; then printf '  Include de archivos que no son .h:\n' ; printf '  "$(resh)"\n' ; fi ; \
		if [ -n "$(resr)" ]; then printf '  Uso de representación de otros tipos:\n' ; printf '  "$(resr)"\n' ; fi ; \
		printf '    NO SE COMPILO $(<)\n' ; \
		rm -f $@; \
	fi;



# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE):$(ODIR)/$(PRINCIPAL).o $(OS)
	@printf 'Compilando y enlazando $(@) \n'; \
	$(LD) $(CCFLAGS) $^ -o $@

# casos de prueba
CASOS = 11 12 13 14 21 22 23 24 A B C D E F


# cadena de archivos, con directorio y extensión
INS=$(CASOS:%=$(INDIR)/%.in)
OUTS=$(CASOS:%=$(OUTDIR)/%.out)
SALS=$(CASOS:%=$(SALIDADIR)/%.sal)
DIFFS=$(CASOS:%=$(SALIDADIR)/%.diff)

$(SALS):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(SALIDADIR)/%.sal:$(INDIR)/%.in
	-timeout 4 ./$(EJECUTABLE) < $< > $@ 2>&1
	@if [ $$(stat -L -c %s $@) -ge 20000 ]; then \
		echo "tamaño excedido" > $@;\
	fi

# test de tiempo
$(SALIDADIR)/t-%.sal:$(INDIR)/t-%.in
	-timeout 10 ./$(EJECUTABLE) < $< > $@ 2>&1


%.diff:Makefile
# cada .diff depende de su .out y de su .sal
$(SALIDADIR)%.diff: $(OUTDIR)%.out $(SALIDADIR)%.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior.
# En el caso de `diff', si los dos archivos comparados no son iguales,
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.



# crea las reglas t-caso, y cada una depende del ejecutable
tS=$(CASOS:%=t-%)
$(tS):$(EJECUTABLE)

# corre el ejecutable con el .in (el primer prerequisito $<) y lo guarda en un archivo temporal
# hace el diff entre el -out (el segundo prerequisito, echo $(word 2,$^)) y el archivo temporal
# borra el archivo temporal
t-%:$(INDIR)/%.in $(OUTDIR)/%.out
	@timeout 4 ./$(EJECUTABLE) < $< > $@tmp;  \
	diff `echo $(word 2,$^)` $@tmp ; \
	if [ $$? -eq 0 ];                                         \
	then                                                      \
		echo ---- Bien ----;                              \
	fi;                                                       \
	rm -f $@tmp



# Test general. Las dependencias son los .diff.
# Con `find` se encuentran los .diff de tamaño > 0 que están en el directorio
# $(SALIDADIR) y lo asigna a $(LST_ERR).
# Si el tamaño de $(LST_ERR) no es cero imprime los casos con error.
# Con `sed` se elimina el nombre de directorio y la extensión.
testing:all $(DIFFS)
	@LST_ERR=$$(find $(SALIDADIR) -name *.diff* -size +0c -print);          \
	if [ -n "$${LST_ERR}" ];                                                \
	then                                                                    \
		echo -- CASOS CON ERRORES --;                                   \
		echo "$${LST_ERR}" | sed -e 's/.*\///' -e 's/\..*//';           \
	fi;                                                                     \
	echo -- RESULTADO DE CADA CASO --;                                      \
	RES=;                                                                   \
	for caso in $(CASOS); do                                                \
		if [ 0 -eq $$(stat -c %s "$(SALIDADIR)/$${caso}.diff") ];       \
		then                                                            \
			RES=$${RES}1 ;                                          \
		else                                                            \
			RES=$${RES}0 ;                                          \
		fi;                                                             \
	done;                                                                   \
	echo $${RES}





# inlcuye la clave de cada archivo en $(ARCHIVO_CLAVES)
$(ARCHIVO_CLAVES):$(ENTREGAR:%=$(CPPDIR)/%.$(EXT))
	rm -f $@
	$(COMANDO_CLAVES) $(ENTREGAR:%=$(CPPDIR)/%.$(EXT)) > $@

claves:$(ARCHIVO_CLAVES)



# Genera el entregable.
CPPS_ENTREGA = $(ENTREGAR:%=%.$(EXT))
entrega:claves
	@rm -f $(ARCHIVO_ENTREGA)
	tar zcf $(ARCHIVO_ENTREGA) $(ARCHIVO_CLAVES) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ARCHIVO_ENTREGA)


# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS)

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(SALIDADIR)/*.sal $(SALIDADIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f $(ARCHIVO_ENTREGA) $(ARCHIVO_CLAVES) *~ $(HDIR)/*~ $(CPPDIR)/*~ $(INDIR)/*~ $(OUTDIR)/*~



check-syntax:
	gcc -o nul -S ${CHK_SOURCES}


LIB = tarea.a
$(LIB):	$(ODIR)/utils.o $(ODIR)/info.o $(ODIR)/$(PRINCIPAL).o
	ar -qc $@ $^	



