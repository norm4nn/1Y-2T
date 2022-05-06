#include <stdio.h>
#include <stdlib.h>
#define TWO_DICE_SUM 11

// Calculates arithmetic mean and variance of numbers from n-element array v[]
// for n = 0: mean = variance = 0
void mean_variance(const double v[], double *mean, double *variance, int n) {
    *mean = 0;
    for(int i=0;i<n;++i) {
    *mean += v[i];
    }
    *mean /= n;
    for(int i=0;i<n;++i) {
    *variance += (v[i]-(*mean))*(v[i]-(*mean));
    }
    *variance /= n;

}

// Fill n-element array v[] with Bernoulli sample (binary values)
void bernoulli_gen(int v[], int bernoulli_percentage, int n) {

    for(int i=0;i<n;++i) {
        int val = rand() % 100;
        if (val < bernoulli_percentage) v[i] = 1;
        else    v[i] = 0;
    }
}

// Calculate pmf (probability mass function) of discrete random variable
// (percentage values from [0, 100]).
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void pmf(double v[], int trials) {
    for(int i=0;i < trials;++i) {
    int d1 = rand()%6+1;
    int d2 = rand()%6+1;
    ++v[d1+d2-2];
    }

    for(int i=0;i < TWO_DICE_SUM;++i) {
    v[i] /= trials;
    v[i] *= 100;
    }
}

// Calculates the cumulative distribution function (cdf) for 'trials' numbers
// (percentage values from [0, 100]).
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void calculate_cdf(double cdf[], int trials){
    for(int i=0;i < trials;++i) {
        int d1 = rand()%6+1;
        int d2 = rand()%6+1;
        for(int i=d1+d2-2;i<=TWO_DICE_SUM;++i)     ++cdf[i];
    }

    for(int i=0;i < TWO_DICE_SUM;++i) {
        cdf[i] /= trials;
        cdf[i] *= 100;
    }

}

// Simulate Monty-Hall problem
// input: n - number of trials
// output: wins - number od wins if door switched
// output: win_probability - probability of win if door switched
void monty_hall(int *wins, double *win_probability, int n) {
    *wins = 0;
    for(int i = 0; i < n; i++) {
        int prize = rand() % 3; // the winning door
        int choice = rand() % 3; // the first choice door
        int reveal; // the door revealed by the host (neither your choice nor the prize door)
        // set reveal
        do {
            reveal = rand() % 3;
        } while (reveal == choice || reveal == prize);
        int remaining = 0; // your second choice (if you switch)
        if (remaining == reveal || remaining == choice) remaining++;
        if(remaining == reveal || remaining == choice) remaining++;
        if (prize == remaining) ++(*wins); // you win if you switched
    }
    *win_probability = (double)(*wins) * 100.0 / n;
}

// read double vector of size n
void read_vector(double v[], int n){
    for(int i=0;i<n;++i) scanf("%lf",&v[i]);
}

// print double vector of size n (with 2 figures after the decimal point)
void print_vector(const double v[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%.2f ", v[i]);
    }
    printf("\n");
}

// print integer vector
void print_int_vector(const int v[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do, len, seed, bernoulli_percentage, m_h_wins, i_tab[100];
    double arithmetic_mean, variance, m_h_probability, d_tab[100] = { 0 };
    scanf("%d", &to_do);

    if(to_do > 1) {
        scanf("%d",&seed);
        srand((unsigned)seed);
    }

    switch (to_do) {
        case 1: // mean_variance
            arithmetic_mean = 0.0;
            variance = 0.0;
            scanf("%d", &len);
            read_vector(d_tab, len);
            mean_variance(d_tab, &arithmetic_mean, &variance, len);
            printf("%.2f %.2f\n", arithmetic_mean, variance);
            break;
        case 2: // bernoulli_gen
            scanf("%d", &len);
            scanf("%d", &bernoulli_percentage);
            bernoulli_gen(i_tab, bernoulli_percentage, len);
            print_int_vector(i_tab, len);
            break;
        case 3: // pmf
            scanf("%d", &len);
            pmf(d_tab, len);
            print_vector(d_tab, TWO_DICE_SUM);
            break;
        case 4: // calculate_cdf
            scanf("%d", &len);
            calculate_cdf(d_tab, len);
            print_vector(d_tab, TWO_DICE_SUM);
            break;
        case 5: // monty_hall
            scanf("%d", &len);
            monty_hall(&m_h_wins, &m_h_probability, len);
            printf("%d %.2f %d %.2f\n", m_h_wins, m_h_probability,
                   len - m_h_wins, 100.0 - m_h_probability);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}
