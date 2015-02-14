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
	vector<int> tipocampos;
	vector<char*> nombrecampos;
	vector<string> espejoCampos;
	vector<int> sizes;
	int opcion;
	int tamano;
	int CantidadCampos;
	char nombre[20];
	int opcion2;
	cout<<"1)Ingresar nuevo"<<endl<<"2)Leer"<<endl<<"3)Agregar mas registros"<<endl<<"4)Borrar registro"<<endl
		<<"Ingrese el codigo de lo que desea hacer:";
	cin>>opcion2;
	if (opcion2==1){
		cout<<"Ingrese cuantos campos tendra su estructura: ";
		cin>>CantidadCampos;
		ofstream out("Registro.bin", ios::out|ios::binary);
		out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int)); //Guarda la cantidad de campos en el archivo binario
		int contador = 0;
		while(true){
			cout<<endl
				<<"1)String"<<endl<<"2)Char"<<endl<<"3)Integer"<<endl<<"4)Double"<<endl<<"5)Float"<<endl
				<<"Ingrese que tipo de dato quiere ingresar en el campo:";
			cin>>opcion;
			if (opcion==1){
				tipocampos.push_back(1);
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				espejoCampos.push_back(nombre);
				cout<<"Ingrese el tamaño del string:";
				cin>>tamano;
				sizes.push_back(tamano);
				out.write(reinterpret_cast<char*>(&nombre), sizeof(char)*20);
			}else if(opcion==2){
				tipocampos.push_back(2);
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				espejoCampos.push_back(nombre);
				sizes.push_back(1);
				out.write(reinterpret_cast<char*>(&nombre), sizeof(char)*20);
			}else if(opcion==3){
				tipocampos.push_back(3);
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				espejoCampos.push_back(nombre);
				sizes.push_back(0);
				out.write(reinterpret_cast<char*>(&nombre), sizeof(char)*20);
			}else if(opcion==4){
				tipocampos.push_back(4);
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				espejoCampos.push_back(nombre);
				sizes.push_back(0);
				out.write(reinterpret_cast<char*>(&nombre), sizeof(char)*20);
			}else if(opcion==5){
				tipocampos.push_back(5);
				cout<<"Ingrese nombre del campo:";
				cin>>nombre;
				nombrecampos.push_back(nombre);
				espejoCampos.push_back(nombre);
				sizes.push_back(0);
				out.write(reinterpret_cast<char*>(&nombre), sizeof(char)*20);
			}else{
				cout<<"Campo no es válido."<<endl;
			}

			contador++;
			if (contador==CantidadCampos){
				break;
			}
		}
		//////////////////////////////////////////////////////////////////	

		for (int i = 0; i < tipocampos.size(); i++){
			out.write(reinterpret_cast<char*>(&tipocampos[i]), sizeof(int));
		}	

		for (int i = 0; i < sizes.size(); i++){
			out.write(reinterpret_cast<char*>(&sizes[i]), sizeof(int));
		}
		cout<<"-------------------------------------------------"<<endl;
		

		while(true){
			cout<<"Ingrese los datos:"<<endl;
			for (int i = 0; i < tipocampos.size(); ++i){
				if(tipocampos[i]==1){
					cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
					char cadena[sizes[i]];
					cin>>cadena;
					out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
				}else if(tipocampos[i]==2){
					cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
					char caracter;
					cin>>caracter;
					out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
				}else if(tipocampos[i]==3){
					cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
					int entero;
					cin>>entero;
					out.write(reinterpret_cast<char*>(&entero), sizeof(int));
				}else if(tipocampos[i]==5){
					cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
					float flotante;
					cin>>flotante;
					out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
				}else{
					cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
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
		ifstream in("Registro.bin", ios::in|ios::binary);
		tipocampos.clear();
		nombrecampos.clear();
		sizes.clear();
		char buf[sizeof(int)];
		in.read(buf,sizeof(int));
		charint primeraleida;
		memcpy(primeraleida.raw,buf,sizeof(int));
		CantidadCampos = primeraleida.num;
		char BufferNombres[CantidadCampos*sizeof(char)*20];
		in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
		int progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			char eslabon[20];
			memcpy(eslabon,BufferNombres+progreso,19);
			eslabon[19]='\0';
			cout<<setw(10)<<eslabon;
			progreso += sizeof(char)*20;
			nombrecampos.push_back(eslabon);
		}	
		char BufferTipo[CantidadCampos*sizeof(int)];
		in.read(BufferTipo,CantidadCampos*sizeof(int));
		charint CI;
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
			tipocampos.push_back(CI.num);
			progreso += sizeof(int);
		}
		/////////
		char BufferSizes[CantidadCampos*sizeof(int)];
		charint elSize;
		in.read(BufferSizes,CantidadCampos*sizeof(int));
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(elSize.raw,BufferSizes+progreso,sizeof(int));
			sizes.push_back(elSize.num);
			progreso += sizeof(int);
		}

		///////////////////////////
		int totalbuffer = 0;
		vector<int> tamanosreales;
		for (int i = 0; i < tipocampos.size(); i++){
			if (tipocampos[i]==1){
				tamanosreales.push_back(sizeof(char)*sizes[i]);
				totalbuffer += sizeof(char)*sizes[i];	
			}else if(tipocampos[i]==2){
				tamanosreales.push_back(sizeof(char));
				totalbuffer += sizeof(char);
			}else if(tipocampos[i]==3){
				tamanosreales.push_back(sizeof(int));
				totalbuffer += sizeof(int);
			}else if(tipocampos[i]==5){
				tamanosreales.push_back(sizeof(float));
				totalbuffer += sizeof(float);
			}else if(tipocampos[i]==4){
				tamanosreales.push_back(sizeof(double));
				totalbuffer += sizeof(double);
			}
		}
		cout<<endl<<"---------------------------------------------------------------------"<<endl;		
		char buffer[totalbuffer];
		int progress = 0;
		while(in.good()){ ///quitar el eof

			in.read(buffer,totalbuffer);
			if(in.eof()){
				break;
			}
			progress = 0;
			for (int i = 0; i < tipocampos.size(); i++){
				if (tipocampos[i]==1){
					char chain[sizes[i]];
					memcpy(chain, buffer+progress, sizes[i]-1);
					chain[sizes[i]-1] = '\0';
					progress += sizes[i];
					cout<<setw(10)<<chain;
					
				}else if(tipocampos[i]==2){
					char car[2];
					memcpy(car,buffer+progress,sizeof(char));
					progress += sizeof(char);
					car[1] = '\0';
					cout<<setw(10)<<car;
				
				}else if(tipocampos[i]==3){
					charint elEntero;
					int entero;
					memcpy(elEntero.raw,buffer+progress,sizeof(int));
					progress += sizeof(int);
					entero = elEntero.num;
					cout<<setw(10)<<entero;

				}else if(tipocampos[i]==5){
					charfloat elFloat;
					float elFlotante;
					memcpy(elFloat.raw,buffer+progress,sizeof(float));
					progress += sizeof(float);
					elFlotante = elFloat.num;
					cout<<setw(10)<<elFlotante;
				
				}else if(tipocampos[i]==4){
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

	}else if(opcion2==3){

	}else if(opcion2==4){

		ifstream in("Registro.bin", ios::in|ios::binary);
		tipocampos.clear();
		nombrecampos.clear();
		sizes.clear();
		char buf[sizeof(int)];
		in.read(buf,sizeof(int));
		charint primeraleida;
		memcpy(primeraleida.raw,buf,sizeof(int));
		CantidadCampos = primeraleida.num;
		char BufferNombres[CantidadCampos*sizeof(char)*20];
		in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
		int progreso = 0;
		cout<<setw(10)<<"Indice";
		for (int i = 0; i < CantidadCampos; ++i){
			char eslabon[20];
			memcpy(eslabon,BufferNombres+progreso,19);
			eslabon[19]='\0';
			cout<<setw(10)<<eslabon;
			progreso += sizeof(char)*20;
			nombrecampos.push_back(eslabon);
		}	
		char BufferTipo[CantidadCampos*sizeof(int)];
		in.read(BufferTipo,CantidadCampos*sizeof(int));
		charint CI;
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
			tipocampos.push_back(CI.num);
			progreso += sizeof(int);
		}
		/////////
		char BufferSizes[CantidadCampos*sizeof(int)];
		charint elSize;
		in.read(BufferSizes,CantidadCampos*sizeof(int));
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(elSize.raw,BufferSizes+progreso,sizeof(int));
			sizes.push_back(elSize.num);
			progreso += sizeof(int);
		}

		///////////////////////////
		int totalbuffer = 0;
		vector<int> tamanosreales;
		for (int i = 0; i < tipocampos.size(); i++){
			if (tipocampos[i]==1){
				tamanosreales.push_back(sizeof(char)*sizes[i]);
				totalbuffer += sizeof(char)*sizes[i];	
			}else if(tipocampos[i]==2){
				tamanosreales.push_back(sizeof(char));
				totalbuffer += sizeof(char);
			}else if(tipocampos[i]==3){
				tamanosreales.push_back(sizeof(int));
				totalbuffer += sizeof(int);
			}else if(tipocampos[i]==5){
				tamanosreales.push_back(sizeof(float));
				totalbuffer += sizeof(float);
			}else if(tipocampos[i]==4){
				tamanosreales.push_back(sizeof(double));
				totalbuffer += sizeof(double);
			}
		}
		cout<<endl<<"---------------------------------------------------------------------"<<endl;		
		char buffer[totalbuffer];
		int progress = 0;
		int correlativo = -1;
		while(in.good()){ ///quitar el eof
			correlativo++;
			in.read(buffer,totalbuffer);
			if(in.eof()){
				break;
			}
			progress = 0;
			cout<<setw(10)<<correlativo;
			for (int i = 0; i < tipocampos.size(); i++){
				if (tipocampos[i]==1){
					char chain[sizes[i]];
					memcpy(chain, buffer+progress, sizes[i]-1);
					chain[sizes[i]-1] = '\0';
					progress += sizes[i];
					cout<<setw(10)<<chain;
					
				}else if(tipocampos[i]==2){
					char car[2];
					memcpy(car,buffer+progress,sizeof(char));
					progress += sizeof(char);
					car[1] = '\0';
					cout<<setw(10)<<car;
				
				}else if(tipocampos[i]==3){
					charint elEntero;
					int entero;
					memcpy(elEntero.raw,buffer+progress,sizeof(int));
					progress += sizeof(int);
					entero = elEntero.num;
					cout<<setw(10)<<entero;

				}else if(tipocampos[i]==5){
					charfloat elFloat;
					float elFlotante;
					memcpy(elFloat.raw,buffer+progress,sizeof(float));
					progress += sizeof(float);
					elFlotante = elFloat.num;
					cout<<setw(10)<<elFlotante;
				
				}else if(tipocampos[i]==4){
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
		int indiceBorrado;
		cout<<"Ingrese el indice de el registro que desea eliminar:";
		cin>>indiceBorrado;

		ifstream er("Registro.bin", ios::in|ios::binary);

		int offset = 0;
		offset += sizeof(int);
		er.close();

	}//end if 4

	return 0;
}