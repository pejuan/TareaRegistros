#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include <unistd.h>
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
struct IndString{
	int rrn;
	char key[20];
};
struct IndNum{
	int rrn;
	int key;
};
struct Nodo{
	IndNum dato;
	Nodo* izq;
	Nodo* der;
};
Nodo* getNew(IndNum data){
	Nodo* nuevo = new Nodo();
	nuevo->dato = data;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	return nuevo;
}
Nodo* insertar(Nodo* raiz, IndNum data){
	if(raiz == NULL){
		raiz = getNew(data);
	}else if(data.key <= raiz->dato.key){
		raiz->izq = insertar(raiz->izq, data);
	}else{
		raiz->der = insertar(raiz->der, data);
	}
	return raiz;
}
bool buscar(Nodo* raiz, IndNum data){
	if(raiz == NULL){

	}
}
void quicksort(int[],int, int, int[]);
void sort(string[],int,int,int[]);
void reindex(char[]);
void leer();
void leerRRN();

int main(int argc, char** argv){
	char fileName[30];
	char fileIndexName[30];
	while(true){
		cout<<"------------------------------------------------------------------------------------------------------------"<<endl
			<<endl;
		cout<<"Para comenzar ingrese el nombre del archivo con el que trabajará:";
		cin>>fileName;
		stringstream arch;
		stringstream archind;
		arch<<fileName<<".bin";
		arch>>fileName;
		archind<<fileName<<".index";
		archind>>fileIndexName;
		if( access(fileName, F_OK) != -1){				
			break;
		}
	}
	while(true){
		vector<int> tipocampos;
		vector<IndString> listaindicesstrings;
		vector<IndNum> listaindicesINT;
		vector<char*> nombrecampos;
		vector<string> espejoCampos;
		vector<int> sizes;
		vector<int> AvailList;
		vector<int> listaIntKeys;
		vector<string> listaStrKeys;
		int opcion;
		int tamano;
		int CantidadCampos;
		char namekey[20];		
		string namekeyespejo;
		char nombre[20];
		int opcion2;
		int tipoLlave;
		cout<<"------------------------------------------------------------------------------------------------------------"<<endl
			<<endl;
		cout<<"0)Abrir archivo"<<endl<<"1)Ingresar nuevo"<<endl<<"2)Listar"<<endl<<"3)Agregar nuevo registro"<<endl<<"4)Borrar registro"<<endl
			<<"5)Buscar registro"<<endl<<"6)Modificar"<<endl<<"7)Compactar"<<endl<<"8)Salir"<<endl
			<<"9)Reindexar"<<endl<<"10)Agregar con índice"<<endl<<"11)Cruzar archivos"<<endl<<"Ingrese el codigo de lo que desea hacer:";
		cin>>opcion2;
		if (opcion2==1){
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
			stringstream archive;
			stringstream archiveind;
			archive<<fileName<<".bin";
			archive>>fileName;
			archiveind<<fileName<<".index";
			archiveind>>fileIndexName;
			cout<<"Ingrese cuantos campos tendra su estructura sin contar la llave: ";
			cin>>CantidadCampos;
			CantidadCampos++;
			ofstream out(fileName, ios::out|ios::binary);
			int avail = -1;
			AvailList.push_back(avail);
			 
			int contador = 0;
			IndString keyStr;
			IndNum keyNum;
			cout<<"---------------------"<<endl<<"1)String"<<endl<<"2)Integer"<<endl<<"0)Sin Llave"<<endl<<"Ingrese de que tipo sera su Llave primaria:";
			cin>>tipoLlave;
			if(tipoLlave==1){
				out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int)); //Guarda la cantidad de campos en el archivo binario
				out.write(reinterpret_cast<char*>(&avail), sizeof(int));//Guarda el primer elemento de avail list
				cout<<"Ingrese el nombre de su llave de tipo String:";
				cin>>namekey;
				namekeyespejo = namekey;
				nombrecampos.push_back(namekey);
				espejoCampos.push_back(namekey);
				out.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
				out.write(reinterpret_cast<char*>(&namekey),sizeof(char)*20);
				tipocampos.push_back(1);
				sizes.push_back(20);
			}else if(tipoLlave==2){
				out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int)); //Guarda la cantidad de campos en el archivo binario
				out.write(reinterpret_cast<char*>(&avail), sizeof(int));//Guarda el primer elemento de avail list
				tipoLlave = 3;
				tipocampos.push_back(3);
				cout<<"Ingrese el nombre de su llave de tipo Integer:";
				cin>>namekey;
				namekeyespejo = namekey;
				nombrecampos.push_back(namekey);
				espejoCampos.push_back(namekey);
				out.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
				out.write(reinterpret_cast<char*>(&namekey),sizeof(char)*20);
				sizes.push_back(0);
			}else{
				CantidadCampos--;
				tipoLlave = 0;
				out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int)); //Guarda la cantidad de campos en el archivo binario
				out.write(reinterpret_cast<char*>(&avail), sizeof(int));//Guarda el primer elemento de avail list
				out.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
			}
			int finish;
			if(tipoLlave==1 || tipoLlave==3){
				finish = CantidadCampos-1;
			}else{
				finish = CantidadCampos;
			}
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
				if (contador==finish){//causa error si no hay llave
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
			
			int counter = 0;
			bool exists = false;
			bool continuar = true;
			ofstream indexout(fileIndexName, ios::out|ios::binary);
			while(true){
				exists = false;
				continuar = true;
				cout<<"Ingrese los datos:"<<endl;
				while(continuar){
					if(tipoLlave==1){
						cout<<"Ingrese la cadena perteneciente al campo llave llamado "<<namekeyespejo<<":";
						char cadenallave[20];
						cin>>cadenallave;
						string strcadenallave = cadenallave;
						for (int i = 0; i < listaStrKeys.size(); i++){
							if(strcadenallave==listaStrKeys[i]){
								exists = true;
								cout<<"Llave primaria no debe repetirse!"<<endl;
							}
						}
						if(!exists){
							listaStrKeys.push_back(strcadenallave);
							out.write(reinterpret_cast<char*>(&cadenallave),sizeof(char)*20);
							indexout.write(reinterpret_cast<char*>(&cadenallave),sizeof(char)*20);
							continuar=false;
						}
					}else if(tipoLlave==3){
						cout<<"Ingrese el entero perteneciente al campo llave llamado "<<namekeyespejo<<":";
						int intllave;
						cin>>intllave;
						for (int i = 0; i < listaIntKeys.size(); i++){
							if(intllave==listaIntKeys[i]){
								exists = true;
								cout<<"Llave primaria no debe repetirse!"<<endl;
							}
						}
						if(!exists){
							listaIntKeys.push_back(intllave);
							out.write(reinterpret_cast<char*>(&intllave),sizeof(int));
							indexout.write(reinterpret_cast<char*>(&intllave),sizeof(int));
							continuar=false;
						}

					}else{
						break;
					}

				}


				int start;
				if(tipoLlave==1 || tipoLlave==3){
					start=1;
				}else{
					start=0;
				}
				for (int i = start; i < tipocampos.size(); ++i){//causa error si no hay llave
					if(tipocampos[i]==1){
						cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
						char cadena[sizes[i]];
						cin>>cadena;
						out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
					}else if(tipocampos[i]==2){
						cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
						char caracter;
						cin>>caracter;
						out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
					}else if(tipocampos[i]==3){
						cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
						int entero;
						cin>>entero;
						out.write(reinterpret_cast<char*>(&entero), sizeof(int));
					}else if(tipocampos[i]==5){
						cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
						float flotante;
						cin>>flotante;
						out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
					}else{
						cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
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
					indexout.close();
					cout<<"Estructura creada con éxito y registros agregados con éxito."<<endl;
					if (tipoLlave==1 || tipoLlave==3){
						reindex(fileName);
					}
					
					break;
				}
				
			}
		}else if(opcion2==2){ //Leer

			ifstream in(fileName, ios::in|ios::binary); //cambiar de vuelta a registro.bin
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			char buf[sizeof(int)*3]; //antes tenia *2
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
			CantidadCampos = primeraleida.num;
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			AvailList.push_back(primerAvail.num);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			char BufferNombres[CantidadCampos*sizeof(char)*20];
			in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
			int progreso = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				char eslabon[20];
				memcpy(eslabon,BufferNombres+progreso,19);
				eslabon[19]='\0';
				cout<<setw(15)<<eslabon;
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
			int elContador = 1;
			while(in.good()){ ///quitar el eof

				in.read(buffer,totalbuffer);
				if(in.eof()){
					break;
				}
				progress = 0;
				char verificacion[2];
				memcpy(verificacion,buffer,sizeof(char));
				verificacion[1] = '\0';
				if (verificacion[0]=='*'){
					
				}else{
					for (int i = 0; i < tipocampos.size(); i++){
						if (tipocampos[i]==1){
							char chain[sizes[i]];
							memcpy(chain, buffer+progress, sizes[i]-1);
							chain[sizes[i]-1] = '\0';
							progress += sizes[i];
							cout<<setw(15)<<chain;
						
						}else if(tipocampos[i]==2){
							char car[2];
							memcpy(car,buffer+progress,sizeof(char));
							progress += sizeof(char);
							car[1] = '\0';
							cout<<setw(15)<<car;
					
						}else if(tipocampos[i]==3){
							charint elEntero;
							int entero;
							memcpy(elEntero.raw,buffer+progress,sizeof(int));
							progress += sizeof(int);
							entero = elEntero.num;
							cout<<setw(15)<<entero;

						}else if(tipocampos[i]==5){
							charfloat elFloat;
							float elFlotante;
							memcpy(elFloat.raw,buffer+progress,sizeof(float));
							progress += sizeof(float);
							elFlotante = elFloat.num;
							cout<<setw(15)<<elFlotante;
					
						}else if(tipocampos[i]==4){
							chardouble elDouble;
							double elDoble;
							memcpy(elDouble.raw,buffer+progress,sizeof(double));
							progress += sizeof(double);
							elDoble = elDouble.num;
							cout<<setw(15)<<elDoble;
						}
					}
					cout<<endl;
				}
				//
				if(elContador%25 == 0){
					cout<<"Quiere continuar leyendo datos?[S/N]: ";
					char option;
					cin>>option;
					if(option=='n' || option=='N'){
						break;
					}
				}
				elContador++;
			}
			in.close();

		}else if(opcion2==3){//Append
			char resp2;
			ifstream in(fileName, ios::in|ios::binary);
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			espejoCampos.clear();
			char buf[sizeof(int)*3];
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));
			CantidadCampos = primeraleida.num;
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			int cualquier = primerAvail.num;
			AvailList.push_back(cualquier);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			if(tipoLlave==1 || tipoLlave==3){

				cout<<"Este archivo contiene llave, utilice la opcion 10 para agregar."<<endl;

			}else{

				char BufferNombres[CantidadCampos*sizeof(char)*20];
				in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
				int progreso = 0;
				for (int i = 0; i < CantidadCampos; ++i){
					char eslabon[20];
					memcpy(eslabon,BufferNombres+progreso,19);
					eslabon[19]='\0';
					progreso += sizeof(char)*20;
					nombrecampos.push_back(eslabon);
					espejoCampos.push_back(eslabon);
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
				in.close();		
				cout<<"-------------------------------------------------"<<endl;
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				while(true){
					cout<<"Ingrese los datos:"<<endl;
					if(AvailList[0] != -1){ //AvailList[0] != -1
						ifstream getting(fileName,ios::in|ios::binary);	
						cout<<AvailList[0]<<endl;
						cualquier = AvailList[0];
						int offset = 0;
						offset += sizeof(int)*3;
						offset += CantidadCampos*sizeof(char)*20;
						offset += CantidadCampos*sizeof(int);
						offset += CantidadCampos*sizeof(int);
						offset += totalbuffer*cualquier;//offset a la posicion que va a reemplazar
						getting.seekg(offset+sizeof(char));//se mueve a la posicion que va a reemplazar+el * justo antes de la pos libre
						char bufAvail[sizeof(int)];
						getting.read(bufAvail,sizeof(int));//Lee la proxima posicion libre
						charint NextAvail;
						memcpy(NextAvail.raw,bufAvail,sizeof(int));
						int premiereAvail = NextAvail.num;
						getting.close();
						fstream addAvail(fileName, ios::out|ios::in|ios::binary);
						addAvail.seekp(sizeof(int));
						addAvail.write(reinterpret_cast<char*>(&premiereAvail),sizeof(int));
						addAvail.close();
						fstream rempl(fileName, ios::out|ios::in|ios::binary);
						rempl.seekp(offset);
						AvailList[0] = premiereAvail;
						cout<<AvailList[0]<<endl;
						
						
						for (int i = 0; i < tipocampos.size(); ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
								char cadena[sizes[i]];
								cin>>cadena;
								rempl.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
								char caracter;
								cin>>caracter;
								rempl.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
								int entero;
								cin>>entero;
								rempl.write(reinterpret_cast<char*>(&entero), sizeof(int));
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
								float flotante;
								cin>>flotante;
								rempl.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
								double doble;
								cin>>doble;
								rempl.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
						rempl.close();
						cout<<"Desea agregar otro registro? [S/N]:";				
						cin>>resp2;
						if (resp2=='s' || resp2=='S'){
					
						}else{
							cout<<"Registro(s) agregado(s) con éxito."<<endl;
							break;
						}

					}else{
						ofstream append(fileName, ios::out|ios::in|ios::app|ios::binary);
						ofstream indexappend(fileIndexName, ios::out|ios::app|ios::binary);
						for (int i = 0; i < tipocampos.size(); ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
								char cadena[sizes[i]];
								cin>>cadena;
								append.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
								if(tipoLlave==1 && i==0){
									indexappend.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(20));
								}
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
								char caracter;
								cin>>caracter;
								append.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
								int entero;
								cin>>entero;
								append.write(reinterpret_cast<char*>(&entero), sizeof(int));
								if(tipoLlave==3 && i==0){
									indexappend.write(reinterpret_cast<char*>(&entero), sizeof(int));
								}
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
								float flotante;
								cin>>flotante;
								append.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
								double doble;
								cin>>doble;
								append.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
						append.close();
						indexappend.close();
						cout<<"Desea agregar otro registro hasta abajo? [S/N]:";				
						cin>>resp2;
						if (resp2=='s' || resp2=='S'){
					
						}else{
							cout<<"Registro(s) agregado(s) con éxito."<<endl;
							break;
						}
					}
					
				}
			}
			


		}else if(opcion2==4){//Borrar

			ifstream in(fileName, ios::in|ios::binary);
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			char buf[sizeof(int)*3];
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));
			CantidadCampos = primeraleida.num;
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			AvailList.push_back(primerAvail.num);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			char BufferNombres[CantidadCampos*sizeof(char)*20];
			in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
			int progreso = 0;
			cout<<setw(10)<<"RRN";
			for (int i = 0; i < CantidadCampos; ++i){
				char eslabon[20];
				memcpy(eslabon,BufferNombres+progreso,19);
				eslabon[19]='\0';
				cout<<setw(15)<<eslabon;
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
			int elContador = 1;
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
						cout<<setw(15)<<chain;
						
					}else if(tipocampos[i]==2){
						char car[2];
						memcpy(car,buffer+progress,sizeof(char));
						progress += sizeof(char);
						car[1] = '\0';
						cout<<setw(15)<<car;
					
					}else if(tipocampos[i]==3){
						charint elEntero;
						int entero;
						memcpy(elEntero.raw,buffer+progress,sizeof(int));
						progress += sizeof(int);
						entero = elEntero.num;
						cout<<setw(15)<<entero;

					}else if(tipocampos[i]==5){
						charfloat elFloat;
						float elFlotante;
						memcpy(elFloat.raw,buffer+progress,sizeof(float));
						progress += sizeof(float);
						elFlotante = elFloat.num;
						cout<<setw(15)<<elFlotante;
					
					}else if(tipocampos[i]==4){
						chardouble elDouble;
						double elDoble;
						memcpy(elDouble.raw,buffer+progress,sizeof(double));
						progress += sizeof(double);
						elDoble = elDouble.num;
						cout<<setw(15)<<elDoble;
					}
				}
				cout<<endl;
				if(elContador%25 == 0){
					cout<<"Quiere continuar listando datos?[S/N]: ";
					char option;
					cin>>option;
					if(option=='n' || option=='N'){
						break;
					}
				}
				elContador++;
			}
			in.close();
			cout<<"1)Por Indice"<<endl<<"2)Por RRN"<<endl<<"3)Cancelar"<<endl<<"Opcion de eliminar:";
			int opcionEliminar;
			cin>>opcionEliminar;
			char mark = '*';
			if(opcionEliminar==2){
				int indiceBorrado;
				cout<<"Ingrese el RRN de el registro que desea eliminar:";
				cin>>indiceBorrado;
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				offset += totalbuffer*indiceBorrado;
				ifstream checker(fileName,ios::in|ios::binary);
				checker.seekg(sizeof(int));
				char charAvail[sizeof(int)];
				checker.read(charAvail,sizeof(int));
				charint tmp;
				memcpy(tmp.raw,charAvail,sizeof(int));
				int tmpnum = tmp.num;
				checker.close();
				fstream er(fileName, ios::out|ios::in|ios::binary);	
				er.seekp(offset);				
				er.write(reinterpret_cast<char*>(&mark),sizeof(char));
				er.write(reinterpret_cast<char*>(&tmpnum),sizeof(int));
				er.close();
				cout<<"Borrado con exito!"<<endl;
				fstream act(fileName, ios::out|ios::in|ios::binary);
				act.seekp(sizeof(int));
				act.write(reinterpret_cast<char*>(&indiceBorrado),sizeof(int));
				act.close();
			}else if(opcionEliminar==1){
				char LlaveStr[20];
				int LlaveEntero;
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				if(tipoLlave==1){
					cout<<"Ingrese la llave del registro que desea eliminar:";
					cin>>LlaveStr;
					string KeyLLaveStr = LlaveStr;
					fstream eliminateRead(fileName,ios::in|ios::out|ios::binary);
					eliminateRead.seekg(offset);
					int count = 0;
					bool encontrado = false;
					while(eliminateRead.good()){

						char bufferEl[totalbuffer];
						eliminateRead.read(bufferEl,totalbuffer);
						if(eliminateRead.eof()){
							break;
						}
						char prueba[20];
						memcpy(prueba,bufferEl,sizeof(char)*19);
						prueba[19] = '\0';
						string pruebaStr = prueba;
						if(pruebaStr == KeyLLaveStr){
							encontrado = true;
							break;
						}
						count++;

					}
					eliminateRead.close();
					if(encontrado){
						ifstream lector(fileName, ios::in|ios::binary);
						lector.seekg(sizeof(int));
						char buffeAvail[sizeof(int)];
						lector.read(buffeAvail,sizeof(int));
						charint lastAvail;
						memcpy(lastAvail.raw,buffeAvail,sizeof(int));
						lector.close();
						offset = 0;
						offset += sizeof(int)*3;
						offset += CantidadCampos*sizeof(char)*20;
						offset += CantidadCampos*sizeof(int);
						offset += CantidadCampos*sizeof(int);
						offset += totalbuffer*count;
						fstream eliminador(fileName,ios::out|ios::in|ios::binary);
						eliminador.seekp(offset);
						eliminador.write(reinterpret_cast<char*>(&mark),sizeof(char));
						eliminador.write(reinterpret_cast<char*>(&lastAvail.num),sizeof(int));
						eliminador.close();
						fstream actualizador(fileName,ios::out|ios::in|ios::binary);
						actualizador.seekp(sizeof(int));
						actualizador.write(reinterpret_cast<char*>(&count),sizeof(int));
						actualizador.close();
						cout<<"Eliminado con éxito!"<<endl;
					}else{
						cout<<"Registro no encontrado"<<endl;
					}
				}else if(tipoLlave==3){
					cout<<"Ingrese la llave del registro que desea eliminar:";
					cin>>LlaveEntero;
					fstream eliminateRead(fileName,ios::in|ios::out|ios::binary);
					eliminateRead.seekg(offset);
					int count = 0;
					bool encontrado = false;
					while(eliminateRead.good()){

						char bufferEl[totalbuffer];
						eliminateRead.read(bufferEl,totalbuffer);
						if(eliminateRead.eof()){
							break;
						}
						charint pruebaInt;
						memcpy(pruebaInt.raw,bufferEl,sizeof(int));
						if(pruebaInt.num == LlaveEntero){
							encontrado = true;
							break;
						}
						count++;

					}
					eliminateRead.close();
					if(encontrado){
						ifstream lector(fileName, ios::in|ios::binary);
						lector.seekg(sizeof(int));
						char buffeAvail[sizeof(int)];
						charint lastAvail;
						lector.read(buffeAvail,sizeof(int));
						memcpy(lastAvail.raw,buffeAvail,sizeof(int));
						lector.close();
						offset = 0;
						offset += sizeof(int)*3;
						offset += CantidadCampos*sizeof(char)*20;
						offset += CantidadCampos*sizeof(int);
						offset += CantidadCampos*sizeof(int);
						offset += totalbuffer*count;
						fstream eliminador(fileName,ios::out|ios::in|ios::binary);
						eliminador.seekp(offset);
						eliminador.write(reinterpret_cast<char*>(&mark),sizeof(char));
						eliminador.write(reinterpret_cast<char*>(&lastAvail.num),sizeof(int));
						eliminador.close();
						fstream actualizador(fileName,ios::out|ios::in|ios::binary);
						actualizador.seekp(sizeof(int));
						actualizador.write(reinterpret_cast<char*>(&count),sizeof(int));
						actualizador.close();
						cout<<"Eliminado con éxito!"<<endl;
					}else{
						cout<<"Registro no encontrado"<<endl;
					}

				}else{
					cout<<"Registros no contienen llave!"<<endl;
				}

			}else{//cancelar eliminar

			}
			
			//end if 4
		}else if(opcion2==5){//buscar

			int metodo;
			ifstream in(fileName, ios::in|ios::binary);
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			char buf[sizeof(int)*3];
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));
			CantidadCampos = primeraleida.num;
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			AvailList.push_back(primerAvail.num);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			char BufferNombres[CantidadCampos*sizeof(char)*20];
			in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
			int progreso = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				char eslabon[20];
				memcpy(eslabon,BufferNombres+progreso,19);
				eslabon[19]='\0';
				progreso += sizeof(char)*20;
				nombrecampos.push_back(eslabon);
				espejoCampos.push_back(eslabon);
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
			in.close();
			cout<<"Elija el metodo con el que realizara la busqueda"<<endl<<"1)Por RRN"<<endl<<"2)Por Campo"<<endl<<"3)Por Indice lineal"
				<<endl<<"Ingrese codigo de opcion:";
			cin>>metodo;
			if (metodo==1){////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				ifstream busq(fileName,ios::in|ios::binary);
				cout<<"Ingrese el RRN del registro que quiere desplegar:";
				int index;
				cin>>index;
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				offset += totalbuffer*index;
				busq.seekg(offset);
				char buffer[totalbuffer];
				busq.read(buffer,totalbuffer);
				for (int i = 0; i < tipocampos.size(); ++i){
					cout<<setw(15)<<espejoCampos[i];
				}
				cout<<endl<<"-----------------------------------------------------------------------"<<endl;
				int progress = 0;
				for (int i = 0; i < tipocampos.size(); i++){
						if (tipocampos[i]==1){
							char chain[sizes[i]];
							memcpy(chain, buffer+progress, sizes[i]-1);
							chain[sizes[i]-1] = '\0';
							progress += sizes[i];
							cout<<setw(15)<<chain;
						
						}else if(tipocampos[i]==2){
							char car[2];
							memcpy(car,buffer+progress,sizeof(char));
							progress += sizeof(char);
							car[1] = '\0';
							cout<<setw(15)<<car;
					
						}else if(tipocampos[i]==3){
							charint elEntero;
							int entero;
							memcpy(elEntero.raw,buffer+progress,sizeof(int));
							progress += sizeof(int);
							entero = elEntero.num;
							cout<<setw(15)<<entero;

						}else if(tipocampos[i]==5){
							charfloat elFloat;
							float elFlotante;
							memcpy(elFloat.raw,buffer+progress,sizeof(float));
							progress += sizeof(float);
							elFlotante = elFloat.num;
							cout<<setw(15)<<elFlotante;
					
						}else if(tipocampos[i]==4){
							chardouble elDouble;
							double elDoble;
							memcpy(elDouble.raw,buffer+progress,sizeof(double));
							progress += sizeof(double);
							elDoble = elDouble.num;
							cout<<setw(15)<<elDoble;
						}
				}
				cout<<endl<<endl;
				busq.close();
			}else if(metodo==2){

				int fieldIndex;
				for (int i = 0; i < espejoCampos.size(); ++i){
					cout<<i<<")"<<espejoCampos[i]<<endl;
				}
				cout<<"Ingrese el codigo del campo por el cual buscara:";
				cin>>fieldIndex;
				char llaveString[sizes[fieldIndex]];
				char llaveChar;
				int llaveInt;
				double llaveDouble;
				float llaveFloat;
				cout<<"Ingrese el valor buscado:";
				int tamanoDato;
				if(tipocampos[fieldIndex]==1){//string
					tamanoDato = sizeof(char)*sizes[fieldIndex];
					cin>>llaveString;
				}else if(tipocampos[fieldIndex]==2){//char
					cin>>llaveChar;
					tamanoDato = sizeof(char);
				}else if(tipocampos[fieldIndex]==3){//int
					cin>>llaveInt;
					tamanoDato = sizeof(int);
				}else if(tipocampos[fieldIndex]==4){//double
					cin>>llaveDouble;
					tamanoDato = sizeof(double);
				}else{//float
					cin>>llaveFloat;
					tamanoDato = sizeof(float);
				}
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				ifstream busq(fileName,ios::in|ios::binary);
				busq.seekg(offset);
				char lectura[totalbuffer];
				int minioffset = 0;
				for (int i = 0; i < fieldIndex; ++i){
					if(tipocampos[i]==1){
						minioffset += sizes[i]*sizeof(char);

					}else if(tipocampos[i]==2){
						minioffset += sizeof(char);

					}else if(tipocampos[i]==3){
						minioffset += sizeof(int);

					}else if(tipocampos[i]==4){//double
						minioffset += sizeof(double);

					}else if(tipocampos[i]==5){//float
						minioffset += sizeof(float);
					}
				}
				int contador = 0;
				bool found = false;
				while(busq.good()){

					busq.read(lectura,totalbuffer);
					if(in.eof()){
						break;
					}
					char verificacion[2];
					memcpy(verificacion,lectura,sizeof(char));
					verificacion[1] = '\0';
					if (verificacion[0]=='*'){
					
					}else{
						if(tipocampos[fieldIndex]==1){
							char datiles[sizes[fieldIndex]];
							memcpy(datiles, lectura+minioffset,tamanoDato-1);
							datiles[tamanoDato-1] = '\0';
							string elDatil = datiles;
							string comparacion = llaveString;
							if (elDatil == comparacion){
								found = true;
							}

						}else if(tipocampos[fieldIndex]==2){
							char datiles[2];
							memcpy(datiles,lectura+minioffset,sizeof(char));
							datiles[1]='\0';
							if (datiles[0] == llaveChar){
								found = true;
							}

						}else if(tipocampos[fieldIndex]==3){
							charint datiles;
							memcpy(datiles.raw,lectura+minioffset,sizeof(int));
							if (datiles.num == llaveInt){
								found = true;
							}
						}else if(tipocampos[fieldIndex]==4){//double
							chardouble datiles;
							memcpy(datiles.raw,lectura+minioffset,sizeof(double));
							if (datiles.num == llaveDouble){
								found = true;
							}

						}else if(tipocampos[fieldIndex]==5){//float
							charfloat datiles;
							memcpy(datiles.raw,lectura+minioffset,sizeof(float));
							if (datiles.num == llaveFloat){
								found = true;
							}
						}					
					}//end else

					if(found){
						for (int i = 0; i < espejoCampos.size(); ++i){
							cout<<setw(15)<<espejoCampos[i];
						}
						cout<<endl<<"---------------------------------------------------------------------"<<endl;
						int progress = 0;
						for (int i = 0; i < tipocampos.size(); i++){
							if (tipocampos[i]==1){
								char chain[sizes[i]];
								memcpy(chain, lectura+progress, sizes[i]-1);
								chain[sizes[i]-1] = '\0';
								progress += sizes[i];
								cout<<setw(15)<<chain;
						
							}else if(tipocampos[i]==2){
								char car[2];
								memcpy(car,lectura+progress,sizeof(char));
								progress += sizeof(char);
								car[1] = '\0';
								cout<<setw(15)<<car;
					
							}else if(tipocampos[i]==3){
								charint elEntero;
								int entero;
								memcpy(elEntero.raw,lectura+progress,sizeof(int));
								progress += sizeof(int);
								entero = elEntero.num;
								cout<<setw(15)<<entero;

							}else if(tipocampos[i]==5){
								charfloat elFloat;
								float elFlotante;
								memcpy(elFloat.raw,lectura+progress,sizeof(float));
								progress += sizeof(float);
								elFlotante = elFloat.num;
								cout<<setw(15)<<elFlotante;
					
							}else if(tipocampos[i]==4){
								chardouble elDouble;
								double elDoble;
								memcpy(elDouble.raw,lectura+progress,sizeof(double));
								progress += sizeof(double);
								elDoble = elDouble.num;
								cout<<setw(15)<<elDoble;
							}

						}
						cout<<endl<<endl;
						break;

					}
					contador++;
				}
				busq.close();

			}else if(metodo==3){
				if(tipoLlave==1){
					cout<<"Ingrese la cadena llave del registro que busca:";
					char cadenakey[20];
					cin>>cadenakey;
					string comparadokey = cadenakey;
					fstream lectorInd(fileIndexName,ios::in|ios::out|ios::binary);
					char buffy[20];
					int cnt = 0;
					bool encontre = false;
					int offset = 0;
					offset += sizeof(int)*3;
					offset += CantidadCampos*sizeof(char)*20;
					offset += CantidadCampos*sizeof(int);
					offset += CantidadCampos*sizeof(int);
					while(lectorInd.good()){
						lectorInd.read(buffy,sizeof(char)*20);
						if(lectorInd.eof()){
							break;
						}else{
							char nuevoChain[20];
							memcpy(nuevoChain,buffy,sizeof(char)*19);
							nuevoChain[sizeof(char)*19] = '\0';
							string comp = nuevoChain;
							if(nuevoChain==comparadokey){
								encontre = true;
								break;
							}else{
								cnt++;
							}
						}

					}
					lectorInd.close();
					if(encontre){
						char buffer[totalbuffer];
						offset += totalbuffer*cnt;
						fstream finalLector(fileName,ios::in|ios::out|ios::binary);
						finalLector.seekg(offset);
						finalLector.read(buffer,totalbuffer);
						for (int i = 0; i < espejoCampos.size(); i++){
							cout<<setw(15)<<espejoCampos[i];
						}
						cout<<endl<<"--------------------------------------------------------------"<<endl;
						int progress = 0;
						for (int i = 0; i < tipocampos.size(); i++){
							if (tipocampos[i]==1){
								char chain[sizes[i]];
								memcpy(chain, buffer+progress, sizes[i]-1);
								chain[sizes[i]-1] = '\0';
								progress += sizes[i];
								cout<<setw(15)<<chain;
							
							}else if(tipocampos[i]==2){
								char car[2];
								memcpy(car,buffer+progress,sizeof(char));
								progress += sizeof(char);
								car[1] = '\0';
								cout<<setw(15)<<car;
						
							}else if(tipocampos[i]==3){
								charint elEntero;
								int entero;
								memcpy(elEntero.raw,buffer+progress,sizeof(int));
								progress += sizeof(int);
								entero = elEntero.num;
								cout<<setw(15)<<entero;

							}else if(tipocampos[i]==5){
								charfloat elFloat;
								float elFlotante;
								memcpy(elFloat.raw,buffer+progress,sizeof(float));
								progress += sizeof(float);
								elFlotante = elFloat.num;
								cout<<setw(15)<<elFlotante;
						
							}else if(tipocampos[i]==4){
								chardouble elDouble;
								double elDoble;
								memcpy(elDouble.raw,buffer+progress,sizeof(double));
								progress += sizeof(double);
								elDoble = elDouble.num;
								cout<<setw(15)<<elDoble;
							}
						}
						cout<<endl;
					
					}else{
						cout<<"Registro no encontrado"<<endl;
					}

				}else if(tipoLlave==3){

					cout<<"Ingrese el entero llave del registro que busca:";
					int intkey;
					cin>>intkey;
					fstream lectorInd(fileIndexName,ios::in|ios::out|ios::binary);
					char buffy[sizeof(int)];
					int cnt = 0;
					bool encontre = false;
					int offset = 0;
					offset += sizeof(int)*3;
					offset += CantidadCampos*sizeof(char)*20;
					offset += CantidadCampos*sizeof(int);
					offset += CantidadCampos*sizeof(int);
					while(lectorInd.good()){
						lectorInd.read(buffy,sizeof(int));
						if(lectorInd.eof()){
							break;
						}else{
							charint nuevoEntero;
							memcpy(nuevoEntero.raw,buffy,sizeof(int));
							int comparar = nuevoEntero.num;
							if(intkey == comparar){
								encontre = true;
								break;
							}else{
								cnt++;
							}
						}

					}
					lectorInd.close();
					if(encontre){
						char buffer[totalbuffer];
						offset += totalbuffer*cnt;
						fstream finalLector(fileName,ios::in|ios::out|ios::binary);
						finalLector.seekg(offset);
						finalLector.read(buffer,totalbuffer);
						for (int i = 0; i < espejoCampos.size(); i++){
							cout<<setw(15)<<espejoCampos[i];
						}
						cout<<endl<<"--------------------------------------------------------------"<<endl;
						int progress = 0;
						for (int i = 0; i < tipocampos.size(); i++){
							if (tipocampos[i]==1){
								char chain[sizes[i]];
								memcpy(chain, buffer+progress, sizes[i]-1);
								chain[sizes[i]-1] = '\0';
								progress += sizes[i];
								cout<<setw(15)<<chain;
							
							}else if(tipocampos[i]==2){
								char car[2];
								memcpy(car,buffer+progress,sizeof(char));
								progress += sizeof(char);
								car[1] = '\0';
								cout<<setw(15)<<car;
						
							}else if(tipocampos[i]==3){
								charint elEntero;
								int entero;
								memcpy(elEntero.raw,buffer+progress,sizeof(int));
								progress += sizeof(int);
								entero = elEntero.num;
								cout<<setw(15)<<entero;

							}else if(tipocampos[i]==5){
								charfloat elFloat;
								float elFlotante;
								memcpy(elFloat.raw,buffer+progress,sizeof(float));
								progress += sizeof(float);
								elFlotante = elFloat.num;
								cout<<setw(15)<<elFlotante;
						
							}else if(tipocampos[i]==4){
								chardouble elDouble;
								double elDoble;
								memcpy(elDouble.raw,buffer+progress,sizeof(double));
								progress += sizeof(double);
								elDoble = elDouble.num;
								cout<<setw(15)<<elDoble;
							}
						}
						cout<<endl;
					
					}else{
						cout<<"Registro no encontrado"<<endl;
					}



				}else{
					cout<<"Archivo no contiene llave primaria."<<endl;
				}
			}


		}else if(opcion2==6){//modificar

			ifstream in(fileName, ios::in|ios::binary);
			tipocampos.clear();
			nombrecampos.clear();
			sizes.clear();
			char buf[sizeof(int)*3];
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));
			CantidadCampos = primeraleida.num;
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			AvailList.push_back(primerAvail.num);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			char BufferNombres[CantidadCampos*sizeof(char)*20];
			in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
			int progreso = 0;
			cout<<setw(10)<<"RRN";
			for (int i = 0; i < CantidadCampos; ++i){
				char eslabon[20];
				memcpy(eslabon,BufferNombres+progreso,19);
				eslabon[19]='\0';
				cout<<setw(15)<<eslabon;
				progreso += sizeof(char)*20;
				nombrecampos.push_back(eslabon);
				espejoCampos.push_back(eslabon);
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
			int elContador = 1;
			while(in.good()){ ///quitar el eof
				correlativo++;
				in.read(buffer,totalbuffer);
				if(in.eof()){
					break;
				}
				progress = 0;
				cout<<setw(15)<<correlativo;
				for (int i = 0; i < tipocampos.size(); i++){
					if (tipocampos[i]==1){
						char chain[sizes[i]];
						memcpy(chain, buffer+progress, sizes[i]-1);
						chain[sizes[i]-1] = '\0';
						progress += sizes[i];
						cout<<setw(15)<<chain;
						
					}else if(tipocampos[i]==2){
						char car[2];
						memcpy(car,buffer+progress,sizeof(char));
						progress += sizeof(char);
						car[1] = '\0';
						cout<<setw(15)<<car;
					
					}else if(tipocampos[i]==3){
						charint elEntero;
						int entero;
						memcpy(elEntero.raw,buffer+progress,sizeof(int));
						progress += sizeof(int);
						entero = elEntero.num;
						cout<<setw(15)<<entero;

					}else if(tipocampos[i]==5){
						charfloat elFloat;
						float elFlotante;
						memcpy(elFloat.raw,buffer+progress,sizeof(float));
						progress += sizeof(float);
						elFlotante = elFloat.num;
						cout<<setw(15)<<elFlotante;
					
					}else if(tipocampos[i]==4){
						chardouble elDouble;
						double elDoble;
						memcpy(elDouble.raw,buffer+progress,sizeof(double));
						progress += sizeof(double);
						elDoble = elDouble.num;
						cout<<setw(15)<<elDoble;
					}
				}
				cout<<endl;
				if(elContador%25 == 0){
					cout<<"Quiere continuar leyendo datos?[S/N]: ";
					char option;
					cin>>option;
					if(option=='n' || option=='N'){
						break;
					}
				}
				elContador++;
			}
			in.close();
			cout<<"1)Por Indice"<<endl<<"2)Por RRN"<<endl<<"3)Cancelar"<<endl<<"Ingrese metodo por el cual modificará:";
			int tipoModificacion;
			cin>>tipoModificacion;
			if(tipoModificacion==2){

				int indiceModificado;
				cout<<"Ingrese el RRN de el registro que desea modificar:";
				cin>>indiceModificado;
				fstream mod(fileName, ios::out|ios::in|ios::binary);
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				offset += totalbuffer*indiceModificado;
				mod.seekp(offset);

				cout<<"Ingrese los datos:"<<endl;
				for (int i = 0; i < tipocampos.size(); ++i){
					if(tipocampos[i]==1){
						cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
						char cadena[sizes[i]];
						cin>>cadena;
						mod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
						if(tipoLlave==1 && i==0){
							fstream indexMod(fileIndexName, ios::out|ios::in|ios::binary);
							indexMod.seekp(indiceModificado*20*sizeof(char));
							indexMod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(20));
							indexMod.close();
						}
					}else if(tipocampos[i]==2){
						cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
						char caracter;
						cin>>caracter;
						mod.write(reinterpret_cast<char*>(&caracter), sizeof(char));
					}else if(tipocampos[i]==3){
						cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
						int entero;
						cin>>entero;
						mod.write(reinterpret_cast<char*>(&entero), sizeof(int));
						if(tipoLlave==3 && i==0){
							fstream indexModInt(fileIndexName,ios::out|ios::in|ios::binary);
							indexModInt.seekp(indiceModificado*sizeof(int));
							indexModInt.write(reinterpret_cast<char*>(&entero), sizeof(int));
							indexModInt.close();
						}
					}else if(tipocampos[i]==5){
						cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
						float flotante;
						cin>>flotante;
						mod.write(reinterpret_cast<char*>(&flotante), sizeof(float));
					}else{
						cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
						double doble;
						cin>>doble;
						mod.write(reinterpret_cast<char*>(&doble), sizeof(double));
					}
				}

				mod.close();
				cout<<"Modificado con exito!"<<endl;
			}else if(tipoModificacion==1){
				char LlaveStr[20];
				int LlaveEntero;
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);
				if(tipoLlave==1){
					cout<<"Ingrese la llave del registro que desea modificar:";
					cin>>LlaveStr;
					string KeyLLaveStr = LlaveStr;
					fstream modifyRead(fileName,ios::in|ios::out|ios::binary);
					//fstream modifyRead(fileIndexName,ios::in|ios::out|ios::binary);
					modifyRead.seekg(offset);
					int count = 0;
					bool encontrado = false;
					while(modifyRead.good()){

						char bufferEl[totalbuffer];
						modifyRead.read(bufferEl,totalbuffer);
						if(modifyRead.eof()){
							break;
						}
						char prueba[20];
						memcpy(prueba,bufferEl,sizeof(char)*19);
						prueba[19] = '\0';
						string pruebaStr = prueba;
						if(pruebaStr == KeyLLaveStr){
							encontrado = true;
							break;
						}
						count++;

					}
					/*while(modifyRead.good()){
						char bufferEl[sizeof(char)*20];
						modifyRead.read(bufferEl,sizeof(char)*20);
						if(modifyRead.eof()){
							break;
						}
						char prueba[20];
						memcpy(prueba,bufferEl,sizeof(char)*19);
						prueba[19] = '\0';
						string pruebaStr = prueba;
						if(pruebaStr == KeyLLaveStr){
							encontrado = true;
							break;
						}
						count++;
					}*/
					modifyRead.close();
					if(encontrado){
						ifstream lector(fileName, ios::in|ios::binary);
						lector.seekg(sizeof(int));
						char buffeAvail[sizeof(int)];
						lector.read(buffeAvail,sizeof(int));
						charint lastAvail;
						memcpy(lastAvail.raw,buffeAvail,sizeof(int));
						lector.close();
						offset = 0;
						offset += sizeof(int)*3;
						offset += CantidadCampos*sizeof(char)*20;
						offset += CantidadCampos*sizeof(int);
						offset += CantidadCampos*sizeof(int);
						offset += totalbuffer*count;
						fstream mod(fileName,ios::out|ios::in|ios::binary);
						mod.seekp(offset);
						cout<<"Ingrese los datos:"<<endl;
						for (int i = 0; i < tipocampos.size(); ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
								char cadena[sizes[i]];
								cin>>cadena;
								mod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
								if(tipoLlave==1 && i==0){
									fstream indexMod(fileIndexName, ios::out|ios::in|ios::binary);
									indexMod.seekp(count*20*sizeof(char));
									indexMod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(20));
									indexMod.close();
								}
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
								char caracter;
								cin>>caracter;
								mod.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
								int entero;
								cin>>entero;
								mod.write(reinterpret_cast<char*>(&entero), sizeof(int));
								if(tipoLlave==3 && i==0){
									fstream indexModInt(fileIndexName,ios::out|ios::in|ios::binary);
									indexModInt.seekp(count*sizeof(int));
									indexModInt.write(reinterpret_cast<char*>(&entero), sizeof(int));
									indexModInt.close();
								}
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
								float flotante;
								cin>>flotante;
								mod.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
								double doble;
								cin>>doble;
								mod.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}		
						mod.close();
						cout<<"Modificado con éxito!"<<endl;
					}else{
						cout<<"Registro no encontrado"<<endl;
					}


				}else if(tipoLlave==3){

					cout<<"Ingrese la llave del registro que desea eliminar:";
					cin>>LlaveEntero;
					fstream modifyRead(fileName,ios::in|ios::out|ios::binary);
					modifyRead.seekg(offset);
					int count = 0;
					bool encontrado = false;
					while(modifyRead.good()){

						char bufferEl[totalbuffer];
						modifyRead.read(bufferEl,totalbuffer);
						if(modifyRead.eof()){
							break;
						}
						charint pruebaInt;
						memcpy(pruebaInt.raw,bufferEl,sizeof(int));
						if(pruebaInt.num == LlaveEntero){
							encontrado = true;
							break;
						}
						count++;
					}
					modifyRead.close();
					if(encontrado){
						ifstream lector(fileName, ios::in|ios::binary);
						lector.seekg(sizeof(int));
						char buffeAvail[sizeof(int)];
						lector.read(buffeAvail,sizeof(int));
						charint lastAvail;
						memcpy(lastAvail.raw,buffeAvail,sizeof(int));
						lector.close();
						offset = 0;
						offset += sizeof(int)*3;
						offset += CantidadCampos*sizeof(char)*20;
						offset += CantidadCampos*sizeof(int);
						offset += CantidadCampos*sizeof(int);
						offset += totalbuffer*count;
						fstream mod(fileName,ios::out|ios::in|ios::binary);
						mod.seekp(offset);
						cout<<"Ingrese los datos:"<<endl;
						for (int i = 0; i < tipocampos.size(); ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
								char cadena[sizes[i]];
								cin>>cadena;
								mod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
								if(tipoLlave==1 && i==0){
									fstream indexMod(fileIndexName, ios::out|ios::in|ios::binary);
									indexMod.seekp(count*20*sizeof(char));
									indexMod.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(20));
									indexMod.close();
								}
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<endl;
								char caracter;
								cin>>caracter;
								mod.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<endl;
								int entero;
								cin>>entero;
								mod.write(reinterpret_cast<char*>(&entero), sizeof(int));
								if(tipoLlave==3 && i==0){
									fstream indexModInt(fileIndexName,ios::out|ios::in|ios::binary);
									indexModInt.seekp(count*sizeof(int));
									indexModInt.write(reinterpret_cast<char*>(&entero), sizeof(int));
									indexModInt.close();
								}
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<endl;
								float flotante;
								cin>>flotante;
								mod.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<endl;
								double doble;
								cin>>doble;
								mod.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}		
						mod.close();
						cout<<"Modificado con éxito!"<<endl;
					}else{
						cout<<"Registro no encontrado"<<endl;
					}
				}//end tipoLlave=3 es decir entero
			}else{

			}
			

		}else if(opcion2==7){//Compactar

			ifstream in(fileName, ios::in|ios::binary);
			ofstream out("tmp.bin", ios::out|ios::binary);
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			char buf[sizeof(int)*3];
			in.read(buf,sizeof(int)*3);
			charint primeraleida;
			memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
			CantidadCampos = primeraleida.num;
			out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int));
			charint primerAvail;
			memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
			AvailList.push_back(primerAvail.num);
			charint primeratipoLLave;
			memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
			tipoLlave = primeratipoLLave.num;
			int tmpint = -1; //antes tenia primeravail.num pero al compactar el avail list debe volver a ser -1
			out.write(reinterpret_cast<char*>(&tmpint), sizeof(int));
			out.write(reinterpret_cast<char*>(&tipoLlave), sizeof(int));
			char BufferNombres[CantidadCampos*sizeof(char)*20];
			in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
			int progreso = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				char eslabon[20];
				memcpy(eslabon,BufferNombres+progreso,19);
				eslabon[19]='\0';
				out.write(reinterpret_cast<char*>(&eslabon), sizeof(char)*20);
				progreso += sizeof(char)*20;
				nombrecampos.push_back(eslabon);
			}	
			char BufferTipo[CantidadCampos*sizeof(int)];
			in.read(BufferTipo,CantidadCampos*sizeof(int));
			charint CI;
			progreso = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
				int tmpint2 = CI.num;
				out.write(reinterpret_cast<char*>(&tmpint2), sizeof(int));
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
				int tmpint3 = elSize.num;
				out.write(reinterpret_cast<char*>(&tmpint3), sizeof(int));
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
			char buffer[totalbuffer];
			int progress = 0;
			while(in.good()){ ///quitar el eof

				in.read(buffer,totalbuffer);
				if(in.eof()){
					break;
				}
				progress = 0;
				char verificacion[2];
				memcpy(verificacion,buffer,sizeof(char));
				verificacion[1] = '\0';
				if (verificacion[0]=='*'){
					
				}else{
					for (int i = 0; i < tipocampos.size(); i++){
						if (tipocampos[i]==1){
							char chain[sizes[i]];
							memcpy(chain, buffer+progress, sizes[i]-1);
							chain[sizes[i]-1] = '\0';
							progress += sizes[i];
							out.write(reinterpret_cast<char*>(&chain), sizeof(char)*sizes[i]);					
						}else if(tipocampos[i]==2){
							char car[2];
							memcpy(car,buffer+progress,sizeof(char));
							out.write(reinterpret_cast<char*>(&car), sizeof(char));
							progress += sizeof(char);
							car[1] = '\0';				
						}else if(tipocampos[i]==3){
							charint elEntero;
							int entero;
							memcpy(elEntero.raw,buffer+progress,sizeof(int));
							progress += sizeof(int);
							entero = elEntero.num;
							out.write(reinterpret_cast<char*>(&entero), sizeof(int));
						}else if(tipocampos[i]==5){
							charfloat elFloat;
							float elFlotante;
							memcpy(elFloat.raw,buffer+progress,sizeof(float));
							progress += sizeof(float);
							elFlotante = elFloat.num;
							out.write(reinterpret_cast<char*>(&elFlotante), sizeof(float));				
						}else if(tipocampos[i]==4){
							chardouble elDouble;
							double elDoble;
							memcpy(elDouble.raw,buffer+progress,sizeof(double));
							progress += sizeof(double);
							elDoble = elDouble.num;
							out.write(reinterpret_cast<char*>(&elDoble), sizeof(double));
						}
					}
				}
			}
			in.close();
			out.close();
			remove(fileName);
			int result = rename("tmp.bin",fileName);
			cout<<"Archivo compactado con éxito."<<endl;
		}else if(opcion2 == 8){//Salir
			break;

		}else if(opcion2 == 9){//Reindexar
			listaindicesstrings.clear();
			listaindicesINT.clear();
			ifstream in(fileName, ios::in|ios::binary); //cambiar de vuelta a registro.bin
			tipocampos.clear();
			nombrecampos.clear();
			AvailList.clear();
			sizes.clear();
			reindex(fileName);
		}else if(opcion2==10){//agregar usando índices
			while(true){
				listaindicesstrings.clear();
				listaindicesINT.clear();
				espejoCampos.clear();
				ifstream in(fileName, ios::in|ios::binary); //cambiar de vuelta a registro.bin
				ofstream out("tmp.bin",ios::out|ios::binary);
				tipocampos.clear();
				nombrecampos.clear();
				AvailList.clear();
				sizes.clear();
				char buf[sizeof(int)*3]; //antes tenia *2
				in.read(buf,sizeof(int)*3);
				charint primeraleida;
				memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
				CantidadCampos = primeraleida.num;
				out.write(reinterpret_cast<char*>(&CantidadCampos),sizeof(int));
				charint primerAvail;
				memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
				int av2 = -1; //antes tenia primerAvail.num pero esto esta compactando al mismo tiempo por ende avail list = -1
				AvailList.push_back(av2);
				out.write(reinterpret_cast<char*>(&av2),sizeof(int));
				charint primeratipoLLave;
				memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
				tipoLlave = primeratipoLLave.num;
				out.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
				char BufferNombres[CantidadCampos*sizeof(char)*20];
				in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
				int progreso = 0;
				for (int i = 0; i < CantidadCampos; ++i){
					char eslabon[20];
					memcpy(eslabon,BufferNombres+progreso,19);
					eslabon[19]='\0';
					out.write(reinterpret_cast<char*>(&eslabon),sizeof(char)*20);
					progreso += sizeof(char)*20;
					nombrecampos.push_back(eslabon);
					espejoCampos.push_back(eslabon);
				}	
				char BufferTipo[CantidadCampos*sizeof(int)];
				in.read(BufferTipo,CantidadCampos*sizeof(int));
				charint CI;
				progreso = 0;
				for (int i = 0; i < CantidadCampos; ++i){
					memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
					tipocampos.push_back(CI.num);
					int yay = CI.num;
					out.write(reinterpret_cast<char*>(&yay),sizeof(int));
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
					int losSize = elSize.num;
					out.write(reinterpret_cast<char*>(&losSize),sizeof(int));
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
				in.close();
				int offset = 0;
				offset += sizeof(int)*3;
				offset += CantidadCampos*sizeof(char)*20;
				offset += CantidadCampos*sizeof(int);
				offset += CantidadCampos*sizeof(int);

				fstream inRRN(fileName, ios::in|ios::binary);
				inRRN.seekg(offset);
				char buffer[totalbuffer];
				int contadorRRN = 0;
				vector<int> keysArrayINT;
				vector<string> keysArrayStr;
				vector<int> rrnArray;
				while(inRRN.good()){ ///quitar el eof

					inRRN.read(buffer,totalbuffer);
					if(inRRN.eof()){
						break;
					}
					if(tipoLlave==1){
						IndString ind;
						ind.rrn = contadorRRN;
						memcpy(ind.key,buffer,sizeof(char)*19);
						ind.key[19] = '\0';
						string theKeyStr = ind.key;
						listaindicesstrings.push_back(ind);
						rrnArray.push_back(contadorRRN);
						keysArrayStr.push_back(theKeyStr);
					}else if(tipoLlave==3){
						IndNum ind2;
						ind2.rrn = contadorRRN;
						charint llavecharint;
						memcpy(llavecharint.raw,buffer,sizeof(int));
						ind2.key = llavecharint.num;
						int thekey = llavecharint.num;
						listaindicesINT.push_back(ind2);
						rrnArray.push_back(contadorRRN);
						keysArrayINT.push_back(thekey);
					}else{
						break;
					}
					contadorRRN++;
				}
				inRRN.close();
				cout<<endl;
				if(tipoLlave == 3){
					//Leer el registro nuevo
					cout<<"Ingrese el entero perteneciente a la llave "<<espejoCampos[0]<<":";
					int keykey;
					int posicionAIngresar = -1;
					cin>>keykey;
					for (int i = 0; i < listaindicesINT.size()-1; i++){
						if (keykey<keysArrayINT[0]){
							posicionAIngresar = 0;
							break;
						}else if(keykey>keysArrayINT[i] && keykey<keysArrayINT[i+1]){
							posicionAIngresar = i;
							break;
						}
					}

					ifstream inNuevo(fileName,ios::in|ios::binary);
					inNuevo.seekg(offset);
					if(posicionAIngresar == 0){
						out.write(reinterpret_cast<char*>(&keykey),sizeof(int));
						for (int i = 1; i < CantidadCampos; ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
								char cadena[sizes[i]];
								cin>>cadena;
								out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
								char caracter;
								cin>>caracter;
								out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
								int entero;
								cin>>entero;
								out.write(reinterpret_cast<char*>(&entero), sizeof(int));
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
								float flotante;
								cin>>flotante;
								out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
								double doble;
								cin>>doble;
								out.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
					}
					int progress = 0;
					for (int i = 0; i < listaindicesINT.size(); ++i)
					{
						inNuevo.read(buffer,totalbuffer);
						if(inNuevo.eof()){
							break;
						}
						progress = 0;
						char verificacion[2];
						memcpy(verificacion,buffer,sizeof(char));
						verificacion[1] = '\0';
						if (verificacion[0]=='*'){
							
						}else{
							for (int i = 0; i < tipocampos.size(); i++){
								if (tipocampos[i]==1){
									char chain[sizes[i]];
									memcpy(chain, buffer+progress, sizes[i]-1);
									chain[sizes[i]-1] = '\0';
									progress += sizes[i];
									out.write(reinterpret_cast<char*>(&chain), sizeof(char)*sizes[i]);
								
								}else if(tipocampos[i]==2){
									char car[2];
									memcpy(car,buffer+progress,sizeof(char));
									out.write(reinterpret_cast<char*>(&car), sizeof(char));
									progress += sizeof(char);
									car[1] = '\0';
							
								}else if(tipocampos[i]==3){
									charint elEntero;
									int entero;
									memcpy(elEntero.raw,buffer+progress,sizeof(int));
									progress += sizeof(int);
									entero = elEntero.num;
									out.write(reinterpret_cast<char*>(&entero), sizeof(int));

								}else if(tipocampos[i]==5){
									charfloat elFloat;
									float elFlotante;
									memcpy(elFloat.raw,buffer+progress,sizeof(float));
									progress += sizeof(float);
									elFlotante = elFloat.num;
									out.write(reinterpret_cast<char*>(&elFlotante), sizeof(float));
								}else if(tipocampos[i]==4){
									chardouble elDouble;
									double elDoble;
									memcpy(elDouble.raw,buffer+progress,sizeof(double));
									progress += sizeof(double);
									elDoble = elDouble.num;
									out.write(reinterpret_cast<char*>(&elDoble), sizeof(double));
								}
							}
						}
						if (i == posicionAIngresar && i != 0){
							out.write(reinterpret_cast<char*>(&keykey),sizeof(int));
							for (int i = 1; i < CantidadCampos; ++i){
								if(tipocampos[i]==1){
									cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
									char cadena[sizes[i]];
									cin>>cadena;
									out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
								}else if(tipocampos[i]==2){
									cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
									char caracter;
									cin>>caracter;
									out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
								}else if(tipocampos[i]==3){
									cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
									int entero;
									cin>>entero;
									out.write(reinterpret_cast<char*>(&entero), sizeof(int));
								}else if(tipocampos[i]==5){
									cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
									float flotante;
									cin>>flotante;
									out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
								}else{
									cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
									double doble;
									cin>>doble;
									out.write(reinterpret_cast<char*>(&doble), sizeof(double));
								}
							}
						}
					}//fin del for
					inNuevo.close();
					if(posicionAIngresar == -1){
						out.write(reinterpret_cast<char*>(&keykey),sizeof(int));
						for (int i = 1; i < CantidadCampos; ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
								char cadena[sizes[i]];
								cin>>cadena;
								out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
								char caracter;
								cin>>caracter;
								out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
								int entero;
								cin>>entero;
								out.write(reinterpret_cast<char*>(&entero), sizeof(int));
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
								float flotante;
								cin>>flotante;
								out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
								double doble;
								cin>>doble;
								out.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
						out.close();
					}else{
						out.close();
					}
					remove(fileName);
					int result = rename("tmp.bin",fileName);
					cout<<"Registro agregado con éxito!"<<endl;


				}else if(tipoLlave==1){//si la llave es string

					cout<<"Ingrese la cadena perteneciente a la llave "<<espejoCampos[0]<<":";
					string keykeyStr;
					int posicionAIngresar = -1;
					cin>>keykeyStr;
					for (int i = 0; i < listaindicesstrings.size()-1; i++){
						if (keykeyStr.compare(keysArrayStr[0])<0){
							posicionAIngresar = 0;
							break;
						}else if(keykeyStr.compare(keysArrayStr[i])>0 && keykeyStr.compare(keysArrayStr[i+1])<0){
							posicionAIngresar = i;
							break;
						}
					}
					char theKeyAlBin[20];
					strcpy(theKeyAlBin,keykeyStr.c_str());
					ifstream inNuevo(fileName,ios::in|ios::binary);
					inNuevo.seekg(offset);
					if(posicionAIngresar == 0){
						out.write(reinterpret_cast<char*>(&theKeyAlBin),sizeof(char)*20);
						for (int i = 1; i < CantidadCampos; ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
								char cadena[sizes[i]];
								cin>>cadena;
								out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
								char caracter;
								cin>>caracter;
								out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
								int entero;
								cin>>entero;
								out.write(reinterpret_cast<char*>(&entero), sizeof(int));
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
								float flotante;
								cin>>flotante;
								out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
								double doble;
								cin>>doble;
								out.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
					}
					int progress = 0;
					for (int i = 0; i < listaindicesstrings.size(); ++i)
					{
						inNuevo.read(buffer,totalbuffer);
						if(inNuevo.eof()){
							break;
						}
						progress = 0;
						char verificacion[2];
						memcpy(verificacion,buffer,sizeof(char));
						verificacion[1] = '\0';
						if (verificacion[0]=='*'){
							
						}else{
							for (int i = 0; i < tipocampos.size(); i++){
								if (tipocampos[i]==1){
									char chain[sizes[i]];
									memcpy(chain, buffer+progress, sizes[i]-1);
									chain[sizes[i]-1] = '\0';
									progress += sizes[i];
									out.write(reinterpret_cast<char*>(&chain), sizeof(char)*sizes[i]);
								
								}else if(tipocampos[i]==2){
									char car[2];
									memcpy(car,buffer+progress,sizeof(char));
									out.write(reinterpret_cast<char*>(&car), sizeof(char));
									progress += sizeof(char);
									car[1] = '\0';
							
								}else if(tipocampos[i]==3){
									charint elEntero;
									int entero;
									memcpy(elEntero.raw,buffer+progress,sizeof(int));
									progress += sizeof(int);
									entero = elEntero.num;
									out.write(reinterpret_cast<char*>(&entero), sizeof(int));

								}else if(tipocampos[i]==5){
									charfloat elFloat;
									float elFlotante;
									memcpy(elFloat.raw,buffer+progress,sizeof(float));
									progress += sizeof(float);
									elFlotante = elFloat.num;
									out.write(reinterpret_cast<char*>(&elFlotante), sizeof(float));
								}else if(tipocampos[i]==4){
									chardouble elDouble;
									double elDoble;
									memcpy(elDouble.raw,buffer+progress,sizeof(double));
									progress += sizeof(double);
									elDoble = elDouble.num;
									out.write(reinterpret_cast<char*>(&elDoble), sizeof(double));
								}
							}
						}
						if (i == posicionAIngresar && i != 0){
							out.write(reinterpret_cast<char*>(&theKeyAlBin),sizeof(char)*20);
							for (int i = 1; i < CantidadCampos; ++i){
								if(tipocampos[i]==1){
									cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
									char cadena[sizes[i]];
									cin>>cadena;
									out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
								}else if(tipocampos[i]==2){
									cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
									char caracter;
									cin>>caracter;
									out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
								}else if(tipocampos[i]==3){
									cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
									int entero;
									cin>>entero;
									out.write(reinterpret_cast<char*>(&entero), sizeof(int));
								}else if(tipocampos[i]==5){
									cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
									float flotante;
									cin>>flotante;
									out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
								}else{
									cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
									double doble;
									cin>>doble;
									out.write(reinterpret_cast<char*>(&doble), sizeof(double));
								}
							}
						}
					}//fin del for
					inNuevo.close();
					if(posicionAIngresar == -1){
						out.write(reinterpret_cast<char*>(&theKeyAlBin),sizeof(char)*20);
						for (int i = 1; i < CantidadCampos; ++i){
							if(tipocampos[i]==1){
								cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<":";
								char cadena[sizes[i]];
								cin>>cadena;
								out.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
							}else if(tipocampos[i]==2){
								cout<<"Ingrese el caracter perteneciente al campo "<<espejoCampos[i]<<":";
								char caracter;
								cin>>caracter;
								out.write(reinterpret_cast<char*>(&caracter), sizeof(char));
							}else if(tipocampos[i]==3){
								cout<<"Ingrese el entero perteneciente al campo "<<espejoCampos[i]<<":";
								int entero;
								cin>>entero;
								out.write(reinterpret_cast<char*>(&entero), sizeof(int));
							}else if(tipocampos[i]==5){
								cout<<"Ingrese el float perteneciente al campo "<<espejoCampos[i]<<":";
								float flotante;
								cin>>flotante;
								out.write(reinterpret_cast<char*>(&flotante), sizeof(float));
							}else{
								cout<<"Ingrese el double perteneciente al campo "<<espejoCampos[i]<<":";
								double doble;
								cin>>doble;
								out.write(reinterpret_cast<char*>(&doble), sizeof(double));
							}
						}
						out.close();
					}else{
						out.close();
					}

					remove(fileName);
					int result = rename("tmp.bin",fileName);
					cout<<"Registro agregado con éxito!"<<endl<<"Desea agregar un nuevo registro[S/N]:";
					char respuesta;
					cin>>respuesta;
					if(respuesta=='s' || respuesta=='S'){

					}else{
						break;
					}


				}else{//end if key instance of string
					cout<<"Este registro no contiene llave, utilice la opcion 3 para agregar a este archivo"<<endl;
					break;
				}
			}
		}else if(opcion2==0){//end else if 10
			while(true){
				cout<<"Ingrese el nombre del archivo con el que trabajará:";
				cin>>fileName;
				stringstream arch;
				stringstream archind;
				arch<<fileName<<".bin";
				arch>>fileName;
				archind<<fileName<<".index";
				archind>>fileIndexName;
				if( access(fileName, F_OK) != -1){				
					break;
				}else{

				}
			}
			
		}else if(opcion2==11){//cruzar

			
			cout<<"1)Sin indice"<<endl<<"2)Con indice"<<endl<<"Ingrese tipo de cruzamiento:";
			int opcionCruz;
			cin>>opcionCruz;
			charint cantindadCamposPrimero;
			charint cantidadCamposSegundo;
			charint tipoKeyPrim;
			charint tipoKeySecu;
			vector<int> camposUsadosPrimero;
			vector<int> tiposPrimero;
			vector<int> tiposSegundo;
			vector<int> camposUsadosSegundo;
			vector<int> sizesPrimero;
			vector<int> sizesSegundo;
			int rrn;
			string espejoName;
			if(opcionCruz==1){
				char archivo1[20];
				char archivo2[20];
				stringstream first, second;
				cout<<"Ingrese el nombre del primer archivo:";
				cin>>archivo1;
				cout<<"Ingrese el nombre del segundo archivo:";
				cin>>archivo2;
				first<<archivo1<<".bin";
				second<<archivo2<<".bin";
				first>>archivo1;
				second>>archivo2;
				cout<<"Ingrese el nombre del archivo nuevo:";
				char nuevoArchivo[30];
				cin>>nuevoArchivo;
				stringstream strstrm;
				strstrm<<nuevoArchivo<<".bin";
				strstrm>>nuevoArchivo;
				ifstream lectorPrim(archivo1, ios::in|ios::binary);
				char buffer[sizeof(int)*3];
				lectorPrim.read(buffer, sizeof(int)*3);
				memcpy(cantindadCamposPrimero.raw,buffer,sizeof(int));
				char bufferNames[20];
				vector<char*> nombreCamposPrim;
				vector<string> espejosPrim;
				vector<char*> nombreCamposSecu;
				vector<string> espejosSecu;
				cout<<"Campos del primer archivo:"<<endl;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(bufferNames,sizeof(char)*20);
					espejoName = bufferNames;
					nombreCamposPrim.push_back(bufferNames);
					espejosPrim.push_back(bufferNames);
					cout<<i<<")"<<espejoName<<endl;
				}
				cout<<"Ingrese el numero de los campos que desea utilizar (-1 para salir):"<<endl;
				while(true){
					cin>>rrn;
					if(rrn < 0){
						break;
					}else if(rrn < cantindadCamposPrimero.num){
						camposUsadosPrimero.push_back(rrn);
					}
				}
				ifstream lectorSecu(archivo2, ios::in|ios::binary);
				lectorSecu.read(buffer, sizeof(int)*3);
				memcpy(cantidadCamposSegundo.raw,buffer,sizeof(int));
				cout<<"Campos del segundo archivo:"<<endl;
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(bufferNames,sizeof(char)*20);
					espejoName = bufferNames;
					nombreCamposSecu.push_back(bufferNames);
					espejosSecu.push_back(bufferNames);
					cout<<i<<")"<<espejoName<<endl;
				}
				cout<<"Ingrese el numero de los campos que desea utilizar (-1 para salir):"<<endl;
				while(true){
					cin>>rrn;
					if(rrn < 0){
						break;
					}else if(rrn < cantidadCamposSegundo.num){
						camposUsadosSegundo.push_back(rrn);
					}
				}
				char buffInt[sizeof(int)];
				charint numeroUniversal;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					tiposPrimero.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					tiposSegundo.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					sizesPrimero.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					sizesSegundo.push_back(numeroUniversal.num);
				}
				int totalbufferPrim = 0;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					if(tiposPrimero[i]==1){
						totalbufferPrim += sizesPrimero[i];
					}else if(tiposPrimero[i]==2){
						totalbufferPrim += sizeof(char);
					}else if(tiposPrimero[i]==3){
						totalbufferPrim += sizeof(int);
					}else if(tiposPrimero[i]==4){
						totalbufferPrim += sizeof(double);
					}else if(tiposPrimero[i]==5){
						totalbufferPrim += sizeof(float);
					}else{
						cout<<"Hubo clavo"<<endl;
					}
				}
				int totalbufferSecu = 0;
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					if(tiposSegundo[i]==1){
						totalbufferSecu += sizesSegundo[i];
					}else if(tiposSegundo[i]==2){
						totalbufferSecu += sizeof(char);
					}else if(tiposSegundo[i]==3){
						totalbufferSecu += sizeof(int);
					}else if(tiposSegundo[i]==4){
						totalbufferSecu += sizeof(double);
					}else if(tiposSegundo[i]==5){
						totalbufferSecu += sizeof(float);
					}else{
						cout<<"Hubo clavo"<<endl;
					}
				}
				int CantidadCampos = camposUsadosPrimero.size()+camposUsadosSegundo.size();
				int menosuno = -1;
				int cero = 0;
				fstream out(nuevoArchivo, ios::out|ios::binary);
				out.write(reinterpret_cast<char*>(&CantidadCampos),sizeof(int));
				out.write(reinterpret_cast<char*>(&menosuno),sizeof(int));
				out.write(reinterpret_cast<char*>(&cero),sizeof(int));
				stringstream theName;
				
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					string theFirst = espejosPrim[camposUsadosPrimero[i]];
					char nuevoNombre[20];
					strcpy(nuevoNombre,theFirst.c_str());
					out.write(reinterpret_cast<char*>(&nuevoNombre),sizeof(char)*20);
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					string theSecond = espejosSecu[camposUsadosSegundo[i]];
					char nuevoNombre2[20];
					strcpy(nuevoNombre2,theSecond.c_str());
					out.write(reinterpret_cast<char*>(&nuevoNombre2),sizeof(char)*20);
				}
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					out.write(reinterpret_cast<char*>(&tiposPrimero[camposUsadosPrimero[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					out.write(reinterpret_cast<char*>(&tiposSegundo[camposUsadosSegundo[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					out.write(reinterpret_cast<char*>(&sizesPrimero[camposUsadosPrimero[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					out.write(reinterpret_cast<char*>(&sizesSegundo[camposUsadosSegundo[i]]),sizeof(int));
				}
				char bufferPrim[totalbufferPrim];
				char bufferSecu[totalbufferSecu];
				vector<int> offPrim;
				vector<int> offSecu;
				int number = 0;
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					number = 0;
					for (int j = 0; j < camposUsadosPrimero[i]; j++){
						if(tiposPrimero[j]==1){
							number += sizesPrimero[j];
						}else if(tiposPrimero[j]==2){
							number += sizeof(char);
						}else if(tiposPrimero[j]==3){
							number += sizeof(int);
						}else if(tiposPrimero[j]==4){
							number += sizeof(double);
						}else if(tiposPrimero[j]==5){
							number += sizeof(float);
						}else{
							cout<<"Hubo clavo"<<endl;
						}
					}
					offPrim.push_back(number);
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					number = 0;
					for (int j = 0; j < camposUsadosSegundo[i]; j++){
						if(tiposSegundo[j]==1){
							number += sizesSegundo[j];
						}else if(tiposSegundo[j]==2){
							number += sizeof(char);
						}else if(tiposSegundo[j]==3){
							number += sizeof(int);
						}else if(tiposSegundo[j]==4){
							number += sizeof(double);
						}else if(tiposSegundo[j]==5){
							number += sizeof(float);
						}else{
							cout<<"Hubo clavo"<<endl;
						}
					}
					offSecu.push_back(number);
				}
				while(lectorPrim.good() && lectorSecu.good()){
					lectorPrim.read(bufferPrim,totalbufferPrim);
					lectorSecu.read(bufferSecu,totalbufferSecu);
					if(lectorPrim.eof()){
						break;
					}
					if(lectorSecu.eof()){
						break;
					}
					for (int i = 0; i < camposUsadosPrimero.size(); i++){
						if(tiposPrimero[camposUsadosPrimero[i]]==1){
							char newStr[sizesPrimero[camposUsadosPrimero[i]]];
							memcpy(newStr,bufferPrim+offPrim[i],sizeof(char)*(sizesPrimero[camposUsadosPrimero[i]]-1));
							newStr[sizesPrimero[camposUsadosPrimero[i]]-1] = '\0';
							out.write(reinterpret_cast<char*>(&newStr),sizeof(char)*sizesPrimero[camposUsadosPrimero[i]]);
						}else if(tiposPrimero[camposUsadosPrimero[i]]==2){
							char newchar[2];
							memcpy(newchar,bufferPrim+offPrim[i],sizeof(char));
							newchar[1] = '\0';
							out.write(reinterpret_cast<char*>(&newchar),sizeof(char));
						}else if(tiposPrimero[camposUsadosPrimero[i]]==3){
							charint nuevoInt;
							memcpy(nuevoInt.raw,bufferPrim+offPrim[i],sizeof(int));
							out.write(reinterpret_cast<char*>(&nuevoInt.num),sizeof(int));
						}else if(tiposPrimero[camposUsadosPrimero[i]]==4){
							chardouble nuevoDouble;
							memcpy(nuevoDouble.raw,bufferPrim+offPrim[i],sizeof(double));
							out.write(reinterpret_cast<char*>(&nuevoDouble.num),sizeof(double));
						}else if(tiposPrimero[camposUsadosPrimero[i]]==5){
							charfloat nuevoFloat;
							memcpy(nuevoFloat.raw,bufferPrim+offPrim[i],sizeof(float));
							out.write(reinterpret_cast<char*>(&nuevoFloat.num),sizeof(float));
						}
					}
					for (int i = 0; i < camposUsadosSegundo.size(); i++){
						if(tiposSegundo[camposUsadosSegundo[i]]==1){
							char newStr1[sizesSegundo[camposUsadosSegundo[i]]];
							memcpy(newStr1,bufferSecu+offSecu[i],sizeof(char)*(sizesSegundo[camposUsadosSegundo[i]]-1));
							newStr1[sizesSegundo[camposUsadosSegundo[i]]-1] = '\0';
							out.write(reinterpret_cast<char*>(&newStr1),sizeof(char)*sizesSegundo[camposUsadosSegundo[i]]);
						}else if(tiposSegundo[camposUsadosSegundo[i]]==2){
							char newchar1[2];
							memcpy(newchar1,bufferSecu+offSecu[i],sizeof(char));
							newchar1[1] = '\0';
							out.write(reinterpret_cast<char*>(&newchar1),sizeof(char));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==3){
							charint nuevoInt1;
							memcpy(nuevoInt1.raw,bufferSecu+offSecu[i],sizeof(int));
							out.write(reinterpret_cast<char*>(&nuevoInt1.num),sizeof(int));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==4){
							chardouble nuevoDouble1;
							memcpy(nuevoDouble1.raw,bufferSecu+offSecu[i],sizeof(double));
							out.write(reinterpret_cast<char*>(&nuevoDouble1.num),sizeof(double));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==5){
							charfloat nuevoFloat1;
							memcpy(nuevoFloat1.raw,bufferSecu+offSecu[i],sizeof(float));
							out.write(reinterpret_cast<char*>(&nuevoFloat1.num),sizeof(float));
						}
					}

				}
				out.close();
				lectorPrim.close();
				lectorSecu.close();
				cout<<"Archivos cruzados con éxito!"<<endl;
			}else if(opcionCruz==2){
					char archivo1[20];
					char archivo2[20];
				while(true){	
					char tmpBuff[sizeof(int)*3];
					stringstream first, second;
					cout<<"Ingrese el nombre del primer archivo:";
					cin>>archivo1;
					cout<<"Ingrese el nombre del segundo archivo:";
					cin>>archivo2;
					first<<archivo1<<".bin";
					second<<archivo2<<".bin";
					first>>archivo1;
					second>>archivo2;
					ifstream readerPrim(archivo1, ios::in|ios::binary);
					readerPrim.read(tmpBuff,sizeof(int)*3);
					memcpy(tipoKeyPrim.raw,tmpBuff+sizeof(int)*2,sizeof(int));
					readerPrim.close();
					ifstream readerSecu(archivo2, ios::in|ios::binary);
					readerSecu.read(tmpBuff,sizeof(int)*3);
					memcpy(tipoKeySecu.raw,tmpBuff+sizeof(int)*2,sizeof(int));
					readerSecu.close();
					if((tipoKeyPrim.num ==1 || tipoKeyPrim.num==3) && (tipoKeySecu.num ==1 || tipoKeySecu.num ==3)){
						cout<<"1)Primero"<<endl<<"2)Segundo"<<endl<<"Ingrese el archivo cuya llave quiere utilizar:";
						int numberArchive;
						cin>>numberArchive;
						if(numberArchive==2){
							char temp[20];
							strcpy(temp,archivo1);
							strcpy(archivo1,archivo2);
							strcpy(archivo2,temp);	
						}
						camposUsadosPrimero.push_back(0);
						break;
					}
				}
				
				cout<<"Ingrese el nombre del archivo nuevo:";
				char nuevoArchivo[30];
				cin>>nuevoArchivo;
				stringstream strstrm;
				strstrm<<nuevoArchivo<<".bin";
				strstrm>>nuevoArchivo;
				ifstream lectorPrim(archivo1, ios::in|ios::binary);
				char buffer[sizeof(int)*3];
				lectorPrim.read(buffer, sizeof(int)*3);
				memcpy(cantindadCamposPrimero.raw,buffer,sizeof(int));
				char bufferNames[20];
				vector<char*> nombreCamposPrim;
				vector<string> espejosPrim;
				vector<char*> nombreCamposSecu;
				vector<string> espejosSecu;
				cout<<"Campos del primer archivo:"<<endl;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(bufferNames,sizeof(char)*20);
					espejoName = bufferNames;
					nombreCamposPrim.push_back(bufferNames);
					espejosPrim.push_back(bufferNames);
					cout<<i<<")"<<espejoName<<endl;
				}
				cout<<"Ingrese el numero de los campos que desea utilizar (-1 para salir):"<<endl;
				while(true){
					cin>>rrn;
					if(rrn < 0){
						break;
					}else if(rrn < cantindadCamposPrimero.num && rrn != 0){
						camposUsadosPrimero.push_back(rrn);
					}else if(rrn == 0){

					}
				}
				ifstream lectorSecu(archivo2, ios::in|ios::binary);
				lectorSecu.read(buffer, sizeof(int)*3);
				memcpy(cantidadCamposSegundo.raw,buffer,sizeof(int));
				cout<<"Campos del segundo archivo:"<<endl;
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(bufferNames,sizeof(char)*20);
					espejoName = bufferNames;
					nombreCamposSecu.push_back(bufferNames);
					espejosSecu.push_back(bufferNames);
					cout<<i<<")"<<espejoName<<endl;
				}
				cout<<"Ingrese el numero de los campos que desea utilizar (-1 para salir):"<<endl;
				while(true){
					cin>>rrn;
					if(rrn < 0){
						break;
					}else if(rrn < cantidadCamposSegundo.num){
						camposUsadosSegundo.push_back(rrn);
					}
				}
				char buffInt[sizeof(int)];
				charint numeroUniversal;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					tiposPrimero.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					tiposSegundo.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					lectorPrim.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					sizesPrimero.push_back(numeroUniversal.num);
				}
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					lectorSecu.read(buffInt,sizeof(int));
					memcpy(numeroUniversal.raw,buffInt,sizeof(int));
					sizesSegundo.push_back(numeroUniversal.num);
				}
				int totalbufferPrim = 0;
				for (int i = 0; i < cantindadCamposPrimero.num; i++){
					if(tiposPrimero[i]==1){
						totalbufferPrim += sizesPrimero[i];
					}else if(tiposPrimero[i]==2){
						totalbufferPrim += sizeof(char);
					}else if(tiposPrimero[i]==3){
						totalbufferPrim += sizeof(int);
					}else if(tiposPrimero[i]==4){
						totalbufferPrim += sizeof(double);
					}else if(tiposPrimero[i]==5){
						totalbufferPrim += sizeof(float);
					}else{
						cout<<"Hubo clavo"<<endl;
					}
				}
				int totalbufferSecu = 0;
				for (int i = 0; i < cantidadCamposSegundo.num; i++){
					if(tiposSegundo[i]==1){
						totalbufferSecu += sizesSegundo[i];
					}else if(tiposSegundo[i]==2){
						totalbufferSecu += sizeof(char);
					}else if(tiposSegundo[i]==3){
						totalbufferSecu += sizeof(int);
					}else if(tiposSegundo[i]==4){
						totalbufferSecu += sizeof(double);
					}else if(tiposSegundo[i]==5){
						totalbufferSecu += sizeof(float);
					}else{
						cout<<"Hubo clavo"<<endl;
					}
				}
				int CantidadCampos = camposUsadosPrimero.size()+camposUsadosSegundo.size();
				int menosuno = -1;
				int tipoKey = tiposPrimero[0];
				fstream out(nuevoArchivo, ios::out|ios::binary);
				out.write(reinterpret_cast<char*>(&CantidadCampos),sizeof(int));
				out.write(reinterpret_cast<char*>(&menosuno),sizeof(int));
				out.write(reinterpret_cast<char*>(&tipoKey),sizeof(int));
				stringstream theName;
				
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					string theFirst = espejosPrim[camposUsadosPrimero[i]];
					char nuevoNombre[20];
					strcpy(nuevoNombre,theFirst.c_str());
					out.write(reinterpret_cast<char*>(&nuevoNombre),sizeof(char)*20);
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					string theSecond = espejosSecu[camposUsadosSegundo[i]];
					char nuevoNombre2[20];
					strcpy(nuevoNombre2,theSecond.c_str());
					out.write(reinterpret_cast<char*>(&nuevoNombre2),sizeof(char)*20);
				}
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					out.write(reinterpret_cast<char*>(&tiposPrimero[camposUsadosPrimero[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					out.write(reinterpret_cast<char*>(&tiposSegundo[camposUsadosSegundo[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					out.write(reinterpret_cast<char*>(&sizesPrimero[camposUsadosPrimero[i]]),sizeof(int));
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					out.write(reinterpret_cast<char*>(&sizesSegundo[camposUsadosSegundo[i]]),sizeof(int));
				}
				char bufferPrim[totalbufferPrim];
				char bufferSecu[totalbufferSecu];
				vector<int> offPrim;
				vector<int> offSecu;
				int number = 0;
				for (int i = 0; i < camposUsadosPrimero.size(); i++){
					number = 0;
					for (int j = 0; j < camposUsadosPrimero[i]; j++){
						if(tiposPrimero[j]==1){
							number += sizesPrimero[j];
						}else if(tiposPrimero[j]==2){
							number += sizeof(char);
						}else if(tiposPrimero[j]==3){
							number += sizeof(int);
						}else if(tiposPrimero[j]==4){
							number += sizeof(double);
						}else if(tiposPrimero[j]==5){
							number += sizeof(float);
						}else{
							cout<<"Hubo clavo"<<endl;
						}
					}
					offPrim.push_back(number);
				}
				for (int i = 0; i < camposUsadosSegundo.size(); i++){
					number = 0;
					for (int j = 0; j < camposUsadosSegundo[i]; j++){
						if(tiposSegundo[j]==1){
							number += sizesSegundo[j];
						}else if(tiposSegundo[j]==2){
							number += sizeof(char);
						}else if(tiposSegundo[j]==3){
							number += sizeof(int);
						}else if(tiposSegundo[j]==4){
							number += sizeof(double);
						}else if(tiposSegundo[j]==5){
							number += sizeof(float);
						}else{
							cout<<"Hubo clavo"<<endl;
						}
					}
					offSecu.push_back(number);
				}
				stringstream newInd;
				newInd<<nuevoArchivo<<".index";
				newInd>>nuevoArchivo;
				ofstream outInd(nuevoArchivo, ios::out|ios::binary);
				while(lectorPrim.good() && lectorSecu.good()){
					lectorPrim.read(bufferPrim,totalbufferPrim);
					lectorSecu.read(bufferSecu,totalbufferSecu);
					if(lectorPrim.eof()){
						break;
					}
					if(lectorSecu.eof()){
						break;
					}
					
					for (int i = 0; i < camposUsadosPrimero.size(); i++){
						if(tiposPrimero[camposUsadosPrimero[i]]==1){
							char newStr[sizesPrimero[camposUsadosPrimero[i]]];
							memcpy(newStr,bufferPrim+offPrim[i],sizeof(char)*(sizesPrimero[camposUsadosPrimero[i]]-1));
							newStr[sizesPrimero[camposUsadosPrimero[i]]-1] = '\0';
							out.write(reinterpret_cast<char*>(&newStr),sizeof(char)*sizesPrimero[camposUsadosPrimero[i]]);
							if(i==0 && tipoKey==1){
								outInd.write(reinterpret_cast<char*>(&newStr),sizeof(char)*sizesPrimero[camposUsadosPrimero[i]]);
							}
						}else if(tiposPrimero[camposUsadosPrimero[i]]==2){
							char newchar[2];
							memcpy(newchar,bufferPrim+offPrim[i],sizeof(char));
							newchar[1] = '\0';
							out.write(reinterpret_cast<char*>(&newchar),sizeof(char));
						}else if(tiposPrimero[camposUsadosPrimero[i]]==3){
							charint nuevoInt;
							memcpy(nuevoInt.raw,bufferPrim+offPrim[i],sizeof(int));
							out.write(reinterpret_cast<char*>(&nuevoInt.num),sizeof(int));
							if(i==0 && tipoKey==3){
								outInd.write(reinterpret_cast<char*>(&nuevoInt.num),sizeof(int));
							}
						}else if(tiposPrimero[camposUsadosPrimero[i]]==4){
							chardouble nuevoDouble;
							memcpy(nuevoDouble.raw,bufferPrim+offPrim[i],sizeof(double));
							out.write(reinterpret_cast<char*>(&nuevoDouble.num),sizeof(double));
						}else if(tiposPrimero[camposUsadosPrimero[i]]==5){
							charfloat nuevoFloat;
							memcpy(nuevoFloat.raw,bufferPrim+offPrim[i],sizeof(float));
							out.write(reinterpret_cast<char*>(&nuevoFloat.num),sizeof(float));
						}
					}
					for (int i = 0; i < camposUsadosSegundo.size(); i++){
						if(tiposSegundo[camposUsadosSegundo[i]]==1){
							char newStr1[sizesSegundo[camposUsadosSegundo[i]]];
							memcpy(newStr1,bufferSecu+offSecu[i],sizeof(char)*(sizesSegundo[camposUsadosSegundo[i]]-1));
							newStr1[sizesSegundo[camposUsadosSegundo[i]]-1] = '\0';
							out.write(reinterpret_cast<char*>(&newStr1),sizeof(char)*sizesSegundo[camposUsadosSegundo[i]]);
						}else if(tiposSegundo[camposUsadosSegundo[i]]==2){
							char newchar1[2];
							memcpy(newchar1,bufferSecu+offSecu[i],sizeof(char));
							newchar1[1] = '\0';
							out.write(reinterpret_cast<char*>(&newchar1),sizeof(char));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==3){
							charint nuevoInt1;
							memcpy(nuevoInt1.raw,bufferSecu+offSecu[i],sizeof(int));
							out.write(reinterpret_cast<char*>(&nuevoInt1.num),sizeof(int));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==4){
							chardouble nuevoDouble1;
							memcpy(nuevoDouble1.raw,bufferSecu+offSecu[i],sizeof(double));
							out.write(reinterpret_cast<char*>(&nuevoDouble1.num),sizeof(double));
						}else if(tiposSegundo[camposUsadosSegundo[i]]==5){
							charfloat nuevoFloat1;
							memcpy(nuevoFloat1.raw,bufferSecu+offSecu[i],sizeof(float));
							out.write(reinterpret_cast<char*>(&nuevoFloat1.num),sizeof(float));
						}
					}


				}
				outInd.close();
				out.close();
				lectorPrim.close();
				lectorSecu.close();
				cout<<"Archivos cruzados con éxito!"<<endl;

			}else{
				cout<<"Opcion no valida!"<<endl;
			}




		}//end cruzar


	}//end while
	

	return 0;
}

void reindex(char fileName[20]){
	vector<int> tipocampos;
	vector<IndString> listaindicesstrings;
	vector<IndNum> listaindicesINT;
	vector<char*> nombrecampos;
	vector<string> espejoCampos;
	vector<int> sizes;
	vector<int> AvailList;
	vector<int> listaIntKeys;
	vector<string> listaStrKeys;
	int opcion;
	int tamano;
	int CantidadCampos;
	char namekey[20];		
	string namekeyespejo;
	char nombre[20];
	int opcion2;
	int tipoLlave;
	listaindicesstrings.clear();
	listaindicesINT.clear();
	ifstream in(fileName, ios::in|ios::binary); //cambiar de vuelta a registro.bin
	tipocampos.clear();
	nombrecampos.clear();
	AvailList.clear();
	sizes.clear();
	char buf[sizeof(int)*3]; //antes tenia *2
	in.read(buf,sizeof(int)*3);
	charint primeraleida;
	memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
	CantidadCampos = primeraleida.num;
	charint primerAvail;
	memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
	AvailList.push_back(primerAvail.num);
	charint primeratipoLLave;
	memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
	tipoLlave = primeratipoLLave.num;
	char BufferNombres[CantidadCampos*sizeof(char)*20];
	in.read(BufferNombres,CantidadCampos*sizeof(char)*20);
	int progreso = 0;
	for (int i = 0; i < CantidadCampos; ++i){
		char eslabon[20];
		memcpy(eslabon,BufferNombres+progreso,19);
		eslabon[19]='\0';
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
	in.close();
	int offset = 0;
	offset += sizeof(int)*3;
	offset += CantidadCampos*sizeof(char)*20;
	offset += CantidadCampos*sizeof(int);
	offset += CantidadCampos*sizeof(int);
	fstream inRRN(fileName, ios::in|ios::binary);
	inRRN.seekg(offset);
	char buffer[totalbuffer];
	int contadorRRN = 0;
	while(inRRN.good()){ ///quitar el eof

		inRRN.read(buffer,totalbuffer);
		if(inRRN.eof()){
			break;
		}
		if(tipoLlave==1){
			IndString ind;
			ind.rrn = contadorRRN;
			char verificacion[2];
			memcpy(verificacion,buffer,sizeof(char));
			if(verificacion[0]=='*'){//////si no funciona quitar esta verificacion
				//quite la reducción del contador porque es el offset, y lo ocupo intacto.
			}else{
				memcpy(ind.key,buffer,sizeof(char)*19);
				ind.key[19] = '\0';
				listaindicesstrings.push_back(ind);
			}	

		}else if(tipoLlave==3){
			IndNum ind2;
			ind2.rrn = contadorRRN;
			charint llavecharint;
			char verificacion2[2];
			memcpy(verificacion2,buffer,sizeof(char));
			if(verificacion2[0]=='*'){

			}else{
				memcpy(llavecharint.raw,buffer,sizeof(int));
				ind2.key = llavecharint.num;
				listaindicesINT.push_back(ind2);
			}
			
		}else{
			break;
		}
		contadorRRN++;
	}
	inRRN.close();
	if(tipoLlave == 3){
		int keysArray[listaindicesINT.size()];
		int rrnArray[listaindicesINT.size()];
		for (int i = 0; i < listaindicesINT.size(); ++i){
			//cout<<listaindicesINT[i].key<<" ";
			keysArray[i] = listaindicesINT[i].key;
			rrnArray[i] = listaindicesINT[i].rrn;
			//cout<<keysArray[i]<<":"<<rrnArray[i]<<" ";
		}
		///////////////////////////////////////////////////////////////////////
		quicksort(keysArray,0,listaindicesINT.size()-1, rrnArray);

		///////////////////////////////////////////////////////////////////////
		int hasta = listaindicesINT.size();
		listaindicesINT.clear();
		for (int i = 0; i < hasta; ++i){
			IndNum ind;
			ind.rrn = rrnArray[i];
			ind.key = keysArray[i];
			listaindicesINT.push_back(ind);
		}
		cout<<endl;
		stringstream ss;
		ss<<fileName<<".index";
		char nombreIndices[26];
		ss>>nombreIndices;
		fstream out(nombreIndices, ios::out|ios::binary);
		for (int i = 0; i < listaindicesINT.size(); ++i){
			int numerito, numerote;
			numerito = rrnArray[i];
			numerote = keysArray[i];
			out.write(reinterpret_cast<char*>(&numerito),sizeof(int));
		}
		out.close();
		ifstream in2(fileName,ios::in|ios::binary);
		ofstream out2("tmp.bin",ios::out|ios::binary);
		tipocampos.clear();
		nombrecampos.clear();
		AvailList.clear();
		sizes.clear();
		char buf[sizeof(int)*3]; //antes tenia *2
		in2.read(buf,sizeof(int)*3);
		charint primeraleida;
		memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
		CantidadCampos = primeraleida.num;
		out2.write(reinterpret_cast<char*>(&CantidadCampos),sizeof(int));
		charint primerAvail;
		memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
		int hola = primerAvail.num;
		AvailList.push_back(hola);
		out2.write(reinterpret_cast<char*>(&hola),sizeof(int));
		charint primeratipoLLave;
		memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
		tipoLlave = primeratipoLLave.num;
		out2.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
		char BufferNombres[CantidadCampos*sizeof(char)*20];
		in2.read(BufferNombres,CantidadCampos*sizeof(char)*20);
		int progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			char eslabon[20];
			memcpy(eslabon,BufferNombres+progreso,19);
			eslabon[19]='\0';
			progreso += sizeof(char)*20;
			out2.write(reinterpret_cast<char*>(&eslabon),sizeof(char)*20);
			nombrecampos.push_back(eslabon);
		}	//marca
		char BufferTipo[CantidadCampos*sizeof(int)];
		in2.read(BufferTipo,CantidadCampos*sizeof(int));
		charint CI;
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
			int cant = CI.num;
			out2.write(reinterpret_cast<char*>(&cant),sizeof(int));
			tipocampos.push_back(CI.num);
			progreso += sizeof(int);
		}
		/////////
		char BufferSizes[CantidadCampos*sizeof(int)];
		charint elSize;
		in2.read(BufferSizes,CantidadCampos*sizeof(int));
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(elSize.raw,BufferSizes+progreso,sizeof(int));
			int tamanito = elSize.num;
			out2.write(reinterpret_cast<char*>(&tamanito),sizeof(int));
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
		in2.close();
		for (int k = 0; k < listaindicesINT.size(); k++){
			ifstream in3(fileName, ios::in|ios::binary);
			int mux = rrnArray[k];
			offset = 0;
			offset += sizeof(int)*3;
			offset += CantidadCampos*sizeof(char)*20;
			offset += CantidadCampos*sizeof(int);
			offset += CantidadCampos*sizeof(int);
			offset += totalbuffer*mux;
			in3.seekg(offset);
			char buffersito[totalbuffer];
			in3.read(buffersito,totalbuffer);
			progress = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				if (tipocampos[i]==1){
					char chain[sizes[i]];
					memcpy(chain, buffersito+progress, sizes[i]-1);
					chain[sizes[i]-1] = '\0';
					progress += sizes[i];
					out2.write(reinterpret_cast<char*>(&chain),sizeof(char)*sizes[i]);
				
				}else if(tipocampos[i]==2){
					char car[2];
					memcpy(car,buffersito+progress,sizeof(char));
					out2.write(reinterpret_cast<char*>(&car),sizeof(char));
					progress += sizeof(char);
					car[1] = '\0';
						
				}else if(tipocampos[i]==3){
					charint elEntero;
					int entero;
					memcpy(elEntero.raw,buffersito+progress,sizeof(int));
					progress += sizeof(int);
					entero = elEntero.num;
					out2.write(reinterpret_cast<char*>(&entero),sizeof(int));
					
				}else if(tipocampos[i]==5){
					charfloat elFloat;
					float elFlotante;
					memcpy(elFloat.raw,buffersito+progress,sizeof(float));
					progress += sizeof(float);
					elFlotante = elFloat.num;
					out2.write(reinterpret_cast<char*>(&elFlotante),sizeof(float));
			
				}else if(tipocampos[i]==4){
					chardouble elDouble;
					double elDoble;
					memcpy(elDouble.raw,buffersito+progress,sizeof(double));
					progress += sizeof(double);
					elDoble = elDouble.num;
					out2.write(reinterpret_cast<char*>(&elDoble),sizeof(double));
					
				}
			}
				
			in3.close();
		}
		out.close();
		remove(fileName);
		int result = rename("tmp.bin",fileName);
		cout<<"Registros ordenados con éxito!"<<endl;

	}else if(tipoLlave==1){//end if is not tipollave==1
		string keysArrayStr[listaindicesstrings.size()];
		int rrnArray[listaindicesstrings.size()];
		for (int i = 0; i < listaindicesstrings.size(); ++i){
			keysArrayStr[i] = listaindicesstrings[i].key;
			rrnArray[i] = listaindicesstrings[i].rrn;
		}
		sort(keysArrayStr,0,listaindicesstrings.size()-1, rrnArray);
		int hasta = listaindicesstrings.size();
		listaindicesstrings.clear();
		for (int i = 0; i < hasta; ++i){
			IndString ind;
			ind.rrn = rrnArray[i];
			//ind.key = keysArrayStr[i];
			strcpy(ind.key,keysArrayStr[i].c_str());
			listaindicesstrings.push_back(ind);
		}
		cout<<endl;
		stringstream ss;
		ss<<fileName<<".index";
		char nombreIndices[26];
		ss>>nombreIndices;
		fstream out(nombreIndices, ios::out|ios::binary);
		for (int i = 0; i < listaindicesstrings.size(); ++i){
			int numerito;
			char theString[20];
			numerito = rrnArray[i];
			//theString = keysArrayStr[i].c_str();
			strcpy(theString,keysArrayStr[i].c_str());
			out.write(reinterpret_cast<char*>(&theString),sizeof(char)*20);
		}
		out.close();
		/////////////////////////////////////////////////////////////////////////////
		ifstream in2(fileName,ios::in|ios::binary);
		ofstream out2("tmp.bin",ios::out|ios::binary);
		tipocampos.clear();
		nombrecampos.clear();
		AvailList.clear();
		sizes.clear();
		char buf[sizeof(int)*3]; //antes tenia *2
		in2.read(buf,sizeof(int)*3);
		charint primeraleida;
		memcpy(primeraleida.raw,buf,sizeof(int));//Copia al buffer la cantidad de campos
		CantidadCampos = primeraleida.num;
		out2.write(reinterpret_cast<char*>(&CantidadCampos),sizeof(int));
		charint primerAvail;
		memcpy(primerAvail.raw,buf+sizeof(int),sizeof(int));//Copia al buffer el primer elemento del avail list
		int firstAvail = primerAvail.num;
		AvailList.push_back(firstAvail);
		out2.write(reinterpret_cast<char*>(&firstAvail),sizeof(int));
		charint primeratipoLLave;
		memcpy(primeratipoLLave.raw,buf+sizeof(int)+sizeof(int),sizeof(int));
		tipoLlave = primeratipoLLave.num;
		out2.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
		char BufferNombres[CantidadCampos*sizeof(char)*20];
		in2.read(BufferNombres,CantidadCampos*sizeof(char)*20);
		int progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			char eslabon[20];
			memcpy(eslabon,BufferNombres+progreso,19);
			eslabon[19]='\0';
			progreso += sizeof(char)*20;
			out2.write(reinterpret_cast<char*>(&eslabon),sizeof(char)*20);
			nombrecampos.push_back(eslabon);
		}
		char BufferTipo[CantidadCampos*sizeof(int)];
		in2.read(BufferTipo,CantidadCampos*sizeof(int));
		charint CI;
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(CI.raw,BufferTipo+progreso,sizeof(int));
			int cant = CI.num;
			out2.write(reinterpret_cast<char*>(&cant),sizeof(int));
			tipocampos.push_back(CI.num);
			progreso += sizeof(int);
		}
		/////////
		char BufferSizes[CantidadCampos*sizeof(int)];
		charint elSize;
		in2.read(BufferSizes,CantidadCampos*sizeof(int));
		progreso = 0;
		for (int i = 0; i < CantidadCampos; ++i){
			memcpy(elSize.raw,BufferSizes+progreso,sizeof(int));
			int tamanito = elSize.num;
			out2.write(reinterpret_cast<char*>(&tamanito),sizeof(int));
			sizes.push_back(elSize.num);
			progreso += sizeof(int);
		}
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
		in2.close();
		for (int k = 0; k < listaindicesstrings.size(); k++){
			ifstream in3(fileName, ios::in|ios::binary);
			int mux = rrnArray[k];
			offset = 0;
			offset += sizeof(int)*3;
			offset += CantidadCampos*sizeof(char)*20;
			offset += CantidadCampos*sizeof(int);
			offset += CantidadCampos*sizeof(int);
			offset += totalbuffer*mux;
			in3.seekg(offset);
			char buffersito[totalbuffer];
			in3.read(buffersito,totalbuffer);
			progress = 0;
			for (int i = 0; i < CantidadCampos; ++i){
				if (tipocampos[i]==1){
					char chain[sizes[i]];
					memcpy(chain, buffersito+progress, sizes[i]-1);
					chain[sizes[i]-1] = '\0';
					progress += sizes[i];
					out2.write(reinterpret_cast<char*>(&chain),sizeof(char)*sizes[i]);
				
				}else if(tipocampos[i]==2){
					char car[2];
					memcpy(car,buffersito+progress,sizeof(char));
					out2.write(reinterpret_cast<char*>(&car),sizeof(char));
					progress += sizeof(char);
					car[1] = '\0';	
			
				}else if(tipocampos[i]==3){
					charint elEntero;
					int entero;
					memcpy(elEntero.raw,buffersito+progress,sizeof(int));
					progress += sizeof(int);
					entero = elEntero.num;
					out2.write(reinterpret_cast<char*>(&entero),sizeof(int));
					

				}else if(tipocampos[i]==5){
					charfloat elFloat;
					float elFlotante;
					memcpy(elFloat.raw,buffersito+progress,sizeof(float));
					progress += sizeof(float);
					elFlotante = elFloat.num;
					out2.write(reinterpret_cast<char*>(&elFlotante),sizeof(float));
			
				}else if(tipocampos[i]==4){
					chardouble elDouble;
					double elDoble;
					memcpy(elDouble.raw,buffersito+progress,sizeof(double));
					progress += sizeof(double);
					elDoble = elDouble.num;
					out2.write(reinterpret_cast<char*>(&elDoble),sizeof(double));
					
				}
			}
				
			in3.close();
		}
		out.close();
		remove(fileName);
		int result = rename("tmp.bin",fileName);
		cout<<"Registros ordenados con éxito!"<<endl;
	}else{
		cout<<"Registro no contiene llave!"<<endl;
	}
}

void quicksort(int A[], int izq, int der, int B[]) {
 int pivote=A[izq]; // tomamos primer elemento como pivote
 int pivote2 = B[izq];
 int i=izq; // i realiza la búsqueda de izquierda a derecha
 int j=der; // j realiza la búsqueda de derecha a izquierda
 int aux;
 int aux2;
	while(i<j){            // mientras no se crucen las búsquedas
    	while(A[i]<=pivote && i<j) i++; // busca elemento mayor que pivote
    	while(A[j]>pivote) j--;         // busca elemento menor que pivote
    	if (i<j) {                      // si no se han cruzado                      
	        aux= A[i]; 
	        aux2 = B[i];                 // los intercambia
	        A[i]=A[j];
	        B[i]=B[j];
	        A[j]=aux;
	        B[j]=aux2;
    	}
 	}
  A[izq]=A[j]; // se coloca el pivote en su lugar de forma que tendremos
  B[izq]=B[j];
  A[j]=pivote; // los menores a su izquierda y los mayores a su derecha
  B[j]= pivote2;
	if(izq<j-1)
		quicksort(A,izq,j-1,B); // ordenamos subarray izquierdo
	if(j+1 <der)
     	quicksort(A,j+1,der,B); // ordenamos subarray derecho
}
void sort(string A[], int izq, int der, int B[]){
	string pivote = A[izq]; // tomamos primer elemento como pivote
	int pivote2 = B[izq];
	int i=izq; // i realiza la búsqueda de izquierda a derecha
	int j=der; // j realiza la búsqueda de derecha a izquierda
	string aux;
	int aux2;
	while(i<j){            // mientras no se crucen las búsquedas
	   	while(A[i].compare(pivote)<=0 && i<j) i++; // busca elemento mayor que pivote
	   	while(A[j].compare(pivote)>0) j--;         // busca elemento menor que pivote
	   	if (i<j) {                      // si no se han cruzado                      
	        aux= A[i]; 
	        aux2 = B[i];                 // los intercambia
	        A[i]=A[j];
	        B[i]=B[j];
	        A[j]=aux;
	        B[j]=aux2;
	   	}
	}
	A[izq]=A[j]; // se coloca el pivote en su lugar de forma que tendremos
	B[izq]=B[j];
	A[j]=pivote; // los menores a su izquierda y los mayores a su derecha
	B[j]= pivote2;
	if(izq<j-1)
		sort(A,izq,j-1,B); // ordenamos subarray izquierdo
	if(j+1 < der)
	   	sort(A,j+1,der,B); // ordenamos subarray derecho
}