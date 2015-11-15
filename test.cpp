#include <iostream>
#include <stdio.h>

using namespace std;

struct RegistroRepuestos {
    int codigo_producto;
    int modelo_pertenencia;
    int stock;
    int fecha_ultima_reposicion;
    double precio_unitario;
    char descripcion[20];
};

struct NodoListaRepuestos {
    RegistroRepuestos nodo_info;
    NodoListaRepuestos* nodo_siguiente;
};

void ArmarListaRepuestos(NodoListaRepuestos*& lista_repuestos, RegistroRepuestos registro_archivo){
    NodoListaRepuestos* nuevo = new NodoListaRepuestos();
    nuevo->nodo_info = registro_archivo;
    nuevo->nodo_siguiente = NULL;

    if ( lista_repuestos == NULL ){
        lista_repuestos = nuevo;
    }
    else{
        NodoListaRepuestos* auxiliar = lista_repuestos;
        while ( auxiliar->nodo_siguiente != NULL ){
            auxiliar = auxiliar->nodo_siguiente;
        }
        auxiliar->nodo_siguiente = nuevo;
    }
}

void MostrarLista(NodoListaRepuestos* lista){
    NodoListaRepuestos* auxiliar = lista;
    int i = 1;
    while ( auxiliar != NULL ){
		cout << "El repuesto " << i << " "<< endl;
	/*	cout << auxiliar->nodo_info.modelo_pertenencia << endl;
        cout << auxiliar->nodo_info.stock << endl;
        cout << auxiliar->nodo_info.fecha_ultima_reposicion << endl;
        cout << auxiliar->nodo_info.precio_unitario << endl;
        cout << auxiliar->nodo_info.descripcion << endl;*/
        i = i + 1;
        auxiliar = auxiliar->nodo_siguiente;
    }
}

int main() {
    FILE* archivo_repuestos_desordenado = fopen("repuestos.dat", "r+b");
    RegistroRepuestos registro_archivo;


    NodoListaRepuestos* lista_repuestos = NULL;
    fread(&registro_archivo,sizeof(registro_archivo),1,archivo_repuestos_desordenado);
    while ( !feof(archivo_repuestos_desordenado) ){
        ArmarListaRepuestos(lista_repuestos, registro_archivo);
        fread(&registro_archivo,sizeof(registro_archivo),1,archivo_repuestos_desordenado);
    }

    MostrarLista(lista_repuestos);
    // TODO Ordenar lista por modelo_pertenencia y codigo_producto

}
