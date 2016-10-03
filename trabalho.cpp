#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string.h>
#define N 11

using namespace std;

typedef struct No { 
	char nome[21];
	char endereco[21];
	int idade;
	struct No* prox;
} No;

typedef struct lista {
	struct No* inicio;
	//int numelem;
} lista;

No* vetor[N];

int valor_nome(char nome[21]) {
	int i, total = 0;
	for (i=0; nome[i] != '\0'; i++)
		if (nome[i] == ' ')
			total += 27;
		else
			total += nome[i] - 96;
	
	return total % N;
}



void mostrarVetor () {
	for(int i=0; i<N; i++) {
		if (vetor[i] == NULL) {
			cout << "Posicao " << i << " vazia." << endl;
		} else {
			No *elo = vetor[i];
			cout << "Posicao " << i << ": " << endl;
			while (elo != NULL) {
				cout << "\n" << "Nome: " << elo->nome << "\n" << "Idade: " << elo->idade << "\n" << "Endereco: " << elo->endereco << "\n" << endl;
				elo = elo->prox;
			}
		}
		cout << endl;		
	}
	cout << endl;
}

/*
void vetorOrdenado(){
	No *elo;
	No *p;
	for(int i = 0; i < N; i++){
		elo = vetor[i];
		if (elo == NULL){
			i++; //testar
		}else{
			No *aux = elo->prox;
			if(aux == NULL){
				i++;
			}else{
				for(int j = i; elo->prox != NULL; j++){
					if(elo->nome > aux->nome){
						p->nome = elo->nome;
						elo->nome = aux->nome;
						aux->nome = p->nome;
					}
					elo = elo->prox;
					aux = elo->prox;	
				}
			}	
		}
	}
	return;	
}
*/
void mostrarPos (int pos){
	if (vetor[pos] == NULL){
		cout << "A posicao " << pos << " do vetor esta vazia." << endl;
	}else{
		cout << "\n" << "Por posição" << "\n" << endl;
		No * elo = vetor[pos];
		while (elo != NULL) {
			cout << "\n" << "Nome: " << elo->nome << "\n" << "Idade: " << elo->idade << "\n" << "Endereco: " << elo->endereco << "\n" << endl;
			elo = elo->prox;
		}
	}
	return;
}

//funcao de insercao
void inserir (char nome[], char endereco[], int idade) {
	int pos = valor_nome(nome);
	No *elo, *eloant;
	No* novoelo = (No*)malloc(sizeof(No));
	

	//cout << "Alocado com sucesso" << endl;
	strcpy(novoelo->endereco,endereco);
	novoelo->idade = idade;
	strcpy(novoelo->nome,nome);
	novoelo->prox = NULL;

	for(elo = vetor[pos], eloant = NULL; (elo) && (strcmp(elo->nome, nome) < 0); eloant = elo, elo = elo->prox);	

	if(elo)
		if(eloant){
			if (!strcmp(elo->nome, nome)){
				novoelo->prox = elo;
				eloant->prox = novoelo;
			}			
		}
		else{
			vetor[pos] = novoelo;
			novoelo->prox = elo;
		}
	else{
		if (eloant)
			eloant->prox = novoelo;
		else
			vetor[pos] = novoelo;
	}
}

void remover (char nome[]) {
	int pos = valor_nome(nome);
	
	No *elo, *eloant;
	for(elo = vetor[pos], eloant = NULL; (elo) && strcmp(elo->nome, nome); eloant = elo, elo = elo->prox);

	if(elo){
		if(eloant)
			eloant->prox = elo->prox;
		else
			vetor[pos] = elo->prox;
		free(elo);
	}
}

void consultar(char nome[]){
	int pos = valor_nome(nome);
	No *elo;
	if(vetor[pos] != NULL){
		elo = vetor[pos];
	}else{
		return;
	}

	//Pessoa procurada na primeira posição da lista
	if( !strcmp(elo->nome, nome)){
		cout << "Nome: " << elo->nome << "\n" << "Idade: " << elo->idade << "\n" << "Endereco: " << elo->endereco << endl;
		return;
	}
	//Percorre a lista da posição pos em busca da pessoa
	while(elo->prox != NULL){
		elo = elo->prox;
		if(! strcmp(elo->nome, nome)){
			cout << "Nome: " << elo->nome << "\n" << "Idade: " << elo->idade << "\n" << "Endereco: " << elo->endereco << endl;
			return;
		}
	}	
	return;
}

int main(){
	char nome[21], endereco[21], op;
	int idade, qtd, i;


	do{
	scanf(" %c", &op);
	switch(op){
		case 'i':
			scanf(" %d", &qtd);
			for(i=0; i<qtd;i++){
//				printf("pasou aki%d\n", i);
				scanf(" %[^\n]s", nome);
				scanf(" %d", &idade);
				scanf(" %[^\n]s", endereco);
				inserir(nome, endereco, idade);
			}
			break;
		case 'r':
			scanf(" %[^\n]s", nome);
			remover(nome);
			break;
		case 'c':
			scanf(" %[^\n]s", nome);
			consultar(nome);
			break;
		case 'l':
			scanf(" %d", &i);
			mostrarPos(i);
			break;
		case 'o':
			break;
		case 'e':
			return 0;
		}
	}while(1);
}
