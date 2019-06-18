#include "pch.h"
#include<opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

void adicaoFormaDireta(Mat imgA, Mat imgB); //ok
void adicaoPorIntervalo(Mat imgA, Mat imgB); //ok
void adicaoNormalizacao(Mat imgA, Mat imgB); //ok

void subtracaoNormalizacao(Mat imgA, Mat imgB); //ok
void subtracaoFormaDireta(Mat imgA, Mat imgB); //ok
void subtracaoPorIntervalo(Mat imgA, Mat imgB); //dúvida


void multiplicacaoFormaDireta(Mat imgA, Mat imgB); //ok
void multiplicacaoPorIntervalo(Mat imgA, Mat imgB); //ok
void multiplicacaoNormalizacao(Mat imgA, Mat imgB); //ok

void divisaocaoFormaDireta(Mat imgA, Mat imgB); //ok
void divisaoPorIntervalo(Mat imgA, Mat imgB); //
void divisaoNormalizacao(Mat imgA, Mat imgB); //ok



int maior(vector<vector<float>> mat, Mat imgA, Mat imgB); //ok
int menor(vector<vector<float>> mat, Mat imgA, Mat imgB); //ok

void escalar(Mat imgA, int valorASerMultiplicado); //ok
void media(Mat imgA, Mat imgB);


int formaDireta(int k);

int main(int argc, const char * argv[]) {

	Mat imgA, imgB, imgFinal01;
	int k = 0;

	//Define caminho das imagens
	String imageNameB("data/opencv.jpg");

	String imageNameA("data/robo.jpg");


		/*String imageNameB("C:/Users/Karina/source/repos/SegmentationHardExudatosPI/SegmentationHardExudatosPI/teste/IDRiD_01.jpg");

		String imageNameA("C:/Users/Karina/source/repos/SegmentationHardExudatosPI/SegmentationHardExudatosPI/teste/IDRiD_01_OD.tif");*/

	// Ler imagens 
	imgB = imread(imageNameA, IMREAD_GRAYSCALE);
	imgA = imread(imageNameB, IMREAD_GRAYSCALE);

	int option;

	cout << " 1. Adicao \n 2. Subtracao \n 3. Multiplicacao \n 4. Divisao \n 5. Media \n 6. Escalar \n Resposta: ";

	cin >> option;

	switch (option) {
	case 1:
		adicaoNormalizacao(imgA, imgB);
		adicaoFormaDireta(imgA, imgB);
		adicaoPorIntervalo(imgA, imgB);
		break;
	case 2:
		subtracaoFormaDireta(imgA, imgB);
		subtracaoNormalizacao(imgA, imgB);
		subtracaoPorIntervalo(imgA, imgB);
		break;
	case 3:
		multiplicacaoFormaDireta(imgA, imgB);
		multiplicacaoPorIntervalo(imgA, imgB);
		multiplicacaoNormalizacao(imgA, imgB);
		break;
	case 4:
		divisaocaoFormaDireta(imgA, imgB);
		divisaoPorIntervalo(imgA, imgB);
		divisaoNormalizacao(imgA, imgB);
		break;
	case 5:
		media(imgA, imgB);
		break;
	case 6:
		int valor;
		cout << "Digite um valor inteiro nao negativo: \n Resposta: ";
		cin >> valor;
		escalar(imgA, valor);
		break;

	case 7:
		cout << "Programa encerrado";
	default:
		cout << "Valor inválido";
		break;
	}
	waitKey(0);



	return 0;

}

//Caso 1: adição (imgFinal01 = imgA + imgB)
void adicaoFormaDireta(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) + (int)imgB.at<uchar>(row, col);
			if (k > 255)
				imgFinal01.at<uchar>(row, col) = (uchar)255;
			else
				imgFinal01.at<uchar>(row, col) = k;
		}
	}

	namedWindow("Forma Direta - adicao", WINDOW_AUTOSIZE);
	imshow("Forma Direta - adicao", imgFinal01);
	imwrite("resultado/Forma Direta - adicao.jpg", imgFinal01); //Salva a imagem

}

