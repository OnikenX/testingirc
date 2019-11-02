#include <stdio.h>
#include <string.h>

//String to int
//torna uma string(array de chars) para int
int str2int(char * str){
	
	//defenição das variáveis
		//all - o numero final
		//len - tamanho do array de chars
		//exp - exponente
		//i e f - contadores de fors
	int all=0, lev = 0, exp, i, f;
    
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

int main(int argc, char **argv){
    if(argc != 2){
        printf("call the program with a number as a argument\n");
        return -1;
    }
    printf("\no numero enviado é %s==%d\n", argv[1], str2int(argv[1]));
    return 0;
}