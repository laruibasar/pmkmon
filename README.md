# pmkmon

Exercicio para resposta ao pedido da Premium Minds.

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