void adicaoPorIntervalo(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k, valor;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) + (int)imgB.at<uchar>(row, col);
			if (k > 255) {
				valor = k + 255;
				imgFinal01.at<uchar>(row, col) = valor;
			}
			else {
				imgFinal01.at<uchar>(row, col) = k;
			}
		}
	}

	namedWindow("Por intervalo - adicao", WINDOW_AUTOSIZE);
	imshow("Por intervalo - adicao", imgFinal01);
	imwrite("resultado/Por intervalo - adicao.jpg", imgFinal01); //Salva a imagem

}

void adicaoNormalizacao(Mat imgA, Mat imgB) {

	float y;
	int z;

	y = 350 - 45;
	z = (255 / y) * (300 - 45);

	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	int maiorValor = 0, menorValor = 0;
	vector<vector<float>> mat(imgA.rows, vector<float>(imgA.cols));

	//Copia na matriz mat os valores da soma de imgA e imgB
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) + (int)imgB.at<uchar>(row, col);
			mat[row][col] = k;

		}
	}

	maiorValor = maior(mat, imgA, imgB);
	menorValor = menor(mat, imgA, imgB);

	y = maiorValor - menorValor;
	//Faz a normalização
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			z = (255 / y) * (mat[row][col] - menorValor); //Fómula para normalização

			imgFinal01.at<uchar>(row, col) = z;
		}
	}

	namedWindow("Normalizacao - adicao", WINDOW_AUTOSIZE);
	imshow("Normalizacao - adicao", imgFinal01);
	imwrite("resultado/Normalizacao - adicao.jpg", imgFinal01); //Salva a imagem

}


//Caso 2: subtração (imgFinal01 = imgA - imgB)
void subtracaoFormaDireta(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) - (int)imgB.at<uchar>(row, col);
			if (k < 0)
				imgFinal01.at<uchar>(row, col) = 0;
			else
				imgFinal01.at<uchar>(row, col) = k;
		}
	}

	namedWindow("Forma Direta - Subtracao", WINDOW_AUTOSIZE);
	imshow("Forma Direta - Subtracao", imgFinal01);
	imwrite("resultado/Forma Direta - Subtracao.jpg", imgFinal01); //Salva a imagem
}

void subtracaoPorIntervalo(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k, valor;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) - (int)imgB.at<uchar>(row, col);
			if (k < 0) {
				valor = (k * (-1));
				imgFinal01.at<uchar>(row, col) = valor;
			}
			else {
				imgFinal01.at<uchar>(row, col) = k;
			}
		}
	}

	namedWindow("Por intervalo - Subtracao", WINDOW_AUTOSIZE);
	imshow("Por intervalo - Subtracao", imgFinal01);
	imwrite("resultado/Por intervalo - Subtracao.jpg", imgFinal01); //Salva a imagem

}

void subtracaoNormalizacao(Mat imgA, Mat imgB) {

	float y;
	int z;

	y = 350 - 45;
	z = (255 / y) * (300 - 45);

	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	int maiorValor = 0, menorValor = 0;
	vector<vector<float>> mat(imgA.rows, vector<float>(imgA.cols));

	//Copia na matriz mat os valores da soma de imgA e imgB
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) - (int)imgB.at<uchar>(row, col);
			mat[row][col] = k;

		}
	}

	maiorValor = maior(mat, imgA, imgB);
	menorValor = menor(mat, imgA, imgB);

	y = maiorValor - menorValor;
	//Faz a normalização
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			z = (255 / y) * (mat[row][col] - menorValor); //Fómula para normalização

			imgFinal01.at<uchar>(row, col) = z;
		}
	}

	namedWindow("Normalizacao - Subtracao", WINDOW_AUTOSIZE);
	imshow("Normalizacao - Subtracao", imgFinal01);
	imwrite("resultado/Normalizacao - Subtracao.jpg", imgFinal01); //Salva a imagem

}


//Caso 3: multiplicacao (imgFinal01 = imgA * imgB)
void multiplicacaoFormaDireta(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) * (int)imgB.at<uchar>(row, col);
			if (k > 255)
				imgFinal01.at<uchar>(row, col) = (uchar)255;
			else
				imgFinal01.at<uchar>(row, col) = k;
		}
	}

	namedWindow("Forma Direta - multiplicacao", WINDOW_AUTOSIZE);
	imshow("Forma Direta - multiplicacao", imgFinal01);
	imwrite("resultado/Forma Direta - multiplicacao.jpg", imgFinal01); //Salva a imagem

}

