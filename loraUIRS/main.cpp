#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

std::ifstream ff;
std::ofstream res;
std::ofstream res0;
std::vector<long double> ff_vector;

std::vector<long double> Covariance(std::vector<long double> v);
void print(std::vector<long double> v);
void printintotxt(std::vector<long double> v);
std::vector<long double> getCov(long double t0, long double tk, long double dt);

int main()
{
    ff.open("FF_out.txt");
    if(ff.is_open()){
        std::string temp;
        while(std::getline(ff, temp)){
            ff_vector.push_back(std::stold(temp));
        }
        ff.close();
        print(ff_vector);
        print(Covariance(ff_vector));
        res.open("result.txt");
        printintotxt(Covariance(ff_vector));
        res.close();
        std::vector<long double> temp_v = getCov(0.0, 500.0, 0.01);
        res0.open("result0.txt");
        for(const auto elem : temp_v){
            res0<<elem<<"|"<<std::endl;
        }
    }else{
        std::cout<<"read file error"<<std::endl;
    }

    return 0;
}

std::vector<long double> getCov(long double t0, long double tk, long double dt){
    std::vector<long double> temp;
    while(t0 < tk){
        temp.push_back( 4*(1+7*std::abs(t0))*std::exp(-7*t0) );
        t0+=dt;
    }
    return temp;
}

void print(std::vector<long double> v){
    for(const auto elem : v){
        std::cout<<elem<<std::endl;
    }
}

void printintotxt(std::vector<long double> v){
    for(const auto elem : v){
        res<<elem<<"|"<<std::endl;
    }
}

std::vector<long double> Covariance(std::vector<long double> v){
    std::vector<long double> cov(v.size());
    for(unsigned int i = 0; i < v.size(); i++){
        cov[i] = 0;
        for(unsigned int j = 0; j < v.size() - i; j++){
            cov[i] += v[i+j]*v[j];
        }
        cov[i] /= v.size();
    }
    return cov;
}
