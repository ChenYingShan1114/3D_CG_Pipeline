#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath> 
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
void drawALine(int x_start, int x_end, int y_start, int y_end, float R, float G, float B);
int i = 0;
// there is no "clearData" and "clearScreen" in the .in file. So the size of vector will become more and more bigger.

#define ROWS 4
#define COLUMNS 4

using namespace std;
string filename;
string in_path;

float tmpArrange[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
int anvalue = 0;
vector<float> obj_v1_arr;
vector<float> obj_v2_arr;
vector<float> obj_v3_arr;
vector<float> obj_vt1_arr;
vector<float> obj_vt2_arr;
vector<float> obj_vt3_arr;
vector<float> obj_vn1_arr;
vector<float> obj_vn2_arr;
vector<float> obj_vn3_arr;

vector<int> obj_fv1_arr;
vector<int> obj_fvt1_arr;
vector<int> obj_fvn1_arr;
vector<int> obj_fv2_arr;
vector<int> obj_fvt2_arr;
vector<int> obj_fvn2_arr;
vector<int> obj_fv3_arr;
vector<int> obj_fvt3_arr;
vector<int> obj_fvn3_arr;

vector<float> obj_v1_arr_view;
vector<float> obj_v2_arr_view;
vector<float> obj_v3_arr_view;

vector<float> x_start_view;
vector<float> x_end_view;
vector<float> y_start_view;
vector<float> y_end_view;
vector<float> z_start_view;
vector<float> z_end_view;

int vertex_number = 0;
int vt_number = 0;
int vn_number = 0;
int face_number = 0;
int Width = 0;
int Height = 0;
int left_boundary = 0;
int right_boundary = 0;
int top_boundary = 0;
int botton_boundary = 0;

float M_matrix[ROWS][COLUMNS] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

float V_matrix[ROWS][COLUMNS] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

float P_matrix[ROWS][COLUMNS] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

float Transform_matrix[ROWS][COLUMNS] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};
float Unit_matrix[ROWS][COLUMNS] = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

float Point_matrix[ROWS] = { 0.0, 0.0, 0.0, 0.0 };

void ClearData() {
    obj_v1_arr.clear();
    obj_v2_arr.clear();
    obj_v3_arr.clear();
    obj_vt1_arr.clear();
    obj_vt2_arr.clear();
    obj_vt3_arr.clear();
    obj_vn1_arr.clear();
    obj_vn2_arr.clear();
    obj_vn3_arr.clear();
    obj_fv1_arr.clear();
    obj_fvt1_arr.clear();
    obj_fvn1_arr.clear();
    obj_fv2_arr.clear();
    obj_fvt2_arr.clear();
    obj_fvn2_arr.clear();
    obj_fv3_arr.clear();
    obj_fvt3_arr.clear();
    obj_fvn3_arr.clear();
}

void Multiply_point(float Operator[][4], float Point[])
{
    float Zero_matrix[ROWS] = { 0.0, 0.0, 0.0, 0.0 };
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLUMNS; k++) {
            Zero_matrix[i] = Zero_matrix[i] + Operator[i][k] * Point[k];
            Point_matrix[i] = Zero_matrix[i];
        }
    }
    for (int i = 0; i < ROWS; i++) {
        //cout << "   origin point: " << Point[i] << endl;
        //cout << "transform point: " << Point_matrix[i] << endl;
    }
    //cout << endl;

}

// this arrange function canʼt read f v1//vn1 v2//vn2 v3//vn3.
void ArrangeBySlash(string str) {
    int current = 0;
    int next;        
    int avalue = 0;
    while (1){

        next = str.find_first_of("/", current);
        if (next != current){
            string tmp = str.substr(current, next - current);
            if (tmp.size() != 0){
                //cout << a << " " << tmp << endl;
                //tmpSlash[a] = stof(tmp);
                //tmpArrange[avalue+anvalue]  = std::stof(tmp);
                if (tmp == "\r"){
                    //cout << avalue+anvalue << "bbbb " << tmp << endl;
                    //cout << avalue+anvalue << " rrr" << tmp << endl;
                    //avalue++;
                }
                else{
                    //cout << avalue+anvalue << " yaaab" << tmp << "yaaac" << endl;
                    //cout << avalue+anvalue << " " << tmp << endl;
                    tmpArrange[avalue+anvalue]  = std::stof(tmp);
                    //cout << avalue+anvalue << " " << tmpArrange[avalue+anvalue]<< endl;
                    avalue++;                    
                }
            }
        }
        if (next == string::npos) break;
        current = next + 1;
    }
    anvalue = anvalue + 3;
} 

void ArrangeBySpace(string str) {
    for (int i = 0; i<12; i++){
        tmpArrange[i] = 0.0;
    }
    int current = 0;
    int next;
    anvalue = 0;
    while (1){
        next = str.find_first_of(" ", current);
        if (next != current){
            string tmp = str.substr(current, next - current);
            if (tmp.size() != 0){
                //cout << a << " " << tmp << endl;
                ArrangeBySlash(tmp);
                //tmpArrange[a] = stof(tmp);
                //cout << a << " " << tmp << endl;
//                a++;
            }
        }
        if (next == string::npos) break;
        current = next + 1;
    }
} 

void Arrange(string str) {
    int a = 0;
    string w = "";
    float w_f;
    for (auto x : str)
    {
        if (x == ' ')
        {
            if (w == "") {
            }
            else {
                w_f = strtof(w.c_str(), nullptr);
                tmpArrange[a] = w_f;
                a++;
            }
            w = "";
        }
        else {
            w = w + x;
        }
    }
    w_f = strtof(w.c_str(), nullptr);
    tmpArrange[a] = w_f;
}

