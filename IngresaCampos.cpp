#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

union charint{
	char raw[sizeof(int)];
	int num;
};
union charfloat{
	char raw[sizeof(float)];
	float num;
};
union chardouble{
	char raw[sizeof(double)];
	double num;
};

int main(int argc, char** argv){
	vector<string> tipocampos;
	vector<string> nombrecampos;
	vector<int> sizes;
	int opcion;
	int tamano;
	string nombre;
	int opcion2;
	cout<<"1)Ingresar"<<endl<<"2)Leer"<<endl<<"Ingrese el codigo de lo que desea hacer:";
	cin>>opcion2;
	if (opcion2==1){
		while(true){
			cout<<endl
				<<"1)String"<<endl<<"2)Char"<<endl<<"3)Integer"<<endl<<"4)Double"<<endl<<"5)Float"<<endl
				<<"Ingrese que tipo de dato quiere ingresar en el campo:";
			cin>>opcion;
			if (opcion==1){
				tipocampos.push_back("String");
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				cout<<"Ingrese el tamaño del string:";
				cin>>tamano;
				sizes.push_back(tamano);
			}else if(opcion==2){
				tipocampos.push_back("Char");
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				sizes.push_back(1);
			}else if(opcion==3){
				tipocampos.push_back("Integer");
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				sizes.push_back(0);
			}else if(opcion==4){
				tipocampos.push_back("Double");
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				sizes.push_back(0);
			}else if(opcion==5){
				tipocampos.push_back("Float");
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				sizes.push_back(0);
			}else{
				cout<<"Campo no es válido."<<endl;
			}
			cout<<"Desea continuar agregando campos? [S/N]: ";
			char resp;
			cin>>resp;
			if (resp=='S' || resp=='s'){
			
			}else{
				break;
			}
		}
	
		ofstream fileCampos;
		fileCampos.open("Metadata.txt");
		for (int i = 0; i < nombrecampos.size(); i++){
			fileCampos<<nombrecampos[i]<<" ";
		}	
		fileCampos.close();

		ofstream fileTipoCampos;
		fileTipoCampos.open("Metadata3.txt");
		for (int i = 0; i < tipocampos.size(); i++){
			fileTipoCampos<<tipocampos[i]<<" ";
		}	
		fileTipoCampos.close();

		ofstream longitudCampos;
		longitudCampos.open("Metadata2.txt");
		for (int i = 0; i < sizes.size(); i++){
			longitudCampos<<sizes[i]<<",";
		}
		longitudCampos.close();
		cout<<"-------------------------------------------------"<<endl;
		ofstream out("Registro.bin", ios::out|ios::binary);

		while(true){
			cout<<"Ingrese los datos:"<<endl;
			for (int i = 0; i < tipocampos.size(); ++i){
				if(tipocampos[i]=="String"){
					cout<<"Ingrese la cadena perteneciente al campo "<<nombrecampos[i]<<endl;
					char cadena[sizes[i]];
					cin>>cadena;
					out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
				}else if(tipocampos[i]=="Char"){
					cout<<"Ingrese el caracter perteneciente al campo "<<nombrecampos[i]<<endl;
					char caracter;
					cin>>caracter;
					out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
				}else if(tipocampos[i]=="Integer"){
					cout<<"Ingrese el entero perteneciente al campo "<<nombrecampos[i]<<endl;
					int entero;
					cin>>entero;
					out.write(reinterpret_cast<char*>(&entero), sizeof(int));
				}else if(tipocampos[i]=="Float"){
					cout<<"Ingrese el float perteneciente al campo "<<nombrecampos[i]<<endl;
					float flotante;
					cin>>flotante;
					out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
				}else{
					cout<<"Ingrese el double perteneciente al campo "<<nombrecampos[i]<<endl;
					double doble;
					cin>>doble;
					out.write(reinterpret_cast<char*>(&doble), sizeof(double));
				}
			}


			cout<<"Desea agregar otro registro? [S/N]:";
			char resp2;
			cin>>resp2;
			if (resp2=='s' || resp2=='S'){
			
			}else{
				out.close();
				break;
			}
		}
	}else if(opcion2==2){
		string metadata = "";
		string metadata2 = "";
		string metadata3 = "";
		ifstream file("Metadata.txt");
		getline(file,metadata);
		file.close();
		ifstream file2("Metadata2.txt");
		getline(file2,metadata2);
		file2.close();
		ifstream file3("Metadata3.txt");
		getline(file3,metadata3);
		file3.close();
		////////////////////////////
		stringstream ss1(metadata);
		string read;
		while(ss1 >> read){
			nombrecampos.push_back(read);		
		}
		////////////////////////////
		stringstream ss2(metadata2);
		int e;
		while(ss2 >> e){
			sizes.push_back(e);
			if(ss2.peek() == ','){
				ss2.ignore();
			}
		}
		///////////////////////////
		stringstream ss3(metadata3);
		string read3;
		while(ss3 >> read3){
			tipocampos.push_back(read3);
		}
		///////////////////////////

		int totalbuffer = 0;
		vector<int> tamanosreales;
		for (int i = 0; i < tipocampos.size(); i++){
			if (tipocampos[i]=="String"){
				tamanosreales.push_back(sizeof(char)*sizes[i]);
				totalbuffer += sizeof(char)*sizes[i];	
			}else if(tipocampos[i]=="Char"){
				tamanosreales.push_back(sizeof(char));
				totalbuffer += sizeof(char);
			}else if(tipocampos[i]=="Integer"){
				tamanosreales.push_back(sizeof(int));
				totalbuffer += sizeof(int);
			}else if(tipocampos[i]=="Float"){
				tamanosreales.push_back(sizeof(float));
				totalbuffer += sizeof(float);
			}else if(tipocampos[i]=="Double"){
				tamanosreales.push_back(sizeof(double));
				totalbuffer += sizeof(double);
			}
		}
		/////////////////////////////////////////////////////////////
		cout<<endl<<endl;
		for (int i = 0; i < nombrecampos.size(); i++)
		{
			cout<<setw(10)<<nombrecampos[i];
		}
		cout<<endl<<"---------------------------------------------------------------------"<<endl;
		ifstream in("Registro.bin", ios::in|ios::binary);
		char buffer[totalbuffer];
		int progress = 0;
		while(in.good()){ ///quitar el eof

			in.read(buffer,totalbuffer);
			if(in.eof()){
				break;
			}
			progress = 0;
			for (int i = 0; i < tipocampos.size(); i++){
				if (tipocampos[i]=="String"){
					char chain[sizes[i]];
					memcpy(chain, buffer+progress, sizes[i]-1);
					chain[sizes[i]-1] = '\0';
					progress += sizes[i];
					cout<<setw(10)<<chain;
					
				}else if(tipocampos[i]=="Char"){
					char car[2];
					memcpy(car,buffer+progress,sizeof(char));
					progress += sizeof(char);
					car[1] = '\0';
					cout<<setw(10)<<car;
				
				}else if(tipocampos[i]=="Integer"){
					charint elEntero;
					int entero;
					memcpy(elEntero.raw,buffer+progress,sizeof(int));
					progress += sizeof(int);
					entero = elEntero.num;
					cout<<setw(10)<<entero;

				}else if(tipocampos[i]=="Float"){
					charfloat elFloat;
					float elFlotante;
					memcpy(elFloat.raw,buffer+progress,sizeof(float));
					progress += sizeof(float);
					elFlotante = elFloat.num;
					cout<<setw(10)<<elFlotante;
				
				}else if(tipocampos[i]=="Double"){
					chardouble elDouble;
					double elDoble;
					memcpy(elDouble.raw,buffer+progress,sizeof(double));
					progress += sizeof(double);
					elDoble = elDouble.num;
					cout<<setw(10)<<elDoble;
				}
			}
			cout<<endl;
		}
		in.close();


	}

	return 0;
}