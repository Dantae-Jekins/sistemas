## Biblioteca de alocação

Uma biblioteca de alocação de memória com duas funções principais: aloca e libera.
O controle da alocação é feito através de um buffer de memória e um buffer de controle, por implementação o buffer de controle sempre vai ter "size(buffer de memória)/8" espaços. Para cada byte de memória, temos um bit de controle.

O bit de controle indica se seu byte correspondente na memória é um byte de header ou não, os bytes de header servem para armazenar o tamanho do bloco de memória alocado logo a seguir dele, o tamanho do header é arbritário
