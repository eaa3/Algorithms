#include "vetor2D.h"

float grausToRad(float graus)
{
    return (graus*float(M_PI))/180.0f;
}
float radToGraus(float radianos)
{
    return (radianos*180.0f)/float(M_PI);
}

const Vetor2D Vetor2D::ZERO = Vetor2D(0,0);

Vetor2D::Vetor2D()
{
    this->x = 0;
    this->y = 0;

}

Vetor2D::Vetor2D(float x,float y)
{
    this->x = x;
    this->y = y;
}

Vetor2D::Vetor2D(float angle)
{
    (*this) = Vetor2D(cosf(grausToRad(angle)),-sinf(grausToRad(angle)));
}

Vetor2D::~Vetor2D()
{

}

void Vetor2D::operator*= (float k)
{
    this->x *= k;
    this->y *= k;
}
Vetor2D Vetor2D::operator* (float k)
{
    return Vetor2D(this->x*k,this->y*k);
}

void Vetor2D::operator/= (float k)
{
    this->x /= k;
    this->y /= k;
}

Vetor2D Vetor2D::operator/ (float k)
{
    return Vetor2D(this->x/k,this->y/k);
}

//Soma de vetores

void Vetor2D::operator+= (Vetor2D other)
{
    this->x += other.getX();
    this->y += other.getY();

}

Vetor2D Vetor2D::operator+ (Vetor2D other)
{
    return Vetor2D(this->x + other.getX(),this->y + other.getY());
}

void Vetor2D::operator-= (Vetor2D other)
{
    this->x -= other.getX();
    this->y -= other.getY();
}

Vetor2D Vetor2D::operator- (Vetor2D other)
{
    return Vetor2D( this->x - other.getX(), this->y - other.getY() );
}

//Sobrecarga para atribuição

void Vetor2D::operator= (Vetor2D other)
{
    this->x = other.getX();
    this->y = other.getY();
}

//Sobrecargas para comparação

bool Vetor2D::operator== (Vetor2D other)
{
    return ((this->x == other.getX()) && (this->y == other.getY()));
}

bool Vetor2D::operator!= (Vetor2D other)
{
    return ((this->x != other.getX()) || (this->y != other.getY()));
}

//Transformação linear rotacão

Vetor2D Vetor2D::rotate(float degrees)
{
    //convertendo para radianos
    degrees = grausToRad(degrees);

    return Vetor2D(this->x*cosf(degrees) - this->y*sinf(degrees),this->x*sinf(degrees) + this->y*cosf(degrees));
}


float Vetor2D::getNorma()
{
    return sqrt(this->prodInterno(*this));
}
void Vetor2D::setNorma(float norma)
{
    if(this->getNorma())
    {
        (*this) = this->normalizar()*norma;
    }
}

Vetor2D Vetor2D::normalizar()
{
    float size = this->getNorma();


    return Vetor2D(this->x/size,this->y/size);
}

Vetor2D Vetor2D::proj(Vetor2D other)
{

    return other*(this->prodInterno(other)/other.prodInterno(other));
}

float Vetor2D::prodInterno(Vetor2D other)
{
    return this->x*other.getX() + this->y*other.getY();
}



//Angulo entre this e outro vetor
float Vetor2D::angleBetween(Vetor2D other)
{
    return radToGraus(acos(this->prodInterno(other)/(this->getNorma()*other.getNorma())));
}

void Vetor2D::setAngle(float angle)
{
    float norma = this->getNorma();

    (*this) = Vetor2D(angle);

    if(norma){
        this->setNorma(norma);
    }
}
float Vetor2D::getAngle()
{
    return radToGraus(atan2f(this->y,this->x));
}

void Vetor2D::setX(float x)
{
    this->x = x;
}
float Vetor2D::getX()
{
    return this->x;
}

void Vetor2D::setY(float y)
{
    this->y = y;
}
float Vetor2D::getY()
{
    return this->y;
}

string Vetor2D::toString()
{
    stringstream cord;
    cord.precision(2);
    cord << std::fixed << "( " << this->x << " , " << this->y << " )";

    return cord.str();
}
