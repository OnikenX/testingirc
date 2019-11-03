/*============================== Cliente UDP ===========================
  IRC 2016-17 - P6 - Teste sobre sockets UDP - Out./16
  Jose' Marinho
========================================================================*/

#include <winsock.h>
#include <stdio.h>

#define MAX_RESPONSE	100
#define MAX_MSGS		5
#define TIMEOUT			(MAX_MSGS+1)*60000 //msec

void Abort(char *msg);

/*________________________________ main _______________________________________
*/


//String to int
//torna uma string(array de chars) para int
double str2int(char * str){
	
	//defenição das variáveis
		//all - o numero final
		//len - tamanho do array de chars
		//exp - exponente
		//i e f - contadores de fors
	int lev = 0, exp, i, f;
    double all=0;
	//loop para a crição
	for (i=strlen(str)-1; 0<=i; --i){
        
		//meter o expoente a 1
		exp = 1;
		//criar o nivel do expoente se o for preciso
		for (f=0;f<lev;++f)
			exp*=10;
		
		//add do exp 
		all += (str[i]-'0')*exp;
        
		//diminoir o nivel 
		++lev;
        
	}
	
	return all;

}

int main( int argc , char *argv[] )
{
		//VERIFICACAO DOS ARGUMENTOS
	if(argc != 4){
		fprintf(stderr,"<Cliente> Sintaxe: %s valor_decimal_a_enviar ip_destino porto_destino\n",argv[0]);
		//(uk: <Client> Sintax: %s double_value_to_send server_ip server_port\n)
		exit(EXIT_FAILURE);
	}
	int i, port = str2int(argv[1]);
	double msg;
	char * ip;
	
		//DECLARACAO DAS VARIAVEIS
	DWORD timeout;
	WSADATA wsaData;
	SOCKET s;
	double sentValue;
	int iResult, nbytes, size;
	struct sockaddr_in serv_addr;
	char response[MAX_RESPONSE];

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("<Cliente> WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	// a) Crie um socket UDP (uk: create an UDP socket).

	s = socket( PF_INET , SOCK_DGRAM , IPPROTO_UDP );

	if(s == INVALID_SOCKET)
		Abort("Impossibilidade de criar socket");
	
	// b) Active o timeout de recepcao com um valor definido pela constante TIMEOUT.
	//	  (uk: receive operations must be subject to a timeout value defined by constant TIMEOUT).

	timeout = TIMEOUT;
	//set do timeout
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	
	memset( (char*)&serv_addr, 0 , sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]);

	// c) Preencha o campo relativo ao porto de destino pretendido e que foi passado atraves.
	//    da linha de comando (uk: set the server port number to the value that
	//	  was provided as a command line argument).

	serv_addr.sin_port = htons(str2int(argv[3]));



	// d) Coloque o valor decimal passado atraves da linha de comando na variavel sentValue
	//	  (uk: set sentValue to the double value that was provided as a command line argument).

	sentValue = str2int(argv[1]);

	// e) Envie o conteudo da variavel sentValue ao servidor em formato binario
	//	  (uk: transmit the value of variable sentValue in binary format to the server).

	if(sendto( s , (char *)&sentValue, sizeof(sentValue), 0 ,(struct sockaddr*)&serv_addr , sizeof(serv_addr) ) == SOCKET_ERROR)
		Abort("SO nao conseguiu aceitar o datagram");
	
	printf("<Cliente> Foi enviado o valor %fl\nAguardando response...\n", sentValue);

	// f) Aguarde pela recepcao de um datagrama e coloque o seu conteudo na variavel response
	//	  (uk: await for a datagram/message and put its content into string response).

	size = sizeof(serv_addr);
	nbytes = recvfrom(s, (char *)&response, sizeof(response), 0, (struct sockaddr *)&serv_addr, &size);

	if(nbytes == SOCKET_ERROR){

		// g) Verifique se ocorreu algum timeout
		//	  (uk: check if any timeout has occured).

		if(nbytes != SOCKET_ERROR)
			Abort("Erro enquanto aguarda pela response");
		else
			Abort("Timeout de recepcao");
	}

	// h) Termine a string recebida (uk: terminate string response).

	/* response ... = ...; */
	
	printf("<Cliente> Mensagem recebida: %s\n", response); 

	closesocket(s);

	printf("\n");
	exit(EXIT_SUCCESS);
}

/*________________________________ Abort________________________________________
  Mostra uma mensagem de erro e o codigo associado ao ultimo erro com Winsocks. 
  Termina a aplicacao com "exit status" a 1 (constante EXIT_FAILURE)
________________________________________________________________________________*/

void Abort(char *msg)
{
	fprintf(stderr,"<Cliente> Erro fatal: <%s> (%d)\n",msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}