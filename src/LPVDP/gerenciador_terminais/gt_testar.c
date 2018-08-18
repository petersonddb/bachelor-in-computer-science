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

#include <gerenciador_terminais.h>

#include <string.h>

#define GT_TESTES_SAIDA "[GT TESTES]"

/* Prototipos */
void gt_testar_saida(FILE *, char *);

/**
 * Testa o gerenciador de terminais
 * @param saida um descritor de arquivo para imprimir a saída
 * @return o código de resultado
 */
gt_resultado gt_testar(FILE *saida) {
    
    gt_terminal t, *t_tmp;
    gt_ip4_endereco ip4;
    gt_nome_t nome;
    gt_resultado resultado;
    
    ed_llbd *lista;
    ed_llbd_resultado llbd_resultado;
    
    int bd;
    
    gt_testar_saida(saida, "== Testando inclusão de novo terminal no bd ==");
    if((bd = gt_bd_abrir(GT_BD_ABERTURA_MODO_LE)) < 0) {
        gt_testar_saida(saida, "BD não pode ser aberto!");
        return GT_TESTES_FALHA;
    }
    
    t = gt_obter_terminal_ip4("__TESTE_A", "127.0.0.1", 8081);
    if((resultado = gt_bd_incluir(t, bd)) != GT_INCLUIDO && resultado != GT_ENCONTRADO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    
    t = gt_obter_terminal_ip4("__TESTE_B", "127.0.0.1", 8080);
    if((resultado = gt_bd_incluir(t, bd)) != GT_INCLUIDO && resultado != GT_ENCONTRADO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    
    gt_testar_saida(saida, "== Testando recuperação do terminal recém incluído no bd ==");
    memset(&t, 0, sizeof(gt_terminal));
    if((resultado = gt_bd_buscar_por_nome("__TESTE_A", &t, bd)) != GT_ENCONTRADO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    
    memset(&t, 0, sizeof(gt_terminal));
    if((resultado = gt_bd_buscar_por_nome("__TESTE_B", &t, bd)) != GT_ENCONTRADO ) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    
    gt_testar_saida(saida, "== Imprimindo todos os terminais do BD ==");
    gt_bd_imprimir_ipv4(saida, bd);
    
    gt_testar_saida(saida, "== Testando carregamento dos terminais em uma lista ==");
    if((llbd_resultado = ed_llbd_criar(&lista)) != ED_LLBD_CRIADA) {
        gt_testar_saida(saida, ed_llbd_str_resultado(llbd_resultado));
        return GT_TESTES_FALHA;
    }
    
    if((resultado = gt_bd_buscar(lista, bd)) != GT_CARREGADOS) {
        gt_testar_saida(saida, gt_str_resultado(llbd_resultado));
        return GT_TESTES_FALHA;
    }
        
    gt_testar_saida(saida, "== Testando recuperação dos terminais recém adicionados na lista ==");
    memset(nome, 0 , sizeof(gt_nome_t));
    strcpy(nome, "__TESTE_A");
    if((resultado = gt_ed_llbd_buscar_por_nome(*lista, nome, &t_tmp)) != GT_ENCONTRADO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    ip4 = gt_obter_ip4_de_endereco(t_tmp->endereco);
    fprintf(saida, "Nome: %s Tipo: IP Versão: 4 Endereço: %s Porta: %d\n", t_tmp->nome, ip4.ip_endereco, ip4.porta);
    
    memset(nome, 0 , sizeof(gt_nome_t));
    strcpy(nome, "__TESTE_B");
    if((resultado = gt_ed_llbd_buscar_por_nome(*lista, nome, &t_tmp)) != GT_ENCONTRADO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    ip4 = gt_obter_ip4_de_endereco(t_tmp->endereco);
    fprintf(saida, "Nome: %s Tipo: IP Versão: 4 Endereço: %s Porta: %d\n", t_tmp->nome, ip4.ip_endereco, ip4.porta);
    
    gt_testar_saida(saida, "== Imprimindo todos os terminais da lista ==");
    gt_ed_llbd_imprimir_ipv4(*lista, saida);
    
    gt_testar_saida(saida, "== Testando remoção de todos os terminais da lista ==");
    if((llbd_resultado = ed_llbd_liberar(lista)) != ED_LLBD_ATUALIZADA) {
        gt_testar_saida(saida, ed_llbd_str_resultado(llbd_resultado));
        return GT_TESTES_FALHA;
    }
    
    gt_testar_saida(saida, "== Testando remocao de todos os terminais recem adicionados no BD ==");
    if((resultado = gt_bd_remover_por_nome("__TESTE_A", bd)) != GT_REMOVIDO || (resultado = gt_bd_remover_por_nome("__TESTE_B", bd)) != GT_REMOVIDO) {
        gt_testar_saida(saida, gt_str_resultado(resultado));
        return GT_TESTES_FALHA;
    }
    
    gt_bd_fechar(bd);
    
    return GT_TESTES_CONCLUIDO;
    
}

/**
 * Exibe a mensagem na saída infomada
 * @param saida saida um descritor de arquivo para imprimir a saída
 * @param msg uma mensagem a ser exibida
 */
void gt_testar_saida(FILE *saida, char *msg) {
    fprintf(saida, "%s: %s\n", GT_TESTES_SAIDA, msg);
}
