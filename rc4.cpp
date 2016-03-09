#include <iostream>
#include <istream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

vector<int> spritz(vector<int> s_, int tam){
    int i=0;
    int j=0;
    int w=5;
    int k=0;
    int z=0;
    vector<int> aux;
    aux.resize(tam);
    
    for (int x = 0; x < tam; x++){
        i = (i + w) % 256;
        j = (k + s_[j + s_[i]]) % 256;
        k = (i + k + s_[j]) % 256;
        
        //Intercambiando...
        int auxiliar = 0;
        auxiliar = s_[i];
        s_[i] = s_[j];
        s_[j] = auxiliar;
        
        z = (s_[j + s_[i + s_[z + k]]]) % 256;
        aux[x] = s_[z];
    }
    return aux;
}

vector<int> generador_sec(vector<int> s_, int tam){
    
    int i = 0;
    int f = 0;
    int t = 0;
    vector<int> aux;
    aux.resize(tam);
    
    for(int x = 0; x<tam; x++){
        i = (i + 1) % 256;
        f = (f + s_[i]) % 256;
        
        //Intercambiando...
        int auxiliar = 0;
        auxiliar = s_[i];
        s_[i] = s_[f];
        s_[f] = auxiliar;
        
        t = (s_[i] + s_[f]) % 256;
        aux[x] = s_[t];
    }
    return aux;
}

vector<int> separar(char* semilla_){
    int i=0;
    vector<int> vec_aux;
    char* mensaje;
    mensaje = strtok (semilla_," ,");
    while (mensaje != NULL)
    {
        vec_aux.resize(vec_aux.size()+1);
        vec_aux[i] = atoi(mensaje);
        mensaje = strtok (NULL, " ,");
        i++;
    }    
    return vec_aux;
}


int main(){
    int f, aux;
    char* semilla;
    semilla = new char[256];
    char* texto;
    texto = new char[256];
    vector<int> s;
    vector<int> k;
    vector<int> s_c;
    vector<int> semilla_c;
    vector<int> texto_o;
    vector<int> texto_cifrado;
    s.resize(256);
    k.resize(256);
    
    //-------------------------------------------------------------------//
   
    //Rellenamos el vector S de 0 a 255.
    for (int i=0; i<=255; i++){
        s[i] = i;
    }
    cout << endl;
    
    cout << "Introduzca la semilla de clave: " << endl;
    cin.getline(semilla,256);
    cout << "Introduzca el texto original: " << endl;
    cin.getline(texto,256);
    
    //----------------------------------------------
    //Separamos el texto introducido por ','.
    //----------------------------------------------
    
    semilla_c = separar(semilla);
    texto_o = separar(texto);
    cout << endl;
    
    //Imprimimos la semilla y el texto introducida.
    cout << "Semilla: " << endl;
    for(int i=0; i<semilla_c.size(); i++){
        cout << semilla_c[i];
    }
    cout << endl;
    cout << "Texto: " << endl;
    for(int i=0; i<semilla_c.size(); i++){
        cout << texto_o[i];
    }    
    cout << endl;
    
    //----------------------------------------------
    //Rellenamos el vector k con la plantilla.
    //----------------------------------------------

    int i=0;
    for (int j=0; j<=k.size()-1; j++){
        if(i < semilla_c.size()){
            k[j] = semilla_c[i];
            i++;
        }
        else{
            i=0;
            k[j] = semilla_c[i];
            i++;
        }
    }
    cout << endl;
    cout << "Vector S inicializado: " << endl;
    for (int i=0; i<=255; i++){
        cout <<  s[i] << " ";
    }
    cout << endl << endl;
    cout << "Vector semilla: " << endl;
    for (int i=0; i<=255; i++){
        cout << k[i] << " ";
    }
    cout << endl;
    
    //----------------------------------------------
    // Inicialización, KSA.
    //----------------------------------------------
    /*for (int i=0; i<s.size(); i++){
        // s[i] = i; el vector s ya está rellenado de 0 a 255
        k[i] = s[i % semilla_c.size()]; k ya contiene la semilla hasta su tamaño
    }*/
    f=0;
    aux = 0;
    for(int i=0;i<256;i++){
        f = (f + s[i] + k[i]) % 256;
        aux = s[i];
        s[i] = s[f];
        s[f] = aux;
    }
    cout << endl;
    cout << "Vector S (KSA): " << endl;
    for (int i=0; i<=255; i++){
        cout << s[i] << " ";
    }
    cout << endl;
    
    //----------------------------------------------
    // Generación de secuencia cifrante. PRGA
    //----------------------------------------------

    s_c.resize(texto_o.size());
    s_c = generador_sec(s, texto_o.size());
    cout << endl;
    cout << "Vector con Secuencia Cifrante (PRGA): " << endl;
    for (int i=0; i<s_c.size(); i++){
        cout << s_c[i] << " ";
    }
    cout << endl;
    
    //----------------------------------------------
    // XOR
    //----------------------------------------------
    
    texto_cifrado.resize(s_c.size());
    for (int i=0; i<s_c.size(); i++){
        texto_cifrado[i] = s_c[i] ^ texto_o[i];
    }
    cout << endl;
    cout << "TEXTO CIFRADO: " << endl;
    for (int i=0; i<s_c.size(); i++){
        cout << texto_cifrado[i] << " ";
    }
    cout << endl;
    
    
    //----------------------------------------------
    // Modificación Spritz
    //----------------------------------------------
    
    vector<int> texto_spritz;
    //texto_spritz.resize(s_c.size());
    
    texto_spritz = spritz(s, texto_o.size());
    
    cout << endl;
    cout << "Vector con Spritz: " << endl;
    for (int i=0; i<s_c.size(); i++){
        cout << texto_spritz[i] << " ";
    }
    cout << endl;
    
    //CLAVE (decimal): 01 35 69 103 137 171 205 239
    
    //RESULTADO (decimal): 116 148 194 231 16 75 8 121 
    
    
    return 0;
}