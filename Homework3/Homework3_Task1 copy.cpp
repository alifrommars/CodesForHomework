// Общи забележки:
// При четене на входа, приемете, че потребителят въвежда данни в коректен формат и тип. Валидацията на стойностите им е ваша задача.
// Всички масиви трябва да са с точната големина (не по-големи от нужното).
// Разрешено е използването само на библиотеките new и iostream.


                // Задача 1
//          Напишете следните функции:
// 1. input, която въвежда от стандартния вход две цели числа N и M, 
// след това създава в динамичната памет двумерен масив с N реда, M 
// колони и елементи - цели числа и накрая прочита от стандартния вход елементите на масива.
// 2. transform, която въвежда цяло число D от стандартния вход и в подаден масив 
// (създаден от горната функция) заменя всички елементи, които имат точно D делителя, с 0.
// 3. clear, която премахва от масива, създаден чрез първата функция, всички редове 
// и всички колони, съставени само от нулеви елементи, като премества оставащите на
// тяхно място и запазва относителния им ред.
// 4. print, която извежда на екрана двумерен масив.
// Помислете какви трябва да са аргументите и връщаният резултат за всяка функция.
// Демонстрирайте използването им в смислена цялостна програма.

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

int** input(int& N, int& M){
    cout << "Enter the number of rows: ";
    cin >> N;
    while (N <= 0){
        cout << "Invalid input. Please enter a positive value for rows: ";
        cin >> N;
    }

    cout << "Enter the number of columns: ";
    cin >> M;
    while (M <= 0){
        cout << "Invalid input. Please enter a positive value for columns: ";
        cin >> M;
    }
        /***************************/
        /*  Row by row allocation  */
        /***************************/
    int** matrix = new (nothrow) int*[N];

    for (int i = 0; i < N; i++){
        matrix[i] = new (nothrow) int[M];
        for (int j = 0; j < M; j++){
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

void transform(int** matrix, int N, int M, int D){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (matrix[i][j] % D == 0){
                matrix[i][j] = 0;
            }
        }
    }
}

void clear(int**& matrix, int& N, int& M){
    // Removing zero rows
    for (int i = 0; i < N; i++){
        bool zeroRows = true;
        for (int j = 0; j < M; j++){
            if (matrix[i][j] != 0){
                zeroRows = false;
                break;
            }
        }
        if (zeroRows){
            delete[] matrix[i];
            for (int k = i; k < N - 1; k++) {
                matrix[k] = matrix[k + 1];
            }
            N--;
            i--;
        }
    }

    // Removing zero columns
    for (int j = 0; j < M; j++){
        bool zeroCols = true;
        for (int i = 0; i < N; i++){
            if (matrix[i][j] != 0){
                zeroCols = false;
                break;
            }
        }
        if (zeroCols) {
            for (int i = 0; i < N; i++){
                for (int k = j; k < M - 1; k++){
                    matrix[i][k] = matrix[i][k + 1];
                }
            }
            M--;
            j--;
        }
    }
}

void print(int** matrix, int N, int M){
    cout << "Matrix:" << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void freeMatrix(int**& matrix, int N){
    for (int i = 0; i < N; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

int main(){
    int N, M;
    int** matrix = input(N, M);

    int D;
    cout << "Enter integer number D for transformation: ";
    cin >> D;

    transform(matrix, N, M, D);

    clear(matrix, N, M);

    bool isMatrixAllZeros = true;
    for (int i = 0; i < N && isMatrixAllZeros; i++){
        for (int j = 0; j < M; j++){
            if (matrix[i][j] != 0){
                isMatrixAllZeros = false;
                break;
            }
        }
    }

    print(matrix, N, M);

    if (isMatrixAllZeros){
        cout << "The resulting matrix contains only zeros." << endl;
    }

    freeMatrix(matrix, N);

    return 0;
}