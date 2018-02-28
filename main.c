#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>


#define LIMPA_TELA "clear"

typedef struct
{
    char nome[50], sobrenome[50], endereco[100], telefone[16], email[100];
}Pessoa;

void tiraPulaLinha(char *palavra)
{
    int i=0;
    while(palavra[i] != '\0' && palavra[i] != '\n' )
        i++;
    palavra[i] = '\0';
}

void pressENTER()
{
    printf(" ---------------------------------------------------------\n");
    printf("|    Pressione ENTER para retornar ao menu principal.     |\n");
    printf(" ---------------------------------------------------------\n");
    getchar();
    system(LIMPA_TELA);

}

void salvaQuantidade(int *n, char *enderecoTamanho)
{
    FILE *tamanhoAgenda = fopen(enderecoTamanho,"wb");

    fwrite(n, sizeof(int), 1, tamanhoAgenda);

    fclose(tamanhoAgenda);
}

void adquireQuantidade(int *n, char *enderecoTamanho)
{
    FILE *tamanhoAgenda = fopen(enderecoTamanho,"rb");

    if(tamanhoAgenda == NULL)
    {
        tamanhoAgenda = fopen(enderecoTamanho,"wb");
        *n=0;
        fwrite(n, sizeof(int), 1, tamanhoAgenda);
        fclose(tamanhoAgenda);
    }

    fread(n, sizeof(int), 1, tamanhoAgenda);

    fclose(tamanhoAgenda);
}

Pessoa *criaAgenda (int *n, char *enderecoTamanho, char *enderecoAgenda)
{
    int quantidade;
    Pessoa *minhaAgenda;
    adquireQuantidade(n, enderecoTamanho);
    quantidade = *n + 1;

    minhaAgenda = malloc(sizeof(Pessoa) * quantidade);

    if(*n > 0)
    {
        FILE *save = fopen(enderecoAgenda,"rb");

        fread(minhaAgenda, sizeof(Pessoa), (*n), save);

        fclose(save);
    }

    return minhaAgenda;
}

int menu()
{
    int opcao;

    printf(" ---------------------------------------------------------\n");
    printf("|      ..:: Agenda Eletrônica - Agendator 3000 ::..       |\n");
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    printf("|   Selecione a opção desejada abaixo:                    |\n");
    printf("|    1 - Incluir:                                         |\n");
    printf("|    2 - Editar:                                          |\n");
    printf("|    3 - Listar:                                          |\n");
    printf("|    4 - Buscar:                                          |\n");
    printf("|    5 - Excluir:                                         |\n");
    printf("|    0 - Encerrar:                                        |\n");
    printf(" ---------------------------------------------------------\n");

    scanf("%d",&opcao);
    getchar();

    return opcao;
}

int trocarPorNome(Pessoa primeira, Pessoa segunda)
{
    if(strcmp(primeira.nome, segunda.nome) == 0 )
    {
        if(strcmp(primeira.sobrenome, segunda.sobrenome) > 0 )
        {
            return 1;
        }

        return 0;
    }
    else if(strcmp(primeira.nome, segunda.nome) > 0 )
    {
        return 1;
    }
    return 0;
}

void BubbleSort(Pessoa *agenda, int *n, int (*funcao)(Pessoa, Pessoa) )
{
    int i,j;
    for(i=0; i<*n-1; i++)
    {
        for(j=0; j<*n-1; j++)
        {
            if( funcao(agenda[j], agenda[j+1]) > 0 )
            {
                Pessoa temp = agenda[j];
                agenda[j] = agenda[j+1];
                agenda[j+1] = temp;
            }
        }
    }
}


