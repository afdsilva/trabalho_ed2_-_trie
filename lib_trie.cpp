/**
 * Trabalho Trie - ED2
 * Andre Felipe da Silva
 * Matricula: 11107587
 * e-mail: afdsilva@inf.ufpel.edu.br
 **/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include "lib_trie.h"

using namespace std;

Nodo::Nodo() {
	int i;

	this->final = 0;
	for(i=0;i < tAlfabeto;i++)
		letra[i] = NULL;
}
Nodo::Nodo(string palavra) {
	int i;

	this->final = 0;
	for(i=0;i < tAlfabeto;i++)
		letra[i] = NULL;
	this->inserePalavra(palavra);
}

int Nodo::hWord(string palavra) {
	return (palavra[0] - 'A') % tAlfabeto;
}

/**
 * Insere uma nova palavra
 **/
int Nodo::inserePalavra(string palavra) {
	int retorno = 0;

	string nPalavra = palavra.substr(1);
	int l = hWord(palavra);

	if (nPalavra[0] != '\0' && nPalavra.length() > 0) {
		if(this->letra[l] == NULL) {
			this->letra[l] = new Nodo(nPalavra);
			retorno = 1;
		} else
			retorno = this->letra[l]->inserePalavra(nPalavra);
	} else if(!this->getFinal()) {
		setFinal();
		retorno = 1;
	}

	return retorno;
}

int Nodo::buscaPalavra(string palavra) {

	int retorno = 0;
	int l = hWord(palavra);
	string nPalavra = palavra.substr(1);
	//verifica se a palavra eh diferente do vazio
	if (nPalavra[0] != '\0') {
		//palavra sem o primeiro caracter é diferente de \0
		//se for vai verificar o proximo caracter
		if (this->letra[l] != NULL) {
			//proximo caracter existe chama recursao
			retorno = this->letra[l]->buscaPalavra(nPalavra);
		} else {
			//do contrario nao encontrou a palavra
			retorno = 0;
		}
	} else {
		//se for a palavra vazia, soh por descargo de conciencia verifica se o nodo eh final ou nao
		if (this->getFinal())
			retorno = 1;
	}

	return retorno;
}

int Nodo::removePalavra(string palavra) {
	int retorno = 0;
	int i;
	int l = hWord(palavra);
	string nPalavra = palavra.substr(1);
	if (buscaPalavra(palavra)) {
		//verifica se nao eh o ultimo caracter valido da palavra
		if (nPalavra[0] != '\0') {
			//se nao for chama o metodo recursivamente (como na busca, passando a palavra sem o 1o caracter)
			if (this->letra[l] != NULL) {
				retorno = this->letra[l]->removePalavra(nPalavra);
				if (retorno == 1) {
					//se ao retornar das recursoes for 1 o retorno, remove o nodo
					//this->letra[l] = NULL;
				}
				
			} else {
				//nao encontrou a palavra (nao chegou no final da string)
				retorno =  0;
			}
		} else {
			//ultimo caracter (provavelmente) verifica se é final
			if (this->getFinal()) {
				//eh final, reverte a flag
				this->setFinal();
				retorno = 1; //fez a remocao com sucesso, retorna 1
			}
		}
		
		
		/**
		
		
		if (palavra[0] != '\0' && this->letra[l] != NULL) {
			nPalavra = palavra.substr(1); //verifica restante da substring sem o 1o caracter
			retorno = this->letra[l]->removePalavra(nPalavra); // procura o restante da substring recursivamente
			for (i = 0; i < tAlfabeto; i++) //porem, caso ainda exista algum nodo retorna 2, indicando que ainda há nodos ativos
				if (this->letra[i] != NULL) //testa se existe algum nodo ativo
					retorno = 2; //existe, retorna 2
			if (retorno == 1) { //faz apenas se o retorno for 1, indicando que não há nodos em excesso
				this->letra[l] = NULL; //remove o ponteiro para o Nodo
			}
		} else if(this->getFinal()) {
			//palavra vazia, encontrou numa e a palavra existe:
			this->setFinal(); //remove flag do final
			retorno = 1; //retorna 1, pq fez a operacao com sucesso
			for (i = 0; i < tAlfabeto; i++) //porem, caso ainda exista algum nodo retorna 2, indicando que ainda há nodos ativos
				if (this->letra[i] != NULL) //testa se existe algum nodo ativo
					retorno = 2; //existe, retorna 2
		}
		**/
	} else {
		//chegou no final da string
		if (this->getFinal()) {
			//eh final, reverte a flag
			this->setFinal();
			retorno = 1; //fez a remocao com sucesso, retorna 1
			for (i = 0; i < tAlfabeto; i++)
				if (this->letra[i] != NULL)
					retorno = 2;			// se encontrar ao menos um nodo existente, nao remove o nodo pai
		}
	}
	return retorno;
}
void Nodo::setFinal() {
	if (this->getFinal()) this->final = 0;
	else this->final = 1;
}
int Nodo::getFinal() {
	return this->final;
}
