#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "lib_trie.h"

int main(int argc, char * argv[]) {
	
	char * palavra = argv[1];
	if (argc > 1) {

		Arvore * nArvore = Arvore::Palindromo(palavra);
		
		nArvore->Mostra();

	}

	return 0;
}