int tmp_v_size = 0.0;
void ReadOBJFile(string str){

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            M_matrix[i][j] = Transform_matrix[i][j];
        }
    }
    string obj_path;
    obj_path.append("../Mesh/").append(str);
    cout << "obj_path: " << obj_path << endl; 
    fstream fp;
    fp.open(obj_path, ios::in);
    if (!fp) {
        //cout << "Failed to open the file.\n";
        exit(0);
    }
    else {
        //cout << "open obj" << endl;
    }
    string InputLine, DataStyle;
    int a = 0;
    vertex_number = 0;
    vt_number = 0;
    vn_number = 0;
    face_number = 0;
    float point[4] = {0.0, 0.0, 0.0, 0.0};
    while (getline(fp,InputLine)){
        a = 0;
        while (a < 1){
            a++;
            DataStyle = InputLine.substr(0, InputLine.find(" "));
            //cout << "InputLine" << DataStyle << endl;
            if (a == 1){
                a++;
                if (DataStyle == "v"){ // position of point
                    //cout << "V" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //cout << InputLine << endl;
                    ArrangeBySpace(InputLine);
                    //cout << "x = " << tmpArrange[0] << ", y = " << tmpArrange[3] << ", z = " << tmpArrange[6] << endl;
                    point[0] = tmpArrange[0];
                    point[1] = tmpArrange[3];
                    point[2] = tmpArrange[6];
                    point[3] = 1.0;
                    Multiply_point(Transform_matrix, point);
                    //cout << "x = " << Point_matrix[0] << ", y = " << Point_matrix[1] << ", z = " << Point_matrix[2] << endl;

                    obj_v1_arr.push_back(Point_matrix[0]);
                    obj_v2_arr.push_back(Point_matrix[1]);
                    obj_v3_arr.push_back(Point_matrix[2]);
                    vertex_number++;
                }
                else if (DataStyle == "vt"){ // position of texture space (did this need to be transformed by transformation matrix???)
                    //cout << "VT" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //cout << InputLine << endl;
                    ArrangeBySpace(InputLine);
                    //cout << "vtx = " << tmpArrange[0] << ", vty = " << tmpArrange[3] << ", vtz = " << tmpArrange[6] << endl;
                    point[0] = tmpArrange[0];
                    point[1] = tmpArrange[3];
                    point[2] = tmpArrange[6];
                    point[3] = 1.0;
                    Multiply_point(Transform_matrix, point);
                    obj_vt1_arr.push_back(Point_matrix[0]);
                    obj_vt2_arr.push_back(Point_matrix[1]);
                    obj_vt3_arr.push_back(Point_matrix[2]);
                    vt_number++;
                }
                else if (DataStyle == "vn") { // normal vector 
                    //cout << "VN" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //cout << InputLine << endl;
                    ArrangeBySpace(InputLine);
                    //cout << "vnx = " << tmpArrange[0] << ", vny = " << tmpArrange[3] << ", vnz = " << tmpArrange[6] << endl;
                    point[0] = tmpArrange[0];
                    point[1] = tmpArrange[3];
                    point[2] = tmpArrange[6];
                    point[3] = 0.0;
                    Multiply_point(Transform_matrix, point);
                    //cout << "x = " << Point_matrix[0] << ", y = " << Point_matrix[1] << ", z = " << Point_matrix[2] << endl;
                    obj_vn1_arr.push_back(Point_matrix[0]);
                    obj_vn2_arr.push_back(Point_matrix[1]);
                    obj_vn3_arr.push_back(Point_matrix[2]);
                    vn_number++;
                }
                else if (DataStyle == "f"){
                    //cout << "F" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //cout << InputLine << endl;
                    ArrangeBySpace(InputLine);
                    //cout << " + tmp_v_size " << tmp_v_size << endl;
                    if (tmpArrange[9] != 0){
                        
                        //cout << "square" << endl;
                        //cout << "fv1 = " << tmpArrange[0] << ", fv2 = " << tmpArrange[3] << ", fv3 = " << tmpArrange[6] << endl;
                        //cout << "fvt1 = " << tmpArrange[1] << ", fvt2 = " << tmpArrange[4] << ", fvt3 = " << tmpArrange[7] << endl;
                        //cout << "fvn1 = " << tmpArrange[2] << ", fvn2 = " << tmpArrange[5] << ", fvn3 = " << tmpArrange[8] << endl;
                        /*
                        obj_fv1_arr.push_back(tmpArrange[0] + tmp_v_size);
                        obj_fvt1_arr.push_back(tmpArrange[1]);
                        obj_fvn1_arr.push_back(tmpArrange[2]);
                        obj_fv2_arr.push_back(tmpArrange[3] + tmp_v_size);
                        obj_fvt2_arr.push_back(tmpArrange[4]);
                        obj_fvn2_arr.push_back(tmpArrange[5]);
                        obj_fv3_arr.push_back(tmpArrange[6] + tmp_v_size);
                        obj_fvt3_arr.push_back(tmpArrange[7]);
                        obj_fvn3_arr.push_back(tmpArrange[8]);
                        face_number++;
                        
                        //cout << "fv1 = " << tmpArrange[6] << ", fv2 = " << tmpArrange[9] << ", fv3 = " << tmpArrange[0] << endl;
                        //cout << "fvt1 = " << tmpArrange[7] << ", fvt2 = " << tmpArrange[10] << ", fvt3 = " << tmpArrange[1] << endl;
                        //cout << "fvn1 = " << tmpArrange[8] << ", fvn2 = " << tmpArrange[11] << ", fvn3 = " << tmpArrange[2] << endl;
                        
                        obj_fv1_arr.push_back(tmpArrange[6] + tmp_v_size);
                        obj_fvt1_arr.push_back(tmpArrange[7]);
                        obj_fvn1_arr.push_back(tmpArrange[8]);
                        obj_fv2_arr.push_back(tmpArrange[9] + tmp_v_size);
                        obj_fvt2_arr.push_back(tmpArrange[10]);
                        obj_fvn2_arr.push_back(tmpArrange[11]);
                        obj_fv3_arr.push_back(tmpArrange[0] + tmp_v_size);
                        obj_fvt3_arr.push_back(tmpArrange[1]);
                        obj_fvn3_arr.push_back(tmpArrange[2]);
                        face_number++;
                        */
                        
                        obj_fv1_arr.push_back(tmpArrange[0] + tmp_v_size);
                        obj_fvt1_arr.push_back(tmpArrange[1]);
                        obj_fvn1_arr.push_back(tmpArrange[2]);
                        obj_fv2_arr.push_back(tmpArrange[3] + tmp_v_size);
                        obj_fvt2_arr.push_back(tmpArrange[4]);
                        obj_fvn2_arr.push_back(tmpArrange[5]);
                        obj_fv3_arr.push_back(tmpArrange[9] + tmp_v_size);
                        obj_fvt3_arr.push_back(tmpArrange[10]);
                        obj_fvn3_arr.push_back(tmpArrange[11]);
                        face_number++;
                        obj_fv1_arr.push_back(tmpArrange[6] + tmp_v_size);
                        obj_fvt1_arr.push_back(tmpArrange[7]);
                        obj_fvn1_arr.push_back(tmpArrange[8]);
                        obj_fv2_arr.push_back(tmpArrange[9] + tmp_v_size);
                        obj_fvt2_arr.push_back(tmpArrange[10]);
                        obj_fvn2_arr.push_back(tmpArrange[11]);
                        obj_fv3_arr.push_back(tmpArrange[3] + tmp_v_size);
                        obj_fvt3_arr.push_back(tmpArrange[4]);
                        obj_fvn3_arr.push_back(tmpArrange[5]);
                        face_number++;
                        
                    }
                    else {
                        //cout << "triangle" << endl;
                        //cout << "fv1 = " << tmpArrange[0] << ", fv2 = " << tmpArrange[3] << ", fv3 = " << tmpArrange[6] << ", fv4 = " << tmpArrange[9] << endl;
                        //cout << "fvt1 = " << tmpArrange[1] << ", fvt2 = " << tmpArrange[4] << ", fvt3 = " << tmpArrange[7] << ", fvt4 = " << tmpArrange[10] << endl;
                        //cout << "fvn1 = " << tmpArrange[2] << ", fvn2 = " << tmpArrange[5] << ", fvn3 = " << tmpArrange[8] << ", fvn4 = " << tmpArrange[11] << endl;
                        obj_fv1_arr.push_back(tmpArrange[0] + tmp_v_size);
                        obj_fvt1_arr.push_back(tmpArrange[1]);
                        obj_fvn1_arr.push_back(tmpArrange[2]);
                        obj_fv2_arr.push_back(tmpArrange[3] + tmp_v_size);
                        obj_fvt2_arr.push_back(tmpArrange[4]);
                        obj_fvn2_arr.push_back(tmpArrange[5]);
                        obj_fv3_arr.push_back(tmpArrange[6] + tmp_v_size);
                        obj_fvt3_arr.push_back(tmpArrange[7]);
                        obj_fvn3_arr.push_back(tmpArrange[8]);
                        face_number++;                         
                    }
                }
            }
            InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
            if (InputLine.find(" ") == -1) {
                break;
            }
        }
    }
    fp.close();
    //cout << "v = " << vertex_number << ", vt = " << vt_number << ", vn = " << vn_number << ", f = " << face_number << endl;
    cout << "v1 size = " << obj_v1_arr.size() << ", vt1 size = " << obj_vt1_arr.size() << ", vn1 size = " << obj_vn1_arr.size()<< ", fv1 size = " << obj_fv1_arr.size() << endl;
    tmp_v_size = obj_v1_arr.size();
}

