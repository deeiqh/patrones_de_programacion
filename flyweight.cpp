/*
https://docs.google.com/presentation/d/1_znCnvImkLtVWtM-8d8eUyQ4oJuDiIdbCmOX7rbPY8s/edit?usp=sharing
*/
#include <iostream>
#include <map>
#include <utility>
#include <string>

using namespace std;
#define pii_f_s pair<int,int>,float,string

template<class Radio, class Color>
class Fabrica_pelotas{
public:
	Radio radio;
	Color color;

	static map< pair<Radio,Color>,Fabrica_pelotas* > map_radioColor; // solo para buscar ḿás rápido

	Fabrica_pelotas(){};
	Fabrica_pelotas(Radio radio, Color color):radio(radio),color(color){};
};

template<class Posicion, class Radio, class Color>
class Pelota{
public:	
	Posicion posicion;
	Fabrica_pelotas<Radio,Color> *fabrica;
	
	Pelota(Posicion posicion, Fabrica_pelotas<Radio,Color> *fabrica=NULL):posicion(posicion), fabrica(fabrica){};
};


class Fabrica{
public:
	template<class Posicion, class Radio, class Color>
	Pelota<Posicion,Radio,Color> crear_pelota(Posicion posicion, Radio radio, Color color){

		static map< pair<Radio,Color>,Fabrica_pelotas<Radio,Color>* > map_radioColor; // solo para buscar ḿás rápido

		auto it = map_radioColor.find(make_pair(radio,color));

		if(  it != map_radioColor.end()){// si ya hay fábrica de esas pelotas
			return Pelota<Posicion,Radio,Color> (posicion,(*it).second);	
		}

		Fabrica_pelotas<Radio,Color> *fabrica_pelotas = new Fabrica_pelotas<Radio,Color>(radio, color);
		map_radioColor[make_pair(radio,color)] = fabrica_pelotas;

		return Pelota<Posicion,Radio,Color> (posicion,fabrica_pelotas);	
	}
};

int main(){

	Fabrica fabrica;

	Pelota<pii_f_s> pelota_1 = fabrica.crear_pelota<pii_f_s>( make_pair(12,13), 13.5, "rojo" );
	Pelota<pii_f_s> pelota_2 = fabrica.crear_pelota<pii_f_s>( make_pair(13,13), 13.5, "rojo" );
	Pelota<pii_f_s> pelota_3 = fabrica.crear_pelota<pii_f_s>( make_pair(13,145), 13.5, "rojo" );
	Pelota<pii_f_s> pelota_4 = fabrica.crear_pelota<pii_f_s>( make_pair(34,67), 13.5, "rojo" );
	Pelota<pii_f_s> pelota_5 = fabrica.crear_pelota<pii_f_s>( make_pair(987,12), 14.7, "amarillo" );
	Pelota<pii_f_s> pelota_6 = fabrica.crear_pelota<pii_f_s>( make_pair(120,122), 14.7, "amarillo" );
	Pelota<pii_f_s> pelota_7 = fabrica.crear_pelota<pii_f_s>( make_pair(12,113), 17, "azul" );

	return 0;
}
