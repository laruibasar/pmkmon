# pmkmon

Exercicio para resposta ao pedido da Premium Minds.

# Objetivo

O Ash está a apanhar pokémons num mundo que consiste numa grelha bidimensional infinita de casas. Em cada casa há exatamente um pokémon.
O Ash começa por apanhar o pokémon que está na casa onde começa. A seguir, move-se para a casa imediatamente a norte, sul, este ou oeste de onde se encontra e apanha o pokémon que aí se encontrar, e assim sucessivamente. Atenção: se ele passar numa casa onde já passou (e, portanto, onde já apanhou um pokémon), já lá não está um pokémon para ele apanhar!
Objetivo: começando com um mundo cheio de pokémons (um em cada casa!), quantos pokémons o Ash apanha para uma dada sequência de movimentos?

## Formato input

O programa deve ler uma linha do stdin, que contém uma sequência de movimentos. Cada movimento é descrito por uma letra `N`, `S`, `E` ou `O` (respetivamente: norte, sul, este, oeste).

## Formato output

O programa deve escrever uma linha para o stdout, apenas com um número: quantos pokémons o Ash apanhou?

## Exemplos

1. Input: E Output: 2
1. Input: NESO Output: 4
1. Input: NSNSNSNSNS Output: 2

## Considerações técnicas

* Usar a linguagem / stack tecnológica que preferir. No entanto, é preciso que, com o código-fonte, seja forneçido o comando completo que permite compilar (se necessário) e executar a solução.
* A solução deve ser correta (do ponto de vista funcional) e eficiente (tempo gasto, memória ocupada, etc.). Sugere-se a escrita de testes que ponham à prova a a solução para lá dos inputs de exemplo (inputs de maior dimensão, casos bicudos, etc.), e que se inclua  no código-fonte.
* Muito valor ao quão compreensível e organizado é o teu código.

# Requisitos

Desenvolvido e testado em OpenBSD 6.8 e MacOS Catalina 10.15.7, não utiliza nada mais do que as biblioteca standard do SO.

Necessário ter as ferramentas base de cada sistema, sendo que no MacOS pode ser necessário ter as ferramentas do XCode.

# Compilar

Para facilidade existe um Makefile disponivel que permite compilar a aplicação bem como a aplicação de testes.

Na pasta da aplicação:

```sh
$ make all
$ ./test
$ ./pmkmon
```

Para executar a aplicação basta passar os argumentos na linha de comandos: `./pmkmon NNEESSOOO`