void Inner_product(float Operator[][COLUMNS], float Transform[][COLUMNS]) {
    float Zero_matrix[ROWS][COLUMNS] = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };
    float a = 0.0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            a = 0.0;
            for (int k = 0; k < ROWS; k++) {
                a = a + Operator[i][k] * Transform[k][j];
            }
            Zero_matrix[i][j] = a;
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Transform_matrix[i][j] = Zero_matrix[i][j];
            //cout << " " << Transform_matrix[i][j];
        }
    }
}

void Scale(float sx, float sy, float sz) {
    float scale_matrix[ROWS][COLUMNS] = {
        { sx, 0.0, 0.0, 0.0},
        {0.0,  sy, 0.0, 0.0},
        {0.0, 0.0,  sz, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << ", " << scale_matrix[i][j];
        }
        cout << endl;
    }
    */
    Inner_product(scale_matrix, Transform_matrix);
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << " " << Transform_matrix[i][j];
        }
        cout << endl;
    }
    */
}

void Rotate(float anglex, float angley, float anglez) {
    float Degreex = anglex * 3.14159 / 180;
    float Degreey = angley * 3.14159 / 180;
    float Degreez = anglez * 3.14159 / 180;
    float rotate_matrix_x[ROWS][COLUMNS] = {
        {1.0,          0.0,           0.0, 0.0},
        {0.0, cos(Degreex), -sin(Degreex), 0.0},
        {0.0, sin(Degreex),  cos(Degreex), 0.0},
        {0.0,          0.0,           0.0, 1.0}
    };
    float rotate_matrix_y[ROWS][COLUMNS] = {
        { cos(Degreey), 0.0, sin(Degreey), 0.0},
        {          0.0, 1.0,          0.0, 0.0},
        {-sin(Degreey), 0.0, cos(Degreey), 0.0},
        {          0.0, 0.0,          0.0, 1.0}
    };
    float rotate_matrix_z[ROWS][COLUMNS] = {
        {cos(Degreez), -sin(Degreez), 0.0, 0.0},
        {sin(Degreez),  cos(Degreez), 0.0, 0.0},
        {         0.0,           0.0, 1.0, 0.0},
        {         0.0,           0.0, 0.0, 1.0}
    };
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << ", " << rotate_matrix_y[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << ", " << rotate_matrix_z[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << ", " << rotate_matrix_x[i][j];
        }
        cout << endl;
    }
    */
    Inner_product(rotate_matrix_y, Transform_matrix);
    Inner_product(rotate_matrix_z, Transform_matrix);
    Inner_product(rotate_matrix_x, Transform_matrix);
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << " " << Transform_matrix[i][j];
        }
        cout << endl;
    }
    */
}

void Translate(float tx, float ty, float tz) {
    float translate_matrix[ROWS][COLUMNS] = {
        {1.0, 0.0, 0.0,  tx},
        {0.0, 1.0, 0.0,  ty},
        {0.0, 0.0, 1.0,  tz},
        {0.0, 0.0, 0.0, 1.0}
    };
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << ", " << translate_matrix[i][j];
        }
        cout << endl;
    }
    */
    Inner_product(translate_matrix, Transform_matrix);
    /*
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            cout << " " << Transform_matrix[i][j];
        }
        cout << endl;
    }
    */
}

void Observer(float epx, float epy, float epz, float COIx, float COIy, float COIz, float Tilt){

    float Eye_matrix[ROWS][COLUMNS] = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    float translate_matrix[ROWS][COLUMNS] = {
        {1.0, 0.0, 0.0, -epx},
        {0.0, 1.0, 0.0, -epy},
        {0.0, 0.0, 1.0, -epz},
        {0.0, 0.0, 0.0,  1.0}
    };
    Inner_product(translate_matrix, Eye_matrix);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Eye_matrix[i][j] = Transform_matrix[i][j];
            //cout << " " << Eye_matrix[i][j];
        }
        //cout << " 111" << endl;
    }

    float z_axis[4] = {COIx - epx, COIy - epy, COIz - epz, 0.0};   
    float z_length = sqrt( (z_axis[0])*(z_axis[0]) + (z_axis[1])*(z_axis[1]) + (z_axis[2])*(z_axis[2]));
    z_axis[0] = z_axis[0] / z_length;
    z_axis[1] = z_axis[1] / z_length;
    z_axis[2] = z_axis[2] / z_length;
    //cout << "z = " << (z_axis[0]) << " " << (z_axis[1]) << " " << (z_axis[2]) << endl;    
    //cout << "z = " << (z_axis[0])*(z_axis[0]) + (z_axis[1])*(z_axis[1]) + (z_axis[2])*(z_axis[2]) << endl;
  
    float y_tmp[4] = {0.0, 1.0, 0.0, 0.0};
    //cout << "tmp y = " << (y_tmp[0]) << " " << (y_tmp[1]) << " " << (y_tmp[2]) << endl;    
    //cout << "tmp y = " << (y_tmp[0])*(y_tmp[0]) + (y_tmp[1])*(y_tmp[1]) + (y_tmp[2])*(y_tmp[2]) << endl;


    float x_axis[4] = {y_tmp[1] * z_axis[2] - z_axis[1] * y_tmp[2], y_tmp[2] * z_axis[0] - z_axis[2] * y_tmp[0], y_tmp[0] * z_axis[1] - z_axis[0] * y_tmp[1], 0.0};
    float x_length = sqrt( (x_axis[0])*(x_axis[0]) + (x_axis[1])*(x_axis[1]) + (x_axis[2])*(x_axis[2]));
    x_axis[0] = x_axis[0] / x_length;
    x_axis[1] = x_axis[1] / x_length;
    x_axis[2] = x_axis[2] / x_length;    
    //cout << "x = " << (x_axis[0]) << " " << (x_axis[1]) << " " << (x_axis[2]) << endl;    
    //cout << "x = " << (x_axis[0])*(x_axis[0]) + (x_axis[1])*(x_axis[1]) + (x_axis[2])*(x_axis[2]) << endl;

    float y_axis[4] = {z_axis[1] * x_axis[2] - x_axis[1] * z_axis[2], z_axis[2] * x_axis[0] - x_axis[2] * z_axis[0], z_axis[0] * x_axis[1] - x_axis[0] * z_axis[1], 0.0};
    //cout << "y = " << (y_axis[0]) << " " << (y_axis[1]) << " " << (y_axis[2]) << endl;    
    //cout << "y = " << (y_axis[0])*(y_axis[0]) + (y_axis[1])*(y_axis[1]) + (y_axis[2])*(y_axis[2]) << endl;

    float GR_matrix[ROWS][COLUMNS] = {
        {x_axis[0], x_axis[1], x_axis[2], 0.0},
        {y_axis[0], y_axis[1], y_axis[2], 0.0},
        {z_axis[0], z_axis[1], z_axis[2], 0.0},
        {      0.0,       0.0,       0.0, 1.0}
    };
    Inner_product(GR_matrix, Eye_matrix);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Eye_matrix[i][j] = Transform_matrix[i][j];
            //cout << " " << GR_matrix[i][j];
        }
        //cout << " 111" << endl;
    }

    float mirror_x[ROWS][COLUMNS] = {
        {-1.0, 0.0, 0.0, 0.0},
        { 0.0, 1.0, 0.0, 0.0},
        { 0.0, 0.0, 1.0, 0.0},
        { 0.0, 0.0, 0.0, 1.0}
    };
    Inner_product(mirror_x, Eye_matrix);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Eye_matrix[i][j] = Transform_matrix[i][j];
        }
    }

    float Degreez = Tilt * 3.14159 / 180;
    float rotate_matrix_z[ROWS][COLUMNS] = {
        {cos(Degreez), -sin(Degreez), 0.0, 0.0},
        {sin(Degreez),  cos(Degreez), 0.0, 0.0},
        {         0.0,           0.0, 1.0, 0.0},
        {         0.0,           0.0, 0.0, 1.0}
    };
    Inner_product(rotate_matrix_z, Eye_matrix);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            Eye_matrix[i][j] = Transform_matrix[i][j];
        }
    }



    //cout << "V Matrix" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            V_matrix[i][j] = Eye_matrix[i][j];
            //cout << " " << Eye_matrix[i][j];
        }
        //cout << endl;
    }
}

