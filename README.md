# War - Missões Estratégicas em C

Este projeto implementa um sistema de **missões estratégicas individuais** para um jogo inspirado em War, utilizando a linguagem **C**.

## Funcionalidades

- Sorteio automático de missão para o jogador.
- Armazenamento da missão dinamicamente com ponteiros.
- Sistema de territórios e ataques simulando rolagem de dados.
- Verificação da missão do jogador após cada turno.
- Modularização com funções específicas (`atribuirMissao`, `atacar`, `verificarMissao`, `exibirMissao`, `liberarMemoria`).

## Estruturas principais

- `Territorio`: representa um território com `nome`, `cor` e `tropas`.
- `missaoJogador`: string alocada dinamicamente com a missão sorteada.

## Como compilar e rodar

Certifique-se de ter o **GCC** instalado. No terminal:

```bash
gcc war.c -o war.exe
.\war.exe
