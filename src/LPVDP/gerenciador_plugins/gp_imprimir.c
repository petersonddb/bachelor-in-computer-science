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

#include <dirent.h>

/**
 * Imprime os plugins de um
 * diretório na saída especificada
 * @param saida um arquivo de saída
 * @param rp o diretório com os plugins
 * @return o código de resultado
 */
gp_resultado gp_imprimir(FILE *saida, DIR *rp) {
    struct dirent *ent;
    
    if(rp == NULL)
        return GP_FALHA_REPOSITORIO_NULO;
    
    while((ent = readdir(rp)) != NULL)
        if(ent->d_type == DT_REG)
            fprintf(saida, "Plugin: %s\n", ent->d_name);
    
    return GP_IMPRESSOS;
    
}
