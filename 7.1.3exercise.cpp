#include <iostream>
#include <string>

using namespace std;

class Sale_book{   //class 默认 private  struct 默认 public  一般是操作函数公开数据类型私有
public:
    string bookNo;
    double revenue;
    double sales_volume;

    Sale_book() = default;
    Sale_book(const string & s) : bookNo(s){}
    Sale_book(const string & s, double & n, double & p) : bookNo(s),revenue(n),sales_volume(p){}

    string isISBN() const;
    Sale_book & combine(const Sale_book &);
    double unit_price(Sale_book &);
};

class Screen{
public:
    typedef string::size_type pos;  //pos 相当于无符号int
    Screen() = default;
    Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht * wd,c){}
    char get() const { return contents[cursor];}
    char get(pos r, pos c) const;
    Screen &move(pos r, pos c);

    Screen & set(char);
    Screen & set(pos, pos , char);

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
    mutable string :: size_type  star = 10;
};

Screen & Screen::move(pos r, pos c) {
    pos row = r*width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r,pos c) const {
    pos row = r*width;
    return contents[row + c];
}

Screen & Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

Screen & Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;
    return *this;
}

string Sale_book::isISBN() const {
    return bookNo;
}

Sale_book & Sale_book::combine(const Sale_book & lhs)
{
    sales_volume += lhs.sales_volume;
    revenue += lhs.revenue;
    return *this;   //this 是常量指针
}

double Sale_book::unit_price(Sale_book &lhs)
{
    if(lhs.revenue)
        return lhs.revenue/lhs.sales_volume;
    else
        return 0;
}

Sale_book & add(const Sale_book & total , const Sale_book & trans)
{
    Sale_book sum = total;
    sum.combine(trans);
    return sum;
}

void read(Sale_book & input)
{
    cin >> input.bookNo >> input.revenue >> input.sales_volume;
}

void print(Sale_book & output)
{
    cout << output.bookNo << " " << output.revenue << " " << output.sales_volume;
}

int main(){
    //友元 不是类的操作函数但是想要访问类的私有元素则将改函数定义为友元函数 friend  友元不是类成员

    //可变数据成员，当我们希望修改某个数据成员，即使是一个const成员， 可在变量声明种加入mutable

    string America;
    char CCC = 'H';
    string::size_type v = 10;
    America = (v,CCC);
    cout << v << endl;
    cout << America[0] <<endl;
    Screen myScreen;
    myScreen.move(4,0).set('#');

    return 0;
}

