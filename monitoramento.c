// Trabalho de monitoramento de temperatura
// Nome:
// Data:
//
// Ideia do programa: simular um sensor de temperatura. Eu defino um limite
// seguro, e o programa vai lendo temperaturas uma por uma. Se a temperatura
// passar do limite 3 vezes seguidas, o programa para sozinho (por seguranca).
// Da tambem pra sair a qualquer hora digitando -9999.
// No final ele mostra media, maior, menor e quantas ficaram acima do limite.

#include <stdio.h>

int main(void) {

    float limite;           // limite definido pelo usuario
    float temperatura;      // valor lido a cada vez
    float soma = 0.0f;
    float maior = -1000.0f;
    float menor = 1000.0f;

    int totalLeituras = 0;
    int totalAcimaLimite = 0;
    int consecutivas = 0;          // quantas vezes SEGUIDAS passou do limite
    int encerradoPorSeguranca = 0; // vira 1 se parou por causa das 3 seguidas
    int continuar = 1;
    int leituraValida;

    const float VALOR_SAIDA = -9999.0f; // digitando isso encerra na mao

    printf("=====================================================\n");
    printf("      SISTEMA DE MONITORAMENTO DE TEMPERATURA\n");
    printf("=====================================================\n\n");

    // pede o limite ate a pessoa digitar um numero de verdade
    // usei do-while aqui porque preciso ler primeiro pra depois checar
    do {
        printf("Digite o limite de temperatura considerado seguro (ex: 40.0): ");
        leituraValida = (scanf("%f", &limite) == 1);

        if (!leituraValida) {
            printf("Valor invalido! Digite apenas numeros (ex: 35.5).\n");
            while (getchar() != '\n') { /* limpa o que sobrou no buffer */ }
        }
    } while (!leituraValida);

    printf("\nLimite de seguranca definido: %.2f graus\n", limite);
    printf("Agora digite as temperaturas lidas pelo sensor, uma por vez.\n");
    printf("Para encerrar manualmente a qualquer momento, digite %.0f.\n\n", VALOR_SAIDA);

    // laco principal. usei while porque nao sei quantas temperaturas
    // vao ser digitadas, isso so vai depender do que acontecer durante
    // a execucao (usuario sair ou dar 3 acima do limite seguidas)
    while (continuar) {

        // le uma temperatura valida (mesma logica do limite la em cima)
        do {
            printf("Temperatura #%d: ", totalLeituras + 1);
            leituraValida = (scanf("%f", &temperatura) == 1);

            if (!leituraValida) {
                printf("Valor invalido! Digite apenas numeros.\n");
                while (getchar() != '\n') { /* limpa o buffer */ }
            }
        } while (!leituraValida);

        // usuario quis sair
        if (temperatura == VALOR_SAIDA) {
            printf("\nEncerramento manual solicitado pelo usuario.\n");
            continuar = 0;
            continue;
        }

        // temperatura fora de uma faixa que faz sentido pra um sensor
        // ambiente (chutei entre -90 e 60 graus). se vier algo assim,
        // pede de novo e nem conta essa leitura
        if (temperatura < -90.0f || temperatura > 60.0f) {
            printf("Temperatura fora de uma faixa plausivel (-90 a 60). Tente novamente.\n");
            continue;
        }

        // leitura valida, entao ja atualiza as estatisticas
        totalLeituras++;
        soma += temperatura;

        if (temperatura > maior) {
            maior = temperatura;
        }
        if (temperatura < menor) {
            menor = temperatura;
        }

        if (temperatura > limite) {
            totalAcimaLimite++;
            consecutivas++;
            printf(">> Atencao: temperatura acima do limite! (%d vez(es) seguida(s))\n", consecutivas);
        } else {
            consecutivas = 0; // quebrou a sequencia, zera de novo
        }

        // deu 3 seguidas acima do limite -> encerra sozinho
        if (consecutivas == 3) {
            encerradoPorSeguranca = 1;
            printf("\n*** ALERTA: 3 temperaturas consecutivas acima do limite! ***\n");
            printf("*** Monitoramento encerrado automaticamente por seguranca. ***\n");
            continuar = 0;
        }
    }

    // relatorio final
    printf("\n=====================================================\n");
    printf("                  RELATORIO FINAL\n");
    printf("=====================================================\n");

    if (totalLeituras == 0) {
        printf("Nenhuma leitura valida foi registrada.\n");
    } else {
        float media = soma / totalLeituras;
        float percentual = (totalAcimaLimite * 100.0f) / totalLeituras;

        printf("Total de leituras validas.......: %d\n", totalLeituras);
        printf("Temperatura media................: %.2f\n", media);
        printf("Maior temperatura................: %.2f\n", maior);
        printf("Menor temperatura................: %.2f\n", menor);
        printf("Leituras acima do limite.........: %d\n", totalAcimaLimite);
        printf("Percentual acima do limite........: %.2f%%\n", percentual);
        printf("Motivo do encerramento...........: %s\n",
               encerradoPorSeguranca
                   ? "3 temperaturas consecutivas acima do limite"
                   : "encerramento manual pelo usuario");
    }

    printf("=====================================================\n");

    return 0;
}
