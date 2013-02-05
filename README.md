trabalho_ed2_-_trie
===================
Andre Felipe da Silva
Matricula: 11107587
e-mail: afdsilva@inf.ufpel.edu.br

Trabalho Estrutura de Dados 2 - Trie

Compilacao:
   make

-opcional
   make package (gera pacote)

Execucao
   ./trie <string_por_linha_de_comando>
   ./trie 
      <entrada_padrao>

Bugs:
  (corrigido) Nao remove os nodos antigos da arvore de palindromos quando existe mais de um menor ex: GGG ACA, depois quando for remover ele remove apenas o ultimo que foi pesquisado precisaria de um historico, vou tentar fazer em meia hora mas caso nao seja possivel, entregarei outra revisao mais tarde se for permitido;
      NOTA: a arvore eh gerada novamente, nao sei se eh o metodo certo, mas foi o mais rapido que encontrei devido as circuntancias;
  Nao foi testado com outros caracteres, provavelmente (quase certo) que nao executara;
Limitacoes:
  Com strings grandes esta demorando um tempo consideravel, talvez seja minha implementacao orientada a objeto, que conforme o andamento do trabalho acabou ficando meio complexa;