void multiplicacaoPorIntervalo(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k, valor;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) * (int)imgB.at<uchar>(row, col);
			if (k > 255) {
				valor = k - 255;
				imgFinal01.at<uchar>(row, col) = valor;
			}
			else {
				imgFinal01.at<uchar>(row, col) = k;
			}
		}
	}

	namedWindow("Por intervalo - multiplicacao", WINDOW_AUTOSIZE);
	imshow("Por intervalo - multiplicacao", imgFinal01);
	imwrite("resultado/Por intervalo - multiplicacao.jpg", imgFinal01); //Salva a imagem
}

void multiplicacaoNormalizacao(Mat imgA, Mat imgB) {

	float y;
	int z;

	y = 350 - 45;
	z = (255 / y) * (300 - 45);

	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	int maiorValor = 0, menorValor = 0;
	vector<vector<float>> mat(imgA.rows, vector<float>(imgA.cols));

	//Copia na matriz mat os valores da soma de imgA e imgB
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = (int)imgA.at<uchar>(row, col) * (int)imgB.at<uchar>(row, col);
			mat[row][col] = k;

		}
	}

	maiorValor = maior(mat, imgA, imgB);
	menorValor = menor(mat, imgA, imgB);

	y = maiorValor - menorValor;
	//Faz a normalização
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			z = (255 / y) * (mat[row][col] - menorValor); //Fómula para normalização

			imgFinal01.at<uchar>(row, col) = z;
		}
	}

	namedWindow("Normalizacao - multiplicacao", WINDOW_AUTOSIZE);
	imshow("Normalizacao - multiplicacao", imgFinal01);
	imwrite("resultado/Normalizacao - multiplicacao.jpg", imgFinal01); //Salva a imagem
}



//Caso 4: divisao (imgFinal01 = imgA / imgB)
void divisaocaoFormaDireta(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k, divisor;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			if ((int)imgB.at<uchar>(row, col) == 0) {
				divisor = 1;
				k = (int)imgA.at<uchar>(row, col) / divisor;
			}
			else
			{
				k = (int)imgA.at<uchar>(row, col) / (int)imgB.at<uchar>(row, col);
			}

			imgFinal01.at<uchar>(row, col) = k;
		}
	}

	namedWindow("Forma Direta - divisao", WINDOW_AUTOSIZE);
	imshow("Forma Direta - divisao", imgFinal01);
	imwrite("resultado/Forma Direta - divisao.jpg", imgFinal01); //Salva a imagem

}

void divisaoPorIntervalo(Mat imgA, Mat imgB) {
	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k, valor;
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			if ((int)imgB.at<uchar>(row, col) == 0) {
				k = (int)imgA.at<uchar>(row, col) / 1;
			}
			else {
				k = (int)imgA.at<uchar>(row, col) / (int)imgB.at<uchar>(row, col);
			}

			if (k > 255) {
				valor = k - 255;
				imgFinal01.at<uchar>(row, col) = valor;
			}
			else {
				imgFinal01.at<uchar>(row, col) = k;
			}
		}
	}

	namedWindow("Por intervalo - divisao", WINDOW_AUTOSIZE);
	imshow("Por intervalo - divisao", imgFinal01);
	imwrite("resultado/Por intervalo - divisao.jpg", imgFinal01); //Salva a imagem
}

void divisaoNormalizacao(Mat imgA, Mat imgB) {

	float y;
	int z;

	y = 350 - 45;
	z = (255 / y) * (300 - 45);

	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;
	int maiorValor = 0, menorValor = 0;
	vector<vector<float>> mat(imgA.rows, vector<float>(imgA.cols));

	//Copia na matriz mat os valores da soma de imgA e imgB
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			if ((int)imgB.at<uchar>(row, col) == 0) {
				k = (int)imgA.at<uchar>(row, col) / 1;
			}
			else
			{
				k = (int)imgA.at<uchar>(row, col) / (int)imgB.at<uchar>(row, col);

			}
			mat[row][col] = k;

		}
	}

	maiorValor = maior(mat, imgA, imgB);
	menorValor = menor(mat, imgA, imgB);

	y = maiorValor - menorValor;
	//Faz a normalização
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			z = (255 / y) * (mat[row][col] - menorValor); //Fómula para normalização

			imgFinal01.at<uchar>(row, col) = z;
		}
	}

	namedWindow("Normalizacao - divisao", WINDOW_AUTOSIZE);
	imshow("Normalizacao - divisao", imgFinal01);
	imwrite("resultado/Normalizacao - divisao.jpg", imgFinal01); //Salva a imagem
}


