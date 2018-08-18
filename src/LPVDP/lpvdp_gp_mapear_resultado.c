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

#include <lpvdp.h>

/**
 * Mapeia um código de resultado de uma
 * operação em gerenciamento de plugins para o
 * código de resultado correspondente de
 * uma operação da plataforma
 * @param gp_r o código de resultado da operação em gerenciamento de plugins
 * @return o código de resultado de operação da plataforma
 */
lpvdp_resultado lpvdp_gp_mapear_resultado(gp_resultado gp_r) {
    switch(gp_r) {
        case GP_FALHA_REPOSITORIO_NULO: return LPVDP_GP_FALHA_REPOSITORIO_NULO;
        case GP_FALHA_TESTES: return LPVDP_TESTES_CONCLUIDO;
        case GP_FALHA_CARREGAMENTO: return LPVDP_GP_FALHA_CARREGAMENTO;
        case GP_FALHA_NOME_NULO: return LPVDP_GP_FALHA_NOME_NULO;
        default: return LPVDP_DESCONHECIDO;
    }
}
