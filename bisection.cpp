// Chương trình giải phương trình đa thức bằng phương pháp chia đôi

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

// Hàm chia đôi
void bisection(double a, double b, double saiso)
{
    double c, tolerance;
    int n = 0;

    // In tiêu đề cho bảng kết quả
    cout << left << setw(5) << "n"
         << setw(12) << "a"
         << setw(12) << "b"
         << setw(12) << "c"
         << setw(12) << "f(c)"
         << setw(12) << "tolerance" << endl;
    do
    {
        // Tính điểm chính giữa của khoảng [a, b]
        c = (a + b) / 2.0;
        // Tính sai số giữa b và a
        tolerance = b - a;

        // In kết quả của lần lặp hiện tại
        cout << left << setw(5) << n
             << setw(12) << setprecision(4) << fixed << a
             << setw(12) << setprecision(4) << fixed << b
             << setw(12) << setprecision(4) << fixed << c
             << setw(12) << setprecision(4) << fixed << f(c)
             << setw(12) << setprecision(4) << fixed << tolerance << endl;

        // Kiểm tra nếu sai số đã nhỏ hơn sai số cho phép
        if (tolerance < saiso)
        {
            break;
        }

        // Cập nhật lại khoảng phân lý [a, b] dựa trên dấu của f(c)
        if (f(c) * f(a) < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
        n++;
    } while (tolerance >= saiso); // Lặp lại cho đến khi độ chênh lệch nhỏ hơn sai số cho phép

    // In kết quả cuối cùng sau khi kết thúc vòng lặp
    cout << "Kết thúc sau " << n << " bước.\n Ta có được 2 nghiệm gần đúng là " << a << " và " << b << "\n";
}

int main()
{
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

    // Nhập khoảng phân ly và xử lý các trường hợp không hợp lệ
    double a, b;
    bool valid_input;
    do
    {
        valid_input = true;
        cout << "Nhập khoảng phân ly [a, b] cách nhau bởi dấu cách: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        ss >> a >> b;

        if (ss.fail() || !(ss >> ws).eof() || a >= b)
        {
            cout << "Khoảng phân ly không hợp lệ. Vui lòng nhập lại.\n";
            valid_input = false;
        }
    } while (!valid_input);

    // Kiểm tra điều kiện f(a) * f(b) < 0
    if (f(a) * f(b) >= 0)
    {
        cout << "Khoảng phân ly không thỏa mãn điều kiện f(a) * f(b) < 0, vì f(a) = " << f(a) << " và f(b) = " << f(b) << ".\n";
        return 0;
    }
    cout << "f(a) * f(b) = " << f(a) << " * " << f(b) << " = " << f(a) * f(b) << " < 0, thoả mãn điều kiện f(a) * f(b) < 0" << "\n";
    // Nhập sai số và xử lý các trường hợp không hợp lệ
    double saiso;
    do
    {
        valid_input = true;
        cout << "Nhập sai số cho phép: ";
        cin >> saiso;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Sai số không hợp lệ. Vui lòng nhập lại.\n";
            valid_input = false;
        }
    } while (!valid_input);

    // Gọi hàm chia đôi với các tham số đã nhập
    bisection(a, b, saiso);

    return 1;
}