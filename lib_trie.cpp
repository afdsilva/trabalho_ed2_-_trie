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

/**
 * Classe Nodo
 **/
Nodo::Nodo() {
	int i;

	this->final = 0;
	for(i=0;i < tAlfabeto;i++)
		letra[i] = NULL;
	this->setOcorrencias(0);
}
Nodo::Nodo(string palavra) {
	int i;

	this->final = 0;
	for(i=0;i < tAlfabeto;i++)
		letra[i] = NULL;
	this->inserePalavra(palavra);
	this->setOcorrencias(0);
}
Nodo::~Nodo() {
	int i;
	for(i = 0; i < tAlfabeto; i++)
		this->letra[i]->~Nodo();
	delete(this);
}
int Nodo::hWord(string palavra) {
	//return (palavra[0] - iAlfabeto) % tAlfabeto;
	return (palavra[0] - iAlfabeto);
}
string Nodo::hWordReturn(int i) {

	stringstream ss;
	string s;
	char c = (char) (i + iAlfabeto);
	ss << c;
	ss >> s;
	//return (palavra[0] - iAlfabeto) % tAlfabeto;
	return s;
}


Nodo * Nodo::acessaNodo(int posicao) {
	Nodo * retorno;
	if (this->letra[posicao])
		retorno = this->letra[posicao];

	return retorno;
}

/**
 * Insere uma nova palavra
 **/
int Nodo::inserePalavra(string palavra) {
	int retorno = 0;
	if (palavra.length()) {
		int l = (palavra.length() ? hWord(palavra) : '0'); // funcao 'hash', retorna o 1o caracter da palavra
		string nPalavra = palavra.substr(1); //palavra sem o 1o caracter
		//se palavra chegou no final, ou seja, <= 0
		if (palavra.length()) {
			//testa se jah nao existe nodo
			if (!this->letra[l]) { //nao existe, cria um novo nodo para palavra sem o 1o caracter
				//testa tamanho da palavra sem o 1o caracter, caso seja 0 cria um nodo vazio
				if (nPalavra.length()) {
					this->letra[l] = new Nodo(nPalavra);
				} else {
					//criou o ultimo nodo
					this->letra[l] = new Nodo();
					
					if (!this->letra[l]->getFinal()) {
						this->letra[l]->setFinal();
						retorno = 1;
					}
				}
			}
			else { //do contrario apenas insere recursivamente
				retorno = this->letra[l]->inserePalavra(nPalavra);
			}
		} else {
			//se a palavra chegou no final, é a base da recursão
			//verifica se a palavra jah nao existe
			cout << "Final" << endl;
			if (!this->getFinal()) {
				this->addOcorrencias();
				this->setFinal();
				retorno = 1;
			} else {
				this->addOcorrencias();
			}
		}
	}
	return retorno;
}
int Nodo::inserePalavra(string palavra, int ocorrencias) {
	inserePalavra(palavra);
	this->ocorrencias = ocorrencias;
}
int Nodo::getOcorrencias() {
	return this->ocorrencias;
}
int Nodo::getOcorrencias(string palavra) {
	int retorno = 0;
	if (palavra.length()) {
		if (buscaPalavra(palavra)) {
			int l = hWord(palavra);
			string nPalavra = palavra.substr(1);
			if (this->letra[l]) {
				//proximo caracter existe chama recursao
				retorno = this->letra[l]->getOcorrencias(nPalavra);
			}
		}
	} else {
		//se for a palavra vazia, verifica se o nodo eh final ou nao e retorna
		if (this->getFinal()) {
			retorno = this->ocorrencias;
		}
	}
	return retorno;
}
void Nodo::setOcorrencias(int ocorrencias) {
	this->ocorrencias = ocorrencias;
}
void Nodo::setOcorrencias(string palavra, int ocorrencias) {
	if (palavra.length()) {
		if (buscaPalavra(palavra)) {
			int l = hWord(palavra);
			string nPalavra = palavra.substr(1);
			if (this->letra[l]) {
				//proximo caracter existe chama recursao
				this->letra[l]->setOcorrencias(nPalavra, ocorrencias);
			}
		}
	} else {
		//se for a palavra vazia, verifica se o nodo eh final ou nao
		if (this->getFinal()) {
			this->ocorrencias = ocorrencias;
		}
	}
}
void Nodo::addOcorrencias() {
	int i = this->getOcorrencias();
	this->setOcorrencias(i++);
}
void Nodo::addOcorrencias(string palavra) {
	int i = this->getOcorrencias(palavra);
	i++;
	this->setOcorrencias(palavra, i);
}

