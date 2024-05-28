// Chương trình tính gần đúng tích phân xác định bằng phương pháp Simpson

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>
#include <sstream>
#include <string>
#include <D:/Programming Projects/PPT_Nhom_2/exprtk-master/exprtk.hpp>

using namespace std;

// Biểu diễn hàm số bằng chuỗi
string expression_string;
// Biến x trong biểu thức
double x;
// Biểu thức
exprtk::expression<double> expression;
// Biểu thức biên dịch
exprtk::parser<double> parser;
// Symbol table
exprtk::symbol_table<double> symbol_table;

// Hàm tính giá trị của hàm số tại x
double f(double x_val)
{
    x = x_val;
    return expression.value();
}

// Hàm tính gần đúng tích phân xác định bằng phương pháp Simpson
double simpson(double a, double b, int n)
{
    int interval = n;
    double h = (b - a) / interval;

    // Tính các giá trị x_i và y_i
    vector<double> x(interval + 1), y(interval + 1);
    for (int i = 0; i <= interval; ++i)
    {
        x[i] = a + i * h;
        y[i] = f(x[i]);
    }

    // In ra bảng giá trị
    cout << setw(5) << "interval" << setw(15) << "x" << setw(15) << "y" << endl;
    for (int i = 0; i <= interval; ++i)
    {
        cout << setw(5) << i << setw(15) << x[i] << setw(15) << y[i] << endl;
    }

    // Tính các thành phần của biểu thức I_s
    double y0_yn = y[0] + y[interval];
    double y_odd = 0;
    for (int i = 1; i < interval; i += 2)
    {
        y_odd += y[i];
    }
    double y_even = 0;
    for (int i = 2; i < interval; i += 2)
    {
        y_even += y[i];
    }

    // In ra biểu thức I_s
    cout << "I_s = " << h << "/3 * [" << y0_yn << " + 4(" << y_odd << ") + 2(" << y_even << ")]" << endl;

    // Tính I_s
    return (h / 3)* (y0_yn + 4 * y_odd + 2 * y_even);
}

int main()
{

    // Nhập giới hạn dưới và giới hạn trên của vùng tích phân và xử lý các trường hợp không hợp lệ
    double a, b;
    cout << "Nhập giới hạn dưới a: ";
    while (!(cin >> a))
    {
        cout << "Giới hạn dưới không hợp lệ, xin vui lòng nhập lại: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nhập giới hạn trên b: ";
    while (!(cin >> b) || b <= a)
    {
        cout << "Giới hạn trên không hợp lệ, xin vui lòng nhập lại: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    bool valid_expression = false;
    do
    {
        // Nhập biểu thức hàm số từ người dùng
        cout << "Nhập biểu thức hàm số (ví dụ: sin(x) + x^2 - 1/x): ";
        getline(cin, expression_string);

        // Thêm biến x vào symbol table
        symbol_table.add_variable("x", x);

        //  Đăng ký symbol table với biểu thức
        expression.register_symbol_table(symbol_table);
        
        // Biên dịch biểu thức
        if (parser.compile(expression_string, expression))
        {
            valid_expression = true;
        }
        else
        {
            cout << "Biểu thức không hợp lệ. Vui lòng nhập lại.\n";
        }
    } while (!valid_expression);


    // Nhập số khoảng chia và xử lý các trường hợp không hợp lệ
    int n = 0;
    cout << "Nhập số khoảng chia: ";

    while (!(cin >> n) || n <= 0)
    {
        cout << "Khoảng chia không hợp lệ, xin vui lòng nhập lại: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    double result = 0;
    result = simpson(a, b, n);
    
    // In ra kết quả
    cout << "Dừng lại sau " << n << " bước chia.\n";
    cout << fixed << setprecision(4);
    cout << "Giá trị gần đúng của tích phân là: " << result << endl;

    return result;
}