void WorldtoEye(){ // havenʼt debug yet
    float point[4] = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < obj_v1_arr.size(); i++){
        point[0] = obj_v1_arr[i];
        point[1] = obj_v2_arr[i];
        point[2] = obj_v3_arr[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        Multiply_point(V_matrix, point);
        //obj_v1_arr[i] = Point_matrix[0];
        //obj_v2_arr[i] = Point_matrix[1];
        //obj_v3_arr[i] = Point_matrix[2];
        obj_v1_arr_view.push_back(Point_matrix[0]);
        obj_v2_arr_view.push_back(Point_matrix[1]);
        obj_v3_arr_view.push_back(Point_matrix[2]);
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
    }
    for (int i = 0; i < obj_vt1_arr.size(); i++){
        point[0] = obj_vt1_arr[i];
        point[1] = obj_vt2_arr[i];
        point[2] = obj_vt3_arr[i];
        point[3] = 1.0;
        //cout << "   before: xt = " << obj_vt1_arr[i]  << ", yt = " << obj_vt2_arr[i]  << ", zt = " << obj_vt3_arr[i] << endl;
        Multiply_point(V_matrix, point);
        obj_vt1_arr[i] = Point_matrix[0];
        obj_vt2_arr[i] = Point_matrix[1];
        obj_vt3_arr[i] = Point_matrix[2];
        //cout << "    after: xt = " << obj_vt1_arr[i]  << ", yt = " << obj_vt2_arr[i]  << ", zt = " << obj_vt3_arr[i] << endl;
    }
    for (int i = 0; i < obj_vn1_arr.size(); i++){
        point[0] = obj_vn1_arr[i];
        point[1] = obj_vn2_arr[i];
        point[2] = obj_vn3_arr[i];
        point[3] = 0.0;
        //cout << "   before: xn = " << obj_vn1_arr[i]  << ", yn = " << obj_vn2_arr[i]  << ", zn = " << obj_vn3_arr[i] << endl;
        Multiply_point(V_matrix, point);
        obj_vn1_arr[i] = Point_matrix[0];
        obj_vn2_arr[i] = Point_matrix[1];
        obj_vn3_arr[i] = Point_matrix[2];
        //cout << "    after: xn = " << obj_vn1_arr[i]  << ", yn = " << obj_vn2_arr[i]  << ", zn = " << obj_vn3_arr[i] << endl;
    }

} 

void Projection(float Hither, float Yon, float Hav){
    float AspectRatio = Width / Height;
    float DegreeHav = Hav * 3.14159 / 180;
    float temp = Yon / (Yon - Hither) * tan(DegreeHav);
    /*
    float matrix[ROWS][COLUMNS] = {
        {1.0,         0.0,            0.0,            0.0},
        {0.0, AspectRatio,            0.0,            0.0},
        {0.0,         0.0,           temp, -temp * Hither},//fill in the value
        {0.0,         0.0, tan(DegreeHav),            1.0}
    };
    */
    P_matrix[1][1] = AspectRatio;
    P_matrix[2][2] = temp;
    P_matrix[2][3] = -temp * Hither;
    P_matrix[3][2] = tan(DegreeHav);
    P_matrix[3][3] = 0.0;
}

void EyetoProject(){ // Is this done the perpective divide??? // havanʼt debug yet
    float point[4] = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < obj_v1_arr.size(); i++){
        point[0] = obj_v1_arr_view[i];
        point[1] = obj_v2_arr_view[i];
        point[2] = obj_v3_arr_view[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << point[3] << endl;
        Multiply_point(P_matrix, point);
        obj_v1_arr_view[i] = Point_matrix[0] / Point_matrix[3];
        obj_v2_arr_view[i] = Point_matrix[1] / Point_matrix[3];
        obj_v3_arr_view[i] = Point_matrix[2] / Point_matrix[3];
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << Point_matrix[3] << endl;
    }
    for (int i = 0; i < obj_vt1_arr.size(); i++){
        point[0] = obj_vt1_arr[i];
        point[1] = obj_vt2_arr[i];
        point[2] = obj_vt3_arr[i];
        point[3] = 1.0;
        //cout << "   before: xt = " << obj_vt1_arr[i]  << ", yt = " << obj_vt2_arr[i]  << ", zt = " << obj_vt3_arr[i] << endl;
        Multiply_point(P_matrix, point);
        obj_vt1_arr[i] = Point_matrix[0];
        obj_vt2_arr[i] = Point_matrix[1];
        obj_vt3_arr[i] = Point_matrix[2];
        //cout << "    after: xt = " << obj_vt1_arr[i]  << ", yt = " << obj_vt2_arr[i]  << ", zt = " << obj_vt3_arr[i] << endl;
    }
    for (int i = 0; i < obj_vn1_arr.size(); i++){
        point[0] = obj_vn1_arr[i];
        point[1] = obj_vn2_arr[i];
        point[2] = obj_vn3_arr[i];
        point[3] = 0.0;
        //cout << "   before: xn = " << obj_vn1_arr[i]  << ", yn = " << obj_vn2_arr[i]  << ", zn = " << obj_vn3_arr[i] << endl;
        Multiply_point(P_matrix, point);
        obj_vn1_arr[i] = Point_matrix[0];
        obj_vn2_arr[i] = Point_matrix[1];
        obj_vn3_arr[i] = Point_matrix[2];
        //cout << "    after: xn = " << obj_vn1_arr[i]  << ", yn = " << obj_vn2_arr[i]  << ", zn = " << obj_vn3_arr[i] << endl;
    }
} 

void DrawATriangle(float x1, float x2, float x3, float y1, float y2, float y3){
    drawALine(x1, x2, y1, y2, 1.0, 0.0, 0.0);
    drawALine(x2, x3, y2, y3, 1.0, 0.0, 0.0);
    drawALine(x3, x1, y3, y1, 1.0, 0.0, 0.0);
}

vector<float> x_start;
vector<float> x_end;
vector<float> y_start;
vector<float> y_end;
vector<float> z_start;
vector<float> z_end;
void SavePoint(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3){
    x_start.push_back(x1);
    x_end.push_back(x2);
    x_start.push_back(x2);
    x_end.push_back(x3);
    x_start.push_back(x3);
    x_end.push_back(x1);
    y_start.push_back(y1);
    y_end.push_back(y2);
    y_start.push_back(y2);
    y_end.push_back(y3);
    y_start.push_back(y3);
    y_end.push_back(y1);
    z_start.push_back(z1);
    z_end.push_back(z2);
    z_start.push_back(z2);
    z_end.push_back(z3);
    z_start.push_back(z3);
    z_end.push_back(z1);
}

vector<int> obj_fv1_arr_see;
vector<int> obj_fv2_arr_see;
vector<int> obj_fv3_arr_see;
float normal_vector[3] = {0.0, 0.0, 0.0};
void GetNormalVector(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3){
    //cout << "GetNormalVector";
    float v1[3] = {x2 - x1, y2 - y1, z2 - z1};
    float v2[3] = {x3 - x2, y3 - y2, z3 - z2};
    //float vector_3[3] = {x1 - x3, y1 - y3, z1 - z3};
    normal_vector[0] = v1[1] * v2[2] - v1[2] * v2[1];
    normal_vector[1] = v1[2] * v2[0] - v1[0] * v2[2];
    normal_vector[2] = v1[0] * v2[1] - v1[1] * v2[0];
    
}

