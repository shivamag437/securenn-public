
#include <iostream>
#include <string>
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
	NeuralNetConfig* config = new NeuralNetConfig(NUM_ITERATIONS);


/****************************** SELECT NETWORK ******************************/ 
	//MINIONN, Network-D in GAZELLE
	whichNetwork = "MiniONN/GAZELLE-D";
	CNNConfig* l0 = new CNNConfig(16,1,5,5,MINI_BATCH_SIZE,28,28,2,2);
	CNNConfig* l1 = new CNNConfig(16,16,5,5,MINI_BATCH_SIZE,12,12,2,2);
	FCConfig* l2 = new FCConfig(MINI_BATCH_SIZE, 256, 100);
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
	// testMatMul(784, 128, 10, NUM_ITERATIONS);
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



	end_m(whichNetwork);
	cout << "----------------------------------" << endl;  	
	cout << NUM_OF_PARTIES << "PC code, P" << partyNum << endl;
	cout << NUM_ITERATIONS << " iterations, " << whichNetwork << ", batch size " << MINI_BATCH_SIZE << endl;
	cout << "----------------------------------" << endl << endl;  


	size_t size = 1024;

	//SecureNN+
	vector<myType> x(size, 5),y(size,5), z(size, 0);/*,z(1);*/

	// x[0] = floatToMyType(float(3));
	//y[0] = floatToMyType(-2);
	//testtanh(y);
	// z[0] = floatToMyType(float(1));

	// testexp(x);
	// testexp(y);
	// testexp(z);

	// vector<myType> c(1);
	// x[0] = floatToMyType(1);
	// x[0] = -1 * x[0];
	// cout<<"After multiplication with -1: "<<MyTypetofloat(x[0])<<endl;
	// x[0] = x[0] + y[0];
	// cout<<"After adding 2: "<<MyTypetofloat(x[0])<<endl;
	// cout<<"Value of x(float to fixed): "<<x[0]<<endl;
	// float p = MyTypetofloat(x[0]);
	// //cout<<"Value of x(without func): "<<double(1)*(pow(2,13))<<endl;
	// // double p = double(x[0])/pow(2,13);
	// cout<<"Value of x(fixed to float): "<<p<<endl;
	// float g = 2.0;
	
	// testdiv();
	// testtanh(x);
	x[0]=floatToMyType(20);
	x[1]=floatToMyType(18);
	x[2]=floatToMyType(5);
	x[3]=floatToMyType(-4);
	x[4]=floatToMyType(-5);
	int i = 0;
	int iterations = 1000;
	
	start_m();
	for(i = 0;i<iterations;++i)
		testexp(x, size);
	end_m("Exponentiation");

	
	start_m();
	for(i = 0;i<iterations;++i)
		funcDivisionMPC(x, y, z, size);
	end_m("Division");
	
	start_m();
	for(i = 0;i<iterations;++i)
		testsigmoid(x,size);
	end_m("Sigmoid");
	
	start_m();
	for(i = 0;i<iterations;++i)
		testtanh(x, size);
	end_m("TanH");

	start_m();
	for(i = 0;i<iterations;++i)
		testsoftmax(x, size);
	end_m("softmax");

	start_m();
	for(i = 0;i<iterations;++i)
		testSigmoidDerivative(x, size);
	end_m("Derivative of Sigmoid");

	start_m();
	for(i = 0;i<iterations;++i)
		testTanhDerivative(x, size);
	end_m("Derivative of TanH");

	start_m();
	testTaylorExp(x, size);
	end_m("Taylor Expansion");

	vector<myType> a(1,floatToMyType(1));
	// vector<myType> b(1,floatToMyType(1)),c(1);

	testexp(a,1);
	// testTanhDerivative(a,1);
	// testexp(a,1);
	// pointWiseProduct(a,b,c,1);

	// myType test = 31855933495705600 * (1<<13);
	// cout<<"Test value: "<<test;

	// vector<myType> a(3, 1),b(3, 1),c(3, 1);
	// a[0] = floatToMyType(0);
	// a[1] = floatToMyType(1);
	// a[2] = floatToMyType(2);
	// b[0] = floatToMyType(0);
	// b[1] = floatToMyType(1);
	// b[2] = floatToMyType(2);

	// pointWiseProduct(a, b,c,3);
	// vector<myType> S(3);
	// vector<myType> temp(size, 1);

	// S[0] = floatToMyType(1);
	// S[1] = floatToMyType(1);
	// S[2] = floatToMyType(1);

	// cout<<"S before dot Product: ";
	// for(int i=0;i<size;i++){
	// 	cout<<S[i]<<" ";
	// }
	// cout<<endl;
	// funcDotProductMPC(S,temp,S,size);
	// cout<<"S after dot Product: ";
	// for(int i=0;i<size;i++){
	// 	cout<<S[i]<<" ";
	// }
	// cout<<endl;


	//softmax
	// testsoftmax();
// /****************************** CLEAN-UP ******************************/ 
	delete aes_common;
	delete aes_indep;
	delete aes_a_1;
	delete aes_a_2;
	delete aes_b_1;
	delete aes_b_2;
	delete aes_c_1;
	delete aes_parallel;
	delete config;
	delete l0;
	delete l1;
	delete l2;
	// delete l3;
	delete network;
	if (partyNum != PARTY_S)
		deleteObjects();


	return 0;
}

