//******************************************************
//Instituto Federal Sul-rio-grandense - Campus Camaqu�
//Disciplina......: Linguagem de programa��o
//Curso t�cnico integrado em Automa��o Industrial
//Aluno...........: Eduardo Machado Behling
//******************************************************


#include<stdio.h>
#include<wchar.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>
#include<math.h>
#include<conio.h>

#define LIMITECHAR 25

typedef WCHAR str;

enum class Sorts { Por_ID, Por_Nome, Por_Custo, Por_Lucro, Por_Imposto, Por_Pre�o, Por_Quantidade };

template<typename T>
void Merge(T* a, T* b, T* c, size_t lenb, size_t lenc, Sorts& sort, bool inversed) {
	size_t i = 0, j = 0, k = 0;
	while (i < lenb && j < lenc)
	{
		switch (sort) //Organiza os "Produto"s pela a organiza��o desejada.
		{
		case Sorts::Por_ID:
			if (inversed)
			{
				if (b[i].ID >= c[j].ID)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].ID <= c[j].ID)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		case Sorts::Por_Nome:
			break;
		case Sorts::Por_Custo:
			if (inversed)
			{
				if (b[i].custo >= c[j].custo)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].custo <= c[j].custo)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		case Sorts::Por_Lucro:
			if (inversed)
			{
				if (b[i].lucro_liquido >= c[j].lucro_liquido)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].lucro_liquido <= c[j].lucro_liquido)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		case Sorts::Por_Imposto:
			if (inversed)
			{
				if (b[i].imposto >= c[j].imposto)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].imposto <= c[j].imposto)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		case Sorts::Por_Pre�o:
			if (inversed)
			{
				if (b[i].pre�o >= c[j].pre�o)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].pre�o <= c[j].pre�o)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		case Sorts::Por_Quantidade:
			if (inversed)
			{
				if (b[i].quantidade >= c[j].quantidade)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			else
			{
				if (b[i].quantidade <= c[j].quantidade)
				{
					a[k] = b[i];
					i++;
				}
				else {
					a[k] = c[j];
					j++;
				}
			}
			break;
		default:
			break;
		}
		k++;
	}
	while (i < lenb) {
		a[k] = b[i];
		i++;
		k++;
	}
	while (j < lenc) {
		a[k] = c[j];
		j++;
		k++;
	}
}

template<typename T>
void MergeSort(T* a, long long lenA, Sorts& sort, bool inversed = false) {
	/*
	MergeSort algoritmo, pesquisei como se implementa e adaptei para minha struct "Produto"
	*/
	if (lenA < 2)
	{
		return;
	}
	size_t mid = lenA / 2;
	T* left = (T*)malloc(mid * sizeof(T));
	T* right = (T*)malloc((lenA - mid) * sizeof(T));
	for (size_t i = 0; i < mid; i++)
	{
		left[i] = a[i];
	}
	for (size_t i = mid; i < lenA; i++)
	{
		right[i - mid] = a[i];
	}
	MergeSort<T>(left, mid, sort, inversed);
	MergeSort<T>(right, lenA - mid, sort, inversed);
	Merge<T>(a, left, right, mid, lenA - mid, sort, inversed);
}

struct Produto {
	WCHAR nome[LIMITECHAR];
	unsigned long long ID;
	unsigned int quantidade;
	unsigned short lucro_percentual;
	double lucro_liquido;
	double custo;
	double pre�o;
	double imposto;
private:
	static unsigned long long _ID; //Um membro estatico da classe que aumenta a cada instaciamento

public:
	Produto(const WCHAR* Nome, double Custo, float Lucro, unsigned int Quantidade) {
		wcsncpy_s(nome, Nome, 25);
		custo = Custo;
		quantidade = Quantidade;
		lucro_percentual = Lucro;
		lucro_liquido = (Lucro / 100) * custo;
		ID = ++_ID; //ID � unico porque aumenta a cada instaciamento
		imposto = 0.05 * (custo + lucro_liquido);
		pre�o = custo + lucro_liquido - imposto;
	}
};

unsigned long long Produto::_ID = 0; //Inicializando o ID para 0;

template<typename T>
struct DArray {
	/*
		Uma array dinamicamente dimensionada, isto faz com que possa adcionar itens sem um "limite";
	*/
	T* array;
	long long size;
	long long used;