void incluir(Pessoa *agenda, int *n)
{
    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|     Você possui %d registros salvos na sua agenda!      |\n",*n);
    printf(" ---------------------------------------------------------\n");
    printf(" ---------------------------------------------------------\n");
    printf("|         Para adicionar uma nova pessoa, insira:         |\n");
    printf(" ---------------------------------------------------------\n");
    printf(" ---------------------------------------------------------\n");
    printf("|                          NOME:                          |\n");
    printf(" ---------------------------------------------------------\n");
    fflush(stdin);
    fgets(agenda[*n].nome,50,stdin);
    tiraPulaLinha(agenda[*n].nome);
    printf(" ---------------------------------------------------------\n");
    printf("|                        SOBRENOME:                       |\n");
    printf(" ---------------------------------------------------------\n");
    fflush(stdin);
    fgets(agenda[*n].sobrenome,50,stdin);
    tiraPulaLinha(agenda[*n].sobrenome);
    printf(" ---------------------------------------------------------\n");
    printf("|                        TELEFONE:                        |\n");
    printf(" ---------------------------------------------------------\n");
    fflush(stdin);
    fgets(agenda[*n].telefone,16,stdin);
    tiraPulaLinha(agenda[*n].telefone);
    printf(" ---------------------------------------------------------\n");
    printf("|                        ENDEREÇO:                        |\n");
    printf(" ---------------------------------------------------------\n");
    fflush(stdin);
    fgets(agenda[*n].endereco,100,stdin);
    tiraPulaLinha(agenda[*n].endereco);
    printf(" ---------------------------------------------------------\n");
    printf("|                         EMAIL:                          |\n");
    printf(" ---------------------------------------------------------\n");
    fflush(stdin);
    fgets(agenda[*n].email,100,stdin);
    tiraPulaLinha(agenda[*n].email);

    (*n)++;

}

void editar(Pessoa *agenda, int *n) {
    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|  Qual o numero do registro que você gostaria de editar? |\n");
    printf(" ---------------------------------------------------------\n");

    int i, opcao, opcao2;
    printf(" ---------------------------------------------------------\n");
    for (i = 0; i < *n; i++) {
        printf("|%d: %s\n", (i + 1), agenda[i].nome);
    }
    printf(" ---------------------------------------------------------\n");
    scanf("%d", &opcao);
    printf(" ---------------------------------------------------------\n");
    printf("|              O que você gostaria de editar?\n");
    printf("| 1- Nome: %s\n", agenda[opcao - 1].nome);
    printf("| 2- Sobrenome: %s\n", agenda[opcao - 1].sobrenome);
    printf("| 3- Telefone: %s\n", agenda[opcao - 1].telefone);
    printf("| 4- Endereço: %s\n", agenda[opcao - 1].endereco);
    printf("| 5- Email: %s\n", agenda[opcao - 1].email);
    printf("| 6- Cancelar\n");
    printf(" ---------------------------------------------------------\n");
    scanf("%d", &opcao2);

    getchar();

    if (opcao2 == 1)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|           Insira o novo NOME para o registro.           |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(agenda[opcao - 1].nome, 50, stdin);
        tiraPulaLinha(agenda[opcao - 1].nome);
    }

    else if (opcao2 == 2)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|         Insira o novo SOBRENOME para o registro.        |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(agenda[opcao - 1].sobrenome, 50, stdin);
        tiraPulaLinha(agenda[opcao - 1].sobrenome);
    }

    else if (opcao2 == 3)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|         Insira o novo TELEFONE para o registro.         |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(agenda[opcao - 1].telefone, 16, stdin);
        tiraPulaLinha(agenda[opcao - 1].telefone);
    }

    else if (opcao2 == 4)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|         Insira o novo ENDEREÇO para o registro.         |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(agenda[opcao - 1].endereco, 100, stdin);
        tiraPulaLinha(agenda[opcao - 1].endereco);
    }

    else if (opcao2 == 5)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|           Insira o novo EMAIL para o registro.          |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(agenda[opcao - 1].email, 100, stdin);
        tiraPulaLinha(agenda[opcao - 1].email);
    }

    else if (opcao2 == 6)
    {
        //não faz nada.
    }

    else
    {
        printf(" ---------------------------------------------------------\n");
        printf("|    Opcao Inexistente! Favor selecionar outra opcao.     |\n");
        printf(" ---------------------------------------------------------\n");
        editar(agenda, n);
    }
}

