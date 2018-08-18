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

#include <gerenciador_plugins.h>

#include <string.h>

#define GP_TESTES_SAIDA "[GP TESTES]"

/* Prototipos */
void gp_testar_saida(FILE *, char *);

/**
 * Testa o gerenciador de plugins
 * @param saida um descritor de arquivo para imprimir a saída
 * @return o código de resultado
 */
gp_resultado gp_testar(FILE *saida) {
    
    gp_resultado resultado;
    gp_caminho_t plugin;
    
    gp_testar_saida(saida, "== Todos os plugins ==");
    gp_imprimir(saida, gp_abrir());
    
    gp_testar_saida(saida, "== Acessando um plugin ==");
    plugin = gp_obter_caminho("libsample_plugin_um.so");
    fprintf(saida, "Nome: %s\n", plugin);
    if((resultado = gp_exec(plugin)) != GP_EXECUTADO) {
        gp_testar_saida(saida, gp_str_resultado(resultado));
        return GP_FALHA_TESTES;
    }
    
    return GP_TESTES_CONCLUIDO;
    
}

/**
 * Exibe a mensagem na saída infomada
 * @param saida saida um descritor de arquivo para imprimir a saída
 * @param msg uma mensagem a ser exibida
 */
void gp_testar_saida(FILE *saida, char *msg) {
    fprintf(saida, "%s: %s\n", GP_TESTES_SAIDA, msg);
}
