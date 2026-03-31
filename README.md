# Projeto 1 - Computação Visual e Processamento de Imagens

Este projeto consiste em uma aplicação desenvolvida em linguagem C que realiza tarefas de processamento de imagens. Ele inclui suporte ao carregamento de imagens, conversão para escala de cinza, visualização e interação através de uma interface gráfica de usuário (GUI) interativa utilizando a biblioteca SDL3.

## Integrantes

* Lucas Zanini da Silva - 10417361
* Tiago Teraoka e Sá - 10418485

## Organização do Projeto

O código-fonte da aplicação é modularizado, garantindo fácil manutenção e leitura. A estrutura principal inclui:

- **`main.c`**: Ponto de entrada da aplicação. Orquestra o carregamento da imagem, o processo de conversão e a chamada da interface gráfica.
- **`include/`** e **`src/`**: Diretórios contendo os cabeçalhos (`.h`) e a implementação (`.c`) de cada funcionalidade específica:
  - **`image_loader`**: Lida com o carregamento de imagens em disco usando a biblioteca **SDL_image**.
  - **`grayscale`**: Responsável pelas operações de processamento de imagens, como a conversão para escala de cinza e a adaptação do formato da superfície (*Surface*).
  - **`histogram`**: Responsável pela geração visual do histograma da imagem processada e manipulação da Imagem para geração da versão equalizada.
  - **`image_saver`**: Oferece suporte para salvar as imagens resultantes de volta no disco.
  - **`gui`**: Contém a lógica de interface gráfica, lidando com renderização de janelas, interações do usuário e renderização de textos via **SDL_ttf**.
- **`public/`** e **`SDL_Files/`**: Diretórios com os ativos do projeto (por exemplo, imagens de teste, fontes `.ttf`, etc).
- **`Makefile`**: Arquivo de automação de compilação.

## Dependências

Para compilar e executar a aplicação, você deve ter as seguintes ferramentas e bibliotecas instaladas em seu ambiente de desenvolvimento:

- Compilador **GCC** (ou similar)
- Biblioteca **SDL3**
- Biblioteca **SDL3_image**
- Biblioteca **SDL3_ttf**

## Como Compilar

O projeto pode ser compilado de duas formas distintas: utilizando o `Makefile` disponibilizado (método mais simples e recomendado) ou manualmente sem o `Makefile`.

### 1. Compilando com Makefile (Recomendado)

Abra o terminal na raiz do diretório do projeto e execute:

```bash
make
```

Isso irá gerar um executável chamado `projeto1` (ou `projeto1.exe` no Windows).

Caso precise limpar o build anterior, execute:
```bash
make clean
```

### 2. Compilando sem Makefile

Se você preferir compilar manualmente (sem `make`), execute o compilador chamando todos os arquivos fonte e passando as flags corretas (ajuste os caminhos se não usar macOS/Homebrew):

**No macOS (com as bibliotecas instaladas no Homebrew):**
```bash
gcc -Wall -I. -I/opt/homebrew/include main.c src/image_loader.c src/grayscale.c src/histogram.c src/image_saver.c src/gui.c -o projeto1 -L/opt/homebrew/lib -lSDL3 -lSDL3_image -lSDL3_ttf
```

**No Linux/Windows (dependendo de onde os cabeçalhos SDL3 estiverem incluídos globalmente):**
```bash
gcc -Wall -I. main.c src/image_loader.c src/grayscale.c src/histogram.c src/image_saver.c src/gui.c -o projeto1 -lSDL3 -lSDL3_image -lSDL3_ttf
```

## Como Executar

A execução do programa requer estritamente que um argumento seja passado pela linha de comandos: **o caminho da imagem a ser lida**.

Para rodar a aplicação através do terminal após ter efetuado a compilação:

```bash
./projeto1 <caminho_da_imagem.ext>
```

**Exemplo prático de execução com a imagem de teste fornecida no projeto:**
```bash
./projeto1 public/teste.jpg
```

Assim que a aplicação abrir, utilize as opções disponilizadas na janela da interface gráfica para interagir como o processamento da imagem!