void DeleteZData(){
    for (int i = 0; i < obj_fv1_arr.size(); i++){
        //cout << i << endl;
        float x1 = obj_v1_arr_view[obj_fv1_arr[i] - 1];
        float x2 = obj_v1_arr_view[obj_fv2_arr[i] - 1];
        float x3 = obj_v1_arr_view[obj_fv3_arr[i] - 1];
        float y1 = obj_v2_arr_view[obj_fv1_arr[i] - 1];
        float y2 = obj_v2_arr_view[obj_fv2_arr[i] - 1];
        float y3 = obj_v2_arr_view[obj_fv3_arr[i] - 1];
        float z1 = obj_v3_arr_view[obj_fv1_arr[i] - 1];
        float z2 = obj_v3_arr_view[obj_fv2_arr[i] - 1];
        float z3 = obj_v3_arr_view[obj_fv3_arr[i] - 1];
        GetNormalVector(x1, x2, x3, y1, y2, y3, z1, z2, z3);
        //cout << normal_vector[2] << endl; 
        if (normal_vector[2] > 0.0){
            obj_fv1_arr_see.push_back(obj_fv1_arr[i]);
            obj_fv2_arr_see.push_back(obj_fv2_arr[i]);
            obj_fv3_arr_see.push_back(obj_fv3_arr[i]);
        }
    }
}

