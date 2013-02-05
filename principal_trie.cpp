#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "lib_trie.h"

int main(int argc, char * argv[]) {
	Arvore * nArvore;
	
	if (argc > 1) {

		char * palavra = argv[1];
		
		nArvore = Arvore::Palindromo(palavra);
		
		nArvore->Mostra();

	} else {
		string entrada;
		cin >> entrada;
		nArvore = Arvore::Palindromo(entrada);
		
		nArvore->Mostra();	 
	}

	return 0;
}
