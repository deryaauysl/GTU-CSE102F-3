
// parse kismini dogru yapamamisim, strtok ile tokenize edip aldigim katsayi us degerlerini falan bir arraye
// atamam gerekiyormus. bu eksik. buradaki kodda da coeff'leri overwrite ediyorum bu yuzden yanlis hesaplama yapiyor.

#include <stdio.h>
#include <string.h>
#include <math.h>

int readExponent(char *polynomialString, int *i)
{
    int exponent = 1;

    if (polynomialString[*i] == '^')
    {
        (*i)++;
        sscanf(&polynomialString[*i], "%d", &exponent);
        printf("exponent is () ; %d \n", exponent);
    }
    return exponent;
}
int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int digit_num(int number)
{

    if (number == 0)
        return 1;

    int counter = 0;

    while (number > 0)
    {
        number /= 10;
        counter++;
    }
    return counter;
}

double evaluatePolynomial(char *polynomialString, double x_val, double y_val)
{
    double result = 0.0;
    int i = 0;
    int is_first_digit = 0;
    int x_exponent = 1, y_exponent = 1;
    double coeff = 1.0; // coefficient
    int sign = 1;
    int num;
    int counter = 0;

    for (int i = 0; polynomialString[i] != '\0'; i++)
    {
        // printf("karakter >>> %c\n", polynomialString[i]);

        if (polynomialString[i] == '+')
        {
            sign = 1;
            printf("sign is positive\n");
            i++;
        }

        if (polynomialString[i] == '-')
        {
            sign = -1;
            printf("sign is negative\n");
            i++;
        }

        while (polynomialString[i] != '+' && polynomialString[i] != '-' && polynomialString[i] != ' ')
        {

            if ((polynomialString[i] == 'x') && (polynomialString[i++] == '^'))
            {
                x_exponent = readExponent(polynomialString, &i);
                counter = digit_num(num);
                i += counter;
                counter = 0;
            }
            else if ((polynomialString[i] == 'x') && (polynomialString[i++] != '^'))
            {
                i++;
                x_exponent = 1;
                coeff = 1.0; // Set the coefficient of x to 1
            }
            else if ((polynomialString[i] == 'y') && (polynomialString[i++] == '^'))
            {
                y_exponent = readExponent(polynomialString, &i);
                counter = digit_num(num);
                i += counter;
                counter = 0;
            }
            else if ((polynomialString[i] == 'y') && (polynomialString[i++] != '^'))
            {
                i++;
                y_exponent = 1;
                coeff = 1.0; // Set the coefficient of x to 1
            }
            else
            {
                sscanf(&polynomialString[i], "%lf", &coeff);
                coeff = coeff * sign;
                counter = digit_num(coeff);
                i += counter;
                // printf("katnumbernin basamak numbersi %d\n", counter);
                counter = 0;
                counter++;
            }
        }

        // Sonuç hesaplama
        result += coeff * pow(x_val, x_exponent) * pow(y_val, y_exponent);
        // printf("counter :%d", counter);

        // Reset the exponents for the next monomial
        x_exponent = 1;
        y_exponent = 1;
        // Initialize coefficients for the next monomial
        coeff = 1.0;
        coeff = 1.0;

        if (polynomialString[i] == ' ')
        {
            i++;      // Boşluk karakteri geç
            continue; // Döngünün bir sonraki iterasyonuna geç
        }
    }

    return result;
}

int main()
{
    FILE *valuesfile, *polynomfile, *evofile;
    double x, y, evaluatedpolynom;

    char line_p[1000];

    polynomfile = fopen("polynomials.txt", "r");
    evofile = fopen("evaluations.txt", "w");

    while (fgets(line_p, sizeof(line_p), polynomfile) != NULL)
    {
        valuesfile = fopen("values.txt", "r");

        if (valuesfile == NULL)
        {
            printf(" value dosyasi acilamadi");
        }

        while (fscanf(valuesfile, "%lf %lf", &x, &y) == 2)
        {
            evaluatedpolynom = evaluatePolynomial(line_p, x, y);
            fprintf(evofile, "%.2f ", evaluatedpolynom);
        }

        fprintf(evofile, "\n");
        fclose(valuesfile);
    }

    fclose(polynomfile);
    fclose(evofile);

    return 0;
}
