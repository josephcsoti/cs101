# ------------------------------------------------
# File Name: Makefile
# Desc: Runs, compiles, and submits java files
# Instructions: Run using command "make <task>"

# Name:   Joseph Csoti
# CruzID: 1617438 // jcsoti
# Class:  CMPS 101
# Date:   11/08/18
# ------------------------------------------------

MAINCLASS  = Sparse
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS)

_PROJ  = pa3
_CLASS = cmps101-pt.f18
_CRUID = jcsoti

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit:
	submit $(_CLASS) $(_PROJ) $(SOURCES)

check:
	ls /afs/cats.ucsc.edu/class/$(_CLASS)/$(_PROJ)/$(_CRUID)