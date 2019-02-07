/**
 *   LPVDP - Layered Parallel Virtual Distributed Platform
 *   Copyright (C) 2018 Peterson Daronch de Bem (petersondaronch@gmail.com)
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, version 3 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <lpvdp_iu.h>

#include <string.h>

/* protótipos */
void incluir_terminal();
void listar_terminais();

/**
 * interface com usuário para
 * gerenciamento de terminais
 */
void lpvdp_iu_terminais() {
    int op;
    
    do {
        printf(
            "===== LPVDP - Terminals =====\n\n"
            "\t[1] Add\n"
            "\t[2] List\n"
            "\t[3] Go back\n\n"
            ">"
        );
        scanf("%d", &op);
        switch(op) {
            case 1:
                incluir_terminal();
                break;
            case 2:
                listar_terminais();
                break;
            case 3:
                break;
            default:
                printf("Invalid option!\n");
        }
    } while(op != 3);
}

/**
 * interface para inclusão de
 * novo terminal
 */
void incluir_terminal() {
    gt_nome_t nome;
    gt_ip4_endereco endereco;
    
    char continuar;
    
    lpvdp_resultado resultado;
    
    printf("\nNew terminal:\n");
    do {        
        printf("Name: ");
        getchar(); //remove o \n
        fgets(nome, GT_TERMINAL_NOME_TAMANHO, stdin);
        nome[strlen(nome) - 1] = 0; //remove o \n
        printf("IP: ");
        fgets(endereco.ip_endereco, GT_TERMINAL_IP4_ENDERECO_TAMANHO, stdin);
        endereco.ip_endereco[strlen(endereco.ip_endereco) - 1] = 0; //remove o \n
        printf("Port: ");
        scanf("%d", &endereco.porta);
        if((resultado = lpvdp_gt_incluir(gt_obter_terminal_ip4(nome, endereco.ip_endereco, endereco.porta))) != LPVDP_GT_INCLUIDO) {
            printf("Failed: %s\n", lpvdp_str_resultado(resultado));
            printf("Try again (y/n): ");
            scanf("%c", &continuar);
        } else {
            printf("Registered!\n");
            continuar = 'n';
        }
    } while(continuar == 'y');
    printf("\n");
    
}

/**
 * mostra todos os terminais
 * cadastrados
 */
void listar_terminais() {
    printf("\nKnown terminals:\n");
    lpvdp_gt_listar(stdout);
    printf("\n");
}
