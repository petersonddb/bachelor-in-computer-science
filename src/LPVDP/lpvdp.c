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

#include <string.h>

#include <pthread.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <dlfcn.h>

#define LPVDP_MSG "[LPVDP]"

/* comente para desativar msgs de depuracao */
#define DEBUG

/* tipos */
typedef struct {
    ed_llbd terminais;
    capacidade_t capacidade_maxima,
                 qtde_tarefas;
    pthread_t t_entrada;
    gt_porta_t porta_entrada;
} estado;

typedef struct {
    gp_nome_t plugin;
    gp_func_nome_t func;
    lpvdp_argumentos args;
    cb_sucesso sucesso;
    cb_fracasso fracasso;
} paralelizacao_argumentos;

typedef struct {
    gp_nome_t plugin;
    cb_msg msg;
} execucao_argumentos;

typedef enum {
    MSG_REALIZAR_TAREFA = 0x0,
    MSG_DISPONIVEL = 0x1,
    MSG_INDISPONIVEL = 0x2
} mensagem;

/* protótipos */
void *thread_execucao(void *);
void *thread_paralelizar(void *);
void *thread_entrada(void *);
void *thread_tarefa(void *);

lpvdp_resultado tarefa(gp_nome_t, gp_func_nome_t, lpvdp_argumentos *);

lpvdp_resultado abrir_conexao_rede(int *, gt_porta_t);
lpvdp_resultado conectar_rede_ipv4(int *, gt_terminal);

/* estado */
estado st;
pthread_mutex_t m_st;

/**
 * @param _st um estado
 * @return a lista de terminais do estado informado
 */
ed_llbd estado_obter_terminais(estado _st) {
    return _st.terminais;
}

/**
 * @param _st o ponteiro para um estado
 * @return o ponteiro para a lista de terminais do estado
 */
ed_llbd *estado_obter_ptr_terminais(estado *_st) {
    return &_st->terminais;
}

/**
 * @param _st um estado
 * @return a capacidade maxima de trabalhos suportavel pela plataforma do estado informado
 */
capacidade_t estado_obter_capacidade_maxima(estado _st) {
    return _st.capacidade_maxima;
}

/**
 * @param _st um estado
 * @return o numero de tarefas sendo realizada pela plataforma do estado informado
 */
capacidade_t estado_obter_qtde_tarefas(estado _st) {
    return _st.qtde_tarefas;
}

/**
 * @param _st um estado
 * @return o descritor da thread de entrada de solicitacoes remotas
 */
pthread_t estado_obter_thread_entrada(estado _st) {
    return _st.t_entrada;
}

/**
 * @param _st o ponteiro para um estado
 * @return um ponteiro para o descritor da thread de entrada de solicitacoes remotas do estado
 */
pthread_t *estado_obter_ptr_thread_entrada(estado *_st) {
    return &_st->t_entrada;
}

/**
 * @param _st um estado
 * @return a porta de entrada para solicitacoes remotas
 */
gt_porta_t estado_obter_porta_entrada(estado _st) {
    return _st.porta_entrada;
}

/**
 * configura a lista de terminais de um estado
 * @param _st um estado
 * @param terminais a nova lista de terminais para o estado informado
 */
void estado_conf_terminais(estado *_st, ed_llbd terminais) {
    _st->terminais = terminais;
}

/**
 * configura a capacidade maxima de trabalhos suportados em um estado
 * @param _st um estado
 * @param capacidade_maxima a nova capacidade
 */
void estado_conf_capacidade_maxima(estado *_st, capacidade_t capacidade_maxima) {
    _st->capacidade_maxima = capacidade_maxima;
}

/**
 * configura a qtde de tarefas sendo realizadas em um estado
 * @param _st um estado
 * @param qtde_tarefas a nova qtde de tarefas
 */
void estado_conf_qtde_tarefas(estado *_st, capacidade_t qtde_tarefas) {
    _st->qtde_tarefas = qtde_tarefas;
}

/**
 * configura o descritor da thread de entrada de solicitacoes remotas
 * @param _st um estado
 * @param t_entrada um descritor de thread
 */
void estado_conf_thread_entrada(estado *_st, pthread_t t_entrada) {
    _st->t_entrada = t_entrada;
}

/**
 * configura a porta de entrada para solicitacoes remotas
 * @param _st o ponteiro para um estado
 * @param porta_entrada a nova porta de entrada
 */