//Case 5: média
void media(Mat imgA, Mat imgB) {

	Mat imgFinal01;
	imgA.copyTo(imgFinal01);
	int k;

	//Faz a média local utilizando processamento por vizinhança
	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			k = ((int)imgA.at<uchar>(row, col) + (int)imgB.at<uchar>(row, col)) / 2;
			imgFinal01.at<uchar>(row, col) = k;

		}
	}

	namedWindow("Media", WINDOW_AUTOSIZE);
	imshow("Media", imgFinal01);
	imwrite("resultado/Media.jpg", imgFinal01); //Salva a imagem
}

//Caso 6: Escalar - Forma Direta
void escalar(Mat imgA, int valor) {
	Mat imgEscalarMult, imgEscalarAdicao, imgEscalarSub, imgEscalarDiv;
	imgA.copyTo(imgEscalarMult);
	imgA.copyTo(imgEscalarAdicao);
	imgA.copyTo(imgEscalarSub);
	imgA.copyTo(imgEscalarDiv);

	int multiplicacao, adicao, subtracao, divisao;

	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			//Multiplicacao
			multiplicacao = (int)imgA.at<uchar>(row, col) * valor;
			imgEscalarMult.at<uchar>(row, col) = formaDireta(multiplicacao); //Forma direta

			adicao = (int)imgA.at<uchar>(row, col) + valor;
			imgEscalarAdicao.at<uchar>(row, col) = formaDireta(adicao); //Forma direta

			subtracao = (int)imgA.at<uchar>(row, col) - valor;
			imgEscalarSub.at<uchar>(row, col) = formaDireta(subtracao); //Forma direta


			divisao = (int)imgA.at<uchar>(row, col) / valor;
			imgEscalarDiv.at<uchar>(row, col) = formaDireta(divisao); //Forma direta

		}
	}
	namedWindow("Forma Escalar - multiplicacao.jpg", WINDOW_AUTOSIZE);
	imshow("Forma Escalar - multiplicacao.jpg", imgEscalarMult);
	imwrite("resultado/Forma Escalar - multiplicacao.jpg", imgEscalarMult); //Salva a imagem


	namedWindow("Forma Escalar - adicao", WINDOW_AUTOSIZE);
	imshow("Forma Escalar - adicao", imgEscalarAdicao);
	imwrite("resultado/Forma Escalar - adicao.jpg", imgEscalarAdicao); //Salva a imagem


	namedWindow("Forma Escalar - subtracao", WINDOW_AUTOSIZE);
	imshow("Forma Escalar - subtracao", imgEscalarSub);
	imwrite("resultado/Forma Escalar - subtracao.jpg", imgEscalarSub); //Salva a imagem

	namedWindow("Forma Escalar - divisao", WINDOW_AUTOSIZE);
	imshow("Forma Escalar - divisao", imgEscalarDiv);
	imwrite("resultado/Forma Escalar - divisao.jpg", imgEscalarDiv); //Salva a imagem

}

//Pega maior valor de uma matriz
int maior(vector<vector<float>> mat, Mat imgA, Mat imgB) {

	int maior = mat[0][0];

	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			if (mat[row][col] > maior) {
				maior = mat[row][col];
			}
		}
	}
	return maior;

}

//Pega menor valor de uma matriz
int menor(vector<vector<float>> mat, Mat imgA, Mat imgB) {

	int menor = mat[0][0];

	for (int row = 0; row < imgA.rows; row++) {
		for (int col = 0; col < imgA.cols; col++) {
			if (mat[row][col] < menor) {
				menor = mat[row][col];
			}
		}
	}
	return menor;
}

int formaDireta(int k) {

	if (k > 255)
		return k = 255;
	else if (k < 0)
		return k = 0;
	else
		return k;
}







//https://agostinhobritojr.github.io/tutorial/pdi/zx