// This line represents the preprocesseur directive. Its role is to load C ++ features to do certain actions
#include <iostream>
#include <cmath>
#include <iomanip>

/* This line is very important it permits to create our work space. The names space "std" is one of the most in C++.
It corresponds to the "std" library.*/
using namespace std;

// Computate the present value
// N is the number of full years until maturity
// d is the year fraction until next coupon payment
double PV(double futureValue, double couponRate, double r, int N,double d)
{
    double temp_PV=0;
    double coupon=couponRate*futureValue;
// The loop "for" is usefull to group the initialisation, the condition and the incrementaiton process
    for(int i=0;i<=N;i++)
    {
        temp_PV += coupon*pow(1+r,-i-d);
    }

    temp_PV += + futureValue*pow(1+r,-N-d);

    return temp_PV;
}

// Compute the Yield-to-Maturity(YTM) by iteration : Secant method
double iterationYTM(double futureValue,double couponRate,double priceValue,int N,double d,double i0=0.00001, double i1= 10)
{
    //Here, we add an admissible intervall for the value of d
    while (d > 1 || d < 0)
    {
        cout << "Please enter a value between 0 and 1 for the next coupon payment : " << endl;
        cin >> d;
    }

    //Here, we add an admissible intervall for the value of the future value
    while (futureValue < 0)
    {
        cout << " Please enter a positive value for the future value : " << endl;
        cin >> futureValue;
    }

    //Here, we add an admissible intervall for the value of the present value
    while (priceValue < 0)
    {
        cout << " Please enter a positive value for the present value : " << endl;
        cin >> priceValue;
    }

    //Here, we add an admissible intervall for the value of the present value
    while (N < 0 )
    {
        cout << " Please enter a positive integer for the years before the maturity of your bond" << endl;
        cin >> N;
    }







    //number of iteration
    const int MaxIter=50000;
    //error limit
    double epsilon = 0.0000001;
    //temporary iterative values
    double midP=0.0,midCdif;
    //Algorithm interval
    double lowCdif=priceValue- PV(futureValue, couponRate, i0, N,d);
    double highCdif=priceValue- PV(futureValue, couponRate, i1, N,d);

    if(priceValue == futureValue)
    {
        return couponRate;
    }

    else if(couponRate == 0)
    {
        return  pow((futureValue/priceValue),1/N+d)-1;
    }
    if (lowCdif*highCdif>0)
        return -1;
    else
        for(int i=0;i<=MaxIter;i++){
            midP=(i0+i1)/2.0;
            midCdif=priceValue- PV(futureValue, couponRate, midP, N,d);
            if(abs(midCdif)<epsilon) return midP;
            else
            {
                if (midCdif>0) i1=midP;
                else i0=midP;
            }

        }

    return midP;
}


// it's not the function but only the way to check if our function run.
int main() {

    double couponRate, coupon, d, futureValue, priceValue;
    int N;
    cout << "Hello and welcome in your financial management automat" << endl;
    //First requirements to manage your investment
    cout << " Please, can you enter your bond characteristics" << endl;
    cout << " The coupon value" << ", The next coupon payment" << ", The future value" << ", The present value" << " and the number of Year before maturity" << endl;
    //The user presents his bond
    cin >> coupon >> d >> futureValue >> priceValue >> N;


    //With these information, we compute the coupon rate.
    couponRate=coupon/futureValue;

        double YTM=iterationYTM(futureValue,couponRate,priceValue,N,d);
        double YTMpourcentage;
        YTMpourcentage = YTM*100;
        cout<<"To conclude, your YTM="<< setprecision(3) <<YTMpourcentage<<"%"<<endl;
    //We summarize all the information we have on this bond
    cout <<"Finally, we have a coupon rate = "<< couponRate <<", a coupon value = "<< coupon <<", the next coupon payment in "<< d <<" years"<<", a future value = "<< futureValue <<", a present value = "<< priceValue <<" and your bond comes to maturity in "<< N << " years" << endl;

    return 0;

}