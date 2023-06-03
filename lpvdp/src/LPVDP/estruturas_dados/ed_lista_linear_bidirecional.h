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

#ifndef ED_LISTA_LINEAR_BIDIRECIONAL_H
#define ED_LISTA_LINEAR_BIDIRECIONAL_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    /* constantes */
    typedef enum ed_llbd_resultado {
        ED_LLBD_CRIADA = 0x1,
        ED_LLBD_VAZIA = 0x2,
        ED_LLBD_NAO_VAZIA = 0x3,
        ED_LLBD_DESLOCAMENTOS_INVERTIDOS = 0x4,
        ED_LLBD_NULA = 0x5,
        ED_LLBD_NO_NULO = 0x6,
        ED_LLBD_PADRAO_NULO = 0x7,
        ED_LLBD_NO_ENCONTRADO = 0x8,
        ED_LLBD_NO_NAO_ENCONTRADO = 0x9,
        ED_LLBD_NO_ATUALIZADO = 0xA,
        ED_LLBD_NO_REMOVIDO = 0xB,
        ED_LLBD_ATUALIZADA = 0xC,
        ED_LLBD_NO_CRIADO = 0xD
    } ed_llbd_resultado;
    
    /* tipos */
    typedef void* ed_llbd_carga;
    typedef unsigned int ed_llbd_desl;
    
    /* estruturas */
    typedef struct ed_llbd_no {
        ed_llbd_carga carga;
        struct ed_llbd_no *proximo, *anterior;
    } ed_llbd_no;

    typedef struct ed_llbd {
        ed_llbd_no *primeiro, *ultimo;
    } ed_llbd;    
    
    /* interface */
    ed_llbd_resultado ed_llbd_criar(ed_llbd **);
    ed_llbd_resultado ed_llbd_vazia(ed_llbd);    
    ed_llbd_resultado ed_llbd_adicionar(ed_llbd *, ed_llbd_no *);
    ed_llbd_resultado ed_llbd_remover(ed_llbd *, void *, ed_llbd_desl, ed_llbd_desl);
    ed_llbd_resultado ed_llbd_liberar(ed_llbd *);
    ed_llbd_resultado ed_llbd_atualizar(ed_llbd, ed_llbd_carga, void *, ed_llbd_desl, ed_llbd_desl);
    ed_llbd_resultado ed_llbd_buscar_por_carga(ed_llbd, ed_llbd_no **, void *, ed_llbd_desl, ed_llbd_desl);
    ed_llbd_no* ed_llbd_obter_primeiro(ed_llbd);
    ed_llbd_no* ed_llbd_obter_ultimo(ed_llbd);
    ed_llbd_resultado ed_llbd_conf_primeiro(ed_llbd *, ed_llbd_no *);
    ed_llbd_resultado ed_llbd_conf_ultimo(ed_llbd *, ed_llbd_no *);
    
    ed_llbd_resultado ed_llbd_no_criar(ed_llbd_no **);
    ed_llbd_carga ed_llbd_no_obter_carga(ed_llbd_no);
    ed_llbd_no* ed_llbd_no_obter_proximo(ed_llbd_no);
    ed_llbd_no* ed_llbd_no_obter_anterior(ed_llbd_no);
    ed_llbd_resultado ed_llbd_no_conf_carga(ed_llbd_no *, ed_llbd_carga);
    ed_llbd_resultado ed_llbd_no_conf_proximo(ed_llbd_no *, ed_llbd_no *);
    ed_llbd_resultado ed_llbd_no_conf_anterior(ed_llbd_no *, ed_llbd_no *);
    
    char *ed_llbd_str_resultado(ed_llbd_resultado);
    
#ifdef __cplusplus
}
#endif

#endif /* ED_LISTA_LINEAR_BIDIRECIONAL_H */