void Clipping(){
    
    x_start.clear();
    x_end.clear();
    y_start.clear();
    y_end.clear();
    z_start.clear();
    z_end.clear();

    for (int i = 0; i < obj_fv1_arr_see.size(); i++){
        //cout << i << endl;
        float x1 = obj_v1_arr_view[obj_fv1_arr_see[i] - 1];
        float x2 = obj_v1_arr_view[obj_fv2_arr_see[i] - 1];
        float x3 = obj_v1_arr_view[obj_fv3_arr_see[i] - 1];
        float y1 = obj_v2_arr_view[obj_fv1_arr_see[i] - 1];
        float y2 = obj_v2_arr_view[obj_fv2_arr_see[i] - 1];
        float y3 = obj_v2_arr_view[obj_fv3_arr_see[i] - 1];
        float z1 = obj_v3_arr_view[obj_fv1_arr_see[i] - 1];
        float z2 = obj_v3_arr_view[obj_fv2_arr_see[i] - 1];
        float z3 = obj_v3_arr_view[obj_fv3_arr_see[i] - 1];
        SavePoint(x1, x2, x3, y1, y2, y3, z1, z2, z3);
    }
    

    // c1 boundary
    vector<float> x_start_1;
    vector<float> x_end_1;
    vector<float> y_start_1;
    vector<float> y_end_1;
    vector<float> z_start_1;
    vector<float> z_end_1;
    for (int i = 0; i < x_start.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c1_start = 1 + x_start[i];
        float c1_end = 1 + x_end[i];
        if (c1_start < 0 && c1_end < 0){
            // do nothing
        }
        else if (c1_start >= 0 && c1_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_1.push_back(x_start[i]);
            x_end_1.push_back(x_end[i]);
            y_start_1.push_back(y_start[i]);
            y_end_1.push_back(y_end[i]);
            z_start_1.push_back(z_start[i]);
            z_end_1.push_back(z_end[i]);
        }
        else if (c1_start < 0 && c1_end >= 0){
            x_start_1.push_back(x_start[i] + (c1_start / (c1_start - c1_end)) * (x_end[i] - x_start[i]));
            x_end_1.push_back(x_end[i]);    
            y_start_1.push_back(y_start[i] + (c1_start / (c1_start - c1_end)) * (y_end[i] - y_start[i]));
            y_end_1.push_back(y_end[i]);
            z_start_1.push_back(z_start[i] + (c1_start / (c1_start - c1_end)) * (z_end[i] - z_start[i]));
            z_end_1.push_back(z_end[i]);
        }
        else if (c1_start >= 0 && c1_end < 0){
            x_start_1.push_back(x_start[i]);
            x_end_1.push_back(x_start[i] + (c1_start / (c1_start - c1_end)) * (x_end[i] - x_start[i]));
            y_start_1.push_back(y_start[i]);
            y_end_1.push_back(y_start[i] + (c1_start / (c1_start - c1_end)) * (y_end[i] - y_start[i]));
            z_start_1.push_back(z_start[i]);
            z_end_1.push_back(z_start[i] + (c1_start / (c1_start - c1_end)) * (z_end[i] - z_start[i]));    
        }
    }
    //cout << "1+xʼ size: " << x_start.size() << ", clipping 1+xʼ size: " << x_start_1.size() << endl; 

    // c2 boundary
    vector<float> x_start_2;
    vector<float> x_end_2;
    vector<float> y_start_2;
    vector<float> y_end_2;
    vector<float> z_start_2;
    vector<float> z_end_2;
    for (int i = 0; i < x_start_1.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c2_start = 1 - x_start_1[i];
        float c2_end = 1 - x_end_1[i];
        if (c2_start < 0 && c2_end < 0){
            // do nothing
        }
        else if (c2_start >= 0 && c2_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_2.push_back(x_start_1[i]);
            x_end_2.push_back(x_end_1[i]);
            y_start_2.push_back(y_start_1[i]);
            y_end_2.push_back(y_end_1[i]);
            z_start_2.push_back(z_start_1[i]);
            z_end_2.push_back(z_end_1[i]);
        }
        else if (c2_start < 0 && c2_end >= 0){
            x_start_2.push_back(x_start_1[i] + (c2_start / (c2_start - c2_end)) * (x_end_1[i] - x_start_1[i]));
            x_end_2.push_back(x_end_1[i]);  
            y_start_2.push_back(y_start_1[i] + (c2_start / (c2_start - c2_end)) * (y_end_1[i] - y_start_1[i]));
            y_end_2.push_back(y_end_1[i]);
            z_start_2.push_back(z_start_1[i] + (c2_start / (c2_start - c2_end)) * (z_end_1[i] - z_start_1[i]));
            z_end_2.push_back(z_end_1[i]); 
        }
        else if (c2_start >= 0 && c2_end < 0){
            x_start_2.push_back(x_start_1[i]);
            x_end_2.push_back(x_start_1[i] + (c2_start / (c2_start - c2_end)) * (x_end_1[i] - x_start_1[i]));    
            y_start_2.push_back(y_start_1[i]);
            y_end_2.push_back(y_start_1[i] + (c2_start / (c2_start - c2_end)) * (y_end_1[i] - y_start_1[i]));
            z_start_2.push_back(z_start_1[i]);
            z_end_2.push_back(z_start_1[i] + (c2_start / (c2_start - c2_end)) * (z_end_1[i] - z_start_1[i]));
        }
    }
    //cout << "1-xʼ size: " << x_start_1.size() << ", clipping 1-xʼ size: " << x_start_2.size() << endl; 
    
    // c3 boundary
    vector<float> x_start_3;
    vector<float> x_end_3;
    vector<float> y_start_3;
    vector<float> y_end_3;
    vector<float> z_start_3;
    vector<float> z_end_3;
    for (int i = 0; i < x_start_2.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c3_start = 1 + y_start_2[i];
        float c3_end = 1 + y_end_2[i];
        if (c3_start < 0 && c3_end < 0){
            // do nothing
        }
        else if (c3_start >= 0 && c3_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_3.push_back(x_start_2[i]);
            x_end_3.push_back(x_end_2[i]);
            y_start_3.push_back(y_start_2[i]);
            y_end_3.push_back(y_end_2[i]);
            z_start_3.push_back(z_start_2[i]);
            z_end_3.push_back(z_end_2[i]);
        }
        else if (c3_start < 0 && c3_end >= 0){
            x_start_3.push_back(x_start_2[i] + (c3_start / (c3_start - c3_end)) * (x_end_2[i] - x_start_2[i]));
            x_end_3.push_back(x_end_2[i]);    
            y_start_3.push_back(y_start_2[i] + (c3_start / (c3_start - c3_end)) * (y_end_2[i] - y_start_2[i]));
            y_end_3.push_back(y_end_2[i]);
            z_start_3.push_back(z_start_2[i] + (c3_start / (c3_start - c3_end)) * (z_end_2[i] - z_start_2[i]));
            z_end_3.push_back(z_end_2[i]);
        }
        else if (c3_start >= 0 && c3_end < 0){
            x_start_3.push_back(x_start_2[i]);
            x_end_3.push_back(x_start_2[i] + (c3_start / (c3_start - c3_end)) * (x_end_2[i] - x_start_2[i]));
            y_start_3.push_back(y_start_2[i]);
            y_end_3.push_back(y_start_2[i] + (c3_start / (c3_start - c3_end)) * (y_end_2[i] - y_start_2[i]));
            z_start_3.push_back(z_start_2[i]);
            z_end_3.push_back(z_start_2[i] + (c3_start / (c3_start - c3_end)) * (z_end_2[i] - z_start_2[i]));    
        }
    }
    //cout << "1+yʼ size: " << x_start_2.size() << ", clipping 1+yʼ size: " << x_start_3.size() << endl; 

    // c4 boundary
    vector<float> x_start_4;
    vector<float> x_end_4;
    vector<float> y_start_4;
    vector<float> y_end_4;
    vector<float> z_start_4;
    vector<float> z_end_4;
    for (int i = 0; i < x_start_3.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c4_start = 1 - y_start_3[i];
        float c4_end = 1 - y_end_3[i];
        if (c4_start < 0 && c4_end < 0){
            // do nothing
        }
        else if (c4_start >= 0 && c4_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_4.push_back(x_start_3[i]);
            x_end_4.push_back(x_end_3[i]);
            y_start_4.push_back(y_start_3[i]);
            y_end_4.push_back(y_end_3[i]);
            z_start_4.push_back(z_start_3[i]);
            z_end_4.push_back(z_end_3[i]);
        }
        else if (c4_start < 0 && c4_end >= 0){
            x_start_4.push_back(x_start_3[i] + (c4_start / (c4_start - c4_end)) * (x_end_3[i] - x_start_3[i]));
            x_end_4.push_back(x_end_3[i]);    
            y_start_4.push_back(y_start_3[i] + (c4_start / (c4_start - c4_end)) * (y_end_3[i] - y_start_3[i]));
            y_end_4.push_back(y_end_3[i]);
            z_start_4.push_back(z_start_3[i] + (c4_start / (c4_start - c4_end)) * (z_end_3[i] - z_start_3[i]));
            z_end_4.push_back(z_end_3[i]);
        }
        else if (c4_start >= 0 && c4_end < 0){
            x_start_4.push_back(x_start_3[i]);
            x_end_4.push_back(x_start_3[i] + (c4_start / (c4_start - c4_end)) * (x_end_3[i] - x_start_3[i]));
            y_start_4.push_back(y_start_3[i]);
            y_end_4.push_back(y_start_3[i] + (c4_start / (c4_start - c4_end)) * (y_end_3[i] - y_start_3[i]));
            z_start_4.push_back(z_start_3[i]);
            z_end_4.push_back(z_start_3[i] + (c4_start / (c4_start - c4_end)) * (z_end_3[i] - z_start_3[i]));   
        }
    }
    //cout << "1-yʼ size: " << x_start_3.size() << ", clipping 1-yʼ size: " << x_start_4.size() << endl; 

    // c5 boundary
    vector<float> x_start_5;
    vector<float> x_end_5;
    vector<float> y_start_5;
    vector<float> y_end_5;
    vector<float> z_start_5;
    vector<float> z_end_5;
    for (int i = 0; i < x_start_4.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c5_start = 0 + z_start_4[i];
        float c5_end = 0 + z_end_4[i];
        if (c5_start < 0 && c5_end < 0){
            // do nothing
        }
        else if (c5_start >= 0 && c5_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_5.push_back(x_start_4[i]);
            x_end_5.push_back(x_end_4[i]);
            y_start_5.push_back(y_start_4[i]);
            y_end_5.push_back(y_end_4[i]);
            z_start_5.push_back(z_start_4[i]);
            z_end_5.push_back(z_end_4[i]);
        }
        else if (c5_start < 0 && c5_end >= 0){
            x_start_5.push_back(x_start_4[i] + (c5_start / (c5_start - c5_end)) * (x_end_4[i] - x_start_4[i]));
            x_end_5.push_back(x_end_4[i]);    
            y_start_5.push_back(y_start_4[i] + (c5_start / (c5_start - c5_end)) * (y_end_4[i] - y_start_4[i]));
            y_end_5.push_back(y_end_4[i]);
            z_start_5.push_back(z_start_4[i] + (c5_start / (c5_start - c5_end)) * (z_end_4[i] - z_start_4[i]));
            z_end_5.push_back(z_end_4[i]);
        }
        else if (c5_start >= 0 && c5_end < 0){
            x_start_5.push_back(x_start_4[i]);
            x_end_5.push_back(x_start_4[i] + (c5_start / (c5_start - c5_end)) * (x_end_4[i] - x_start_4[i]));
            y_start_5.push_back(y_start_4[i]);
            y_end_5.push_back(y_start_4[i] + (c5_start / (c5_start - c5_end)) * (y_end_4[i] - y_start_4[i]));
            z_start_5.push_back(z_start_4[i]);
            z_end_5.push_back(z_start_4[i] + (c5_start / (c5_start - c5_end)) * (z_end_4[i] - z_start_4[i]));
        }
    }
    //cout << "0+zʼ size: " << x_start_4.size() << ", clipping 0+zʼ size: " << x_start_5.size() << endl; 

    vector<float> x_start_6;
    vector<float> x_end_6;
    vector<float> y_start_6;
    vector<float> y_end_6;
    vector<float> z_start_6;
    vector<float> z_end_6;
    // c6 boundary
    for (int i = 0; i < x_start_5.size(); i++){
        //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
        float c6_start = 1 - z_start_5[i];
        float c6_end = 1 - z_end_5[i];
        if (c6_start < 0 && c6_end < 0){
            // do nothing
        }
        else if (c6_start >= 0 && c6_end >= 0){
            //cout << "x start: " << x_start[i] << ", x end: " << x_end[i] << endl;
            x_start_6.push_back(x_start_5[i]);
            x_end_6.push_back(x_end_5[i]);
            y_start_6.push_back(y_start_5[i]);
            y_end_6.push_back(y_end_5[i]);
            z_start_6.push_back(z_start_5[i]);
            z_end_6.push_back(z_end_5[i]);
        }
        else if (c6_start < 0 && c6_end >= 0){
            x_start_6.push_back(x_start_5[i] + (c6_start / (c6_start - c6_end)) * (x_end_5[i] - x_start_5[i]));
            x_end_6.push_back(x_end_5[i]);    
            y_start_6.push_back(y_start_5[i] + (c6_start / (c6_start - c6_end)) * (y_end_5[i] - y_start_5[i]));
            y_end_6.push_back(y_end_5[i]);
            z_start_6.push_back(z_start_5[i] + (c6_start / (c6_start - c6_end)) * (z_end_5[i] - z_start_5[i]));
            z_end_6.push_back(z_end_5[i]);
        }
        else if (c6_start >= 0 && c6_end < 0){
            x_start_6.push_back(x_start_5[i]);
            x_end_6.push_back(x_start_5[i] + (c6_start / (c6_start - c6_end)) * (x_end_5[i] - x_start_5[i]));
            y_start_6.push_back(y_start_5[i]);
            y_end_6.push_back(y_start_5[i] + (c6_start / (c6_start - c6_end)) * (y_end_5[i] - y_start_5[i]));
            z_start_6.push_back(z_start_5[i]);
            z_end_6.push_back(z_start_5[i] + (c6_start / (c6_start - c6_end)) * (z_end_5[i] - z_start_5[i]));
        }
    }
    //cout << "1-zʼ size: " << x_start_5.size() << ", clipping 1-zʼ size: " << x_start_6.size() << endl; 

    for (int i = 0; i < x_start_6.size(); i++){
        x_start_view.push_back(x_start_6[i]);
        x_end_view.push_back(x_end_6[i]);
        y_start_view.push_back(y_start_6[i]);
        y_end_view.push_back(y_end_6[i]);
        z_start_view.push_back(z_start_6[i]);
        z_end_view.push_back(z_end_6[i]);
    }
}