void listarNomes(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|        Exibindo %d NOME(S) salvos na sua agenda!        |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|                       %d     \n",(i+1));
        printf("| %s\n",agenda[i].nome);
    }
    printf(" ---------------------------------------------------------\n");

}

void listarSobrenomes(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|      Exibindo %d SOBRENOME(S) salvos na sua agenda!     |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|                       %d     \n",(i+1));
        printf("| %s\n",agenda[i].sobrenome);
    }
    printf(" ---------------------------------------------------------\n");
}

void listarEnderecos(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|      Exibindo %d ENDEREÇO(S) salvos na sua agenda!      |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|                       %d     \n",(i+1));
        printf("| %s\n",agenda[i].endereco);
    }
    printf(" ---------------------------------------------------------\n");
}

void listarTelefones(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|      Exibindo %d TELEFONE(S) salvos na sua agenda!      |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|                       %d     \n",(i+1));
        printf("| %s\n",agenda[i].telefone);
    }
    printf(" ---------------------------------------------------------\n");

}

void listarEmails(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|        Exibindo %d EMAIL(S) salvos na sua agenda!       |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|                       %d     \n",(i+1));
        printf("| %s\n",agenda[i].email);
    }
    printf(" ---------------------------------------------------------\n");

}

void listarTudo(Pessoa *agenda, int *n)
{
    int i;

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|      Exibindo %d registro(s) salvos na sua agenda!      |\n",*n);
    printf(" ---------------------------------------------------------\n");

    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|             %s %s\n",agenda[i].nome,agenda[i].sobrenome);
        printf("| Telefone: %s\n",agenda[i].telefone);
        printf("| Email: %s\n",agenda[i].email);
        printf("| Endereço: %s\n",agenda[i].endereco);
        printf("|\n");
        printf(" ---------------------------------------------------------\n");
    }

}

void menuListar(Pessoa *agenda, int *n)
{
    int opcao;

    system(LIMPA_TELA);
    printf("\n ---------------------------------------------------------\n");
    printf("|   Selecione como gostaria que sua agenda seja listada:  |\n");
    printf("|    1 - Registros Completos:                             |\n");
    printf("|    2 - Nomes:                                           |\n");
    printf("|    3 - Sobrenomes:                                      |\n");
    printf("|    4 - Endereços:                                       |\n");
    printf("|    5 - Telefones:                                       |\n");
    printf("|    6 - Emails:                                          |\n");
    printf("|    0 - Sair do menu:                                    |\n");
    printf(" ---------------------------------------------------------\n");

    scanf("%d",&opcao);
    getchar();

    if(opcao == 2)
    {
        listarNomes(agenda,n);
        pressENTER();
    }

    else if(opcao == 3)
    {
        listarSobrenomes(agenda,n);
        pressENTER();
    }

    else if(opcao == 4)
    {
        listarEnderecos(agenda,n);
        pressENTER();
    }

    else if(opcao == 5)
    {
        listarTelefones(agenda,n);
        pressENTER();
    }

    else if(opcao == 6)
    {
        listarEmails(agenda,n);
        pressENTER();
    }

    else if(opcao == 1)
    {
        listarTudo(agenda,n);
        pressENTER();

    }

    else if(opcao == 0)
    {
        //Não faz nada.
    }

    else
    {
        printf(" ---------------------------------------------------------\n");
        printf("|    Opcao Inexistente! Favor selecionar outra opcao.     |\n");
        printf(" ---------------------------------------------------------\n");
        menuListar(agenda,n);
    }
}

void excluir(Pessoa *agenda, int *n)
{
    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|  Qual o numero do registro que você gostaria de apagar? |\n");
    printf(" ---------------------------------------------------------\n");

    int i, opcao;
    printf(" ---------------------------------------------------------\n");
    for (i=0; i< *n; i++)
    {
        printf("|%d: %s\n",(i+1),agenda[i].nome);
    }
    printf(" ---------------------------------------------------------\n");
    scanf("%d",&opcao);
    for (i=opcao; i< *n; i++)
    {
        agenda[i-1] = agenda[i];
    }
    (*n)--;

    getchar();
    fflush(stdin);

}