	DArray(long long initS) {
		array = (T*)malloc(initS * sizeof(T));
		size = initS;
		used = 0;
	}

	T add(T element, long long index = -1) {
		if (index < 0 || index > used) {
			if (used + 1 == size)
			{
				size *= 2;
				array = (T*)realloc(array, size * sizeof(T));
			}
			array[used++] = element;
			return element;
		}
		else {
			array[index] = element;
			return element;
		}
	}

	void print() {
		for (size_t i = 0; i < used; i++)
		{
			printf("ID = %llu, name = %s, price = %lf\n", array[i].ID, array[i].name, array[i].price);
		}
	}
};

struct Somatorio
	/*
		Soma o valor de todos os atributos dos produtos que foram entrados;
		Utilizado no final da tabela;
	*/
{
	double custo;
	double lucro;
	double imposto;
	double pre�o_de_venda;
	unsigned int quantidade;
	double media;
	double lucro_obtivel;
	double imposto_pago;

	Somatorio(DArray<Produto>& produtos) {
		custo = 0;
		lucro = 0;
		imposto = 0;
		pre�o_de_venda = 0;
		quantidade = 0;
		lucro_obtivel = 0;
		imposto_pago = 0;
		for (size_t i = 0; i < produtos.used; i++)
		{
			custo += produtos.array[i].custo;
			lucro += produtos.array[i].lucro_liquido;
			imposto += produtos.array[i].imposto;
			pre�o_de_venda += produtos.array[i].pre�o;
			quantidade += produtos.array[i].quantidade;
			lucro_obtivel += (produtos.array[i].pre�o - produtos.array[i].custo) * produtos.array[i].quantidade;
			imposto_pago += produtos.array[i].imposto * produtos.array[i].quantidade;
		}
		media = pre�o_de_venda / produtos.used;
	}
};

enum class Valida��o {
	Erro_Nome_Invalido, Erro_Nome_NA, Erro_Custo_Invalido, Erro_Custo_NA, Erro_Lucro_Invalido, Erro_Lucro_NA,
	Erro_Quantidade_Invalida, Erro_Quantidade_NA, Formata��o_Incorreta, Entrada_Valida
};

double String_Para_Double(WCHAR* array, size_t tamanho) {
	double temp = 0;
	for (size_t i = 0; i < tamanho; i++)
	{
		if (array[i] == ',' || array[i] == '.')
		{
			i++;
			temp /= 10;
		}
		temp += (array[i] - '0') * (pow(10.0, tamanho - i - 1));
	}
	return temp / 100;
}

int String_Para_Inteiro(WCHAR* array, size_t tamanho) {
	int temp = 0;
	for (size_t i = 0; i < tamanho; i++)
	{
		temp += (array[i] - '0') * (pow(10.0, tamanho - i - 1));
	}
	return temp;
}

Produto Executa_Comando(WCHAR* array) {
	WCHAR Nome[25];
	unsigned int Quantidade = 1;
	unsigned short Lucro = 1, Espa�o_Conserto = 0;
	long double Pre�o = 0;
	size_t inicio = 0;
	enum class Segmento_Comando { nome, pre�o_de_custo, porcetagem_de_lucro, quantidade, termino };
	Segmento_Comando Segmento_Atual = Segmento_Comando::nome;
	for (size_t i = 0; true; i++)
	{
		if (array[i] == ';' || array[i] == '\0') //checa por caractere divisor ';' ou pelo fim da string 'comando'
		{
			for (size_t j = 0; array[j + inicio] == ' '; j++) //checa quanto de espa�amento tem entre cada parametro, ex: "nome;      custo;lucro;              quantidade"
			{
				Espa�o_Conserto++;
			}
			switch (Segmento_Atual)
			{
			case Segmento_Comando::nome:
				array[i] = '\0';
				wcsncpy_s(Nome, array, 25);
				Segmento_Atual = Segmento_Comando::pre�o_de_custo;
				array[i] = ';';
				break;
			case Segmento_Comando::pre�o_de_custo:
				array[i] = '\0';
				Pre�o = String_Para_Double(array + inicio + Espa�o_Conserto, i - inicio - Espa�o_Conserto); //passa o inicio do segmento, ignorando os segmentos anteriores e os espa�os;
				Segmento_Atual = Segmento_Comando::porcetagem_de_lucro;
				Espa�o_Conserto = 0;
				array[i] = ';';
				break;
			case Segmento_Comando::porcetagem_de_lucro:
				array[i] = '\0';
				Lucro = String_Para_Inteiro(array + inicio + Espa�o_Conserto, i - inicio - Espa�o_Conserto); //passa o inicio do segmento, ignorando os segmentos anteriores e os espa�os;
				Segmento_Atual = Segmento_Comando::quantidade;
				Espa�o_Conserto = 0;
				array[i] = ';';
				break;
			case Segmento_Comando::quantidade:
				Quantidade = String_Para_Inteiro(array + inicio + Espa�o_Conserto, i - inicio - Espa�o_Conserto); //passa o inicio do segmento, ignorando os segmentos anteriores e os espa�os;
				Segmento_Atual = Segmento_Comando::termino;
				break;
			case Segmento_Comando::termino:
				break;
			default:
				exit(-1); //caso haja um problema na interpreta��o dos segmentos termina a aplica��o.
				break;
			}
			inicio = i + 1; //marca o inicio do segmento atual;
		}
		if (array[i] == '\0')
		{
			return Produto(Nome, Pre�o, Lucro, Quantidade); //cria um Produto com os parametros do comando
		}
	}
}

