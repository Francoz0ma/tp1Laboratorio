#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED


void FECHA(int *,int *,int *);///PROTOTIPO PARA VALIDACION DE FECHA.
void Recuperarpaciente(int );

///////////////////////////////////////////////////
int BuscarDNIrestricciones(int *x,int *z){
FILE *p;
struct paciente paci;
struct fecha fe;

p=fopen("pacientes.dat","rb");
if(p==NULL){
    cout<<"ERROR de archivo"<<endl;
  exit(1);
}
while(fread(&paci,sizeof paci,1,p)==1){
if(paci.dni==*x&&paci.estado==false){
    *z=*x;
    *x=0;

}
else{
    if(paci.dni==*x&&paci.estado==true){
        return -1;
}
}
}
return *x;
}

struct paciente nuevopaciente(){

struct paciente paci;
struct fecha fe;
int punteroDNI;
int y,u;
char recuperar;

bool z=true;
while(z==true){
cout<<"DNI"<<endl;
cin>>punteroDNI;
BuscarDNIrestricciones(&punteroDNI,&y);

cout<<"punteroDNI vale:  "<<punteroDNI<<endl;
cout<<"y vale: "<<y<<endl;
if(punteroDNI>0){
    paci.dni=punteroDNI;
    z=false;
}
else {
        if(punteroDNI==0){
        cout<<"Paciente  dado de baja. ¿Recuperar? (S/N)"<<endl;
        cin>>recuperar;
        if(recuperar=='s'){
         Recuperarpaciente(y);
        }
        }
    else {
    cout<<"El paciente  ya existe en nuestros registros"<<endl;
    cout<<endl;
    cout<<"Volver a ingresar un DNI"<<endl;}
    }

}

cin.ignore();
z=true;
while(z==true){

cout<<"Apellidos"<<endl;
cin.getline(paci.apellidos,  50);
if(strlen(paci.apellidos)==0){
    cout<<"ERROR debe ingresar Apellido"<<endl;
}
else {
    z=false;
}
}


z=true;
while(z==true){
cout<<"Nombre"<<endl;
cin.getline(paci.nombres, 50);
if(strlen(paci.nombres)==0){
    cout<<"ERROR debe ingresar Nombre"<<endl;
}
else {
    z=false;
}
}

z=true;
while(z==true){
cout<<"Genero"<<endl;
cin>>paci.genero;
if(paci.genero=='f'||paci.genero=='m'||paci.genero=='o'){
    z=false;
}
else cout<<"Ingrese un genero correcto"<<endl;
}



int d,m,a;
FECHA(&d,&m,&a); /// FUNCION PARA RESTRICCION DE FECHA
 paci.fe.dia=d; ///
 paci.fe.mes=m; ///
 paci.fe.anio=a;



z=true;
while(z==true){
cout<<"Obra Social"<<endl;
cin>>paci.obraSocial;
if(paci.obraSocial>=1&&paci.obraSocial<=50){
    z=false;
}
else cout<<"Ingrese una obra social del rango de 1 a 50"<<endl;
}

return paci;

}


void listarpacientes(paciente paci,fecha fe){

if(paci.estado==true){

cout<<"DNI"<<endl;
cout<<paci.dni<<endl;
cout<<"Apellidos"<<endl;
cout<<paci.apellidos<<endl;
cout<<"Nombre"<<endl;
cout<<paci.nombres<<endl;
cout<<"Genero"<<endl;
cout<<paci.genero<<endl;
cout<<"Fecha de nacimiento"<<endl;
cout<<"DIA"<<endl;
cout<<paci.fe.dia<<endl;
cout<<"MES"<<endl;
cout<<paci.fe.mes<<endl;
cout<<"ANIO"<<endl;
cout<<paci.fe.anio<<endl;
cout<<"Obra Social"<<endl;
cout<<paci.obraSocial<<endl;


cout<<"*******************************************"<<endl;
}

}





/// FUNCIONES CON ARCHIVOS//////////////////////////////



void cargarnpaciente(){

FILE *p;

struct paciente paci;
struct fecha fe;

   p = fopen("pacientes.dat","ab");
    if(p==NULL){
        cout<<"ERROR de archivo"<<endl;
        exit(1);
    }
    paci=nuevopaciente();
    fwrite(&paci, sizeof paci,1,p);

    fclose(p);

}

///FUNCIONES DE ARCHIVO LLAMADAS POR MAIN ///////

void mostrarpaciente(){

FILE *pa;

struct paciente paci;
struct fecha fe;

   pa = fopen("pacientes.dat","rb");

    if(pa==NULL){
        cout<<"ERROR de archivo"<<endl;
        exit(1);
    }

   while(fread(&paci, sizeof paci,1,pa)==1){

    listarpacientes(paci,fe);


   }
    fclose(pa);



}




////PUNTO 3 DEL MENU DE PACIENTES (BUSCAR PACIENTE) //////////////////

void buscarpacientes(){

FILE *pac;

struct paciente paci;
struct fecha fe;

int buscarpa;

int validacion=1;

cout<<"Ingrese DNI: "<<endl;
cin>>buscarpa;

pac = fopen("pacientes.dat","rb");

if(pac==NULL){
    cout<<"ERROR de archivo "<<endl;
    exit(1);
}

while(fread(&paci,sizeof paci,1,pac)==1){
    if(buscarpa==paci.dni){
        listarpacientes(paci,fe);

        validacion=0;
    }
    cout<<endl;
}
if(validacion==1){
cout<<"No existe ese dni en la base de datos del hospital"<<endl;
}
fclose(pac);

}