void salvar(Pessoa *agenda, int *n, char *enderecoAgenda, char *enderecoTamanho)
{
    FILE *save = fopen(enderecoAgenda,"wb");

    fwrite(agenda, sizeof(Pessoa), *n, save);

    fclose(save);

    salvaQuantidade(n, enderecoTamanho);

    system(LIMPA_TELA);
    printf(" ---------------------------------------------------------\n");
    printf("|                     Mudanças Salvas!                    |\n");
    printf(" ---------------------------------------------------------\n");
}


void exibirBuscado(Pessoa *agenda, int indice, int achou)
{
    if(indice == -1)
    {
        system(LIMPA_TELA);
        printf(" ---------------------------------------------------------\n");
        printf("|                Registro não encontrado!                 |\n");
        printf(" ---------------------------------------------------------\n");

    }

    else
    {
        if(achou == 0)
        {
            system(LIMPA_TELA);
            printf(" ---------------------------------------------------------\n");
            printf("|           Exibindo os dados de sua pesquisa!            |\n");
            printf(" ---------------------------------------------------------\n");
        }

        printf(" ---------------------------------------------------------\n");
        printf("| Nome: %s\n",agenda[indice].nome);
        printf("| Sobrenome: %s\n",agenda[indice].sobrenome);
        printf("| Telefone: %s\n",agenda[indice].telefone);
        printf("| Email: %s\n",agenda[indice].email);
        printf("| Endereço: %s\n",agenda[indice].endereco);
        printf(" ---------------------------------------------------------\n");
    }
}

void busca(Pessoa* agenda, int *n, Pessoa buscado)
{
    int i, achou=0;

    for(i=0;i<*n; i++)
    {
        if( strcmp(agenda[i].nome, buscado.nome) == 0)
        {
            exibirBuscado(agenda, i, achou);
            achou = 1;
        }

        if( strcmp(agenda[i].sobrenome, buscado.sobrenome) == 0)
        {
            exibirBuscado(agenda, i, achou);
            achou = 1;
        }

        if( strcmp(agenda[i].endereco, buscado.endereco) == 0)
        {
            exibirBuscado(agenda, i, achou);
            achou = 1;
        }

        if( strcmp(agenda[i].telefone, buscado.telefone) == 0)
        {
            exibirBuscado(agenda, i, achou);
            achou = 1;
        }

        if( strcmp(agenda[i].email, buscado.email) == 0)
        {
            exibirBuscado(agenda, i, achou);
            achou = 1;
        }
    }

    if(achou == 0)
    {
        exibirBuscado(agenda, -1, achou);
    }
}

void menuBusca(Pessoa *agenda, int *n)
{
    system(LIMPA_TELA);
    printf("\n ---------------------------------------------------------\n");
    printf("|   Selecione como gostaria de fazer sua busca:           |\n");
    printf("|    1 - Nomes:                                           |\n");
    printf("|    2 - Sobrenomes:                                      |\n");
    printf("|    3 - Endereços:                                       |\n");
    printf("|    4 - Telefones:                                       |\n");
    printf("|    5 - Emails:                                          |\n");
    printf("|    0 - Sair do menu:                                    |\n");
    printf(" ---------------------------------------------------------\n");

    int opcao;

    scanf("%d",&opcao);
    getchar();

    Pessoa buscar;

    if(opcao == 1)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|          Digite o nome que gostaria de buscar:          |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(buscar.nome, 50, stdin);
        tiraPulaLinha(buscar.nome);
        busca(agenda, n, buscar);
        pressENTER();
    }

    else if(opcao == 2)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|        Digite o sobrenome que gostaria de buscar:       |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(buscar.sobrenome, 50, stdin);
        tiraPulaLinha(buscar.sobrenome);
        busca(agenda, n, buscar);
        pressENTER();
    }

    else if(opcao == 3)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|        Digite o endereço que gostaria de buscar:        |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(buscar.endereco, 100, stdin);
        tiraPulaLinha(buscar.endereco);
        busca(agenda, n, buscar);
        pressENTER();
    }

    else if(opcao == 4)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|        Digite o telefone que gostaria de buscar:        |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(buscar.telefone, 16, stdin);
        tiraPulaLinha(buscar.telefone);
        busca(agenda, n, buscar);
        pressENTER();
    }

    else if(opcao == 5)
    {
        printf(" ---------------------------------------------------------\n");
        printf("|          Digite o email que gostaria de buscar:         |\n");
        printf(" ---------------------------------------------------------\n");
        fflush(stdin);
        fgets(buscar.email, 100, stdin);
        tiraPulaLinha(buscar.email);
        busca(agenda, n, buscar);
        pressENTER();
    }

    else if(opcao == 0)
    {
        system(LIMPA_TELA);
    }

    else
    {
        printf(" ---------------------------------------------------------\n");
        printf("|    Opcao Inexistente! Favor selecionar outra opcao.     |\n");
        printf(" ---------------------------------------------------------\n");
        menuBusca(agenda, n);
    }
}