void estado_conf_porta_entrada(estado *_st, gt_porta_t porta_entrada) {
    _st->porta_entrada = porta_entrada;
}

/**
 * aumenta o contador do n. de tarefas sendo realizadas pela plataforma
 * @param qtde a qtde em que deve ser aumentado
 */
void aumentar_qtde_tarefas(capacidade_t qtde) {
    estado_conf_qtde_tarefas(&st, estado_obter_qtde_tarefas(st) + qtde);
}

/**
 * diminui o contador do n. de tarefas sendo realizadas pela plataforma
 * @param qtde a qtde em que deve ser diminuida
 */
void diminuir_qtde_tarefas(capacidade_t qtde) {
    aumentar_qtde_tarefas(-1 * qtde);
}

/**
 * inicializa a plataforma
 * @param capacidade_maxima a capacidade maxima de trabalho suportavel
 * @param porta_entrada a porta de entrada de solicitacoes remotas
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_init(capacidade_t capacidade_maxima, gt_porta_t porta_entrada) {
    gt_resultado gt_r;
    ed_llbd_resultado ed_llbd_r;
    
    ed_llbd *terminais;
    
    lpvdp_resultado lpvdp_r;
    
    int bd, *skt_entrada;
    
    if(pthread_mutex_init(&m_st, NULL))
        return LPVDP_FALHA_TRAVA_ESTADO;
    
    if((bd = gt_bd_abrir(GT_BD_ABERTURA_MODO_L)) <= 0)
        return LPVDP_GT_FALHA_ACESSO_BD;
        
    if((ed_llbd_r = ed_llbd_criar(&terminais)) != ED_LLBD_CRIADA) {
        gt_bd_fechar(bd);
        return lpvdp_ed_llbd_mapear_resultado(ed_llbd_r);
    }
    
    if((gt_r = gt_bd_buscar(terminais, bd)) != GT_CARREGADOS) {
        gt_bd_fechar(bd);
        return lpvdp_gt_mapear_resultado(gt_r);
    }
    
    gt_bd_fechar(bd);
    
    estado_conf_terminais(&st, *terminais);
    estado_conf_capacidade_maxima(&st, capacidade_maxima);
    estado_conf_qtde_tarefas(&st, 0);
    estado_conf_porta_entrada(&st, porta_entrada);
    
    skt_entrada = (int *) malloc(sizeof(int));
    if((lpvdp_r = abrir_conexao_rede(skt_entrada, porta_entrada)) != LPVDP_CONEXAO_REDE_ABERTA)
        return lpvdp_r;
    
    if(pthread_create(estado_obter_ptr_thread_entrada(&st), NULL, thread_entrada, (void *) skt_entrada))
        return LPVDP_FALHA_TENTRADA;
    
    return LPVDP_INICIADO;
}

/**
 * abre uma escuta para receber mensagens remotas
 * @param skt um ponteiro para o socket
 * @param porta a porta a escutar
 * @return o codigo de resultado
 */
