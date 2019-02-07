#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct fraction
{
    double numerator;
    double denominator;
};
typedef struct fraction fraction;

fraction egypt(fraction*,int,int);
double gcd(double,double);

fraction egypt(fraction *f,int count,int total)
{

    int i;
    double cd,lcm;
    fraction temp = f[total];

    for(i = 1 + total; i < total + count; i++)
    {
        lcm = (temp.denominator * f[i].denominator) / gcd(temp.denominator,f[i].denominator);

        temp.numerator = temp.numerator * (lcm / temp.denominator) + f[i].numerator * (lcm / f[i].denominator);
        temp.denominator = lcm;

        cd = gcd(temp.numerator,temp.denominator);

        temp.numerator /= cd;
        temp.denominator /= cd;
    }

    return temp;
}

double gcd(double a,double b)
{
    if(a == 0)
        return b;
    else
        return gcd(fmod(b,a),a);
}

int main()
{
    int i,j,instances,index,*temp,flag = 0,total = 0;
    fraction *frac,*output;

    //printf("\nEnter the instances: \n");
    scanf("%d",&instances);

    output = calloc(instances,sizeof(fraction));
    frac = calloc(1,sizeof(fraction));
    temp = calloc(instances,sizeof(int));

    if(!output || !frac || !temp)
    {
        printf("\nError in allocating memory !!! \n");

        free(frac);
        free(output);
        free(temp);

        exit(0);
    }

    for (j = 0; j < instances; j++)
    {
        //printf("\nEnter the number of fractions to be inputed: \n");
        scanf("%d",&temp[j]);

        frac = realloc(frac,(temp[j] + total)*sizeof(fraction));

        if(frac == NULL)
        {
            printf("\nError in reallocation of memory !!! \n");

            free(frac);
            free(output);
            free(temp);

            exit(0);
        }

        for(i = 0 + total; i < temp[j] + total; i++)
        {
            frac[i].numerator = 1;
            //printf("\nEnter the denominator: \n");
            scanf("%lf",&frac[i].denominator);
        }
        if(temp[j] > 1)
            output[j] = egypt(frac,temp[j],total);
        else
            output[j] = frac[total + temp[j] - 1];

        total += temp[j];
    }

    for(j = 0; j < instances; j++)
    {
        for(i = 0; i < temp[j]; i++)
        {
            index = i + flag;
            if(i == temp[j] - 1)
                printf(" %0.0lf / %0.0lf = %0.0lf / %0.0lf",frac[index].numerator,frac[index].denominator,output[j].numerator,output[j].denominator);
            else
                printf(" %0.0lf / %0.0lf +",frac[index].numerator,frac[index].denominator);
        }
        printf("\n");
        flag += temp[j];
    }

    free(temp);
    free(frac);
    free(output);

    return 0;
}
