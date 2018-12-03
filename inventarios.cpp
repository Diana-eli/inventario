
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



using namespace std;
//DEFINIENDO LAS VARIABLES NECESARIAS
string articulo, auxnombre, cantidad, fecha;
int id=0, auxid=0;
char grupo[10];
char opca;
bool encontrado = false;


void altas()
{
    ///Variables de la biblioteca fstream para el manejo de archivos
    ofstream escritura;
    ifstream consulta;

    do{
    escritura.open("inventario.txt", ios::out | ios::app);//crea y escribe, si ya tiene texto une al final del archivo
    consulta.open("inventario.txt", ios::in);//solamente consulta o lee usando la variable sobre el archivo físico alumnos.txt

    if (escritura.is_open() && consulta.is_open()){


            bool repetido=false;

            cout<<"\n";
            cout<<"\tIngresa el ID del aticulo:    ";
            cin>>auxid;
            
            ///A continuación se aplica el tipo de lectura de archivos secuencial
            consulta>>id;
            while (!consulta.eof()){
                consulta>>articulo>>cantidad>>fecha;
                if (auxid==id){
                    cout<<"\t\tYa existe el ID...\n";
                    repetido=true;
                    break;
                }
                consulta>>id;
            }

            if (repetido==false){
                cout<<"\tIngresa el articulo:   ";
                cin>>articulo;
                cout<<"\tIngresa la cantidad de articulos: ";
                cin>>cantidad;
                cout<<"\tIngresa la fecha:    ";
                cin>>fecha;
                //ESCRIBIENDO LOS DATOS CAPTURADOS POR EL USUARIO EN EL ARCHIVO
                escritura<<auxid<<" "<<articulo<<" "<<cantidad<<" "<<fecha<<endl;
                cout<<"\n\tRegistro agregado...\n";
            }

            cout<<"\n\tDeseas ingresar otro articulo? (S/N): ";
            cin>>opca;

    }else{
        cout<<"El archivo no se pudo abrir \n";
    }

    escritura.close();
    consulta.close();

    }while (opca=='S' or opca=='s');

}

void bajas()
{
    ofstream aux;
    ifstream lectura;

    encontrado=false;

    aux.open("auxiliar.txt", ios::out);
    lectura.open("inventario.txt", ios::in);

    if (aux.is_open() && lectura.is_open()){

        cout<<"\n";
        cout<<"\tIngresa el ID del articulo: ";
        cin>>auxid;
            
            ///De nuevo se aplica el tipo de lectura de archivos secuencial, esto quiere decir que lee campo por campo hasta
            ///hasta llegar al final del archivo gracias a la función .eof()
            lectura>>id;
            while (!lectura.eof()){
                lectura>>articulo>>cantidad>>fecha;
                if (auxid==id){
                        encontrado=true;
                        cout<<"\n";
                        cout<<"\tID:    "<<id<<endl;
                        cout<<"\tArticulo:   "<<articulo<<endl;
                        cout<<"\tCantidad: "<<cantidad<<endl;
                        cout<<"\tFecha:    "<<fecha<<endl;
                        cout<<"\t________________________________\n\n";
                        cout<<"\tRealmente deseas eliminar el articulo actual (S/N)? ---> ";
                        cin>>opca;

                        if (opca=='S' or opca=='s'){
                            cout<<"\n\n\t\t\tarticulo eliminado...\n\n\t\t\a";
                        }else{
                            aux<<id<<" "<<articulo<<" "<<cantidad<<" "<<fecha<<endl;
                        }

                    }else{
                        aux<<id<<" "<<articulo<<" "<<cantidad<<" "<<fecha<<endl;
                    }
                lectura>>id;
            }
    }else{
        cout<<"\n\tEl archivo no se pudo abrir \n";
    }

    if (encontrado==false){
                cout<<"\n\tNo se encontro ningun registro con el ID que ingresaste: "<<auxid<<"\n\n\t\t\t";
            }

    aux.close();
    lectura.close();
    remove ("inventario.txt");
    rename("auxiliar.txt", "alumnos.txt");
}


void consultas()
{
    //Lectura de archivos

    ifstream lectura;
    lectura.open("inventario.txt", ios::out | ios::in);//CREA, ESCRIBE O LEE
    if (lectura.is_open()){
       //LEYENDO Y MOSTRANDO CADA CAMPO DEL ARCHIVO DE FORMA SECUENCIAL
       lectura>>id;
       while (!lectura.eof()){
            lectura>>articulo>>cantidad>>fecha;
            cout<<"\n";
            cout<<"\tID:    "<<id<<endl;
            cout<<"\tArticulo:   "<<articulo<<endl;
            cout<<"\tCantidad: "<<cantidad<<endl;
            cout<<"\tFecha:    "<<fecha<<endl;
            lectura>>id;
            cout<<"\t________________________________\n";
       }

    }else{
        cout<<"El archivo no se pudo abrir \n";
    }
    lectura.close();
}


