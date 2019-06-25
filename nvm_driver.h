/**
 *\file
 *\brief driver que utiliza as fun��es de leitura e escrita em uma mem�ria n�o vol�til.
 *
 *
 *
 * Created: 24/06/2019 20:26:37
 *  Author: Lucas
 */ 


#ifndef NVM_DRIVER_H_
#define NVM_DRIVER_H_
//! Uniao utilizada para converter float em byte e vice-versa
typedef union {
	float a;
	uint8_t bytes[4];
} float_store;


//! Funcao para inicializar o driver asf 
void configure_nvm(void);
//! Funcao para ler um valor de ponto flutuante 
//! @param address Endere�o de memoria onde o valor deve ser lido
float read_float(uint32_t address);
//! Funcao para escrever um valor em um endere�o de memoria
//! @param address Endereco onde o valor vai ser armazenado
//! @param num Valor que vai ser escrito na mem�ria
void write_float(uint32_t address, float num);


#endif /* NVM_DRIVER_H_ */