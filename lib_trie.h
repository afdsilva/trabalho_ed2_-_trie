/**
 * Trabalho Trie - ED2
 * Andre Felipe da Silva
 * Matricula: 11107587
 * e-mail: afdsilva@inf.ufpel.edu.br
 **/
 
#ifndef LIBTRIE_H
#define LIBTRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define tAlfabeto 5
#define iAlfabeto 65
#define fAlfabeto 122

class Nodo {
	Nodo * letra[tAlfabeto];
	int final;

	int hWord(string);
public:
	Nodo();
	Nodo(string);
	int inserePalavra(string);
	int buscaPalavra(string);
	int removePalavra(string);
	void setFinal();
	int getFinal();

};

class Arvore {
	Nodo * raiz;
public:
	Arvore(); //cria uma arvore vazia
	Arvore(string palavra); //cria uma arvore com uma palavra
	//insere sufixos
	
	//reverte palavra
	//procura palindromo
	
};

#endif
