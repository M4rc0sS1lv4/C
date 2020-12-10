#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "forcateste.h"


//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
//numero maximo de chutes
char chutes[26];
int chutesdados = 0;

//criando uma fun��o
void abertura() {
	// imprime cabe�alho
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta() {
	//captura um novo chute
	char chute;
	//toda vez que usar char coloque um espa�o antes do %c para n�o dar buffer
	scanf(" %c", &chute);
	
	//guardo chute no array chutes e fa�a chutesdados++
	if(chute >= 'A' && chute <= 'Z') {
		chutes[chutesdados] = chute;
		(chutesdados)++;
	} else {
		printf("Somente letras maiusculas\n");
	}
	
}

int jachutou(char letra) {
	int achou = 0;
	
	//varrendo o array chutes para ver se a palavra ja foi chutada
	//int = 0 � pq o array come�o no 0
	//j tem q se menor que a palavra secreta 
	for(int j = 0; j < chutesdados; j++) {
		//se a letra em chutes na posi��o j foi igual a posi��o i j� foi chutada
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}
	
	return achou;
}

void desenhaforca() {
	
	int erros = chuteserrados();
	
	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
    	(erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
    	(erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), 
    	(erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");
	
	//varrendo o array e colocando - em cada posi��o
	//int = 0 � pq o array come�o no 0
	//i tem q se menor que a palavra secreta 
	for(int i = 0; i < strlen(palavrasecreta); i++) {
			
		int achou = jachutou(palavrasecreta[i]);
			
		if(achou) {
			printf("%c", palavrasecreta[i]);
		} else {
			printf("_ ");
		}
			
	}
	printf("\n");
}

void adicionapalavra() {
	
	char quer;
	
	printf("Voce desejar a adicionar uma nova palavra no jogo? (S/N) ");
	//espa�o %c sinaliza que s� quer ler um char
	scanf(" %c", &quer);
	
	if(quer == 'S' or quer == 's') {
		
		char novapalavra[TAMANHO_PALAVRA];
		printf("Qual nova palavra? ");
		scanf("%s", novapalavra);
		
		FILE* f;
		//r+ leitura e escrita
		f = fopen("palavras.txt", "r+");	
		if(f == 0) {
			printf("Desculpe, BD n�o disponivel\n\n");
			exit(1);
		}
	
		
		int qtd;
		//le a quantidade do arquivo
		fscanf(f, "%d", &qtd);
		//adicionando +1 na variavel e n�o arquivo
		//representa a linha do numero
		qtd++;
		
		//para posicionar o ponteiro em outro lugar
		//nome do arquivo e sua posi��o
		//� uma constante em rela��o a posi��o passada
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		//posicionando a seta no final do arquivo
		fseek(f, 0, SEEK_END);
		//imprimindo a nova palavra
		fprintf(f,"\n%s", novapalavra);
		
		fclose(f);
	}
}

void escolhepalavra() {
	//devolve um ponteiro
	FILE* f;
	
	//criando um diretorio
	//dando nome "palavras.txt
	//modo leitura "r"
	f = fopen("palavras.txt", "r");
	
	if(f == 0) {
		printf("Desculpe, BD n�o disponivel\n\n");
		exit(1);
	}
	
	int qtddepalavras;
	//ler arquivo
	//nome do arquivo de leitura
	//saida do arquivo
	fscanf(f, "%d", &qtddepalavras);
	
	//escolhendo uma linha aleat�ria com uma semente
	srand(time(0));
	//faz o resto da quantidade de inteiros o rand 
	//pelo o numero de palavras
	int randomico = rand() % qtddepalavras;
	
	//percorre as linhas at� achar a linha escolhida que esta no randomico
	//coloca na palavra secreta
	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavrasecreta);
	}
	
	//fechando o arquivo
	fclose(f);
}

int acertou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}
	
	return 1;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) erros++;
    }

    return erros;
}

int enforcou() {
	
	return chuteserrados() >= 5;
	
}

int main() {

    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

    } while (!acertou() && !enforcou());
    
    if(acertou()) {
        printf("\nParabens, voce ganhou!\n\n");
 
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
 
    } else {
        printf("\nPuxa, voc� foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);
 
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
 
    adicionapalavra();
}
