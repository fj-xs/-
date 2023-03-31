#include <iostream>
#include <cmath>
#ifndef COMPLEX
#define COMPLEX
using namespace std;
class Complex{
public:  
    Complex(double real = 0.0, double imag = 0.0): m_real(real), m_imag(imag){ }
public:  
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);
    friend Complex operator*(const Complex &c1, const Complex &c2);
    friend Complex operator/(const Complex &c1, const Complex &c2);
    friend bool operator> (const Complex &c1, const Complex &c2);
    friend bool operator< (const Complex &c1, const Complex &c2);
    friend bool operator==(const Complex &c1, const Complex &c2);
    friend bool operator!=(const Complex &c1, const Complex &c2);
    Complex & operator+=(const Complex &c);
    Complex & operator-=(const Complex &c);
    Complex & operator*=(const Complex &c);
    Complex & operator/=(const Complex &c);
     void display ();
     double read_Real (double r);
     double read_Imaginary (double i);
     double read_modulus();
public:  
    double real() const{ return m_real; }
    double imag() const{ return m_imag; }
    double modulus() const{ return m_modulus; } 
    double m_real;  
    double m_imag;  
    double m_modulus;  
};

Complex operator+(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}

Complex operator-(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}

Complex operator*(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}

Complex operator/(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = (c1.m_real*c2.m_real + c1.m_imag*c2.m_imag) / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    c.m_imag = (c1.m_imag*c2.m_real - c1.m_real*c2.m_imag) / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    return c;
}

bool operator==(const Complex &c1, const Complex &c2){
    if( c1.m_real == c2.m_real && c1.m_imag == c2.m_imag ){
        return true;
    }else{
        return false;
    }
}

bool operator>(const Complex &c1, const Complex &c2){
    if( c1.m_modulus > c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator>(const Complex &c1, double m){
    if( c1.m_modulus > m*m){
        return true;
    }else{
        return false;
    }
}
bool operator<(const Complex &c1, const Complex &c2){
    if(c1.m_modulus < c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator<(const Complex &c1, double m){
    if(c1.m_modulus < m*m ){
        return true;
    }else{
        return false;
    }
}
bool operator<=(const Complex &c1, const Complex &c2){
    if(c1.m_modulus <= c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator<=(const Complex &c1, double m){
    if(c1.m_modulus <= m*m ){
        return true;
    }else{
        return false;
    }
}
bool operator>=(const Complex &c1, double m){
    if(c1.m_modulus >= m*m ){
        return true;
    }else{
        return false;
    }
}

bool operator!=(const Complex &c1, const Complex &c2){
    if( c1.m_real != c2.m_real || c1.m_imag != c2.m_imag ){
        return true;
    }else{
        return false;
    }
}

Complex & Complex::operator+=(const Complex &c){
    this->m_real += c.m_real;
    this->m_imag += c.m_imag;
    return *this;
}

Complex & Complex::operator-=(const Complex &c){
    this->m_real -= c.m_real;
    this->m_imag -= c.m_imag;
    return *this;
}

Complex & Complex::operator*=(const Complex &c){
    this->m_real = this->m_real * c.m_real - this->m_imag * c.m_imag;
    this->m_imag = this->m_imag * c.m_real + this->m_real * c.m_imag;
    return *this;
}

Complex & Complex::operator/=(const Complex &c){
    this->m_real = (this->m_real*c.m_real + this->m_imag*c.m_imag) / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    this->m_imag = (this->m_imag*c.m_real - this->m_real*c.m_imag) / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    return *this;
}

void Complex::display (){
	if ( m_real != 0 ){
		if  ( m_imag > 0 )     cout << m_real << "+" << m_imag << "i" << " "; 
		else if (m_imag == 0)  cout << m_real << " "<< endl;
		else                   cout << m_real << m_imag << "i" << " ";
	} 
	else if ( m_real ==0 && m_imag ==0) cout << "0 " <<endl;
	else                                cout << m_imag << "i " << endl; 
}

double Complex::read_Real (double r){
    m_real = r;		
}
double Complex::read_Imaginary (double i){
    m_imag = i;		
}
double Complex::read_modulus(){
	m_modulus = m_imag * m_imag + m_real*m_real;
}
#endif
