#include <iostream>
#include <cstdlib> // inclui rand() e srand()
#include <ctime>   // inclui time() para seed
#include <vector>
#include <set> // para std::set

using namespace std;

struct no{
	int info;
	struct no *prox;
};

typedef no *noPtr;

noPtr topo = NULL;
noPtr fim = NULL;

//a roleta europeia possui 37 casas e a rodada sempre começa no 0
void listaCirc(int A[]){
	//adicionando os valores do vetor na lista circular
	for(int i = 0; i < 37; i++){
		noPtr p = new no;
		p->info = A[i];
		if(topo == NULL){
			topo = p;
			fim = p;
			fim->prox = topo;
		}else{
			fim->prox = p;
			fim = p;
			fim->prox = topo;
		}
	}
}

int roleta(noPtr topo){
	int volta = rand() % 300 + 1; // gera um número entre 1 a 300
	
	noPtr p = topo;
	for(int i = 0; i < volta; i++){
		p = p->prox;
	}
	
	cout << "Numero na roleta: " << p->info;
    return p->info;
}

void listar(noPtr topo){
	noPtr p = topo;
	int i = 0;
	do{
		cout << p->info << " ";
		p = p->prox;
		i++;
	}while(i<37);
}

void liberarLista(noPtr &topo) {
    if (topo == NULL) return;
    noPtr p = topo, prox;
    do {
        prox = p->prox;
        delete p;
        p = prox;
    } while (p != topo);
    topo = NULL;
}

int main() {
    int num, aposta, val;
    set<int> uniqueNumbers; // set: biblioteca do c++ que armazena valores inteiros unicos. uniqueNunbers é um conjunto 
    vector<int> vet;        // vector: vetor dinamico do c++ que armazena sequencia de valores inteiros

    srand(time(0)); // seed random: inicializa o gerador de numeros aleatorios
    //time(0): retorna tempo atual. o tempo atual é usado como a semente para garantir que os números gerados sejam diferentes a cada execução do programa.
	//sem srand, o gerador usaria a mesma semente padrão em todas as execuções, resultando na mesma sequência de números aleatórios.

    while(uniqueNumbers.size() < 36){
        val = rand() % 36 + 1; // gera um número entre 1 a 36
        if(uniqueNumbers.insert(val).second){ // insere no conjunto; retorna false se já existir
            vet.push_back(val); // adiciona ao vetor se for único
        }
    }
    
    /* insert(val) adiciona o valor val ao conjunto e second é um valor booleano que indica que a inserção foi bem sucedida, se o numero ja
    existir, é retornado false
    push.back(val) funçao usada para inserir um novo elemento no final do vetor
    */

    int V[37];
    V[0] = 0;
    for (int i = 0; i < 36; i++) {
        V[i+1] = vet[i];
    }

    // cria a lista circular
    listaCirc(V);
    
    cout << "37 valores unicos da roleta:\n";
    listar(topo);
    
    cout << "\nDigite o valor voce quer apostar: ";
    cin >> aposta;
    
    num = roleta(topo);
    
    if(aposta == num){
	cout << "\nValores iguais. Voce ganhou";
    }else{
    	cout << "\nNao foi dessa vez";
    }
    
    liberarLista(topo);

    return 0;
}


