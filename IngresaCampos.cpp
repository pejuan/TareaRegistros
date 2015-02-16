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
	cout<<"1)Ingresar nuevo"<<endl<<"2)Leer/Listar"<<endl<<"3)Agregar mas registros"<<endl<<"4)Borrar registro"<<endl
		<<"5)Buscar registro"<<endl<<"6)Modificar"<<endl<<"Ingrese el codigo de lo que desea hacer:";
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

		ifstream in("Registro.bin", ios::in|ios::binary);
		tipocampos.clear();
		nombrecampos.clear();
		sizes.clear();
		espejoCampos.clear();
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
		ofstream append("Registro.bin", ios::out|ios::in|ios::app|ios::binary);
		cout<<"-------------------------------------------------"<<endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		while(true){
			cout<<"Ingrese los datos:"<<endl;
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


			cout<<"Desea agregar otro registro? [S/N]:";
			char resp2;
			cin>>resp2;
			if (resp2=='s' || resp2=='S'){
			
			}else{
				append.close();
				break;
			}
		}


	}else if(opcion2==4){//Borrar

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
		cout<<"Ingrese el indice de el registro que desea eliminar:";
		cin>>indiceBorrado;

		fstream er("Registro.bin", ios::out|ios::in|ios::binary);

		int offset = 0;
		offset += sizeof(int);
		offset += CantidadCampos*sizeof(char)*20;
		offset += CantidadCampos*sizeof(int);
		offset += CantidadCampos*sizeof(int);
		offset += totalbuffer*indiceBorrado;
		er.seekp(offset);
		char mark = '*';
		er.write(reinterpret_cast<char*>(&mark),sizeof(char));
		er.close();
		cout<<"Borrado con exito!"<<endl;
		//end if 4
	}else if(opcion2==5){//buscar

		int metodo;
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
		cout<<"Elija el metodo con el que realizara la busqueda"<<endl<<"1)Por Indice"<<endl<<"2)Por Campo"<<endl
			<<"Ingrese codigo de opcion:";
		cin>>metodo;
		if (metodo==1){////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			ifstream busq("Registro.bin",ios::in|ios::binary);
			cout<<"Ingrese el indice del registro que quiere desplegar:";
			int index;
			cin>>index;
			int offset = 0;
			offset += sizeof(int);
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
			cout<<endl;
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
			offset += sizeof(int);
			offset += CantidadCampos*sizeof(char)*20;
			offset += CantidadCampos*sizeof(int);
			offset += CantidadCampos*sizeof(int);
			char garbage[offset];
			ifstream busq("Registro.bin",ios::in|ios::binary);
			busq.read(garbage,offset);

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
					cout<<endl;
					break;

				}
				contador++;
			}
			busq.close();

























		}


	}else if(opcion2==6){//modificar

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
		cout<<"Ingrese el indice de el registro que desea modificar:";
		cin>>indiceModificado;
		fstream mod("Registro.bin", ios::out|ios::in|ios::binary);

		int offset = 0;
		offset += sizeof(int);
		offset += CantidadCampos*sizeof(char)*20;
		offset += CantidadCampos*sizeof(int);
		offset += CantidadCampos*sizeof(int);
		offset += totalbuffer*indiceModificado;
		char buffMod[offset];
		mod.read(buffMod,offset);

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

	}

	return 0;
}