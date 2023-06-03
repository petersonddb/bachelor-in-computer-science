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

#include <dlfcn.h>
#include <stdio.h>

/* constantes */
#define INIT_FUNC "init_lpvdp"

/* tipos */
typedef void (*init)(void);

/**
 * executa um plugin
 * @param plugin o caminho do plugin
 * @return o código de resultado
 */
gp_resultado gp_exec(gp_caminho_t plugin) {
    
    gp_resultado resultado;
    init init_func;
    
    void* libhandle = dlopen(plugin, RTLD_NOW);
    if (!libhandle) 
        return GP_FALHA_CARREGAMENTO;
    
    init_func = dlsym(libhandle, INIT_FUNC);
    if(!init_func)
        resultado = GP_FALHA_CARREGAMENTO;
    else 
        init_func();
    
    dlclose(libhandle);
    
    return GP_EXECUTADO;
    
}
