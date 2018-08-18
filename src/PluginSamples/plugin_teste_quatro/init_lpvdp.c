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

#include <stdio.h>
#include <string.h>

#include <lpvdp.h>

/* propriedades */
int estado;

/* prototipos */
lpvdp_argumentos jamais_voltarei(lpvdp_argumentos);
lpvdp_argumentos sucesso(lpvdp_argumentos);
void falha(lpvdp_resultado);

void init_lpvdp() {
    lpvdp_argumentos args;
    lpvdp_resultado lpvdp_r;
    
    estado = 1;
    
    printf("Ola de dentro do plugin teste quatro!\n");
    
    args.bytes = sizeof(int);
    args.dados = (void *) malloc(sizeof(int));
    *(int *) args.dados = (int) 100;
    
    /* Chamada a API da plataforma para paralelizar uma funcao */
    lpvdp_r = lpvdp_paralelizar("libsample_plugin_quatro.so", "jamais_voltarei", args, sucesso, falha);
    
    if(lpvdp_r != LPVDP_PARALELIZADO)
        printf("Falha ao solicitar a paralelizacao na plataforma do plugin quatro: %s\n", lpvdp_str_resultado(lpvdp_r));
    else 
        while(estado);
    
    printf("Bye de dentro do plugin quatro\n");
    
}

lpvdp_argumentos jamais_voltarei(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    memset(&ret, 0, sizeof(lpvdp_argumentos));
    printf("Ola de dentro da funcao que jamais retornara do plugin quatro, recebi: %d!\n", *(int*)args.dados);
    
    while(1);
    
    return ret;
}

lpvdp_argumentos sucesso(lpvdp_argumentos args) {
    lpvdp_argumentos ret;
    
    memset(&ret, 0, sizeof(lpvdp_argumentos));
    printf("Ola de dentro da funcao sucesso do plugin quatro, recebi: %d!\n", *(int*)args.dados);
    --estado;
    
    return ret;
}

void falha(lpvdp_resultado resultado) {
    printf("Ola de dentro da funcao falha do plugin quatro com resultado: %s\n", lpvdp_str_resultado(resultado));
    --estado;
}