void Show(){
    DeleteZData();
    //cout << "before delete triangle: " << obj_fv1_arr.size() << ", after delete triangle: " << obj_fv1_arr_see.size() << endl;
    Clipping();
    float scale_x = 0.5 * (right_boundary - left_boundary);
    float scale_y = 0.5 * (top_boundary - botton_boundary);
    float scale_z = 0;
    float translate_x = 0.5 * (right_boundary + left_boundary);
    float translate_y = 0.5 * (top_boundary + botton_boundary);
    float translate_z = 0;
    float view_scale_matrix[ROWS][COLUMNS] = {
        {scale_x,     0.0,     0.0, 0.0},
        {    0.0, scale_y,     0.0, 0.0},
        {    0.0,     0.0, scale_z, 0.0},
        {    0.0,     0.0,     0.0, 1.0}
    };
    float point[4] = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < x_start_view.size(); i++){
        point[0] = x_start_view[i];
        point[1] = y_start_view[i];
        point[2] = z_start_view[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << point[3] << endl;
        Multiply_point(view_scale_matrix, point);
        x_start_view[i] = Point_matrix[0];
        y_start_view[i] = Point_matrix[1];
        z_start_view[i] = Point_matrix[2];
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << Point_matrix[3] << endl;
        point[0] = x_end_view[i];
        point[1] = y_end_view[i];
        point[2] = z_end_view[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << point[3] << endl;
        Multiply_point(view_scale_matrix, point);
        x_end_view[i] = Point_matrix[0];
        y_end_view[i] = Point_matrix[1];
        z_end_view[i] = Point_matrix[2];
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << Point_matrix[3] << endl;
    }
    float view_translate_matrix[ROWS][COLUMNS]= {
        {1.0, 0.0, 0.0, translate_x},
        {0.0, 1.0, 0.0, translate_y},
        {0.0, 0.0, 1.0, translate_z},
        {0.0, 0.0, 0.0,         1.0}
    };
    for (int i = 0; i < x_start_view.size(); i++){
        point[0] = x_start_view[i];
        point[1] = y_start_view[i];
        point[2] = z_start_view[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << point[3] << endl;
        Multiply_point(view_translate_matrix, point);
        x_start_view[i] = Point_matrix[0];
        y_start_view[i] = Point_matrix[1];
        z_start_view[i] = Point_matrix[2];
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << Point_matrix[3] << endl;
        point[0] = x_end_view[i];
        point[1] = y_end_view[i];
        point[2] = z_end_view[i];
        point[3] = 1.0;
        //cout << "   before: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << point[3] << endl;
        Multiply_point(view_translate_matrix, point);
        x_end_view[i] = Point_matrix[0];
        y_end_view[i] = Point_matrix[1];
        z_end_view[i] = Point_matrix[2];
        //cout << "    after: x = " << obj_v1_arr[i]  << ", y = " << obj_v2_arr[i]  << ", z = " << obj_v3_arr[i] << endl;
        //cout << Point_matrix[3] << endl;
    }
    glPointSize(0.1);
    glBegin(GL_POINTS);

    //for (int i = 0; i < obj_v1_arr_view.size(); i++){
    //    glVertex2i(obj_v1_arr_view[i], obj_v2_arr_view[i]);    
    //}
    //cout << "obj size: "<< obj_fv1_arr.size() << endl;
    /*
    for (int i = 0; i < obj_fv1_arr.size(); i++){
        //cout << i << endl;
        float x1 = obj_v1_arr_view[obj_fv1_arr[i] - 1];
        float x2 = obj_v1_arr_view[obj_fv2_arr[i] - 1];
        float x3 = obj_v1_arr_view[obj_fv3_arr[i] - 1];
        float y1 = obj_v2_arr_view[obj_fv1_arr[i] - 1];
        float y2 = obj_v2_arr_view[obj_fv2_arr[i] - 1];
        float y3 = obj_v2_arr_view[obj_fv3_arr[i] - 1];
        //cout << "point1 = ( " << x1 << ", " << y1 << ")" << endl;
        //cout << "point2 = ( " << x2 << ", " << y2 << ")" << endl;
        //cout << "point3 = ( " << x3 << ", " << y3 << ")" << endl;
        DrawATriangle(x1, x2, x3, y1, y2, y3);
    }
    */
    for (int i = 0; i < x_start_view.size(); i++){
        float x1 = x_start_view[i];
        float x2 = x_end_view[i];
        float y1 = y_start_view[i];
        float y2 = y_end_view[i];
        drawALine(x1, x2, y1, y2, 1.0, 0.0, 0.0);
    }
    glColor3f(1.0, 1.0, 1.0);    
    drawALine(left_boundary, left_boundary, top_boundary, botton_boundary, 1.0, 1.0, 1.0);
    drawALine(left_boundary, right_boundary, botton_boundary, botton_boundary, 1.0, 1.0, 1.0);
    drawALine(right_boundary, right_boundary, botton_boundary, top_boundary, 1.0, 1.0, 1.0);
    drawALine(right_boundary, left_boundary, top_boundary, top_boundary, 1.0, 1.0, 1.0);
    glEnd();
    glutSwapBuffers();
    obj_v1_arr_view.clear();
    obj_v2_arr_view.clear();
    obj_v3_arr_view.clear();
    obj_fv1_arr_see.clear();
    obj_fv2_arr_see.clear();
    obj_fv3_arr_see.clear();
    x_start_view.clear();
    x_end_view.clear();
    y_start_view.clear();
    y_end_view.clear();
    z_start_view.clear();
    z_end_view.clear();
    
}

void display() {

    fstream fp;
    fp.open(in_path, ios::in);
    if (!fp) {
        //cout << "Failed to open the file.\n";
        exit(0);
    }
    else {
        //cout << "open!!" << endl;
    }
    string InputLine, Instruction;
    int a = 0;
    while (getline(fp, InputLine)) {
        a = 0;
        while (a < 1) {
            cout << endl;
            a++;
            Instruction = InputLine.substr(0, InputLine.find(" "));
            if (a == 1) {
                if (Instruction == "reset") {
                    cout << "Reset" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLUMNS; j++) {
                            Transform_matrix[i][j] = Unit_matrix[i][j];
                        }
                    }
                }
                else if (Instruction == "translate") {
                    cout << "translate ";
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    cout << InputLine << endl;
                    Arrange(InputLine);
                    //cout << "   tx = " << tmpArrange[0] << ", ty = " << tmpArrange[1] << ", tz = " << tmpArrange[2] << endl;
                    Translate(tmpArrange[0], tmpArrange[1], tmpArrange[2]);
                }
                else if (Instruction == "scale") {
                    cout << "scale ";
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    cout << InputLine << endl;
                    Arrange(InputLine);
                    //cout << "   sx = " << tmpArrange[0] << ", sy = " << tmpArrange[1] << ", sz = " << tmpArrange[2] << endl;
                    Scale(tmpArrange[0], tmpArrange[1], tmpArrange[2]);
                }
                else if (Instruction == "rotate") {
                    cout << "Rotate ";
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    cout << InputLine << endl;
                    Arrange(InputLine);
                    //cout << "   thetax = " << tmpArrange[0] << ", thetay = " << tmpArrange[1] << ", thetaz = " << tmpArrange[2] << endl;
                    Rotate(tmpArrange[0], tmpArrange[1], tmpArrange[2]);
                }
                else if (Instruction == "clearData") {
                    cout << "clearData" << endl;
                    //ClearData();
                }
                else if (Instruction == "clearScreen") {
                    cout << "clearScreen" << endl;
                    //glClear(GL_COLOR_BUFFER_BIT);
                    //glutSwapBuffers();
                }
                else if (Instruction == "end") {
                    cout << "End" << endl;
                    exit(0);
                }
                else if (Instruction == "object") {
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.find(".obj") - 3);
                    ReadOBJFile(InputLine);
                    //cout << "Object" << endl;
                    //cout << "filename: " << InputLine << "hii" << endl;
                }
                else if (Instruction == "observer") {
                    cout << "Observer" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //cout << InputLine << endl;
                    Arrange(InputLine);
                    //cout << "   CAMERA POSITION: epx = " << tmpArrange[0] << ",  epy = " << tmpArrange[1] << ",  epz = " << tmpArrange[2] << endl;
                    //cout << "   CAMERA VIEW: COIx = " << tmpArrange[3] << ", COIy = " << tmpArrange[4] << ", COIz = " << tmpArrange[5] << endl;
                    //cout << "   CAMERA: Tilt angle = " << tmpArrange[6] << endl;
                    //cout << "   VIEW: Hither = " << tmpArrange[7] << ", Yon = " << tmpArrange[8] << ", Hav = " << tmpArrange[9] << endl;
                    Observer(tmpArrange[0], tmpArrange[1], tmpArrange[2], tmpArrange[3], tmpArrange[4], tmpArrange[5], tmpArrange[6]);
                    cout << endl << "M Matrix" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLUMNS; j++) {
                            cout << " " << M_matrix[i][j];
                        }
                        cout << endl;
                    }  
                    cout << endl << "V Matrix" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLUMNS; j++) {
                            cout << " " << V_matrix[i][j];
                        }
                        cout << endl;
                    }
                    WorldtoEye();   
                    Projection(tmpArrange[7], tmpArrange[8], tmpArrange[9]);       
                    cout << endl << "P Matrix" << endl;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLUMNS; j++) {
                            cout << " " << P_matrix[i][j];
                        }
                        cout << endl;
                    }
                    EyetoProject();           
                }
                else if (Instruction == "viewport") {
                    cout << "Viewport" << endl;
                    InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    Arrange(InputLine);
                    //cout << "   vxl = " << tmpArrange[0] << ", vxr = " << tmpArrange[1] << ", vyb = " << tmpArrange[2] << ", vyt = " << tmpArrange[3] << endl;
                    left_boundary = 0.5 * Width * tmpArrange[0] + 0.5 * Width;
                    right_boundary = 0.5 * Width * tmpArrange[1] + 0.5 * Width;
                    botton_boundary = 0.5 * Height * tmpArrange[2] + 0.5 * Height;
                    top_boundary = 0.5 * Height * tmpArrange[3] + 0.5 * Height;
                    //cout << "W = " << Width << ", H = " << Height << endl;
                    //cout << "   l = " << left_boundary << ", r = " << right_boundary << ", b = " << botton_boundary << ", t = " << top_boundary << endl;

                }
                else if (Instruction == "display") {
                    cout << "Display" << endl;
                    glClear(GL_COLOR_BUFFER_BIT);
                    glutSwapBuffers();
                    //InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
                    //ArrangeBySpace(InputLine);
                    //VIEW(tmpArrange[0], tmpArrange[1], tmpArrange[2], tmpArrange[3], tmpArrange[4], tmpArrange[5], tmpArrange[6], tmpArrange[7]);
                    //View();
                    Show();
                    fgetc(stdin);
                }
                else if (Instruction == "#") {
                    break;
                }
                else if (Instruction == "") {
                    break;
                }
                else {
                    break;
                }
            }
            InputLine = InputLine.substr(InputLine.find(" ") + 1, InputLine.length());
            if (InputLine.find(" ") == -1) {
                break;
            }
        }
    }
    fp.close();
    
}