size_t Contador_de_Algarismos(int numero) {
	size_t contador = 1;
	while (numero > 9)
	{
		numero /= 10;
		contador++;
	}
	return contador;
}

size_t Contador_de_Caracteres(const WCHAR* string) {
	/*
	Conta quantos caracteres h� at� o char '\0' sendo assim:
	retorna o tamanho da string + 1 ('\0')
	*/
	for (size_t i = 0; true; i++)
	{
		if (string[i] == '\0')
		{
			return i;
		}
	}
}

//overload para ascii chars
size_t Contador_de_Caracteres(const char* string) {
	for (size_t i = 0; true; i++)
	{
		if (string[i] == '\0')
		{
			return i;
		}
	}
}

void separator(char* sep, size_t size, char ch) {
	/*
	Printa "size" quantidade do char "ch" em sequencia;
	sep � um array de char que serve para que os chars n�o sejam printados invidualmente, causam um efeito visual desgradavel
	sep � um parametero para evitar o custo de perfomance de inicializar uma array para cada chamada da fun��o
	*/
	if (size == 0) {
		printf("%c", ch);
	}
	else {
		for (size_t i = 0; i < size; i++)
		{
			sep[i] = ch;
		}
		sep[size] = '\0';
		printf("%s", sep);
	}
}

