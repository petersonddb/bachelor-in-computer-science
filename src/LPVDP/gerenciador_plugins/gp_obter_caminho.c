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

#define GP_PREFIXO_CAMINHO GP_REPOSITORIO

#include <string.h>

/**
 * cria o caminho completo de um
 * plugin
 * @param nome um nome de plugin
 * @return o caminho do plugin
 */
gp_caminho_t gp_obter_caminho(gp_nome_t nome) {
    gp_caminho_t n;
    char *repositorio;

    repositorio = gp_get_from_homed(GP_PREFIXO_CAMINHO);
    n = (gp_caminho_t) malloc(strlen(repositorio) + strlen(nome) + 1);
    strcpy(n, repositorio);
    strcat(n, "/");
    strcat(n, nome);
    
    return n;
}
