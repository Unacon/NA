#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <bitset>

using namespace cv;
using namespace std;

int main (int argc, char** argv){
  Mat image,frame,image1,frame1;
  VideoCapture cap;
  int width,height,i,j,teste,rangeinf,rangesup,x=0,y=0,z=0;
  int n,posicao=-1; // Quantidade de Bits.
  char key;

  cap.open(0); // Captura Video

  if(!cap.isOpened()){
    cout << "Erro" << endl;
    return -1;
  }//Verifica se video foi aberto

  //Dimensões do Video
  width=cap.get(CV_CAP_PROP_FRAME_WIDTH); 
  height=cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  
  cout<<"Largura: "<<width<<"\nAltura: "<<height<<endl;
  cout<<"Qual range de trabalho\n";
  cin>>rangeinf;
  cin>>rangesup;
  
  //Ajusta espaço de aleatoridade
  if(rangeinf>rangesup){
    int k;
    k=rangesup;
    rangesup=rangeinf;
    rangeinf=k;
  }
  //Erro do espaço
  if(rangeinf==rangesup){
    cout<<"Errado\n";
   return 0;
  }

  //Tamanho do numero binário
  n=log(abs(rangesup))/log(2) + 1;

  //Cria numero binário de 32 bits
  bitset<32> aleatorio;

  cout<<"Range inferior: "<<rangeinf<<"\nRange Superior:  "<<rangesup<<endl;
  cout<<"Quantidade de Bits: "<<n<<endl;
  cout<<"Botao 'z' gera numero aleatorio\n";

  namedWindow("Video",WINDOW_AUTOSIZE);

  while(1){
  //Captura duas imagens
  cap >>image;
  cap>>image1;
  //Transforma em tons de cinza
  cvtColor(image, frame, CV_BGR2GRAY); 
  cvtColor(image1, frame1, CV_BGR2GRAY);
  
  //Comandos
  key = (char) waitKey(10);
  if( key == 27 ) break; //Esc - Para programa 
    if( key == 122 ){  //Z - Gera numero
      cout<<"Gerando Numero Aleatorio\n";
      posicao=0; // Zera posição do número binário
      aleatorio.reset();  // Reseta número binário   
    } 
  //Verifica posição 
  if(posicao>=0){
     //Laço para pegar o primeiro pixel diferente entre imagens
     for(i=x;i<height;i++){
      for(j=y;j<width;j++){
	if(y>=width) y=0;
	if(x>=height) x=0;
 	if(frame.at<uchar>(i,j)!=frame1.at<uchar>(i,j)){
	  teste=frame1.at<uchar>(i,j);
	  z=1;
	  break;	  	  	  	  
	}	
      }
  	if(z==1) break;
    }
     x=i+1;
     y=j+1;

     /* Coloca valor do pixel em binario
        Designa valor para posicao do numero binario   */   
     aleatorio[posicao]=teste%2;
     z=0;

     //Incrementa a posicao
     posicao+=1;
    }
    //Numero binario completo, entra nesse if
    if(posicao>=n){
      /* Transforma numero binario em inteiro
	 Modula numero para o range		*/
      cout<<"Numero: "<<aleatorio.to_ulong()%(rangesup-rangeinf+1)+rangeinf<<endl;
      posicao=-1;
    }
    
    imshow("Video",frame);

  }	
  return 0;
}

