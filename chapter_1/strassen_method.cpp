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

int_matrix matrix_multiplication(int_matrix &a, int_matrix &b){

}




int main(void){

}