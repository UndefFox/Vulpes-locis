#include "mat3x3.h"

#include <math.h>


namespace ct {

Mat3x3 Mat3x3::operator*(const Mat3x3 mult) {
    Mat3x3 output;

    output.elements[0] = (elements[0] * mult.elements[0]) + (elements[1] * mult.elements[3]) + (elements[2] * mult.elements[6]);
    output.elements[3] = (elements[3] * mult.elements[0]) + (elements[4] * mult.elements[3]) + (elements[5] * mult.elements[6]);
    output.elements[6] = (elements[6] * mult.elements[0]) + (elements[7] * mult.elements[3]) + (elements[8] * mult.elements[6]);

    output.elements[1] = (elements[0] * mult.elements[1]) + (elements[1] * mult.elements[4]) + (elements[2] * mult.elements[7]);
    output.elements[4] = (elements[3] * mult.elements[1]) + (elements[4] * mult.elements[4]) + (elements[5] * mult.elements[7]);
    output.elements[7] = (elements[6] * mult.elements[1]) + (elements[7] * mult.elements[4]) + (elements[8] * mult.elements[7]);

    output.elements[2] = (elements[0] * mult.elements[2]) + (elements[1] * mult.elements[5]) + (elements[2] * mult.elements[8]);
    output.elements[5] = (elements[3] * mult.elements[2]) + (elements[4] * mult.elements[5]) + (elements[5] * mult.elements[8]);
    output.elements[8] = (elements[6] * mult.elements[2]) + (elements[7] * mult.elements[5]) + (elements[8] * mult.elements[8]);

    return output;
}

Vector3 Mat3x3::operator*(const Vector3 mult) {
    Vector3 output;

    output.x = (elements[0] * mult.x) + (elements[1] * mult.y) + (elements[2] * mult.z);
    output.y = (elements[3] * mult.x) + (elements[4] * mult.y) + (elements[5] * mult.z);
    output.z = (elements[6] * mult.x) + (elements[7] * mult.y) + (elements[8] * mult.z);

//-0.46286
//0.61844
    return output;
}

void Mat3x3::setCell(int a, int b, float val) {
    elements[a + 3 * b] = val;
}

float Mat3x3::getCell(int a, int b) {
    return elements[a + 3 * b];
}

Mat3x3 transpose(Mat3x3 mat) {
    Mat3x3 output = mat;

    output.setCell(1, 0, mat.getCell(0, 1));
    output.setCell(2, 0, mat.getCell(0, 2));
    output.setCell(2, 1, mat.getCell(1, 2));

    output.setCell(0, 1, mat.getCell(1, 0));
    output.setCell(0, 2, mat.getCell(2, 0));
    output.setCell(1, 2, mat.getCell(2, 1));

    return output;
}

Mat3x3 getRotationMatrix(float roll, float pitch, float yaw) {
    Mat3x3 output{};

    Mat3x3 buff{};

    buff = {};
    float c3 = std::cos(yaw);
    float s3 = std::sin(yaw);
    buff.setCell(2, 2, 1);
    buff.setCell(0, 0, c3);
    buff.setCell(1, 0, -s3);
    buff.setCell(0, 1, s3);
    buff.setCell(1, 1, c3);

    output = buff;

    buff = {};
    float c2 = std::cos(pitch);
    float s2 = std::sin(pitch);
    buff.setCell(1, 1, 1);
    buff.setCell(0, 0, c2);
    buff.setCell(2, 0, s2);
    buff.setCell(0, 2, -s2);
    buff.setCell(2, 2, c2);

    output = output * buff;

    buff = {};
    float c1 = std::cos(roll);
    float s1 = std::sin(roll);
    buff.setCell(0, 0, 1);
    buff.setCell(1, 1, c1);
    buff.setCell(2, 1, -s1);
    buff.setCell(1, 2, s1);
    buff.setCell(2, 2, c1);

    output = output * buff;



    return output;
}


}