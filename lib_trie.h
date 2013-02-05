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

#define tAlfabeto 54
#define iAlfabeto 65
#define fAlfabeto 122
#define eAlfabeto -65
class Nodo {
	Nodo * letra[tAlfabeto];
	int final;
	int ocorrencias;

public:
	Nodo();
	Nodo(string);

	void setFinal();
	int getFinal();
	Nodo * acessaNodo(int);

	int inserePalavra(string);
	int inserePalavra(string, int);
	int removePalavra(string);
	int buscaPalavra(string);
	int buscaSubPalavra(string);
	int buscaArvore(string,string);
	string subPalavra(string);
	int contaPalavras();
	void listaPalavras(string);
	string retornaPalavra(string);
	Nodo * retornaNodo(string palavra);

	static string invertePalavra(string);
	int contaPalindromo(string);

	static string hWordReturn(int);
	static int hWord(string);

	int getOcorrencias(string);
	int getOcorrencias();
	void setOcorrencias(string, int);
	void setOcorrencias(int);
	void addOcorrencias(string);
	void addOcorrencias();

	~Nodo();
};

class Arvore {
	Nodo * raiz;

public:
	Arvore(); //cria uma arvore vazia
	Arvore(string); //cria uma arvore com uma palavra
	Arvore(Nodo *); //cria uma arvore apartir de um nodo
	static Arvore * arvorePrefixo(string);
	static Arvore * arvorePrefixo(Nodo *);
	static Arvore * arvoreSufixo(string);
	static Arvore * arvoreSufixo(Nodo *);

	int inserePalavra(string);
	int buscaPalavra(string);
	int buscaSubPalavra(string);
	int buscaArvore(string);

	void Mostra();
	Nodo * retornaNodo(string palavra);
	static Arvore * Palindromo(string);
	int contaPalindromo();
	static int ehPalindromo(string);

	~Arvore();
};

#endif