/// PUNTO 2 MENU PACIENTE (MODIFICAR PACIENTE) ////////////////////



///PROTOTIPOS DE FUNCION

int buscarpamodificar(int );

struct paciente buscarregistropaciente(int );

bool grabarregistrodepaciente(struct paciente,int );

///



void modificarpaciente(){

struct paciente paci;
struct fecha fe;

int numdni;
int posicion;
int obrasocial;
bool x=true;

while(x==true){

cout<<"Ingrese el numero de DNI del paciente al cual quiere modificar la obra social"<<endl;
cin>>numdni;

posicion=buscarpamodificar(numdni);

if(posicion==-1){
    cout<<"ERROR no existe ese numero de DNI en la base de datos del hospital"<<endl;
    cout<<"VUELVA A INGRESAR UN DNI"<<endl;
}
else{

   x=false;

}
}

paci=buscarregistropaciente(posicion);


bool n1=true;
while(n1==true){
cout<<"INGRESE EL NUEVO NUMERO DE OBRA SOCIAL"<<endl;
cin>>obrasocial;
if(obrasocial>=1&&obrasocial<=50){
    n1=false;}
    else cout<<"Ingrese una obra social del rango de  1 a 50"<<endl;}


paci.obraSocial=obrasocial;

grabarregistrodepaciente(paci,posicion);

}




int buscarpamodificar(int numdni){

FILE *mod;
int posicion=0;
struct paciente paci;
struct fecha fe;

mod = fopen("pacientes.dat","rb");
if(mod==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}
while(fread(&paci,sizeof paci,1,mod)==1){

if(paci.dni==numdni){
        fclose(mod);
    return posicion;
}
posicion++;
}
fclose(mod);
return -1;
}



struct paciente buscarregistropaciente(int posicion){

FILE *mm;

struct paciente paci;
struct fecha fe;

mm = fopen("pacientes.dat","rb");

if (mm==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

fseek(mm,posicion*sizeof(struct paciente),0);

fread(&paci,sizeof paci,1,mm);

fclose(mm);

    return paci;

}

///la funcion de abajo es la que por fin modifica el numero de la obra social.
bool grabarregistrodepaciente(struct paciente paci,int posicion){

FILE *k;

bool nuevonum;

k=fopen("pacientes.dat","rb+");
if(k==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

fseek(k,posicion*sizeof paci,0);

nuevonum=fwrite(&paci,sizeof paci,1,k);

fclose(k);

return nuevonum;
}

///PUNTO 5 DEL MENU PACIENTES (ELIMINAR PACIENTES)////////

void eliminarpaciente(){

struct paciente paci;
struct fecha fe;
int dninum;
int posicion;
bool x=true;

while(x==true){
cout<<"Ingresar dni del paciente a eliminar"<<endl;
cin>>dninum;

posicion=buscarpamodificar(dninum);

if(posicion==-1){
    cout<<"Error el dni ingresado no existe vuelva a ingresar un dni"<<endl;
}
else {
    x=false;
}
}


paci=buscarregistropaciente(posicion);

paci.estado=false;


if(grabarregistrodepaciente(paci,posicion)){
    cout<<"Registro de paciente eliminado"<<endl;
}
else {
    cout<<"No se pudo eliminar el registro"<<endl;
}
}




void Recuperarpaciente(int punteroDNI){

struct paciente paci;
struct fecha fe;

int posicion;
bool x=true;

while(x==true){

posicion=buscarpamodificar(punteroDNI);

if(posicion==-1){
    cout<<"Error el dni ingresado no existe vuelva a ingresar un dni"<<endl;
}
else {
    x=false;
}
}


paci=buscarregistropaciente(posicion);

paci.estado=true;


if(grabarregistrodepaciente(paci,posicion)){
    cout<<"Registro de paciente recuperado"<<endl;
}
else {
    cout<<"No se pudo recuperar el paciente"<<endl;
}
}


///       BACKUP    //////////////////////////////////////////////////////////////////////////

void backupPacientes(){

FILE *puntero1,*puntero2;

struct paciente paci;
struct fecha fe;

puntero1=fopen("pacientes.dat","rb");
if(puntero1==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

puntero2=fopen("pacientes.bkp","wb");
if(puntero2==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

while(fread(&paci,sizeof(paciente),1,puntero1)==1){

    fwrite(&paci,sizeof(paciente),1,puntero2);

}

fclose(puntero2);
fclose(puntero1);
}



///   RESTAURAR BACKUP    //////////////////////////////////////////////////////////////////

void RestaurarBackupPacientes(){

FILE *puntero1,*puntero2;

struct paciente paci;
struct fecha fe;

puntero1=fopen("pacientes.bkp","rb");
if(puntero1==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

puntero2=fopen("pacientes.dat","wb");
if(puntero2==NULL){
    cout<<"ERROR de archivo"<<endl;
    exit(1);
}

while(fread(&paci,sizeof(paciente),1,puntero1)==1){

    fwrite(&paci,sizeof(paciente),1,puntero2);

}

fclose(puntero2);
fclose(puntero1);
}


#endif // PACIENTES_H_INCLUDED
