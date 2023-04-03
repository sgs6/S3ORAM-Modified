/*
 * ClientS3ORAM.hpp
 *
 *  Created on: Mar 15, 2017
 *      Author: ceyhunozkaptan, thanghoang
 */
 
#ifndef CLIENTS3ORAM_HPP
#define CLIENTS3ORAM_HPP

#include "config.h"
#include <pthread.h>
#include "zmq.hpp"
#include "struct_socket.h"

class ClientS3ORAM
{
private:
	//client storage for ORAM operations
    TYPE_ID** metaData; //this is for position_map scanning optimization
    TYPE_POS_MAP* pos_map;
    
    
    //variables for retrieval operation
	TYPE_INDEX numRead;
	TYPE_DATA** sharedVector;
    
    TYPE_DATA** retrievedShare;
    TYPE_DATA* recoveredBlock;
    
    unsigned char** vector_buffer_out;	
    unsigned char** block_buffer_out; 
    unsigned char** blocks_buffer_in;
    
    //variables for eviction
    TYPE_INDEX numEvict;
    TYPE_DATA*** sharedMatrix;
	TYPE_DATA** evictMatrix; 
	unsigned char** evict_buffer_out;

    //thread
	pthread_t thread_sockets[NUM_SERVERS];

#if defined(PRECOMP_MODE)
	TYPE_DATA** precompOnes;
	TYPE_DATA** precompZeros;
#endif

public:
    ClientS3ORAM();
    ~ClientS3ORAM();

    //main functions
    int init();
    int load();
    int access(TYPE_ID blockID);
    int accessQuerry(long long int value, int firstValue);
    int sendORAMTree();
    
    //retrieval_vector
    int getLogicalVector(TYPE_DATA* logicalVector, TYPE_ID blockID);

    //eviction_matrix
    int getEvictMatrix(TYPE_DATA** evictMatrix, TYPE_INDEX n_evict);
    
    //socket
	static void* thread_socket_func(void* args);	
    static int sendNrecv(std::string ADDR, unsigned char* data_out, size_t data_out_size, unsigned char* data_in, size_t data_in_size, int CMD);

    //logging
	static unsigned long int exp_logs[9]; 	static unsigned long int thread_max;
	static char timestamp[16];
	
};

#endif // CLIENTORAM_HPP
