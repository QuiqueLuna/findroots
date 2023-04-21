#include<iostream>
#include<vector>
#include<cmath>
#define EPSILON 0.00001
using namespace std;

vector<double>roots;

//Original Function
double func(double a, double b, double c, double d, double x){
    return a*x*x*x + b*x*x + c*x + d;
}
//Derivated Function
double derivFunc(double a, double b, double x){
    return 3*a*x*x + 2*b*x + x;
}
 
//Finds one root of the cubic polynomial
double newtonRaphson(double a, double b, double c, double d, double x){
    double h = func(a,b,c,d,x) / derivFunc(a,b,x);
    while (abs(h) >= EPSILON){
        h = func(a,b,c,d,x)/derivFunc(a,b,x);
        x = x - h;
    }
    return x;
}

//Obtain coefficients of cuadratic polynomial 
pair<double,double> division(double a, double b, double c, double r){
    double b2 = r*a+b;
    double c2 = b2*r+c;
    return {b2,c2};
}

//Obtain roots of second degree polynomial
void quadraticFormula(double a, double b, double c){
    double discriminant = b*b - 4*a*c;
    if(discriminant>0){
        double root2 = (-b+sqrt(discriminant))/(2*a);
        double root3 = (-b-sqrt(discriminant))/(2*a);
        roots.push_back(root2);
        roots.push_back(root3);
    }else if(discriminant==0){
        double root2 = (-b+sqrt(discriminant))/(2*a);
        roots.push_back(root2);
    }
}

//Verifies the cubic polynomial, and proceeds to obtain the first root with newton 
//method,factorize the root and finally solve the second degree polynomial
void findCubicRoots(double a, double b, double c, double d){
    if(a==0){
        if(b==0){
            if(c!=0)roots.push_back(d==0 ? 0:(-d/c));
        }else{
            quadraticFormula(b,c,d);
        }
    }else{
        double x0 = -20;
        double root1 = newtonRaphson(a,b,c,d,x0);
        roots.push_back(root1);
        pair<double,double> degree2 = division(a,b,c,root1);
        quadraticFormula(a,degree2.first,degree2.second);

    }
    cout<<"{";
    for(int i=0;i<roots.size();i++){
        cout<<roots[i]<<(i==((int)roots.size()-1) ? "":", ");
    }
    cout<<"}\n";
}

int main(int argc, char *argv[]){
    if(argc!=5){
        return 0;
    }

    double a=atof(argv[1]),b=atof(argv[2]),c=atof(argv[3]),d=atof(argv[4]);
    findCubicRoots(a,b,c,d);
    return 0;
}