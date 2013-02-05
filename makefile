# Trabalho ED2 - Trie
# André Felipe da Silva
# Matricula: 11107587
# e-mail: afdsilva@inf.ufpel.edu.br

# ultimo update: 04.02.2013

DATA = 04.02.2013
TRABALHO = trabalho_ed2_trie
EXECUTABLE = trie
BASE_FILENAME = $(TRABALHO)\[$(DATA)\].$(REVISION)
REVISION=1
CFLAGS =-std=c++0x -g -c -lm

all: lib_trie.o principal_trie.cpp
	@echo "Finalizando compilação e Linkando..."
	g++ -Wall -g lib_trie.o principal_trie.cpp -o $(EXECUTABLE)
lib_trie.o: lib_trie.h lib_trie.cpp
	@echo "Compilando Biblioteca Trie"
	g++ $(CFLAGS) lib_trie.cpp
#principal_trie.o: principal_trie.cpp
#	@echo "Compilando Arquivo Principal..."
#	g++ $(CFLAGS)  principal_trie.cpp

clean:
ifneq ($(wildcard *.o),)
	rm *.o
endif
ifeq ($(wildcard $(EXECUTABLE)),$(EXECUTABLE))
	rm $(EXECUTABLE)
endif

package:
	@echo "Empacotando: "
ifneq ($(wildcard *$(BASE_FILENAME)*),)
	rename 's/tar.gz/$(REVISION).tar.gz' $(wildcard *$(BASE_FILENAME)*) 
	#@echo "Arquivo Existe"
endif
ifeq ($(wildcard $(BASE_FILENAME).tar.gz),)
	mkdir $(BASE_FILENAME)
	cp README.md *.cpp *.h makefile $(BASE_FILENAME)/
	#tar -zcvf $(BASE_FILENAME).tar.gz $(BASE_FILENAME)/
	zip -r $(BASE_FILENAME).zip $(BASE_FILENAME)/
	rm -R $(BASE_FILENAME)/
endif
