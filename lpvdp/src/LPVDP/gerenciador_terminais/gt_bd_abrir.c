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

#include <unistd.h>
#include <sys/stat.h> 
#include <pwd.h>
#include <string.h>
//#include <pthread.h>

#define GT_BD_NOME ".lpvdp_gt.bd"

/* estado */
/* TODO adicionar sincronismo usando POSIX threads (mutex) */

char *get_from_homed(char *);

/**
 * Abre o arquivo com os dados
 * @param modo as flags de permissões
 * @return o código de resultado
 */
int gt_bd_abrir(gt_bd_abertura_modo modo) {
    int bd;
    char *arquivo;
    arquivo = get_from_homed(GT_BD_NOME);
    if((bd = open(arquivo, modo)) < 0) {
        gt_bd_fechar(creat(arquivo, S_IRUSR | S_IWUSR));
        bd = open(arquivo, modo);
    }
    free(arquivo);
    return bd;
}

/**
 * @return o caminho informado precedido pelo diretório home do usuário
 */
char *get_from_homed(char *caminho) {
    char *homed, *novo_caminho;
    novo_caminho = NULL;
    if(caminho != NULL) {
        if((homed = getenv("XDG_CONF_HOME")) == NULL &&
            (homed = getenv("HOME")) == NULL)
            homed = getpwuid(getuid())->pw_dir;
        if((novo_caminho =
            (char *) malloc(sizeof(char)*(strlen(homed)+strlen(caminho)+1)))
            != NULL) {
            strcpy(novo_caminho, homed);
	    strcat(novo_caminho, "/");
	    strcat(novo_caminho, caminho);
        }
    }
    return novo_caminho;
}
