#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>
using namespace std;
vector<string> elementos;
vector<string> descrip;
vector<string> sample;
vector<string> meses={"Ene","Feb","Maz","Apr","May","Jun","Jul","Ago","Sep","Oct","Nov","Dic"};
vector<string> ignorar;
vector<string> muestra_contenido_de(const std::string &a_carpeta)
{
    WIN32_FIND_DATA ffd{};
    vector<string> Names;
    if (auto handle = FindFirstFile((a_carpeta + "/*.*").c_str(), &ffd))
    {
        do
        {
        	Names.push_back(ffd.cFileName);
            //std::cout << ffd.cFileName << '\n';
        }
        while (FindNextFile(handle, &ffd) != 0);
    }
    return Names;
}
void LLenarVectors()
{
	char* linea=new char[1000];
	ifstream Archi("Data/Ignorados.txt");
	Archi.getline(linea,1000);
	string ign(linea),auxIgn="";
	if(Archi)
		for(int i=0;i<ign.size();i++)
		{
			if(ign[i]==',')
			{
				ignorar.push_back(auxIgn);
				auxIgn="";
			}
			else
			{
				auxIgn+=ign[i];
			}
		}
		ignorar.push_back(auxIgn);
		Archi.close();

	Archi.open("Data/Elementos.txt");
	Archi.getline(linea,1000);
	string Elem(linea),auxElem="";
	for(int i=0;i<Elem.size();i++)
	{
		if(Elem[i]==',')
		{
			elementos.push_back(auxElem);
			auxElem="";
		}
		else
		{
			auxElem+=Elem[i];
		}
	}
	elementos.push_back(auxElem);
	Archi.close();

	Archi.open("Data/Descripciones.txt");
	Archi.getline(linea,1000);
	string Descrip(linea),auxDescrip="";
	for(int i=0;i<Descrip.size();i++)
	{
		if(Descrip[i]==',')
		{
			descrip.push_back(auxDescrip);
			auxDescrip="";
		}
		else
		{
			auxDescrip+=Descrip[i];
		}
	}
	descrip.push_back(auxDescrip);
	Archi.close();

	Archi.open("Data/Samples.txt");
	Archi.getline(linea,1000);
	string samp(linea),auxsamp="";
	for(int i=0;i<samp.size();i++)
	{
		if(samp[i]==',')
		{
			sample.push_back(auxsamp);
			auxsamp="";
		}
		else
		{
			auxsamp+=samp[i];
		}
	}
	sample.push_back(auxsamp);
	Archi.close();
}
void FindDate2(char* linea, vector<string> &fechas)
{
	string lin(linea);
	string uno="",dos="",tres="",respuesta="";
	for(int i=0;i<lin.size();i++)
	{
		if(lin[i]>=48 && lin[i]<=57)
		{
			uno+=lin[i];
			i++;
			while(lin[i]>=48 && lin[i]<=57)
			{
				uno+=lin[i];
				i++;
			}
			if(lin[i]=='/' || lin[i]=='-')
			{
				i++;
				if(lin[i]>=48 && lin[i]<=57)
				{
					dos+=lin[i];
					i++;
					while(lin[i]>=48 && lin[i]<=57)
					{
						dos+=lin[i];
						i++;
					}
					if(lin[i]=='/' || lin[i]=='-')
					{
						i++;
						if(lin[i]>=48 && lin[i]<=57)
						{
							tres+=lin[i];
							i++;
							while(lin[i]>=48 && lin[i]<=57)
							{
								tres+=lin[i];
								i++;
							}
							respuesta=uno+"/"+dos+"/"+tres;
							fechas.push_back(respuesta);
							respuesta="";
						}
						
					}
				}
			}
		}
	}
}
void FindDate(char* linea, vector<string> &fechas)
{
	int i=0,ban;
	string lin(linea);
	string uno,mes,dos;
	if(lin.size()>=8)
	{
		for(int i=0;i<lin.size();i++)
		{
			if(lin[i]>=48 && lin[i]<=57)
			{
				int j=i;
				while(lin[j]>=48 && lin[j]<=57)
				{
					j++;
				}
				if(lin[j]=='-' || lin[j]=='/')
				{
					ban=j-i;
					uno=lin.substr(i,ban);
					j++;
					if(lin[j]>=48 && lin[j]<=57)
					{
						mes=lin.substr(j,2);
						j+=2;
					}
					else if(lin[j]>=65 && lin[j]<=90)
					{
						mes=lin.substr(j,3);
						j+=3;
					}
					if(lin[j]=='-' || lin[j]=='/')
					{
						if(ban==4)
						{
							dos=lin.substr(j+1,2);
							fechas.push_back(uno+"/"+mes+"/"+dos);
							i=j+2;
						}
						else if(ban==2)
						{
							dos=lin.substr(j+1,4);
							fechas.push_back(uno+"/"+mes+"/"+dos);
							i=j+4;
						}
					}
				}
			}
			
		}
		return;
	}
	else
		return;
}
string recopilarNombre(string nom)
{
	string res;
	for(int i=0;i<nom.size();i++)
	{
		if(nom[i]!='.')
			res+=nom[i];
		else
		{
			return res;
		}
	}
}
bool findElem(char* linea)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		for(int i=0;i<elementos.size();i++)
		{
			if(elementos[i]==aux)
				return true;
		}
	}
	return false;
}
bool esElement(char* ele)
{
	string elem(ele);
	for(int i=0;i<elementos.size();i++)
	{
		if(elementos[i]==elem)
			return true;
	}
	return false;
}
bool esdescription(char* des)
{
	string desc(des);
	for(int i=0;i<descrip.size();i++)
	{
		if(descrip[i]==desc)
			return true;
	}
	return false;
}
bool buscarSample(char* linea,long& sam)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		sam++;
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		for(int i=0;i<sample.size();i++)
		{
			if(sample[i]==aux)
				return true;
		}
	}
	sam=0;
	return false;
}
bool buscarSamp(char* linea)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		for(int i=0;i<sample.size();i++)
		{
			if(sample[i]==aux)
				return true;
		}
	}
	return false;
}
bool buscarDescription(char* linea)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		for(int i=0;i<descrip.size();i++)
		{
			if(descrip[i]==aux)
				return true;
		}
	}
	return false;
}
bool buscarDetection(char* linea)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		if(aux=="Min Detection" || aux=="Max Detection")
			return true;
	}
	return false;
}
bool BuscarIgnorar(char* linea)
{
	string lin(linea),aux;
	int j=0,k=0;
	while(j<lin.size())
	{
		while(linea[k]!=',' && k<lin.size())
		{
			k++;
		}
		aux=lin.substr(j,k-j);
		j=k+1;
		k++;
		for(int i=0;i<ignorar.size();i++)
		{
			if(ignorar[i]==aux)
				return true;
		}
	}
	return false;
}
bool saltoLinea(char* A)
{
	int i=0;
	while(A[i]!='\0')
	{
		if(A[i]=='\n')
		{
			return true;
		}
		i++;
	}
	return false;
}
bool soloComas(char* B)
{
	int i=0;
	while(B[i]!='\0')
	{
		if(B[i]!=','){return false;}
		i++;
	}
	return true;
}
string combinar(char* A,char* B)
{
	string first(A),second(B);
	string res="";
	int k=0,i=0;
	int tam2=second.size(),tam1=first.size();
	while(i<tam1)
	{
		while(first[i]!=',' && i<first.size())
		{
			res+=first[i];
			i++;	
		}
		i++;
		while(second[k]!=',' && k<second.size())
		{
			res+=second[k];
			k++;
		}
		k++;
		res+=',';
	}
	return res;
}
void archivosP(vector<string> &VEC)
{
	bool band=false;
	for(int i=0;i<VEC.size();i++)
	{
		for(int j=0;j<VEC[i].size();j++)
		{
			if(VEC[i][j]=='.')
			{
				band=true;
			}
		}
		if(!band)
		{
			VEC.erase(VEC.begin()+i);
			i--;
		}
		else
		{
			band=false;
		}
	}
}
bool archiCSV(string arch)
{
	int n=arch.size();
	if(arch[n-4]=='.' && (arch[n-1]=='v' && arch[n-2]=='s' && arch[n-3]=='c') || (arch[n-1]=='V' && arch[n-2]=='S' && arch[n-3]=='C'))
		return true;
	else 
		return false;
}
void Analizador(string carpeta)
{
	vector<string> Archivos=muestra_contenido_de(carpeta);
	archivosP(Archivos);
	int comas=0;
	char *lectura=new char[10000];
	char *escritura=new char[10000];
	char* lec=new char[1000];
	char* esc=new char[1000];
	long sam,eleposicion;
	vector<string> fechas;
	string nomArchi;
	for(int i=2;i<Archivos.size();i++)
	{
		if(archiCSV(Archivos[i]))
		{
			comas=0;	
			sam=0;
			fstream archivo(carpeta+"/"+Archivos[i]);	
			if(archivo.is_open() && !archivo.eof())
	        {
	        	cout<<Archivos[i]<<endl;
				while(fechas.size()<2 && !archivo.eof())
				{
					archivo.getline(lectura,1000);
					FindDate2(lectura,fechas);

				}
				if(archivo.eof())
				{
					cout<<"ERROR: Busqueda de fechas."<<endl;
					return;
				}
				eleposicion=archivo.tellp();
				archivo.getline(lectura,10000,',');
				while(!esElement(lectura))
				{	
					//cout<<lectura<<endl;
					archivo.getline(lectura,100,',');
					if(saltoLinea(lectura))
					{
						comas=0;
					}
					else
					{
						comas++;
					}
				}
				archivo.getline(lec,1000);
				strcat(lectura,",");
				strcat(lectura,lec);
				for(int k=0;k<comas;k++)
				{
					archivo.getline(escritura,100,',');
				}
				while(!esdescription(escritura) && !archivo.eof())
				{
					//cout<<escritura<<"->";
					if(saltoLinea(escritura))
					{
						for(int k=0;k<comas-1;k++)
						{
							archivo.getline(escritura,100,',');
						}
					}	
					archivo.getline(escritura,100,',');
				}
				if(archivo.eof())
				{
					cout<<"Error en el formato de la descripcion."<<endl;
				}
				archivo.getline(esc,10000);
				strcat(escritura,",");
				strcat(escritura,esc);
				
				string r=combinar(lectura,escritura);
				nomArchi=recopilarNombre(Archivos[i]);
				ofstream result(carpeta+"/resultados/"+nomArchi+".CSV");

				result<<"Certified,File Created,File Received,Sample,";
				
				result<<r<<endl;
				archivo.seekp(eleposicion);
				while(!buscarSample(lectura,sam) && !archivo.eof())
				{
					archivo.getline(lectura,1000);
				}
				
				if(archivo.eof())
					cout<<"Error en la busqueda del SAMPLE."<<endl;
				else
				{
					archivo.getline(lectura,1000);
					while(BuscarIgnorar(lectura))
					{
						archivo.getline(lectura,1000);
					}
					//cout<<"sam: "<<sam<<" comas: "<<comas<<endl;
					while(!archivo.eof())
					{
						string lineastr(lectura);
						string samp="",dat="";
						int co=0,m=0;
						bool subtitulo=false;
						for(;co<sam-1 && m<lineastr.size();m++)
						{
							if(lineastr[m]==',')
							{
								co++;
							}
						}

						while(lineastr[m]!=',')
						{
							samp+=lineastr[m];
							m++;
						}
						m++;
						co=0;
						for(;co<comas-sam && m<lineastr.size();m++)
						{
							//cout<<lineastr[m];
							if(lineastr[m]==',')
							{
								co++;
							}
						}
						//cout<<endl;
						for(;m<lineastr.size();m++)
						{
							dat+=lineastr[m];
						}

						if(dat=="" || samp=="")
							subtitulo=true;

						if(!subtitulo)
						{
							if(soloComas(lectura))
							{
								break;
							}
							else
							{
								result<<nomArchi<<","<<fechas[0]<<","<<fechas[1]<<","<<samp<<","<<dat<<endl;	
							}
						}
						else
						{
							break;
						}
						archivo.getline(lectura,1000);
					}
				}
				result.close();
	        	archivo.close();
	        	fechas.clear();
	        }
	        else
	        {
	        	cout<<"Error al abrir el archivo: "<<Archivos[i]<<endl;
	        }
		}
		else
			cout<<Archivos[i]<<"->  Error en el formato del archivo. SOLO SE PERMITEN ARCHIVOS CSV."<<endl;
        
	}
	
}
int main()
{
	LLenarVectors();
	Analizador("Originales");
	system("PAUSE");	
	return 0;

}