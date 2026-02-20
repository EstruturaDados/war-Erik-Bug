// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Corrigido: era strings.h
#include <time.h>    // Adicionado para rand()

// --- Constantes Globais ---
#define TAM_STRING 100

// --- Estrutura de Dados ---
struct Territorio {  // Corrigido: sem acento
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// --- Protótipos das Funções ---
void LimparBufferEntrada();
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios);
void exibirMapa(struct Territorio* mapa, int numTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
int validarAtaque(struct Territorio* atacante, struct Territorio* defensor);
void exibirResultadoAtaque(struct Territorio* atacante, struct Territorio* defensor, int atacanteVenceu);

// --- Função para limpar buffer de entrada ---
void LimparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(struct Territorio* mapa, int numTerritorios) {
    printf("\n============================================\n");
    printf("        --- CADASTRO DE TERRITÓRIOS ---         \n");
    printf("============================================\n");
    
    for (int i = 0; i < numTerritorios; i++) {
        printf("\n--- Território %d de %d ---\n", i + 1, numTerritorios);

        printf("Nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército (ex: azul, vermelho): ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        LimparBufferEntrada();
    }
}

// --- Função para exibir o mapa ---
void exibirMapa(struct Territorio* mapa, int numTerritorios) {
    printf("\n                  --- MAPA DE TERRITÓRIOS ---                  \n");
    printf("----------------------------------------------------------------\n");
    
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d", i + 1);
        printf("\tNome: %s\t", mapa[i].nome);
        printf("\tCor: %s\t", mapa[i].cor);
        printf("\tTropas: %d\n", mapa[i].tropas);
    }
    printf("----------------------------------------------------------------\n");
}

// --- Função para validar se o ataque é permitido ---
int validarAtaque(struct Territorio* atacante, struct Territorio* defensor) {
    // Verifica se não é o mesmo território
    if (atacante == defensor) {
        printf("Erro: Não é possível atacar o próprio território!\n");
        return 0;
    }
    
    // Verifica se são de cores diferentes
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar um território da mesma cor!\n");
        return 0;
    }
    
    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 0) {
        printf("Erro: Território atacante não tem tropas!\n");
        return 0;
    }
    
    return 1;
}

// --- Função para exibir resultado do ataque ---
void exibirResultadoAtaque(struct Territorio* atacante, struct Territorio* defensor, int atacanteVenceu) {
    printf("\n=== RESULTADO DO ATAQUE ===\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    if (atacanteVenceu) {
        printf("\n🏆 VITÓRIA DO ATACANTE! 🏆\n");
        printf("O território %s agora é controlado por %s\n", defensor->nome, atacante->cor);
    } else {
        printf("\n💔 DERROTA DO ATACANTE! 💔\n");
        printf("O atacante perdeu 1 tropa\n");
    }
}

// --- Função principal de ataque ---
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Validar se o ataque é permitido
    if (!validarAtaque(atacante, defensor)) {
        printf("Ataque inválido!\n");
        return;
    }
    
    printf("\n⚔️  BATALHA INICIADA ⚔️\n");
    printf("%s (%s) vs %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    
    // Simular dados de batalha
    int dadoAtacante = rand() % 6 + 1;  // 1-6
    int dadoDefensor = rand() % 6 + 1;  // 1-6
    
    printf("\n🎲 Dados da batalha:\n");
    printf("Atacante rolou: %d\n", dadoAtacante);
    printf("Defensor rolou: %d\n", dadoDefensor);
    
    // Determinar resultado
    if (dadoAtacante > dadoDefensor) {
        // Atacante venceu
        // Transfere a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do atacante para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas += tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        exibirResultadoAtaque(atacante, defensor, 1);
        
    } else {
        // Atacante perdeu
        atacante->tropas--;
        
        exibirResultadoAtaque(atacante, defensor, 0);
    }
}

// --- Função para liberar memória alocada ---
void liberarMemoria(struct Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória liberada com sucesso!\n");
    }
}

// --- Função Principal (main) ---
int main() {
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    struct Territorio* mapa = NULL;
    int numTerritorios = 0;
    int opcao;
    
    printf("============================================\n");
    printf("        --- JOGO DE BATALHA - RISK ---         \n");
    printf("============================================\n");
    
    // Solicitar número de territórios
    do {
        printf("\nDigite o número de territórios (mínimo 2): ");
        scanf("%d", &numTerritorios);
        LimparBufferEntrada();
        
        if (numTerritorios < 2) {
            printf("Erro: É necessário pelo menos 2 territórios para jogar!\n");
        }
    } while (numTerritorios < 2);
    
    // Alocação dinâmica de memória para os territórios
    mapa = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));
    
    if (mapa == NULL) {
        printf("Erro fatal: Falha na alocação de memória!\n");
        return 1;
    }
    
    // Cadastrar territórios
    cadastrarTerritorios(mapa, numTerritorios);
    
    // Loop principal do jogo
    do {
        printf("\n============================================\n");
        printf("--- MENU PRINCIPAL ---\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Cadastrar novos territórios\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        LimparBufferEntrada();
        
        switch(opcao) {
            case 1:
                exibirMapa(mapa, numTerritorios);
                break;
                
            case 2: {
                int atacanteIdx, defensorIdx;
                
                printf("\n--- SELECIONAR ATAQUE ---\n");
                exibirMapa(mapa, numTerritorios);
                
                printf("\nEscolha o território ATACANTE (1-%d): ", numTerritorios);
                scanf("%d", &atacanteIdx);
                printf("Escolha o território DEFENSOR (1-%d): ", numTerritorios);
                scanf("%d", &defensorIdx);
                LimparBufferEntrada();
                
                // Converter para índices do vetor (0-based)
                atacanteIdx--;
                defensorIdx--;
                
                // Validar índices
                if (atacanteIdx >= 0 && atacanteIdx < numTerritorios && 
                    defensorIdx >= 0 && defensorIdx < numTerritorios) {
                    
                    atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
                    
                } else {
                    printf("Erro: Índices de território inválidos!\n");
                }
                
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            }
            
            case 3: {
                int novoNum;
                printf("\nDigite o novo número de territórios: ");
                scanf("%d", &novoNum);
                LimparBufferEntrada();
                
                if (novoNum > 0) {
                    // Realocar memória
                    struct Territorio* novoMapa = (struct Territorio*) realloc(mapa, novoNum * sizeof(struct Territorio));
                    
                    if (novoMapa != NULL) {
                        mapa = novoMapa;
                        
                        if (novoNum > numTerritorios) {
                            // Cadastrar apenas os novos territórios
                            for (int i = numTerritorios; i < novoNum; i++) {
                                printf("\n--- Novo Território %d ---\n", i + 1);
                                printf("Nome: ");
                                fgets(mapa[i].nome, TAM_STRING, stdin);
                                mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
                                
                                printf("Cor: ");
                                fgets(mapa[i].cor, TAM_STRING, stdin);
                                mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
                                
                                printf("Tropas: ");
                                scanf("%d", &mapa[i].tropas);
                                LimparBufferEntrada();
                            }
                        }
                        
                        numTerritorios = novoNum;
                        printf("Territórios atualizados com sucesso!\n");
                    } else {
                        printf("Erro na realocação de memória!\n");
                    }
                }
                break;
            }
            
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
        
    } while (opcao != 0);
    
    // Liberar memória alocada
    liberarMemoria(mapa);
    
    return 0;
}
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
