# Trabalho GA - Processamento Gráfico

## Autor: Rafael do Amaral Porciuncula

### Como jogar:

O objetivo é pegar todas as laranjas que cairem da árvore, sem pegar nenhuma das folhas que também podem cair!
Para iniciar o jogo basta clicar "Enter" após fechar a mensagem inicial explicativa. Para controlar o cesto, basta utilizar as setas do teclado!
Ao perder o jogo, seja por deixar uma laranja cair, ou por pegar uma folha, o jogador será informado sobre a quantidade de laranjas coletadas e poderá reiniciar o jogo clicando "Enter" novamente.

### Para compilar selecionar a opção Debug x86

### Dependências (Não deve ser necessário realizar alterações):

- Selecionar o projeto e clicar em _Properties_ -> _C/C++_ -> _General_ -> Additional Include Directories e adicionar os seguintes caminhos: `../../dependencies/glfw-3.3.4.bin.WIN32/include;../../dependencies/GLAD/include;../../dependencies/glm`
- Selecionar o projeto e clicar em _Properties_ -> _Linker_ -> _General_ -> Additional Library Directories e adicionar o seguinte caminho: `../../dependencies/glfw-3.3.4.bin.WIN32/lib-vc2019`
- Selecionar o projeto e clicar em _Properties_ -> _Linker_ -> _Input_ -> Additional Directories e adicionar os seguintes caminhos: `glfw3.lib;opengl32.lib;%(AdditionalDependencies)`
