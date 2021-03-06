
#pragma once
#include <random>
#include "tools.h"
#include "connect.h"
#include "globals.h"
using namespace std;

extern void start_time();
extern void start_communication();
extern void end_time(string str);
extern void end_communication(string str);



void funcTruncate2PC(vector<myType> &a, size_t power, size_t size, size_t party_1, size_t party_2);
void funcXORModuloOdd2PC(vector<smallType> &bit, vector<myType> &shares, vector<myType> &output, size_t size);
void funcReconstruct2PC(const vector<myType> &a, size_t size, string str);
void funcReconstructBit2PC(const vector<smallType> &a, size_t size, string str);
void funcConditionalSet2PC(const vector<myType> &a, const vector<myType> &b, vector<smallType> &c, 
							vector<myType> &u, vector<myType> &v, size_t size);
void funcMatMulMPC(const vector<myType> &a, const vector<myType> &b, vector<myType> &c, 
				size_t rows, size_t common_dim, size_t columns,
			 	size_t transpose_a, size_t transpose_b);
void funcDotProductMPC(const vector<myType> &a, const vector<myType> &b, 
					   vector<myType> &c, size_t size);
void funcPrivateCompareMPC(const vector<smallType> &share_m, const vector<myType> &r, 
							  const vector<smallType> &beta, vector<smallType> &betaPrime, 
							  size_t size, size_t dim);
void funcShareConvertMPC(vector<myType> &a, size_t size);
void funcComputeMSB4PC(const vector<myType> &a, vector<smallType> &b, size_t size);
void funcComputeMSB3PC(const vector<myType> &a, vector<myType> &b, size_t size);
void funcSelectShares4PC(const vector<myType> &a, const vector<smallType> &b, vector<myType> &c, size_t size);
void funcSelectShares3PC(const vector<myType> &a, const vector<myType> &b, vector<myType> &c, size_t size);
void funcRELUPrime4PC(const vector<myType> &a, vector<smallType> &b, size_t size);
void funcRELUPrime3PC(const vector<myType> &a, vector<myType> &b, size_t size);
void funcRELUMPC(const vector<myType> &a, vector<myType> &b, size_t size);
void funcDivisionMPC(const vector<myType> &a, const vector<myType> &b, vector<myType> &quotient, 
						size_t size);
void funcMaxMPC(vector<myType> &a, vector<myType> &max, vector<myType> &maxIndex, 
						size_t rows, size_t columns);
void funcMaxIndexMPC(vector<myType> &a, const vector<myType> &maxIndex, 
						size_t rows, size_t columns);
void aggregateCommunication();


//Debug
void debugDotProd();
void debugComputeMSB();
void debugPC();
void debugDivision();
void debugMax();
void debugSS();
void debugMatMul();
void debugReLUPrime();
void debugMaxIndex();

//Test
void testMatMul(size_t rows, size_t common_dim, size_t columns, size_t iter);
void testConvolution(size_t iw, size_t ih, size_t fw, size_t fh, size_t C, size_t D, size_t iter);
void testRelu(size_t r, size_t c, size_t iter);
void testReluPrime(size_t r, size_t c, size_t iter);
void testMaxPool(size_t p_range, size_t q_range, size_t px, size_t py, size_t D, size_t iter);
void testMaxPoolDerivative(size_t p_range, size_t q_range, size_t px, size_t py, size_t D, size_t iter);

//S++ functions
void testdiv();
void dummyCompare(vector<myType> &x, vector<myType> &r, vector<myType> &m, size_t size, char op = '>');
void funcPrivateCompareMPC_2(vector<myType> &x, vector<myType> &r, vector<myType> &m, size_t size, char op = ">");
void funcSplitFraction(vector<myType> &x, vector<myType> &int_x, vector<myType> &frac_x, size_t size);
void funcIntegerExp(vector<myType> &x, vector<myType> &c, size_t size);
void funcExponentiation_2(vector<myType> &x, vector<myType> &c, size_t size);
void funcExponentiation(vector<myType> &x, vector<myType> &c, size_t size);
void testexp(vector<myType> &x, size_t size); 
void funcSigmoid(vector<myType> &x, vector<myType> &c, size_t size, float gain=1.0);
void testsigmoid(vector<myType> &x, size_t size, float gain=1.0);
void funcTanh(vector<myType> &x, vector<myType> &c, size_t size);
void testtanh(vector<myType> &x, size_t size);
void funcSoftmax(vector<myType> &z, vector<myType> &smax, int k);
void testsoftmax(vector<myType> &z, size_t size);
void funcSigmoidDerivative (vector<myType> &x, vector<myType> &c, size_t size, float gain=1.0);
void testSigmoidDerivative(vector<myType> &x, size_t size);
void funcTanhDerivative(vector<myType> &x, vector<myType> &c, size_t size);
void testTanhDerivative(vector<myType> &x, size_t size);
void pointWiseProduct(vector<myType> &a, vector<myType> &b, vector<myType> &c,size_t size);
void funcTaylorExp(vector<myType> &x, vector<myType> &c, size_t size);
void testTaylorExp(vector<myType> &x, size_t size);