int main(int argc, char*argv[])
{
    setlocale(LC_ALL,NULL);

    int opcao, n, funcionando = 1, quant, i;

    char enderecoAgenda[500], enderecoTamanho[500], buffer[500], buffer2[500];

    Pessoa *minhaAgenda;

    system(LIMPA_TELA);

    sprintf(buffer, "%s",*argv);

    quant = strlen(buffer);

    for(i=quant; i>0; i--)
    {
        if(buffer[i] == '/')
            break;
    }

    quant = i;

    for(i=0; i<quant; i++)
    {
        buffer2[i] = buffer[i];
    }

    sprintf(enderecoAgenda, "%s/AgendaBIN.txt",buffer2);
    sprintf(enderecoTamanho, "%s/TamanhoAgendaBIN.txt",buffer2);

    opcao = menu();

    while (funcionando == 1)
    {
        if(opcao == 1)
        {
            minhaAgenda = criaAgenda(&n, enderecoTamanho, enderecoAgenda);
            incluir(minhaAgenda, &n);
            BubbleSort(minhaAgenda, &n, trocarPorNome);
            salvar(minhaAgenda, &n, enderecoAgenda, enderecoTamanho);
            pressENTER();
            opcao = menu();
        }

        else if(opcao == 2)
        {
            minhaAgenda = criaAgenda(&n, enderecoTamanho, enderecoAgenda);
            editar(minhaAgenda, &n);
            BubbleSort(minhaAgenda, &n, trocarPorNome);
            salvar(minhaAgenda, &n, enderecoAgenda, enderecoTamanho);
            pressENTER();
            opcao = menu();
        }

        else if(opcao == 3)
        {
            minhaAgenda = criaAgenda(&n, enderecoTamanho, enderecoAgenda);
            menuListar(minhaAgenda, &n);
            opcao = menu();
        }

        else if(opcao == 4)
        {
            minhaAgenda = criaAgenda(&n, enderecoTamanho, enderecoAgenda);
            menuBusca(minhaAgenda, &n);
            opcao = menu();
        }

        else if(opcao == 5)
        {
            minhaAgenda = criaAgenda(&n, enderecoTamanho, enderecoAgenda);;
            excluir(minhaAgenda, &n);
            BubbleSort(minhaAgenda, &n, trocarPorNome);
            salvar(minhaAgenda, &n, enderecoAgenda, enderecoTamanho);
            pressENTER();
            opcao = menu();
        }

        else if(opcao == 0)
        {
            printf(" ---------------------------------------------------------\n");
            printf("|        ..::Obrigado por usar a Agendator 3000::..       |\n");
            printf(" ---------------------------------------------------------\n");
            funcionando = 0;
        }

        else
        {
            printf(" ---------------------------------------------------------\n");
            printf("|    Opcao Inexistente! Favor selecionar outra opcao.     |\n");
            printf(" ---------------------------------------------------------\n");
            opcao = menu();
        }
    }

    free(minhaAgenda);
    return 0;
}