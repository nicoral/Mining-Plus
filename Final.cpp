#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <vector>
using namespace std;

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
vector<string> SplitElements(string Header)
{
	vector<string> elements;
	string elem="";
	for(int i=44;i<Header.size();i++)
	{
		if(Header[i]==',')
		{
			elements.push_back(elem);
			elem="";
		}
		else
		{
			elem+=Header[i];
		}
	}
	elements.push_back(elem);
	return elements;
}
bool PosicionesElements(vector<string> &AllElemts,vector<string> &ActualElemets,vector<int> &Posiciones)
{
	bool find;
	for(int x=0;x<ActualElemets.size();x++)
	{
		find=false;
		for(int y=0;y<AllElemts.size();y++)
		{
			if(ActualElemets[x]==AllElemts[y])
			{
				Posiciones[x]=y;
				find=true;
				break;
			}
		}
		if(!find)
		{
			cout<<"Error: "<<ActualElemets[x]<<" No se encuentra en header principal"<<endl;
			return false;
		}
	}
	return true;
}
void Consolidacion()
{
	fstream head("Data/Header.txt");
	char* linea=new char[10000];
	if(!head.is_open())
	{
		cout<<"Error: Archivo de Header.txt no se encuentra ."<<endl;
		return;
	}
	head.getline(linea,10000);
	vector<string> elements;
	elements=SplitElements(linea);
	vector<string> Archivos;
	Archivos=muestra_contenido_de("Originales/resultados/");
	ofstream ArchivoFinal("ExcelFinal.csv");
	ArchivoFinal<<"Certified,File Created,File Received,Sample,";
	for(int i=0;i<elements.size();i++)
	{
		if(i<elements.size()-1)
		{
			ArchivoFinal<<elements[i]<<",";	
		}
		else
			ArchivoFinal<<elements[i]<<endl;		
	}
	for(int i=2;i<Archivos.size();i++)
	{
		fstream ArchiActual("Originales/resultados/"+Archivos[i]);
		if(ArchiActual.is_open())
		{
			vector<string> eleActuls;
			 

			for(int j=0;j<4;j++)
			{
				ArchiActual.getline(linea,1000,',');

			}
			ArchiActual.getline(linea,1000);
			string ele(linea),auxEle="";
			for(int j=0;j<ele.size();j++)
			{
				if(ele[j]==',')
				{
					eleActuls.push_back(auxEle);
					auxEle="";
				}
				else
				{
					auxEle+=ele[j];
				}
			}
			string CerFech="";
			for(int j=0;j<3;j++)
			{
				ArchiActual.getline(linea,1000,',');
				string auxCerFech(linea);
				CerFech+=auxCerFech+",";
			}
			vector<int> Posiciones(eleActuls.size(),0);
			if(!PosicionesElements(elements,eleActuls,Posiciones))
			{
				cout<<Archivos[i]<<endl;
				return;
			}
			while(!ArchiActual.eof())
			{
				ArchiActual.getline(linea,1000,',');
				string sample(linea);
				ArchiActual.getline(linea,1000);
				int posiEle=0;
				vector<string> newLine(elements.size(),"");
				string auxNewLine="",NeewLine(linea);
				for(int j=0;j<NeewLine.size();j++)
				{
					if(NeewLine[j]==',')
					{
						newLine[Posiciones[posiEle]]=auxNewLine;
						posiEle++;
						auxNewLine="";
					}
					else
					{
						auxNewLine+=NeewLine[j];
					}
				}
				auxNewLine="";
				for(int j=0;j<newLine.size();j++)
				{
					if(j<newLine.size()-1)
					{
						if(newLine[j]!="")
						{
							auxNewLine+=newLine[j]+",";
						}
						else
						{
							auxNewLine+=",";	
						}
					}
					else
					{
						auxNewLine+=newLine[j];	
					}
				}
				ArchivoFinal<<CerFech<<sample<<","<<auxNewLine<<endl;
				for(int j=0;j<3;j++)
				{
					ArchiActual.getline(linea,1000,',');
				}
			}
		}
		else
		{
			cout<<"Error: Con el archivo "<<Archivos[i]<<endl;
			return;
		}
	}
}




int main()
{
	Consolidacion();
	system("PAUSE");
	return 0;
}