lpvdp_resultado abrir_conexao_rede(int *skt, gt_porta_t porta) {
    struct sockaddr_in endereco;
    
    if((*skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return LPVDP_FALHA_ABRIR_CONEXAO_REDE;
    
    memset(&endereco, 0, sizeof(struct sockaddr_in));
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = htonl(INADDR_ANY);
    endereco.sin_port = htons(porta);
    
    if(bind(*skt, (struct sockaddr *) &endereco, sizeof(struct sockaddr)) < 0)
        return LPVDP_FALHA_ABRIR_CONEXAO_REDE;
    
    if(listen(*skt, estado_obter_capacidade_maxima(st)) < 0)
        return LPVDP_FALHA_ABRIR_CONEXAO_REDE;
    
    return LPVDP_CONEXAO_REDE_ABERTA;
}

/**
 * conectar-se a um endereco de rede
 * remoto
 * @param skt um ponteiro para o inteiro que recebera o descritor da conexao
 * @param t um terminal com os dados para realizar a conexao
 * @return o codigo de resultado
 */
lpvdp_resultado conectar_rede_ipv4(int *skt, gt_terminal t) {
    struct sockaddr_in endereco;
    
    gt_ip4_endereco ip4;
    
    if((*skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        return LPVDP_FALHA_ABRIR_CONEXAO_REDE;
    
    ip4 = gt_obter_ip4_de_endereco(t.endereco);
    
    memset(&endereco, 0, sizeof(struct sockaddr_in));
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = inet_addr(ip4.ip_endereco);
    endereco.sin_port = htons(ip4.porta);
    
    if(connect(*skt, (struct sockaddr *) &endereco, sizeof(struct sockaddr)) < 0) {
        close(*skt);
        return LPVDP_FALHA_ABRIR_CONEXAO_REDE;
    }
    
    return LPVDP_CONEXAO_REDE_ABERTA;
}

/**
 * abre uma porta de entrada
 * para solicitacoes remotas
 * @param um ponteiro para um inteiro cujo o valor seja um descritor de um socket aberto, vinculado e escutando
 * @return nada
 */
void *thread_entrada(void *args) {
    int *skt, cliente_tamanho, c_skt, bytes_recebidos, bytes;
    
    struct sockaddr_in cliente;
    
    skt = (int *) args;
    
    mensagem msg;
    
    do {
        memset(&cliente, 0, sizeof(struct sockaddr_in));
        cliente_tamanho = sizeof(cliente);
        if((c_skt = accept(*skt, (struct sockaddr *) &cliente, &cliente_tamanho)) >= 0) {
            
#ifdef DEBUG
            printf("%s: New client connected!\n", LPVDP_MSG);
#endif            
            bytes_recebidos = 0;
            memset(&msg, 0, sizeof(mensagem));
            do {
                if((bytes = recv(c_skt, &msg + bytes_recebidos, sizeof(mensagem) - bytes_recebidos, 0)) < 1)
                    break;
                bytes_recebidos += bytes;
            } while(bytes_recebidos < sizeof(mensagem));
            
            if(bytes > 0) {
                switch(msg) {
                    case MSG_REALIZAR_TAREFA:
#ifdef DEBUG
            printf("%s: New task requested!\n", LPVDP_MSG);
#endif
                        {
                            pthread_t tid;
                            int *ptr_skt;
                            
                            ptr_skt = (int *) malloc(sizeof(int));
                            *ptr_skt = c_skt;
                            if(pthread_create(&tid, NULL, thread_tarefa, (void *) ptr_skt)) {
                                close(c_skt);
                                free(ptr_skt);
                            }
                        }
                        break;
                    default:
                        close(c_skt);
                }
            }
            
        }
    } while(c_skt >= 0);
    
    close(*skt);
}

/**
 * mostra todos os plugins disponíveis
 * @param saida o arquivo para escrever o resultado
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_gp_listar(FILE *saida) {
    gp_resultado resultado;
    
    if((resultado = gp_imprimir(saida, gp_abrir())) != GP_IMPRESSOS)
        return lpvdp_gp_mapear_resultado(resultado);
    
    return LPVDP_IMPRESSOS;
}

/**
 * mostra todos os terminais cadastrados
 * @param saida o arquivo para escrever o resultado
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_gt_listar(FILE *saida) {
    gt_resultado resultado;
    int bd;
    
    if((bd = gt_bd_abrir(GT_BD_ABERTURA_MODO_L)) <= 0)
        return LPVDP_GT_FALHA_ACESSO_BD;
    
    fprintf(saida, "Database:\n");
    if((resultado = gt_bd_imprimir_ipv4(saida, bd)) != GT_IMPRESSOS)
        return lpvdp_gt_mapear_resultado(resultado);
    
    gt_bd_fechar(bd);
    
    fprintf(saida, "\nLoaded:\n");
    
    pthread_mutex_lock(&m_st);
    
    if((resultado = gt_ed_llbd_imprimir_ipv4(estado_obter_terminais(st), saida)) != GT_IMPRESSOS)
        return lpvdp_gt_mapear_resultado(resultado);
    
    pthread_mutex_unlock(&m_st);
    
    return LPVDP_IMPRESSOS;
}

/**
 * testa todos os modulos do sistema
 * @param saida o arquivo para escrever o resultado
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_testar(FILE *saida) {
    gt_resultado gt_r;
    gp_resultado gp_r;
    
    if((gt_r = gt_testar(saida)) != GT_TESTES_CONCLUIDO)
        return lpvdp_gt_mapear_resultado(gt_r);
    
    if((gp_r = gp_testar(saida)) != GP_TESTES_CONCLUIDO)
        return lpvdp_gp_mapear_resultado(gp_r);
    
    return LPVDP_TESTES_CONCLUIDO;
}

/**
 * inclui um novo terminal na plataforma
 * @param terminal o novo terminal
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_gt_incluir(gt_terminal terminal) {
    gt_resultado gt_r;
    gt_terminal *t;
    
    int bd;
    
    if((bd = gt_bd_abrir(GT_BD_ABERTURA_MODO_LE)) <= 0)
        return lpvdp_gt_mapear_resultado(gt_r);
    
    if((gt_r = gt_bd_incluir(terminal, bd)) != GT_INCLUIDO) {
        gt_bd_fechar(bd);
        return lpvdp_gt_mapear_resultado(gt_r);
    }
    gt_bd_fechar(bd);
    
    if((gt_r = gt_criar(&t)) != GT_CRIADO)
        return lpvdp_gt_mapear_resultado(gt_r);
    memcpy(t, &terminal, sizeof(gt_terminal));
    
    pthread_mutex_lock(&m_st);
    
    if((gt_r = gt_ed_llbd_adicionar(estado_obter_ptr_terminais(&st), t)) != GT_INCLUIDO)
        return lpvdp_gt_mapear_resultado(gt_r);
    
    pthread_mutex_unlock(&m_st);
    
    return LPVDP_GT_INCLUIDO;
}

/**
 * executa um plugin
 * @param plugin o caminho do plugin
 * @return o codigo do resultado
 */
lpvdp_resultado lpvdp_gp_exec(gp_nome_t plugin, cb_msg msg) {
    execucao_argumentos *e_args;
    
    pthread_t tid;
    
    if((e_args = (execucao_argumentos *) malloc(sizeof(execucao_argumentos))) == NULL)
        return LPVDP_FALHA_FALTA_MEMORIA;
    
    strcpy(e_args->plugin, plugin);
    e_args->msg = msg;
    
    if(pthread_create(&tid, NULL, thread_execucao, (void *) e_args))
        return LPVDP_FALHA_PARALELIZACAO;
    
    return LPVDP_GP_EXECUTADO;
}

/**
 * poe um plugin em execucao
 * @param args os dados para execucao do plugin em forma de uma estrutura execucao_argumentos
 * @return nada
 */
void *thread_execucao(void *args) {
    execucao_argumentos e_args;
    
    gp_resultado gp_r;
    
    e_args = *(execucao_argumentos *) args;
    
    free((execucao_argumentos *) args);
    
    if((gp_r = gp_exec(gp_obter_caminho(e_args.plugin))) != GP_EXECUTADO)
        e_args.msg(lpvdp_gp_mapear_resultado(gp_r));
    else
        e_args.msg(LPVDP_GP_EXECUTADO);
}

/**
 * inicia uma funcao de um plugin paralela
 * e distribuidamente, esta funcao retornara
 * imediatamente
 * @param nome_plugin o nome do plugin
 * @param nome_func o nome da funcao do plugin
 * @param args os argumentos para a funcao
 * @param sucesso uma funcao para ser executada com os argumentos de retorno, em caso de sucesso
 * @param fracasso uma funcao para ser executada em caso de fracasso
 * @return o codigo de resultado
 */
lpvdp_resultado lpvdp_paralelizar(char *nome_plugin, char *nome_func, lpvdp_argumentos args, cb_sucesso sucesso, cb_fracasso fracasso) {
    gp_resultado gp_r;
    
    paralelizacao_argumentos *p_args;
    
    pthread_t tid;
    
    p_args = (paralelizacao_argumentos *) malloc(sizeof(paralelizacao_argumentos));
    
    if((gp_r = gp_obter_nome(nome_plugin, p_args->plugin)) != GP_COPIADO)
        return lpvdp_gp_mapear_resultado(gp_r);
    
    if((gp_r = gp_func_obter_nome(nome_func, p_args->func)) != GP_COPIADO)
        return lpvdp_gp_mapear_resultado(gp_r);
    
    //if(sucesso == NULL)
        //return LPVDP_FALHA_CB_SUCESSO_NULO;
    p_args->sucesso = sucesso;
    
    //if(fracasso == NULL)
        //return LPVDP_FALHA_CB_FRACASSO_NULO;
    p_args->fracasso = fracasso;
    
    p_args->args = args;
    
    if(pthread_create(&tid, NULL, thread_paralelizar, (void * ) p_args))
        return LPVDP_FALHA_PARALELIZACAO;
 
    return LPVDP_PARALELIZADO;
    
}

/**
 * uma thread para manter comunicacao
 * com o servidor que ira/esta trabalhando
 * na execucao da tarefa solicitada
 * @param args um conjunto de argumentos no formato paralelizacao_argumentos
 * @return nada
 */
void *thread_paralelizar(void *args) {

    ed_llbd_no *no;
    
    gt_terminal *t;
    
    paralelizacao_argumentos p_args;
    
    p_args = *(paralelizacao_argumentos *) args;
    
#ifdef DEBUG
    printf("%s: Thread for coordinate the task execution is running!\n", LPVDP_MSG);
#endif
    
    pthread_mutex_lock(&m_st);
    
    no = ed_llbd_obter_primeiro(estado_obter_terminais(st));    
    while(no != NULL) {
        t = (gt_terminal *) ed_llbd_no_obter_carga(*no);
        if(strcmp(t->nome, "")) {
            int skt;
            
            if(conectar_rede_ipv4(&skt, *t) == LPVDP_CONEXAO_REDE_ABERTA) {
                int bytes, bytes_recebidos;
            
                mensagem msg;
                
                lpvdp_argumentos ret_args;
                
                msg = MSG_REALIZAR_TAREFA;
                if(send(skt, &msg, sizeof(mensagem), 0) < sizeof(mensagem)) {
                    close(skt);
                    continue;
                }

                bytes_recebidos = 0;
                memset(&msg, 0, sizeof(mensagem));
                do {
                    if((bytes = recv(skt, &msg + bytes_recebidos, sizeof(mensagem) - bytes_recebidos, 0)) <= 0)
                        break;
                    bytes_recebidos += bytes;
                } while(bytes_recebidos < sizeof(mensagem));
                
                if(bytes <= 0 || msg != MSG_DISPONIVEL) {
                    close(skt);
                    no = ed_llbd_no_obter_proximo(*no);
                    continue;
                }
                
                pthread_mutex_unlock(&m_st);
                
                if(send(skt, &p_args, sizeof(paralelizacao_argumentos), 0) < sizeof(paralelizacao_argumentos)) {
                    close(skt);
                    continue;
                }
                
                if(send(skt, p_args.args.dados, p_args.args.bytes, 0) < sizeof(p_args.args.bytes)) {
                    close(skt);
                    continue;
                }
                
                bytes_recebidos = 0;
                memset(&msg, 0, sizeof(mensagem));
                do {
                    if((bytes = recv(skt, &msg + bytes_recebidos, sizeof(mensagem) - bytes_recebidos, 0)) <= 0)
                        break;
                    bytes_recebidos += bytes;
                } while(bytes_recebidos < sizeof(mensagem));
                
                if(bytes <= 0 || msg != MSG_DISPONIVEL) {
                    close(skt);
                    no = ed_llbd_no_obter_proximo(*no);
                    continue;
                }
                
                pthread_mutex_lock(&m_st);
                
                bytes_recebidos = 0;
                memset(&ret_args, 0, sizeof(lpvdp_argumentos));
                do {
                    if((bytes = recv(skt, &ret_args + bytes_recebidos, sizeof(lpvdp_argumentos) - bytes_recebidos, 0)) <= 0)
                        break;
                    bytes_recebidos += bytes;
                } while(bytes_recebidos < sizeof(lpvdp_argumentos));
                
                if(bytes <= 0) {
                    close(skt);
                    continue;
                }
                
                bytes_recebidos = 0;
                ret_args.dados = (void *) malloc(ret_args.bytes);
                do {
                    if((bytes = recv(skt, ret_args.dados + bytes_recebidos, ret_args.bytes - bytes_recebidos, 0)) <= 0)
                        break;
                    bytes_recebidos += bytes;
                } while(bytes_recebidos < ret_args.bytes);
                
                if(bytes <= 0) {
                    close(skt);
                    continue;
                }
                
                if(p_args.sucesso != NULL)
                    p_args.sucesso(ret_args);
                
                close(skt);
                
                pthread_mutex_unlock(&m_st);
                return NULL;
            }
            
        }
        no = ed_llbd_no_obter_proximo(*no);
    }
    
    pthread_mutex_unlock(&m_st);
    
    if(p_args.fracasso != NULL)
        p_args.fracasso(LPVDP_FALHA_GT_INDISPONIVEL);
    
}

/**
 * coordena a comunicacao durante 
 * a execucao de uma tarefa solicitada
 * remotamente
 * @param args um ponteiro para o descritor do socket da conexao que solicitou a tarefa
 * @return nada
 */
void *thread_tarefa(void *args) {
    int skt, bytes, bytes_recebidos;
    
    mensagem msg;
    
    paralelizacao_argumentos p_args;
    
    lpvdp_resultado lpvdp_r;
    
    skt = *(int *) args;
    
#ifdef DEBUG
    printf("%s: Thread for coordinate the task execution is running!\n", LPVDP_MSG);
#endif
    
    pthread_mutex_lock(&m_st);
    
    if(estado_obter_capacidade_maxima(st) > estado_obter_qtde_tarefas(st)) {
        msg = MSG_DISPONIVEL;
    } else {
#ifdef DEBUG
    printf("%s: Platform unavailable (overloaded)!\n", LPVDP_MSG);
#endif
        msg = MSG_INDISPONIVEL;
        send(skt, &msg, sizeof(mensagem), 0);
        close(skt);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    if(send(skt, &msg, sizeof(mensagem), 0) < sizeof(mensagem)) {
        close(skt);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    aumentar_qtde_tarefas(1);
    pthread_mutex_unlock(&m_st);
    
    bytes_recebidos = 0;
    memset(&p_args, 0, sizeof(paralelizacao_argumentos));
    do {
        if((bytes = recv(skt, &p_args + bytes_recebidos, sizeof(paralelizacao_argumentos) - bytes_recebidos, 0)) <= 0)
            break;
        bytes_recebidos += bytes;
    } while(bytes_recebidos < sizeof(paralelizacao_argumentos));
    
    if(bytes <= 0) {
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    bytes_recebidos = 0;
    p_args.args.dados = (void *) malloc(p_args.args.bytes);
    do {
        if((bytes = recv(skt, p_args.args.dados + bytes_recebidos, p_args.args.bytes - bytes_recebidos, 0)) <= 0)
            break;
        bytes_recebidos += bytes;
    } while(bytes_recebidos < p_args.args.bytes);
    
    if(bytes <= 0) {
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    if((lpvdp_r = tarefa(p_args.plugin, p_args.func, &p_args.args)) != LPVDP_GP_EXECUTADO) {
#ifdef DEBUG
    printf("%s: Platform unavailable (the plugin and/or its procedure does not exist)!\n", LPVDP_MSG);
#endif
        msg = MSG_INDISPONIVEL;
        send(skt, &msg, sizeof(mensagem), 0);
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
        
    msg = MSG_DISPONIVEL;
    if(send(skt, &msg, sizeof(mensagem), 0) < 0) {
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    if(send(skt, &p_args.args, sizeof(lpvdp_argumentos), 0) <= 0) {
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    if(send(skt, p_args.args.dados, p_args.args.bytes, 0) <= 0) {
        close(skt);
        pthread_mutex_lock(&m_st);
        diminuir_qtde_tarefas(1);
        pthread_mutex_unlock(&m_st);
        return NULL;
    }
    
    pthread_mutex_lock(&m_st);
    diminuir_qtde_tarefas(1);
    pthread_mutex_unlock(&m_st);
    close(skt);
    return NULL;
    
}

/**
 * executa uma funcao de
 * um plugin
 * @param nome o nome do plugin
 * @param func_nome o nome da funcao do plugin
 * @param args um ponteiro para os argumentos para a funcao e que recebera o retorno
 * @return o codigo de resultado
 */
lpvdp_resultado tarefa(gp_nome_t nome, gp_func_nome_t func_nome, lpvdp_argumentos *args) {
    
    lpvdp_resultado resultado;
    gp_func gp_func;
    
    void* libhandle = dlopen(gp_obter_caminho(nome), RTLD_NOW);
    if (!libhandle) 
        return lpvdp_gp_mapear_resultado(GP_FALHA_CARREGAMENTO);
    
    gp_func = dlsym(libhandle, func_nome);
    if(!gp_func)
        resultado = lpvdp_gp_mapear_resultado(GP_FALHA_CARREGAMENTO);
    else {
        *args = gp_func(*args);
        resultado = LPVDP_GP_EXECUTADO;
    }
    
    dlclose(libhandle);
    
    return resultado;
}