/**
 * Verifica se a palavra se encontra na trie
 **/
int Nodo::buscaPalavra(string palavra) {

	int retorno = 0;
	if (palavra.length()) {
		int l = hWord(palavra);
		string nPalavra = palavra.substr(1);
		if (this->letra[l]) {
			//proximo caracter existe chama recursao
			retorno = this->letra[l]->buscaPalavra(nPalavra);
		}
	} else {
		//se for a palavra vazia, verifica se o nodo eh final ou nao e retorna
		if (this->getFinal())
			retorno = 1;
	}	return retorno;
}
/**
 * Remove a palavra da trie
 **/
int Nodo::removePalavra(string palavra) {
	int i, retorno = 0;
	if (palavra.length()) {
		int l = hWord(palavra);
		string nPalavra = palavra.substr(1);

		//verifica se nao eh o ultimo caracter valido da palavra
		if (nPalavra.length()) {
			//se nao for chama o metodo recursivamente (como na busca, passando a palavra sem o 1o caracter)
			if (this->letra[l]) {
				retorno = this->letra[l]->removePalavra(nPalavra);
				if (retorno == 1) {
					//se ao retornar das recursoes for 1 o retorno, remove o nodo
					this->letra[l] = NULL;
				}
				
			} else {
				//nao encontrou a palavra (nao chegou no final da string)
				retorno =  0;
			}
		} else {
			//ultimo caracter (provavelmente) verifica se é final
			if (this->letra[l]->getFinal()) {
				//eh final, reverte a flag
				this->letra[l]->setFinal();
				retorno = 1; //fez a remocao com sucesso, retorna 1
				for (i = 0; i < tAlfabeto; i++)
					if (this->letra[i] != NULL)
						retorno = 2;			// se encontrar ao menos um nodo existente, nao remove o nodo pai
			}
		}

	} else {
		//ultimo caracter (provavelmente) verifica se é final
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
/**
 * Verifica quantas vezes uma subpalavra se repete
 **/

int Nodo::buscaSubPalavra(string palavra) {
	int l, i, retorno = 0;
	string sPalavra;
	
	if (palavra.length()) {
		sPalavra = palavra.substr(1);
		if (sPalavra.length()) {
			l = hWord(palavra);
			if (this->letra[l]) {
				retorno += this->letra[l]->buscaSubPalavra(sPalavra);
			}
		} else {
				retorno = 1;
		}
	}
	return retorno;
}

/**
 * Retorna a string do nodo, util apenas para recuperar uma palavra do nodo, não utilizar em arvores
 * nota: retorna apenas a ultima string
 **/

string Nodo::retornaPalavra(string palavra) {
	string retorno;
	int i;
	if (!this->getFinal()) {
		for(i = 0; i < tAlfabeto; i++) {
			if (this->letra[i]) {
				palavra.append(this->hWordReturn(i));
				retorno = this->letra[i]->retornaPalavra(palavra);
			}
		}
	} else {
		retorno = palavra;
	}

	return retorno;
}
/**
 * Contador de Palavras
 **/
int Nodo::contaPalavras() {
	int i;
	int retorno = 0;
	if (this->getFinal())
		retorno++;
	for (i = 0; i < tAlfabeto; i++) {
		if (this->letra[i]) {
			retorno += this->letra[i]->contaPalavras();
		}
	}
	
	return retorno;
}
int Nodo::buscaArvore(string palavra,string aux) {
	int i,j;
	
	int retorno = 0;
/**
	if (this->getFinal()) {
		Arvore * prefixos;
		string auxPalavra, nPalavra;
		for (i = 1; i <= aux.length(); i++) {
			auxPalavra = aux.substr(0,i);
			prefixos = Arvore::arvorePrefixo(auxPalavra);
			retorno = (prefixos->buscaPalavra(palavra) ? 1 : retorno);
			//nPalavra = auxPalavra.substr(auxPalavra.length()-j);
			//retorno = (palavra == nPalavra ? 1 : retorno);
			if (retorno && palavra.length() > 1) {
				//sufixos->Mostra();
			}
				//cout << "aux: " << aux << " palavra: " << palavra << " auxPalavra: " << auxPalavra << endl;
		}
		//Arvore * sufixos = Arvore::arvoreSufixo(aux);
		//Arvore * invertido = Arvore::arvoreSufixo(Nodo::invertePalavra(aux));
		//retorno = (sufixos->buscaPalavra(palavra) ? 1 : (invertido->buscaPalavra(palavra) ? 1 : 0));
	}
	for (i = 1; i <= iPalavra.length(); i++) {
		auxPalavra = iPalavra.substr(0,i);
		//cout << auxPalavra << endl;
		for (j = 1; j <= auxPalavra.length(); j++) {
			nPalavra = auxPalavra.substr(auxPalavra.length()-j);
			if (Arvore::ehPalindromo(nPalavra))
				cout << nPalavra << (Arvore::ehPalindromo(nPalavra) ? " eh" : " nao") << " palindroma ocorrencias: " << sArvore->buscaSubPalavra(nPalavra) << " ocorrencias invertida: " << iArvore->buscaSubPalavra(nPalavra) << endl;
		}
			cout << "-------------------------------------------" << endl;
	}
	for (i = 0; i < tAlfabeto; i++) {
		if (this->letra[i]) {
			string s = hWordReturn(i);
			aux.append(s);
			retorno += this->letra[i]->buscaSubArvore(palavra, aux);
		}
	}
	
**/
	return retorno;
}

/**
 * Retorna um vetor de strings contendo todas strings da arvore concatenada
 **/
void Nodo::listaPalavras(string palavra) {
	int i,j,x = 0;
	string nPalavra;
	if (this->getFinal()) {
		cout << palavra << endl;
	}
	//cout << "Palavra: " << palavra << " Final: " << this->getFinal() << endl;
	for (i=0; i< tAlfabeto;i++) {
		nPalavra.clear();
		if (this->letra[i]) {
			//cout << "i: " << i << " | " << (this->letra[i] != NULL ? "Existe" : "Não existe") << " | Flag: " << this->getFinal() << endl;
			string s = hWordReturn(i);
			nPalavra.append(palavra).append(s);
			//nPalavra.append(s).append(palavra); // inverte string
			//nPalavra.append(s);
			this->letra[i]->listaPalavras(nPalavra);
		}
	}
}

/**
 * Inverte uma palavra
 **/
string Nodo::invertePalavra(string palavra) {
	int i;
	string retorno;
	retorno.clear();
	string nLetra;
	for (i = 1; i <= palavra.length(); i++) {
		nLetra = palavra[palavra.length()-i];
		retorno.append(nLetra);
	}
	retorno[i] = '\0';
	 return retorno;
}

/**
 * Metodos que setam e recuperam a informação do estado final na trie
 **/
void Nodo::setFinal() {
	if (this->getFinal()) this->final = 0;
	else this->final = 1;
}
int Nodo::getFinal() {
	return this->final;
}

/**
 * Classe Arvore
 **/

Arvore::Arvore( ) {

	this->raiz = new Nodo();
}
Arvore::Arvore(string palavra) {

	this->raiz = new Nodo(palavra);
}
Arvore::Arvore(Nodo * nNodo) {
	this->raiz = nNodo;
}
int Arvore::inserePalavra(string palavra) {
	int retorno = 0;
	if (palavra.length()) {
		retorno = this->raiz->inserePalavra(palavra);
	}
	return retorno;
}
int Arvore::buscaPalavra(string palavra) {
	int retorno = 0;
	if (palavra.length()) {
		retorno = this->raiz->buscaPalavra(palavra);
	}
	return retorno;
}

Arvore::~Arvore() {
	delete(this->raiz);
}

/**
int Arvore::buscaArvore(string palavra) {
	
	int retorno = this->raiz->buscaSubArvore(palavra, "");

	return retorno;
}
**/

int Arvore::buscaSubPalavra(string palavra) {
	
	int retorno = this->raiz->buscaSubPalavra(palavra);

	return retorno;
}

Arvore * Arvore::arvoreSufixo(string palavra) {
	
	int i;
	Arvore * rArvore = new Arvore();
	string nPalavra;

	for (i = 0; i < palavra.length(); i++) {
		//cout << "palavra: " << palavra << " i: " << i << " substring: " << palavra.substr(palavra.length() - i) << endl;
		nPalavra = palavra.substr(i);
		rArvore->inserePalavra(nPalavra);
	}
	return rArvore;
}
Arvore * Arvore::arvoreSufixo(Nodo * nPalavra) {
	string teste;
	Arvore * arvore = arvoreSufixo(nPalavra->retornaPalavra(""));
	return arvore;
}
Arvore * Arvore::arvorePrefixo(string palavra) {
	
	int i;
	Arvore * rArvore = new Arvore();
	string nPalavra;
	
	for (i = 1; i <= palavra.length(); i++) {
		//cout << "palavra: " << palavra << " i: " << i << " substring: " << palavra.substr(palavra.length() - i) << endl;
		nPalavra = palavra.substr(0,i);
		if (ehPalindromo(nPalavra)) {
			//cout << nPalavra << "é'palindromo" << endl;
		}
		rArvore->inserePalavra(nPalavra);
	}
	return rArvore;
}
Arvore * Arvore::arvorePrefixo(Nodo * nPalavra) {
	Arvore * arvore = arvorePrefixo(nPalavra->retornaPalavra(""));
	return arvore;
}

/**
 * Gera uma arvore com o(s) maior(es) Palindromo(s)
 **/
Arvore * Arvore::Palindromo(string palavra) {
	//inverte string
	
	Arvore * retorno = new Arvore();
	int i,j, ocorrencias, maior = 0, maisOcorrencias = 0;
	string iPalavra = Nodo::invertePalavra(palavra);
	string nPalavra, aPalavra, maiorPalindromo, antigoMaior;
	int l;
	
	//gera uma arvore de sufixos
	//cout << "Arvore Normal: " << palavra << endl;
	Arvore * sArvore = arvoreSufixo(palavra);
	//sArvore->Mostra();
	//utilizando a arvore de sufixos, vai procurar nas substrings da string original invertida

	for (i = 0; i < iPalavra.length(); i++) {
		nPalavra = iPalavra.substr(i);
		//cout << "nPalavra: " << nPalavra;
		for (j = 1; j <= nPalavra.length(); j++) {
			aPalavra = nPalavra.substr(0,j);
			if (aPalavra.length() > 1) {
				if (sArvore->buscaSubPalavra(aPalavra) && Arvore::ehPalindromo(aPalavra)) {
					maior = (aPalavra.length() >= maior ? aPalavra.length() : maior);
					
					antigoMaior = maiorPalindromo;
					maiorPalindromo = (aPalavra.length() >= maior ? aPalavra : maiorPalindromo);
					if (aPalavra.length() >= maiorPalindromo.length()) {
						//cout << "antigo: " << antigoMaior << " novo: " << maiorPalindromo << endl;
						//cout << "antigo: " << antigoMaior.length() << " novo: " << maiorPalindromo.length() << endl;
						if (antigoMaior.length() < maiorPalindromo.length()) {
							//cout << "removendo antigo" << endl;
							//retorno->raiz->removePalavra(antigoMaior);
							retorno = new Arvore();
						}
						if (!retorno->inserePalavra(aPalavra)) {
							//cout << aPalavra << " jah existe" << endl;
							retorno->raiz->addOcorrencias(aPalavra);
							//nNodo->addOcorrencias();

						}
					}
					//ocorrencias = retorno->raiz->getOcorrencias(aPalavra);
					//maisOcorrencias = ( ocorrencias > maisOcorrencias ? ocorrencias : maisOcorrencias);
				}
			}
			//sArvore->buscaSubPalavra(aPalavra);
		}
	}
	//cout << "palindromo que apareceu mais vezes: " << maisOcorrencias << endl;
	//cout << "maior palindromo: " << maior << " caracteres" << endl;
/**/
	return retorno;
}

/** /

int Arvore::contaPalindromo() {
	return this->raiz->contaPalindromo("");
}
/**
int Nodo::contaPalindromo(string aux) {
	int retorno = 0;
	int i;
	Nodo * aNodo;
	string s;
	
	if (this->getFinal()) {
		//final da palavra
		//cout << aux << endl;
	}
	for(i=0;i < tAlfabeto; i++) {
		aNodo = this->letra[i];
		if (aNodo) {
			s = Nodo::hWordReturn(i);
			aux.append(s);
			cout << "s: " << s << "aux: " << aux << endl;
			//retorno += aNodo->contaPalindromo(aux);
		}
	}
	return retorno;
}
**/
/**
 * Verifica se a palavra possui palindromos e retorna
 * a arvore de palindromos
 **/
/** /
int Arvore::buscaArvorePalindromo(string palavra) {
	Arvore * retorno = new Arvore();
	int i, j;
	string nPalavra;
	
	if (palavra.length()) {
		for (i = 1; i <= palavra.length(); i++) {
			nPalavra = palavra.substr(0,i); // palavra sem o 1o caracter
			for (j = 1; j <= nPalavra.length(); j++) {
				
			}
			if (nPalavra.length() > 1) {
				cout << "nPalavra: " << nPalavra << " ocorrencias: " << ;
			}
		}
	}
	return retorno;
}
/**/
int Arvore::ehPalindromo(string palavra) {
	string invertida = Nodo::invertePalavra(palavra);

	return (palavra == invertida ? 1 : 0);
}
/**
 * Imprime na tela todas palavra da arvore
 **/
void Arvore::Mostra() {
	this->raiz->listaPalavras("");
}
