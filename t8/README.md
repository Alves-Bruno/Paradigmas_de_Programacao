# Trabalho 08

Este é o repositório onde os arquivos do t8 estão armazenados.
***

## Atividades Propostas

| TRABALHO | Descrição | 
|:---------:| --------- |
|t8|Gerador em C++ de Aplicação Web/Mobile em HTML5/Javascript.|[Descrição](https://github.com/AndreaInfUFSM/elc117-2017a/tree/master/trabalhos/t8)|

## Descrição

##### Nomes: Bruno Alves e Gabriel Mazzardo.

Observação: Este projeto foi testado em uma distribuição Linux (Linux Mint 18). Sinta-se à vontade para testar em outros SOs.

##### Pasta sem_interface

Nesta pasta estão os arquivos para a aplicação que deve ser executada em linha de código. 

Para compilar o código, digite o comando:

```{r, engine='bash', count_lines}
make
```

Para executar um novo projeto:

```{r, engine='bash', count_lines}
./main
```

Para abrir um projeto já existente:

```{r, engine='bash', count_lines}
./main nome_do_projeto.csv
```

Para mais informações sobre as operações válidas, digite "help" dentro da aplicação.

##### Pasta com_interface

Nesta pasta estão os arquivos para a aplicação com interface gráfica, feita com o FLTK. Portanto você deve ter instalado a biblioteca e as dependências do FLTK.

Para compilar o código, digite o comando:

```{r, engine='bash', count_lines}
make
```

Para executar um novo projeto:

```{r, engine='bash', count_lines}
./code_generator
```

Segue os Passos para criar um projeto simples:

1. Project -> New Project
2. Adicione o nome do projeto e o arquivo a ser criado (indique a extensão com .csv).
3. Code -> Set Title, para adcionar um titulo (que será mostrado na página web).
4. Preencha os campos de Label e Name, selecione a opção "Text Input", para criar uma seção de texto.
5. Preencha os campos de Label e Name, selecione a opção "Radio Input", para criar uma seção de Radio.
6. Para adicionar os botões da seção de Radio Button vá até Code -> Insert Radio Buttons.
7. Preencha os campos, de acordo com o número de botões que deseja adicionar.
8. Você pode adcionar quantos botões quiser, desde que a seção de Radio tenha sido aberta (como demonstrado no passo 5).
9. Se sobrarem campos de Radio Button, deixe em branco.
10. Code -> Generate code.

##### Códigos HTML

Os códigos gerados vão para a pasta HTML, mais especificamente HTML/index.html

##### Bugs 

Caso tenha algum problema ou sugestão, adicione um issue no nosso repositório.

