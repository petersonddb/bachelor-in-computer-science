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

#include <stdio.h>
#include <string.h>

/* protótipos */
void listar_plugins();
void executar_plugin();
void msg(lpvdp_resultado);

/**
 * interface com o usuário
 * para gerenciamento de plugins
 */
void lpvdp_iu_plugins() {
    int op;
    do {
        printf(
            "===== LPVDP - Plugins =====\n\n"
            "\t[1] List\n"
            "\t[2] Run\n"
            "\t[3] Go back\n\n"
            ">"
        );
        scanf("%d", &op);
        switch(op) {
            case 1:
                listar_plugins();
                break;
            case 2:
                executar_plugin();
                break;
            case 3:
                break;
            default:
                printf("Invalid option!\n");
        }
    } while(op != 3);
}

/**
 * interface para mostrar
 * todos os plugins
 */
void listar_plugins() {
    printf("\nAvailable plugins:\n");
    lpvdp_gp_listar(stdout);
    printf("\n");
}

/**
 * interface para executar
 * um plugin
 */
void executar_plugin() {
    gp_nome_t nome;
    
    char continuar;
    
    lpvdp_resultado resultado;
    
    printf("\nRun a plugin:\n");
    do {
        printf("Name: ");
        getchar(); //remove o \n
        fgets(nome, GP_NOME_TAMANHO, stdin);
        nome[strlen(nome) - 1] = 0; //remove o \n
        printf("Running...\n");
        if((resultado = lpvdp_gp_exec(nome, msg)) != LPVDP_GP_EXECUTADO) {
            printf("Failed: %s\n", lpvdp_str_resultado(resultado));
            printf("Try again (y/n): ");
            scanf("%c", &continuar);
        } else {
            continuar = 'n';
        }
    } while(continuar == 'y');
    printf("\n");
}

/**
 * exibe uma mensagem
 * @param resultado o codigo da mensagem
 */
void msg(lpvdp_resultado resultado)  {
    printf("%s\n", lpvdp_str_resultado(resultado));
}