size_t Desenhar_Tabela(DArray<Produto>& produtos) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); //pegando quantos caracteres cabem na janela
	char* separador = (char*)malloc(info.dwSize.X + 10);
	size_t Margem = info.dwSize.X - 82;
	if (Margem % 2 != 0)
	{
		Margem++;
	}
	separator(separador, Margem / 2, ' ');
	printf("Voc� adicionou os seguintes itens: (Pressione a tecla \'q\' para fechar a aplica��o)\n\n");
	Margem = info.dwSize.X - 15;
	if (Margem % 2 != 0)
	{
		Margem++;
	}
	separator(separador, Margem / 2, ' ');
	printf("Organizar por:\n\n");
	Margem = info.dwSize.X - 106;
	if (Margem % 2 != 0)
	{
		Margem++;
	}
	separator(separador, Margem / 2, ' ');
	printf("[F1] ID    [F2] Custo de Fabrica��o    [F3] Lucro    [F4] Imposto    [F5] Pre�o Liquido    [F6] Quantidade\n");
	Margem = (info.dwSize.X - 134) / 2;
	if (Margem % 2 != 0)
	{
		Margem--;
	}
	separator(separador, Margem, ' ');
	separator(separador, 135, '_');
	printf("\n");
	separator(separador, Margem, ' ');
	printf("| ID [#]| Nome                    | Custo de Fabrica��o [R$]|   Lucro [R$/%c]    |   Imposto [R$/%c]  | Pre�o Liquido [R$]|  Quantidade |\n", '%', '%');
	separator(separador, Margem, ' ');
	printf("|");
	separator(separador, 7, '_');
	printf("|");
	separator(separador, 25, '_');
	printf("|");
	separator(separador, 25, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 13, '_');
	printf("|\n");
	for (size_t i = 0; i < produtos.used; i++)
	{
		separator(separador, Margem, ' ');
		printf("|");
		size_t temp = 6 - Contador_de_Algarismos(produtos.array[i].ID);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("#%llu", produtos.array[i].ID);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("#%llu", produtos.array[i].ID);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		wprintf(L"%ls", produtos.array[i].nome);
		separator(separador, 25 - Contador_de_Caracteres(produtos.array[i].nome), ' ');
		printf("|");
		temp = 25 - Contador_de_Algarismos(produtos.array[i].custo) - 3;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf", produtos.array[i].custo);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf", produtos.array[i].custo);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - (Contador_de_Algarismos(produtos.array[i].lucro_liquido) + 3 + Contador_de_Algarismos(produtos.array[i].lucro_percentual) + 4);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf (%d%c)", produtos.array[i].lucro_liquido, produtos.array[i].lucro_percentual, '%');
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf (%d%c)", produtos.array[i].lucro_liquido, produtos.array[i].lucro_percentual, '%');
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - Contador_de_Algarismos(produtos.array[i].imposto) - 8;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf (5%c)", produtos.array[i].imposto, '%');
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf (5%c)", produtos.array[i].imposto, '%');
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - Contador_de_Algarismos(produtos.array[i].pre�o) - 3;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf", produtos.array[i].pre�o);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf", produtos.array[i].pre�o);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 13 - Contador_de_Algarismos(produtos.array[i].quantidade);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%u", produtos.array[i].quantidade);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%u", produtos.array[i].quantidade);
			separator(separador, temp / 2, ' ');
		}
		printf("|\n");
		separator(separador, Margem, ' ');
		printf("|");
		separator(separador, 7, 175);
		printf("|");
		separator(separador, 25, 175);
		printf("|");
		separator(separador, 25, 175);
		printf("|");
		separator(separador, 19, 175);
		printf("|");
		separator(separador, 19, 175);
		printf("|");
		separator(separador, 19, 175);
		printf("|");
		separator(separador, 13, 175);
		printf("|\n");
	}
	separator(separador, Margem, ' ');
	printf("|");
	auto temp = 7 - Contador_de_Algarismos(produtos.array[produtos.used - 1].ID);
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + 1, ' ');
	}
	printf("%llu", produtos.array[produtos.used - 1].ID);
	separator(separador, temp / 2, ' ');
	printf("|");
	separator(separador, 10, ' ');
	printf("TOTAL");
	separator(separador, 10, ' ');
	printf("|");
	Somatorio soma(produtos);
	temp = 25 - Contador_de_Algarismos(soma.custo) - 3;
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
		printf("%.2lf", soma.custo);
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + temp % 2, ' ');
		printf("%.2lf", soma.custo);
		separator(separador, temp / 2, ' ');
	}
	printf("|");
	temp = 19 - Contador_de_Algarismos(soma.lucro) - 9;
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
		printf("%.2lf (XXX%)", soma.lucro);
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + temp % 2, ' ');
		printf("%.2lf (XXX%)", soma.lucro);
		separator(separador, temp / 2, ' ');
	}
	printf("|");
	temp = 19 - Contador_de_Algarismos(soma.imposto) - 8;
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
		printf("%.2lf (5%c)", soma.imposto, '%');
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + temp % 2, ' ');
		printf("%.2lf (5%c)", soma.imposto, '%');
		separator(separador, temp / 2, ' ');
	}
	printf("|");
	temp = 19 - Contador_de_Algarismos(soma.media) - 3;
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
		printf("%.2lf", soma.media);
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + temp % 2, ' ');
		printf("%.2lf", soma.media);
		separator(separador, temp / 2, ' ');
	}
	printf("|");
	temp = 13 - Contador_de_Algarismos(soma.quantidade);
	if (temp % 2 == 0)
	{
		separator(separador, temp / 2, ' ');
		printf("%u", soma.quantidade);
		separator(separador, temp / 2, ' ');
	}
	else
	{
		separator(separador, temp / 2 + temp % 2, ' ');
		printf("%u", soma.quantidade);
		separator(separador, temp / 2, ' ');
	}
	printf("|\n");
	separator(separador, Margem, ' ');
	printf("|");
	separator(separador, 7, '_');
	printf("|");
	separator(separador, 25, '_');
	printf("|");
	separator(separador, 25, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 19, '_');
	printf("|");
	separator(separador, 13, '_');
	printf("|\n");
	printf("\n\n");
	size_t center = info.dwSize.X - 67;
	center /= 2;
	if ((info.dwSize.X - 67) % 2 != 0)
	{
		center++;
	}
	separator(separador, center, ' ');
	separator(separador, 68, '_');
	printf("\n");
	separator(separador, center, ' ');
	printf("|");
	temp = 67 - sizeof("DADOS EXTRAS:");
	temp /= 2;
	if ((67 - sizeof("DADOS EXTRAS:")) % 2 != 0)
	{
		separator(separador, temp + 1, ' ');
	}
	else
	{
		separator(separador, temp, ' ');
	}
	printf("DADOS EXTRAS:");
	separator(separador, temp, ' ');
	printf("|\n");
	separator(separador, center, ' ');
	printf("|");
	separator(separador, 66, '_');
	printf("|\n");
	const char Dados[3][45] = { "Media entre o pre�o l�quido de cada item", "Lucro obtido na venda de todo o estoque",
							   "Imposto pago na venda de todo o estoque" };
	size_t size;
	bool Lucro_Negativo = false;
	double Values[3] = { soma.media, soma.lucro_obtivel, soma.imposto_pago };
	for (size_t i = 0; i < 3; i++)
	{
		separator(separador, center, ' ');
		printf("|");
		size = Contador_de_Caracteres(Dados[i]);
		temp = 45 - size;
		temp /= 2;
		if ((45 - size) % 2 != 0)
		{
			separator(separador, temp + 1, ' ');
		}
		else
		{
			separator(separador, temp, ' ');
		}
		printf("%s", Dados[i]);
		separator(separador, temp, ' ');
		printf("|");
		size = Contador_de_Algarismos(Values[i]) + 8;
		if (Values[i] < 0)
		{
			Lucro_Negativo = true;
		}
		temp = 20 - size;
		if (Lucro_Negativo)
		{
			printf(" R$:%.2lf", Values[i]);
			Lucro_Negativo = false;
		}
		else {
			printf(" R$: %.2lf", Values[i]);
		}
		separator(separador, temp, ' ');
		printf("|\n");
		separator(separador, center, ' ');
		if (i == 2)
		{
			separator(separador, 68, 175);
			printf("\n");
		}
		else {
			printf("|");
			separator(separador, 45, 175);
			printf("|");
			separator(separador, 20, 175);
			printf("|\n");
		}
	}
	return Margem;
}

