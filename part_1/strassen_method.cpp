#include <bits/stdc++.h>

class int_matrix{
    private:
        std::vector<int> m;
        size_t dim_x, dim_y;
    public:
    
        int_matrix(size_t dimy, size_t dimx){
            dim_y = dimy;
            dim_x = dimx;

            m.resize(dim_y * dim_x);
        }

        int_matrix(int_matrix &copy){
            dim_x = copy.dim_x;
            dim_y = copy.dim_y;
            m = copy.m;
        }

        int &at(size_t line, size_t column){
            if(line >= dim_y || column >= dim_x){
                throw std::out_of_range("matrix indices out of range");
            }

            return m[dim_x * line + column];
        }

        size_t get_dim_x(void){
            return dim_x;
        }

        size_t get_dim_y(void){
            return dim_y;
        }
};

inline int_matrix operator+(int_matrix &a, int_matrix &b){
    if(a.get_dim_x() != b.get_dim_x() || a.get_dim_y() != b.get_dim_y()){
        std::cout << "tamanhos errados" << std::endl;
        return int_matrix(0,0);
    }

    int_matrix result(a.get_dim_x(),a.get_dim_x());
    
    for(size_t i = 0; i < a.get_dim_y(); i++){
        for(size_t j = 0; j < a.get_dim_y(); j++){
            result.at(i,j) = a.at(i,j) + b.at(i,j);
        }
    }

    return result;
}

inline int_matrix operator-(int_matrix &a, int_matrix &b){
    if(a.get_dim_x() != b.get_dim_x() || a.get_dim_y() != b.get_dim_y()){
        std::cout << "tamanhos errados" << std::endl;
        return int_matrix(0,0);
    }

    int_matrix result(a.get_dim_x(),a.get_dim_x());
    
    for(size_t i = 0; i < a.get_dim_y(); i++){
        for(size_t j = 0; j < a.get_dim_y(); j++){
            result.at(i,j) = a.at(i,j) - b.at(i,j);
        }
    }

    return result;
}



inline int_matrix matrix_multiplication(int_matrix &a, int_matrix &b){
    if(a.get_dim_x() != b.get_dim_x()){
        std::cout << "tamanhos errados" << std::endl;
        return int_matrix(0,0);
    }

    int_matrix result(a.get_dim_x(),a.get_dim_x());
    for(size_t i = 0; i < a.get_dim_x(); i++){
        for(size_t j = 0; j < a.get_dim_x(); j++){
            
            int sum = 0;

            for(size_t k = 0; k < a.get_dim_x(); k++){
                sum += a.at(i,k) + b.at(k,j);
            }

            result.at(i,j) = sum;
        }
    }
     
}

int_matrix sum_sub_matrix(size_t fst_y_pos, size_t fst_x_pos, size_t scd_y_pos, size_t scd_x_pos,size_t size, int_matrix &a, int_matrix &b){
    int_matrix result(size,size);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            result.at(i,j) = a.at(i + fst_y_pos, j + fst_x_pos) + b.at(i + scd_y_pos, j + scd_x_pos) ;
        }
    }
    return result;

}


int_matrix sub_sub_matrix(size_t fst_y_pos, size_t fst_x_pos, size_t scd_y_pos, size_t scd_x_pos,size_t size, int_matrix &a, int_matrix &b){
    int_matrix result(size,size);
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            result.at(i,j) = a.at(i + fst_y_pos, j + fst_x_pos) - b.at(i + scd_y_pos, j + scd_x_pos) ;
        }
    }
    return result;

}

// int_maethod(int_matrix &a, int_matrix &b){}

int_matrix sub_strassen(size_t line, size_t col, size_t size, int_matrix &a, int_matrix &b){
    if(size > 1){
        size_t y_middle = line + size/2;
        size_t x_middle = col + size/2;

        int_matrix s_1 = sub_sub_matrix(line,x_middle,y_middle,x_middle,size/2,b,b); //b12 - b22
        int_matrix s_2 = sum_sub_matrix(line,col,line,x_middle,size/2,a,a); //a11 + a12
        int_matrix s_3 = sum_sub_matrix(y_middle,col,y_middle,x_middle,size/2,a,a); // a21 + a22
        int_matrix s_4 = sub_sub_matrix(y_middle,col,line,col,size/2,b,b); //b21 - b11
        int_matrix s_5 = sum_sub_matrix(line,col,y_middle,x_middle,size/2,a,a); //a11 + a22
        int_matrix s_6 = sum_sub_matrix(line,col,y_middle,x_middle,size/2,b,b); //b11 + b22
        int_matrix s_7 = sub_sub_matrix(line,x_middle,y_middle,x_middle,size/2,a,a); //a12 - a22
        int_matrix s_8 = sum_sub_matrix(y_middle,col,y_middle,x_middle,size/2,b,b); // b21 + b22
        int_matrix s_9 = sub_sub_matrix(line,col,y_middle,col,size/2,a,a); //a11 - a21
        int_matrix s_10 = sum_sub_matrix(line,col,line,x_middle,size/2,b,b); //b11 + b12

    }

    return int_matrix(0,0);
}


int main(void){
    int_matrix test(5,5);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            test.at(i,j) = (i+1)*(j+1);
        }
    }

    int_matrix result = sum_sub_matrix(0,0,0,0,5,test,test);
    for(int i = 0; i < 5 ; i++ ){
        for(int j = 0; j < 5 ; j++){
            std::cout << result.at(i,j) << " ";
        }
        std::cout << "\n";
    }

    return 0;

}