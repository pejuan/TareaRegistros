#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>
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
struct IndString
{
	int rrn;
	char key[20];
};
struct IndNum
{
	int rrn;
	int key;
};
static void quicksort(vector<IndNum>, int, int);
int main(int argc, char** argv){
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
		char fileName[20];
		string namekeyespejo;
		char nombre[20];
		int opcion2;
		int tipoLlave;
		cout<<"------------------------------------------------------------------------------------------------------------"<<endl
			<<endl;
		cout<<"1)Ingresar nuevo"<<endl<<"2)Leer/Listar"<<endl<<"3)Agregar mas registros"<<endl<<"4)Borrar registro"<<endl
			<<"5)Buscar registro"<<endl<<"6)Modificar"<<endl<<"7)Compactar"<<endl<<"8)Salir"<<endl
			<<"9)Keysort"<<endl<<"Ingrese el codigo de lo que desea hacer:";
		cin>>opcion2;
		if (opcion2==1){
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
			cout<<"Ingrese cuantos campos tendra su estructura sin contar la llave: ";
			cin>>CantidadCampos;
			CantidadCampos++;
			ofstream out(fileName, ios::out|ios::binary);
			int avail = -1;
			AvailList.push_back(avail);
			out.write(reinterpret_cast<char*>(&CantidadCampos), sizeof(int)); //Guarda la cantidad de campos en el archivo binario
			out.write(reinterpret_cast<char*>(&avail), sizeof(int)); //Guarda el primer elemento de avail list
			int contador = 0;
			IndString keyStr;
			IndNum keyNum;
			cout<<"---------------------"<<endl<<"1)String"<<endl<<"2)Integer"<<endl<<"Ingrese de que tipo sera su Llave primaria:";
			cin>>tipoLlave;
			if(tipoLlave==1){
				cout<<"Ingrese el nombre de su llave de tipo String:";
				cin>>namekey;
				namekeyespejo = namekey;
				nombrecampos.push_back(namekey);
				espejoCampos.push_back(namekey);
				out.write(reinterpret_cast<char*>(&tipoLlave),sizeof(int));
				out.write(reinterpret_cast<char*>(&namekey),sizeof(char)*20);
				tipocampos.push_back(1);
				sizes.push_back(20);
			}else{
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
				if (contador==(CantidadCampos-1)){
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
							continuar=false;
						}
					}else{
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
							continuar=false;
						}

					}
				}
				
				for (int i = 1; i < tipocampos.size(); ++i){
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
					cout<<"Estructura creada con éxito y registros agregados con éxito."<<endl;
					break;
				}
			}
		}else if(opcion2==2){ //Leer
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			}
			in.close();

		}else if(opcion2==3){//Append
			char resp2;
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
				if(false){ //AvailList[0] != -1
					ifstream getting(fileName,ios::in|ios::binary);	
					cout<<AvailList[0]<<endl;
					cualquier = AvailList[0];
					cout<<"Cualquier:"<<cualquier<<endl;		
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
					cout<<"premiereAvail:"<<premiereAvail<<endl;
					ofstream addAvail(fileName, ios::out|ios::binary);
					addAvail.seekp(sizeof(int));
					addAvail.write(reinterpret_cast<char*>(&premiereAvail),sizeof(int));
					addAvail.close();
					ofstream rempl(fileName, ios::out|ios::binary);
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
					for (int i = 0; i < tipocampos.size(); ++i){
						if(tipocampos[i]==1){
							cout<<"Ingrese la cadena perteneciente al campo "<<espejoCampos[i]<<endl;
							char cadena[sizes[i]];
							cin>>cadena;
							append.write(reinterpret_cast<char*>(&cadena), sizeof(char)*(sizes[i]));////aqui quitar el -1
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

					cout<<"Desea agregar otro registro hasta abajo? [S/N]:";				
					cin>>resp2;
					if (resp2=='s' || resp2=='S'){
				
					}else{
						cout<<"Registro(s) agregado(s) con éxito."<<endl;
						break;
					}
				}
				
			}


		}else if(opcion2==4){//Borrar
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			cout<<setw(10)<<"Indice";
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
			}
			in.close();
			int indiceBorrado;
			cout<<"Ingrese el RRn de el registro que desea eliminar:";
			cin>>indiceBorrado;
			int offset = 0;
			offset += sizeof(int)*3;
			offset += CantidadCampos*sizeof(char)*20;
			offset += CantidadCampos*sizeof(int);
			offset += CantidadCampos*sizeof(int);
			offset += totalbuffer*indiceBorrado;
			ifstream checker("Registro.bin",ios::in|ios::binary);
			checker.seekg(sizeof(int));
			char charAvail[sizeof(int)];
			checker.read(charAvail,sizeof(int));
			charint tmp;
			memcpy(tmp.raw,charAvail,sizeof(int));
			int tmpnum = tmp.num;
			checker.close();
			fstream er("Registro.bin", ios::out|ios::in|ios::binary);	
			er.seekp(offset);
			char mark = '*';
			er.write(reinterpret_cast<char*>(&mark),sizeof(char));
			er.write(reinterpret_cast<char*>(&tmpnum),sizeof(int));
			er.close();
			cout<<"Borrado con exito!"<<endl;
			fstream act("Registro.bin", ios::out|ios::in|ios::binary);
			act.seekp(sizeof(int));
			act.write(reinterpret_cast<char*>(&indiceBorrado),sizeof(int));
			act.close();
			//end if 4
		}else if(opcion2==5){//buscar
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			cout<<"Elija el metodo con el que realizara la busqueda"<<endl<<"1)Por RRN"<<endl<<"2)Por Campo"<<endl
				<<"Ingrese codigo de opcion:";
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
				////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////////////////////////////////////////////////////
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

			}


		}else if(opcion2==6){//modificar
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			cout<<setw(10)<<"Indice";
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
			}
			in.close();
			int indiceModificado;
			cout<<"Ingrese el RRN de el registro que desea modificar:";
			cin>>indiceModificado;
			fstream mod("Registro.bin", ios::out|ios::in|ios::binary);

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

		}else if(opcion2==7){//Compactar
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			int tmpint = primerAvail.num;
			out.write(reinterpret_cast<char*>(&tmpint), sizeof(int));
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
		}else if(opcion2 == 8){
			break;






		}else if(opcion2 == 9){
			listaindicesstrings.clear();
			listaindicesINT.clear();
			cout<<"Ingrese el nombre del archivo con el que realizara la accion:";
			cin>>fileName;
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
			while(in.good()){ ///quitar el eof

				in.read(buffer,totalbuffer);
				if(in.eof()){
					break;
				}
				if(tipoLlave==1){
					IndString ind;
					ind.rrn = contadorRRN;
					memcpy(ind.key,buffer,sizeof(char)*19);
					ind.key[19] = '\0';
					listaindicesstrings.push_back(ind);

				}else{
					IndNum ind2;
					ind2.rrn = contadorRRN;
					charint llavecharint;
					memcpy(llavecharint.raw,buffer,sizeof(int));
					ind2.key = llavecharint.num;
					listaindicesINT.push_back(ind2);
				}
				contadorRRN++;
			}
			inRRN.close();


			///////////////////////////////////////////////////////////////////////


			///////////////////////////////////////////////////////////////////////

			
		}



	}//end while
	

	return 0;
}

static void quicksort(vector<IndNum> A, int izq, int der) {
 int pivote=A[izq].key; // tomamos primer elemento como pivote
 int i=izq; // i realiza la búsqueda de izquierda a derecha
 int j=der; // j realiza la búsqueda de derecha a izquierda
 int aux;

 while(i<j){            // mientras no se crucen las búsquedas
    while(A[i].key <=pivote && i<j) i++; // busca elemento mayor que pivote
    while(A[j].key >pivote) j--;         // busca elemento menor que pivote
    if (i<j) {                      // si no se han cruzado                      
        aux= A[i].key;                  // los intercambia
        A[i].key = A[j].key;
        A[j].key = aux;
    }
  }
  A[izq].key =A[j].key; // se coloca el pivote en su lugar de forma que tendremos
  A[j].key =pivote; // los menores a su izquierda y los mayores a su derecha
  if(izq<j-1)
     quicksort(A,izq,j-1); // ordenamos subarray izquierdo
  if(j+1 <der)
     quicksort(A,j+1,der); // ordenamos subarray derecho
}