Valida��o Valida��o_Comando(const str* comando) {
	bool Validade_dos_Segmentos[4] = { 0 };
	str Intermediario[100];
	unsigned short Segmento_Atual = 0, inicio;
	for (size_t i = 0; comando[i] != '\0'; i++)
	{
		if (comando[i] == ';')
		{
			Segmento_Atual++;
		}
	}
	if (Segmento_Atual != 3)
	{
		return Valida��o::Formata��o_Incorreta;
	}
	Segmento_Atual = 0;
	for (size_t i = 0; true; i++)
	{
		if (comando[i] == ';' || comando[i] == '\0') {
			switch (Segmento_Atual)
			{
			case 0:
				wcsncpy_s(Intermediario, comando, 100);
				Intermediario[i] = '\0';
				if (Contador_de_Caracteres(Intermediario) < 26 && i != 0)
				{
					Segmento_Atual++;
				}
				else if (i == 0) {
					return Valida��o::Erro_Nome_NA;
				}
				else {
					return Valida��o::Erro_Nome_Invalido;
				}
				break;

			case 1:
				for (size_t j = inicio; comando[j] != L';'; j++)
				{
					if ((comando[j] - L'0' > 9 || comando[j] - L'0' < 0) && comando[j] != ' ' && (comando[j] != ',' && comando[j] != '.')) {
						return Valida��o::Erro_Custo_Invalido;
					}
				}
				if (comando[inicio] == L';')
				{
					return Valida��o::Erro_Custo_NA;
				}
				Segmento_Atual++;
				break;

			case 2:
				for (size_t j = inicio; comando[j] != L';'; j++)
				{
					if ((comando[j] - L'0' > 9 || comando[j] - L'0' < 0) && comando[j] != ' ') {
						return Valida��o::Erro_Lucro_Invalido;
					}
				}
				if (comando[inicio] == L';')
				{
					return Valida��o::Erro_Lucro_NA;
				}
				Segmento_Atual++;
				break;

			case 3:
				for (size_t j = inicio; comando[j] != L'\0'; j++)
				{
					if ((comando[j] - L'0' > 9 || comando[j] - L'0' < 0) && comando[j] != ' ') {
						return Valida��o::Erro_Quantidade_Invalida;
					}
				}
				if (comando[inicio] == L'\0')
				{
					return Valida��o::Erro_Quantidade_NA;
				}
				Segmento_Atual++;
				break;

			default:
				return Valida��o::Entrada_Valida;
				break;
			}
			inicio = i + 1;
		}
	}
}