void buscar()
{
    ifstream lectura;
    lectura.open("inventario.txt", ios::out | ios::in);

    encontrado=false;

    if (lectura.is_open()){
        cout<<"\n\tIngresa el ID del articulo a buscae: ";
        cin>>auxid;

        lectura>>id;
        while(!lectura.eof()){
            lectura>>articulo>>cantidad>>fecha;
        //comparar cada registro para ver si es encontrado

        if(auxid==id){
            cout<<"\n";
            cout<<"\tID:    "<<id<<endl;
            cout<<"\tArticulo:   "<<articulo<<endl;
            cout<<"\tCantidad: "<<cantidad<<endl;
            cout<<"\tFecha:    "<<fecha<<endl;
            cout<<"\t________________________________\n";
            encontrado=true;
            break;
        }//fin del if mostrar encontrado

        //lectura adelantada
        lectura>>id;
        }//fin del while
        if (encontrado==false){
            cout<<"\n\n\tNo hay registros con este ID: "<<auxid<<"\n\n\t\t\t";
        }
    }else{
        cout<<"\n\tAun no se pudo abrir el archivo...";
    }

    lectura.close();
}

void modificar()
{
    ofstream aux;
    ifstream lectura;

    encontrado=false;

    aux.open("auxiliar.txt", ios::out);
    lectura.open("inventario.txt", ios::in);

    if (aux.is_open() && lectura.is_open()){

        cout<<"\n";
        cout<<"\tIngresa el ID del articulo que deseas modificar: ";
        cin>>auxid;

            lectura>>id;
            while (!lectura.eof()){
                lectura>>articulo>>cantidad>>fecha;
                if (auxid==id){
                    encontrado=true;
                    cout<<"\n";
                    cout<<"\tID:    "<<id<<endl;
                    cout<<"\tArticulo:   "<<articulo<<endl;
                    cout<<"\tCantidad: "<<cantidad<<endl;
                    cout<<"\tFecha:    "<<fecha<<endl;
                    cout<<"\t________________________________\n\n";
                    cout<<"\tIngresa el nuevo articulo  con el ID: "<<auxid<<"\n\n\t---> ";
                    cin>>auxnombre;

                    aux<<id<<" "<<auxnombre<<" "<<cantidad<<" "<<fecha<<endl;
                    cout<<"\n\n\t\t\tRegistro modificado...\n\t\t\a";
                    }else{
                    aux<<id<<" "<<articulo<<" "<<cantidad<<" "<<fecha<<endl;
                    }
                lectura>>id;
            }
    }else{
        cout<<"\n\tEl archivo no se pudo abrir \n";
    }

    if (encontrado==false){
                cout<<"\n\tNo se encontro ningun registro con el ID: "<<auxid<<"\n\n\t\t\t";
            }

    aux.close();
    lectura.close();
    remove ("inventario.txt");
    rename("auxiliar.txt", "inventario.txt");
}

int main()
{
    system ("color 9");
    int opc;

    do{
    system("cls");

    cout<<"\n\tInventarios\n\n";
    cout<<"\n\t1.-Registrar de articulos";
    cout<<"\n\t2.-Eliminar articulos";
    cout<<"\n\t3.-Consultas";
    cout<<"\n\t4.-Buscar un articulo";
    cout<<"\n\t5.-Modificaciones";
    cout<<"\n\t6.-Salir";
    cout<<"\n\n\tElige una opcion:  ";
    cin>>opc;
    switch (opc)
    {
case 1:{
    system("cls");
    altas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 2:{
    system("cls");
    bajas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}

case 3:{
    system("cls");
    consultas();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 4:{
    system("cls");
    buscar();
    cout<<"\n\t\t";
    system ("pause");
    break;
}
case 5:{
    system("cls");
    modificar();
    cout<<"\n\t\t";
    system ("pause");

    break;
}
case 6:{
    cout<<"\n\n\tHa elegido salir...\n\n\t\t"; system ("pause");
    break;
}
default:{
    cout<<"\n\n\tHa elegido una opcion inexistente...\n\n\t\t"; system ("pause");
    break;
}
    }//fin switch

    }while (opc!=6);

    system("cls");

    return 0;
}
