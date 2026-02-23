#include<stdio.h>
#include<math.h>

// function declarations

void primecheck(int n);
void palindromecheck(int n);
void armstrongcheck(int n);
void factorialcheck(int n);
void fibonaccicheck(int n);


int main() {

    int choice, num;

    do{
        printf("\n===== NUMBER UTILITY TOOLKIT =====\n");
        printf("1. Prime Number Check\n");
        printf("2. Palindrome Check\n");
        printf("3. Armstrong Number Check\n");
        printf("4. Factorial Check\n");
        printf("5. Fibonacci Check\n");
        printf("6. Exit\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 5){
            printf("Enter a number : ");
            scanf("%d", &num);

        }

        switch(choice){
            case 1:
                primecheck(num);
                break;

            case 2:
                palindromecheck(num);
                break;
            
            case 3:
                armstrongcheck(num);
                break;

            case 4:
                factorialcheck(num);
                break;
                
            case 5:
                fibonaccicheck(num);
                break;

            case 6:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice! please try again. \n");
        }

    } while(choice != 6);
    
    return 0;
}

// function definitions

//prime check

void primecheck(int n){
    int i, flag = 1;

    if(n <= 1){
        flag = 0;
    }else{
        for(i = 2; i <= n/2; i++){
            if(n % i == 0){
                flag = 0;
                break;

            }
        }
    }
    if(flag )
        printf("%d is a prime number.\n", n);
    else
        printf("%d is not a prime number. \n", n);
}


// palindrome check

void palindromecheck(int n){
    int original = n, reversed = 0, remainder;

    while(n > 0){
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }

    if(original == reversed){
        printf("%d is a palindrome number. \n", original);

    }else{
        printf("%d is not a palindrome number. \n", original);

    }
}

//Armstrong check

void armstrongcheck(int n){
    int original = n, sum = 0, remainder, digits = 0;

    int temp = n;

    while(temp > 0){
        digits++;
        temp /= 10;

    }

    temp = n;

    while(temp > 0){
        remainder = temp % 10;

        int power = 1;
        for(int i = 0; i < digits; i++){
            power *= remainder;
        }
        sum += power;
        temp /= 10;
    }

    if(sum == original){
        printf("%d is an Armstrong Number. \n", original);

    }else{
        printf("%d is not an Armstrong Number. \n", original);

    }

}

// Factorial check

void factorialcheck(int n){
    long long fact = 1;
    int i;

    if(n < 0){
        printf("Factorial is not defined for negative numbers. \n");
        return;
    }
    for(i = 1; i <= n; i++){
        fact *= i;
    }
    printf("Factorial of %d is %lld. \n", n, fact);

}

// Fibonacci check

void fibonaccicheck(int n){
    int first = 0, second = 1, next, i;

    if(n <= 0){
        printf("Please enter a positive integer. \n");
        return;
    }
    printf("Fibonacci sequence up to %d terms :\n", n);

    for(i = 1; i <= n; i++){
        printf("%d ", first);
        next = first + second;
        first = second;
        second = next;

    }

    printf("\n");
    
}