int tmp[2] = {0, 0};
void GetSizeOfWindow(){
    int a = 0;
    fstream fp;
    string InputLine;
    fp.open(in_path, ios::in);
    getline(fp, InputLine);
    fp.close();
    int current = 0;
    int next;
    while (1){
        next = InputLine.find_first_of(" ", current);
        if (next != current){
            string tmpstring = InputLine.substr(current, next - current);
            if (tmpstring.size() != 0){
                tmp[a] = stoi(tmpstring);
                a++;
            }
        }
        if (next == string::npos) break;
        current = next + 1;
    }
}

int main(int argc, char* argv[]) {
    filename = argv[1];
    in_path.append("../Data/").append(filename);
    //cout << in_path << endl;
    GetSizeOfWindow();
    Width = tmp[0];
    Height = tmp[1];
    glutInit(&argc, argv);
    fgetc(stdin);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 10);
    gluOrtho2D(0, Width, 0, Height);

    glutCreateWindow("Your First GLUT Window!");
    glutDisplayFunc(display);
    gluOrtho2D(0, Width, 0, Height);
    glutMainLoop();

    return 0;
}

void drawALine(int x_start, int x_end, int y_start, int y_end, float R, float G, float B) {
    //cout << "drawALine" << endl;
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    if (abs(dy) < abs(dx)) {
        if (x_end > x_start) {
            for (i = x_start; i <= x_end; i++) {
                glColor3f(R, G, B);
                glVertex2i(i, round(y_start + dy * (i - x_start) / dx));
                //savePixel(i, (int)round(y_start + dy * (i - x_start) / dx), R, G, B);
            }
        }
        else {
            for (i = x_start; i >= x_end; i--) {
                glColor3f(R, G, B);
                glVertex2i(i, round(y_start + dy * (i - x_start) / dx));
                //savePixel(i, (int)round(y_start + dy * (i - x_start) / dx), R, G, B);
            }
        }
    }
    else if (abs(dx) == 0 && abs(dy) == 0) {
        glColor3f(R, G, B);
        glVertex2i(x_start, y_start);
        //savePixel(x_start, y_start, , G, B);
    }
    else if (abs(dx) <= abs(dy)) {
        if (y_end > y_start) {
            for (i = y_start; i <= y_end; i++) {
                glColor3f(R, G, B);
                glVertex2i(round(x_start + dx * (i - y_start) / dy), i);
                //savePixel((int)round(x_start + dx * (i - y_start) / dy), i, R, G, B);
            }
        }
        else {
            for (i = y_start; i >= y_end; i--) {
                glColor3f(R, G, B);
                glVertex2i(round(x_start + dx * (i - y_start) / dy), i);
                //savePixel((int)round(x_start + dx * (i - y_start) / dy), i, R, G, B);
            }
        }
    }
}