bool Handler_Valida��o(const str* comando) {
	Valida��o Feedback = Valida��o_Comando(comando);
	switch (Feedback)
	{
	case Valida��o::Erro_Nome_NA:
		printf("ERRO: Par�metro \"Nome\" n�o foi especificado");
		break;
	case Valida��o::Erro_Custo_NA:
		printf("ERRO: Par�metro \"Custo de Produ��o\" n�o foi especificado");
		break;
	case Valida��o::Erro_Lucro_NA:
		printf("ERRO: Par�metro \"Lucro\" n�o foi especificado");
		break;
	case Valida��o::Erro_Quantidade_NA:
		printf("ERRO: Par�metro \"Quantidade\" n�o foi especificado");
		break;
	case Valida��o::Erro_Nome_Invalido:
		printf("ERRO: Par�metro \"Nome\" � maior que o limite de %d caracteres", LIMITECHAR);
		break;
	case Valida��o::Erro_Custo_Invalido:
		printf("ERRO: Par�metro \"Custo de Produ��o\" cont�m caracteres n�o numericos");
		break;
	case Valida��o::Erro_Lucro_Invalido:
		printf("ERRO: Par�metro \"Lucro\" cont�m caracteres n�o numericos");
		break;
	case Valida��o::Erro_Quantidade_Invalida:
		printf("ERRO: Par�metro \"Quantidade\" cont�m caracteres n�o numericos");
		break;
	case Valida��o::Formata��o_Incorreta:
		printf("ERRO: Formata��o Incorreta, uso incorreto do caractere divisor \';\'");
		break;
	default:
		return true;
		break;
	}
	return false;
}

void Modificar_Valores(DArray<Produto>& produtos, size_t Margem) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	CONSOLE_CURSOR_INFO Cinfo;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(handle, &Cinfo);
	Cinfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &Cinfo); //Escondendo o cursor durante a processamento
	GetConsoleScreenBufferInfo(handle, &info); //Pega a localiza��o do cursor para retornar no final
	char* separador = (char*)malloc(100);
	COORD cords = { Margem + 1,8 };
	for (size_t i = 0; i < produtos.used; i++)
	{
		SetConsoleCursorPosition(handle, cords);
		size_t temp = 6 - Contador_de_Algarismos(produtos.array[i].ID);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("#%llu", produtos.array[i].ID);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("#%llu", produtos.array[i].ID);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		wprintf(L"%ls", produtos.array[i].nome);
		separator(separador, 25 - Contador_de_Caracteres(produtos.array[i].nome), ' ');
		printf("|");
		temp = 25 - Contador_de_Algarismos(produtos.array[i].custo) - 3;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf", produtos.array[i].custo);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf", produtos.array[i].custo);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - (Contador_de_Algarismos(produtos.array[i].lucro_liquido) + 3 + Contador_de_Algarismos(produtos.array[i].lucro_percentual) + 4);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf (%d%c)", produtos.array[i].lucro_liquido, produtos.array[i].lucro_percentual, '%');
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf (%d%c)", produtos.array[i].lucro_liquido, produtos.array[i].lucro_percentual, '%');
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - Contador_de_Algarismos(produtos.array[i].imposto) - 8;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf (5%c)", produtos.array[i].imposto, '%');
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf (5%c)", produtos.array[i].imposto, '%');
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 19 - Contador_de_Algarismos(produtos.array[i].pre�o) - 3;
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%.2lf", produtos.array[i].pre�o);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%.2lf", produtos.array[i].pre�o);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		temp = 13 - Contador_de_Algarismos(produtos.array[i].quantidade);
		if (temp % 2 == 0)
		{
			separator(separador, temp / 2, ' ');
			printf("%u", produtos.array[i].quantidade);
			separator(separador, temp / 2, ' ');
		}
		else
		{
			separator(separador, temp / 2 + temp % 2, ' ');
			printf("%u", produtos.array[i].quantidade);
			separator(separador, temp / 2, ' ');
		}
		printf("|");
		cords.Y += 2;
	}
	Cinfo.bVisible = TRUE;
	SetConsoleCursorPosition(handle, info.dwCursorPosition);
	SetConsoleCursorInfo(handle, &Cinfo);
}

