#include <iostream>
#include "mat4x4.h"
#include "vector3.h"

using namespace std;

int main()
{
    float a[4][4] = { {1, 2, 3, 4}, 
                      {5, 6, 7, 8},
                      {9, 10 , 11, 12},
                      {13, 14, 15, 16} };
    
    float b[4][4] = { {1, 5, 9, 13},
                      {2, 6, 10, 14},
                      {3, 7, 11, 15},
                      {4, 8, 12, 16} };
    Mat4x4 m1;
    Mat4x4 m2;
    m1.Set(a);
    m2.Set(b);

    m2 = m2.Transpose();
    
    m1.Set(m2);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << m1.matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}