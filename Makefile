#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geometrie main


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

conventions.o : conventions.c conventions.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module conventions"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

list_contour.o : list_contour.c list_contour.h conventions.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module list_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

list_bezier2.o : list_bezier2.c list_bezier2.h conventions.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module list_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

list_bezier3.o : list_bezier3.c list_bezier3.h list_bezier2.h conventions.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module list_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour.o : contour.c contour.h image.h geom2d.h conventions.h list_contour.h list_bezier2.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_Bezier.o : simplification_Bezier.c simplification_Bezier.h main.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_Bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_Bezier3.o : simplification_Bezier3.c simplification_Bezier3.h main.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_Bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main.o : main.c main.h contour.h image.h geom2d.h conventions.h list_contour.h list_bezier2.h simplification_Bezier.h list_bezier3.h simplification_Bezier3.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geometrie.o : test_geometrie.c geom2d.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

		
########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geometrie : test_geometrie.o geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

contour : image.o geom2d.o conventions.o list_contour.o list_bezier2.o contour.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_Bezier : main.o simplification_Bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_Bezier"
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

simplification_Bezier3 : main.o simplification_Bezier3.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_Bezier3"
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

main : image.o geom2d.o conventions.o list_contour.o list_bezier2.o list_bezier3.o contour.o simplification_Bezier.o simplification_Bezier3.o main.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module main"
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
