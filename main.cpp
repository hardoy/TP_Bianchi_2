// Algoritmos y Estructuras de Datos
// Trabajo Práctico Número Dos
// Alumno: Antonio Agustín Hardoy
// Curso: K1091
// Legajo: 156.290-3

#include <iostream>

using namespace std;

struct RegistroRepuestos {
    int codigo_producto;
    int modelo_pertenencia;
    int stock;
    int fecha_ultima_reposicion;
    double precio_unitario;
    char descripcion[20];
};

struct Info {
    int codigo_producto;
    int modelo_pertenencia;
    int posicion;
};

struct NodoRepuestos {
    Info info;
    NodoRepuestos * siguiente;
};

void InstertarOrdenado(NodoRepuestos *&, RegistroRepuestos, int);
void ArmarArchivoOrdenado(NodoRepuestos*, FILE*, RegistroRepuestos);
void EliminarLista(NodoRepuestos*&);

int main() {
    FILE* archivo_repuestos_desordenado = fopen("repuestos.dat", "r+b");
    RegistroRepuestos registro_archivo;
    int posicion = 0;
    NodoRepuestos* lista_repuestos = NULL;

    fread(&registro_archivo,sizeof(registro_archivo),1,archivo_repuestos_desordenado);
    while ( !feof(archivo_repuestos_desordenado) ){
        InstertarOrdenado(lista_repuestos, registro_archivo, posicion);
        fread(&registro_archivo,sizeof(registro_archivo),1,archivo_repuestos_desordenado);
        posicion = posicion + 1;
    }

    ArmarArchivoOrdenado(lista_repuestos, archivo_repuestos_desordenado, registro_archivo);

    fclose(archivo_repuestos_desordenado);

    EliminarLista(lista_repuestos);

    return 0;
}

void InstertarOrdenado(NodoRepuestos *& lista, RegistroRepuestos registro_archivo, int posicion){
    NodoRepuestos * nuevo = new NodoRepuestos();
    nuevo->info.codigo_producto = registro_archivo.codigo_producto;
    nuevo->info.modelo_pertenencia = registro_archivo.modelo_pertenencia;
    nuevo->info.posicion = posicion;
    nuevo->siguiente = NULL;
    NodoRepuestos * auxiliar = lista;
    NodoRepuestos * anterior = NULL;

    while( auxiliar != NULL && auxiliar->info.modelo_pertenencia < nuevo->info.modelo_pertenencia ){
        anterior = auxiliar;
        auxiliar = auxiliar->siguiente;
    }
    while( auxiliar != NULL && auxiliar->info.codigo_producto <= nuevo->info.codigo_producto &&
            nuevo->info.modelo_pertenencia == auxiliar->info.modelo_pertenencia ){
        anterior = auxiliar;
        auxiliar = auxiliar->siguiente;
    }
    if( anterior == NULL ){
        lista = nuevo;
    }
    else{
        anterior->siguiente = nuevo;
    }
    nuevo->siguiente = auxiliar;
}

void ArmarArchivoOrdenado(NodoRepuestos* lista, FILE* archivo, RegistroRepuestos registro){
    FILE* archivo_repuestos_ordenado = fopen("repuestos_ordenado.dat", "w+b");

    NodoRepuestos* auxiliar = lista;
    while (auxiliar != NULL ){
        fseek(archivo, auxiliar->info.posicion * sizeof(RegistroRepuestos), SEEK_SET);
        fread(&registro,sizeof(registro),1,archivo);
        fwrite(&registro, sizeof(RegistroRepuestos), 1, archivo_repuestos_ordenado);
        auxiliar = auxiliar->siguiente;
    }
    fclose(archivo_repuestos_ordenado);
}

void EliminarLista(NodoRepuestos*& lista){

    NodoRepuestos* auxiliar;

    while ( lista != NULL ){
        auxiliar = lista;
        lista = lista->siguiente;
        delete auxiliar;
    }

}