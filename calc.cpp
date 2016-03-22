#include "hFramework.h"


class Calculator {
private:
    int state = 0;
    int operaion = 0;
    int number[2] = {0,0};
public:
    Calculator() {};
    void chooseOperation();
    void chooseNumber(int num);
    void displayResult();
    void initialState();
    int getState();
};

void hMain()
{
    Calculator calc;
    while (true)
    {
        if (Serial.available() > 0)
        {
            switch(calc.getState()) {
                case 0:
                    calc.chooseOperation();
                    break;
                case 1:
                case 2:
                    calc.chooseNumber(calc.getState());
                    break;
                case 3:
                    calc.displayResult();
                    break;
                default:
                    calc.initialState();
            }
        }
    }
}

void Calculator::chooseOperation() {
    printf("Choose an operation:\t'q': Add\t'w': Sub\t'e':Mult\t'r':Div");
    char c = Serial.getch();
    switch(c) {
        case 'q':
            printf("Addition chosen");
            this->state = 1;
            this->operaion = 0;
            break;
        case 'w':
            printf("Substraction chosen");
            this->state = 1;
            this->operaion = 1;
            break;
        case 'e':
            printf("Multiplication chosen");
            this->state = 1;
            this->operaion = 2;
            break;
        case 'r':
            printf("Division chosen");
            this->state = 1;
            this->operaion = 3;
            break;
        default:
            printf("Invalid input");
            this->state = 0;
    }
}
void Calculator::chooseNumber(int num) {
    printf("Choose a number 0-9 \t'a': Done");
    char c = Serial.getch();
    std::string numbers = "0123456789";
    int index = numbers.find(c);
    
    if(index != std::string::npos) {
        this->number[num - 1] = this->number[num - 1] * 10 + (int)c;
        printf("Number: %d",this->number[num - 1]);
        this->state = num;
    } else if(c == 'a') {
        this->state = num + 1;
    } else {
        printf("Invalid input");
        this->state = num;
    }
}
void Calculator::displayResult() {
    int result = 0;
    float res = 0;
    switch(this->operaion) {
        case 1:
            result = this->number[0] - this->number[1];
            printf("Result: %d.",result);
            break;
        case 2:
            result = this->number[0] * this->number[1];
            printf("Result: %d.",result);
            break;
        case 3:
            if(this->number[1] == 0) {
                printf("Can't devide by 0.");
            } else {
                res = this->number[0] / this->number[1];
                printf("Result: %f.",res);
            }
            break;
        default:
            result = this->number[0] + this->number[1];
            printf("Result: %d.",result);
            break;
    }
    this->state = 4;
}
void Calculator::initialState() {
    this->operaion = 0;
    this->number[0] = 0;
    this->number[1] = 0;
    this->state = 0;
}
int Calculator::getState() {
    return this->state;
}