void Organizar_Tabela(DArray<Produto>* produtos, size_t Margem, Sorts sort, bool invertido = false) {
	MergeSort<Produto>(produtos->array, produtos->used, sort, invertido);
	Modificar_Valores(*produtos, Margem);
}

int main() {
	setlocale(LC_ALL, "Portuguese"); //Determinando o idioma utilizado pelo programa (faz UTF-16 characteres serem printados)
	DArray<Produto> produtos(11); //Uma Array Dinamica de Produtos
	WCHAR comando[100]; //Armazena a resposta do usuario   //nome.max = 25 chars, price.max = 20.000,00, lucro.max = 100, quantidade.max = 20.000;
	auto w = GetConsoleWindow();
	MoveWindow(w, 255, 50, 1250, 750, TRUE); //Movendo e dimesionando o console
	ShowScrollBar(w, SB_VERT, FALSE); //Escondendo Scrollbar vertical
	printf("Adcione quantos itens desejar, desde que obede�a a formata��o a seguir:\n\">>>Nome; Custo de Fabrica��o (xxx.xx ou xxx,xx ou xxxxx); Lucro em Porcetagem; Quantidade\"\npara terminar de adcionar itens entre este comando \"!q\"\n\n");
	while (true) //Adciona produtos at� o usuario entrar "!q"
	{
		printf("\n>>>");
		wscanf_s(L"%[^\n]s", comando, 98);
		getchar(); //scanf deixa um '\n' passar que ira bagun�ar o proximo scanf, isto serve para tirar o '\n' do buffer
		if (comando[0] == '!' && comando[1] == 'q' && comando[2] == '\0') //Checando o comando de termina��o
		{
			break;
		}
		if (Handler_Valida��o(comando)) { //Checa a validade do comando
			produtos.add(Executa_Comando(comando)); //Cria um objeto "Produto" de acordo com o codigo entrado
			printf("SUCESSO: Item \"%ls\" adcionado com sucesso.", produtos.array[produtos.used - 1].nome); //Indica o sucesso da opera��o da execu��o do comamdo
		}
	}
	system("cls");
	auto margem = Desenhar_Tabela(produtos);
	char Reposta = 'a';
	enum Index_Inverter { ID, Custo, Lucro, Imposto, Pre�o, Quantidade };
	bool Inverter[6] = { 0 };
	Inverter[ID] = true;
	while (Reposta != 'q')
	{
		Reposta = _getch();
		switch (Reposta)
		{
		case ';': //F1 == ';' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_ID, Inverter[ID]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == ID)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case '<': //F2 == '<' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_Custo, Inverter[Custo]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == Custo)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case '=': //F3 == '=' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_Lucro, Inverter[Lucro]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == Lucro)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case '>': //F4 == '>' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_Imposto, Inverter[Imposto]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == Imposto)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case '?': //F5 == '?' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_Pre�o, Inverter[Pre�o]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == Pre�o)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case '@': //F6 == '@' in _getch()
			Organizar_Tabela(&produtos, margem, Sorts::Por_Quantidade, Inverter[Quantidade]);
			for (size_t i = 0; i < 6; i++)
			{
				if (i == Quantidade)
				{
					Inverter[i] = !Inverter[i];
				}
				else {
					Inverter[i] = false;
				}
			}
			break;
		case 'q': //para termina��o do programa
			return 0;
			break;
		default: //caso seja outra tecla n�o fa�a nada e continue
			break;
		}
	}
}