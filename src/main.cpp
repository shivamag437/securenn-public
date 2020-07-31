
#include <iostream>
#include <string>
#include <fstream>
#include "secondary.h"
#include "connect.h"
#include "AESObject.h"
#include "NeuralNetConfig.h"
#include "NeuralNetwork.h"
#include "Functionalities.h"


using namespace std;
extern int partyNum;
int NUM_OF_PARTIES;	


AESObject* aes_common;
AESObject* aes_indep;
AESObject* aes_a_1;
AESObject* aes_a_2;
AESObject* aes_b_1;
AESObject* aes_b_2;
AESObject* aes_c_1;
ParallelAESObject* aes_parallel;



int main(int argc, char** argv)
{
	

/****************************** PREPROCESSING ******************************/ 
	parseInputs(argc, argv);
	string whichNetwork = "No Network";
	
	std::ofstream f;
	f.open("benchmarks.csv");
	f << "S.no,Input Image Size,Filters in CNNlayer1,Filters in CNNlayer2,Neurons in FCLayer1,Neurons in FCLayer2,Exec Time (wall clock),Exec Time (CPU)\n";
	f.close();

	int runs = 10;
	for(int k=0; k<runs; k++) 
	{
		NeuralNetConfig* config = new NeuralNetConfig(NUM_ITERATIONS);


/****************************** SELECT NETWORK ******************************/ 
	

		int cnn_filters_layer1 = 16 - k;
		int cnn_filters_layer2 = 16 + k;
		//MINIONN, Network-D in GAZELLE
		whichNetwork = "MiniONN/GAZELLE-D";
		CNNConfig* l0 = new CNNConfig(cnn_filters_layer1,1,5,5,MINI_BATCH_SIZE,28,28,2,2);
		CNNConfig* l1 = new CNNConfig(cnn_filters_layer2,cnn_filters_layer1,5,5,MINI_BATCH_SIZE,12,12,2,2);
		FCConfig* l2 = new FCConfig(MINI_BATCH_SIZE, cnn_filters_layer2 * 16, 100);
		FCConfig* l3 = new FCConfig(MINI_BATCH_SIZE, 100, 10);
		config->addLayer(l0);
		config->addLayer(l1);
		config->addLayer(l2);
		config->addLayer(l3);



		//LeNet
		// whichNetwork = "LeNet";
		// CNNConfig* l0 = new CNNConfig(20,1,5,5,MINI_BATCH_SIZE,28,28,2,2);
		// CNNConfig* l1 = new CNNConfig(50,20,5,5,MINI_BATCH_SIZE,12,12,2,2);
		// FCConfig* l2 = new FCConfig(MINI_BATCH_SIZE, 800, 500);
		// FCConfig* l3 = new FCConfig(MINI_BATCH_SIZE, 500, 10);
		// config->addLayer(l0);
		// config->addLayer(l1);
		// config->addLayer(l2);
		// config->addLayer(l3);

		//SecureML
		// whichNetwork = "SecureML";
		// FCConfig* l0 = new FCConfig(MINI_BATCH_SIZE, LAYER0, LAYER1); 
		// FCConfig* l1 = new FCConfig(MINI_BATCH_SIZE, LAYER1, LAYER2); 
		// FCConfig* l2 = new FCConfig(MINI_BATCH_SIZE, LAYER2, LAST_LAYER_SIZE); 
		// config->addLayer(l0);
		// config->addLayer(l1);
		// config->addLayer(l2);

		//Chameleon
		// whichNetwork = "Sarda";
		// ChameleonCNNConfig* l0 = new ChameleonCNNConfig(5,1,5,5,MINI_BATCH_SIZE,28,28,2,2);
		// FCConfig* l1 = new FCConfig(MINI_BATCH_SIZE, 980, 100);
		// FCConfig* l2 = new FCConfig(MINI_BATCH_SIZE, 100, 10);
		// config->addLayer(l0);
		// config->addLayer(l1);
		// config->addLayer(l2);

		
		config->checkNetwork();
		NeuralNetwork* network = new NeuralNetwork(config);


	/****************************** AES SETUP and SYNC ******************************/ 
		aes_indep = new AESObject(argv[4]);
		aes_common = new AESObject(argv[5]);
		aes_a_1 = new AESObject("files/keyD");
		aes_a_2 = new AESObject("files/keyD");
		aes_b_1 = new AESObject("files/keyD");
		aes_b_2 = new AESObject("files/keyD");
		aes_c_1 = new AESObject("files/keyD");
		aes_parallel = new ParallelAESObject(argv[5]);

		if (!STANDALONE)
		{
			initializeCommunication(argv[3], partyNum);
			synchronize(2000000);	
		}

		if (PARALLEL)
			aes_parallel->precompute();


	/****************************** RUN NETWORK/BENCHMARKS ******************************/ 
		start_m();

		// whichNetwork = "Mat-Mul";
		// testMatMul(1, 1, 1, 1);
		// testMatMul(1, 500, 100, NUM_ITERATIONS);
		// testMatMul(1, 100, 1, NUM_ITERATIONS);

		// whichNetwork = "Convolution";
		// testConvolution(28, 28, 5, 5, 1, 20, NUM_ITERATIONS);
		// testConvolution(28, 28, 3, 3, 1, 20, NUM_ITERATIONS);
		// testConvolution(8, 8, 5, 5, 16, 50, NUM_ITERATIONS);

		// whichNetwork = "Relu";
		// testRelu(128, 128, NUM_ITERATIONS);
		// testRelu(576, 20, NUM_ITERATIONS);
		// testRelu(64, 16, NUM_ITERATIONS);

		// whichNetwork = "ReluPrime";
		// testReluPrime(128, 128, NUM_ITERATIONS);
		// testReluPrime(576, 20, NUM_ITERATIONS);
		// testReluPrime(64, 16, NUM_ITERATIONS);

		// whichNetwork = "MaxPool";
		// testMaxPool(24, 24, 2, 2, 20, NUM_ITERATIONS);
		// testMaxPool(24, 24, 2, 2, 16, NUM_ITERATIONS);
		// testMaxPool(8, 8, 4, 4, 50, NUM_ITERATIONS);

		// whichNetwork = "MaxPoolDerivative";
		// testMaxPoolDerivative(24, 24, 2, 2, 20, NUM_ITERATIONS);
		// testMaxPoolDerivative(24, 24, 2, 2, 16, NUM_ITERATIONS);
		// testMaxPoolDerivative(8, 8, 4, 4, 50, NUM_ITERATIONS);

		whichNetwork += " train";
		train(network, config);

		// whichNetwork += " test";
		// test(network);
		
		string log_info = string(k)+","+"28x28,"+string(cnn_filters_layer1)+","+string(cnn_filters_layer2)+","+string(cnn_filters_layer2*16)+","+"100,";
		log_csv("benchmarks.csv",log_info);

		end_m(whichNetwork);
		cout << "----------------------------------" << endl;  	
		cout << NUM_OF_PARTIES << "PC code, P" << partyNum << endl;
		cout << NUM_ITERATIONS << " iterations, " << whichNetwork << ", batch size " << MINI_BATCH_SIZE << endl;
		cout << "Number of filters in CNN layers: " << cnn_filters_layer1 <<"," << cnn_filters_layer2 << endl;
		cout << "----------------------------------" << endl << endl;

		delete config;
		delete l0;
		delete l1;
		delete l2;
		delete l3;
		delete network;
	}


	/*//SecureNN+s
	vector<myType> x(1);
	x[0] = 123456;
	cout<<"Value of x: "<<x[0]<<endl;
	// testexp(x);
	testdiv();*/

// /****************************** CLEAN-UP ******************************/ 
	delete aes_common;
	delete aes_indep;
	delete aes_a_1;
	delete aes_a_2;
	delete aes_b_1;
	delete aes_b_2;
	delete aes_c_1;
	delete aes_parallel;
	/*delete config;
	delete l0;
	delete l1;
	delete l2;
	delete l3;
	delete network;*/
	if (partyNum != PARTY_S)
		deleteObjects();


	return 0;
}

